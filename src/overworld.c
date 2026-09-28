/* NetHack 5.0  overworld.c */
/* Open-world variant: the Overworld, a single huge outdoor level. */
/* NetHack may be freely redistributed.  See license for details. */

/*
 * The Overworld replaces the Dungeons of Doom.  It is one enormous level
 * (OW_SIZE x OW_SIZE) that is generated lazily, a chunk at a time, as the
 * hero approaches.  There are no stairs.  Depth -- which drives level
 * difficulty, monster and object generation, shop and special room
 * selection, trap types, and everything else that normally depends on
 * which dungeon level the hero is on -- is a function of the distance from
 * the center: the map is divided into concentric rings OW_RING_WIDTH cells
 * wide, and ring N has depth N.
 *
 * The center holds the sacred plaza with three high altars, one for each
 * alignment; the hero starts on the high altar of their own god.  Returning
 * there and offering the Amulet of Yendor wins the game.
 *
 * Special levels and branch dungeons (the Gnomish Mines, the Oracle,
 * Sokoban, the Quest, Medusa's island, the demon lairs of Gehennom, and so
 * on) are reached through rings of evenly spaced magic portals at the depth
 * where they belong; larger rings have more portals.  Leaving a branch
 * returns the hero to the particular portal that was used to enter it.
 *
 * Gehennom is the outermost part of the world, walled off by a ring of
 * impassable mountains.  The only way through is the Valley of the Dead,
 * reached (as in the classic game) via Medusa's island and the Castle.
 */

#include "hack.h"
#include <math.h>
#include <time.h>

extern const struct shclass shtypes[]; /* shknam.c */

/* local helpers */
staticfn unsigned ow_hash(int, int, unsigned);
staticfn int ow_vnoise(int, int, int, unsigned);
staticfn int ow_fbm(int, int, int, unsigned);
staticfn int ow_elev(int, int);
staticfn int ow_moist(int, int);
staticfn int ow_temp(int, int);
staticfn boolean ow_on_road(int, int);
staticfn void ow_set_terrain(int, int);
staticfn void ow_gen_chunk(int, int);
staticfn void ow_paint_plaza(void);
staticfn int ow_dnum_named(const char *);
staticfn void ow_add_ring(xint16, int, int);
staticfn void ow_portal_pos(const struct ow_ringinfo *, int, int *, int *);
staticfn void ow_make_portal_sites(int, int, int, int);
staticfn void ow_structures(int, int, int, int, int, int);
staticfn void ow_populate(int, int, int, int, int, int);
staticfn boolean ow_open_spot(int, int);
staticfn boolean ow_rect_clear(int, int, int, int, boolean);
staticfn boolean ow_find_spot(int, int, int, int, coord *, boolean);
staticfn void ow_house(int, int, int, int, int, boolean, int);
staticfn struct mkroom *ow_building(int, int, int, int, int, int, boolean);
staticfn void ow_town(int, int, int, int, int, boolean);
staticfn void ow_vault(int, int, int, int, int);
staticfn void ow_compound(int, int, int, int, int);
staticfn void ow_ruins(int, int, int, int, int);
staticfn void ow_shrine(int, int, int, int, int);
staticfn void ow_camp(int, int, int, int, int);
staticfn void ow_oasis(int, int, int, int, int);
staticfn void ow_graveyard(int, int, int, int, int);
staticfn void ow_hell_lair(int, int, int, int, int);
staticfn void ow_fix_walls(int, int, int, int);
staticfn int ow_pick_shoptype(int, int);
staticfn int ow_barrier_r0(void);
staticfn int ow_edge_r0(void);
staticfn void ow_place_on_portal(xint16, coordxy *, coordxy *);
staticfn boolean ow_rndspot_near(int, int, int, int, coord *, boolean);
static int ow_want_ring = 0; /* if nonzero, ow_rndspot_near() must pick a
                                spot in this ring */
staticfn void ow_generate_area(int, int, int);
staticfn boolean ow_mysterious_force(int);
staticfn int ow_circumference_portals(int);
void ow_test_hook(void);
void ow_world_dump(void);

/* hero's current depth while in the overworld, or the depth being
   generated; see depth() in dungeon.c */
#define OW_RING_OF(x, y) (ow_ring_at((x), (y)))

/* ------------------------------------------------------------------ */
/* basic geometry                                                      */
/* ------------------------------------------------------------------ */

/* integer square root */
int
ow_isqrt(long v)
{
    long r, lo = 0, hi = 65536;

    if (v <= 0)
        return 0;
    while (lo < hi) {
        r = (lo + hi + 1) / 2;
        if (r * r <= v)
            lo = r;
        else
            hi = r - 1;
    }
    return (int) lo;
}

/* distance of <x,y> from the center of the overworld */
int
ow_dist(int x, int y)
{
    long dx = x - OW_CX, dy = y - OW_CY;

    return ow_isqrt(dx * dx + dy * dy);
}

/* which ring (depth) contains map location <x,y> */
int
ow_ring_at(int x, int y)
{
    return 1 + ow_dist(x, y) / OW_RING_WIDTH;
}

/* compass bearing of <x,y> as seen from the center, degrees 0..359 with
   0 == east and increasing clockwise on screen (i.e. toward the south) */
int
ow_bearing(int x, int y)
{
    int dx = x - OW_CX, dy = y - OW_CY, a;
    double ang;

    if (!dx && !dy)
        return 0;
    ang = atan2((double) dy, (double) dx) * 180.0 / 3.14159265358979;
    a = (int) (ang + 360.5);
    return a % 360;
}

/* map location at distance 'r' from the center along 'bearing' */
void
ow_polar(int r, int bearing, int *x, int *y)
{
    double a = (double) bearing * 3.14159265358979 / 180.0;

    *x = OW_CX + (int) (r * cos(a) + (r * cos(a) < 0 ? -0.5 : 0.5));
    *y = OW_CY + (int) (r * sin(a) + (r * sin(a) < 0 ? -0.5 : 0.5));
}

/* radius at which the Gehennom barrier begins */
staticfn int
ow_barrier_r0(void)
{
    return (svow.barrier_ring - 1) * OW_RING_WIDTH + 5;
}

/* radius at which the world ends */
staticfn int
ow_edge_r0(void)
{
    return svow.max_ring * OW_RING_WIDTH;
}

/* is <x,y> beyond the Gehennom barrier (i.e. in Gehennom proper)? */
boolean
ow_in_gehennom(int x, int y)
{
    if (!svow.inited)
        return FALSE;
    return (boolean) (ow_dist(x, y) >= ow_barrier_r0() + 5);
}

/* is <x,y> inside the barrier ring's solid rock band (or beyond it)? */
boolean
ow_past_barrier(int x, int y)
{
    return (boolean) (svow.inited && ow_dist(x, y) >= ow_barrier_r0());
}

/* is the hero somewhere that counts as Gehennom? */
boolean
u_in_gehennom(void)
{
    if (In_hell(&u.uz))
        return TRUE;
    if (In_overworld) {
        /* while generating part of the map, it's where the generation
           is happening that matters (monster selection, etc) */
        if (ow_gen_depth > 0)
            return ow_in_gehennom(ow_gen_x, ow_gen_y);
        if (u.ux)
            return ow_in_gehennom(u.ux, u.uy);
    }
    return FALSE;
}

/* is map location <x,y> of the current level part of Gehennom? */
boolean
xy_in_gehennom(coordxy x, coordxy y)
{
    if (In_hell(&u.uz))
        return TRUE;
    if (In_overworld)
        return ow_in_gehennom(x, y);
    return FALSE;
}

/* ------------------------------------------------------------------ */
/* depth                                                               */
/* ------------------------------------------------------------------ */

/* the portal record for dungeon 'dnum', if any */
struct ow_portalrec *
ow_find_portrec(xint16 dnum)
{
    int i;

    for (i = 0; i < svow.nportrec; i++)
        if (svow.portrec[i].dnum == dnum)
            return &svow.portrec[i];
    return (struct ow_portalrec *) 0;
}

/* remember which overworld portal was used to enter dungeon 'dnum' */
void
ow_note_portal(xint16 dnum, coordxy x, coordxy y)
{
    struct ow_portalrec *pr = ow_find_portrec(dnum);

    if (!pr) {
        if (svow.nportrec >= OW_MAXPORTALS)
            return;
        pr = &svow.portrec[svow.nportrec++];
        pr->dnum = dnum;
    }
    pr->x = x, pr->y = y;
}

/* the ring holding the portals to dungeon 'dnum', or 0 */
int
ow_branch_ring(xint16 dnum)
{
    int i;

    for (i = 0; i < svow.nrings; i++)
        if (svow.rings[i].dnum == dnum)
            return svow.rings[i].ring;
    return 0;
}

/* the dungeon that the current branch dungeon was entered from, followed
   back to one that hangs directly off the overworld */
staticfn xint16 ow_root_branch(xint16);

staticfn xint16
ow_root_branch(xint16 dnum)
{
    branch *br;
    int guard = 0;

    while (dnum > 0 && guard++ < MAXDUNGEON) {
        for (br = svb.branches; br; br = br->next)
            if (br->end2.dnum == dnum && br->end1.dnum != dnum)
                break;
        if (!br)
            break;
        if (br->end1.dnum == 0)
            return dnum;
        dnum = br->end1.dnum;
    }
    return dnum;
}

/* depth of the overworld "level" as a whole; used by depth() when asked
   about the overworld: the hero's ring when there, otherwise the ring of
   the portal the hero would return through */
int
ow_level_depth(void)
{
    struct ow_portalrec *pr;
    xint16 root;

    if (ow_gen_depth > 0)
        return ow_gen_depth;
    if (!svow.inited)
        return 1;
    if (In_overworld) {
        if (!u.ux)
            return 1;
        return ow_ring_at(u.ux, u.uy);
    }
    root = ow_root_branch(u.uz.dnum);
    if ((pr = ow_find_portrec(root)) != 0)
        return ow_ring_at(pr->x, pr->y);
    if (ow_branch_ring(root))
        return ow_branch_ring(root);
    return 1;
}

/* ------------------------------------------------------------------ */
/* noise                                                               */
/* ------------------------------------------------------------------ */

staticfn unsigned
ow_hash(int x, int y, unsigned salt)
{
    unsigned h = (unsigned) x * 374761393U + (unsigned) y * 668265263U
                 + salt * 2246822519U + (unsigned) svow.seed * 3266489917U;

    h = (h ^ (h >> 13)) * 1274126177U;
    h ^= h >> 16;
    return h;
}

/* smooth value noise in 0..1023 over a lattice of the given scale */
staticfn int
ow_vnoise(int x, int y, int scale, unsigned salt)
{
    int lx = (x >= 0) ? x / scale : -((-x + scale - 1) / scale),
        ly = (y >= 0) ? y / scale : -((-y + scale - 1) / scale);
    int fx = x - lx * scale, fy = y - ly * scale;
    long v00 = ow_hash(lx, ly, salt) & 1023,
         v10 = ow_hash(lx + 1, ly, salt) & 1023,
         v01 = ow_hash(lx, ly + 1, salt) & 1023,
         v11 = ow_hash(lx + 1, ly + 1, salt) & 1023;
    /* smoothstep weights, fixed point with 'scale' as 1.0 */
    long sx = (long) fx * fx * (3 * scale - 2 * fx) / ((long) scale * scale),
         sy = (long) fy * fy * (3 * scale - 2 * fy) / ((long) scale * scale);
    long a = v00 + (v10 - v00) * sx / scale,
         b = v01 + (v11 - v01) * sx / scale;

    return (int) (a + (b - a) * sy / scale);
}

/* fractal (three octave) noise, 0..1023 */
staticfn int
ow_fbm(int x, int y, int scale, unsigned salt)
{
    int v = ow_vnoise(x, y, scale, salt) * 4
            + ow_vnoise(x, y, max(scale / 2, 2), salt + 17) * 2
            + ow_vnoise(x, y, max(scale / 4, 2), salt + 31);

    return v / 7;
}

/* elevation: mountains where high, lakes where low */
staticfn int
ow_elev(int x, int y)
{
    return ow_fbm(x, y, 48, 101);
}

/* moisture: forests and swamps where high */
staticfn int
ow_moist(int x, int y)
{
    return ow_fbm(x, y, 40, 202);
}

/* temperature: tundra where low, desert where high */
staticfn int
ow_temp(int x, int y)
{
    return ow_fbm(x, y, 96, 303);
}

/* The upper world's great roads radiate from the plaza toward the Gehennom
   barrier; they are always passable, cutting through forest and hill,
   bridging lakes, and tunneling through mountains. */
#define OW_NROADS 8
staticfn boolean
ow_on_road(int x, int y)
{
    int d = ow_dist(x, y), b, i, wob, rd;

    if (d < 7 || d > ow_barrier_r0() - 2)
        return FALSE;
    b = ow_bearing(x, y);
    for (i = 0; i < OW_NROADS; i++) {
        int center = i * (360 / OW_NROADS) + 22, diff, off;

        /* roads meander a little */
        wob = (ow_vnoise(d, i * 1000, 24, 404) - 512) / 16; /* +/- 32 */
        rd = center + (wob * 16) / max(d / 8, 16);
        diff = b - rd;
        while (diff > 180)
            diff -= 360;
        while (diff < -180)
            diff += 360;
        /* convert angular difference to distance off the road */
        off = (int) ((long) d * (diff < 0 ? -diff : diff) * 314 / 18000);
        if (off <= 1)
            return TRUE;
    }
    return FALSE;
}

/* determine the kind of land at <x,y> (independent of generation order) */
int
ow_biome_at(int x, int y)
{
    int d = ow_dist(x, y), e, m, t;

    if (d < 8)
        return OWB_PLAZA;
    if (d >= ow_edge_r0())
        return OWB_EDGE;
    if (d >= ow_barrier_r0() + 5) {
        /* Gehennom */
        e = ow_fbm(x, y, 40, 505);
        m = ow_fbm(x, y, 56, 606);
        if (e > 640)
            return OWB_HELLCAVE;
        if (m > 620)
            return OWB_HELLMAZE;
        if (e < 360)
            return OWB_HELLLAVA;
        return OWB_HELLPLAIN;
    }
    if (d >= ow_barrier_r0())
        return OWB_BARRIER;
    if (d >= ow_barrier_r0() - OW_RING_WIDTH)
        return OWB_BARRENS;
    e = ow_elev(x, y);
    m = ow_moist(x, y);
    t = ow_temp(x, y);
    if (d < OW_RING_WIDTH + 8) {
        /* the first ring is gentle: no mountains, lakes or swamps */
        if (m > 600)
            return OWB_FOREST;
        return OWB_MEADOW;
    }
    if (e > 690)
        return OWB_MOUNTAIN;
    if (e > 630)
        return OWB_HILLS;
    if (e < 230)
        return (t < 330) ? OWB_TUNDRA : OWB_LAKE;
    if (t < 300)
        return OWB_TUNDRA;
    if (t > 740)
        return OWB_DESERT;
    if (m > 700 && e < 470)
        return OWB_SWAMP;
    if (m > 640)
        return OWB_DEEPFOREST;
    if (m > 550)
        return OWB_FOREST;
    if ((ow_hash(x / 40, y / 40, 707) % 23) == 0 && m < 450)
        return OWB_RUINS;
    return OWB_MEADOW;
}

