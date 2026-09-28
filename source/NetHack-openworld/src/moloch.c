/* NetHack 5.0  moloch.c */
/* Copyright (c) Tomsod and the EvilHack development team, 2019-2025. */
/* NetHack may be freely redistributed.  See license for details. */

/*
 * The Infidel role (created by Tomsod for EvilHack): a cultist of Moloch,
 * who is entrusted by the Cult with the Amulet of Yendor from the start and
 * must return it to Moloch's Sanctum, where Moloch imbues the Idol of
 * Moloch with the Amulet's power; the Idol must then be invoked on the high
 * altar of the weakest of the gods of heaven to overthrow that god.
 *
 * This file has the parts of the role that don't naturally belong in one
 * of the core files: the permutation of the gods, Moloch's demand for
 * regular sacrifices, the demonic form of an Infidel crowned Emissary of
 * Moloch (wings and barbed tail), and the Idol of Moloch's #invoke power.
 */

#include "hack.h"

staticfn void idol_imbued_msg(struct obj *);

/* The pseudo-race of an Infidel who has been crowned by Moloch.  It isn't
   available at the start of the game; role_init() and gcrownu() switch
   gu.urace to it.  Mental faculties are not changed by demonization, so
   the Int and Wis maximums of the original race are kept. */
const struct Race race_demon = {
    "demon",
    "demonic",
    "demonkind",
    "Dem",
    { 0, 0 },
    PM_DEMON,
    NON_PM,
    NON_PM,
    MH_DEMON | ROLE_MALE | ROLE_FEMALE,
    MH_DEMON,
    MH_DEMON,
    MH_HUMAN | MH_ELF | MH_DWARF | MH_GNOME | MH_ORC | MH_GIANT
        | MH_CENTAUR | MH_ILLITHID | MH_TORTLE,
    /*    Str     Int Wis Dex Con Cha */
    { 3, 3, 3, 3, 3, 3 },
    { STR18(100), 18, 18, 20, 20, 18 },
    /* Init   Lower  Higher */
    { 8, 0, 0, 8, 4, 0 }, /* Hit points */
    { 4, 0, 6, 0, 6, 0 }  /* Energy */
};

/* switch the hero's race to the demonic one, keeping the mental
   maximums of the original race */
void
set_demon_race(void)
{
    xint16 maxint = gu.urace.attrmax[A_INT],
           maxwis = gu.urace.attrmax[A_WIS];

    if (gu.urace.mnum == PM_DEMON)
        return;
    gu.urace = race_demon;
    gu.urace.attrmax[A_INT] = maxint;
    gu.urace.attrmax[A_WIS] = maxwis;
}

/* Return an alignment from a (lawful, neutral, chaotic) permutation chosen
   at random at the start of the game; only relevant to Infidels:
   inf_align(1) is the god whose high altar the imbued Idol of Moloch must
   be invoked on to win, while inf_align(2) and inf_align(3) are the gods
   the quest leader and the high priest of the Sanctum warn against. */
aligntyp
inf_align(int num) /* 1..3 */
{
    aligntyp first, other;

    first = (aligntyp) (u.uinf_aligns % 3 - 1);
    if (num <= 1)
        return first;
    other = (aligntyp) ((u.uinf_aligns + num) % 2);
    if (other <= first)
        other--;
    return other;
}

/* can the hero's god hear a prayer?  Moloch dwells deep below, and can't
   hear his worshippers outside Gehennom most of the time, unless they carry
   the Idol of Moloch */
boolean
moloch_hears_prayer(void)
{
    if (u.ualign.type != A_NONE || Inhell)
        return TRUE;
    if (Role_if(PM_INFIDEL) && u.uhave.questart)
        return TRUE;
    return (boolean) !rn2(5);
}

/* Moloch demands regular sacrifices; called once per turn */
void
moloch_demands(void)
{
    if (u.umoloch_due > svm.moves)
        return;
    if (u.umoloch_due == svm.moves
        && (u.ualign.type == A_NONE || u.ualignbase[A_CURRENT] == A_NONE)) {
        You_feel("%s urge to perform a sacrifice.",
                 (u.ualign.type == A_NONE) ? "an" : "a faint");
        stop_occupation();
    }
    if (u.ualign.type == A_NONE
        && rn2((int) min(svm.moves - u.umoloch_due + 1000L, 100000L))
               >= 1000) {
        if (!rn2(100) && u.ualign.record > -99) {
            adjalign(-1);
            /* give our infidel some feedback every once in a while */
            if (!rn2(5))
                You_feel("your favor with %s starting to slip.", u_gname());
        }
        if (u.ualign.record < -10 && !rn2(u.ugangr + 1)
            && rn2(-u.ualign.record + 90) >= 100) {
            const char *angry = (char *) 0;

            u.ugangr++;
            /* avoid repetitive messages */
            switch (u.ugangr) {
            case 1:
                angry = "";
                break;
            case 4:
                angry = "very ";
                break;
            case 7:
                angry = "extremely ";
                break;
            }
            if (angry) {
                You_feel("that %s is %sangry at your lack of offerings.",
                         u_gname(), angry);
                stop_occupation();
            }
        }
    }
}

