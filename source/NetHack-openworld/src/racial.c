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
            /* a starving vampire drags itself along */
            return (u.uhs == STARVED) ? 7 : 15;
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

/* would polymorphing into mntmp just make the hero a "new man" of its own
   race?  giants and centaurs are only their own race's placeholder form,
   so they can become other giants or centaurs (EvilHack) */
boolean
your_race_form(int mntmp)
{
    if (!ismnum(mntmp))
        return FALSE;
    if (Race_if(PM_GIANT))
        return (mntmp == PM_GIANT);
    if (Race_if(PM_CENTAUR))
        return (mntmp == PM_CENTAUR);
    return your_race(&mons[mntmp]);
}

/* the hero is a ghost in its natural, incorporeal form (polymorphing
   into any other form replaces the ghostly body and its traits) */
boolean
u_ghost(void)
{
    return (!Upolyd && Race_if(PM_GHOST));
}

/* does a physical blow or missile pass partly through a ghost hero's
   insubstantial body (halving its damage)?  silver and blessed weapons,
   and attackers who are themselves incorporeal (ghosts, shades), hurt a
   ghost as much as anyone else */
boolean
u_ghost_passthru(struct monst *magr, struct obj *weapon)
{
    if (!u_ghost())
        return FALSE;
    if (magr && magr != &gy.youmonst && noncorporeal(magr->data))
        return FALSE;
    if (weapon && (weapon->blessed
                   || objects[weapon->otyp].oc_material == SILVER))
        return FALSE;
    return TRUE;
}

/* halve (rounding up) the damage of a physical blow against a ghost hero
   when it passes partly through; see u_ghost_passthru() */
int
u_ghost_dmg(int dmg, struct monst *magr, struct obj *weapon)
{
    if (dmg > 0 && u_ghost_passthru(magr, weapon))
        dmg = (dmg + 1) / 2;
    return dmg;
}

/* set while a draugr's bite is being resolved, so that the victim can rise
   as a zombie if it dies of it */
static boolean racial_bite;

void
set_racial_bite(boolean on)
{
    racial_bite = on;
}

boolean
racial_bite_active(void)
{
    return racial_bite;
}

/* does the hero go hungry the way vampires do (thirst for blood, and
   starvation that debilitates without killing)?  in the natural form or
   polymorphed into a vampire; other forms get hungry normally */
boolean
u_vamp_hunger(void)
{
    return (Race_if(PM_VAMPIRE)
            && (!Upolyd || is_vampire(gy.youmonst.data)));
}

/* once per turn: a starving vampire can hardly hear or see (EvilHack) */
void
vampire_starvation(void)
{
    if (!u_vamp_hunger())
        return;
    if (u.uhs >= FAINTING && (HDeaf & TIMEOUT) < 2L)
        incr_itimeout(&HDeaf, 2L);
    if (u.uhs == STARVED && BlindedTimeout < 2L) {
        boolean was_blind = !!Blind;

        make_blinded(BlindedTimeout + 2L, FALSE);
        if (!was_blind && Blind)
            pline("Your vision fades as your hunger overwhelms you.");
    }
}

/*
 * Armor.
 */

/* would the hero break out of body armor, cloaks and shirts?  giants are
   too big for them and tortles have their shell (EvilHack); centaurs,
   although large, have a humanoid torso and can wear them */
boolean
u_breakarm(void)
{
    if (Upolyd)
        return breakarm(gy.youmonst.data);
    return (Race_if(PM_GIANT) || Race_if(PM_TORTLE));
}

/* would body armor, cloaks and shirts slip off the hero? */
boolean
u_sliparm(void)
{
    return Upolyd ? sliparm(gy.youmonst.data) : FALSE;
}

/* the hero's natural armor class before any worn gear: the current form
   when polymorphed; giants have a thick hide (AC 6) and tortles their
   shell (AC 0), which grows thicker as they grow up (EvilHack) */
int
u_base_ac(void)
{
    int uac = mons[u.umonnum].ac;

    if (!Upolyd) {
        if (Race_if(PM_GIANT))
            uac = 6;
        else if (Race_if(PM_TORTLE))
            uac = 0 - u.ulevel / 3;
    }
    return uac;
}

/* armor class adjustments that depend on the hero's race besides worn
   armor: a tortle hiding in its shell is very hard to damage; the
   shapeshifting doppelganger and werewolf toughen their unarmored skin
   (Slash'EM) */
int
u_race_ac_adjust(void)
{
    int adj = 0;

    if (Hidinshell)
        adj -= 40;
    if ((Race_if(PM_DOPPELGANGER) || Race_if(PM_HUMAN_WEREWOLF)) && !uarm)
        adj -= (u.ulevel / 4) + 1;
    return adj;
}