/* short name of biome for messages */
const char *
ow_biome_name(int b)
{
    static const char *const names[NUM_OW_BIOMES] = {
        "meadows", "woods", "deep forest", "mountains", "hills", "lakelands",
        "swamps", "frozen tundra", "desert", "ancient ruins",
        "blasted borderlands", "mountains of the Barrier",
        "scorched plains of Gehennom", "lava fields of Gehennom",
        "obsidian labyrinth of Gehennom", "caverns of Gehennom",
        "edge of the world", "sacred plaza",
    };

    return (b >= 0 && b < NUM_OW_BIOMES) ? names[b] : "wilderness";
}

/* set the terrain of one map location from its biome */
staticfn void
ow_set_terrain(int x, int y)
{
    struct rm *lev = &levl[x][y];
    int b = ow_biome_at(x, y), h = (int) (ow_hash(x, y, 808) % 1000), e, m;
    boolean road = FALSE;

    lev->typ = ROOM;
    lev->flavor = OWF_GRASS;
    lev->lit = 1;
    lev->flags = 0;
    lev->horizontal = 0;
    lev->roomno = NO_ROOM;
    lev->edge = 0;
    lev->candig = 0;

    if (b != OWB_PLAZA && b != OWB_EDGE && b != OWB_BARRIER
        && b < OWB_HELLPLAIN && ow_on_road(x, y))
        road = TRUE;

    switch (b) {
    case OWB_PLAZA:
        lev->flavor = OWF_MARBLE;
        break;
    case OWB_MEADOW:
        if (road)
            break;
        if (h < 25)
            lev->typ = TREE, lev->flavor = OWF_FOREST;
        break;
    case OWB_FOREST:
        lev->flavor = OWF_FOREST;
        if (!road && h < 270)
            lev->typ = TREE;
        break;
    case OWB_DEEPFOREST:
        lev->flavor = OWF_FOREST;
        lev->lit = (h % 5) != 0; /* dim under the canopy */
        if (!road && h < 440)
            lev->typ = TREE;
        break;
    case OWB_HILLS:
        lev->flavor = OWF_DIRT;
        if (!road) {
            e = ow_elev(x, y);
            /* rocky knolls near the mountains; elsewhere scattered trees
               (boulders are strewn about by ow_populate()) */
            if (e > 668 && ow_fbm(x, y, 6, 1507) > 520)
                lev->typ = STONE, lev->flavor = OWF_MOUNTAIN;
            else if (h < 50)
                lev->typ = TREE;
        }
        break;
    case OWB_MOUNTAIN:
        lev->flavor = OWF_MOUNTAIN;
        if (!road) {
            lev->typ = STONE;
            lev->lit = 0;
            /* caves wind through the larger mountain ranges */
            m = ow_fbm(x, y, 12, 909);
            if (ow_elev(x, y) > 740 && m > 470 && m < 540) {
                lev->typ = ROOM;
                lev->flavor = OWF_DIRT;
            }
        } else {
            lev->flavor = OWF_DIRT; /* mountain pass */
        }
        break;
    case OWB_LAKE:
        e = ow_elev(x, y);
        if (road) {
            lev->flavor = OWF_DIRT; /* causeway */
        } else if (e < 200) {
            lev->typ = POOL, lev->flavor = OWF_NONE;
        } else {
            lev->flavor = OWF_SAND; /* beach */
        }
        break;
    case OWB_SWAMP:
        lev->flavor = OWF_MUD;
        if (!road && ((x + y) % 2) == 0 && h < 800)
            lev->typ = POOL;
        else if (!road && h < 40)
            lev->typ = TREE;
        break;
    case OWB_TUNDRA:
        lev->flavor = OWF_SNOW;
        e = ow_elev(x, y);
        if (!road && e < 230)
            lev->typ = ICE; /* frozen lake */
        else if (!road && h < 12)
            lev->typ = TREE;
        break;
    case OWB_DESERT:
        lev->flavor = OWF_SAND;
        if (!road && h < 6)
            lev->typ = TREE; /* cactus */
        break;
    case OWB_RUINS:
        lev->flavor = OWF_DIRT;
        if (!road && h < 30)
            lev->typ = TREE;
        break;
    case OWB_BARRENS:
        lev->flavor = OWF_ASH;
        if (!road && h < 20)
            lev->typ = TREE; /* dead trees */
        break;
    case OWB_BARRIER:
        lev->typ = STONE;
        lev->flavor = OWF_BARRIER;
        lev->lit = 0;
        lev->wall_info |= (W_NONDIGGABLE | W_NONPASSWALL);
        break;
    case OWB_HELLPLAIN:
        lev->flavor = OWF_ASH;
        lev->lit = 0;
        if (h < 30)
            lev->typ = LAVAPOOL, lev->lit = 1;
        else if (ow_fbm(x, y, 7, 1609) > 700)
            lev->typ = STONE, lev->flavor = OWF_HELLROCK; /* crags */
        break;
    case OWB_HELLLAVA:
        lev->flavor = OWF_ASH;
        lev->lit = 0;
        m = ow_fbm(x, y, 10, 1001);
        if (m < 430 || (m > 560 && h < 600))
            lev->typ = LAVAPOOL, lev->lit = 1;
        break;
    case OWB_HELLMAZE: {
        /* a binary-tree maze on a 2x2 lattice: every cell carves either
           north or east, which is locally computable and connected */
        int cx = x >> 1, cy = y >> 1;
        boolean xodd = (x & 1) != 0, yodd = (y & 1) != 0;

        lev->flavor = OWF_ASH;
        lev->lit = 0;
        if (xodd && yodd) {
            ; /* cell center: floor */
        } else if (!xodd && !yodd) {
            lev->typ = STONE, lev->flavor = OWF_HELLROCK; /* post */
        } else if (!xodd) {
            /* wall between cell (cx-1,cy) and (cx,cy): open if the west
               cell carved east */
            if (ow_hash(cx - 1, cy, 1102) & 1)
                ;
            else
                lev->typ = STONE, lev->flavor = OWF_HELLROCK;
        } else {
            /* wall between cell (cx,cy-1) and (cx,cy): open if the south
               one (cx,cy) carved north */
            if (!(ow_hash(cx, cy, 1102) & 1))
                ;
            else
                lev->typ = STONE, lev->flavor = OWF_HELLROCK;
        }
        break;
    }
    case OWB_HELLCAVE:
        lev->flavor = OWF_HELLROCK;
        lev->lit = 0;
        lev->typ = STONE;
        m = ow_fbm(x, y, 14, 1203);
        if (m > 440 && m < 590) {
            lev->typ = ROOM;
            lev->flavor = OWF_ASH;
            if (h < 25)
                lev->typ = LAVAPOOL, lev->lit = 1;
        }
        break;
    case OWB_EDGE:
    default:
        if (ow_dist(x, y) < ow_edge_r0() + 6) {
            lev->typ = LAVAPOOL; /* the burning sea at the end of the world */
            lev->lit = 1;
            lev->flavor = OWF_NONE;
        } else {
            lev->typ = STONE;
            lev->flavor = OWF_HELLROCK;
            lev->lit = 0;
            lev->wall_info |= (W_NONDIGGABLE | W_NONPASSWALL);
        }
        break;
    }
    /* the map's own border is never passable */
    if (x < OW_EDGE || y < OW_EDGE || x >= OW_SIZE - OW_EDGE
        || y >= OW_SIZE - OW_EDGE) {
        lev->typ = STONE;
        lev->flavor = OWF_HELLROCK;
        lev->lit = 0;
        lev->wall_info |= (W_NONDIGGABLE | W_NONPASSWALL);
    }
}

/* ------------------------------------------------------------------ */
/* game setup: rings and depths                                        */
/* ------------------------------------------------------------------ */

staticfn int
ow_dnum_named(const char *name)
{
    int i;

    for (i = 0; i < svn.n_dgns; i++)
        if (!strcmp(svd.dungeons[i].dname, name))
            return i;
    return -1;
}

/* number of portals around ring 'ring': about one per 64 cells of
   circumference, so outer rings have proportionally more portals */
staticfn int
ow_circumference_portals(int ring)
{
    int r = (ring - 1) * OW_RING_WIDTH + OW_RING_WIDTH / 2;
    int n = (int) ((2L * 314L * r) / (100L * 64L));

    if (n < 3)
        n = 3;
    if (n > 48)
        n = 48;
    return n;
}

staticfn void
ow_add_ring(xint16 dnum, int ring, int nportals)
{
    struct ow_ringinfo *ri;

    if (dnum < 0 || svow.nrings >= OW_MAXRINGS)
        return;
    ri = &svow.rings[svow.nrings++];
    ri->dnum = dnum;
    ri->ring = (xint16) ring;
    ri->nportals = (xint16) (nportals ? nportals
                                      : ow_circumference_portals(ring));
    ri->phase = (xint16) rn2(360);
}

/* set a branch dungeon's depth so that its entry level has 'entrydepth' */
staticfn void ow_set_dgn_depth(int, int);

staticfn void
ow_set_dgn_depth(int dnum, int entrydepth)
{
    if (dnum < 0)
        return;
    svd.dungeons[dnum].depth_start
        = entrydepth - (svd.dungeons[dnum].entry_lev - 1);
}

/*
 * Called for a new game, after init_dungeons().  Decide where each
 * branch's ring of portals is (with the same sort of randomization that
 * dungeon.lua uses to position branches in the classic game) and fix up
 * the depths of the branch dungeons to match.
 */
void
ow_init(void)
{
    int mines, oracle, soko, bigrm, quest, medusa, valley, gehlen, bottom,
        asmo, juib, baal, orcus, wiz, vlad, fake1, fake2, i;
    int dn_mines = ow_dnum_named("The Gnomish Mines"),
        dn_oracle = ow_dnum_named("The Oracle"),
        dn_soko = ow_dnum_named("Sokoban"),
        dn_bigrm = ow_dnum_named("The Big Room"),
        dn_quest = ow_dnum_named("The Quest"),
        dn_knox = ow_dnum_named("Fort Ludios"),
        dn_medusa = ow_dnum_named("Medusa's Island"),
        dn_geh = ow_dnum_named("Gehennom"),
        dn_asmo = ow_dnum_named("Asmodeus' Lair"),
        dn_juib = ow_dnum_named("Juiblex's Swamp"),
        dn_baal = ow_dnum_named("Baalzebub's Lair"),
        dn_orcus = ow_dnum_named("Orcus Town"),
        dn_wiz = ow_dnum_named("The Wizard's Tower"),
        dn_fake1 = ow_dnum_named("The Black Tower"),
        dn_fake2 = ow_dnum_named("The Hollow Tower"),
        dn_vlad = ow_dnum_named("Vlad's Tower"),
        dn_gates = ow_dnum_named("The Gates of Moloch");

    (void) memset((genericptr_t) &svow, 0, sizeof svow);
    svow.seed = ((unsigned long) rn2(0x7fff) << 15) ^ (unsigned long) rn2(0x7fff)
                ^ ((unsigned long) rn2(0x7fff) << 7);
    if (!svow.seed)
        svow.seed = 12345;

    /* Dungeons of Doom equivalents (cf. dungeon.lua in the classic game) */
    mines = 2 + rn2(3);            /* 2..4 */
    oracle = 5 + rn2(5);           /* 5..9 */
    soko = oracle + 1;             /* entrance just past the Oracle */
    bigrm = 10 + rn2(3);           /* 10..12 */
    quest = oracle + 6 + rn2(2);   /* 11..16 */
    medusa = 21 + rn2(4);          /* 21..24; the Castle is one deeper */
    valley = medusa + 2;           /* Valley of the Dead */
    /* Gehennom proper */
    gehlen = 20 + rn2(5);          /* Valley through Sanctum */
    bottom = valley + gehlen - 1;  /* Moloch's Sanctum */
    asmo = valley + 1 + rn2(6);
    juib = valley + 3 + rn2(4);
    baal = valley + 5 + rn2(4);
    vlad = valley + 8 + rn2(5);
    orcus = valley + 9 + rn2(6);
    wiz = valley + 10 + rn2(6);
    fake1 = bottom - 6 + rn2(4);
    fake2 = bottom - 6 + rn2(4);
    if (fake2 == fake1)
        fake2 = (fake1 > bottom - 6) ? fake1 - 1 : fake1 + 1;

    svow.barrier_ring = (xint16) valley;
    svow.hell_ring = (xint16) (valley + 1);
    svow.max_ring = (xint16) (bottom + 2);
    /* the map must be big enough for the whole world */
    if (svow.max_ring * OW_RING_WIDTH > OW_CX - OW_EDGE - 8)
        svow.max_ring = (xint16) ((OW_CX - OW_EDGE - 8) / OW_RING_WIDTH);

    ow_add_ring(dn_mines, mines, 0);
    ow_add_ring(dn_oracle, oracle, 0);
    ow_add_ring(dn_soko, soko, 0);
    ow_add_ring(dn_bigrm, bigrm, 0);
    ow_add_ring(dn_quest, quest, 0);
    ow_add_ring(dn_medusa, medusa, 0);
    /* the hell side of the barrier has gates back into the Valley */
    ow_add_ring(dn_geh, valley + 1, 0);
    ow_add_ring(dn_asmo, asmo, 0);
    ow_add_ring(dn_juib, juib, 0);
    ow_add_ring(dn_baal, baal, 0);
    ow_add_ring(dn_vlad, vlad, 0);
    ow_add_ring(dn_orcus, orcus, 0);
    ow_add_ring(dn_wiz, wiz, 0);
    ow_add_ring(dn_fake1, fake1, 0);
    ow_add_ring(dn_fake2, fake2, 0);
    ow_add_ring(dn_gates, bottom - 1, 0);

    /* depths of the branch dungeons; stairway branches go one level
       beyond the portal ring, like the classic branch stairs, while the
       single special levels are at the depth of their ring */
    ow_set_dgn_depth(dn_mines, mines + 1);
    ow_set_dgn_depth(dn_oracle, oracle);
    ow_set_dgn_depth(dn_soko, soko - 1);  /* entry is Sokoban's bottom */
    ow_set_dgn_depth(dn_bigrm, bigrm);
    ow_set_dgn_depth(dn_quest, quest);
    ow_set_dgn_depth(dn_knox, medusa - 3); /* adjusted when its portal is made */
    ow_set_dgn_depth(dn_medusa, medusa);
    ow_set_dgn_depth(dn_geh, valley);
    ow_set_dgn_depth(dn_asmo, asmo);
    ow_set_dgn_depth(dn_juib, juib);
    ow_set_dgn_depth(dn_baal, baal);
    ow_set_dgn_depth(dn_orcus, orcus);
    ow_set_dgn_depth(dn_wiz, wiz);
    ow_set_dgn_depth(dn_fake1, fake1);
    ow_set_dgn_depth(dn_fake2, fake2);
    ow_set_dgn_depth(dn_vlad, vlad - 1);  /* entry is the tower's bottom */
    ow_set_dgn_depth(dn_gates, bottom - 1);

    /* spread out rings that share a depth so their portals interleave */
    for (i = 1; i < svow.nrings; i++) {
        int j;

        for (j = 0; j < i; j++)
            if (svow.rings[j].ring == svow.rings[i].ring)
                svow.rings[i].phase = (xint16) ((svow.rings[j].phase
                                                 + 360 / svow.rings[j].nportals
                                                       / 2 + 7 * i) % 360);
    }

    svow.deepest_ring = 1;
    svow.last_ring_seen = 1;
    svow.last_zone_msg = -1;
    svow.inited = TRUE;
}

