/* NetHack: Open World	racial.c */
/* Copyright (c) NetHack: Open World contributors, 2026. */
/* NetHack may be freely redistributed.  See license for details. */

/*
 * Traits and special abilities of the Open World player races:
 *
 *   giant, centaur, illithid, tortle, draugr and vampire (ported from
 *   EvilHack, cross-checked with Hack'EM), werewolf (Slash'EM's
 *   lycanthrope), doppelganger (Slash'EM, Hack'EM) and the ghost.
 *
 * Most racial checks live where the affected game mechanic is; this file
 * collects the helpers they share and the self-contained abilities (the
 * tortle's shell, the vampire's shapechange, polymorphing at will, the
 * ghost's phasing and fearsome presence).
 */

#include "hack.h"

/*
 * Basic racial traits.
 */

/* does the hero count as undead (for holy and unholy water, blessed
   weapons, turn undead, temples and the like)?  draugr, vampires and
   ghosts do in their natural form; any hero does while polymorphed into
   an undead form */
boolean
u_undead(void)
{
    if (Upolyd)
        return (is_undead(gy.youmonst.data)
                || is_vampshifter(&gy.youmonst));
    return (Race_if(PM_DRAUGR) || Race_if(PM_VAMPIRE) || Race_if(PM_GHOST));
}

/* the hero's physical size: the current form when polymorphed; giants
   are huge and centaurs and tortles large in their natural form (every
   other race is as big as its role's human-sized monster) */
int
u_size(void)
{
    if (!Upolyd && (Race_if(PM_GIANT) || Race_if(PM_CENTAUR)
                    || Race_if(PM_TORTLE)))
        return (int) mons[gu.urace.mnum].msize;
    return (int) gy.youmonst.data->msize;
}

/* the hero's body weight, analogous to u_size() */
unsigned
u_bodyweight(void)
{
    if (!Upolyd && (Race_if(PM_GIANT) || Race_if(PM_CENTAUR)
                    || Race_if(PM_TORTLE)))
        return mons[gu.urace.mnum].cwt;
    return gy.youmonst.data->cwt;
}

/* the hero's base movement rate: the form's speed when polymorphed,
   else the race's (EvilHack: giants, tortles and draugr are slow,
   vampires quick and centaurs very fast) */
int
u_race_speed(void)
{
    if (!Upolyd) {
        switch (Race_switch) {
        case PM_GIANT:
        case PM_TORTLE:
        case PM_DRAUGR:
            return 10;
        case PM_VAMPIRE:
            return 15;
        case PM_CENTAUR:
            return 18;
        default:
            break;
        }
    }
    return gy.youmonst.data->mmove;
}

/* does the hero, in the natural form of a race that ignores it, have no
   use for boots? (centaur hooves and tortle feet are the wrong shape) */
boolean
u_race_no_boots(void)
{
    return (!Upolyd && (Race_if(PM_CENTAUR) || Race_if(PM_TORTLE)));
}

/* the hero is a giant, by race or current form */
boolean
u_giant(void)
{
    return Upolyd ? is_giant(gy.youmonst.data) : Race_if(PM_GIANT);
}

/* the hero is a centaur, by race or current form */
boolean
u_centaur(void)
{
    return Upolyd ? (gy.youmonst.data->mlet == S_CENTAUR)
                  : Race_if(PM_CENTAUR);
}

/* the hero can pick up, carry and throw boulders (giant race or a
   rock-throwing form) */
boolean
u_throws_rocks(void)
{
    return Upolyd ? throws_rocks(gy.youmonst.data) : Race_if(PM_GIANT);
}

/* the hero is an illithid, by race or current (mind flayer) form */
boolean
u_illithid(void)
{
    return Upolyd ? is_mind_flayer(gy.youmonst.data)
                  : Race_if(PM_ILLITHID);
}

/* the hero is a vampire, by race or current form */
boolean
u_vampire(void)
{
    return Upolyd ? is_vampire(gy.youmonst.data) : Race_if(PM_VAMPIRE);
}

/* the hero is a draugr (or a zombie, when polymorphed) */
boolean
u_draugr(void)
{
    return Upolyd ? (gy.youmonst.data->mlet == S_ZOMBIE
                     && (gy.youmonst.data->mhflags & MH_DRAUGR) != 0)
                  : Race_if(PM_DRAUGR);
}

/*
 * Intrinsics that belong to the race's body rather than to its nature:
 * the flight of illithids and vampires (experience level 12) and of
 * ghosts, and the ghost's lack of breath, only work in the natural form.
 * Called whenever the hero's form changes (set_uasmon()) and after level
 * changes (adjabil(), which gives the gain and loss messages); when
 * 'check_fall' is set, losing flight makes the hero land on whatever is
 * underneath.
 */
void
race_form_props(boolean check_fall)
{
    boolean flies = FALSE, breathless = FALSE,
            was_flying = !!Flying;

    if (!Upolyd) {
        if (Race_if(PM_GHOST))
            flies = breathless = TRUE;
        else if ((Race_if(PM_ILLITHID) || Race_if(PM_VAMPIRE))
                 && u.ulevel >= 12)
            flies = TRUE;
    }
    if (flies)
        HFlying |= FROMRACE;
    else
        HFlying &= ~FROMRACE;
    if (breathless)
        HMagical_breathing |= FROMRACE;
    else
        HMagical_breathing &= ~FROMRACE;

    if (!program_state.restoring && u.ulevel > 0) {
        float_vs_flight();
        if (check_fall && was_flying && !Flying)
            spoteffects(TRUE);
    }
}

/*racial.c*/