/* the armor class a worn piece of armor gives the hero; a ghost can hardly
   bear the weight of armor on its insubstantial body, so only half of the
   base protection (rounded down) counts, but enchantment counts fully */
int
u_arm_bonus(struct obj *obj)
{
    int base = objects[obj->otyp].a_ac
               - min((int) greatest_erosion(obj), objects[obj->otyp].a_ac);

    if (u_ghost())
        base /= 2;
    return base + obj->spe;
}

/*
 * Tortles (EvilHack): #monster retreats into the shell, where the tortle
 * is blind, can't move, fight or handle things, but is very hard to hurt
 * (much better armor class and half physical damage) and heals a bit
 * faster.  It can stay inside for up to 200 turns; after emerging it
 * needs 300 to 399 turns before it can hide again.
 */

/* rigid gauntlets or helmets slow down retreating into the shell (and
   cursed ones prevent it) */
staticfn boolean
rigid_armor(struct obj *obj)
{
    int mat = objects[obj->otyp].oc_material;

    return (mat == WOOD || mat == BONE || mat == GLASS || mat == MINERAL
            || mat == GEMSTONE || (mat >= IRON && mat <= MITHRIL));
}

int
toggleshell(void)
{
    boolean was_blind = !!Blind, was_hiding = Hidinshell;

    /* at most 200 turns inside, then 300 to 399 turns before hiding
       again is possible */
    u.uinshell = was_hiding ? -rn1(100, 300) : 200;

    find_ac();
    disp.botl = TRUE;
    if (was_blind != !!Blind)
        toggle_blindness();
    return 1;
}

/* afternmv callback when retreating or emerging took a while */
staticfn int
toggleshell_done(void)
{
    (void) toggleshell();
    return 0;
}

int
doenshelling(void)
{
    int delay = 0;

    if (!Hidinshell && u.uinshell) {
        You_cant("retreat into your shell again so soon.");
        return ECMD_OK;
    } else if (!Hidinshell && Punished) {
        You_cant("retreat into your shell with an iron ball chained to "
                 "your %s!", body_part(LEG));
        return ECMD_OK;
    } else if (uarmg && rigid_armor(uarmg) && uarmg->cursed) {
        Your("cursed %s prevent you from retreating into your shell.",
             gloves_simple_name(uarmg));
        return ECMD_OK;
    } else if (uarmh && rigid_armor(uarmh) && uarmh->cursed) {
        Your("cursed %s prevents you from retreating into your shell.",
             helm_simple_name(uarmh));
        return ECMD_OK;
    }

    /* variable delay when wearing rigid gauntlets or a rigid helmet */
    if (uarmg && rigid_armor(uarmg))
        delay += rn2(3) + 2;
    if (uarmh && rigid_armor(uarmh))
        delay += rn2(3) + 2;

    You("%s%s your shell.", delay ? "begin to " : "",
        Hidinshell ? "emerge from" : "retreat into");

    if (delay) {
        static char shelling_reason[40];

        ga.afternmv = toggleshell_done;
        nomul(-delay);
        if (Hidinshell) {
            gn.nomovemsg = "You finish emerging from your shell.";
            Sprintf(shelling_reason, "emerging from %s shell", uhis());
        } else {
            gn.nomovemsg = "You finish hiding in your shell.";
            Sprintf(shelling_reason, "retreating into %s shell", uhis());
        }
        gm.multi_reason = shelling_reason;
        return ECMD_TIME;
    }
    (void) toggleshell();
    return ECMD_TIME;
}

/* does a hiding tortle's shell turn aside this melee attack?  small and
   medium-sized biters, stingers and mind flayers' tentacles can't get
   through it (EvilHack) */
boolean
shell_blocks(struct monst *mtmp, struct attack *mattk)
{
    if (!Hidinshell)
        return FALSE;
    if (mattk->aatyp == AT_BITE && mtmp->data->msize <= MZ_LARGE) {
        Your("protective shell blocks %s bite!", s_suffix(mon_nam(mtmp)));
        return TRUE;
    }
    if (mattk->aatyp == AT_TENT && is_mind_flayer(mtmp->data)) {
        Your("protective shell blocks %s tentacle attack!",
             s_suffix(mon_nam(mtmp)));
        return TRUE;
    }
    if (mattk->aatyp == AT_STNG) {
        pline("%s stinger glances off of your protective shell!",
              s_suffix(Monnam(mtmp)));
        return TRUE;
    }
    return FALSE;
}