/* location of portal #k of ring 'ri'; the portal site is kept wholly
   inside one generation chunk */
staticfn void
ow_portal_pos(const struct ow_ringinfo *ri, int k, int *px, int *py)
{
    int r = (ri->ring - 1) * OW_RING_WIDTH + OW_RING_WIDTH / 2,
        ang = (ri->phase + (k * 360) / ri->nportals) % 360, x, y, cx0, cy0;

    ow_polar(r, ang, &x, &y);
    cx0 = (x / OW_CHUNK) * OW_CHUNK;
    cy0 = (y / OW_CHUNK) * OW_CHUNK;
    if (x < cx0 + 4)
        x = cx0 + 4;
    if (x > cx0 + OW_CHUNK - 5)
        x = cx0 + OW_CHUNK - 5;
    if (y < cy0 + 4)
        y = cy0 + 4;
    if (y > cy0 + OW_CHUNK - 5)
        y = cy0 + OW_CHUNK - 5;
    *px = x, *py = y;
}

/* for #overview and similar: the dungeon reached by the portal at <x,y> */
const char *
ow_portal_dest_name(xint16 dnum)
{
    if (dnum < 0 || dnum >= svn.n_dgns)
        return "somewhere";
    if (dnum == ow_dnum_named("Gehennom"))
        return "the Valley of the Dead";
    return svd.dungeons[dnum].dname;
}

/* ------------------------------------------------------------------ */
/* chunk generation                                                    */
/* ------------------------------------------------------------------ */

/* is the chunk containing map location <x,y> generated? */
boolean
ow_generated(int x, int y)
{
    int cx = x / OW_CHUNK, cy = y / OW_CHUNK;

    if (x < 0 || y < 0 || cx >= OW_NCHUNKS || cy >= OW_NCHUNKS)
        return FALSE;
    return (boolean) (svow.genmap[cx][cy] != 0);
}

/* generate every chunk within 'radius' of <x,y> */
staticfn void
ow_generate_area(int x, int y, int radius)
{
    int cx0 = max(0, (x - radius) / OW_CHUNK),
        cx1 = min(OW_NCHUNKS - 1, (x + radius) / OW_CHUNK),
        cy0 = max(0, (y - radius) / OW_CHUNK),
        cy1 = min(OW_NCHUNKS - 1, (y + radius) / OW_CHUNK),
        cx, cy, miny = OW_SIZE, maxy = -1, nmade = 0;
    boolean was_in_mklev = gi.in_mklev;
    clock_t t0 = clock();

    for (cx = cx0; cx <= cx1; cx++)
        for (cy = cy0; cy <= cy1; cy++) {
            if (svow.genmap[cx][cy])
                continue;
            gi.in_mklev = TRUE;
            ow_gen_chunk(cx, cy);
            gi.in_mklev = was_in_mklev;
            miny = min(miny, cy * OW_CHUNK - 2);
            maxy = max(maxy, cy * OW_CHUNK + OW_CHUNK + 1);
            nmade++;
        }
    if (maxy >= 0 && iflags.vision_inited && !was_in_mklev) {
        /* terrain changed: rebuild line of sight blockage for those rows */
        vision_reset_rows(max(0, miny), min(ROWNO - 1, maxy));
        gv.vision_full_recalc = 1;
    }
    if (nmade && getenv("OWHACK_TIMING"))
        fprintf(stderr, "ow_generate_area: %d chunks in %.3fs\n", nmade,
                (double) (clock() - t0) / CLOCKS_PER_SEC);
}

/* make sure the neighborhood of <x,y> exists */
void
ow_ensure_generated(int x, int y)
{
    if (!In_overworld || !svow.inited)
        return;
    ow_generate_area(x, y, OW_GEN_RADIUS);
}

/* called once per hero move: keep the world generated around the hero,
   track depth reached, and give ring and zone messages */
void
ow_maintain(void)
{
    static int lastcx = -1, lastcy = -1;
    int cx, cy, ring, biome;

    if (!In_overworld || !svow.inited || !u.ux) {
        ow_test_hook();
        return;
    }
    cx = u.ux / OW_CHUNK, cy = u.uy / OW_CHUNK;
    if (cx != lastcx || cy != lastcy || !svow.genmap[cx][cy]) {
        ow_generate_area(u.ux, u.uy, OW_GEN_RADIUS);
        lastcx = cx, lastcy = cy;
    }
    if (wizard && getenv("OWHACK_TELEFILE"))
        ow_test_hook();
    if (getenv("OWHACK_MAPDUMP"))
        ow_debug_dump(u.ux, u.uy, 110, 45);
    {
        static coordxy lastux = 0, lastuy = 0;

        if (u.ux != lastux || u.uy != lastuy) {
            lastux = u.ux, lastuy = u.uy;
            if (flags.compass)
                disp.botl = TRUE; /* compass bearing and distance */
        }
    }
    ring = ow_ring_at(u.ux, u.uy);
    if (ring > svow.deepest_ring) {
        svow.deepest_ring = (xint16) ring;
        if (ring > 1)
            livelog_printf(LL_DEBUG, "reached depth %d of the Overworld",
                           ring);
        /* reaching new depths is like arriving on a new dungeon level */
        if (Role_if(PM_TOURIST)) {
            more_experienced(level_difficulty(), 0);
            newexplevel();
        }
    }
    if (ring < svow.last_ring_seen && u.uhave.amulet && u_in_gehennom()
        && ring + 3 < ow_branch_ring(sanctum_level.dnum) + 1
        && ow_mysterious_force(ring))
        return;
    if (ring != svow.last_ring_seen) {
        if (ring > svow.last_ring_seen && flags.verbose)
            You_feel("that the land grows more dangerous.");
        else if (ring < svow.last_ring_seen && flags.verbose && !rn2(3))
            You_feel("a little safer here.");
        svow.last_ring_seen = (xint16) ring;
        disp.botl = TRUE;
        /* quest leader's call when first reaching the quest's ring */
        if (ring == ow_branch_ring(quest_dnum) && !svow.qcall_done
            && !(u.uevent.qcompleted || u.uevent.qexpelled
                 || svq.quest_status.leader_is_dead)) {
            svow.qcall_done = TRUE;
            if (!u.uevent.qcalled) {
                u.uevent.qcalled = 1;
                com_pager("quest_portal");
            } else {
                com_pager(Role_if(PM_ROGUE) ? "quest_portal_demand"
                                            : "quest_portal_again");
            }
        }
    }
    biome = ow_biome_at(u.ux, u.uy);
    if (biome != svow.last_zone_msg) {
        int prev = svow.last_zone_msg;

        svow.last_zone_msg = (xint16) biome;
        if (prev >= 0 && flags.verbose && !Blind) {
            switch (biome) {
            case OWB_BARRENS:
                if (prev != OWB_BARRIER)
                    pline("The land here is scorched and lifeless.");
                break;
            case OWB_HELLPLAIN:
            case OWB_HELLLAVA:
            case OWB_HELLMAZE:
            case OWB_HELLCAVE:
                if (prev < OWB_HELLPLAIN || prev > OWB_HELLCAVE) {
                    You("are in Gehennom.");
                    hellish_smoke_mesg();
                }
                break;
            case OWB_DESERT:
            case OWB_TUNDRA:
            case OWB_SWAMP:
            case OWB_DEEPFOREST:
            case OWB_MOUNTAIN:
            case OWB_RUINS:
                if (!rn2(2))
                    You("enter the %s.", ow_biome_name(biome));
                break;
            default:
                break;
            }
        }
    }
    if (ow_in_gehennom(u.ux, u.uy) && !u.uevent.gehennom_entered) {
        u.uevent.gehennom_entered = 1;
        record_achievement(ACH_HELL);
    }
}

/*
 * Climbing out of Gehennom with the Amulet: each time the hero crosses
 * inward into a shallower ring there is a chance of the "mysterious force"
 * sending them back outward, as with climbing stairs in the classic game.
 * Returns TRUE if the hero was moved.
 */
staticfn boolean
ow_mysterious_force(int ring)
{
    int odds, diff, x, y, want;
    coord cc;

    if (rn2(4 + svc.context.mysteryforce))
        return FALSE;
    odds = 3 + (int) u.ualign.type; /* 2..4 */
    diff = (odds <= 1) ? 0 : rn2(odds);
    want = ring + diff;
    if (want > svow.max_ring - 1)
        want = svow.max_ring - 1;
    diff = want - ring;
    pline("A mysterious force momentarily surrounds you...");
    svc.context.mysteryforce += rn2(diff + 2); /* L:0-4,N:0-3,C:0-2 */
    /* back out along the hero's bearing, into the middle of the ring */
    ow_polar((want - 1) * OW_RING_WIDTH + OW_RING_WIDTH / 2,
             ow_bearing(u.ux, u.uy), &x, &y);
    ow_ensure_generated(x, y);
    ow_want_ring = want;
    if (ow_rndspot_near(x, y, 14, 60, &cc, TRUE)) {
        ow_want_ring = 0;
        teleds(cc.x, cc.y, TELEDS_TELEPORT);
    } else {
        ow_want_ring = 0;
        (void) safe_teleds(TELEDS_NO_FLAGS);
    }
    svow.last_ring_seen = (xint16) ow_ring_at(u.ux, u.uy);
    disp.botl = TRUE;
    ow_maintain();
    return TRUE;
}

/* the sacred plaza at the center of the world, with the three high
   altars; the middle one belongs to the hero's own god */
staticfn void
ow_paint_plaza(void)
{
    int x, y, i, d;
    aligntyp own = u.ualignbase[A_ORIGINAL], others[2], a;
    struct rm *lev;

    for (i = 0, a = A_CHAOTIC; a <= A_LAWFUL; a++)
        if (a != own)
            others[i++] = a;

    for (x = OW_CX - 9; x <= OW_CX + 9; x++)
        for (y = OW_CY - 9; y <= OW_CY + 9; y++) {
            d = ow_dist(x, y);
            if (d > 8)
                continue;
            lev = &levl[x][y];
            lev->typ = ROOM;
            lev->flavor = OWF_MARBLE;
            lev->lit = 1;
            lev->flags = 0;
            /* the plaza is holy ground: it can't be dug into */
            lev->wall_info |= W_NONDIGGABLE;
        }
    /* four fountains at the corners of the plaza */
    for (i = 0; i < 4; i++) {
        x = OW_CX + ((i & 1) ? 5 : -5);
        y = OW_CY + ((i & 2) ? 3 : -3);
        levl[x][y].typ = FOUNTAIN;
        levl[x][y].flags = 0;
        svl.level.flags.nfountains++;
    }
    /* the three high altars */
    for (i = 0; i < 3; i++) {
        x = OW_CX + (i - 1) * 4;
        y = OW_CY;
        a = (i == 1) ? own : others[i ? 1 : 0];
        lev = &levl[x][y];
        lev->typ = ALTAR;
        /* high altars: AM_SANCTUM is what makes an altar "high" */
        lev->altarmask = Align2amask(a) | AM_SHRINE | AM_SANCTUM;
        svow.altar_x[i] = x, svow.altar_y[i] = y;
        svow.altar_align[i] = a;
    }
}

/* is <x,y> one of the three high altars of the plaza? */
boolean
ow_is_high_altar(coordxy x, coordxy y)
{
    int i;

    if (!In_overworld || !svow.inited)
        return FALSE;
    for (i = 0; i < 3; i++)
        if (svow.altar_x[i] == x && svow.altar_y[i] == y)
            return (boolean) (levl[x][y].typ == ALTAR);
    return FALSE;
}

/* location of the high altar of the hero's original god */
void
ow_home_altar(coordxy *x, coordxy *y)
{
    *x = svow.altar_x[1] ? svow.altar_x[1] : OW_CX;
    *y = svow.altar_y[1] ? svow.altar_y[1] : OW_CY;
}

/* build the little plazas around any portals within this chunk */
staticfn void
ow_make_portal_sites(int x0, int y0, int x1, int y1)
{
    int r, k, px, py, x, y;
    struct trap *ttmp;
    char buf[BUFSZ];

    for (r = 0; r < svow.nrings; r++) {
        struct ow_ringinfo *ri = &svow.rings[r];

        if (ri->dnum < 0 || ri->dnum >= svn.n_dgns)
            continue;
        for (k = 0; k < ri->nportals; k++) {
            ow_portal_pos(ri, k, &px, &py);
            if (px < x0 || px > x1 || py < y0 || py > y1)
                continue;
            /* clear a small circle of paving stones around the portal,
               ringed by standing stones (boulders) with gaps */
            for (x = px - 3; x <= px + 3; x++)
                for (y = py - 3; y <= py + 3; y++) {
                    long dd = (long) (x - px) * (x - px)
                              + (long) (y - py) * (y - py);
                    struct rm *lev = &levl[x][y];

                    if (dd > 10)
                        continue;
                    if (lev->typ == STONE && (lev->wall_info & W_NONDIGGABLE))
                        continue; /* never breach the barrier */
                    lev->typ = ROOM;
                    lev->flavor = ow_in_gehennom(x, y) ? OWF_ASH : OWF_PAVED;
                    lev->lit = 1;
                    lev->flags = 0;
                    if (dd >= 8 && ((x + y) & 1) == 0 && x != px && y != py)
                        (void) mksobj_at(BOULDER, x, y, TRUE, FALSE);
                }
            if ((ttmp = t_at(px, py)) != 0)
                deltrap(ttmp);
            mkportal(px, py, ri->dnum, svd.dungeons[ri->dnum].entry_lev);
            if ((ttmp = t_at(px, py)) != 0) {
                ttmp->tseen = 1; /* portal sites are landmarks */
                ttmp->madeby_u = 0;
            }
            Sprintf(buf, "%s", ow_portal_dest_name(ri->dnum));
            (void) strsubst(buf, "The ", "");
            if (ri->dnum == quest_dnum && gu.urole.homebase)
                Sprintf(buf, "%s", gu.urole.homebase);
            make_engr_at(px, py + 1, buf, NULL, 0L, ENGRAVE);
        }
    }
}

