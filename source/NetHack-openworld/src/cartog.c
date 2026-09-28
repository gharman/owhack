/* NetHack 5.0  cartog.c */
/* Open-world variant: the Cartographer's instruments and talents -- the
   sextant, the surveyor's eye, and the Celestial Sextant's charting. */
/* NetHack may be freely redistributed.  See license for details. */

#include "hack.h"
#include <math.h>

staticfn int compass_bearing(int, int, int, int);
staticfn const char *bearing_name(int);
staticfn int shaky_distance(int);
staticfn int shaky_bearing(int);
staticfn void sighting_report(winid, coordxy, coordxy, boolean, boolean);
staticfn const char *dungeon_title(xint16, char *);
staticfn boolean carrying_celestial_sextant(void);
staticfn void surveyors_eye(void);
staticfn void sense_portals(void);
staticfn int chart_nearby_portals(void);

/* the sixteen points of the compass, clockwise from north */
static const char *const compass16[16] = {
    "north", "north-northeast", "northeast", "east-northeast",
    "east", "east-southeast", "southeast", "south-southeast",
    "south", "south-southwest", "southwest", "west-southwest",
    "west", "west-northwest", "northwest", "north-northwest"
};

/* compass bearing of <x2,y2> as seen from <x1,y1>, in whole degrees
   clockwise from north (north being up on the map) */
staticfn int
compass_bearing(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1, dy = y2 - y1;
    double a;

    if (!dx && !dy)
        return 0;
    a = atan2((double) dx, (double) -dy) * 180.0 / 3.14159265358979;
    return ((int) (a + 360.5)) % 360;
}

/* name of the compass point nearest to 'bearing' */
staticfn const char *
bearing_name(int bearing)
{
    return compass16[((bearing * 2 + 22) / 45) % 16];
}

/* an unsteady hand: off by up to a fifth or so */
staticfn int
shaky_distance(int d)
{
    int err = d / 5 + 2;

    d += rn2(2 * err + 1) - err;
    return max(d, 1);
}

staticfn int
shaky_bearing(int b)
{
    return (b + 360 + rn2(61) - 30) % 360;
}

/* "the Gnomish Mines" and so on, for a dungeon number */
staticfn const char *
dungeon_title(xint16 dnum, char *buf)
{
    if (dnum == quest_dnum && gu.urole.homebase) {
        Sprintf(buf, "the Quest (%s)", gu.urole.homebase);
        return buf;
    }
    Strcpy(buf, ow_portal_dest_name(dnum));
    if (!strncmp(buf, "The ", 4))
        *buf = 't';
    return buf;
}

/*
 * The reading from a sighting taken at overworld location <x,y>: which
 * ring that is, how far and in which direction the center of the world
 * lies, and the nearest portal of each ring of portals that the hero
 * knows about.  'from_branch' means that <x,y> is the portal which the
 * hero will come back out at, rather than where the hero stands.
 */
staticfn void
sighting_report(
    winid win,
    coordxy x, coordxy y,
    boolean exact,
    boolean from_branch)
{
    char buf[BUFSZ], dbuf[BUFSZ];
    int d, b, r, k, px, py, bx, by, nlisted = 0;
    long dd, bestdd;
    int ring = ow_ring_at(x, y);

    Sprintf(buf, "%s ring %d of the world (depth %d)%s.",
            from_branch ? "Its way out lies in" : "You are in", ring, ring,
            ow_in_gehennom(x, y) ? ", in Gehennom" : "");
    putstr(win, 0, buf);
    d = ow_dist(x, y);
    if (d < 2) {
        putstr(win, 0, from_branch
                       ? "That is at the very centre of the world."
                       : "You stand at the very centre of the world.");
    } else {
        b = compass_bearing(x, y, OW_CX, OW_CY);
        if (!exact)
            d = shaky_distance(d), b = shaky_bearing(b);
        Sprintf(buf, "The centre of the world lies %d square%s %s, "
                     "bearing %d (%s).",
                d, plur(d), from_branch ? "from there" : "away", b,
                bearing_name(b));
        putstr(win, 0, buf);
    }

    for (r = 0; r < svow.nrings; r++) {
        const struct ow_ringinfo *ri = &svow.rings[r];

        if (!ow_ring_known(r))
            continue;
        bestdd = -1L, bx = by = 0;
        for (k = 0; k < ri->nportals; k++) {
            ow_ring_portal_pos(r, k, &px, &py);
            dd = (long) (px - x) * (px - x) + (long) (py - y) * (py - y);
            if (bestdd < 0L || dd < bestdd)
                bestdd = dd, bx = px, by = py;
        }
        if (bestdd < 0L)
            continue;
        if (!nlisted++) {
            putstr(win, 0, "");
            putstr(win, 0, from_branch ? "Nearest portals to it:"
                                       : "Nearest portals:");
        }
        d = ow_isqrt(bestdd);
        b = compass_bearing(x, y, bx, by);
        if (!exact && d)
            d = shaky_distance(d), b = shaky_bearing(b);
        if (!d)
            Sprintf(buf, "  %s (ring %d): right here.",
                    dungeon_title(ri->dnum, dbuf), (int) ri->ring);
        else
            Sprintf(buf, "  %s (ring %d): %d square%s, bearing %d (%s).",
                    dungeon_title(ri->dnum, dbuf), (int) ri->ring, d,
                    plur(d), b, bearing_name(b));
        putstr(win, 0, buf);
    }
    if (!nlisted) {
        putstr(win, 0, "");
        putstr(win, 0, "You have not charted any portals yet.");
    }
}