/* once per turn, from race_timeouts() */
staticfn void
shell_timeout(void)
{
    if (Hidinshell) {
        if (--u.uinshell == 1) {
            You("emerge from your shell.");
            (void) toggleshell();
            nomul(0);
        }
    } else if (u.uinshell < 0) {
        u.uinshell++;
    }
}

/* leave the shell at once (polymorph and the like) */
void
leave_shell(void)
{
    if (Hidinshell)
        (void) toggleshell();
}

/* racial timers, once per turn from nh_timeout() */
void
race_timeouts(void)
{
    if (u.uinshell)
        shell_timeout();
    if (u.uvampireshape > 0) {
        if (--u.uvampireshape == 20 && Race_if(PM_VAMPIRE))
            You_feel("your shapechanging ability start to return.");
    }
}

/*
 * Shapeshifting races.
 */

/* the vampire race's #monster shapechange forms (EvilHack) */
static const short vampire_forms[] = {
    PM_VAMPIRE_BAT, PM_FOG_CLOUD, PM_WARG
};

/* is the hero a vampire in one of its shapechange forms?  while
   shapechanged, a vampire's gear melds into the new body instead of
   falling off or breaking (EvilHack) */
boolean
u_vampire_form(void)
{
    int i;

    if (!Upolyd || !Race_if(PM_VAMPIRE))
        return FALSE;
    for (i = 0; i < SIZE(vampire_forms); i++)
        if (u.umonnum == vampire_forms[i])
            return TRUE;
    return FALSE;
}

/* turn into one of the vampire forms (menu choice) */
staticfn void
vampire_shapechange(void)
{
    winid win;
    menu_item *selected = (menu_item *) 0;
    anything any;
    int i, n, mndx, clr = NO_COLOR;
    /* how the hero's alignment has been abused affects how long it takes
       before shapechanging is possible again: 2600 to 2800 turns for a
       spotless record, up to 5600 to 6000 for a badly abused one */
    int abuse = (u.ualign.abuse == 0) ? -1000
                : (u.ualign.abuse < 5) ? 100
                  : (u.ualign.abuse < 15) ? 200
                    : (u.ualign.abuse < 30) ? 500
                      : (u.ualign.abuse < 50) ? 1000 : 2000;
    if (Unchanging) {
        You("fail to transform!");
        return;
    }
    win = create_nhwindow(NHW_MENU);
    start_menu(win, MENU_BEHAVE_STANDARD);
    any = cg.zeroany;
    for (i = 0; i < SIZE(vampire_forms); i++) {
        mndx = vampire_forms[i];
        if (svm.mvitals[mndx].mvflags & G_GENOD)
            continue;
        any.a_int = mndx + 1; /* +1: never 0 */
        add_menu(win, &nul_glyphinfo, &any, 0, 0, ATR_NONE, clr,
                 pmname(&mons[mndx], Ugender), MENU_ITEMFLAGS_NONE);
    }
    end_menu(win, "Pick a form to change into.");
    n = select_menu(win, PICK_ONE, &selected);
    destroy_nhwindow(win);
    if (n <= 0)
        return;
    mndx = selected[0].item.a_int - 1;
    free((genericptr_t) selected);
    /* the cooldown only starts if the transformation took place */
    if (polymon(mndx))
        u.uvampireshape += rn1((u.ualign.abuse == 0) ? 201 : 401,
                               3600 + abuse);
}

/* #monster for a vampire in its natural form or a shapechange form */
staticfn int
dovampshape(void)
{
    if (u.ulevel < 3) {
        You("must first reach experience level three to shapechange.");
    } else if (u_vampire_form()) {
        /* voluntarily reverting early shortens the wait before the next
           shapechange, at the cost of half of the natural form's hit
           points (but never below one) */
        u.uhp -= (u.uhp / 2);
        if (u.uhp < 1)
            u.uhp = 1;
        rehumanize();
        if (u.uvampireshape > 200)
            u.uvampireshape = 200;
        return ECMD_TIME;
    } else if (u.uvampireshape > 0
               && (!wizard
                   || y_n("You can't shapechange so soon.  Override?")
                          != 'y')) {
        You_cant("shapechange so soon.");
    } else if (Stunned || Confusion) {
        You_cant("use shapechange while incapacitated.");
    } else if (u.uhunger < 50) {
        You("are too weak from hunger to shapechange.");
    } else if (ACURR(A_STR) < 4) {
        You("lack the strength to shapechange.");
    } else {
        vampire_shapechange();
        return Upolyd ? ECMD_TIME : ECMD_OK;
    }
    return ECMD_OK;
}

/* the werewolf race changing between @ and beast forms at will */
staticfn void
race_were_change(void)
{
    if (gm.multi >= 0) {
        if (go.occupation)
            stop_occupation();
        else
            nomul(0);
    }
    gw.were_changes++;
    (void) polymon(u.ulycn);
}