/* generate one chunk of the overworld */
staticfn void
ow_gen_chunk(int cx, int cy)
{
    int x0 = cx * OW_CHUNK, y0 = cy * OW_CHUNK,
        x1 = min(x0 + OW_CHUNK - 1, OW_SIZE - 1),
        y1 = min(y0 + OW_CHUNK - 1, OW_SIZE - 1), x, y, ring;
    unsigned h = ow_hash(cx, cy, 1301);

    clock_t c0 = clock(), c1, c2, c3, c4;
    static double tt[5];
    static int nchunks = 0;

    svow.genmap[cx][cy] = 1;
    for (x = max(x0, 1); x <= x1; x++)
        for (y = y0; y <= y1; y++)
            ow_set_terrain(x, y);
    c1 = clock();

    /* the level's depth for anything generated in this chunk */
    ring = ow_ring_at((x0 + x1) / 2, (y0 + y1) / 2);
    ow_gen_depth = ring;
    ow_gen_x = (x0 + x1) / 2, ow_gen_y = (y0 + y1) / 2;

    if (OW_CX >= x0 - 9 && OW_CX <= x1 + 9 && OW_CY >= y0 - 9
        && OW_CY <= y1 + 9)
        ow_paint_plaza();
    else
        ow_structures(cx, cy, x0, y0, x1, y1);
    c2 = clock();
    ow_make_portal_sites(x0, y0, x1, y1);

    ow_fix_walls(max(x0 - 1, 1), max(y0 - 1, 0), min(x1 + 1, OW_SIZE - 1),
                 min(y1 + 1, OW_SIZE - 1));
    if (ow_past_barrier(x0, y0) || ow_past_barrier(x1, y1)
        || ow_past_barrier(x0, y1) || ow_past_barrier(x1, y0)) {
        /* in Gehennom, molten lava lights up its surroundings */
        for (x = max(x0, 1); x <= x1; x++)
            for (y = y0; y <= y1; y++) {
                int dx, dy;

                if (levl[x][y].lit || !ow_in_gehennom(x, y))
                    continue;
                for (dx = -2; dx <= 2 && !levl[x][y].lit; dx++)
                    for (dy = -2; dy <= 2; dy++)
                        if (isok(x + dx, y + dy)
                            && levl[x + dx][y + dy].typ == LAVAPOOL) {
                            levl[x][y].lit = 1;
                            break;
                        }
            }
    }
    /* wall fixups may have turned rock under an engraving into wall */
    {
        struct engr *ep, *nep;

        for (ep = head_engr; ep; ep = nep) {
            nep = ep->nxt_engr;
            if (ep->engr_x >= x0 - 1 && ep->engr_x <= x1 + 1
                && ep->engr_y >= y0 - 1 && ep->engr_y <= y1 + 1
                && (!ACCESSIBLE(levl[ep->engr_x][ep->engr_y].typ)
                    || is_pool_or_lava(ep->engr_x, ep->engr_y)))
                del_engr(ep);
        }
    }
    c3 = clock();
    ow_populate(cx, cy, x0, y0, x1, y1);
    c4 = clock();
    nhUse(h);
    ow_gen_depth = 0;
    tt[0] += (double) (c1 - c0) / CLOCKS_PER_SEC;
    tt[1] += (double) (c2 - c1) / CLOCKS_PER_SEC;
    tt[2] += (double) (c3 - c2) / CLOCKS_PER_SEC;
    tt[3] += (double) (c4 - c3) / CLOCKS_PER_SEC;
    if (getenv("OWHACK_TIMING") && !(++nchunks % 40))
        fprintf(stderr, "chunks %d: terrain %.3f struct %.3f walls %.3f pop %.3f\n",
                nchunks, tt[0], tt[1], tt[2], tt[3]);
}

/* turn stone next to open ground into walls and join them up */
staticfn void
ow_fix_walls(int x0, int y0, int x1, int y1)
{
    int x, y;

    wallify_map(x0, y0, x1, y1);
    fix_wall_spines(max(x0 - 1, 1), max(y0 - 1, 0),
                    min(x1 + 1, COLNO - 1), min(y1 + 1, ROWNO - 1));
    for (x = max(x0 - 1, 1); x <= min(x1 + 1, COLNO - 1); x++)
        for (y = max(y0 - 1, 0); y <= min(y1 + 1, ROWNO - 1); y++)
            if (IS_WALL(levl[x][y].typ) || levl[x][y].typ == SDOOR)
                xy_set_wall_state(x, y);
}

/* ------------------------------------------------------------------ */
/* structures                                                          */
/* ------------------------------------------------------------------ */

/* a location that monsters/objects/features can be put on */
staticfn boolean
ow_open_spot(int x, int y)
{
    struct rm *lev;

    if (!isok(x, y) || x < OW_EDGE || y < OW_EDGE
        || x >= OW_SIZE - OW_EDGE || y >= OW_SIZE - OW_EDGE)
        return FALSE;
    lev = &levl[x][y];
    return (boolean) (lev->typ == ROOM && !t_at(x, y) && !MON_AT(x, y)
                      && !sobj_at(BOULDER, x, y) && !lev->roomno
                      && ow_dist(x, y) > 9);
}

/* is the rectangle suitable for building on?  'rock' allows solid stone
   (mountains); water, lava, the barrier, portal sites and existing
   structures are never allowed */
staticfn boolean
ow_rect_clear(int x0, int y0, int x1, int y1, boolean rock)
{
    int x, y;

    if (x0 < OW_EDGE + 2 || y0 < OW_EDGE + 2 || x1 >= OW_SIZE - OW_EDGE - 2
        || y1 >= OW_SIZE - OW_EDGE - 2)
        return FALSE;
    for (x = x0; x <= x1; x++)
        for (y = y0; y <= y1; y++) {
            struct rm *lev = &levl[x][y];

            if (IS_POOL(lev->typ) || IS_LAVA(lev->typ) || lev->roomno
                || lev->flavor == OWF_BARRIER || lev->flavor == OWF_PAVED
                || lev->flavor == OWF_MARBLE || IS_WALL(lev->typ)
                || IS_DOOR(lev->typ) || IS_FURNITURE(lev->typ)
                || t_at(x, y) || (lev->wall_info & W_NONDIGGABLE))
                return FALSE;
            if (!rock && lev->typ == STONE && lev->flavor == OWF_MOUNTAIN
                && ow_biome_at(x, y) == OWB_MOUNTAIN)
                return FALSE;
            if (ow_dist(x, y) < 14)
                return FALSE;
        }
    return TRUE;
}

/* find a random open spot in a rectangle */
staticfn boolean
ow_find_spot(int x0, int y0, int x1, int y1, coord *cc, boolean anyfloor)
{
    int tries, x, y;

    for (tries = 0; tries < 60; tries++) {
        x = rn1(x1 - x0 + 1, x0);
        y = rn1(y1 - y0 + 1, y0);
        if (anyfloor ? (isok(x, y) && levl[x][y].typ == ROOM
                        && !t_at(x, y) && !MON_AT(x, y))
                     : ow_open_spot(x, y)) {
            cc->x = x, cc->y = y;
            return TRUE;
        }
    }
    return FALSE;
}

/* make a rectangle of floor */
staticfn void ow_floor(int, int, int, int, int, boolean);

staticfn void
ow_floor(int x0, int y0, int x1, int y1, int flavor, boolean lit)
{
    int x, y;

    for (x = x0; x <= x1; x++)
        for (y = y0; y <= y1; y++) {
            struct rm *lev = &levl[x][y];
            struct obj *otmp;

            lev->typ = ROOM;
            lev->flags = 0;
            lev->flavor = flavor;
            lev->lit = lit ? 1 : 0;
            while ((otmp = sobj_at(BOULDER, x, y)) != 0) {
                obj_extract_self(otmp);
                obfree(otmp, (struct obj *) 0);
            }
        }
}

/* draw the walls of a building whose interior is <x0,y0>-<x1,y1> */
staticfn void ow_walls(int, int, int, int, int);

staticfn void
ow_walls(int x0, int y0, int x1, int y1, int flavor)
{
    int x, y;

    for (x = x0 - 1; x <= x1 + 1; x++) {
        levl[x][y0 - 1].typ = HWALL, levl[x][y0 - 1].horizontal = 1;
        levl[x][y1 + 1].typ = HWALL, levl[x][y1 + 1].horizontal = 1;
        levl[x][y0 - 1].flavor = levl[x][y1 + 1].flavor = flavor;
        levl[x][y0 - 1].flags = levl[x][y1 + 1].flags = 0;
    }
    for (y = y0; y <= y1; y++) {
        levl[x0 - 1][y].typ = VWALL, levl[x0 - 1][y].horizontal = 0;
        levl[x1 + 1][y].typ = VWALL, levl[x1 + 1][y].horizontal = 0;
        levl[x0 - 1][y].flavor = levl[x1 + 1][y].flavor = flavor;
        levl[x0 - 1][y].flags = levl[x1 + 1][y].flags = 0;
    }
    levl[x0 - 1][y0 - 1].typ = TLCORNER;
    levl[x1 + 1][y0 - 1].typ = TRCORNER;
    levl[x0 - 1][y1 + 1].typ = BLCORNER;
    levl[x1 + 1][y1 + 1].typ = BRCORNER;
}

/* put a door in a building's wall; side: 0 top, 1 bottom, 2 left, 3 right */
staticfn void ow_door(int, int, int, int, int, int, struct mkroom *, int);

staticfn void
ow_door(int x0, int y0, int x1, int y1, int side, int mask,
        struct mkroom *croom, int where)
{
    int x, y;

    switch (side) {
    case 0:
        x = where ? where : rn1(x1 - x0 + 1, x0), y = y0 - 1;
        break;
    case 1:
        x = where ? where : rn1(x1 - x0 + 1, x0), y = y1 + 1;
        break;
    case 2:
        x = x0 - 1, y = where ? where : rn1(y1 - y0 + 1, y0);
        break;
    default:
        x = x1 + 1, y = where ? where : rn1(y1 - y0 + 1, y0);
        break;
    }
    levl[x][y].typ = DOOR;
    levl[x][y].doormask = mask;
    if (croom)
        add_door(x, y, croom);
}

/* pick a random door state for an ordinary building */
staticfn int ow_rnd_doormask(void);

staticfn int
ow_rnd_doormask(void)
{
    int r = rn2(10);

    return (r < 2) ? D_NODOOR : (r < 5) ? D_ISOPEN : (r < 8) ? D_CLOSED
                                                             : D_LOCKED;
}

/* choose a shop type the way mkshop() does */
staticfn int
ow_pick_shoptype(int w, int h)
{
    int i, j;

    for (j = rnd(100), i = 0; (j -= shtypes[i].prob) > 0; i++)
        continue;
    if ((w * h > 20) && (shtypes[i].symb == WAND_CLASS
                         || shtypes[i].symb == SPBOOK_CLASS))
        i = 0;
    return i;
}

/* peaceful townsfolk */
staticfn struct monst *ow_townsperson(int, int);

staticfn struct monst *
ow_townsperson(int x, int y)
{
    static const short folk[] = { PM_GNOME, PM_GNOME_LEADER, PM_DWARF,
                                  PM_HOBBIT, PM_HOBBIT, PM_WOODLAND_ELF,
                                  PM_GNOME, PM_DWARF, PM_ELF };
    int pm = folk[rn2(SIZE(folk))];
    struct monst *mtmp;

    if (svm.mvitals[pm].mvflags & G_GONE)
        return (struct monst *) 0;
    mtmp = makemon(&mons[pm], x, y, MM_NOGRP | MM_NOMSG);
    if (mtmp) {
        mtmp->mpeaceful = 1;
        set_malign(mtmp);
        mtmp->msleeping = 0;
    }
    return mtmp;
}

/*
 * A building with a room structure.  'town' is the enclosing town room
 * (the building becomes a subroom of it) or Null.  Interior is
 * <x0,y0>-<x1,y1>; walls are drawn around it.  'side' is which wall gets
 * the door.  Returns the room.
 */
staticfn struct mkroom *
ow_building(int x0, int y0, int x1, int y1, int rtype, int side,
            boolean lit)
{
    struct mkroom *croom;

    if (svn.nroom >= MAXNROFROOMS - 1)
        return (struct mkroom *) 0;
    ow_floor(x0 - 1, y0 - 1, x1 + 1, y1 + 1, OWF_PAVED, lit);
    add_room(x0, y0, x1, y1, lit, rtype, FALSE);
    croom = &svr.rooms[svn.nroom - 1];
    croom->needfill = FILL_NORMAL;
    ow_door(x0, y0, x1, y1, side,
            (rtype >= SHOPBASE) ? (rn2(3) ? D_ISOPEN : D_CLOSED)
                                : ow_rnd_doormask(),
            croom, 0);
    return croom;
}

/* same, but as a subroom of a town */
staticfn struct mkroom *ow_subbuilding(struct mkroom *, int, int, int, int,
                                       int, int, boolean);

staticfn struct mkroom *
ow_subbuilding(struct mkroom *town, int x0, int y0, int x1, int y1,
               int rtype, int side, boolean lit)
{
    struct mkroom *croom;

    if (!town || gn.nsubroom >= MAXNROFROOMS - 1
        || town->nsubrooms >= MAX_SUBROOMS - 1)
        return ow_building(x0, y0, x1, y1, rtype, side, lit);
    ow_floor(x0 - 1, y0 - 1, x1 + 1, y1 + 1, OWF_PAVED, lit);
    add_subroom(town, x0, y0, x1, y1, lit, rtype, FALSE);
    croom = town->sbrooms[town->nsubrooms - 1];
    croom->needfill = FILL_NORMAL;
    ow_door(x0, y0, x1, y1, side,
            (rtype >= SHOPBASE) ? (rn2(3) ? D_ISOPEN : D_CLOSED)
                                : ow_rnd_doormask(),
            croom, 0);
    return croom;
}

/* finish off a room made during overworld generation */
staticfn void ow_finish_room(struct mkroom *);

staticfn void
ow_finish_room(struct mkroom *croom)
{
    int i;

    if (!croom)
        return;
    topologize(croom);
    croom->orig_rtype = croom->rtype;
    for (i = 0; i < croom->nsubrooms; i++)
        croom->sbrooms[i]->orig_rtype = croom->sbrooms[i]->rtype;
}

/* put a temple (altar plus priest) in room 'croom' */
staticfn void ow_make_temple(struct mkroom *, unsigned);

staticfn void
ow_make_temple(struct mkroom *croom, unsigned amask)
{
    int ax = (croom->lx + croom->hx) / 2, ay = (croom->ly + croom->hy) / 2;
    struct rm *lev = &levl[ax][ay];

    croom->rtype = TEMPLE;
    croom->needfill = FILL_NONE;
    /* topologize() must see TEMPLE before the priest is made */
    topologize(croom);
    lev->typ = ALTAR;
    lev->altarmask = amask & AM_MASK;
    priestini(&u.uz, croom, ax, ay, FALSE);
    lev->altarmask |= AM_SHRINE;
    svl.level.flags.has_temple = 1;
}

/* a house: walls, a door, and sometimes things inside */
staticfn void
ow_house(int x0, int y0, int x1, int y1, int side, boolean townhouse,
         int ring)
{
    coord cc;
    int n;

    ow_floor(x0 - 1, y0 - 1, x1 + 1, y1 + 1, OWF_PAVED, TRUE);
    ow_walls(x0, y0, x1, y1, OWF_NONE);
    ow_floor(x0, y0, x1, y1, OWF_NONE, TRUE);
    ow_door(x0, y0, x1, y1, side, ow_rnd_doormask(),
            (struct mkroom *) 0, 0);
    if (!rn2(8) && ow_find_spot(x0, y0, x1, y1, &cc, TRUE)) {
        levl[cc.x][cc.y].typ = SINK;
        levl[cc.x][cc.y].flags = 0;
        svl.level.flags.nsinks++;
    }
    for (n = rn2(3); n > 0; n--)
        if (ow_find_spot(x0, y0, x1, y1, &cc, TRUE))
            (void) mkobj_at(RANDOM_CLASS, cc.x, cc.y, TRUE);
    if (!rn2(4) && ow_find_spot(x0, y0, x1, y1, &cc, TRUE))
        (void) mksobj_at(rn2(3) ? LARGE_BOX : CHEST, cc.x, cc.y, TRUE,
                         FALSE);
    if (townhouse && ring < 15 && !rn2(3)
        && ow_find_spot(x0, y0, x1, y1, &cc, TRUE))
        (void) ow_townsperson(cc.x, cc.y);
    else if (!rn2(3) && ow_find_spot(x0, y0, x1, y1, &cc, TRUE))
        (void) makemon((struct permonst *) 0, cc.x, cc.y, NO_MM_FLAGS);
}