/* a sacrifice of the given value was made to Moloch */
void
moloch_offering(int value)
{
    long new_due = svm.moves + (long) value * 500L;

    if (u.umoloch_due < new_due)
        u.umoloch_due = new_due;
}

/* Infidels can't rest or heal without the Amulet of Yendor until Moloch
   has imbued the Idol of Moloch with its power */
boolean
infidel_no_amulet(void)
{
    return (boolean) (u.ualign.type == A_NONE && Role_if(PM_INFIDEL)
                      && !u.uhave.amulet && !u.uidol_imbued);
}

/* An Infidel is crowned the Emissary of Moloch: wings sprout from their
   back and they grow a barbed tail (called from gcrownu()) */
void
infidel_demonize(void)
{
    if (Upolyd)
        rehumanize(); /* return to original form -- not a demon yet */
    /* lose ALL old racial abilities */
    adjabil(u.ulevel, 0);
    set_demon_race();
    /* gain demonic resistances and abilities */
    adjabil(0, u.ulevel);
    /* resistances: not shock resistance because that can be gained by
       leveling up, and not cold resistance because demons and cold
       typically don't mix */
    HSleep_resistance |= FROMOUTSIDE;
    pline1("Wings sprout from your back and you grow a barbed tail!");
    set_uasmon();
    check_wings(TRUE);
    newsym(u.ux, u.uy);
    retouch_equipment(2); /* silver */
    monstseesu(M_SEEN_FIRE | M_SEEN_POISON | M_SEEN_SLEEP);
}

/* A demonic hero's big wings: flight is impossible while they are folded
   under hard body armor (EvilHack) */
void
check_wings(boolean silent) /* we assume a wardrobe change if false */
{
    static unsigned last_worn_armor = 0;
    boolean old_flying = Flying;

    BFlying &= ~W_ARM;
    if (Upolyd || !Race_if(PM_DEMON))
        return;

    if (!uarm) {
        if (!silent && Flying)
            You("spread your wings%s.", old_flying ? "" : " and take flight");
    } else if (!is_metallic(uarm) && objects[uarm->otyp].oc_material != MINERAL
               && objects[uarm->otyp].oc_material != GLASS) {
        if (!silent && uarm->o_id != last_worn_armor)
            Your("%s seems to have holes for wings.", simpleonames(uarm));
    } else {
        BFlying |= W_ARM;
        if (!silent)
            You("fold your wings under your %s.", suit_simple_name(uarm));
    }
    last_worn_armor = uarm ? uarm->o_id : 0;

    if (Flying != old_flying) {
        disp.botl = TRUE;
        if (!silent && !Flying && old_flying)
            float_vs_flight();
    }
}

/* a crowned Infidel lashes out with a barbed, venomous tail in addition to
   their normal melee attacks; returns FALSE if the target died */
boolean
demon_tail_sting(struct monst *mon)
{
    struct attack sting;
    int tmp, armorpenalty, attknum = 0, dieroll;
    boolean mhit;

    if (Upolyd || !Race_if(PM_DEMON) || DEADMONSTER(mon))
        return TRUE;
    /* don't sting things that would be deadly to sting */
    if ((touch_petrifies(mon->data) && !Stone_resistance)
        || noncorporeal(mon->data))
        return TRUE;

    sting.aatyp = AT_STNG;
    sting.adtyp = AD_DRST;
    sting.damn = 2;
    sting.damd = 4;
    tmp = find_roll_to_hit(mon, AT_STNG, (struct obj *) 0, &attknum,
                           &armorpenalty);
    dieroll = rnd(20);
    mhit = (tmp > dieroll || u.uswallow);
    if (!mhit) {
        if (canspotmon(mon))
            You("miss %s with your tail.", mon_nam(mon));
        wakeup(mon, TRUE);
        return TRUE;
    }
    You("sting %s with your barbed tail.", mon_nam(mon));
    /* damageum() handles the venom (AD_DRST) along with the damage */
    return (boolean) !(damageum(mon, &sting, 0) & M_ATTK_DEF_DIED);
}

/* the imbued Idol confers the Amulet's power on its bearer */
boolean
idol_is_imbued(struct obj *obj)
{
    return (boolean) (obj && obj->oartifact == ART_IDOL_OF_MOLOCH
                      && u.uidol_imbued);
}

staticfn void
idol_imbued_msg(struct obj *idol)
{
    You_feel("strange energies envelop %s.", the(xname(idol)));
}

/* Moloch imbues the Idol of Moloch with the power of the Amulet of Yendor
   (Infidel offering the Amulet on Moloch's high altar in the Sanctum,
   or invoking the Idol there while carrying the Amulet) */
void
imbue_idol(struct obj *idol)
{
    idol_imbued_msg(idol);
    if (!u.uidol_imbued) {
        u.uidol_imbued = TRUE;
        record_achievement(ACH_AMUL);
        livelog_printf(LL_ACHIEVE, "imbued %s", artiname(ART_IDOL_OF_MOLOCH));
    }
    if (carried(idol))
        u.uhave.amulet = 1;
    update_inventory();
}

/*moloch.c*/