/* #youpoly:  polymorph under conscious control (Slash'EM); doppelgangers
   can take any form they know, at a cost in energy of 20 plus five for
   each level of the new form (what energy they lack comes out of their
   nutrition), and return to their own form for free; werewolves change
   between their human and wolf forms for 10 energy once they have
   reached experience level 3 */
#define EN_DOPP 20
#define EN_WERE 10
int
polyatwill(void)
{
    if (Unchanging) {
        pline("You cannot change your form.");
        return ECMD_OK;
    }
    if (Upolyd && Race_if(PM_DOPPELGANGER)) {
        rehumanize();
        return ECMD_TIME;
    }
    if (Race_if(PM_DOPPELGANGER)) {
        if (y_n("Polymorph at will?") != 'y')
            return ECMD_OK;
        if (u.uen < EN_DOPP) {
            You("don't have the energy to polymorph!  You need at least %d.",
                EN_DOPP);
            return ECMD_OK;
        }
        u.uen -= EN_DOPP;
        disp.botl = TRUE;
        if (gm.multi >= 0) {
            if (go.occupation)
                stop_occupation();
            else
                nomul(0);
        }
        polyself(POLY_NOFLAGS);
        if (Upolyd) { /* actually changed */
            u.uen -= 5 * mons[u.umonnum].mlevel;
            if (u.uen < 0) {
                morehungry(-u.uen);
                u.uen = 0;
            }
        }
        return ECMD_TIME;
    } else if (Race_if(PM_HUMAN_WEREWOLF)
               && (!Upolyd || u.umonnum == u.ulycn)) {
        if (y_n("Change form?") != 'y')
            return ECMD_OK;
        if (!ismnum(u.ulycn)) {
            /* very serious */
            You("are no longer a lycanthrope!");
            return ECMD_OK;
        } else if (u.ulevel <= 2) {
            You_cant("invoke the change at will yet.");
            return ECMD_OK;
        } else if (u.uen < EN_WERE) {
            You("don't have the energy to change form!");
            return ECMD_OK;
        }
        /* committed to the change now */
        u.uen -= EN_WERE;
        disp.botl = TRUE;
        if (!Upolyd)
            race_were_change();
        else
            rehumanize();
        return ECMD_TIME;
    }
    pline("You can't polymorph at will%s.",
          (Race_if(PM_HUMAN_WEREWOLF) || Race_if(PM_DOPPELGANGER))
              ? " yet" : "");
    return ECMD_OK;
}
#undef EN_DOPP
#undef EN_WERE

/* doppelgangers remember the monsters they have eaten; returns TRUE if the
   form is familiar enough for a sure transformation */
boolean
dopp_knows_form(int mndx)
{
    return (ismnum(mndx) && svm.mvitals[mndx].eaten > 0);
}

/* the eaten-memory counter */
void
note_eaten_form(int mndx)
{
    if (ismnum(mndx) && svm.mvitals[mndx].eaten < 255)
        svm.mvitals[mndx].eaten++;
}

/* amnesia makes a doppelganger forget some of the forms it has eaten
   (Hack'EM) */
void
forget_eaten_forms(void)
{
    int i;

    if (!Race_if(PM_DOPPELGANGER))
        return;
    for (i = LOW_PM; i < NUMMONS; i++)
        if (svm.mvitals[i].eaten && !rn2(3))
            svm.mvitals[i].eaten = 0;
}

/*
 * Illithids: the psychic blast of #monster (as a polymorphed mind flayer)
 * and the psionic wave spell are blocked by a metal helmet.
 */
boolean
u_psionics_blocked(boolean verbose)
{
    if (uarmh && is_metallic(uarmh)) {
        if (verbose)
            pline_The("metal of your %s blocks your psionic attack.",
                      helm_simple_name(uarmh));
        return TRUE;
    }
    return FALSE;
}

/*
 * #monster in the hero's natural form, for races with a special ability;
 * returns -1 if the race has none (the caller then says so).
 */
int
race_monability(void)
{
    if (Upolyd) {
        if (u_vampire_form())
            return dovampshape();
        return -1;
    }
    switch (Race_switch) {
    case PM_TORTLE:
        return doenshelling();
    case PM_ILLITHID:
        if (u_psionics_blocked(TRUE))
            return ECMD_OK;
        return domindblast();
    case PM_VAMPIRE:
        return dovampshape();
    case PM_DOPPELGANGER:
    case PM_HUMAN_WEREWOLF:
        return polyatwill();
    default:
        break;
    }
    return -1;
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