/*
 * A town: a lit, paved enclosure (a room without walls, so that the town
 * watch knows where the town is) holding shops, perhaps a temple, houses,
 * gardens, and a fountain square.  Small villages have fewer buildings.
 */
staticfn void
ow_town(int x0, int y0, int ring, int biome, int size, boolean ruined)
{
    /* building rows are 6 rows including walls, with a main street
       (holding the fountain square) between the two rows */
    int W = size ? 27 : 19, H = size ? 17 : 13, x1 = x0 + W - 1,
        y1 = y0 + H - 1, col, row, ncols = size ? 3 : 2, bx, by, kind,
        nshops = 0, ntemples = 0, i, townno;
    struct mkroom *town, *croom;
    coord cc;
    boolean haswatch = (!ruined && ring <= 14 && size);

    nhUse(biome);
    if (svn.nroom >= MAXNROFROOMS - 2)
        ruined = TRUE; /* no room records left: a ghost town */
    ow_floor(x0, y0, x1, y1, OWF_PAVED, TRUE);
    town = (struct mkroom *) 0;
    if (!ruined) {
        add_room(x0, y0, x1, y1, TRUE, OROOM, TRUE);
        town = &svr.rooms[svn.nroom - 1];
        town->needfill = FILL_NONE;
        svl.level.flags.has_town = 1;
    }

    /* fountain square in the middle */
    bx = (x0 + x1) / 2, by = (y0 + y1) / 2;
    levl[bx][by].typ = FOUNTAIN;
    levl[bx][by].flags = 0;
    svl.level.flags.nfountains++;

    /* two rows of building lots, above and below the main street */
    for (row = 0; row < 2; row++)
        for (col = 0; col < ncols; col++) {
            int lx = x0 + 2 + col * 8, ly = row ? y1 - 5 : y0 + 2,
                hx = lx + 4, hy = ly + 3, side = row ? 0 : 1;

            if (!size)
                ly = row ? y1 - 4 : y0 + 1, hy = ly + 3;
            kind = rn2(10);
            if (ruined) {
                /* ruined buildings: broken walls and debris */
                ow_house(lx, ly, hx, hy, side, FALSE, ring);
                for (i = 0; i < 4; i++) {
                    int wx = rn1(hx - lx + 3, lx - 1),
                        wy = rn2(2) ? ly - 1 : hy + 1;

                    if (IS_WALL(levl[wx][wy].typ))
                        levl[wx][wy].typ = ROOM;
                }
                continue;
            }
            if ((kind < 5 || (col == 0 && row == 0)) && nshops < 4
                && ring > 1 && ring < 25) {
                int st = ow_pick_shoptype(hx - lx + 1, hy - ly + 1);

                croom = ow_subbuilding(town, lx, ly, hx, hy,
                                       SHOPBASE + st, side, TRUE);
                if (croom)
                    nshops++;
            } else if (kind < 7 && !ntemples && ring > 1) {
                croom = ow_subbuilding(town, lx, ly, hx, hy, OROOM, side,
                                       TRUE);
                if (croom) {
                    ow_make_temple(croom, induced_align(50));
                    ntemples++;
                }
            } else if (kind < 9) {
                ow_house(lx, ly, hx, hy, side, TRUE, ring);
            } else {
                /* a garden */
                int tx, ty;

                ow_floor(lx - 1, ly - 1, hx + 1, hy + 1, OWF_GRASS, TRUE);
                for (tx = lx; tx <= hx; tx++)
                    for (ty = ly; ty <= hy; ty++)
                        if (!rn2(3))
                            levl[tx][ty].typ = TREE;
            }
        }
    /* record the town's rooms and stock its shops before anyone moves in */
    if (town) {
        ow_finish_room(town);
        for (i = 0; i < town->nsubrooms; i++)
            fill_special_room(town->sbrooms[i]);
    }
    /* town population, out in the streets (the town's own room number,
       not inside one of its buildings) */
    townno = town ? (int) (town - svr.rooms) + ROOMOFFSET : 0;
    if (haswatch) {
        if (!(svm.mvitals[PM_WATCH_CAPTAIN].mvflags & G_GONE)
            && ow_find_spot(x0, y0, x1, y1, &cc, TRUE)
            && levl[cc.x][cc.y].roomno == townno) {
            struct monst *m = makemon(&mons[PM_WATCH_CAPTAIN], cc.x, cc.y,
                                      NO_MM_FLAGS);

            if (m)
                m->mpeaceful = 1, set_malign(m);
        }
        for (i = rn1(3, 2); i > 0; i--)
            if (!(svm.mvitals[PM_WATCHMAN].mvflags & G_GONE)
                && ow_find_spot(x0, y0, x1, y1, &cc, TRUE)
                && levl[cc.x][cc.y].roomno == townno) {
                struct monst *m = makemon(&mons[PM_WATCHMAN], cc.x, cc.y,
                                          NO_MM_FLAGS);

                if (m)
                    m->mpeaceful = 1, set_malign(m);
            }
    }
    if (!ruined) {
        for (i = rn1(4, 2); i > 0; i--)
            if (ow_find_spot(x0, y0, x1, y1, &cc, TRUE)
                && levl[cc.x][cc.y].roomno == townno)
                (void) ow_townsperson(cc.x, cc.y);
    } else {
        /* ghost towns are haunted, or overrun */
        for (i = rn1(3, 2); i > 0; i--)
            if (ow_find_spot(x0, y0, x1, y1, &cc, TRUE)) {
                struct permonst *pm = rn2(2) ? mkclass(S_ZOMBIE, 0)
                                             : mkclass(S_ORC, 0);

                (void) makemon(pm, cc.x, cc.y, NO_MM_FLAGS);
            }
        if (ow_find_spot(x0, y0, x1, y1, &cc, TRUE))
            (void) makemon(&mons[PM_GHOST], cc.x, cc.y, NO_MM_FLAGS);
    }
}

/* a treasure vault sealed inside solid rock */
staticfn void
ow_vault(int x0, int y0, int x1, int y1, int ring)
{
    int tries, vx, vy, tx, ty;
    struct mkroom *croom;
    struct trap *ttmp;
    coord cc;

    nhUse(ring);
    if (svn.nroom >= MAXNROFROOMS - 1)
        return;
    for (tries = 0; tries < 40; tries++) {
        int x, y;
        boolean ok = TRUE;

        vx = rn1(x1 - x0 - 8, x0 + 4);
        vy = rn1(y1 - y0 - 8, y0 + 4);
        /* need solid rock all around, with a margin */
        for (x = vx - 2; x <= vx + 3 && ok; x++)
            for (y = vy - 2; y <= vy + 3 && ok; y++)
                if (levl[x][y].typ != STONE
                    || (levl[x][y].wall_info & W_NONDIGGABLE))
                    ok = FALSE;
        if (!ok)
            continue;
        add_room(vx, vy, vx + 1, vy + 1, TRUE, VAULT, FALSE);
        croom = &svr.rooms[svn.nroom - 1];
        croom->needfill = FILL_NORMAL;
        for (x = vx - 1; x <= vx + 2; x++)
            for (y = vy - 1; y <= vy + 2; y++)
                levl[x][y].flavor = OWF_MOUNTAIN;
        ow_finish_room(croom);
        fill_special_room(croom);
        svl.level.flags.has_vault = 1;
        gv.vault_x = vx, gv.vault_y = vy;
        /* (the overworld otherwise counts its branch as already made) */
        gm.made_branch = FALSE;
        mk_knox_portal(vx + 1, vy + 1);
        gm.made_branch = TRUE;
        /* sometimes a teleporter nearby leads into the vault */
        if (!rn2(3) && ow_find_spot(max(vx - 12, x0), max(vy - 12, y0),
                                    min(vx + 12, x1), min(vy + 12, y1),
                                    &cc, FALSE)) {
            tx = cc.x, ty = cc.y;
            if ((ttmp = maketrap(tx, ty, TELEP_TRAP)) != 0) {
                ttmp->once = 1;
                ttmp->teledest.x = vx, ttmp->teledest.y = vy;
                make_engr_at(tx, ty, "ad aerarium", NULL, 0L, DUST);
                wipe_engr_at(tx, ty, 5, FALSE);
            }
        }
        return;
    }
}

/* a walled compound holding one of the classic special rooms */
staticfn void
ow_compound(int x0, int y0, int ring, int biome, int kind)
{
    int w = 7 + rn2(4), h = 4 + rn2(2), lx = x0 + 1, ly = y0 + 1,
        hx = lx + w - 1, hy = ly + h - 1, side = rn2(4), i;
    struct mkroom *croom;
    boolean lit = (kind != MORGUE && kind != BEEHIVE) ? TRUE : !rn2(3);
    coord cc;

    nhUse(biome);
    nhUse(ring);
    croom = ow_building(lx, ly, hx, hy, kind, side, lit);
    if (!croom)
        return;
    if (kind == TEMPLE) {
        ow_make_temple(croom, induced_align(60));
        ow_finish_room(croom);
        return;
    }
    if (kind == MORGUE) {
        for (i = rn1(3, 2); i > 0; i--)
            if (ow_find_spot(lx, ly, hx, hy, &cc, TRUE)
                && levl[cc.x][cc.y].typ == ROOM) {
                levl[cc.x][cc.y].typ = GRAVE;
                make_grave(cc.x, cc.y, (char *) 0);
            }
    }
    ow_finish_room(croom);
    fill_special_room(croom);
}

/* broken walls of some long-gone building, with things left behind */
staticfn void
ow_ruins(int x0, int y0, int x1, int y1, int ring)
{
    int n = rn1(3, 2), i, j, x, y, w, h;
    coord cc;

    nhUse(ring);
    for (i = 0; i < n; i++) {
        w = rn1(6, 4), h = rn1(4, 3);
        x = rn1(x1 - x0 - w - 3, x0 + 2), y = rn1(y1 - y0 - h - 3, y0 + 2);
        if (!ow_rect_clear(x - 1, y - 1, x + w, y + h, FALSE))
            continue;
        ow_walls(x, y, x + w - 1, y + h - 1, OWF_MOUNTAIN);
        ow_floor(x, y, x + w - 1, y + h - 1, OWF_DIRT, TRUE);
        /* knock holes in the walls */
        for (j = rn1(6, 3); j > 0; j--) {
            int wx = rn1(w + 2, x - 1), wy = rn1(h + 2, y - 1);

            if (IS_WALL(levl[wx][wy].typ)) {
                levl[wx][wy].typ = ROOM;
                levl[wx][wy].flavor = OWF_DIRT;
                if (!rn2(3))
                    (void) mksobj_at(ROCK, wx, wy, TRUE, FALSE);
            }
        }
        if (ow_find_spot(x, y, x + w - 1, y + h - 1, &cc, TRUE))
            (void) mkobj_at(RANDOM_CLASS, cc.x, cc.y, TRUE);
        if (!rn2(3) && ow_find_spot(x, y, x + w - 1, y + h - 1, &cc, TRUE))
            (void) mksobj_at(CHEST, cc.x, cc.y, TRUE, FALSE);
        if (!rn2(2) && ow_find_spot(x, y, x + w - 1, y + h - 1, &cc, TRUE))
            mktrap(0, MKTRAP_NOFLAGS, (struct mkroom *) 0, &cc);
        if (!rn2(3) && ow_find_spot(x, y, x + w - 1, y + h - 1, &cc, TRUE))
            (void) makemon(!rn2(3) ? mkclass(S_ZOMBIE, 0)
                                   : (struct permonst *) 0,
                           cc.x, cc.y, NO_MM_FLAGS);
        if (!rn2(4) && ow_find_spot(x, y, x + w - 1, y + h - 1, &cc, TRUE))
            (void) mkcorpstat(STATUE, (struct monst *) 0,
                              (struct permonst *) 0, cc.x, cc.y,
                              CORPSTAT_INIT);
    }
}

/* a lone wayside shrine: an unattended altar */
staticfn void
ow_shrine(int x0, int y0, int x1, int y1, int ring)
{
    coord cc;
    int x, y;

    nhUse(ring);
    if (!ow_find_spot(x0 + 3, y0 + 3, x1 - 3, y1 - 3, &cc, FALSE))
        return;
    for (x = cc.x - 1; x <= cc.x + 1; x++)
        for (y = cc.y - 1; y <= cc.y + 1; y++)
            if (levl[x][y].typ == ROOM || levl[x][y].typ == TREE) {
                levl[x][y].typ = ROOM;
                levl[x][y].flavor = OWF_PAVED;
            }
    levl[cc.x][cc.y].typ = ALTAR;
    levl[cc.x][cc.y].altarmask = Align2amask(rn2(3) - 1);
    if (!rn2(3) && levl[cc.x][cc.y + 1].typ == ROOM)
        make_engr_at(cc.x, cc.y + 1, "Pray here", NULL, 0L, ENGRAVE);
}

/* a camp of some band of monsters, with their loot */
staticfn void
ow_camp(int x0, int y0, int x1, int y1, int ring)
{
    static const char camp_classes[] = { S_ORC, S_KOBOLD, S_GNOME,
                                         S_HUMANOID, S_GIANT, S_CENTAUR,
                                         S_OGRE, S_TROLL, S_HUMAN };
    int n = rn1(4, 3), i, cls;
    coord cc, ctr;
    struct permonst *pm;

    if (!ow_find_spot(x0 + 4, y0 + 4, x1 - 4, y1 - 4, &ctr, FALSE))
        return;
    /* ring deeper camps get tougher bands */
    cls = rn2(3) + ring / 5; /* (not inside min(): rn2() would be
                                 evaluated twice) */
    cls = camp_classes[max(0, min((int) SIZE(camp_classes) - 1, cls))];
    for (i = 0; i < n; i++) {
        if (!ow_find_spot(ctr.x - 3, ctr.y - 3, ctr.x + 3, ctr.y + 3, &cc,
                          FALSE))
            continue;
        pm = mkclass(cls, 0);
        if (pm)
            (void) makemon(pm, cc.x, cc.y, NO_MM_FLAGS);
    }
    (void) mkgold((long) rn1(ring * 30, 20), ctr.x, ctr.y);
    for (i = rn2(3); i >= 0; i--)
        (void) mkobj_at(!rn2(3) ? WEAPON_CLASS : RANDOM_CLASS, ctr.x, ctr.y,
                        TRUE);
}