/* apply a sextant (possibly the Celestial Sextant) */
int
use_sextant(struct obj *obj)
{
    boolean celestial = is_art(obj, ART_CELESTIAL_SEXTANT),
            exact = celestial || Role_if(PM_CARTOGRAPHER) || Luck >= 0,
            skyless;
    char buf[BUFSZ], dbuf[BUFSZ];
    coordxy x, y;
    winid win;

    if (!celestial) {
        if (Blind) {
            You_cant("take a sighting while you can't see.");
            return ECMD_OK;
        }
        if (u.uswallow) {
            You_cant("see the sky from in here!");
            return ECMD_OK;
        }
        if (Underwater) {
            You_cant("see the sky from under the %s.", hliquid("water"));
            return ECMD_OK;
        }
        if (In_overworld && ow_under_roof(u.ux, u.uy)) {
            pline("There is %s over your %s; you need a clear view of the"
                  " sky.", an(ceiling(u.ux, u.uy)), body_part(HEAD));
            return ECMD_OK;
        }
    }

    if (!In_overworld && !celestial) {
        /* in a branch: no sky, but the hero can still reckon */
        pline("There is no sky here to take a sighting of.");
        You("reckon that you are on level %d of %s, at depth %d.",
            dunlev(&u.uz), dungeon_title(u.uz.dnum, dbuf), depth(&u.uz));
        return ECMD_TIME;
    }

    skyless = (!In_overworld || u.uswallow || Underwater
               || ow_under_roof(u.ux, u.uy));
    if (celestial && (skyless || Blind))
        pline("%s sights stars that you cannot see.", The(xname(obj)));
    else if (Hallucination)
        You("take a sighting of %s.",
            rn2(2) ? "a passing comet made of cheese"
                   : "the constellation of the Great Grid Bug");
    else if (ow_in_gehennom(u.ux, u.uy))
        You("take a sighting through the smoke of Gehennom.");
    else
        You("take a sighting of the %s.", night() ? "stars" : "sun");
    exercise(A_WIS, TRUE);

    win = create_nhwindow(NHW_MENU);
    if (In_overworld) {
        sighting_report(win, u.ux, u.uy, exact, FALSE);
    } else {
        Sprintf(buf, "You are on level %d of %s, at depth %d.",
                dunlev(&u.uz), dungeon_title(u.uz.dnum, dbuf), depth(&u.uz));
        putstr(win, 0, buf);
        if (ow_branch_origin(&x, &y))
            sighting_report(win, x, y, TRUE, TRUE);
    }
    display_nhwindow(win, TRUE);
    destroy_nhwindow(win);
    return ECMD_TIME;
}

/* is the hero carrying the Celestial Sextant? */
staticfn boolean
carrying_celestial_sextant(void)
{
    struct obj *otmp;

    for (otmp = gi.invent; otmp; otmp = otmp->nobj)
        if (is_art(otmp, ART_CELESTIAL_SEXTANT))
            return TRUE;
    return FALSE;
}

/*
 * The Cartographer's "surveyor's eye": terrain within a few squares of
 * the hero (2 + XL/6) finds its way onto the hero's map as the hero goes
 * by, even where it can't actually be seen (in the dark, round corners,
 * the far side of walls).  Only the lie of the land is mapped; secret
 * doors and passages stay hidden, and remembered objects and traps are
 * left alone.
 */
