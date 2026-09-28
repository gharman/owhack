/* NetHack 5.0  openworld.h */
/* Open-world variant: overworld, viewport and ring-depth declarations. */
/* NetHack may be freely redistributed.  See license for details. */

#ifndef OPENWORLD_H
#define OPENWORLD_H

/*
 * The overworld.
 *
 * The first level of dungeon #0 is a single, very large, lazily generated
 * outdoor map.  Its center holds the three high altars where the hero
 * starts.  Difficulty ("depth") is a function of the distance from the
 * center: the map is divided into concentric rings OW_RING_WIDTH wide and
 * the ring number is the depth used for level difficulty, monster and
 * object generation, and so on.  Special levels and branch dungeons are
 * reached through rings of evenly spaced magic portals at their depth.
 */
#define OW_SIZE        1700               /* overworld is OW_SIZE square */
#define OW_CX          (OW_SIZE / 2)      /* center column */
#define OW_CY          (OW_SIZE / 2)      /* center row */
#define OW_RING_WIDTH  16                 /* map cells per unit of depth */
#define OW_CHUNK       32                 /* generation chunk size */
#define OW_NCHUNKS     (OW_SIZE / OW_CHUNK + 1)
#define OW_EDGE        6                  /* impassable border width */
/* chunks within this many cells of the hero are generated */
#define OW_GEN_RADIUS  96
/* monsters farther than this (per axis) from the hero are dormant */
#define OW_ACTIVE_RX   60
#define OW_ACTIVE_RY   30
/* area treated as "the level" for level-wide effects in the overworld */
#define OW_LOCAL_RX    60
#define OW_LOCAL_RY    30
/* vision is only computed within this distance of the viewer */
#define OW_VISION_RX   60
#define OW_VISION_RY   30

#define OW_MAXPORTALS  512  /* portal return records */

/* kinds of overworld terrain zones ("biomes") */
enum ow_biome {
    OWB_MEADOW = 0,
    OWB_FOREST,
    OWB_DEEPFOREST,
    OWB_MOUNTAIN,
    OWB_HILLS,
    OWB_LAKE,
    OWB_SWAMP,
    OWB_TUNDRA,
    OWB_DESERT,
    OWB_RUINS,
    OWB_BARRENS,     /* land just inside the Gehennom barrier */
    OWB_BARRIER,     /* impassable mountain wall around Gehennom */
    OWB_HELLPLAIN,   /* Gehennom: scorched plain */
    OWB_HELLLAVA,    /* Gehennom: lava fields */
    OWB_HELLMAZE,    /* Gehennom: obsidian labyrinths */
    OWB_HELLCAVE,    /* Gehennom: caverns */
    OWB_EDGE,        /* the edge of the world */
    OWB_PLAZA,       /* the sacred plaza at the center */
    NUM_OW_BIOMES
};

/* a record of which overworld portal the hero used to enter a branch */
struct ow_portalrec {
    xint16 dnum;     /* dungeon entered */
    coordxy x, y;    /* overworld location of the portal used */
};

/* per-branch-dungeon ring assignment */
struct ow_ringinfo {
    xint16 dnum;     /* dungeon reached by this ring of portals */
    xint16 ring;     /* depth (ring number) where its portals are */
    xint16 nportals; /* number of portals around the ring */
    xint16 phase;    /* angular offset of the first portal, 0..359 */
};

#define OW_MAXRINGS 64  /* rings of branch portals */

/* game-state for the overworld; saved with the game */
struct ow_state {
    unsigned long seed;          /* terrain seed */
    boolean inited;
    xint16 barrier_ring;         /* ring holding the Gehennom barrier */
    xint16 hell_ring;            /* first Gehennom ring (barrier+1) */
    xint16 max_ring;             /* outermost usable ring */
    xint16 deepest_ring;         /* deepest ring the hero has reached */
    xint16 nrings;
    struct ow_ringinfo rings[OW_MAXRINGS];
    xint16 nportrec;
    struct ow_portalrec portrec[OW_MAXPORTALS];
    unsigned char genmap[OW_NCHUNKS][OW_NCHUNKS]; /* chunk generated? */
    xint16 last_ring_seen;       /* for "you enter ring N" messages */
    xint16 last_zone_msg;        /* last biome announced */
    coordxy altar_x[3], altar_y[3]; /* the three high altars */
    aligntyp altar_align[3];
    boolean qcall_done;          /* quest call on reaching quest ring */
    coordxy lt_x, lt_y;          /* level teleport destination */
    boolean lt_exact;            /* land exactly at lt_x,lt_y */
    long spare[8];
};

/* how the hero is arriving in the overworld (ow_arrive()) */
enum ow_arrivals {
    OWARR_NEWGAME = 0,
    OWARR_STAIRS,     /* climbing out of a branch */
    OWARR_PORTAL,     /* through a magic portal */
    OWARR_LEVTELE,    /* level teleport, falling, rising, etc */
};

/* viewport (the rectangle of the map shown in the map window) */
struct viewport_state {
    int x0, y0;         /* map coordinates of the viewport's top-left */
    int w, h;           /* viewport size in map cells */
    int focusx, focusy; /* explicit focus (e.g. getpos cursor), 0 = hero */
    boolean valid;      /* origin established */
};

extern struct ow_state svow;        /* saved overworld state */
extern struct viewport_state gvp;   /* viewport */
extern int nh_vp_cols, nh_vp_rows;  /* map window size from window port */
extern int ow_gen_depth;            /* depth override while generating */
extern int ow_gen_x, ow_gen_y;      /* location being generated */

#define Is_overworld(lev) ((lev)->dnum == 0 && (lev)->dlevel == 1)
#define In_overworld      Is_overworld(&u.uz)

#endif /* OPENWORLD_H */