/* an oasis in the desert */
staticfn void
ow_oasis(int x0, int y0, int x1, int y1, int ring)
{
    coord cc;
    int x, y;

    nhUse(ring);
    if (!ow_find_spot(x0 + 5, y0 + 5, x1 - 5, y1 - 5, &cc, FALSE))
        return;
    for (x = cc.x - 4; x <= cc.x + 4; x++)
        for (y = cc.y - 3; y <= cc.y + 3; y++) {
            long dd = (long) (x - cc.x) * (x - cc.x) * 2
                      + (long) (y - cc.y) * (y - cc.y) * 4;

            if (dd > 40 || levl[x][y].typ != ROOM)
                continue;
            levl[x][y].flavor = OWF_GRASS;
            if (dd <= 6)
                levl[x][y].typ = POOL;
            else if (!rn2(3))
                levl[x][y].typ = TREE;
        }
    if (levl[cc.x + 3][cc.y].typ == ROOM) {
        levl[cc.x + 3][cc.y].typ = FOUNTAIN;
        levl[cc.x + 3][cc.y].flags = 0;
        svl.level.flags.nfountains++;
    }
}

/* an old graveyard, unwalled */
staticfn void
ow_graveyard(int x0, int y0, int x1, int y1, int ring)
{
    int n = rn1(6, 4), i;
    coord cc;

    nhUse(ring);
    for (i = 0; i < n; i++) {
        if (!ow_find_spot(x0 + 6, y0 + 6, x1 - 6, y1 - 6, &cc, FALSE))
            continue;
        levl[cc.x][cc.y].typ = GRAVE;
        make_grave(cc.x, cc.y, (char *) 0);
        if (!rn2(3))
            (void) makemon(mkclass(!rn2(3) ? S_MUMMY
                                   : !rn2(2) ? S_ZOMBIE : S_WRAITH, 0),
                           cc.x, cc.y, NO_MM_FLAGS);
    }
    svl.level.flags.graveyard = 1;
}

/* a demon's lair in Gehennom */
staticfn void
ow_hell_lair(int x0, int y0, int x1, int y1, int ring)
{
    coord cc;
    int i;
    struct monst *mtmp;

    nhUse(ring);
    if (!ow_find_spot(x0 + 4, y0 + 4, x1 - 4, y1 - 4, &cc, FALSE))
        return;
    mtmp = makemon(mkclass(S_DEMON, 0), cc.x, cc.y, NO_MM_FLAGS);
    if (mtmp)
        mtmp->msleeping = rn2(2);
    for (i = rn1(3, 2); i > 0; i--)
        (void) mkobj_at(RANDOM_CLASS, cc.x, cc.y, TRUE);
    (void) mkgold((long) rn1(ring * 50, 100), cc.x, cc.y);
    for (i = rn2(3); i > 0; i--) {
        coord tc;

        if (ow_find_spot(cc.x - 3, cc.y - 3, cc.x + 3, cc.y + 3, &tc, FALSE))
            (void) maketrap(tc.x, tc.y, FIRE_TRAP);
    }
}

/* decide what, if anything, gets built in a chunk */
staticfn void
ow_structures(int cx, int cy, int x0, int y0, int x1, int y1)
{
    int mx = (x0 + x1) / 2, my = (y0 + y1) / 2,
        ring = ow_ring_at(mx, my), biome = ow_biome_at(mx, my),
        roll = (int) (ow_hash(cx, cy, 1409) % 1000), tx, ty, kind;
    boolean hell = ow_in_gehennom(mx, my);

    if (biome == OWB_BARRIER || biome == OWB_EDGE || ow_dist(mx, my) < 24)
        return;
    if (ow_past_barrier(x0, y0) != ow_past_barrier(x1, y1)
        || ow_past_barrier(x0, y1) != ow_past_barrier(x1, y0))
        return; /* straddles the barrier */

    if (hell) {
        if (roll < 40)
            ow_hell_lair(x0, y0, x1, y1, ring);
        else if (roll < 70)
            ow_ruins(x0, y0, x1, y1, ring);
        else if (roll < 85)
            ow_camp(x0, y0, x1, y1, ring);
        else if (roll < 95 && ow_rect_clear(x0 + 6, y0 + 6, x0 + 17,
                                            y0 + 13, FALSE))
            ow_compound(x0 + 6, y0 + 6, ring, biome,
                        rn2(3) ? MORGUE : BARRACKS);
        return;
    }
    /* towns and villages */
    if (roll < 110 && biome != OWB_MOUNTAIN && biome != OWB_LAKE
        && biome != OWB_SWAMP && biome != OWB_BARRENS) {
        boolean big = (roll < 40);

        tx = x0 + (big ? 2 : 6), ty = y0 + (big ? 7 : 9);
        if (ow_rect_clear(tx, ty, tx + (big ? 26 : 18), ty + (big ? 16 : 12),
                          FALSE)) {
            ow_town(tx, ty, ring, biome, big ? 1 : 0,
                    (boolean) (ring > 16 && rn2(3)));
            return;
        }
    }
    if (roll < 160 && biome == OWB_MOUNTAIN) {
        ow_vault(x0, y0, x1, y1, ring);
        return;
    }
    if (roll < 200) {
        /* special rooms, chosen by depth the way makelevel() does it */
        if (ring > 4 && !rn2(6))
            kind = COURT;
        else if (ring > 5 && !rn2(8)
                 && !(svm.mvitals[PM_LEPRECHAUN].mvflags & G_GONE))
            kind = LEPREHALL;
        else if (ring > 6 && !rn2(7))
            kind = ZOO;
        else if (ring > 8 && !rn2(5))
            kind = TEMPLE;
        else if (ring > 9 && !rn2(5)
                 && !(svm.mvitals[PM_KILLER_BEE].mvflags & G_GONE))
            kind = BEEHIVE;
        else if (ring > 11 && !rn2(6))
            kind = MORGUE;
        else if (ring > 12 && !rn2(8) && antholemon())
            kind = ANTHOLE;
        else if (ring > 14 && !rn2(4)
                 && !(svm.mvitals[PM_SOLDIER].mvflags & G_GONE))
            kind = BARRACKS;
        else if (ring > 16 && !rn2(8)
                 && !(svm.mvitals[PM_COCKATRICE].mvflags & G_GONE))
            kind = COCKNEST;
        else
            kind = -1;
        tx = x0 + 6, ty = y0 + 8;
        if (kind >= 0 && ow_rect_clear(tx, ty, tx + 13, ty + 8, FALSE)) {
            ow_compound(tx, ty, ring, biome, kind);
            return;
        }
    }
    if (roll < 240 || biome == OWB_RUINS) {
        if (biome == OWB_RUINS || roll < 225) {
            ow_ruins(x0, y0, x1, y1, ring);
            return;
        }
    }
    if (roll < 265) {
        ow_shrine(x0, y0, x1, y1, ring);
        return;
    }
    if (roll < 300 && ring > 2) {
        ow_camp(x0, y0, x1, y1, ring);
        return;
    }
    if (roll < 350 && biome == OWB_DESERT) {
        ow_oasis(x0, y0, x1, y1, ring);
        return;
    }
    if (roll < 370 && ring > 5) {
        ow_graveyard(x0, y0, x1, y1, ring);
        return;
    }
}

/* ------------------------------------------------------------------ */
/* population                                                          */
/* ------------------------------------------------------------------ */

staticfn void
ow_populate(int cx, int cy, int x0, int y0, int x1, int y1)
{
    int mx = (x0 + x1) / 2, my = (y0 + y1) / 2, ring = ow_ring_at(mx, my),
        biome = ow_biome_at(mx, my), n, i, x, y;
    boolean hell = ow_in_gehennom(mx, my), nearhome = ow_dist(mx, my) < 28;
    struct monst *mtmp;
    struct obj *otmp;
    coord cc;
    char buf[BUFSZ];

    nhUse(cx);
    nhUse(cy);
    if (biome == OWB_EDGE)
        return;

    /* monsters */
    n = nearhome ? rn2(2) : rn2(3) + (hell ? 1 : 0) + (ring > 20 ? 1 : 0);
    for (i = 0; i < n; i++) {
        if (!ow_find_spot(x0, y0, x1, y1, &cc, FALSE))
            continue;
        if (nearhome && ow_dist(cc.x, cc.y) < 18)
            continue; /* keep the plaza's surroundings peaceful */
        ow_gen_depth = ow_ring_at(cc.x, cc.y);
        ow_gen_x = cc.x, ow_gen_y = cc.y;
        mtmp = makemon((struct permonst *) 0, cc.x, cc.y, NO_MM_FLAGS);
        if (mtmp && mtmp->data == &mons[PM_GIANT_SPIDER]
            && !t_at(cc.x, cc.y))
            (void) maketrap(cc.x, cc.y, WEB);
    }
    /* aquatic life in lakes */
    if (biome == OWB_LAKE || biome == OWB_SWAMP) {
        for (i = rn2(3); i > 0; i--) {
            x = rn1(x1 - x0 + 1, x0), y = rn1(y1 - y0 + 1, y0);
            if (is_pool(x, y) && !MON_AT(x, y)) {
                struct permonst *pm = mkclass(S_EEL, 0);

                if (pm)
                    (void) makemon(pm, x, y, NO_MM_FLAGS);
            }
            if (is_pool(x, y) && !rn2(2))
                (void) mksobj_at(KELP_FROND, x, y, TRUE, FALSE);
        }
    }
    ow_gen_depth = ring;
    ow_gen_x = mx, ow_gen_y = my;

    /* objects lying about */
    for (i = rn2(3); i > 0; i--)
        if (ow_find_spot(x0, y0, x1, y1, &cc, FALSE))
            (void) mkobj_at(RANDOM_CLASS, cc.x, cc.y, TRUE);
    if (!rn2(3) && ow_find_spot(x0, y0, x1, y1, &cc, FALSE))
        (void) mkgold((long) rnd(10 + rnd(ring + 2) * rnd(30)), cc.x, cc.y);
    if (!rn2(8) && ow_find_spot(x0, y0, x1, y1, &cc, FALSE))
        (void) mksobj_at(rn2(3) ? LARGE_BOX : CHEST, cc.x, cc.y, TRUE, FALSE);
    if (!rn2(12) && ow_find_spot(x0, y0, x1, y1, &cc, FALSE))
        (void) mkcorpstat(STATUE, (struct monst *) 0, (struct permonst *) 0,
                          cc.x, cc.y, CORPSTAT_INIT);
    /* boulders in the hills */
    if (biome == OWB_HILLS || biome == OWB_DESERT || biome == OWB_BARRENS) {
        for (i = rn2(5); i > 0; i--)
            if (ow_find_spot(x0, y0, x1, y1, &cc, FALSE))
                (void) mksobj_at(BOULDER, cc.x, cc.y, TRUE, FALSE);
    }

    /* traps */
    n = nearhome ? 0 : rn2(3) + (hell ? 1 : 0);
    for (i = 0; i < n; i++)
        if (ow_find_spot(x0, y0, x1, y1, &cc, FALSE))
            mktrap(0, MKTRAP_NOFLAGS, (struct mkroom *) 0, &cc);

    /* dungeon features */
    if (!hell && !rn2(20) && ow_find_spot(x0, y0, x1, y1, &cc, FALSE)) {
        levl[cc.x][cc.y].typ = FOUNTAIN;
        levl[cc.x][cc.y].flags = 0;
        svl.level.flags.nfountains++;
    }
    if (!rn2(25) && ow_find_spot(x0, y0, x1, y1, &cc, FALSE)) {
        levl[cc.x][cc.y].typ = GRAVE;
        make_grave(cc.x, cc.y, (char *) 0);
        if (!rn2(3))
            (void) mkgold((long) rnd(20 + ring * 5), cc.x, cc.y);
        if (!rn2(2)) {
            otmp = mkobj(RANDOM_CLASS, TRUE);
            if (otmp) {
                otmp->ox = cc.x, otmp->oy = cc.y;
                add_to_buried(otmp);
            }
        }
    }
    if (!rn2(8) && ow_find_spot(x0, y0, x1, y1, &cc, FALSE)) {
        char pristine[BUFSZ];

        (void) random_engraving(buf, pristine);
        if (*buf)
            make_engr_at(cc.x, cc.y, buf, NULL, 0L, !rn2(3) ? ENGRAVE : DUST);
    }

    /* precious things buried in the rock of the mountains, as mineralize()
       does for ordinary levels */
    for (x = max(x0, 1); x <= x1; x++)
        for (y = y0; y <= y1; y++) {
            struct rm *lev = &levl[x][y];

            if (lev->typ != STONE || lev->flavor != OWF_MOUNTAIN
                || (lev->wall_info & W_NONDIGGABLE))
                continue;
            if (!rn2(400)) {
                otmp = mksobj(rn2(3) ? ROCK : GOLD_PIECE, FALSE, FALSE);
                if (otmp->otyp == GOLD_PIECE)
                    otmp->quan = 1L + rnd(ring * 3),
                    otmp->owt = weight(otmp);
                else
                    obfree(otmp, (struct obj *) 0), otmp = 0;
                if (otmp) {
                    otmp->ox = x, otmp->oy = y;
                    add_to_buried(otmp);
                }
            } else if (!rn2(600)) {
                otmp = mkobj(GEM_CLASS, FALSE);
                if (otmp) {
                    if (otmp->otyp == ROCK) {
                        dealloc_obj(otmp);
                    } else {
                        otmp->ox = x, otmp->oy = y;
                        add_to_buried(otmp);
                    }
                }
            }
        }
}

/* ------------------------------------------------------------------ */
/* making the level, and arriving on it                                */
/* ------------------------------------------------------------------ */

/* create the overworld (called from makelevel()) */
void
mkoverworld(void)
{
    if (!svow.inited)
        ow_init();
    ow_world_dump(); /* (only when testing) */
    svl.level.flags.hero_memory = 1;
    svl.level.flags.is_maze_lev = 0;
    svl.level.flags.temperature = 0;
    /* no stairs; depth varies across the map, so no traditional branch
       stairs are placed (see ow_make_portal_sites()) */
    gm.made_branch = TRUE;
    ow_generate_area(OW_CX, OW_CY, OW_GEN_RADIUS);
}

/* find a place near <x,y> to put the hero */
staticfn boolean
ow_rndspot_near(int x, int y, int rad, int tries, coord *cc, boolean safe)
{
    int i, nx, ny, r;

    ow_ensure_generated(x, y);
    if (isok(x, y) && goodpos(x, y, &gy.youmonst, 0)
        && (!safe || !t_at(x, y))
        && (!ow_want_ring || ow_ring_at(x, y) == ow_want_ring)) {
        cc->x = x, cc->y = y;
        return TRUE;
    }
    for (r = 1; r <= rad; r++)
        for (i = 0; i < tries; i++) {
            nx = x + rn2(2 * r + 1) - r;
            ny = y + rn2(2 * r + 1) - r;
            if (!isok(nx, ny) || !ow_generated(nx, ny))
                continue;
            if (ow_past_barrier(x, y) != ow_past_barrier(nx, ny))
                continue;
            if (ow_want_ring && ow_ring_at(nx, ny) != ow_want_ring)
                continue;
            if (goodpos(nx, ny, &gy.youmonst, 0)
                && (!safe || !t_at(nx, ny))) {
                cc->x = nx, cc->y = ny;
                return TRUE;
            }
        }
    return FALSE;
}

/* put the hero on the portal of dungeon 'dnum' used last, or failing that
   on one of that dungeon's portals */