staticfn void
surveyors_eye(void)
{
    int rad = 2 + u.ulevel / 6, dx, dy;
    coordxy x, y;
    struct rm *lev;

    for (dx = -rad; dx <= rad; dx++)
        for (dy = -rad; dy <= rad; dy++) {
            if (dx * dx + dy * dy > rad * rad + rad)
                continue;
            x = u.ux + dx, y = u.uy + dy;
            if (!isok(x, y) || cansee(x, y))
                continue; /* vision takes care of what's in sight */
            if (In_overworld && !ow_generated(x, y))
                continue;
            lev = &levl[x][y];
            lev->seenv = SVALL;
            magic_map_background(x, y, 0);
            newsym(x, y);
        }
}

/* the Celestial Sextant senses magic portals nearby and marks them on
   the hero's map */
staticfn void
sense_portals(void)
{
    coordxy lx, ly, hx, hy;
    struct trap *t;
    int nfound = 0;

    lvl_effect_bounds(&lx, &ly, &hx, &hy);
    for (t = gf.ftrap; t; t = t->ntrap) {
        if (t->ttyp != MAGIC_PORTAL || t->tx < lx || t->tx > hx
            || t->ty < ly || t->ty > hy)
            continue;
        if (t->tseen && glyph_is_trap(levl[t->tx][t->ty].glyph))
            continue; /* already on the map */
        t->tseen = 1;
        map_trap(t, 0);
        newsym(t->tx, t->ty);
        nfound++;
    }
    if (nfound)
        You("sense the pull of %s.",
            (nfound == 1) ? "a magic portal" : "magic portals");
}

/* called once per player input: the surveyor's eye and portal sense
   act whenever the hero has moved */
void
survey_surroundings(void)
{
    static coordxy lastx = 0, lasty = 0;
    static d_level lastlev = { 0, 0 };

    if (!u.ux || !isok(u.ux, u.uy))
        return;
    if (u.ux == lastx && u.uy == lasty && on_level(&u.uz, &lastlev))
        return;
    lastx = u.ux, lasty = u.uy;
    assign_level(&lastlev, &u.uz);

    if (Role_if(PM_CARTOGRAPHER) && !Blind && !Hallucination && !Underwater
        && !u.uswallow)
        surveyors_eye();
    if (carrying_celestial_sextant())
        sense_portals();
}

/* mark every portal of the rings next to the hero's own (and of the
   hero's own ring) on the map; returns the number of portals marked */
staticfn int
chart_nearby_portals(void)
{
    int ring = ow_ring_at(u.ux, u.uy), r, k, px, py, nmarked = 0;
    struct trap *t;

    for (r = 0; r < svow.nrings; r++) {
        const struct ow_ringinfo *ri = &svow.rings[r];

        if (ri->dnum < 0 || ri->dnum >= svn.n_dgns
            || abs(ri->ring - ring) > 1)
            continue;
        for (k = 0; k < ri->nportals; k++) {
            ow_ring_portal_pos(r, k, &px, &py);
            if (!isok(px, py))
                continue;
            if (ow_generated(px, py)) {
                if ((t = t_at(px, py)) == 0 || t->ttyp != MAGIC_PORTAL)
                    continue;
                t->tseen = 1;
                map_trap(t, 0);
            } else {
                /* not made yet; the portal will be there when it is */
                levl[px][py].glyph
                    = cmap_to_glyph(trap_to_defsym(MAGIC_PORTAL));
            }
            newsym(px, py);
            nmarked++;
        }
    }
    return nmarked;
}

/* #invoke the Celestial Sextant: chart the neighborhood (the whole
   level, in a branch) and, in the open world, the nearby portal rings */
int
invoke_charting(struct obj *obj)
{
    int nmarked;

    if (svl.level.flags.nommap) {
        Your("%s spins as %s blocks the charting!", body_part(HEAD),
             something);
        make_confused(HConfusion + rnd(30), FALSE);
        return ECMD_TIME;
    }
    pline("%s charts %s around you!", The(xname(obj)),
          In_overworld ? "the lands" : "everything");
    notice_mon_off();
    do_mapping();
    notice_mon_on();
    if (In_overworld && (nmarked = chart_nearby_portals()) > 0)
        pline("%s magic portal%s of this ring and the next %s marked on"
              " your map.", (nmarked == 1) ? "The" : "All the",
              plur(nmarked), (nmarked == 1) ? "is" : "are");
    return ECMD_TIME;
}

/*cartog.c*/