staticfn void
ow_place_on_portal(xint16 dnum, coordxy *ox, coordxy *oy)
{
    struct ow_portalrec *pr = ow_find_portrec(dnum);
    int r, px = 0, py = 0;

    if (pr) {
        *ox = pr->x, *oy = pr->y;
        return;
    }
    for (r = 0; r < svow.nrings; r++)
        if (svow.rings[r].dnum == dnum) {
            ow_portal_pos(&svow.rings[r], 0, &px, &py);
            *ox = px, *oy = py;
            return;
        }
    /* not a portal branch (Fort Ludios' vault portal, say): the center */
    ow_home_altar(ox, oy);
}

/*
 * The hero is arriving in the overworld from 'from' (u.uz0).  Put the
 * hero where they belong: back at the portal they left through, at the
 * ring chosen for a level teleport, or at the start.
 */
void
ow_arrive(int how)
{
    coordxy x = 0, y = 0;
    coord cc;
    xint16 fromdn = u.uz0.dnum;
    struct trap *ttmp;

    /* arriving by some means that didn't choose a destination (rising
       through the ceiling out of a branch, say): treat like the stairs */
    if (how == OWARR_LEVTELE && !svow.lt_x)
        how = OWARR_STAIRS;
    if (how == OWARR_NEWGAME || !u.uz0.dlevel || In_tutorial(&u.uz0)) {
        ow_home_altar(&x, &y);
    } else if (how == OWARR_LEVTELE) {
        x = svow.lt_x, y = svow.lt_y;
    } else if (fromdn == ow_dnum_named("Gehennom") && how == OWARR_PORTAL
               && ow_find_portrec(fromdn)) {
        /* back out through a Valley gate */
        ow_place_on_portal(fromdn, &x, &y);
    } else if (fromdn == ow_dnum_named("Gehennom") && how == OWARR_PORTAL) {
        /* first passage out of the Valley: emerge at the gate on the far
           side of the barrier nearest to where the hero entered Medusa's
           island, or at some gate */
        struct ow_portalrec *mr = ow_find_portrec(medusa_level.dnum);
        int bearing = mr ? ow_bearing(mr->x, mr->y) : rn2(360), r, k, best = 9999;

        for (r = 0; r < svow.nrings; r++) {
            struct ow_ringinfo *ri = &svow.rings[r];

            if (ri->dnum != fromdn)
                continue;
            for (k = 0; k < ri->nportals; k++) {
                int px, py, diff;

                ow_portal_pos(ri, k, &px, &py);
                diff = ow_bearing(px, py) - bearing;
                while (diff > 180)
                    diff -= 360;
                while (diff < -180)
                    diff += 360;
                if (diff < 0)
                    diff = -diff;
                if (diff < best)
                    best = diff, x = px, y = py;
            }
        }
        if (x)
            ow_note_portal(fromdn, x, y);
        else
            ow_home_altar(&x, &y);
    } else {
        ow_place_on_portal(ow_root_branch(fromdn), &x, &y);
    }
    ow_ensure_generated(x, y);
    if (how == OWARR_LEVTELE && !svow.lt_exact) {
        ow_want_ring = ow_ring_at(x, y);
        if (ow_rndspot_near(x, y, 12, 30, &cc, TRUE))
            x = cc.x, y = cc.y;
        ow_want_ring = 0;
    } else if (!goodpos(x, y, &gy.youmonst, 0) && !MON_AT(x, y)) {
        if (ow_rndspot_near(x, y, 6, 30, &cc, FALSE))
            x = cc.x, y = cc.y;
    }
    if (getenv("OWHACK_TIMING")) {
        struct trap *tt;

        for (tt = gf.ftrap; tt; tt = tt->ntrap)
            if (tt->ttyp == MAGIC_PORTAL && ow_dist(tt->tx, tt->ty) > 500)
                fprintf(stderr, "(far portal %d,%d)\n", tt->tx, tt->ty);
    }
    if (getenv("OWHACK_TIMING"))
        fprintf(stderr, "ow_arrive how=%d from dnum %d -> %d,%d goodpos=%d mon=%d trap=%d\n",
                how, fromdn, x, y, goodpos(x, y, &gy.youmonst, 0),
                MON_AT(x, y) ? 1 : 0, t_at(x, y) ? t_at(x, y)->ttyp : -1);
    svow.lt_x = svow.lt_y = 0;
    u_on_newpos(x, y);
    if ((ttmp = t_at(x, y)) != 0 && ttmp->ttyp == MAGIC_PORTAL)
        seetrap(ttmp);
    svow.last_ring_seen = (xint16) ow_ring_at(x, y);
    svow.last_zone_msg = -1;
}

/* ------------------------------------------------------------------ */
/* teleportation and level teleportation                               */
/* ------------------------------------------------------------------ */

/*
 * Pick a random destination for an ordinary (within-level) teleport of the
 * hero.  In the overworld, "the level" is the neighborhood: the destination
 * is within OW_LOCAL_RX x OW_LOCAL_RY of the starting point, on generated
 * land, and never on the other side of the Gehennom barrier.
 */
boolean
ow_rnd_teleport_spot(coordxy fromx, coordxy fromy, coord *cc,
                     struct monst *mon)
{
    int tries;
    coordxy x, y;
    boolean past = ow_past_barrier(fromx, fromy);

    for (tries = 0; tries < 400; tries++) {
        x = fromx + rn2(2 * OW_LOCAL_RX + 1) - OW_LOCAL_RX;
        y = fromy + rn2(2 * OW_LOCAL_RY + 1) - OW_LOCAL_RY;
        if (!isok(x, y) || !ow_generated(x, y))
            continue;
        if (ow_past_barrier(x, y) != past)
            continue;
        if (tries < 350 && levl[x][y].roomno && !mon)
            continue; /* prefer not to pop into shops and temples */
        if (mon ? goodpos(x, y, mon, 0)
                : (teleok(x, y, tries < 200) && !(x == fromx && y == fromy)))
        {
            cc->x = x, cc->y = y;
            return TRUE;
        }
    }
    return FALSE;
}

/* the deepest ring that the hero may level teleport to */
int
ow_max_teleport_ring(void)
{
    if (!u.uevent.gehennom_entered && !wizard)
        return svow.barrier_ring - 1;
    return svow.max_ring - 1;
}

/*
 * Level teleport within the open world: arrange to arrive in the overworld
 * at depth (ring) 'newdepth', along the bearing of 'fromx,fromy' (or a
 * random bearing), and return the destination level.
 */
void
ow_prepare_levtele(int newdepth, boolean random_bearing)
{
    int bearing, r, x, y;
    struct ow_portalrec *pr;

    if (newdepth < 1)
        newdepth = 1;
    if (newdepth > ow_max_teleport_ring())
        newdepth = ow_max_teleport_ring();
    if (In_overworld && u.ux && ow_dist(u.ux, u.uy) > 2 && !random_bearing) {
        bearing = ow_bearing(u.ux, u.uy);
    } else if (!In_overworld
               && (pr = ow_find_portrec(ow_root_branch(u.uz.dnum))) != 0
               && !random_bearing) {
        bearing = ow_bearing(pr->x, pr->y);
    } else {
        bearing = rn2(360);
    }
    r = (newdepth - 1) * OW_RING_WIDTH + 2 + rn2(OW_RING_WIDTH - 4);
    if (newdepth == 1)
        r = 10 + rn2(OW_RING_WIDTH - 12);
    ow_polar(r, bearing, &x, &y);
    svow.lt_x = x, svow.lt_y = y, svow.lt_exact = FALSE;
}

/* ------------------------------------------------------------------ */
/* monster activity                                                    */
/* ------------------------------------------------------------------ */

/*
 * Monsters in the overworld only act when the hero is within their
 * neighborhood.  A monster on the far side of the world doesn't come
 * hunting just because it is technically on the same level.
 */
boolean
ow_mon_dormant(struct monst *mtmp)
{
    int dx, dy;

    if (!In_overworld || !u.ux)
        return FALSE;
    dx = mtmp->mx - u.ux, dy = mtmp->my - u.uy;
    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;
    if (dx <= OW_ACTIVE_RX && dy <= OW_ACTIVE_RY)
        return FALSE;
    /* the Wizard and those who covet what the hero carries don't rest */
    if (mtmp->iswiz)
        return FALSE;
    if (is_covetous(mtmp->data)
        && (u.uhave.amulet || u.uhave.bell || u.uhave.book
            || u.uhave.menorah || u.uhave.questart))
        return FALSE;
    return TRUE;
}

/* random spot for a randomly generated monster: out of the hero's sight
   but within the hero's neighborhood */
boolean
ow_rnd_monpos(struct monst *mon, mmflags_nht gpflags, coord *cc)
{
    int tries, x, y;
    boolean past;

    if (!u.ux)
        return FALSE;
    past = ow_past_barrier(u.ux, u.uy);
    for (tries = 0; tries < 200; tries++) {
        x = u.ux + rn2(2 * OW_ACTIVE_RX + 1) - OW_ACTIVE_RX;
        y = u.uy + rn2(2 * OW_ACTIVE_RY + 1) - OW_ACTIVE_RY;
        if (!isok(x, y) || !ow_generated(x, y))
            continue;
        if (ow_past_barrier(x, y) != past || ow_dist(x, y) < 12)
            continue;
        if (distmin(x, y, u.ux, u.uy) < 8)
            continue;
        if (tries < 150 && cansee(x, y))
            continue;
        if (goodpos(x, y, mon, gpflags)) {
            cc->x = x, cc->y = y;
            return TRUE;
        }
    }
    return FALSE;
}

/* ------------------------------------------------------------------ */
/* level-wide effects                                                  */
/* ------------------------------------------------------------------ */

/*
 * Bounds of "the level" for effects that traditionally cover a whole
 * dungeon level (magic mapping, object and gold detection, clairvoyance,
 * and so on).  In the overworld that's the hero's neighborhood.
 */
void
lvl_effect_bounds(coordxy *lx, coordxy *ly, coordxy *hx, coordxy *hy)
{
    if (In_overworld && u.ux) {
        *lx = max(1, u.ux - OW_LOCAL_RX);
        *hx = min(COLNO - 1, u.ux + OW_LOCAL_RX);
        *ly = max(0, u.uy - OW_LOCAL_RY);
        *hy = min(ROWNO - 1, u.uy + OW_LOCAL_RY);
    } else {
        *lx = 1, *hx = COLNO - 1;
        *ly = 0, *hy = ROWNO - 1;
    }
}

/* is <x,y> within the area affected by level-wide effects? */
boolean
in_lvl_effect_bounds(coordxy x, coordxy y)
{
    coordxy lx, ly, hx, hy;

    lvl_effect_bounds(&lx, &ly, &hx, &hy);
    return (boolean) (x >= lx && x <= hx && y >= ly && y <= hy);
}

/* ------------------------------------------------------------------ */
/* compass                                                             */
/* ------------------------------------------------------------------ */

/* direction from the hero toward the center as one of 8 compass points;
   returns index 0..7 = N NE E SE S SW W NW, or -1 if at the center */
int
ow_home_dir(void)
{
    int dx, dy, a;
    double ang;
    coordxy hx, hy;

    ow_home_altar(&hx, &hy);
    dx = hx - u.ux, dy = hy - u.uy;
    if (!dx && !dy)
        return -1;
    /* screen coordinates: north is up (negative y) */
    ang = atan2((double) -dy, (double) dx) * 180.0 / 3.14159265358979;
    a = (int) (ang + 360.0) % 360; /* 0 = east, counterclockwise */
    /* convert to 0 = north, clockwise, in 45 degree sectors */
    a = (450 - a) % 360;
    return ((a + 22) / 45) % 8;
}

static const char *const ow_dirnames[8] = {
    "N", "NE", "E", "SE", "S", "SW", "W", "NW"
};

/* text for the status line: direction and distance to the center */
char *
ow_compass_str(char *buf)
{
    coordxy hx, hy;
    int d;

    *buf = '\0';
    if (!In_overworld || !svow.inited || !u.ux || !flags.compass)
        return buf;
    ow_home_altar(&hx, &hy);
    d = ow_dist(u.ux, u.uy);
    if (u.ux == hx && u.uy == hy)
        Strcpy(buf, "Home:here");
    else if (ow_home_dir() >= 0)
        Sprintf(buf, "Home:%s %d", ow_dirnames[ow_home_dir()], d);
    return buf;
}

/*
 * Draw a compass rose in the top right corner of the map window, with the
 * spoke pointing toward the center of the world highlighted.  Called at
 * the end of flush_screen().
 */
void
ow_draw_compass(void)
{
    static const char spokes[8] = { '|', '/', '-', '\\', '|', '/', '-', '\\' };
    static const int sdx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 },
                     sdy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
    glyph_info ginf;
    int dir, i, cx, cy;

    if (!In_overworld || !svow.inited || !flags.compass || !u.ux
        || gvp.w < 30 || gvp.h < 8)
        return;
    dir = ow_home_dir();
    cx = gvp.w - 2, cy = 1; /* window coordinates of the rose's center */
    for (i = 0; i < 9; i++) {
        int k, wx, wy;
        boolean hot;

        ginf = nul_glyphinfo;
        if (i == 8) {
            wx = cx, wy = cy;
            ginf.ttychar = (dir < 0) ? '*' : '+';
            ginf.gm.sym.color = (dir < 0) ? CLR_YELLOW : CLR_GRAY;
        } else {
            k = i;
            wx = cx + sdx[k], wy = cy + sdy[k];
            hot = (k == dir);
            ginf.ttychar = spokes[k];
            ginf.gm.sym.color = hot ? CLR_YELLOW : CLR_BLUE;
        }
        ginf.glyph = cmap_to_glyph(S_stone);
        ginf.gm.glyphflags &= ~MG_UNEXPL;
        print_glyph(WIN_MAP, wx + 1, wy, &ginf, &nul_glyphinfo);
    }
}

/* the compass rose covers these map window cells */
boolean
ow_compass_covers(int wx, int wy)
{
    int cx, cy;

    if (!In_overworld || !svow.inited || !flags.compass
        || gvp.w < 30 || gvp.h < 8)
        return FALSE;
    cx = gvp.w - 2, cy = 1;
    return (boolean) (wx >= cx - 1 && wx <= cx + 1 && wy >= cy - 1
                      && wy <= cy + 1);
}

/* level teleport from one ring of the overworld to another: an ordinary
   teleport as far as the game is concerned */
void
ow_levtele_within(int newdepth)
{
    coord cc;
    int x = svow.lt_x, y = svow.lt_y;

    nhUse(newdepth);
    if (!x) {
        You1(shudder_for_moment);
        return;
    }
    ow_ensure_generated(x, y);
    ow_want_ring = ow_ring_at(x, y);
    if (!ow_rndspot_near(x, y, 14, 40, &cc, TRUE)) {
        ow_want_ring = 0;
        svow.lt_x = svow.lt_y = 0;
        You1(shudder_for_moment);
        return;
    }
    ow_want_ring = 0;
    svow.lt_x = svow.lt_y = 0;
    teleds(cc.x, cc.y, TELEDS_TELEPORT);
    if (flags.verbose)
        You("materialize %s!", (ow_ring_at(u.ux, u.uy) > newdepth - 1)
                               ? "far from where you were"
                               : "somewhere far away");
    ow_maintain();
}

/* is overworld location <x,y> under a roof (in a building or cave)? */
boolean
ow_under_roof(coordxy x, coordxy y)
{
    int b;

    if (!isok(x, y))
        return FALSE;
    if (levl[x][y].roomno >= ROOMOFFSET) {
        struct mkroom *croom = &svr.rooms[levl[x][y].roomno - ROOMOFFSET];

        /* towns are open-air enclosures; buildings within have roofs */
        if (croom >= svr.rooms && croom < svr.rooms + MAXNROFROOMS
            && croom->rtype == OROOM)
            return FALSE;
        return TRUE;
    }
    b = ow_biome_at(x, y);
    return (boolean) ((b == OWB_MOUNTAIN || b == OWB_HELLCAVE)
                      && levl[x][y].flavor == (b == OWB_MOUNTAIN ? OWF_DIRT
                                                                 : OWF_ASH)
                      && !ow_on_road(x, y));
}

/* ------------------------------------------------------------------ */
/* appearance of terrain                                               */
/* ------------------------------------------------------------------ */

/* color for a map symbol at overworld location <x,y>, or NO_COLOR to
   leave the default */
int
ow_flavor_color(coordxy x, coordxy y, int cmap)
{
    int fl = levl[x][y].flavor;

    if (cmap == S_room) {
        switch (fl) {
        case OWF_GRASS:
        case OWF_FOREST:
            return CLR_GREEN;
        case OWF_SAND:
            return CLR_YELLOW;
        case OWF_SNOW:
        case OWF_MARBLE:
            return CLR_WHITE;
        case OWF_ASH:
            return CLR_RED;
        case OWF_MUD:
        case OWF_DIRT:
            return CLR_BROWN;
        default:
            return NO_COLOR;
        }
    } else if (is_cmap_wall(cmap) && cmap != S_stone) {
        switch (fl) {
        case OWF_MOUNTAIN:
            return CLR_BROWN;
        case OWF_HELLROCK:
            return CLR_RED;
        case OWF_BARRIER:
            return CLR_MAGENTA;
        default:
            return NO_COLOR;
        }
    } else if (cmap == S_tree) {
        if (fl == OWF_ASH)
            return CLR_BROWN; /* dead, blackened trees */
        if (fl == OWF_SNOW)
            return CLR_CYAN; /* snow-laden firs */
        if (fl == OWF_SAND)
            return CLR_BRIGHT_GREEN; /* cactus */
    }
    return NO_COLOR;
}

/* farlook description of overworld terrain, or Null for the default */
const char *
ow_flavor_desc(coordxy x, coordxy y, int cmap)
{
    int fl = levl[x][y].flavor;

    if (cmap == S_room || cmap == S_darkroom) {
        switch (fl) {
        case OWF_GRASS:
            return "grass";
        case OWF_FOREST:
            return "forest floor";
        case OWF_SAND:
            return "sand";
        case OWF_SNOW:
            return "snow";
        case OWF_ASH:
            return "scorched earth";
        case OWF_PAVED:
            return "paving stones";
        case OWF_MARBLE:
            return "marble paving";
        case OWF_MUD:
            return "mud";
        case OWF_DIRT:
            return "dirt";
        default:
            return (const char *) 0;
        }
    } else if (cmap == S_tree) {
        if (fl == OWF_ASH)
            return "dead tree";
        if (fl == OWF_SAND)
            return "cactus";
        if (fl == OWF_SNOW)
            return "fir tree";
    } else if (is_cmap_wall(cmap)) {
        if (fl == OWF_MOUNTAIN)
            return "mountainside";
        if (fl == OWF_HELLROCK)
            return "wall of obsidian";
        if (fl == OWF_BARRIER)
            return "the Barrier";
    }
    return (const char *) 0;
}

/* ------------------------------------------------------------------ */
/* debugging aid for the automated playtests                           */
/* ------------------------------------------------------------------ */

/* write the true terrain around <cx,cy> to a text file; only used when
   the OWHACK_MAPDUMP environment variable names the file (tests) */
void
ow_debug_dump(int cx, int cy, int rx, int ry)
{
    const char *fname = getenv("OWHACK_MAPDUMP");
    FILE *fp;
    int x, y;

    if (!fname || !*fname)
        return;
    if (!(fp = fopen(fname, "w")))
        return;
    if (!In_overworld) {
        struct trap *tt;

        fprintf(fp, "hero %d,%d dnum %d dlevel %d depth %d\n", u.ux, u.uy,
                u.uz.dnum, u.uz.dlevel, depth(&u.uz));
        for (tt = gf.ftrap; tt; tt = tt->ntrap)
            if (tt->ttyp == MAGIC_PORTAL)
                fprintf(fp, "portal %d,%d\n", tt->tx, tt->ty);
            else if (tt->ttyp == VIBRATING_SQUARE)
                fprintf(fp, "vibsq %d,%d\n", tt->tx, tt->ty);
            else
                fprintf(fp, "trap %d,%d %d\n", tt->tx, tt->ty, tt->ttyp);
        {
            stairway *st;

            for (st = gs.stairs; st; st = st->next)
                fprintf(fp, "stairs %d,%d up=%d to %d.%d\n", st->sx, st->sy,
                        st->up, st->tolev.dnum, st->tolev.dlevel);
        }
        {
            struct monst *mtmp;

            for (mtmp = fmon; mtmp; mtmp = mtmp->nmon)
                if (!DEADMONSTER(mtmp) && mtmp->data->msound == MS_LEADER)
                    fprintf(fp, "leader %d,%d\n", mtmp->mx, mtmp->my);
        }
        fclose(fp);
        return;
    }
    fprintf(fp, "hero %d,%d ring %d biome %s seed %lu nroom %d nsub %d\n",
            u.ux, u.uy, ow_ring_at(u.ux, u.uy),
            ow_biome_name(ow_biome_at(u.ux, u.uy)), svow.seed, svn.nroom,
            gn.nsubroom);
    for (y = cy - ry; y <= cy + ry; y++) {
        for (x = cx - rx; x <= cx + rx; x++) {
            char c;
            struct rm *lev;
            struct trap *t;

            if (!isok(x, y)) {
                fputc(' ', fp);
                continue;
            }
            lev = &levl[x][y];
            if (!ow_generated(x, y))
                c = '~';
            else if (x == u.ux && y == u.uy)
                c = '@';
            else if (MON_AT(x, y))
                c = 'M';
            else if ((t = t_at(x, y)) != 0)
                c = (t->ttyp == MAGIC_PORTAL) ? 'P' : '^';
            else
                switch (lev->typ) {
                case STONE: c = ' '; break;
                case TREE: c = '#'; break;
                case POOL: case MOAT: c = '}'; break;
                case LAVAPOOL: c = 'L'; break;
                case ICE: c = 'i'; break;
                case DOOR: c = '+'; break;
                case FOUNTAIN: c = '{'; break;
                case ALTAR: c = '_'; break;
                case GRAVE: c = '|'; break;
                case SINK: c = '#'; break;
                case ROOM:
                    c = lev->roomno ? 'r' : (lev->flavor == OWF_PAVED ? ','
                                            : '.');
                    break;
                default:
                    c = IS_WALL(lev->typ) ? (lev->flavor == OWF_MOUNTAIN
                                             ? 'm' : 'W') : '?';
                    break;
                }
            fputc(c, fp);
        }
        fputc('\n', fp);
    }
    for (x = 0; x < svn.nroom; x++) {
        struct mkroom *r = &svr.rooms[x];

        if (r->hx >= cx - rx && r->lx <= cx + rx && r->hy >= cy - ry
            && r->ly <= cy + ry)
            fprintf(fp, "room %d %d %d %d %d\n", r->lx, r->ly, r->hx, r->hy,
                    r->rtype);
    }
    {
        struct trap *tt;

        for (tt = gf.ftrap; tt; tt = tt->ntrap)
            if (tt->ttyp == MAGIC_PORTAL && tt->tx >= cx - rx
                && tt->tx <= cx + rx && tt->ty >= cy - ry
                && tt->ty <= cy + ry)
                fprintf(fp, "owportal %d,%d %d\n", tt->tx, tt->ty,
                        tt->dst.dnum);
    }
    {
        struct engr *ep;

        for (ep = head_engr; ep; ep = ep->nxt_engr)
            if (!ACCESSIBLE(levl[ep->engr_x][ep->engr_y].typ)
                || is_pool_or_lava(ep->engr_x, ep->engr_y))
                fprintf(fp, "badengr %d,%d typ %d \"%s\"\n", ep->engr_x,
                        ep->engr_y, levl[ep->engr_x][ep->engr_y].typ,
                        ep->engr_txt[actual_text]);
    }
    for (x = 0; x < gn.nsubroom; x++) {
        struct mkroom *r = &gs.subrooms[x];

        if (r->hx >= cx - rx && r->lx <= cx + rx && r->hy >= cy - ry
            && r->ly <= cy + ry)
            fprintf(fp, "room %d %d %d %d %d\n", r->lx, r->ly, r->hx, r->hy,
                    r->rtype);
    }
    fclose(fp);
}

/* level flags describing only the hero's neighborhood (for sounds) */
void
ow_local_levelflags(struct levelflags *lf)
{
    coordxy lx, ly, hx, hy, x, y;
    struct mkroom *croom;
    int pass, fountains = 0, sinks = 0;

    lvl_effect_bounds(&lx, &ly, &hx, &hy);
    for (x = lx; x <= hx; x++)
        for (y = ly; y <= hy; y++) {
            if (levl[x][y].typ == FOUNTAIN)
                fountains++;
            else if (levl[x][y].typ == SINK)
                sinks++;
        }
    lf->nfountains = (uchar) min(fountains, 255);
    lf->nsinks = (uchar) min(sinks, 255);
    lf->has_shop = lf->has_vault = lf->has_zoo = lf->has_court = 0;
    lf->has_morgue = lf->has_beehive = lf->has_barracks = 0;
    lf->has_temple = lf->has_swamp = 0;
    for (pass = 0; pass < 2; pass++)
        for (croom = pass ? &gs.subrooms[0] : &svr.rooms[0]; croom->hx >= 0;
             croom++) {
            if (croom->hx < lx || croom->lx > hx || croom->hy < ly
                || croom->ly > hy)
                continue;
            switch (croom->rtype) {
            case VAULT: lf->has_vault = 1; break;
            case ZOO: lf->has_zoo = 1; break;
            case COURT: lf->has_court = 1; break;
            case MORGUE: lf->has_morgue = 1; break;
            case BEEHIVE: lf->has_beehive = 1; break;
            case BARRACKS: lf->has_barracks = 1; break;
            case TEMPLE: lf->has_temple = 1; break;
            default:
                if (croom->rtype >= SHOPBASE)
                    lf->has_shop = 1;
                break;
            }
        }
    if (ow_biome_at(u.ux, u.uy) == OWB_SWAMP)
        lf->has_swamp = 1;
}

/* #overview: the portal rings that the hero knows about */
void
ow_overview_lines(winid win)
{
    char buf[BUFSZ];
    int r, k, px, py, nknown;
    boolean onow = In_overworld;

    for (r = 0; r < svow.nrings; r++) {
        struct ow_ringinfo *ri = &svow.rings[r];
        const char *dname;

        if (ri->dnum < 0 || ri->dnum >= svn.n_dgns)
            continue;
        nknown = 0;
        /* can only consult the map while it's loaded */
        if (onow)
            for (k = 0; k < ri->nportals; k++) {
                ow_portal_pos(ri, k, &px, &py);
                if (isok(px, py) && glyph_is_trap(levl[px][py].glyph))
                    nknown++;
            }
        if (!nknown && !ow_find_portrec(ri->dnum)
            && !svd.dungeons[ri->dnum].dunlev_ureached)
            continue;
        dname = ow_portal_dest_name(ri->dnum);
        Sprintf(buf, "%sPortals to %s ring the world at depth %d",
                "      ", dname, (int) ri->ring);
        if (nknown)
            Sprintf(eos(buf), " (%d of %d seen)", nknown, (int) ri->nportals);
        Strcat(buf, ".");
        (void) strsubst(buf, "to The ", "to the ");
        add_menu_str(win, buf);
    }
    if (onow && u.ux) {
        Sprintf(buf, "      Now at depth %d, in the %s.",
                ow_ring_at(u.ux, u.uy),
                ow_biome_name(ow_biome_at(u.ux, u.uy)));
        add_menu_str(win, buf);
    }
}

/* test hook: keep the dump current even outside the overworld */
void
ow_test_hook(void)
{
    const char *f;

    /* automated playtesting (wizard mode only): place the hero exactly */
    if (wizard && (f = getenv("OWHACK_TELEFILE")) != 0) {
        FILE *fp = fopen(f, "r");
        int x, y;

        if (fp) {
            int n = fscanf(fp, "%d %d", &x, &y);

            (void) fclose(fp);
            (void) remove(f);
            if (n == 2 && isok(x, y)) {
                coord cc;

                if (In_overworld)
                    ow_ensure_generated(x, y);
                cc.x = x, cc.y = y;
                if (!goodpos(x, y, &gy.youmonst, 0))
                    (void) enexto(&cc, x, y, gy.youmonst.data);
                teleds(cc.x, cc.y, TELEDS_TELEPORT);
            }
        }
    }
    if (!In_overworld && getenv("OWHACK_MAPDUMP"))
        ow_debug_dump(u.ux, u.uy, 0, 0);
}

/* test aid: a coarse picture of the whole world's biomes (one character per
   8x8 cells), written when OWHACK_WORLDMAP names a file */
void
ow_world_dump(void)
{
    static const char bch[NUM_OW_BIOMES] = {
        '.', 't', 'T', 'M', 'h', '~', ',', '*', ':', 'r', '_', '#', 'x',
        'L', 'z', 'c', ' ', '@'
    };
    const char *fname = getenv("OWHACK_WORLDMAP");
    FILE *fp;
    int x, y, r, k, px, py;
    static char grid[OW_SIZE / 8 + 2][OW_SIZE / 8 + 2];

    if (!fname || !*fname || !svow.inited)
        return;
    for (y = 0; y < OW_SIZE / 8; y++)
        for (x = 0; x < OW_SIZE / 8; x++)
            grid[y][x] = bch[ow_biome_at(x * 8 + 4, y * 8 + 4)];
    for (r = 0; r < svow.nrings; r++)
        for (k = 0; k < svow.rings[r].nportals; k++) {
            ow_portal_pos(&svow.rings[r], k, &px, &py);
            grid[py / 8][px / 8] = 'A' + (svow.rings[r].dnum % 26);
        }
    if (!(fp = fopen(fname, "w")))
        return;
    for (r = 0; r < svow.nrings; r++)
        fprintf(fp, "ring %2d: %c = %s (%d portals)\n", svow.rings[r].ring,
                'A' + (svow.rings[r].dnum % 26),
                ow_portal_dest_name(svow.rings[r].dnum),
                svow.rings[r].nportals);
    fprintf(fp, "barrier ring %d, max ring %d\n", svow.barrier_ring,
            svow.max_ring);
    for (y = 0; y < OW_SIZE / 8; y += 2) { /* half vertical resolution */
        for (x = 0; x < OW_SIZE / 8; x++)
            fputc(grid[y][x], fp);
        fputc('\n', fp);
    }
    fclose(fp);
}
