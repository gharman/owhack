/* NetHack 5.0	tech.c */
/* Original code by Warren Cheung (Slash'EM; basis: spell.c, attrib.c)  */
/* Hack'EM and SlashTHEM additions; adapted for NetHack: Open World      */
/* Copyright (c) M. Stephenson 1988                                      */
/* NetHack may be freely redistributed.  See license for details.        */

/*
 * Techniques.
 *
 * A hero learns techniques from their role and race tables as they gain
 * experience levels, and loses them again if drained below the level at
 * which they were learned (except those learned at level 1).  A few are
 * learned from outside sources (disarm, from weapon skill).  #technique
 * lists them and performs one.  Using a technique starts a timeout; some
 * techniques stay active ("in use") for a while.
 *
 * The role and race tables are keyed by the role's and race's filecode,
 * so roles and races can be added without touching the monster list.
 * To add a technique: add its id at the end of enum tech_id (tech.h), its
 * name to tech_names[], an entry in the techeffects() switch, and put it
 * in the tables.
 */

#include "hack.h"
#include <math.h>

staticfn const struct innate_tech *role_tech(void);
staticfn const struct innate_tech *race_tech(void);
staticfn int get_tech_no(int);
staticfn boolean techs_unlettered(void);
staticfn boolean gettech(int *);
staticfn boolean dotechmenu(int, int *);
staticfn const char *tech_status(int);
staticfn int techeffects(int);
staticfn void tech_end_msg(int);
staticfn boolean tech_damage_mon(struct monst *, int);
staticfn boolean race_is(const char *);
staticfn const char *dir_name(int, int);
staticfn const char *the_dest(const char *);
staticfn int tech_dist(int, int);
staticfn int tech_occupation(void);
staticfn int practice_occ(void);
staticfn int tinker_occ(void);
staticfn int draw_energy_occ(void);
staticfn int ma_break_occ(void);
staticfn int tinker_newtyp(int);
staticfn boolean tinker_upgrade(struct obj *);
staticfn boolean can_practice(int);
staticfn int practice_weapon(void);
staticfn boolean monk_hands_free(void);
staticfn int blitz_input(void);
staticfn void doblitzlist(int);
staticfn int blitz_chi_strike(void);
staticfn int blitz_e_fist(void);
staticfn int blitz_pummel(void);
staticfn int blitz_g_slam(void);
staticfn int blitz_uppercut(void);
staticfn int blitz_dash(void);
staticfn int blitz_power_surge(void);
staticfn int blitz_spirit_bomb(void);
staticfn struct monst *tech_target(void);
staticfn int tech_research(int);
staticfn int tech_surgery(int);
staticfn int tech_healhands(int);
staticfn int tech_kiii(int);
staticfn int tech_vanish(int);
staticfn int tech_critstrike(int);
staticfn int tech_cutthroat(int);
staticfn int tech_blessing(void);
staticfn int tech_curse(void);
staticfn int tech_eviscerate(int);
staticfn int tech_berserk(int);
staticfn int tech_icearmor(int);
staticfn int tech_reinforce(void);
staticfn int tech_flurry(int);
staticfn int tech_appraisal(void);
staticfn int tech_practice(void);
staticfn int tech_primalroar(int);
staticfn int tech_liquidleap(int);
staticfn int tech_raisezombies(void);
staticfn int tech_whistleundead(void);
staticfn int revive_ok(struct obj *);
staticfn struct obj *revive_corpse_pick(void);
staticfn int tech_revive(int);
staticfn int tech_tinker(int);
staticfn int tech_rage(int);
staticfn int tech_drawenergy(void);
staticfn int tech_chiheal(int);
staticfn int tech_disarm(int);
staticfn int tech_dazzle(int);
staticfn int tech_blitz(int);
staticfn int tech_souleater(int);
staticfn int tech_jedijump(int);
staticfn int tech_telekinesis(void);
staticfn int tech_spirittempest(int);
staticfn int tech_forcepush(int);
staticfn int tech_pickpocket(int);
staticfn int tech_tumble(int);
staticfn int tech_sunder(int);
staticfn int tech_bloodmagic(int);
staticfn int tech_breakrock(void);
staticfn int tech_survey(void);
staticfn int tech_triangulate(void);
staticfn int tech_waymark(int *);
staticfn int tech_haunt(void);
staticfn int tech_slipfree(void);
staticfn int tech_mindblast(int);
staticfn int tech_holdbreath(int);
staticfn int tech_chargesaber(void);
staticfn int charge_saber_occ(void);
staticfn boolean tele_trap_handle(struct trap *);
staticfn boolean waymark_spot_ok(coordxy, coordxy);
staticfn boolean waymark_teleport(void);
staticfn boolean find_way_out(coordxy *, coordxy *, const char **);

/*
 * Keep the names shorter than 25 characters or the menu will look bad.
 * Indexed by technique id.
 */
static const char *const tech_names[NUM_TECHS] = {
    "no technique",
    "berserk",
    "kiii",
    "research",
    "surgery",
    "reinforce memory",
    "missile flurry",
    "weapon practice",
    "eviscerate",
    "healing hands",
    "turn undead",
    "vanish",
    "cutthroat",
    "blessing",
    "elemental fist",
    "primal roar",
    "liquid leap",
    "critical strike",
    "raise zombies",
    "revivification",
    "tinker",
    "rage eruption",
    "chi strike",
    "draw energy",
    "chi healing",
    "disarm",
    "dazzle",
    "chained blitz",
    "pummel",
    "ground slam",
    "air dash",
    "power surge",
    "spirit bomb",
    "appraisal",
    "souleater",
    "jedi jump",
    "telekinesis",
    "whistle undead",
    "spirit tempest",
    "force push",
    "curse",
    "pickpocket",
    "tumble",
    "sunder",
    "blood magic",
    "break rock",
    "uppercut",
    "ice armor",
    "survey",
    "triangulate",
    "waymark",
    "haunt",
    "slip free",
    "mind blast",
    "hold breath",
    "charge saber",
};

/*
 * Role techniques, keyed by the role's filecode.
 * The vanilla roles and Nec Fla Ice Inf Jed Pir follow Hack'EM; Car and
 * Con are this variant's own.  A chaotic Knight is a Dark Knight (as in
 * Hack'EM and SlashTHEM) and uses drk_tech instead.
 */
static const struct innate_tech
    arc_tech[] = { { 1, T_APPRAISAL, 1 },
                   { 3, T_RESEARCH, 1 },
                   { 0, 0, 0 } },
    bar_tech[] = { { 1, T_BERSERK, 1 },
                   { 5, T_RAGE, 1 },
                   { 0, 0, 0 } },
    car_tech[] = { { 1, T_SURVEY, 1 },
                   { 3, T_TRIANGULATE, 1 },
                   { 8, T_WAYMARK, 1 },
                   { 0, 0, 0 } },
    cav_tech[] = { { 1, T_PRIMAL_ROAR, 1 },
                   { 0, 0, 0 } },
    con_tech[] = { { 1, T_PICKPOCKET, 1 },
                   { 5, T_SLIP_FREE, 1 },
                   { 0, 0, 0 } },
    fla_tech[] = { { 1, T_REINFORCE, 1 },
                   { 3, T_POWER_SURGE, 1 },
                   { 5, T_DRAW_ENERGY, 1 },
                   { 0, 0, 0 } },
    hea_tech[] = { { 1, T_SURGERY, 1 },
                   { 0, 0, 0 } },
    ice_tech[] = { { 1, T_REINFORCE, 1 },
                   { 3, T_ICEARMOR, 1 },
                   { 5, T_DRAW_ENERGY, 1 },
                   { 12, T_POWER_SURGE, 1 },
                   { 0, 0, 0 } },
    inf_tech[] = { { 1, T_CURSE, 1 },
                   { 1, T_REINFORCE, 1 },
                   { 5, T_DRAW_ENERGY, 1 },
                   { 0, 0, 0 } },
    jed_tech[] = { { 1, T_JEDI_JUMP, 1 },
                   { 5, T_CHARGE_SABER, 1 },
                   { 8, T_TELEKINESIS, 1 },
                   { 14, T_FORCE_PUSH, 1 },
                   { 0, 0, 0 } },
    kni_tech[] = { { 1, T_TURN_UNDEAD, 1 },
                   { 1, T_HEAL_HANDS, 1 },
                   { 0, 0, 0 } },
    drk_tech[] = { { 1, T_SOULEATER, 1 },
                   { 0, 0, 0 } },
    mon_tech[] = { { 1, T_PUMMEL, 1 },
                   { 1, T_DASH, 1 },
                   { 1, T_BLITZ, 1 },
                   { 1, T_BREAK_ROCK, 1 },
                   { 2, T_CHI_STRIKE, 1 },
                   { 4, T_CHI_HEALING, 1 },
                   { 6, T_E_FIST, 1 },
                   { 8, T_DRAW_ENERGY, 1 },
                   { 10, T_G_SLAM, 1 },
                   { 13, T_UPPERCUT, 1 },
                   { 17, T_SPIRIT_BOMB, 1 },
                   { 20, T_POWER_SURGE, 1 },
                   { 0, 0, 0 } },
    nec_tech[] = { { 1, T_REINFORCE, 1 },
                   { 2, T_WHISTLE_UNDEAD, 1 },
                   { 3, T_RAISE_ZOMBIES, 1 },
                   { 5, T_BLOOD_MAGIC, 1 },
                   { 8, T_SOULEATER, 1 },
                   { 10, T_POWER_SURGE, 1 },
                   { 14, T_REVIVE, 1 },
                   { 17, T_SPIRIT_TEMPEST, 1 },
                   { 0, 0, 0 } },
    pir_tech[] = { { 1, T_TUMBLE, 1 },
                   { 5, T_SUNDER, 1 },
                   { 0, 0, 0 } },
    pri_tech[] = { { 1, T_TURN_UNDEAD, 1 },
                   { 1, T_BLESSING, 1 },
                   { 10, T_HEAL_HANDS, 1 },
                   { 30, T_REVIVE, 1 },
                   { 0, 0, 0 } },
    ran_tech[] = { { 1, T_FLURRY, 1 },
                   { 0, 0, 0 } },
    rog_tech[] = { { 1, T_PICKPOCKET, 1 },
                   { 1, T_CRIT_STRIKE, 1 },
                   { 15, T_CUTTHROAT, 1 },
                   { 0, 0, 0 } },
    sam_tech[] = { { 1, T_KIII, 1 },
                   { 0, 0, 0 } },
    val_tech[] = { { 1, T_PRACTICE, 1 },
                   { 0, 0, 0 } },
    wiz_tech[] = { { 1, T_REINFORCE, 1 },
                   { 3, T_DRAW_ENERGY, 1 },
                   { 5, T_POWER_SURGE, 1 },
                   { 0, 0, 0 } },
    /*
     * Race techniques, keyed by the race's filecode.
     * Dwa Gno Vam Dop follow Hack'EM, Wer follows Slash'EM's lycanthrope;
     * Gia follows SlashTHEM's ogre; Cen Ill Trt Dra Gho are this
     * variant's own.  Humans, elves and orcs have none (as in Slash'EM).
     */
    dwa_tech[] = { { 1, T_RAGE, 1 },
                   { 0, 0, 0 } },
    gno_tech[] = { { 1, T_VANISH, 1 },
                   { 7, T_TINKER, 1 },
                   { 0, 0, 0 } },
    gia_tech[] = { { 1, T_PRIMAL_ROAR, 1 },
                   { 10, T_BERSERK, 1 },
                   { 0, 0, 0 } },
    cen_tech[] = { { 5, T_FLURRY, 1 },
                   { 0, 0, 0 } },
    ill_tech[] = { { 1, T_MIND_BLAST, 1 },
                   { 0, 0, 0 } },
    trt_tech[] = { { 1, T_HOLD_BREATH, 1 },
                   { 0, 0, 0 } },
    dra_tech[] = { { 1, T_BERSERK, 1 },
                   { 0, 0, 0 } },
    vam_tech[] = { { 1, T_DAZZLE, 1 },
                   { 0, 0, 0 } },
    wer_tech[] = { { 1, T_EVISCERATE, 1 },
                   { 10, T_BERSERK, 1 },
                   { 0, 0, 0 } },
    dop_tech[] = { { 1, T_LIQUID_LEAP, 1 },
                   { 0, 0, 0 } },
    gho_tech[] = { { 1, T_HAUNT, 1 },
                   { 0, 0, 0 } };

static const struct techtable {
    const char *filecode;
    const struct innate_tech *techs;
} role_techtab[] = {
    { "Arc", arc_tech }, { "Bar", bar_tech }, { "Car", car_tech },
    { "Cav", cav_tech }, { "Con", con_tech }, { "Fla", fla_tech },
    { "Hea", hea_tech }, { "Ice", ice_tech }, { "Inf", inf_tech },
    { "Jed", jed_tech }, { "Kni", kni_tech }, { "Mon", mon_tech },
    { "Nec", nec_tech }, { "Pir", pir_tech }, { "Pri", pri_tech },
    { "Ran", ran_tech }, { "Rog", rog_tech }, { "Sam", sam_tech },
    { "Val", val_tech }, { "Wiz", wiz_tech },
    { (const char *) 0, (const struct innate_tech *) 0 }
}, race_techtab[] = {
    { "Dwa", dwa_tech }, { "Gno", gno_tech }, { "Gia", gia_tech },
    { "Cen", cen_tech }, { "Ill", ill_tech }, { "Trt", trt_tech },
    { "Dra", dra_tech }, { "Vam", vam_tech }, { "Wer", wer_tech },
    { "Dop", dop_tech }, { "Gho", gho_tech },
    { (const char *) 0, (const struct innate_tech *) 0 }
};

/* zap types as in zap.c */
#define TECH_ZT_ACID (AD_ACID - 1)
#define TECH_ZT_SPELL_MM (10 + AD_MAGM - 1) /* spell of magic missile */

/* direct access to the hero's technique slots */
#define techid(i) (u.tech_list[i].t_id)
#define techt_inuse(i) (u.tech_list[i].t_inuse)
#define techtout(i) (u.tech_list[i].t_tout)
#define techlev(i) (u.ulevel - u.tech_list[i].t_lev)
#define techname(i) (tech_names[techid(i)])

/* state of multi-turn technique occupations (only one at a time) */
static int tech_delay;          /* turns left, counting up to 0 */
static int tech_occ_id;         /* which technique is being performed */
static coordxy tech_occ_x, tech_occ_y; /* break rock: target */

staticfn const struct innate_tech *
role_tech(void)
{
    const struct techtable *tt;

    if (!gu.urole.filecode)
        return (const struct innate_tech *) 0;
    if (!strcmp(gu.urole.filecode, "Kni")
        && u.ualignbase[A_ORIGINAL] == A_CHAOTIC)
        return drk_tech;
    for (tt = role_techtab; tt->filecode; tt++)
        if (!strcmp(tt->filecode, gu.urole.filecode))
            return tt->techs;
    return (const struct innate_tech *) 0;
}

staticfn const struct innate_tech *
race_tech(void)
{
    const struct techtable *tt;

    if (!gu.urace.filecode)
        return (const struct innate_tech *) 0;
    for (tt = race_techtab; tt->filecode; tt++)
        if (!strcmp(tt->filecode, gu.urace.filecode))
            return tt->techs;
    return (const struct innate_tech *) 0;
}

staticfn boolean
race_is(const char *filecode)
{
    return (boolean) (gu.urace.filecode
                      && !strcmp(gu.urace.filecode, filecode));
}

/* slot holding technique 'tech', or -1 */
staticfn int
get_tech_no(int tech)
{
    int i;

    for (i = 0; i < MAXTECH; i++)
        if (techid(i) == tech)
            return i;
    return -1;
}

/* does the hero know technique 'tech'? */
boolean
tech_known(short tech)
{
    return (boolean) (tech != NO_TECH && get_tech_no(tech) >= 0);
}

/* 0 if technique 'tech_id' isn't active, otherwise turns left + 1
   (the technique ends when this counts down to 1) */
int
tech_inuse(int tech_id)
{
    int i;

    if (tech_id < 1 || tech_id >= NUM_TECHS) {
        impossible("invalid tech: %d", tech_id);
        return 0;
    }
    if ((i = get_tech_no(tech_id)) < 0)
        return 0;
    return techt_inuse(i);
}

/* the level of technique 'tech_id', or 0 if not known */
int
tech_level(int tech_id)
{
    int i = get_tech_no(tech_id);

    return (i < 0) ? 0 : techlev(i);
}

/* lengthen an active technique */
void
extend_tech_time(int tech_id, int t)
{
    int i = get_tech_no(tech_id);

    if (i >= 0 && techt_inuse(i))
        techt_inuse(i) += t;
}

/* stop an active technique prematurely, undoing any lingering bonuses */
void
aborttech(int tech_id)
{
    int i = get_tech_no(tech_id);

    if (i < 0 || !techt_inuse(i))
        return;
    switch (tech_id) {
    case T_RAGE:
        u.uhpmax -= techt_inuse(i) - 1;
        if (u.uhpmax < 1)
            u.uhpmax = 1;
        u.uhp -= techt_inuse(i) - 1;
        if (u.uhp < 1)
            u.uhp = 1;
        disp.botl = TRUE;
        break;
    case T_POWER_SURGE:
        u.uenmax -= techt_inuse(i) - 1;
        if (u.uenmax < 0)
            u.uenmax = 0;
        u.uen -= techt_inuse(i) - 1;
        if (u.uen < 0)
            u.uen = 0;
        disp.botl = TRUE;
        break;
    default:
        break;
    }
    techt_inuse(i) = 0;
    if (tech_id == T_ICEARMOR)
        find_ac();
}

/*
 * Learn (tlevel > 0) or forget (tlevel < 0) technique 'tech' from source
 * 'mask' (FROMEXPER: role, FROMRACE: race, FROMOUTSIDE: anything else).
 * 'tlevel' is the level the technique starts at.
 */
void
learntech(short tech, long mask, int tlevel)
{
    int i;
    const struct innate_tech *tp;

    i = get_tech_no(tech);
    if (tlevel > 0) {
        boolean newtech = FALSE;

        if (i < 0) {
            i = get_tech_no(NO_TECH);
            if (i < 0) {
                impossible("No room for new technique?");
                return;
            }
            newtech = TRUE;
        }
        tlevel = u.ulevel ? u.ulevel - tlevel : 0;
        if (newtech) {
            techid(i) = tech;
            u.tech_list[i].t_lev = (xint16) tlevel;
            techt_inuse(i) = 0;
            u.tech_list[i].t_intrinsic = 0L;
            techtout(i) = 0; /* can be used immediately */
        } else if (u.tech_list[i].t_intrinsic & mask) {
            impossible("Tech already known.");
            return;
        }
        if (mask == FROMOUTSIDE) {
            u.tech_list[i].t_intrinsic &= ~OUTSIDE_LEVEL;
            u.tech_list[i].t_intrinsic |= (tlevel & OUTSIDE_LEVEL);
        }
        if (tlevel < u.tech_list[i].t_lev)
            u.tech_list[i].t_lev = (xint16) tlevel;
        u.tech_list[i].t_intrinsic |= mask;
    } else if (tlevel < 0) {
        if (i < 0 || !(u.tech_list[i].t_intrinsic & mask)) {
            impossible("Tech not known.");
            return;
        }
        u.tech_list[i].t_intrinsic &= ~mask;
        if (!(u.tech_list[i].t_intrinsic & INTRINSIC)) {
            if (techt_inuse(i))
                aborttech(tech);
            techid(i) = NO_TECH;
            u.tech_list[i].t_intrinsic = 0L;
            techtout(i) = 0;
            return;
        }
        /* re-calculate the lowest t_lev from the remaining sources */
        tlevel = -1;
        if (u.tech_list[i].t_intrinsic & FROMOUTSIDE)
            tlevel = (int) (u.tech_list[i].t_intrinsic & OUTSIDE_LEVEL);
        if ((u.tech_list[i].t_intrinsic & FROMEXPER)
            && (tp = role_tech()) != 0) {
            for (; tp->tech_id; tp++)
                if (tp->tech_id == tech)
                    break;
            if (tp->tech_id
                && (tlevel < 0 || tp->ulevel - tp->tech_lev < tlevel))
                tlevel = tp->ulevel - tp->tech_lev;
        }
        if ((u.tech_list[i].t_intrinsic & FROMRACE)
            && (tp = race_tech()) != 0) {
            for (; tp->tech_id; tp++)
                if (tp->tech_id == tech)
                    break;
            if (tp->tech_id
                && (tlevel < 0 || tp->ulevel - tp->tech_lev < tlevel))
                tlevel = tp->ulevel - tp->tech_lev;
        }
        if (tlevel >= 0)
            u.tech_list[i].t_lev = (xint16) tlevel;
    } else {
        impossible("Invalid Tech Level!");
    }
}

/*
 * The hero's experience level went from 'oldlevel' to 'newlevel':
 * learn or forget role and race techniques.  Called with oldlevel 0 for
 * a new character, once role, race and alignment are known.  Techniques
 * learned at level 1 are never lost.
 */
void
adjtech(int oldlevel, int newlevel)
{
    const struct innate_tech *tp;
    int pass, i;
    long mask;

    for (pass = 0; pass < 2; pass++) {
        tp = pass ? race_tech() : role_tech();
        mask = pass ? FROMRACE : FROMEXPER;
        if (!tp)
            continue;
        for (; tp->tech_id; tp++) {
            i = get_tech_no(tp->tech_id);
            if (oldlevel < tp->ulevel && newlevel >= tp->ulevel) {
                if (i >= 0 && (u.tech_list[i].t_intrinsic & mask))
                    continue;
                if (i < 0 && tp->ulevel != 1 && oldlevel > 0)
                    You("learn how to perform %s!",
                        tech_names[tp->tech_id]);
                learntech(tp->tech_id, mask, tp->tech_lev);
            } else if (oldlevel >= tp->ulevel && newlevel < tp->ulevel
                       && tp->ulevel != 1) {
                if (i < 0 || !(u.tech_list[i].t_intrinsic & mask))
                    continue;
                learntech(tp->tech_id, mask, -1);
                if (!tech_known(tp->tech_id))
                    You("lose the ability to perform %s!",
                        tech_names[tp->tech_id]);
            }
        }
    }
    /* automated testing (wizard mode only): start knowing everything */
    if (!oldlevel && wizard && getenv("OWHACK_ALLTECH")) {
        int t;

        for (t = 1; t < NUM_TECHS; t++)
            if (!tech_known((short) t))
                learntech((short) t, FROMOUTSIDE, 1);
    }
}

/*
 * Weapon skill has been advanced: Skilled in a melee weapon teaches the
 * disarm technique (Slash'EM, Hack'EM).
 */
staticfn boolean disarm_skill(int);

staticfn boolean
disarm_skill(int skill)
{
    return (boolean) (skill >= P_FIRST_WEAPON && skill <= P_LAST_WEAPON
                      && skill != P_BOW && skill != P_SLING
                      && skill != P_CROSSBOW && skill != P_DART
                      && skill != P_SHURIKEN && skill != P_BOOMERANG);
}

void
tech_skill_advanced(int skill)
{
    if (disarm_skill(skill) && P_SKILL(skill) >= P_SKILLED
        && !tech_known(T_DISARM)) {
        learntech(T_DISARM, FROMOUTSIDE, 1);
        You("learn how to perform disarm!");
    }
}

/* weapon skills have been lost; disarm needs Skilled in some weapon */
void
tech_skills_lost(void)
{
    int skill;

    if (!tech_known(T_DISARM)
        || !(u.tech_list[get_tech_no(T_DISARM)].t_intrinsic & FROMOUTSIDE))
        return;
    for (skill = P_FIRST_WEAPON; skill <= P_LAST_WEAPON; skill++)
        if (disarm_skill(skill) && P_SKILL(skill) >= P_SKILLED)
            return;
    learntech(T_DISARM, FROMOUTSIDE, -1);
    if (!tech_known(T_DISARM))
        You("lose the ability to perform disarm!");
}

/* ------------------------------------------------------------------ */
/* the #technique command and menus                                    */
/* ------------------------------------------------------------------ */

staticfn const char *
tech_status(int i)
{
    int tlevel = techlev(i);

    return techt_inuse(i) ? "Active"
           : (tlevel <= 0) ? "Beyond recall"
             : !techtout(i) ? "Prepared"
               : (techtout(i) > 100) ? "Not Ready"
                 : "Soon";
}

/* menu letter of technique slot i (letters are assigned in slot order);
   only the first 52 slots have one (only wizard mode can know more
   techniques than that) */
#define techlet(i) \
    ((char) (((i) < 26) ? ('a' + (i)) : ((i) < 52) ? ('A' + (i) - 26) : 0))

/* are technique slots beyond the lettered ones in use? */
staticfn boolean
techs_unlettered(void)
{
    int i;

    for (i = 52; i < MAXTECH; i++)
        if (techid(i) != NO_TECH)
            return TRUE;
    return FALSE;
}

/*
 * Choose a technique: TRUE with the slot in *tech_no if one was picked.
 */
staticfn boolean
gettech(int *tech_no)
{
    int i, ntechs, idx, retry_limit;
    char ilet, lets[BUFSZ], qbuf[QBUFSZ];
    struct _cmd_queue cq, *cmdq;

    for (ntechs = i = 0; i < MAXTECH; i++)
        if (techid(i) != NO_TECH)
            ntechs++;
    if (!ntechs) {
        You("don't know any techniques right now.");
        return FALSE;
    }

    /* repeating the command (^A) reuses the technique chosen last time */
    if ((cmdq = cmdq_pop()) != 0) {
        cq = *cmdq;
        free(cmdq);
        if (cq.typ != CMDQ_KEY)
            return FALSE;
        ilet = cq.key;
        idx = (ilet >= 'a' && ilet <= 'z') ? ilet - 'a'
              : (ilet >= 'A' && ilet <= 'Z') ? ilet - 'A' + 26 : -1;
        if (idx < 0 || idx >= MAXTECH || techid(idx) == NO_TECH)
            return FALSE;
        *tech_no = idx;
        return TRUE;
    }

    if (flags.menu_style == MENU_TRADITIONAL && !techs_unlettered()) {
        /* letters follow the slots, which can have gaps */
        for (idx = 0, i = 0; i < MAXTECH && i < 52; i++)
            if (techid(i) != NO_TECH)
                lets[idx++] = techlet(i);
        lets[idx] = '\0';

        Sprintf(qbuf, "Perform which technique? [%s *?]", lets);
        for (retry_limit = 0;; ++retry_limit) {
            if (retry_limit == 10) {
                pline("That's enough tries.");
                return FALSE;
            }
            ilet = yn_function(qbuf, (char *) 0, '\0', TRUE);
            if (ilet == '*' || ilet == '?')
                break; /* use menu mode */
            if (strchr(quitchars, ilet)) {
                pline1(Never_mind);
                return FALSE;
            }
            idx = (ilet >= 'a' && ilet <= 'z') ? ilet - 'a'
                  : (ilet >= 'A' && ilet <= 'Z') ? ilet - 'A' + 26 : -1;
            if (idx >= 0 && idx < MAXTECH && techid(idx) != NO_TECH) {
                *tech_no = idx;
                return TRUE;
            }
            You("don't know that technique.");
        }
    }
    return dotechmenu(PICK_ONE, tech_no);
}

/* how: PICK_ONE to choose one, PICK_NONE to just list them;
   tech_no is -1 when writing the dumplog */
staticfn boolean
dotechmenu(int how, int *tech_no)
{
    winid tmpwin;
    int i, n, len, longest, techs_useable, tlevel;
    char buf[BUFSZ];
    const char *prefix;
    menu_item *selected;
    anything any;
    boolean dumping = (tech_no == (int *) 0),
            autolet = techs_unlettered(); /* let the menu pick letters */

    tmpwin = create_nhwindow(NHW_MENU);
    start_menu(tmpwin, MENU_BEHAVE_STANDARD);
    any = cg.zeroany;

    techs_useable = 0;
    for (longest = 4, i = 0; i < MAXTECH; i++) {
        if (techid(i) == NO_TECH)
            continue;
        if ((len = (int) strlen(techname(i))) > longest)
            longest = len;
    }
    if (!iflags.menu_tab_sep)
        Sprintf(buf, "%s%-*s Level   Status%s", dumping ? "" : "    ",
                longest, "Name", wizard ? "        Source Timeout" : "");
    else
        Sprintf(buf, "Name\tLevel\tStatus%s",
                wizard ? "\tSource\tTimeout" : "");
    add_menu_heading(tmpwin, buf);

    for (i = 0; i < MAXTECH; i++) {
        if (techid(i) == NO_TECH)
            continue;
        tlevel = techlev(i);
        any = cg.zeroany;
        if (tlevel > 0 && (!techtout(i) || wizard)) {
            /* ready to use (wizard mode can override the timeout) */
            techs_useable++;
            prefix = "";
            any.a_int = i + 1;
        } else {
            prefix = "    ";
        }
        if (dumping)
            prefix = "";
        if (!iflags.menu_tab_sep)
            Sprintf(buf, wizard ? "%s%-*s %5d   %-13s" : "%s%-*s %5d   %s",
                    prefix, longest, techname(i), tlevel, tech_status(i));
        else
            Sprintf(buf, "%s%s\t%d\t%s", prefix, techname(i), tlevel,
                    tech_status(i));
        if (wizard)
            Sprintf(eos(buf), "%c%c%c%c   %7d",
                    iflags.menu_tab_sep ? '\t' : ' ',
                    (u.tech_list[i].t_intrinsic & FROMEXPER) ? 'X' : '-',
                    (u.tech_list[i].t_intrinsic & FROMRACE) ? 'R' : '-',
                    (u.tech_list[i].t_intrinsic & FROMOUTSIDE) ? 'O' : '-',
                    techtout(i));
        add_menu(tmpwin, &nul_glyphinfo, &any,
                 (any.a_int && !autolet) ? techlet(i) : 0, 0, ATR_NONE,
                 NO_COLOR, buf,
                 MENU_ITEMFLAGS_NONE);
    }
    if (!techs_useable)
        how = PICK_NONE;
    end_menu(tmpwin, dumping ? ""
                     : (how == PICK_ONE) ? "Choose a technique"
                       : "Currently known techniques");

    n = select_menu(tmpwin, how, &selected);
    destroy_nhwindow(tmpwin);
    if (n > 0) {
        int selection = selected[0].item.a_int - 1;

        free((genericptr_t) selected);
        if (selection < 0 || dumping)
            return FALSE;
        *tech_no = selection;
        return TRUE;
    }
    return FALSE;
}

/* the #technique command */
int
dotech(void)
{
    int tech_no, res;

    if (!gettech(&tech_no))
        return ECMD_OK;
    if (techlet(tech_no) && !techs_unlettered())
        cmdq_add_key(CQ_REPEAT, techlet(tech_no));
    res = techeffects(tech_no);
    return res ? ECMD_TIME : ECMD_OK;
}

/* for the dumplog */
void
show_techniques(void)
{
    int i;

    for (i = 0; i < MAXTECH; i++)
        if (techid(i) != NO_TECH)
            break;
    if (i == MAXTECH) {
        pline("You didn't know any techniques.");
        pline("%s", "");
        return;
    }
    pline("Techniques:");
    (void) dotechmenu(PICK_NONE, (int *) 0);
}

/* for enlightenment: describe the n-th known technique in buf;
   FALSE when there are no more */
boolean
tech_describe(int n, char *buf, int final)
{
    int i, tlevel;
    const char *st;

    for (i = 0; i < MAXTECH; i++) {
        if (techid(i) == NO_TECH)
            continue;
        if (n-- > 0)
            continue;
        tlevel = techlev(i);
        if (techt_inuse(i))
            st = "active";
        else if (tlevel <= 0)
            st = "beyond recall";
        else if (!techtout(i))
            st = "prepared";
        else if (techtout(i) > 100)
            st = "not ready for a while";
        else
            st = "ready soon";
        Sprintf(buf, " You %s the %s technique (level %d, %s)",
                final ? "knew" : "know", techname(i), tlevel, st);
        return TRUE;
    }
    return FALSE;
}

/* the #wiztechnique command: learn or forget any technique */
int
dowiztech(void)
{
    winid win;
    anything any;
    menu_item *pick_list = (menu_item *) 0;
    int i, n, t, slot;
    char buf[BUFSZ];

    win = create_nhwindow(NHW_MENU);
    start_menu(win, MENU_BEHAVE_STANDARD);
    any = cg.zeroany;
    any.a_int = -1;
    add_menu(win, &nul_glyphinfo, &any, '*', 0, ATR_NONE, NO_COLOR,
             "Reset all technique timeouts", MENU_ITEMFLAGS_NONE);
    add_menu_heading(win, "Known techniques are forgotten, others learned:");
    for (t = 1; t < NUM_TECHS; t++) {
        slot = get_tech_no(t);
        Sprintf(buf, "%-20s%s", tech_names[t],
                (slot >= 0) ? " (known)" : "");
        any = cg.zeroany;
        any.a_int = t;
        add_menu(win, &nul_glyphinfo, &any, 0, 0, ATR_NONE, NO_COLOR, buf,
                 MENU_ITEMFLAGS_NONE);
    }
    end_menu(win, "Learn or forget which techniques?");
    n = select_menu(win, PICK_ANY, &pick_list);
    destroy_nhwindow(win);
    for (i = 0; i < n; i++) {
        t = pick_list[i].item.a_int;
        if (t == -1) {
            for (slot = 0; slot < MAXTECH; slot++)
                techtout(slot) = 0;
            pline("All technique timeouts reset.");
            continue;
        }
        slot = get_tech_no(t);
        if (slot >= 0) {
            if (techt_inuse(slot))
                aborttech(t);
            techid(slot) = NO_TECH;
            u.tech_list[slot].t_intrinsic = 0L;
            techtout(slot) = 0;
            You("forget how to perform %s.", tech_names[t]);
        } else {
            learntech((short) t, FROMOUTSIDE, 1);
            if (tech_known((short) t))
                You("learn how to perform %s!", tech_names[t]);
        }
    }
    if (pick_list)
        free((genericptr_t) pick_list);
    return ECMD_OK;
}

/* ------------------------------------------------------------------ */
/* timeouts                                                            */
/* ------------------------------------------------------------------ */

staticfn void
tech_end_msg(int i)
{
    switch (techid(i)) {
    case T_EVISCERATE:
        You("retract your claws.");
        gu.unweapon = TRUE; /* bare hands now, so new msg for next attack */
        break;
    case T_BLOOD_MAGIC:
        pline_The("darkness leaves your heart.");
        break;
    case T_BERSERK:
        pline_The("red haze in your mind clears.");
        break;
    case T_ICEARMOR:
        Your("icy armor melts away.");
        find_ac();
        break;
    case T_KIII:
        You("calm down.");
        break;
    case T_FLURRY:
        You("relax.");
        break;
    case T_E_FIST:
        You_feel("the power dissipate.");
        break;
    case T_RAGE:
        Your("anger cools.");
        break;
    case T_POWER_SURGE:
        pline_The("awesome power within you fades.");
        break;
    case T_CHI_STRIKE:
        You_feel("the power in your %s dissipate.",
                 makeplural(body_part(HAND)));
        break;
    case T_CHI_HEALING:
        You_feel("the healing power dissipate.");
        break;
    case T_SOULEATER:
        if (uwep)
            pline_The("dark flames surrounding %s dissipate.", yname(uwep));
        break;
    case T_PRIMAL_ROAR:
        You_feel("your primal fury subside.");
        break;
    case T_HOLD_BREATH:
        if (Underwater && !Amphibious && !Swimming
            && !cant_drown(gy.youmonst.data)) {
            You("can't hold your breath any longer!");
            (void) drown();
        } else {
            You("let out your breath.");
        }
        break;
    default:
        break;
    }
}

/* called once per turn from nh_timeout() */
void
tech_timeout(void)
{
    int i;

    for (i = 0; i < MAXTECH; i++) {
        if (techid(i) == NO_TECH)
            continue;
        if (techt_inuse(i)) {
            if (!--techt_inuse(i)) {
                tech_end_msg(i);
            } else {
                switch (techid(i)) {
                case T_RAGE:
                    /* bleed, but don't kill */
                    if (u.uhpmax > 1)
                        u.uhpmax--;
                    if (u.uhp > 1)
                        u.uhp--;
                    disp.botl = TRUE;
                    break;
                case T_POWER_SURGE:
                    /* bleed off power; zero power is not fatal */
                    if (u.uenmax > 1)
                        u.uenmax--;
                    if (u.uen > 0)
                        u.uen--;
                    disp.botl = TRUE;
                    break;
                case T_HOLD_BREATH:
                    if (techt_inuse(i) == 11 && Underwater)
                        You("are running short of breath!");
                    break;
                default:
                    break;
                }
            }
        }
        if (techtout(i) > 0 && !--techtout(i) && techlev(i) > 0) {
            pline("Your %s technique is ready to be used!", techname(i));
            stop_occupation();
        }
    }
}

/* ------------------------------------------------------------------ */
/* performing a technique                                              */
/* ------------------------------------------------------------------ */

staticfn int
techeffects(int tech_no)
{
    int t_timeout = 0, res = 0, tid = techid(tech_no);
    boolean exact = FALSE; /* t_timeout is not scaled by technique level */

    if (techt_inuse(tech_no)) {
        pline("This technique is already active!");
        return 0;
    }
    if (techlev(tech_no) <= 0) {
        You("can't remember how to perform %s!", techname(tech_no));
        return 0;
    }
    if (techtout(tech_no)) {
        You("have to wait %s before using your technique again.",
            (techtout(tech_no) > 100) ? "for a while" : "a little longer");
        if (!wizard || y_n("Use technique anyway?") != 'y')
            return 0;
    }

    switch (tid) {
    /* --- blitz techniques --- */
    case T_PUMMEL:
        if (!getdir((char *) 0))
            return 0;
        res = blitz_pummel();
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_BLITZ:
        res = tech_blitz(tech_no);
        if (res)
            t_timeout = rn1(1000, 1500);
        break;
    case T_E_FIST:
        res = blitz_e_fist();
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_CHI_STRIKE:
        res = blitz_chi_strike();
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_G_SLAM:
        if (!getdir((char *) 0))
            return 0;
        res = blitz_g_slam();
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_UPPERCUT:
        if (!getdir((char *) 0))
            return 0;
        res = blitz_uppercut();
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_DASH:
        if (!getdir((char *) 0))
            return 0;
        res = blitz_dash();
        if (res)
            t_timeout = rn1(100, 100);
        break;
    case T_POWER_SURGE:
        res = blitz_power_surge();
        if (res)
            t_timeout = rn1(1000, 1500);
        break;
    case T_SPIRIT_BOMB:
        if (!getdir((char *) 0))
            return 0;
        res = blitz_spirit_bomb();
        if (res)
            t_timeout = rn1(500, 1000);
        break;

    /* --- regular techniques --- */
    case T_CHI_HEALING:
        res = tech_chiheal(tech_no);
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_RESEARCH:
        res = tech_research(tech_no);
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_EVISCERATE:
        res = tech_eviscerate(tech_no);
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_BERSERK:
        res = tech_berserk(tech_no);
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_ICEARMOR:
        res = tech_icearmor(tech_no);
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_REINFORCE:
        res = tech_reinforce();
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_FLURRY:
        res = tech_flurry(tech_no);
        if (res)
            t_timeout = rn1(500, 500);
        break;
    case T_APPRAISAL:
        res = tech_appraisal();
        if (res)
            t_timeout = rn1(100, 100);
        break;
    case T_PRACTICE:
        res = tech_practice();
        if (res)
            t_timeout = rn1(100, 100);
        break;
    case T_SURGERY:
        res = tech_surgery(tech_no);
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_HEAL_HANDS:
        res = tech_healhands(tech_no);
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_KIII:
        res = tech_kiii(tech_no);
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_TURN_UNDEAD:
        /* the same action as #turn, which has no timeout */
        res = (doturn() & ECMD_TIME) ? 1 : 0;
        break;
    case T_VANISH:
        res = tech_vanish(tech_no);
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_CRIT_STRIKE:
        res = tech_critstrike(tech_no);
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_CUTTHROAT:
        res = tech_cutthroat(tech_no);
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_BLESSING:
        res = tech_blessing();
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_CURSE:
        res = tech_curse();
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_PRIMAL_ROAR:
        res = tech_primalroar(tech_no);
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_LIQUID_LEAP:
        res = tech_liquidleap(tech_no);
        if (res)
            t_timeout = rn1(500, 500);
        break;
    case T_RAISE_ZOMBIES:
        res = tech_raisezombies();
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_WHISTLE_UNDEAD:
        res = tech_whistleundead();
        /* no timeout: a nice perk for necromancers */
        break;
    case T_REVIVE:
        res = tech_revive(tech_no);
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_TINKER:
        res = tech_tinker(tech_no);
        /* no timeout: this costs time */
        break;
    case T_RAGE:
        res = tech_rage(tech_no);
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_DRAW_ENERGY:
        res = tech_drawenergy();
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_PICKPOCKET:
        res = tech_pickpocket(tech_no);
        /* no timeout: the cost is failure or angry victims */
        break;
    case T_DISARM:
        res = tech_disarm(tech_no);
        /* no timeout: the cost is failure or angry victims */
        break;
    case T_DAZZLE:
        res = tech_dazzle(tech_no);
        if (res)
            t_timeout = rn1(100, 100);
        break;
    case T_SPIRIT_TEMPEST:
        res = tech_spirittempest(tech_no);
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_JEDI_JUMP:
        res = tech_jedijump(tech_no);
        if (res)
            t_timeout = rn1(100, 100);
        break;
    case T_SOULEATER:
        res = tech_souleater(tech_no);
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_TELEKINESIS:
        res = tech_telekinesis();
        if (res)
            t_timeout = rn1(100, 100);
        break;
    case T_FORCE_PUSH:
        res = tech_forcepush(tech_no);
        if (res)
            t_timeout = rn1(500, 500);
        break;
    case T_TUMBLE:
        res = tech_tumble(tech_no);
        if (res)
            t_timeout = rn1(100, 100);
        break;
    case T_SUNDER:
        res = tech_sunder(tech_no);
        if (res)
            t_timeout = rn1(500, 500);
        break;
    case T_BLOOD_MAGIC:
        res = tech_bloodmagic(tech_no);
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    case T_BREAK_ROCK:
        res = tech_breakrock();
        /* no timeout: this takes time and training */
        break;
    case T_SURVEY:
        res = tech_survey();
        if (res)
            t_timeout = max(50, 250 - 5 * u.ulevel), exact = TRUE;
        break;
    case T_TRIANGULATE:
        res = tech_triangulate();
        if (res)
            t_timeout = 300, exact = TRUE;
        break;
    case T_WAYMARK: {
        int teleported = 0;

        res = tech_waymark(&teleported);
        if (res && teleported)
            t_timeout = max(200, 1000 - 20 * u.ulevel), exact = TRUE;
        break;
    }
    case T_HAUNT:
        res = tech_haunt();
        if (res)
            t_timeout = max(50, 200 - 3 * u.ulevel), exact = TRUE;
        break;
    case T_SLIP_FREE:
        res = tech_slipfree();
        if (res)
            t_timeout = rn1(500, 500);
        break;
    case T_MIND_BLAST:
        res = tech_mindblast(tech_no);
        if (res)
            t_timeout = rn1(500, 500);
        break;
    case T_HOLD_BREATH:
        res = tech_holdbreath(tech_no);
        if (res)
            t_timeout = rn1(500, 500);
        break;
    case T_CHARGE_SABER:
        res = tech_chargesaber();
        if (res)
            t_timeout = rn1(500, 1000);
        break;
    default:
        impossible("No such technique effect (%d)", tid);
        return 0;
    }

    if (res) {
        if (!u.uconduct.techuse++)
            livelog_printf(LL_CONDUCT,
                           "performed a technique for the first time - %s",
                           tech_names[tid]);
        /* the technique might have been lost meanwhile (level drain) */
        if (techid(tech_no) == tid) {
            if (!exact)
                t_timeout = (t_timeout * (100 - techlev(tech_no))) / 100;
            if (t_timeout > 0)
                techtout(tech_no) = t_timeout;
        }
    }
    return res;
}

/* ------------------------------------------------------------------ */
/* utilities                                                           */
/* ------------------------------------------------------------------ */

/* damage a monster; TRUE if it died */
staticfn boolean
tech_damage_mon(struct monst *mtmp, int amount)
{
    if (DEADMONSTER(mtmp))
        return TRUE;
    if (amount < 1)
        return FALSE;
    mtmp->mhp -= amount;
    if (DEADMONSTER(mtmp)) {
        killed(mtmp);
        return (boolean) DEADMONSTER(mtmp);
    }
    return FALSE;
}

/* the monster in direction u.dx,u.dy (the engulfer when engulfed) */
staticfn struct monst *
tech_target(void)
{
    if (u.uswallow)
        return u.ustuck;
    if (!isok(u.ux + u.dx, u.uy + u.dy))
        return (struct monst *) 0;
    return m_at(u.ux + u.dx, u.uy + u.dy);
}

/* rounded straight-line distance */
staticfn int
tech_dist(int dx, int dy)
{
    long d2 = (long) dx * dx + (long) dy * dy, r = 0;

    while ((r + 1) * (r + 1) <= d2)
        r++;
    if (d2 - r * r > r) /* round to nearest */
        r++;
    return (int) r;
}

/* a destination's name in mid-sentence: "The Oracle" -> "the Oracle" */
staticfn const char *
the_dest(const char *name)
{
    static char buf[BUFSZ];

    Strcpy(buf, name);
    if (!strncmp(buf, "The ", 4))
        buf[0] = 't';
    return buf;
}

/* compass direction of an offset; screen north is up */
staticfn const char *
dir_name(int dx, int dy)
{
    static const char *const names[8] = {
        "east", "northeast", "north", "northwest",
        "west", "southwest", "south", "southeast"
    };
    double ang;
    int sector;

    if (!dx && !dy)
        return "right here";
    ang = atan2((double) -dy, (double) dx) * 180.0 / 3.14159265358979;
    if (ang < 0.0)
        ang += 360.0;
    sector = ((int) (ang + 22.5) / 45) % 8;
    return names[sector];
}

/* bare hands free for martial arts (blitz techniques) */
staticfn boolean
monk_hands_free(void)
{
    if (uwep || (u.twoweap && uswapwep)) {
        You_cant("do this while wielding a weapon!");
        return FALSE;
    } else if (uarms) {
        You_cant("do this while holding a shield!");
        return FALSE;
    }
    return TRUE;
}

/* ------------------------------------------------------------------ */
/* technique occupations (multi-turn actions)                          */
/* ------------------------------------------------------------------ */

staticfn int
tech_occupation(void)
{
    switch (tech_occ_id) {
    case T_PRACTICE:
        return practice_occ();
    case T_TINKER:
        return tinker_occ();
    case T_DRAW_ENERGY:
        return draw_energy_occ();
    case T_BREAK_ROCK:
        return ma_break_occ();
    case T_CHARGE_SABER:
        return charge_saber_occ();
    default:
        return 0;
    }
}

/* weapon practice (Slash'EM) */
staticfn boolean
can_practice(int skill)
{
    return (boolean) (skill != P_NONE && !P_RESTRICTED(skill)
                      && P_SKILL(skill) < P_MAX_SKILL(skill)
                      && u.skills_advanced < P_SKILL_LIMIT);
}

staticfn int
practice_weapon(void)
{
    int skill = weapon_type(uwep);

    if (can_practice(skill)
        || (wizard && y_n("Skill at normal max.  Practice?") == 'y')) {
        if (uwep)
            You("start practicing intensely with %s.", doname(uwep));
        else
            You("start practicing intensely with your %s %s.",
                uarmg ? "gloved" : "bare", makeplural(body_part(HAND)));
        tech_delay = -10;
        tech_occ_id = T_PRACTICE;
        set_occupation(tech_occupation, "practicing", 0);
    } else if (skill != P_NONE && P_SKILL(skill) >= P_MAX_SKILL(skill)) {
        You("cannot increase your skill in %s.", skill_name(skill));
        return 0;
    } else {
        You("cannot learn much about %s right now.",
            (skill != P_NONE) ? skill_name(skill) : "that");
        return 0;
    }
    return 1;
}

staticfn int
practice_occ(void)
{
    if (tech_delay) {
        tech_delay++;
        /* a bit of practice every turn, so an interruption doesn't
           waste all of it */
        use_skill(weapon_type(uwep), 1);
        return 1; /* still busy */
    }
    You("finish your practice session.");
    return 0;
}

/* tinkering: the poor gnome's polypile (Slash'EM, Hack'EM);
   pairs and cycles, so every upgrade can be undone again */
staticfn int
tinker_newtyp(int otyp)
{
    switch (otyp) {
    /* weapons */
    case ORCISH_ARROW: return ARROW;
    case ARROW: return ELVEN_ARROW;
    case ELVEN_ARROW: return ORCISH_ARROW;
    case YA: return SILVER_ARROW;
    case SILVER_ARROW: return YA;
    case ORCISH_SPEAR: return SPEAR;
    case SPEAR: return ELVEN_SPEAR;
    case ELVEN_SPEAR: return DWARVISH_SPEAR;
    case DWARVISH_SPEAR: return ORCISH_SPEAR;
    case JAVELIN: return SILVER_SPEAR;
    case SILVER_SPEAR: return JAVELIN;
    case ORCISH_DAGGER: return DAGGER;
    case DAGGER: return ELVEN_DAGGER;
    case ELVEN_DAGGER: return SILVER_DAGGER;
    case SILVER_DAGGER: return ORCISH_DAGGER;
    case KNIFE: return STILETTO;
    case STILETTO: return KNIFE;
    case AXE: return BATTLE_AXE;
    case BATTLE_AXE: return AXE;
    case PICK_AXE: return DWARVISH_MATTOCK;
    case DWARVISH_MATTOCK: return PICK_AXE;
    case ORCISH_SHORT_SWORD: return SHORT_SWORD;
    case SHORT_SWORD: return ELVEN_SHORT_SWORD;
    case ELVEN_SHORT_SWORD: return DWARVISH_SHORT_SWORD;
    case DWARVISH_SHORT_SWORD: return ORCISH_SHORT_SWORD;
    case BROADSWORD: return ELVEN_BROADSWORD;
    case ELVEN_BROADSWORD: return BROADSWORD;
    case LONG_SWORD: return KATANA;
    case KATANA: return LONG_SWORD;
    case TWO_HANDED_SWORD: return TSURUGI;
    case TSURUGI: return TWO_HANDED_SWORD;
    case MACE: return MORNING_STAR;
    case MORNING_STAR: return MACE;
    case WAR_HAMMER: return FLAIL;
    case FLAIL: return WAR_HAMMER;
    case CLUB: return AKLYS;
    case AKLYS: return CLUB;
    case ORCISH_BOW: return BOW;
    case BOW: return ELVEN_BOW;
    case ELVEN_BOW: return YUMI;
    case YUMI: return ORCISH_BOW;
    /* armor */
    case CORNUTHAUM: return DUNCE_CAP;
    case DUNCE_CAP: return CORNUTHAUM;
    case FEDORA: return ELVEN_LEATHER_HELM;
    case ELVEN_LEATHER_HELM: return FEDORA;
    case DENTED_POT: return ORCISH_HELM;
    case ORCISH_HELM: return DWARVISH_IRON_HELM;
    case DWARVISH_IRON_HELM: return DENTED_POT;
    case HELM_OF_BRILLIANCE: return HELM_OF_TELEPATHY;
    case HELM_OF_TELEPATHY: return HELM_OF_BRILLIANCE;
    case CHAIN_MAIL: return ORCISH_CHAIN_MAIL;
    case ORCISH_CHAIN_MAIL: return CHAIN_MAIL;
    case RING_MAIL: return ORCISH_RING_MAIL;
    case ORCISH_RING_MAIL: return RING_MAIL;
    case LEATHER_ARMOR: return STUDDED_LEATHER_ARMOR;
    case STUDDED_LEATHER_ARMOR: return LEATHER_JACKET;
    case LEATHER_JACKET: return LEATHER_ARMOR;
    case HAWAIIAN_SHIRT: return T_SHIRT;
    case T_SHIRT: return HAWAIIAN_SHIRT;
    case MUMMY_WRAPPING: return ORCISH_CLOAK;
    case ORCISH_CLOAK: return DWARVISH_CLOAK;
    case DWARVISH_CLOAK: return ELVEN_CLOAK;
    case ELVEN_CLOAK: return MUMMY_WRAPPING;
    case ROBE: return ALCHEMY_SMOCK;
    case ALCHEMY_SMOCK: return ROBE;
    case ORCISH_SHIELD: return URUK_HAI_SHIELD;
    case URUK_HAI_SHIELD: return ELVEN_SHIELD;
    case ELVEN_SHIELD: return ORCISH_SHIELD;
    case DWARVISH_ROUNDSHIELD: return LARGE_SHIELD;
    case LARGE_SHIELD: return DWARVISH_ROUNDSHIELD;
    case LEATHER_GLOVES: return GAUNTLETS_OF_DEXTERITY;
    case GAUNTLETS_OF_DEXTERITY: return LEATHER_GLOVES;
    case GAUNTLETS_OF_FUMBLING: return GAUNTLETS_OF_POWER;
    case GAUNTLETS_OF_POWER: return GAUNTLETS_OF_FUMBLING;
    case LOW_BOOTS: return HIGH_BOOTS;
    case HIGH_BOOTS: return LOW_BOOTS;
    case FUMBLE_BOOTS: return ELVEN_BOOTS;
    case ELVEN_BOOTS: return FUMBLE_BOOTS;
    case LEVITATION_BOOTS: return WATER_WALKING_BOOTS;
    case WATER_WALKING_BOOTS: return LEVITATION_BOOTS;
    /* tools */
    case SACK: return OILSKIN_SACK;
    case OILSKIN_SACK: return BAG_OF_HOLDING;
    case BAG_OF_HOLDING: return SACK;
    case LARGE_BOX: return CHEST;
    case CHEST: return ICE_BOX;
    case ICE_BOX: return LARGE_BOX;
    case SKELETON_KEY: return LOCK_PICK;
    case LOCK_PICK: return SKELETON_KEY;
    case CREDIT_CARD: return LOCK_PICK;
    case MIRROR: return EXPENSIVE_CAMERA;
    case EXPENSIVE_CAMERA: return MIRROR;
    case LENSES: return BLINDFOLD;
    case BLINDFOLD: return TOWEL;
    case TOWEL: return LENSES;
    case LEASH: return SADDLE;
    case SADDLE: return LEASH;
    case TIN_OPENER: return TINNING_KIT;
    case TINNING_KIT: return TIN_OPENER;
    case TALLOW_CANDLE: return WAX_CANDLE;
    case WAX_CANDLE: return TALLOW_CANDLE;
    case OIL_LAMP: return BRASS_LANTERN;
    case BRASS_LANTERN: return OIL_LAMP;
    case TIN_WHISTLE: return MAGIC_WHISTLE;
    case MAGIC_WHISTLE: return TIN_WHISTLE;
    case WOODEN_FLUTE: return MAGIC_FLUTE;
    case MAGIC_FLUTE: return WOODEN_FLUTE;
    case TOOLED_HORN: return FROST_HORN;
    case FROST_HORN: return FIRE_HORN;
    case FIRE_HORN: return TOOLED_HORN;
    case WOODEN_HARP: return MAGIC_HARP;
    case MAGIC_HARP: return WOODEN_HARP;
    case LEATHER_DRUM: return DRUM_OF_EARTHQUAKE;
    case DRUM_OF_EARTHQUAKE: return LEATHER_DRUM;
    case FLINT: return TOUCHSTONE;
    case TOUCHSTONE: return FLINT;
    default:
        break;
    }
    return 0; /* not upgradable */
}

/* upgrade the wielded object; TRUE if it changed */
staticfn boolean
tinker_upgrade(struct obj *obj)
{
    int newtyp = tinker_newtyp(obj->otyp);

    if (!newtyp || obj->oartifact)
        return FALSE;
    (void) snuff_lit(obj);
    if (obj->quan > 1L) {
        /* only one item of a stack can be worked on at a time */
        struct obj *otmp = splitobj(obj, 1L);

        freeinv(otmp);
        otmp->nomerge = 1;
        otmp = addinv(otmp);
        otmp->nomerge = 0;
        obj = otmp;
    }
    if (obj->otyp == LEASH && obj->leashmon)
        o_unleash(obj);

    obj->otyp = newtyp;
    obj->oclass = objects[newtyp].oc_class;
    switch (newtyp) {
    case MAGIC_FLUTE:
    case FROST_HORN:
    case FIRE_HORN:
    case MAGIC_HARP:
    case DRUM_OF_EARTHQUAKE:
        obj->spe = rn1(5, 4);
        obj->known = 0;
        break;
    case TINNING_KIT:
        obj->spe = rn1(30, 70);
        obj->known = 0;
        break;
    case EXPENSIVE_CAMERA:
        obj->spe = rn1(70, 30);
        obj->known = 0;
        break;
    case OIL_LAMP:
    case BRASS_LANTERN:
        obj->age = rn1(500, 1000);
        break;
    case TALLOW_CANDLE:
    case WAX_CANDLE:
        obj->age = 20L * (long) objects[newtyp].oc_cost;
        break;
    case SADDLE:
    case LEASH:
        obj->leashmon = 0;
        break;
    default:
        /* keep enchantment of weapons and armor; no stray charges */
        if (obj->oclass != WEAPON_CLASS && obj->oclass != ARMOR_CLASS
            && !is_weptool(obj))
            obj->spe = 0;
        break;
    }
    if (!objects[obj->otyp].oc_uses_known)
        obj->known = 1;
    obj->owt = weight(obj);
    if (obj != uwep) {
        setuwep(obj);
    } else {
        /* re-wield to update wielded-weapon state */
        setuwep((struct obj *) 0);
        setuwep(obj);
    }
    if (uwep && bimanual(uwep) && uarms) {
        You("can't hold %s with your shield on.", yname(uwep));
        setuwep((struct obj *) 0);
    } else if (u.twoweap && !can_twoweapon()) {
        untwoweapon();
    }
    update_inventory();
    return TRUE;
}

staticfn int
tinker_occ(void)
{
    int c = 5;

    if (tech_delay) { /* not if (tech_delay++): at end tech_delay == 0 */
        tech_delay++;
        return 1; /* still busy */
    }
    if (!uwep)
        return 0;
    You("finish your tinkering.");
    if (tech_level(T_TINKER) >= 10)
        c++;
    if (rnl(10) < c && tinker_upgrade(uwep)) {
        if (uwep)
            You("now hold %s!", doname(uwep));
        exercise(A_WIS, TRUE);
    } else {
        pline("Your efforts come to nothing.");
    }
    return 0;
}

/* draw energy from the surroundings (Slash'EM) */
staticfn int
draw_energy_occ(void)
{
    int powbonus = 1;

    if (tech_delay) {
        struct rm *lev;

        tech_delay++;
        confdir(TRUE); /* draw from a random adjacent spot */
        if (isok(u.ux + u.dx, u.uy + u.dy)) {
            lev = &levl[u.ux + u.dx][u.uy + u.dy];
            switch (lev->typ) {
            case ALTAR: /* divine power */
                powbonus = (u.uenmax > 28) ? u.uenmax / 4 : 7;
                break;
            case THRONE: /* regal == pseudo divine */
                powbonus = (u.uenmax > 36) ? u.uenmax / 6 : 6;
                break;
            case CLOUD: /* air */
            case TREE:  /* earth */
                powbonus = 5;
                break;
            case LAVAPOOL: /* fire */
            case LAVAWALL:
                if (Role_if(PM_WIZARD) || (gu.urole.filecode
                                           && !strcmp(gu.urole.filecode,
                                                      "Fla")))
                    powbonus = d(4, 6);
                break;
            case ICE:
                if (gu.urole.filecode && !strcmp(gu.urole.filecode, "Ice"))
                    powbonus = d(4, 6);
                break;
            case AIR:
            case MOAT:  /* doesn't freeze */
            case WATER: /* water: the most ordered form */
                powbonus = 4;
                break;
            case POOL: /* can dry up */
                powbonus = 3;
                break;
            case FOUNTAIN:
                powbonus = 2;
                break;
            case SINK: /* cleansing water */
                if (!rn2(3))
                    powbonus = 2;
                break;
            case GRAVE:
                if (gu.urole.filecode && !strcmp(gu.urole.filecode, "Nec"))
                    powbonus = (u.uenmax > 36) ? u.uenmax / 6 : 6;
                else
                    powbonus = -4; /* death drains power */
                break;
            case ROOM:
                /* the open world's living ground */
                if (lev->flavor == OWF_GRASS || lev->flavor == OWF_FOREST)
                    powbonus = 2;
                else if (lev->flavor == OWF_ASH)
                    powbonus = -2; /* dead, scorched land */
                break;
            default:
                break;
            }
        }
        u.uen += powbonus;
        if (u.uen > u.uenmax) {
            tech_delay = 0;
            u.uen = u.uenmax;
        }
        if (u.uen < 0)
            u.uen = 0;
        disp.botl = TRUE;
        return 1; /* still busy */
    }
    You("finish drawing energy from your surroundings.");
    return 0;
}

/* martial arts rock breaking (Hack'EM) */
staticfn int
ma_break_occ(void)
{
    struct obj *obj, *bobj;
    int prob, skill = P_SKILL(P_BARE_HANDED_COMBAT);
    coordxy x = tech_occ_x, y = tech_occ_y;

    if (distu(x, y) > 2) {
        Your("qi dissipates in all directions.");
        make_confused(HConfusion + 6 + skill, FALSE);
        return 0;
    }
    if ((obj = sobj_at(BOULDER, x, y)) == 0
        && (obj = sobj_at(STATUE, x, y)) == 0) {
        Your("qi dissipates harmlessly.");
        return 0;
    }
    pline("Focusing your qi, you %s the %s.", rn2(2) ? "strike" : "hit",
          (obj->otyp == BOULDER) ? "boulder" : "statue");

    /* even while blind you can first feel and then imagine the rock */
    if (Confusion || Hallucination || Stunned) {
        if (rn2(2)) {
            You("swing wildly, missing the %s.",
                (obj->otyp == BOULDER) ? "boulder" : "statue");
        } else {
            You("slip, hitting your %s against the %s!", body_part(HEAD),
                (obj->otyp == BOULDER) ? "boulder" : "statue");
            losehp(Maybe_Half_Phys(d(1, 4)),
                   (obj->otyp == BOULDER) ? "face planting into a boulder"
                                          : "trying to headbutt a statue",
                   KILLED_BY);
        }
        return 0;
    }

    prob = (40 - u.ulevel) / max(1, skill);
    /* inherently strong races get a bonus, inherently weak ones not */
    if (race_is("Gia"))
        prob -= 3;
    if (race_is("Cen"))
        prob -= 2;
    if (Race_if(PM_ELF))
        prob += 1;
    if (uarmg) {
        if (uarmg->otyp == GAUNTLETS_OF_POWER)
            prob -= 10;
        else if (uarmg->otyp == GAUNTLETS_OF_FUMBLING)
            prob *= 4;
    }
    if (prob < 3)
        prob = 3; /* never always successful without great skill */

    if (skill > P_EXPERT || !rn2(prob)) {
        if (obj->otyp == BOULDER) {
            fracture_rock(obj);
            pline_The("boulder splits and falls apart.");
        } else {
            if (break_statue(obj))
                pline_The("statue shatters into pieces.");
        }
        if ((bobj = sobj_at(BOULDER, x, y)) != 0) {
            /* another boulder here: restack it to the top */
            obj_extract_self(bobj);
            place_object(bobj, x, y);
        }
        newsym(x, y);
        exercise(A_STR, TRUE);
        use_skill(P_BARE_HANDED_COMBAT, 1);
    } else {
        pline("However, your qi is not focused enough to break the %s.",
              (obj->otyp == BOULDER) ? "boulder" : "statue");
        losehp(Maybe_Half_Phys(d(1, 6)),
               (obj->otyp == BOULDER) ? "trying to split a boulder"
                                      : "trying to shatter a statue",
               KILLED_BY);
        if (!rn2(5)) {
            You("need more training to reliably focus your qi.");
            use_skill(P_BARE_HANDED_COMBAT, 1);
        }
    }
    return 0; /* done */
}

/* start breaking a boulder or statue at <x,y>; also used when a monk
   fights a boulder or statue bare-handed (hack.c) */
int
do_breakrock(coordxy x, coordxy y)
{
    if (P_SKILL(P_BARE_HANDED_COMBAT) < P_SKILLED) {
        You("lack the necessary training to focus your qi.");
        return 0;
    }
    You("start channeling your qi.");
    tech_occ_x = x, tech_occ_y = y;
    tech_occ_id = T_BREAK_ROCK;
    set_occupation(tech_occupation, "channeling your qi", 0);
    return 1;
}

/* ------------------------------------------------------------------ */
/* hooks used elsewhere                                                */
/* ------------------------------------------------------------------ */

/* to-hit bonus from active techniques (find_roll_to_hit) */
int
tech_tohit_bonus(void)
{
    int tmp = 0;

    if (tech_inuse(T_KIII))
        tmp += 4;
    if (tech_inuse(T_BERSERK) || tech_inuse(T_SOULEATER))
        tmp += 2;
    return tmp;
}

/*
 * Damage adjustment from active techniques when the hero hits 'mon' with
 * 'obj' (null: bare hands) in a way given by 'thrown' (HMON_xxx); returns
 * the new damage.  Sets *hittxt if a hit message has been given.
 */
int
tech_dmg_bonus(struct monst *mon, struct obj *obj, int thrown, int dmg,
               boolean *hittxt)
{
    boolean melee = (thrown == HMON_MELEE);

    /* bare-handed martial arts techniques */
    if (!obj && melee) {
        if (tech_inuse(T_CHI_STRIKE) && u.uen > 0) {
            int force = 10 + (u.ulevel / 5);

            You_feel("a surge of force.");
            dmg += (u.uen > force) ? force : u.uen;
            u.uen -= force;
            if (u.uen < 0)
                u.uen = 0;
            disp.botl = TRUE;
        }
        if (tech_inuse(T_E_FIST)) {
            int dmgbonus = d(2, 4);

            *hittxt = TRUE;
            switch (rn2(4)) {
            case 0: /* fire */
                if (!Blind)
                    pline("%s is on fire!", Monnam(mon));
                if (resists_fire(mon)) {
                    shieldeff(mon->mx, mon->my);
                    if (!Blind)
                        pline_The("fire doesn't heat %s!", mon_nam(mon));
                    golemeffects(mon, AD_FIRE, dmgbonus);
                    dmgbonus = 0;
                } else if (!rn2(20)) {
                    dmgbonus += rnd(6);
                }
                dmgbonus += destroy_items(mon, AD_FIRE, dmgbonus);
                break;
            case 1: /* cold */
                if (!Blind)
                    pline("%s is covered in frost!", Monnam(mon));
                if (resists_cold(mon)) {
                    shieldeff(mon->mx, mon->my);
                    if (!Blind)
                        pline_The("frost doesn't chill %s!", mon_nam(mon));
                    golemeffects(mon, AD_COLD, dmgbonus);
                    dmgbonus = 0;
                } else if (!rn2(25)) {
                    dmgbonus += rnd(6);
                }
                dmgbonus += destroy_items(mon, AD_COLD, dmgbonus);
                break;
            case 2: /* electricity */
                if (!Blind)
                    pline("%s is zapped!", Monnam(mon));
                if (resists_elec(mon)) {
                    shieldeff(mon->mx, mon->my);
                    if (!Blind)
                        pline_The("zap doesn't shock %s!", mon_nam(mon));
                    golemeffects(mon, AD_ELEC, dmgbonus);
                    dmgbonus = 0;
                } else if (!rn2(100)) {
                    dmgbonus += rnd(20);
                    if (canseemon(mon))
                        pline("%s is jolted with electricity!", Monnam(mon));
                }
                dmgbonus += destroy_items(mon, AD_ELEC, dmgbonus);
                break;
            default: /* acid */
                if (!Blind)
                    pline("%s is covered in acid!", Monnam(mon));
                if (resists_acid(mon)) {
                    if (!Blind)
                        pline_The("acid doesn't burn %s!", mon_nam(mon));
                    dmgbonus = 0;
                } else if (!rn2(100)) {
                    dmgbonus += rnd(20);
                    if (canseemon(mon))
                        pline("%s is severely burned!", Monnam(mon));
                }
                break;
            }
            dmg += dmgbonus;
        }
    }
    /* Kiii doubles the damage, berserk adds some; being in the thick of
       the fight keeps them going (Slash'EM, Hack'EM) */
    if (tech_inuse(T_KIII)) {
        dmg *= 2;
        extend_tech_time(T_KIII, rnd(4));
    }
    if (tech_inuse(T_BERSERK)) {
        dmg += 4;
        extend_tech_time(T_BERSERK, rnd(4));
    }
    if (melee && tech_inuse(T_SOULEATER) && obj && obj == uwep) {
        dmg += d((u.ulevel / 4) + 1, 8);
        pline("Dark flames envelop %s!", mon_nam(mon));
        *hittxt = TRUE;
    }
    if (melee && !obj && tech_inuse(T_EVISCERATE)) {
        dmg += rnd((u.ulevel / 2) + 1) + (u.ulevel / 2);
        You("slash %s!", mon_nam(mon));
        *hittxt = TRUE;
    }
    return dmg;
}

/* extra multishot from missile flurry (dothrow.c) */
int
tech_flurry_bonus(struct obj *obj)
{
    int skill = objects[obj->otyp].oc_skill;

    if (tech_inuse(T_FLURRY) && (skill == -P_BOW || skill == -P_SLING))
        return 1; /* let 'em rip! */
    return 0;
}

/* ice armor: protection when not wearing body armor or a shield */
int
tech_icearmor_ac(void)
{
    if (!tech_inuse(T_ICEARMOR) || uarm || uarms)
        return 0;
    return (u.ulevel / 2) + 2;
}

/* ice armor chills monsters that hit the hero in melee;
   returns TRUE if the attacker died */
boolean
tech_icearmor_passive(struct monst *mtmp)
{
    int icetmp = tech_icearmor_ac(), tmp;

    if (!icetmp || DEADMONSTER(mtmp) || rn2(24) > icetmp)
        return FALSE;
    if (resists_cold(mtmp)) {
        shieldeff(mtmp->mx, mtmp->my);
        pline_The("cold doesn't affect %s.", mon_nam(mtmp));
        golemeffects(mtmp, AD_COLD, icetmp);
        return FALSE;
    }
    tmp = icetmp * d(1, 4);
    if (resists_fire(mtmp))
        tmp += 3;
    pline("%s is suddenly freezing!", Monnam(mtmp));
    if (!rn2(3))
        tmp += destroy_items(mtmp, AD_COLD, tmp);
    if ((mtmp->mhp -= tmp) <= 0) {
        pline("%s is frozen solid!", Monnam(mtmp));
        xkilled(mtmp, XKILL_NOMSG);
        return (boolean) DEADMONSTER(mtmp);
    }
    return FALSE;
}

/* ------------------------------------------------------------------ */
/* the martial arts "blitz" techniques                                 */
/* ------------------------------------------------------------------ */

/* Keep commands that reference the same blitz together, and each
   BLITZ_START before its BLITZ_CHAIN before its BLITZ_END */
#define BLITZ_START 0 /* starts the chain */
#define BLITZ_CHAIN 1 /* goes anywhere in the chain (usually middle) */
#define BLITZ_END 2   /* finishes the chain */

static const struct blitz_tab {
    const char *blitz_cmd; /* the typed command */
    int blitz_len;         /* its length */
    int (*blitz_funct)(void);
    int blitz_tech;        /* the technique needed to use it */
    int blitz_type;        /* BLITZ_START, _CHAIN or _END */
} blitzes[] = {
    { "LLDDR", 5, blitz_chi_strike, T_CHI_STRIKE, BLITZ_START },
    { "RRDDL", 5, blitz_chi_strike, T_CHI_STRIKE, BLITZ_START },
    { "RR", 2, blitz_dash, T_DASH, BLITZ_START },
    { "LL", 2, blitz_dash, T_DASH, BLITZ_START },
    { "UURRDDL", 7, blitz_e_fist, T_E_FIST, BLITZ_START },
    { "UULLDDR", 7, blitz_e_fist, T_E_FIST, BLITZ_START },
    { ">>>>", 4, blitz_power_surge, T_POWER_SURGE, BLITZ_START },
    { "LRL", 3, blitz_pummel, T_PUMMEL, BLITZ_CHAIN },
    { "RLR", 3, blitz_pummel, T_PUMMEL, BLITZ_CHAIN },
    { "DDDD", 4, blitz_g_slam, T_G_SLAM, BLITZ_END },
    { "DUDUDU", 6, blitz_uppercut, T_UPPERCUT, BLITZ_END },
    { "UUUUD", 5, blitz_spirit_bomb, T_SPIRIT_BOMB, BLITZ_END },
    { "", 0, (int (*)(void)) 0, 0, BLITZ_END } /* array terminator */
};

#define MAX_BLITZ 50
#define MIN_CHAIN 2
#define MAX_CHAIN 5

staticfn void
doblitzlist(int maxmoves)
{
    winid tmpwin;
    int i;
    char buf[BUFSZ];
    menu_item *selected;
    anything any;

    tmpwin = create_nhwindow(NHW_MENU);
    start_menu(tmpwin, MENU_BEHAVE_STANDARD);
    any = cg.zeroany;

    Sprintf(buf, "%16s %5s %-17s", "[U = Up]", "", "[L = Left]");
    add_menu_str(tmpwin, buf);
    Sprintf(buf, "%16s %5s %-17s", "[D = Down]", "", "[R = Right]");
    add_menu_str(tmpwin, buf);
    Sprintf(buf, "%16s %5s %-17s", "[> = Descend]", "", "[< = Ascend]");
    add_menu_str(tmpwin, buf);
    Sprintf(buf, "%-30s %10s   %s", "Name", "Type", "Command");
    add_menu_heading(tmpwin, buf);
    for (i = 0; blitzes[i].blitz_len; i++) {
        if (!tech_known(blitzes[i].blitz_tech))
            continue;
        Sprintf(buf, "%-30s %10s   %s",
                (i && blitzes[i].blitz_tech == blitzes[i - 1].blitz_tech)
                    ? "" : tech_names[blitzes[i].blitz_tech],
                (blitzes[i].blitz_type == BLITZ_START) ? "starter"
                : (blitzes[i].blitz_type == BLITZ_CHAIN) ? "chain"
                  : "finisher",
                blitzes[i].blitz_cmd);
        add_menu(tmpwin, &nul_glyphinfo, &any, 0, 0, ATR_NONE, NO_COLOR,
                 buf, MENU_ITEMFLAGS_NONE);
    }
    add_menu_str(tmpwin, "");
    Sprintf(buf, "You have a maximum of %d moves available.", maxmoves);
    add_menu_str(tmpwin, buf);
    end_menu(tmpwin, "Currently known blitz manoeuvres");
    (void) select_menu(tmpwin, PICK_NONE, &selected);
    destroy_nhwindow(tmpwin);
}

/* read the directions making up a blitz; returns the number of commands
   in blitz_chain[], 0 to abort */
static int blitz_chain[MAX_CHAIN];

staticfn int
blitz_input(void)
{
    int i, j, bdone, blitz_num, tech_no = get_tech_no(T_BLITZ),
        max_moves = MIN_CHAIN + (techlev(tech_no) / 10);
    char cmdlist[MAX_BLITZ + 2], prompt[BUFSZ];
    const char *bp;

    doblitzlist(max_moves);
    cmdlist[0] = '\0';
    for (i = 0; i < MAX_BLITZ; i++) {
        if (!i)
            Strcpy(prompt, "Enter Blitz Command [. to end]:");
        else
            Snprintf(prompt, sizeof prompt, "[%s]:", cmdlist);
        if (!getdir(prompt))
            return 0;
        if (!u.dx && !u.dy && !u.dz)
            break;
        if (u.dx == -1)
            Strcat(cmdlist, "L");
        else if (u.dx == 1)
            Strcat(cmdlist, "R");
        if (u.dy == -1)
            Strcat(cmdlist, "U");
        else if (u.dy == 1)
            Strcat(cmdlist, "D");
        if (u.dz == -1)
            Strcat(cmdlist, "<");
        else if (u.dz == 1)
            Strcat(cmdlist, ">");
        if ((int) strlen(cmdlist) >= MAX_BLITZ)
            break;
    }
    if (!*cmdlist)
        return 0;

    /* parse the input; no two identical commands in a row */
    bp = cmdlist;
    blitz_num = 0;
    while (*bp) {
        bdone = 0;
        for (j = 0; blitzes[j].blitz_len; j++) {
            int cmd_len = blitzes[j].blitz_len;
            const char *nam = tech_names[blitzes[j].blitz_tech];

            if (strncmp(bp, blitzes[j].blitz_cmd, cmd_len))
                continue;
            if (blitz_num >= MAX_CHAIN || blitz_num >= max_moves) {
                You("went over the maximum allowable commands [%d].",
                    max_moves);
                return 0;
            }
            if (!tech_known(blitzes[j].blitz_tech)) {
                You("don't know %s yet.", nam);
                return 0;
            }
            if (blitz_num) {
                int prev = blitz_chain[blitz_num - 1];

                if (j == prev) {
                    You_cant("chain two of the exact same commands [%s] "
                             "in a row.", nam);
                    return 0;
                }
                if (blitzes[prev].blitz_type == BLITZ_END) {
                    You_cant("enter more commands after a chain finisher "
                             "[%s].", tech_names[blitzes[prev].blitz_tech]);
                    return 0;
                }
                /* two chain starters in a row are fine */
                if (blitzes[j].blitz_type == BLITZ_START
                    && blitzes[prev].blitz_type != BLITZ_START) {
                    You_cant("enter a chain starter [%s] after starting a "
                             "command chain.", nam);
                    return 0;
                }
            }
            bp += cmd_len;
            blitz_chain[blitz_num++] = j;
            bdone = 1;
            break;
        }
        if (!bdone) {
            pline("You stumble over the sequence [%s].  Try again.",
                  cmdlist);
            return 0;
        }
    }
    return blitz_num;
}

staticfn int
tech_blitz(int tech_no)
{
    int i, dx, dy, blitz_num;

    nhUse(tech_no);
    if (!monk_hands_free())
        return 0;
    if (u.uen < 10) {
        You("are too weak to attempt this!  "
            "You need at least 10 points of energy!");
        return 0;
    }
    if (!getdir("In what direction do you want to blitz?"))
        return 0;
    if (!u.dx && !u.dy)
        return 0;
    dx = u.dx, dy = u.dy;

    if (!(blitz_num = blitz_input()))
        return 0;
    /* energy is used only if a valid sequence was entered */
    u.uen -= 10;
    disp.botl = TRUE;
    for (i = 0; i < blitz_num; i++) {
        u.dx = dx, u.dy = dy, u.dz = 0;
        if (!(*blitzes[blitz_chain[i]].blitz_funct)())
            break;
        if (u.uhp < 1 || gm.multi < 0)
            break;
    }
    return 1;
}

staticfn int
blitz_chi_strike(void)
{
    int tech_no = get_tech_no(T_CHI_STRIKE);

    if (tech_no < 0)
        return 0;
    if (u.uen < 1) {
        You("are too weak to attempt this!  "
            "You need at least one point of energy!");
        return 0;
    }
    You_feel("energy surge through your %s!", makeplural(body_part(HAND)));
    techt_inuse(tech_no) = techlev(tech_no) + 4;
    return 1;
}

staticfn int
blitz_e_fist(void)
{
    int tech_no = get_tech_no(T_E_FIST);

    if (tech_no < 0)
        return 0;
    You("focus the powers of the elements into your %s.",
        makeplural(body_part(HAND)));
    techt_inuse(tech_no) = rnd((techlev(tech_no) / 3) + 1) + d(1, 4) + 2;
    return 1;
}

/* a barrage of blows; u.dx, u.dy already set up */
staticfn int
blitz_pummel(void)
{
    int i, tech_no = get_tech_no(T_PUMMEL);
    struct monst *mtmp;

    if (tech_no < 0 || !monk_hands_free())
        return 0;
    if (!u.dx && !u.dy) {
        You("flex your muscles.");
        return 0;
    }
    You("let loose a barrage of blows!");
    if (!(mtmp = tech_target())) {
        You("strike nothing.");
        return 1;
    }
    if (!force_attack(mtmp, TRUE))
        return 1;
    /* the extra blows */
    for (i = 0; i < 4; i++) {
        if (rn2(70) > techlev(tech_no) + 30)
            break;
        mtmp = tech_target();
        if (!mtmp || DEADMONSTER(mtmp) || u.uhp < 1)
            break;
        if (!force_attack(mtmp, TRUE))
            break;
    }
    return 1;
}

/* slam a monster into the ground; u.dx, u.dy already set up */
staticfn int
blitz_g_slam(void)
{
    int tmp, tech_no = get_tech_no(T_G_SLAM);
    coordxy x = u.ux + u.dx, y = u.uy + u.dy;
    struct monst *mtmp;
    struct trap *chasm;

    if (tech_no < 0 || !monk_hands_free())
        return 0;
    if (!u.dx && !u.dy) {
        You("flex your muscles.");
        return 0;
    }
    if (!(mtmp = tech_target()) || u.uswallow) {
        You("strike nothing.");
        return 0;
    }
    /* required for the first attack, otherwise nothing happens if we
       attempt to attack peacefuls */
    if (!force_attack(mtmp, FALSE))
        return 0;
    mtmp = m_at(x, y);
    if (!mtmp || DEADMONSTER(mtmp) || u.uswallow)
        return 1;
    wakeup(mtmp, TRUE);
    You("hurl %s downwards...", mon_nam(mtmp));
    if (Is_airlevel(&u.uz) || Is_waterlevel(&u.uz))
        return 1;

    tmp = 5 + rnd(6) + (techlev(tech_no) / 5);
    if (!t_at(x, y) && (levl[x][y].typ == ROOM || levl[x][y].typ == CORR)
        && !Sokoban && !In_endgame(&u.uz) && !On_stairs(x, y)
        && (chasm = maketrap(x, y, PIT)) != 0) {
        if (!is_flyer(mtmp->data) && !is_clinger(mtmp->data))
            mtmp->mtrapped = 1;
        chasm->tseen = 1;
        newsym(x, y);
        pline("%s slams into the ground, creating a crater!", Monnam(mtmp));
        tmp *= 2;
    }
    mselftouch(mtmp, "Falling, ", TRUE);
    if (!DEADMONSTER(mtmp) && tech_damage_mon(mtmp, tmp)) {
        if (!cansee(x, y))
            pline("It is destroyed!");
    }
    return 1;
}

/* a mighty uppercut; u.dx, u.dy already set up */
staticfn int
blitz_uppercut(void)
{
    int tmp, tech_no = get_tech_no(T_UPPERCUT);
    struct monst *mtmp;
    struct permonst *mdat;

    if (tech_no < 0 || !monk_hands_free())
        return 0;
    if (!u.dx && !u.dy) {
        You("flex your muscles.");
        return 0;
    }
    if (!(mtmp = tech_target()) || u.uswallow) {
        You("strike nothing.");
        return 0;
    }
    if (mtmp->mpeaceful && !mtmp->mtame) {
        char qbuf[QBUFSZ];

        Sprintf(qbuf, "Really attack %s?", mon_nam(mtmp));
        if (!paranoid_query(ParanoidHit, qbuf))
            return 0;
    }
    mdat = mtmp->data;
    tmp = 10 + rnd(6) + (techlev(tech_no) / 5);
    if (has_head(mdat)) {
        /* bonus against things with heads */
        You("wind up your fist and clock %s with an uppercut!",
            mon_nam(mtmp));
        tmp *= 2;
    } else {
        You("slam %s with your fist!", mon_nam(mtmp));
    }
    setmangry(mtmp, TRUE);
    if (tech_damage_mon(mtmp, tmp))
        return 1;
    wakeup(mtmp, TRUE);
    if (mdat->msize <= gy.youmonst.data->msize && !thick_skinned(mdat)
        && !unsolid(mdat)) {
        if (rn2(2)) {
            if (canspotmon(mtmp))
                pline("%s %s from your powerful strike!", Monnam(mtmp),
                      makeplural(stagger(mdat, "stagger")));
            mhurtle(mtmp, u.dx, u.dy, 1);
        } else if (!mindless(mdat)) {
            if (canspotmon(mtmp))
                Your("forceful blow knocks %s senseless!", mon_nam(mtmp));
            mtmp->mconf = 1;
        }
    }
    return 1;
}

/* dash two squares; u.dx, u.dy already set up */
staticfn int
blitz_dash(void)
{
    coordxy mx, my;
    boolean stopped = FALSE;

    if (u.utrap) {
        You("cannot air dash until you extricate yourself.");
        return 0;
    } else if (Underwater) {
        pline("This is not the water dash!");
        return 0;
    } else if (u.ustuck) {
        You("cannot dash while you are held.");
        return 0;
    } else if (u.usteed) {
        You("cannot dash while riding.");
        return 0;
    }
    if (Stunned || Confusion || Fumbling)
        confdir(TRUE);
    if (!u.dx && !u.dy) {
        You("stretch.");
        return 0;
    }
    if (is_pool(u.ux + 2 * u.dx, u.uy + 2 * u.dy) && !Levitation
        && !Flying && !Wwalking && !Swimming
        && !paranoid_query(ParanoidSwim, "Really dash into the water?"))
        return 0;
    if (is_lava(u.ux + 2 * u.dx, u.uy + 2 * u.dy) && !Levitation
        && !Flying && !paranoid_query(ParanoidSwim,
                                      "Really dash into the lava?"))
        return 0;
    You("dash forwards!");

    mx = u.ux + u.dx, my = u.uy + u.dy;
    /* no cheating in Sokoban; since it's only a 2 step jump we only need
       to check the middle space */
    if (isok(mx, my) && Sokoban) {
        struct trap *ttmp = t_at(mx, my);

        if (ttmp && (is_pit(ttmp->ttyp) || is_hole(ttmp->ttyp)))
            stopped = TRUE;
    }
    if (stopped) {
        if (test_move(u.ux, u.uy, u.dx, u.dy, TEST_MOVE) && !m_at(mx, my)) {
            teleds(mx, my, TELEDS_ALLOW_DRAG);
            sokoban_guilt();
        }
    } else {
        hurtle(u.dx, u.dy, 2, FALSE);
    }
    /* no helplessness after a dash */
    if (gm.multi < 0) {
        gm.multi = 0;
        gm.multi_reason = (const char *) 0;
        gn.nomovemsg = (const char *) 0;
    }
    return 1;
}

staticfn int
blitz_power_surge(void)
{
    int num, tech_no = get_tech_no(T_POWER_SURGE);

    if (tech_no < 0)
        return 0;
    if (Upolyd) {
        You("cannot tap into your full potential in this form.");
        return 0;
    }
    if (techt_inuse(tech_no)) {
        pline("This technique is already active!");
        return 0;
    }
    You("tap into the full extent of your power!");
    num = 50 + (2 * techlev(tech_no));
    techt_inuse(tech_no) = num + 1;
    u.uenmax += num;
    u.uen = u.uenmax;
    disp.botl = TRUE;
    return 1;
}

/* a ball of spiritual energy; u.dx, u.dy already set up */
staticfn int
blitz_spirit_bomb(void)
{
    int num, i, tech_no = get_tech_no(T_SPIRIT_BOMB);
    coordxy sx = u.ux, sy = u.uy;

    if (tech_no < 0 || !monk_hands_free())
        return 0;
    if (!u.dx && !u.dy) {
        You("flex your muscles.");
        return 0;
    }
    You("gather your energy...");
    if (u.uen < 10) {
        pline("But it fizzles out.");
        u.uen = 0;
        disp.botl = TRUE;
        return 1;
    }
    num = 10 + d(5, (techlev(tech_no) / 2) + 1);
    num = (u.uen < num) ? u.uen : num;
    u.uen -= num;
    disp.botl = TRUE;

    for (i = 0; i < 2; i++) {
        if (!isok(sx + u.dx, sy + u.dy) || u.uswallow
            || IS_STWALL(levl[sx + u.dx][sy + u.dy].typ)
            || closed_door(sx + u.dx, sy + u.dy))
            break;
        sx += u.dx, sy += u.dy;
        if (cansee(sx, sy)) {
            /* display the path of the bomb */
            tmp_at(DISP_FLASH, explosion_to_glyph(EXPL_MAGICAL, S_expl_mc));
            tmp_at(sx, sy);
            nh_delay_output();
            tmp_at(DISP_END, 0);
        }
    }
    num = spell_damage_bonus(num);
    /* a magical explosion (credited to the hero) */
    explode(sx, sy, TECH_ZT_SPELL_MM, d(3, 6) + num, SPBOOK_CLASS,
            EXPL_MAGICAL);
    return 1;
}

/* ------------------------------------------------------------------ */
/* regular techniques                                                  */
/* ------------------------------------------------------------------ */

staticfn int
tech_research(int tech_no)
{
    if (Hallucination || Stunned || Confusion) {
        You_cant("concentrate right now!");
        return 0;
    } else if (!gi.invent) {
        You("have nothing to research.");
        return 0;
    } else if ((ACURR(A_INT) + ACURR(A_WIS)) < rnd(60)) {
        pline("Nothing in your pack looks familiar.");
        return 1;
    }
    You("examine your possessions.");
    identify_pack((techlev(tech_no) / 10) + 1, FALSE);
    return 1;
}

staticfn int
tech_surgery(int tech_no)
{
    if (Hallucination || Stunned || Confusion) {
        You("are in no condition to perform surgery!");
        return 0;
    }
    if (Sick || Slimed) {
        struct obj *scalpel = carrying(SCALPEL);

        if (scalpel) {
            pline("Using %s (ow!), you cure your infection!",
                  yname(scalpel));
            make_sick(0L, (char *) 0, TRUE, SICK_ALL);
            make_slimed(0L, (char *) 0);
            if (Upolyd) {
                u.mh -= 5;
                if (u.mh < 1)
                    rehumanize();
            } else if (u.uhp > 6) {
                u.uhp -= 5;
            } else {
                u.uhp = 1;
            }
            disp.botl = TRUE;
            return 1;
        }
        pline("If only you had a scalpel...");
    }
    if (Upolyd ? (u.mh < u.mhmax) : (u.uhp < u.uhpmax)) {
        You("strap your wounds as best you can.");
        healup(techlev(tech_no) + rn1(5, 5), 0, FALSE, FALSE);
        disp.botl = TRUE;
        return 1;
    }
    You("don't need your healing powers!");
    return 0;
}

staticfn int
tech_healhands(int tech_no)
{
    if (Slimed) {
        Your("body is on fire!");
        burn_away_slime();
        return 1;
    } else if (Sick) {
        You("lay your %s on the foul sickness...",
            makeplural(body_part(HAND)));
        make_sick(0L, (char *) 0, TRUE, SICK_ALL);
        return 1;
    } else if (Upolyd ? (u.mh < u.mhmax) : (u.uhp < u.uhpmax)) {
        pline("A warm glow spreads through your body!");
        healup(techlev(tech_no) * 4, 0, FALSE, FALSE);
        return 1;
    }
    pline1(nothing_happens);
    return 0;
}

staticfn int
tech_kiii(int tech_no)
{
    You("scream \"KIIILLL!\"");
    aggravate();
    wake_nearby(FALSE);
    techt_inuse(tech_no) = rnd((techlev(tech_no) / 6) + 1) + 2;
    return 1;
}

staticfn int
tech_vanish(int tech_no)
{
    boolean wasinvis = !!Invis;

    if (Invisible && Fast) {
        You("are already quite nimble and undetectable.");
        return 0;
    }
    techt_inuse(tech_no) = rn1(50, 50) + techlev(tech_no);
    if (!Invisible)
        pline("In a puff of smoke, you disappear!");
    if (!Fast)
        You_feel("more nimble!");
    incr_itimeout(&HInvis, techt_inuse(tech_no));
    incr_itimeout(&HFast, techt_inuse(tech_no));
    newsym(u.ux, u.uy);
    if (!wasinvis)
        see_monsters();
    return 1;
}

/*
 * Base damage is always something, though it may be reduced to zero if
 * the hero is hampered.  Since techlev is never zero, striking vital
 * organs always does _some_ damage.
 */
staticfn int
tech_critstrike(int tech_no)
{
    struct monst *mtmp;
    int oldhp, tmp;

    if (!getdir((char *) 0))
        return 0;
    if (!u.dx && !u.dy) {
        You("decide against that idea.");
        return 0;
    }
    if (!(mtmp = tech_target())) {
        You("perform a flashy twirl!");
        return 0;
    }
    oldhp = mtmp->mhp;
    if (!force_attack(mtmp, FALSE))
        return 0;
    if (!DEADMONSTER(mtmp) && mtmp->mhp < oldhp
        && !noncorporeal(mtmp->data) && !unsolid(mtmp->data)) {
        You("strike %s vital organs!", s_suffix(mon_nam(mtmp)));
        tmp = (mtmp->mhp > 1) ? mtmp->mhp / 2 : 1;
        if (!humanoid(mtmp->data) || is_golem(mtmp->data)
            || mtmp->data->mlet == S_CENTAUR) {
            You("are hampered by the differences in anatomy.");
            tmp /= 2;
        }
        tmp += techlev(tech_no);
        (void) tech_damage_mon(mtmp, tmp);
    }
    return 1;
}

staticfn int
tech_cutthroat(int tech_no)
{
    struct monst *mtmp;
    int oldhp, tmp;

    if (!uwep) {
        You_cant("perform that without a weapon.");
        return 0;
    }
    if (!is_blade(uwep)) {
        You("need a blade to perform cutthroat!");
        return 0;
    }
    if (!getdir((char *) 0))
        return 0;
    if (!u.dx && !u.dy) {
        pline("Things may be going badly, but that's extreme.");
        return 0;
    }
    if (!(mtmp = tech_target())) {
        You("attack...nothing!");
        return 0;
    }
    oldhp = mtmp->mhp;
    if (!force_attack(mtmp, FALSE))
        return 0;
    if (!DEADMONSTER(mtmp) && mtmp->mhp < oldhp) {
        if (!has_head(mtmp->data) || u.uswallow) {
            You_cant("perform cutthroat on %s!", mon_nam(mtmp));
        } else {
            if (rn2(5) < (techlev(tech_no) / 10) + 1) {
                You("sever %s head!", s_suffix(mon_nam(mtmp)));
                tmp = mtmp->mhp;
            } else {
                You("hurt %s badly!", mon_nam(mtmp));
                tmp = mtmp->mhp / 2;
            }
            tmp += techlev(tech_no);
            (void) tech_damage_mon(mtmp, tmp);
        }
    }
    return 1;
}

staticfn int
tech_blessing(void)
{
    char Your_buf[BUFSZ];
    struct obj *obj;
    const char *str;

    if (!(obj = getobj("bless", any_obj_ok, GETOBJ_PROMPT)))
        return 0;
    pline("An aura of holiness surrounds your %s!",
          makeplural(body_part(HAND)));
    Your_buf[0] = '\0';
    if (!Blind)
        (void) Shk_Your(Your_buf, obj);
    if (obj->cursed) {
        if (!Blind)
            pline("%s%s %s.", Your_buf, aobjnam(obj, "softly glow"),
                  hcolor(NH_AMBER));
        uncurse(obj);
        obj->bknown = 1;
    } else if (!obj->blessed) {
        if (!Blind) {
            str = hcolor(NH_LIGHT_BLUE);
            pline("%s%s with a%s %s aura.", Your_buf,
                  aobjnam(obj, "softly glow"),
                  strchr(vowels, *str) ? "n" : "", str);
        }
        bless(obj);
        obj->bknown = 1;
    } else {
        if (obj->bknown) {
            pline("That object is already blessed!");
            return 0;
        }
        obj->bknown = 1;
        pline_The("aura fades.");
    }
    update_inventory();
    return 1;
}

staticfn int
tech_curse(void)
{
    char Your_buf[BUFSZ];
    struct obj *obj;
    const char *str;

    if (!(obj = getobj("curse", any_obj_ok, GETOBJ_PROMPT)))
        return 0;
    pline("An aura of evil surrounds your %s!", makeplural(body_part(HAND)));
    Your_buf[0] = '\0';
    if (!Blind)
        (void) Shk_Your(Your_buf, obj);
    if (obj->blessed) {
        if (!Blind)
            pline("%s%s %s.", Your_buf, aobjnam(obj, "darkly glow"),
                  hcolor(NH_AMBER));
        unbless(obj);
        obj->bknown = 1;
    } else if (!obj->cursed) {
        if (!Blind) {
            str = hcolor(NH_RED);
            pline("%s%s with a%s %s aura.", Your_buf,
                  aobjnam(obj, "harshly glow"),
                  strchr(vowels, *str) ? "n" : "", str);
        }
        curse(obj);
        obj->bknown = 1;
    } else {
        if (obj->bknown) {
            pline("That object is already cursed!");
            return 0;
        }
        obj->bknown = 1;
        pline_The("aura fades.");
    }
    update_inventory();
    return 1;
}

staticfn int
tech_eviscerate(int tech_no)
{
    /* only empty handed, in natural form */
    if (Upolyd || uwep || uarmg) {
        You_cant("do this while %s!", Upolyd ? "polymorphed"
                                      : uwep ? "holding a weapon"
                                             : "wearing gloves");
        return 0;
    }
    Your("fingernails extend into claws!");
    aggravate();
    techt_inuse(tech_no) = d(2, 4) + (techlev(tech_no) / 5) + 2;
    gu.unweapon = TRUE; /* "You begin slashing monsters with your claws" */
    return 1;
}

staticfn int
tech_berserk(int tech_no)
{
    You("fly into a berserk rage!");
    techt_inuse(tech_no) = d(2, 8) + (techlev(tech_no) / 5) + 2;
    incr_itimeout(&HFast, techt_inuse(tech_no));
    return 1;
}

staticfn int
tech_icearmor(int tech_no)
{
    pline("A layer of ice forms around you!");
    if (uarm || uarms)
        pline("It won't protect you much with %s in the way, though.",
              uarm ? "your body armor" : "your shield");
    techt_inuse(tech_no) = d(techlev(tech_no) + 2, 6) + d(1, 8) + 2;
    find_ac();
    return 1;
}

staticfn int
tech_reinforce(void)
{
    /* spellcasters can refresh their memory of a known spell */
    if (Hallucination || Stunned || Confusion) {
        You_cant("concentrate right now!");
        return 0;
    }
    You("concentrate...");
    return studyspell() ? 1 : 0;
}

staticfn int
tech_flurry(int tech_no)
{
    Your("%s %s become blurs as they reach for your quiver!",
         uarmg ? "gloved" : "bare", makeplural(body_part(HAND)));
    techt_inuse(tech_no) = rnd((techlev(tech_no) / 6) + 1) + 2;
    return 1;
}

staticfn int
tech_appraisal(void)
{
    if (!uwep) {
        You("are not wielding anything!");
        return 0;
    }
    if (uwep->known && uwep->rknown && uwep->dknown) {
        You("already know all there is to know about %s.", yname(uwep));
        return 0;
    }
    You("examine %s.", doname(uwep));
    uwep->known = 1;
    uwep->rknown = 1;
    uwep->dknown = 1;
    You("discover it is %s.", doname(uwep));
    update_inventory();
    return 1;
}

staticfn int
tech_practice(void)
{
    if (!uwep || weapon_type(uwep) == P_NONE) {
        You("are not wielding a weapon!");
        return 0;
    }
    if (!uwep->known && not_fully_identified(uwep)) {
        You("examine %s.", doname(uwep));
        if (rnd(15) <= ACURR(A_INT)) {
            makeknown(uwep->otyp);
            uwep->known = 1;
            You("discover it is %s.", doname(uwep));
            update_inventory();
        } else {
            pline("Unfortunately, you didn't learn anything new.");
        }
    }
    return practice_weapon();
}

staticfn int
tech_primalroar(int tech_no)
{
    struct monst *mtmp;
    int i, j;

    You("let out a bloodcurdling roar!");
    aggravate();
    techt_inuse(tech_no) = d(4, 6) + techlev(tech_no) + 12;
    incr_itimeout(&HFast, techt_inuse(tech_no));

    /* nearby pets grow into their adult forms (permanently, as in
       Hack'EM, rather than for a while as in Slash'EM) */
    for (i = -5; i <= 5; i++)
        for (j = -5; j <= 5; j++) {
            if (!isok(u.ux + i, u.uy + j)
                || !(mtmp = m_at(u.ux + i, u.uy + j)))
                continue;
            if (mtmp->mtame && !mtmp->isminion) {
                int type = little_to_big(monsndx(mtmp->data));

                if (type != monsndx(mtmp->data)
                    && !(svm.mvitals[type].mvflags & G_GENOD))
                    (void) newcham(mtmp, &mons[type], NC_SHOW_MSG);
            }
        }
    return 1;
}

staticfn int
tech_liquidleap(int tech_no)
{
    coord cc;
    struct monst *mtmp;
    int dx, dy, range;
    coordxy sx, sy;
    boolean shopdamage = FALSE;

    if (Unchanging) {
        if (!Hallucination)
            Your("form is too rigid to leap!");
        else
            You("feel a little too stiff.");
        return 0;
    }
    if (u.uswallow) {
        You("slosh around a little.");
        return 0;
    }
    if (u.usteed) {
        You_cant("flow away from %s while you are riding.",
                 mon_nam(u.usteed));
        return 0;
    }
    pline("Where do you want to leap to?");
    cc.x = sx = u.ux;
    cc.y = sy = u.uy;
    if (getpos(&cc, TRUE, "the desired position") < 0)
        return 0; /* user pressed ESC */

    dx = cc.x - u.ux;
    dy = cc.y - u.uy;
    if ((dx && dy && dx != dy && dx != -dy) || (!dx && !dy)) {
        You("can only leap in straight lines!");
        return 0;
    } else if (distu(cc.x, cc.y) > 19 + techlev(tech_no)) {
        pline("Too far!");
        return 0;
    } else if (!isok(cc.x, cc.y) || !couldsee(cc.x, cc.y)
               || m_at(cc.x, cc.y) || IS_OBSTRUCTED(levl[cc.x][cc.y].typ)
               || sobj_at(BOULDER, cc.x, cc.y) || closed_door(cc.x, cc.y)) {
        You_cant("flow there!");
        return 0;
    }
    if (is_pool(cc.x, cc.y) && !Levitation && !Flying && !Wwalking
        && !paranoid_query(ParanoidSwim, "Really leap into the water?"))
        return 0;
    if (is_lava(cc.x, cc.y) && !Levitation && !Flying
        && !paranoid_query(ParanoidSwim, "Really leap into the lava?"))
        return 0;

    You("liquify!");
    if (Punished) {
        You("slip out of the iron chain.");
        unpunish();
    }
    if (u.utrap) {
        switch (u.utraptype) {
        case TT_BEARTRAP:
            You("slide out of the bear trap.");
            break;
        case TT_PIT:
            You("leap from the pit!");
            break;
        case TT_WEB:
            You("flow through the web!");
            break;
        case TT_LAVA:
            You("separate from the lava!");
            break;
        case TT_INFLOOR:
        case TT_BURIEDBALL:
            You("ooze out of the %s!", surface(u.ux, u.uy));
            break;
        default:
            break;
        }
        reset_utrap(FALSE);
    }
    if (u.ustuck) {
        You("slip out of %s grasp.", s_suffix(mon_nam(u.ustuck)));
        set_ustuck((struct monst *) 0);
    }

    /* burn the things in the path */
    range = dx ? abs(dx) : abs(dy);
    dx = sgn(dx), dy = sgn(dy);
    tmp_at(DISP_BEAM, zapdir_to_glyph(dx, dy, TECH_ZT_ACID));
    while (range-- > 0) {
        sx += dx, sy += dy;
        tmp_at(sx, sy);
        nh_delay_output();
        if ((mtmp = m_at(sx, sy)) != 0 && !DEADMONSTER(mtmp)) {
            int chance = rn2(20);

            if (chance && (3 - chance) <= AC_VALUE(find_mac(mtmp))) {
                setmangry(mtmp, TRUE);
                You("catch %s in your acid trail!", mon_nam(mtmp));
                if (!resists_acid(mtmp)) {
                    int tmp = 1 + d(2, 4)
                              + rn2((techlev(tech_no) / 5) + 1);

                    if (!Blind)
                        pline_The("acid burns %s!", mon_nam(mtmp));
                    (void) tech_damage_mon(mtmp, tmp);
                } else if (!Blind) {
                    pline_The("acid doesn't affect %s!", mon_nam(mtmp));
                }
            }
        }
        /* interact with dungeon features */
        (void) zap_over_floor(sx, sy, TECH_ZT_ACID, &shopdamage, FALSE, 0);
        /* a little Sokoban guilt... */
        if (Sokoban) {
            struct trap *ttmp = t_at(sx, sy);

            if ((ttmp && (is_pit(ttmp->ttyp) || is_hole(ttmp->ttyp)))
                || levl[sx][sy].typ == IRONBARS)
                sokoban_guilt();
        }
    }
    tmp_at(DISP_END, 0);
    if (shopdamage)
        pay_for_damage("dissolve", FALSE);

    You("reform!");
    teleds(cc.x, cc.y, TELEDS_NO_FLAGS);
    nomul(-1);
    gm.multi_reason = "liquid leaping";
    gn.nomovemsg = "";
    return 1;
}

staticfn int
tech_raisezombies(void)
{
    struct monst *mtmp;
    struct obj *obj, *otmp;
    int i, j, nraised = 0;

    You("chant the ancient curse...");
    for (i = -1; i <= 1; i++)
        for (j = -1; j <= 1; j++) {
            coordxy x = u.ux + i, y = u.uy + j;

            if (!isok(x, y))
                continue;
            /* reviving changes the pile, so look it over again after
               each corpse; a corpse that fails to rise has become an
               undead one and won't be tried again */
            for (;;) {
                int zmndx = NON_PM;

                for (obj = svl.level.objects[x][y]; obj; obj = otmp) {
                    otmp = obj->nexthere;
                    if (obj->otyp != CORPSE || obj->corpsenm < LOW_PM)
                        continue;
                    /* only undead are raised */
                    zmndx = zombie_form(&mons[obj->corpsenm]);
                    if (zmndx != NON_PM
                        && !(svm.mvitals[zmndx].mvflags & G_GENOD))
                        break;
                }
                if (!obj)
                    break;
                /* keep the proportion of oeaten to cnutrit, so that the
                   zombie's hit points reflect how much corpse was left */
                if (obj->oeaten)
                    obj->oeaten = eaten_stat(mons[zmndx].cnutrit, obj);
                obj->corpsenm = zmndx;
                if ((mtmp = revive(obj, TRUE)) != 0) {
                    nraised++;
                    if (!resist(mtmp, SPBOOK_CLASS, 0, TELL)
                        && tamedog(mtmp, (struct obj *) 0, FALSE)) {
                        You("dominate %s!", mon_nam(mtmp));
                    } else {
                        setmangry(mtmp, FALSE);
                    }
                }
            }
        }
    if (!nraised)
        pline("But there are no suitable remains nearby.");
    /* you need to recover */
    nomul(-2);
    gm.multi_reason = "recovering from an attempt to raise zombies";
    gn.nomovemsg = "";
    return 1;
}

staticfn int
tech_whistleundead(void)
{
    struct monst *mtmp, *nextmon;
    int pet_cnt = 0;
    coordxy omx, omy;

    You("whistle an eerie tune.");
    for (mtmp = fmon; mtmp; mtmp = nextmon) {
        nextmon = mtmp->nmon; /* trap might kill mon */
        if (DEADMONSTER(mtmp) || !is_undead(mtmp->data) || !mtmp->mtame)
            continue;
        /* steed is already at your location */
        if (mtmp == u.usteed)
            continue;
        /* in the open world, only undead in the neighbourhood hear it */
        if (!in_lvl_effect_bounds(mtmp->mx, mtmp->my))
            continue;
        if (mtmp->mtrapped) {
            /* no longer in previous trap (affects mintrap) */
            mtmp->mtrapped = 0;
            fill_pit(mtmp->mx, mtmp->my);
        }
        if (M_AP_TYPE(mtmp))
            seemimic(mtmp);
        omx = mtmp->mx, omy = mtmp->my;
        mnexto(mtmp, RLOC_NONE);
        if (mtmp->mx != omx || mtmp->my != omy) {
            mtmp->mundetected = 0; /* reveal non-mimic hider */
            if (canspotmon(mtmp))
                ++pet_cnt;
            if (mintrap(mtmp, NO_TRAP_FLAGS) == Trap_Killed_Mon)
                change_luck(-1);
        }
    }
    if (pet_cnt)
        pline("%s undead servant%s %s.", (pet_cnt > 1) ? "Your" : "Your",
              plur(pet_cnt), (pet_cnt > 1) ? "gather around you"
                                           : "appears at your side");
    else
        pline("Nothing answers your call.");
    return 1;
}

/* getobj callback for the revivification technique */
staticfn int
revive_ok(struct obj *obj)
{
    if (obj && obj->otyp == CORPSE)
        return GETOBJ_SUGGEST;
    return GETOBJ_EXCLUDE;
}

/* choose a corpse to revive: one here on the floor, or one carried */
staticfn struct obj *
revive_corpse_pick(void)
{
    struct obj *otmp;
    char qbuf[QBUFSZ], qsfx[QBUFSZ], c;

    if (can_reach_floor(TRUE)) {
        for (otmp = svl.level.objects[u.ux][u.uy]; otmp;
             otmp = otmp->nexthere) {
            if (otmp->otyp != CORPSE)
                continue;
            /* touching a cockatrice corpse blind and bare-handed... */
            if (will_feel_cockatrice(otmp, FALSE)) {
                feel_cockatrice(otmp, FALSE);
                return (struct obj *) 0;
            }
            Sprintf(qbuf, "There %s ", otense(otmp, "are"));
            Sprintf(qsfx, " here; revive %s?",
                    (otmp->quan == 1L) ? "it" : "one");
            (void) safe_qbuf(qbuf, qbuf, qsfx, otmp, doname, ansimpleoname,
                             (otmp->quan == 1L) ? "a corpse" : "corpses");
            if ((c = yn_function(qbuf, ynqchars, 'n', TRUE)) == 'y')
                return otmp;
            else if (c == 'q')
                return (struct obj *) 0;
        }
    }
    return getobj("revive", revive_ok, GETOBJ_NOFLAGS);
}

staticfn int
tech_revive(int tech_no)
{
    struct monst *mtmp;
    struct obj *obj;
    int num;

    if (u.uswallow) {
        You("don't have enough elbow-room to maneuver.");
        return 0;
    }
    num = 100 - techlev(tech_no); /* WAC make this depend on mon? */
    if ((Upolyd && u.mh <= num) || (!Upolyd && u.uhp <= num)) {
        You("don't have the strength to perform revivification!");
        return 0;
    }
    if (!(obj = revive_corpse_pick()))
        return 0;
    mtmp = revive(obj, TRUE);
    if (mtmp) {
        if (mtmp->isshk)
            make_happy_shk(mtmp, FALSE);
        else if (!resist(mtmp, SPBOOK_CLASS, 0, TELL))
            (void) tamedog(mtmp, (struct obj *) 0, FALSE);
    } else {
        pline("The corpse remains lifeless.");
    }
    if (Upolyd)
        u.mh -= num;
    else
        u.uhp -= num;
    disp.botl = TRUE;
    return 1;
}

staticfn int
tech_tinker(int tech_no)
{
    char qbuf[QBUFSZ];

    if (Blind) {
        You_cant("do any tinkering if you can't see!");
        return 0;
    }
    if (!uwep) {
        You("aren't holding an object to work on!");
        return 0;
    }
    if (uwep->unpaid || (uwep->quan > 1L && inv_cnt(FALSE) >= 52)) {
        You("%s.", uwep->unpaid
                     ? "had better pay for it before you tinker with it"
                     : "have no room for the result of your tinkering");
        return 0;
    }
    if (Has_contents(uwep)) {
        You("need to empty %s before you can work on it.", yname(uwep));
        return 0;
    }
    You("are holding %s.", doname(uwep));
    Snprintf(qbuf, sizeof qbuf, "Start tinkering on %s?", yname(uwep));
    if (y_n(qbuf) != 'y')
        return 0;
    You("start working on %s.", yname(uwep));
    tech_delay = (techlev(tech_no) >= 10) ? -75 + techlev(tech_no)
                                          : -150 + techlev(tech_no);
    tech_occ_id = T_TINKER;
    set_occupation(tech_occupation, "tinkering", 0);
    return 1;
}

staticfn int
tech_rage(int tech_no)
{
    int num;

    if (Upolyd) {
        You_cant("focus your anger!");
        return 0;
    }
    You_feel("the anger inside you erupt!");
    num = 50 + (4 * techlev(tech_no));
    techt_inuse(tech_no) = num + 1;
    u.uhpmax += num;
    u.uhp += num;
    disp.botl = TRUE;
    return 1;
}

staticfn int
tech_drawenergy(void)
{
    if (u.uen >= u.uenmax) {
        if (Hallucination)
            You("are fully charged!");
        else
            You_cant("hold any more energy!");
        return 0;
    }
    You("begin drawing energy from your surroundings!");
    tech_delay = -15;
    tech_occ_id = T_DRAW_ENERGY;
    set_occupation(tech_occupation, "drawing energy", 0);
    return 1;
}

/* charge saber (Jedi; Slash'EM, SlashTHEM, Hack'EM): ten turns of
   concentration pour all of the hero's energy into the wielded lightsaber
   (see charge_saber_occ()) */
staticfn int
tech_chargesaber(void)
{
    if (!uwep || !is_lightsaber(uwep)) {
        You("are not holding a lightsaber!");
        return 0;
    }
    if (is_art(uwep, ART_LIGHTSABER_PROTOTYPE)) {
        pline("%s power cell never needs charging.",
              s_suffix(The(xname(uwep))));
        return 0;
    }
    if (u.uen < 5) {
        You("lack the concentration to charge %s.  "
            "You need at least 5 points of energy!", the(xname(uwep)));
        return 0;
    }
    You("start charging %s.", the(xname(uwep)));
    tech_delay = -10;
    tech_occ_id = T_CHARGE_SABER;
    set_occupation(tech_occupation, "charging", 0);
    return 1;
}

/* the end of charge saber: the charge depends on the energy spent and the
   technique level; an experienced Jedi sometimes gets a big bonus */
staticfn int
charge_saber_occ(void)
{
    int tlevel = tech_level(T_CHARGE_SABER);
    long amount;

    if (tech_delay) {
        tech_delay++;
        return 1; /* still busy */
    }
    if (!uwep || !is_lightsaber(uwep)
        || is_art(uwep, ART_LIGHTSABER_PROTOTYPE)) {
        /* disarmed meanwhile */
        You("have nothing to channel the Force into.");
        return 0;
    }
    amount = (long) u.uen * (long) ((tlevel / rnd(10)) + 51);
    if (tlevel >= 10 && !rn2(5)) {
        You("manage to channel the Force perfectly!");
        amount += 1500L; /* jackpot */
    } else {
        You("channel the Force into %s.", the(xname(uwep)));
    }
    (void) charge_lightsaber(uwep, amount, 0L);
    u.uen = 0;
    disp.botl = TRUE;
    return 0;
}

staticfn int
tech_chiheal(int tech_no)
{
    if (u.uen < 1) {
        You("are too weak to attempt this!  "
            "You need at least one point of energy!");
        return 0;
    }
    You("direct your internal energy to restoring your body!");
    techt_inuse(tech_no) = techlev(tech_no) * 2 + 4;
    return 1;
}

staticfn int
tech_disarm(int tech_no)
{
    struct monst *mtmp;
    struct obj *obj;
    int num, skill;

    if (!uwep || (skill = weapon_type(uwep)) == P_NONE
        || skill == P_BARE_HANDED_COMBAT) {
        You("aren't wielding a proper weapon!");
        return 0;
    }
    if (P_SKILL(skill) < P_SKILLED || Blind) {
        You("aren't capable of doing this!");
        return 0;
    }
    if (u.uswallow) {
        pline("What do you think %s is?  A sword swallower?",
              mon_nam(u.ustuck));
        return 0;
    }
    if (!getdir((char *) 0))
        return 0;
    if (!u.dx && !u.dy) {
        pline("Why don't you try wielding something else instead.");
        return 0;
    }
    mtmp = tech_target();
    if (!mtmp || !canspotmon(mtmp)) {
        You("don't see anything there!");
        return 0;
    }
    obj = MON_WEP(mtmp); /* can be null */
    if (!obj) {
        You_cant("disarm an unarmed foe!");
        return 0;
    }
    if (!mon_visible(mtmp)) {
        You_cant("see %s weapon!", s_suffix(mon_nam(mtmp)));
        return 0;
    }
    num = (rn2(techlev(tech_no) + 15) * (P_SKILL(skill) - P_SKILLED + 1))
          / 10;
    You("attempt to disarm %s...", mon_nam(mtmp));
    setmangry(mtmp, TRUE);
    /* can't yank out cursed items */
    if (num > 0 && (!Fumbling || !rn2(10)) && !obj->cursed) {
        int roll = rn2(num + 1);

        if (roll > 3)
            roll = 3;
        extract_from_minvent(mtmp, obj, TRUE, FALSE);
        switch (roll) {
        case 2:
            /* to the floor near you */
            You("knock %s %s to the %s!", s_suffix(mon_nam(mtmp)),
                xname(obj), surface(u.ux, u.uy));
            if (obj->otyp == CRYSKNIFE
                && (!obj->oerodeproof || !rn2(10))) {
                obj->otyp = WORM_TOOTH;
                obj->oerodeproof = 0;
            }
            place_object(obj, u.ux, u.uy);
            stackobj(obj);
            newsym(u.ux, u.uy);
            break;
        case 3:
            /* right into your inventory */
            You("snatch %s %s!", s_suffix(mon_nam(mtmp)), xname(obj));
            if (obj->otyp == CORPSE && touch_petrifies(&mons[obj->corpsenm])
                && !uarmg && !Stone_resistance
                && !(poly_when_stoned(gy.youmonst.data)
                     && polymon(PM_STONE_GOLEM))) {
                char kbuf[BUFSZ];

                Sprintf(kbuf, "%s corpse", an(mons[obj->corpsenm].pmnames[NEUTRAL]));
                pline("Snatching %s is a fatal mistake.", kbuf);
                instapetrify(kbuf);
            }
            obj = hold_another_object(obj, "You drop %s!", doname(obj),
                                      (const char *) 0);
            break;
        default:
            /* to the floor beneath the monster */
            You("knock %s from %s grasp!", the(xname(obj)),
                s_suffix(mon_nam(mtmp)));
            if (obj->otyp == CRYSKNIFE
                && (!obj->oerodeproof || !rn2(10))) {
                obj->otyp = WORM_TOOTH;
                obj->oerodeproof = 0;
            }
            place_object(obj, mtmp->mx, mtmp->my);
            stackobj(obj);
            newsym(mtmp->mx, mtmp->my);
            break;
        }
    } else if (mtmp->mcanmove && !mtmp->msleeping) {
        pline("%s evades your attack.", Monnam(mtmp));
    } else {
        You("fail to dislodge %s %s.", s_suffix(mon_nam(mtmp)), xname(obj));
    }
    wakeup(mtmp, TRUE);
    if (!mtmp->mcanmove && !rn2(10)) {
        mtmp->mcanmove = 1;
        mtmp->mfrozen = 0;
    }
    return 1;
}

/* short range paralysis by stare (vampires) */
staticfn int
tech_dazzle(int tech_no)
{
    struct monst *mtmp = (struct monst *) 0;
    int i;

    if (Blind) {
        You_cant("see anything!");
        return 0;
    }
    if (!getdir((char *) 0))
        return 0;
    if (!u.dx && !u.dy) {
        You_cant("see yourself!");
        return 0;
    }
    for (i = 1; i <= (techlev(tech_no) / 8) + 1
                && isok(u.ux + (i * u.dx), u.uy + (i * u.dy)); i++) {
        mtmp = m_at(u.ux + (i * u.dx), u.uy + (i * u.dy));
        if (mtmp && canseemon(mtmp))
            break;
        if (!couldsee(u.ux + (i * u.dx), u.uy + (i * u.dy)))
            break;
    }
    if (!mtmp || !canseemon(mtmp)) {
        You("fail to make eye contact with anything!");
        return 0;
    }
    You("stare at %s.", mon_nam(mtmp));
    if (!haseyes(mtmp->data)) {
        pline("...but %s has no eyes!", mon_nam(mtmp));
    } else if (!mtmp->mcansee) {
        pline("...but %s cannot see you!", mon_nam(mtmp));
    } else if ((rn2(6) + rn2(6) + (techlev(tech_no) - mtmp->m_lev)) > 10) {
        You("dazzle %s!", mon_nam(mtmp));
        paralyze_monst(mtmp, rnd(10));
    } else {
        pline("%s breaks the stare!", Monnam(mtmp));
    }
    return 1;
}

staticfn int
tech_souleater(int tech_no)
{
    struct monst *mtmp;
    int weapon_modifier,
        num = Upolyd ? (u.mhmax / 2) : (u.uhpmax / 2);
    boolean isweapon, isedged;

    if ((!Upolyd && u.uhp <= num) || (Upolyd && u.mh <= num)) {
        You("don't have the strength to invoke Souleater!  "
            "It requires at least %d hit points!", num + 1);
        return 0;
    }
    if (!uwep) {
        You("need a weapon to channel your dark energy into!");
        return 0;
    }
    isweapon = (uwep->oclass == WEAPON_CLASS || is_weptool(uwep));
    isedged = (is_pick(uwep) || (objects[uwep->otyp].oc_dir & (PIERCE | SLASH)));
    if (is_missile(uwep) || is_ammo(uwep) || (!isweapon && !isedged)) {
        You("need a proper weapon to channel your dark energy into!");
        return 0;
    }
    You("unleash a burst of dark energy!");
    /* works against anything hostile in line of sight */
    for (mtmp = fmon; mtmp; mtmp = mtmp->nmon) {
        if (DEADMONSTER(mtmp) || mtmp->mpeaceful || mtmp == u.usteed)
            continue;
        if (!couldsee(mtmp->mx, mtmp->my) || distu(mtmp->mx, mtmp->my)
                                                 > BOLT_LIM * BOLT_LIM)
            continue;
        if (nonliving(mtmp->data) && !is_undead(mtmp->data))
            continue; /* no soul to eat */
        if (canspotmon(mtmp))
            pline("%s screams in agony!", Monnam(mtmp));
        mtmp->mhp -= mtmp->mhp / 4;
        if (mtmp->mhp < 1)
            mtmp->mhp = 1;
        wakeup(mtmp, FALSE);
    }
    /* instead of being limited to Soulthief, any artifact that drains
       life is especially good at it */
    weapon_modifier = attacks(AD_DRLI, uwep) ? 5 : 1;
    /* (one more turn than in Hack'EM, so that there is always time for
       at least one blow before the flames die away) */
    techt_inuse(tech_no) = (techlev(tech_no) / 2) + weapon_modifier + 1;
    pline("Dark flames flow from %s.", yname(uwep));
    if (Upolyd)
        u.mh -= num;
    else
        u.uhp -= num;
    disp.botl = TRUE;
    return 1;
}

staticfn int
tech_jedijump(int tech_no)
{
    int cost = 10;

    if (u.uen < cost) {
        You_cant("channel the Force around you.  "
                 "Jedi jumps require %d points of energy!", cost);
        return 0;
    }
    if (!(jump((techlev(tech_no) / 5) + 1) & ECMD_TIME))
        return 0;
    u.uen -= cost;
    disp.botl = TRUE;
    return 1;
}

/* telekinesis on a trap: disarm or spring it; TRUE if time was used */
staticfn boolean
tele_trap_handle(struct trap *ttmp)
{
    struct monst *mtmp;
    coordxy x = ttmp->tx, y = ttmp->ty;

    if (y_n("Disarm the trap?") == 'y') {
        switch (ttmp->ttyp) {
        case BEAR_TRAP:
        case WEB:
        case LANDMINE:
        case DART_TRAP:
        case ARROW_TRAP:
            break;
        default:
            You_cant("disable that trap.");
            return FALSE;
        }
        if (rnl(20) >= 10) {
            pline_The("Force fails you this time!");
            return TRUE;
        }
        if ((mtmp = m_at(x, y)) != 0 && mtmp->mtrapped) {
            mtmp->mtrapped = 0;
            You("free %s.", mon_nam(mtmp));
        }
        switch (ttmp->ttyp) {
        case BEAR_TRAP:
            You("disarm %s bear trap.", the_your[ttmp->madeby_u]);
            cnv_trap_obj(BEARTRAP, 1, ttmp, FALSE);
            break;
        case WEB:
            You("tear %s web apart.", the_your[ttmp->madeby_u]);
            deltrap(ttmp);
            break;
        case LANDMINE:
            You("disarm %s land mine.", the_your[ttmp->madeby_u]);
            cnv_trap_obj(LAND_MINE, 1, ttmp, FALSE);
            break;
        case DART_TRAP:
            You("disarm %s trap.", the_your[ttmp->madeby_u]);
            cnv_trap_obj(DART, 50 - rnl(50), ttmp, FALSE);
            break;
        case ARROW_TRAP:
            You("disarm %s trap.", the_your[ttmp->madeby_u]);
            cnv_trap_obj(ARROW, 50 - rnl(50), ttmp, FALSE);
            break;
        }
        newsym(x, y);
        return TRUE;
    } else if (y_n("Spring this trap?") == 'y') {
        switch (ttmp->ttyp) {
        case LANDMINE:
            You("trigger the land mine.");
            pline("KAABLAMM!!!");
            blow_up_landmine(ttmp);
            newsym(x, y);
            break;
        case ROLLING_BOULDER_TRAP: {
            int style = ROLL | (ttmp->tseen ? LAUNCH_KNOWN : 0);

            You("trigger the trap!");
            if (!launch_obj(BOULDER, ttmp->launch.x, ttmp->launch.y,
                            ttmp->launch2.x, ttmp->launch2.y, style)) {
                deltrap(ttmp);
                newsym(x, y);
                pline("But no boulder was released.");
            }
            break;
        }
        case SQKY_BOARD:
            pline("A board in the distance %s.",
                  Deaf ? "vibrates" : "squeaks loudly");
            wake_nearto(x, y, 40);
            break;
        default:
            You_cant("spring this trap.");
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}

staticfn int
tech_telekinesis(void)
{
    struct obj *otmp;
    struct trap *ttmp;
    coord cc;
    int tries;
    char buf[BUFSZ];

    cc.x = u.ux, cc.y = u.uy;
    for (tries = 0; tries < 10; tries++) {
        pline("Apply telekinesis where?");
        if (getpos(&cc, TRUE, "the spot to apply telekinesis to") < 0) {
            You("release the Force back into your surroundings.");
            return 0;
        }
        if (u_at(cc.x, cc.y)) {
            You("don't need the Force for that.");
            continue;
        }
        if (!cansee(cc.x, cc.y)) {
            You_cant("see what's there!");
            continue;
        }
        if (distu(cc.x, cc.y) > BOLT_LIM * BOLT_LIM) {
            pline("That's too far away.");
            continue;
        }
        if ((ttmp = t_at(cc.x, cc.y)) != 0 && ttmp->tseen
            && y_n("Handle the trap there?") == 'y') {
            if (tele_trap_handle(ttmp))
                return 1;
            continue;
        } else if ((otmp = svl.level.objects[cc.x][cc.y]) != 0) {
            if (y_n(safe_qbuf(buf, "Pick up ", "?", otmp, doname,
                              ansimpleoname, "that")) != 'y')
                continue;
            You("draw %s toward you with the Force.", the(xname(otmp)));
            (void) pickup_object(otmp, otmp->quan, TRUE);
            newsym(cc.x, cc.y);
            return 1;
        } else {
            You_cant("do anything %sthere.", ttmp ? "else " : "");
        }
    }
    pline("You lose your focus.");
    return 0;
}

staticfn int
tech_spirittempest(int tech_no)
{
    int num, dmg, blasts = (u.ulevel > 20) ? (3 + rn2(4)) : 1, tries;
    boolean didblast = FALSE;
    coordxy x, y;

    if (Hallucination && flags.female)
        pline("There is a tempest in me!");
    else
        You("channel the spirits from deep within...");
    if (u.uen < 20) {
        pline("But it fizzles out.");
        u.uen = 0;
        disp.botl = TRUE;
        return 0;
    }
    num = 20 + d(10, (techlev(tech_no) / 3) + 1);
    /* bonus damage can't go over our available energy */
    num = (u.uen < num) ? u.uen : num;
    u.uen -= num;
    disp.botl = TRUE;
    num = spell_damage_bonus(num);

    /* a throwback to the sigil of tempest in Slash'EM: several blasts
       around the hero at experience level 21 and up */
    while (blasts--) {
        for (tries = 0; tries < 20; tries++) {
            int i, j;
            struct monst *mtmp;
            boolean friendly = FALSE;

            confdir(TRUE); /* random direction */
            x = u.ux + u.dx * (2 + rn2(2));
            y = u.uy + u.dy * (2 + rn2(2));
            if (!isok(x, y) || !cansee(x, y) || IS_STWALL(levl[x][y].typ)
                || distu(x, y) <= 2)
                continue;
            /* the spirits spare you and your companions */
            for (i = -1; i <= 1 && !friendly; i++)
                for (j = -1; j <= 1; j++)
                    if (isok(x + i, y + j)
                        && (u_at(x + i, y + j)
                            || ((mtmp = m_at(x + i, y + j)) != 0
                                && mtmp->mpeaceful && canspotmon(mtmp)))) {
                        friendly = TRUE;
                        break;
                    }
            if (!friendly)
                break;
        }
        if (tries == 20)
            continue;
        dmg = d(3, 6) + num;
        explode(x, y, TECH_ZT_SPELL_MM, dmg, SPBOOK_CLASS,
                EXPL_MAGICAL);
        didblast = TRUE;
        if (u.uhp < 1)
            break;
    }
    if (!didblast)
        pline("The spirits find nothing to vent their fury upon.");
    return 1;
}

/* a wand of striking-like push (Jedi) */
staticfn int
tech_forcepush(int tech_no)
{
    struct monst *mon;
    int range = 1 + (techlev(tech_no) / 3), i;
    coordxy sx, sy;

    /* need at least one free hand */
    if (u.twoweap && uswapwep) {
        You_cant("do this while wielding two weapons!");
        return 0;
    } else if (uarms && uwep && bimanual(uwep)) {
        You("need a free %s to do this!", body_part(HAND));
        return 0;
    }
    if (!getdir((char *) 0))
        return 0;
    if (range > 3)
        range = 3;
    if (u.uswallow && u.ustuck) {
        mon = u.ustuck;
        You("blast a hole in %s!", mon_nam(mon));
        expels(mon, mon->data, TRUE);
        return 1;
    }
    if (!u.dx && !u.dy) {
        if (u.dz)
            You("push the %s away with the Force.",
                (u.dz > 0) ? surface(u.ux, u.uy) : ceiling(u.ux, u.uy));
        else
            You("push against yourself.  Nothing happens.");
        return 0;
    }
    You("push with the Force!");
    sx = u.ux, sy = u.uy;
    for (i = 0; i < range; i++) {
        sx += u.dx, sy += u.dy;
        if (!isok(sx, sy) || IS_STWALL(levl[sx][sy].typ)
            || closed_door(sx, sy))
            break;
        if ((mon = m_at(sx, sy)) != 0 && !DEADMONSTER(mon)) {
            if (canspotmon(mon))
                pline("%s gets blasted by the Force!", Monnam(mon));
            setmangry(mon, TRUE);
            wakeup(mon, TRUE);
            mhurtle(mon, u.dx, u.dy, 1 + rn2(1 + (techlev(tech_no) / 3)));
            break;
        }
    }
    return 1;
}

/*
 * Pickpocketing (Hack'EM's thievery): steal one item a monster carries
 * but doesn't wear or wield.  Hack'EM's thievery skill is replaced by the
 * technique's level.
 */
staticfn int
tech_pickpocket(int tech_no)
{
    struct monst *mtmp;
    struct obj *otmp;
    int i = rn2(10), dex = ACURR(A_DEX), dex_pick = 0, other = 0, enc = 0,
        cnt, skill = min(P_EXPERT, P_BASIC + techlev(tech_no) / 6);

    if (!getdir((char *) 0))
        return 0;
    if (!u.dx && !u.dy) {
        You("check your own pockets.  Everything seems to be there.");
        return 0;
    }
    if (u.uswallow) {
        pline("What exactly were you planning on stealing?  Its stomach?");
        return 0;
    }
    mtmp = tech_target();
    if (!mtmp || !canspotmon(mtmp)) {
        pline("No one is there!");
        return 0;
    }
    if (Upolyd) {
        You("must be in your natural form to pickpocket.");
        return 0;
    }
    if (uwep) {
        You_cant("do this while holding a weapon.");
        return 0;
    }
    if (mtmp->mtame) {
        /* pets are off-limits, since #loot can be used to give them as
           much as they can carry */
        You_cant("bring yourself to steal from %s.", mon_nam(mtmp));
        return 0;
    }
    if (mtmp->isshk && !strcmp(shkname(mtmp), "Izchak")) {
        You("find yourself unable to steal from %s.", mon_nam(mtmp));
        return 0;
    }
    /* pick an item carried but not worn or wielded */
    for (cnt = 0, otmp = mtmp->minvent; otmp; otmp = otmp->nobj)
        if (!otmp->owornmask)
            cnt++;
    if (!cnt) {
        pline("%s has nothing for you to %s.", Monnam(mtmp),
              rn2(2) ? "steal" : "pickpocket");
        return 1;
    }
    cnt = rnd(cnt);
    for (otmp = mtmp->minvent; otmp; otmp = otmp->nobj)
        if (!otmp->owornmask && !--cnt)
            break;
    if (!otmp)
        return 1;

    You("%s to %s %s.", rn2(2) ? "try" : "attempt",
        rn2(2) ? "steal from" : "pickpocket", mon_nam(mtmp));

    /* greased objects are difficult to get a grip on */
    if ((otmp->greased || otmp->otyp == OILSKIN_CLOAK
         || otmp->otyp == OILSKIN_SACK) && (!otmp->cursed || rn2(4))) {
        Your("%s slip off of %s %s!", makeplural(body_part(HAND)),
             s_suffix(mon_nam(mtmp)),
             otmp->greased ? "greased" : "slippery");
        if (otmp->greased && !rn2(2)) {
            pline_The("grease wears off.");
            otmp->greased = 0;
        }
        return 1;
    }

    /* dexterity directly affects how successful pickpocketing is */
    if (dex <= 6)
        dex_pick += 3;
    else if (dex <= 9)
        dex_pick += 2;
    else if (dex <= 15)
        dex_pick += 0;
    else if (dex <= 18)
        dex_pick -= 1;
    else if (dex <= 21)
        dex_pick -= 2;
    else if (dex <= 24)
        dex_pick -= 3;
    else
        dex_pick -= 4;
    /* bonus if the target can't see the thief */
    if (!m_canseeu(mtmp))
        other -= 2;
    /* small thieves do better against big targets */
    if ((Race_if(PM_GNOME) || race_is("Dop") || race_is("Gho"))
        && mtmp->data->msize >= MZ_LARGE)
        other -= 1;
    switch (near_capacity()) {
    case UNENCUMBERED:
        break;
    case SLT_ENCUMBER:
        enc += 2;
        break;
    case MOD_ENCUMBER:
        enc += 6;
        break;
    case HVY_ENCUMBER:
        enc += 10;
        break;
    default:
        enc += 20;
        break;
    }
    if (helpless(mtmp) || mtmp->mfrozen)
        other -= 5;
    if (mtmp->mconf || mtmp->mstun)
        other -= 3;
    if (uarms)
        other += 2;
    if (uarm && is_metallic(uarm) && objects[uarm->otyp].oc_bulky)
        other += 3;
    if (Wounded_legs)
        other += 5;
    if (u.usteed)
        other += 5;
    if (Glib)
        other += 7;
    if (Fumbling)
        other += 10;
    if (Confusion || Stunned)
        other += 20;

    if (i + dex_pick + other + enc > skill) {
        if (Confusion || Stunned)
            You("are in no shape to %s anything.",
                rn2(2) ? "pickpocket" : "steal");
        else
            Your("attempt to %s %s %s.", rn2(2) ? "pickpocket" : "steal from",
                 mon_nam(mtmp), rn2(2) ? "failed" : "was unsuccessful");
        /* the victim may notice */
        if (mtmp->mpeaceful && rnd(6) > skill) {
            if (canseemon(mtmp))
                pline("%s notices your pickpocketing attempt and gets "
                      "angry!", Monnam(mtmp));
            setmangry(mtmp, TRUE);
        } else if (!mtmp->mpeaceful && !rn2(3)) {
            wakeup(mtmp, TRUE);
        }
        return 1;
    }

    /* success */
    if (otmp->oartifact && !Blind)
        find_artifact(otmp);
    extract_from_minvent(mtmp, otmp, TRUE, FALSE);
    if (otmp->otyp == CORPSE && otmp->corpsenm >= LOW_PM
        && touch_petrifies(&mons[otmp->corpsenm]) && !uarmg
        && !Stone_resistance) {
        char kbuf[BUFSZ];

        Sprintf(kbuf, "stolen %s corpse",
                mons[otmp->corpsenm].pmnames[NEUTRAL]);
        otmp = hold_another_object(otmp, "You snatched but dropped %s.",
                                   doname(otmp), "You steal: ");
        instapetrify(kbuf);
        return 1;
    }
    (void) hold_another_object(otmp, "You snatched but dropped %s.",
                               doname(otmp), "You steal: ");
    exercise(A_DEX, TRUE);
    return 1;
}

/* tumble past a monster, swapping places with it (Hack'EM's pirates) */
staticfn int
tech_tumble(int tech_no)
{
    struct monst *mtmp;
    int roll, tumbleskill = (techlev(tech_no) / 5) + P_BASIC;
    coordxy tx, ty, mx, my;

    if (u.uswallow) {
        You("tumble in place.");
        return 1;
    }
    if (Underwater) {
        You_cant("tumble in the water!");
        return 0;
    }
    if (Levitation || (Flying && !Breathless)) {
        You_cant("tumble in the air!");
        return 0;
    }
    if (u.utrap || u.ustuck) {
        You_cant("tumble until you extricate yourself.");
        return 0;
    }
    if (u.usteed) {
        You_cant("tumble while riding.");
        return 0;
    }
    if (Punished) {
        You_cant("tumble with a ball and chain dragging behind you.");
        return 0;
    }
    if (Fumbling) {
        You("slip and land on your %s!", body_part(HEAD));
        losehp(Maybe_Half_Phys(rnd(20)), "ill-advised gymnastics", KILLED_BY);
        return 1;
    }
    if (!getdir((char *) 0) || !isok(u.ux + u.dx, u.uy + u.dy))
        return 0;
    if (!u.dx && !u.dy) {
        You("do a somersault.");
        return 1;
    }
    mtmp = tech_target();
    if (!mtmp || !canspotmon(mtmp)) {
        You("don't see anyone to tumble past in that direction.");
        return 0;
    }
    if (mtmp->mpeaceful) {
        pline("That would be very rude.");
        return 0;
    }
    if (mtmp->wormno || mtmp->data->msize >= MZ_HUGE) {
        pline("%s is too big to tumble past.", Monnam(mtmp));
        return 0;
    }
    mx = mtmp->mx, my = mtmp->my;
    if (!test_move(u.ux, u.uy, u.dx, u.dy, TEST_MOVE)) {
        You("don't have room to tumble past %s.", mon_nam(mtmp));
        return 0;
    }
    if (is_pool(mx, my) && !Wwalking && !Swimming
        && !paranoid_query(ParanoidSwim, "Really tumble into the water?"))
        return 0;
    if (is_lava(mx, my)
        && !paranoid_query(ParanoidSwim, "Really tumble into the lava?"))
        return 0;
    roll = rn2(6);
    if (roll > tumbleskill) {
        You(Hallucination ? "are too busy tripping!" : "trip!");
        return 1;
    }

    You("tumble past %s.", mon_nam(mtmp));
    tx = u.ux, ty = u.uy;
    u.ux0 = u.ux, u.uy0 = u.uy;
    mtmp->mtrapped = 0;
    mtmp->mundetected = 0;
    remove_monster(mx, my);
    u_on_newpos(mx, my);
    place_monster(mtmp, tx, ty);
    newsym(tx, ty);
    newsym(mx, my);
    gv.vision_full_recalc = 1;
    /* discombobulate them, unless their new spot did worse */
    if (!minliquid(mtmp) && mintrap(mtmp, NO_TRAP_FLAGS) != Trap_Killed_Mon
        && !DEADMONSTER(mtmp) && rn2(5)) {
        mtmp->mconf = 1;
        if (canseemon(mtmp))
            pline("%s looks confused.", Monnam(mtmp));
    }
    spoteffects(TRUE);
    if (roll == tumbleskill) {
        nomul(-rnd(2));
        gm.multi_reason = "recovering from a tumble";
        gn.nomovemsg = "You recover from your tumble.";
    }
    return 1;
}

/* break a monster's weapon (Hack'EM's pirates) */
staticfn int
tech_sunder(int tech_no)
{
    struct obj *otmp;
    struct monst *mtmp;
    int roll, skill = (techlev(tech_no) / 5) + P_BASIC;

    if (skill > P_EXPERT)
        skill = P_EXPERT;
    if (u.uswallow) {
        pline("Try attacking, instead.");
        return 0;
    }
    if (!getdir((char *) 0) || !isok(u.ux + u.dx, u.uy + u.dy))
        return 0;
    if (!u.dx && !u.dy) {
        if (uwep)
            You_cant("break your own weapon!");
        else
            pline("Break your %s?  You need those!",
                  makeplural(body_part(HAND)));
        return 0;
    }
    mtmp = tech_target();
    if (!mtmp || !canspotmon(mtmp)) {
        You("don't see anyone with equipment to sunder!");
        return 0;
    }
    if (!(otmp = MON_WEP(mtmp))) {
        pline("%s does not have a weapon for you to sunder.", Monnam(mtmp));
        return 0;
    }
    if (mtmp->mpeaceful) {
        char qbuf[QBUFSZ];

        Sprintf(qbuf, "Really attack %s?", mon_nam(mtmp));
        if (!paranoid_query(ParanoidHit, qbuf))
            return 0;
    }
    setmangry(mtmp, TRUE);
    wakeup(mtmp, TRUE);
    roll = rn2(6);
    if (otmp->oartifact || obj_resists(otmp, 0, 0)) {
        pline("%s resists your attempt to sunder it!", The(xname(otmp)));
        return 1;
    }
    if (roll >= skill) {
        You("fail to sunder %s weapon.", s_suffix(mon_nam(mtmp)));
        return 1;
    }
    You("sunder %s %s!", s_suffix(mon_nam(mtmp)), xname(otmp));
    if (otmp->otyp == CORPSE && otmp->corpsenm >= LOW_PM
        && touch_petrifies(&mons[otmp->corpsenm]) && !uwep && !uarmg
        && !Stone_resistance) {
        char kbuf[BUFSZ];

        Sprintf(kbuf, "sundering %s with an unarmed strike",
                killer_xname(otmp));
        m_useup(mtmp, otmp);
        instapetrify(kbuf);
        return 1;
    }
    m_useup(mtmp, otmp);
    if (rn2(3)) {
        pline("%s is %s!", Monnam(mtmp), rn2(2) ? "shocked" : "bewildered");
        mtmp->mconf = 1;
    }
    return 1;
}

staticfn int
tech_bloodmagic(int tech_no)
{
    You("invite a dark power into your heart!");
    techt_inuse(tech_no) = (techlev(tech_no) * 6 + 1) + 2;
    return 1;
}

staticfn int
tech_breakrock(void)
{
    coordxy x, y;

    if (!getdir((char *) 0))
        return 0;
    if (!u.dx && !u.dy) {
        You("flex your muscles.");
        return 0;
    }
    x = u.ux + u.dx, y = u.uy + u.dy;
    if (!isok(x, y) || (!sobj_at(BOULDER, x, y) && !sobj_at(STATUE, x, y))) {
        You("find nothing there to break.");
        return 0;
    }
    if (uwep || uarms) {
        You("need your bare %s to focus your qi.",
            makeplural(body_part(HAND)));
        return 0;
    }
    return do_breakrock(x, y);
}

/* ------------------------------------------------------------------ */
/* NetHack: Open World techniques                                      */
/* ------------------------------------------------------------------ */

/* Cartographer: map the surrounding terrain */
staticfn int
tech_survey(void)
{
    int radius = 8 + u.ulevel / 2;

    if (u.uswallow) {
        You("can't survey anything from in here.");
        return 0;
    }
    if (Underwater) {
        You_cant("survey the land from under water.");
        return 0;
    }
    if (svl.level.flags.nommap) {
        pline_The("lay of the land here defies all your attempts to "
                  "survey it.");
        return 1;
    }
    if (Blind)
        You("pace out your surroundings and feel your way around.");
    else
        You("survey your surroundings.");
    do_survey_mapping(u.ux, u.uy, radius, radius / 2);
    return 1;
}

/* where is the way out of this branch level? */
staticfn boolean
find_way_out(coordxy *ox, coordxy *oy, const char **what)
{
    stairway *st;
    struct trap *ttmp;
    int entry = svd.dungeons[u.uz.dnum].entry_lev, pass, best = -1, d;
    boolean outward;

    /* first pass: only ways that lead out toward where the hero came
       in; second pass: any way somewhere else */
    for (pass = 0; pass < 2 && best < 0; pass++) {
        for (st = gs.stairs; st; st = st->next) {
            if (st->tolev.dnum != u.uz.dnum)
                outward = (u.uz.dlevel == entry || st->tolev.dnum == 0);
            else
                outward = (abs(st->tolev.dlevel - entry)
                           < abs(u.uz.dlevel - entry));
            if (!pass && !outward)
                continue;
            d = distu(st->sx, st->sy);
            if (best < 0 || d < best) {
                best = d;
                *ox = st->sx, *oy = st->sy;
                *what = st->isladder ? (st->up ? "the ladder up"
                                               : "the ladder down")
                                     : (st->up ? "the up staircase"
                                               : "the down staircase");
            }
        }
        for (ttmp = gf.ftrap; ttmp; ttmp = ttmp->ntrap) {
            if (ttmp->ttyp != MAGIC_PORTAL)
                continue;
            if (ttmp->dst.dnum != u.uz.dnum)
                outward = (u.uz.dlevel == entry || ttmp->dst.dnum == 0);
            else
                outward = (abs(ttmp->dst.dlevel - entry)
                           < abs(u.uz.dlevel - entry));
            if (!pass && !outward)
                continue;
            d = distu(ttmp->tx, ttmp->ty);
            if (best < 0 || d < best) {
                best = d;
                *ox = ttmp->tx, *oy = ttmp->ty;
                *what = "a magic portal";
            }
        }
    }
    return (boolean) (best >= 0);
}

/* Cartographer: find the nearest way somewhere */
staticfn int
tech_triangulate(void)
{
    coordxy x, y;
    const char *what = "";
    xint16 dnum;
    boolean found = FALSE;

    if (u.uswallow) {
        You("can't get your bearings in here.");
        return 0;
    }
    if (Stunned || Confusion || Hallucination) {
        Your("sense of direction is a little too muddled right now.");
        return 0;
    }
    You("take your bearings.");
    if (In_overworld) {
        if (ow_nearest_portal(u.ux, u.uy, &x, &y, &dnum)) {
            struct trap *ttmp = t_at(x, y);

            if (ttmp && ttmp->ttyp == MAGIC_PORTAL)
                ttmp->tseen = 1;
            map_location(x, y, 1);
            pline("The nearest magic portal, to %s, lies %d %s to the %s.",
                  the_dest(ow_portal_dest_name(dnum)),
                  tech_dist(x - u.ux, y - u.uy),
                  (tech_dist(x - u.ux, y - u.uy) == 1) ? "pace" : "paces",
                  dir_name(x - u.ux, y - u.uy));
            found = TRUE;
        }
        if (ow_nearest_town(u.ux, u.uy, &x, &y)) {
            int i, j;

            for (i = -1; i <= 1; i++)
                for (j = -1; j <= 1; j++)
                    if (isok(x + i, y + j))
                        map_location(x + i, y + j, 1);
            if (distu(x, y) <= 2 || levl[u.ux][u.uy].flavor == OWF_PAVED)
                pline("The heart of this town lies %d paces to the %s.",
                      tech_dist(x - u.ux, y - u.uy),
                      dir_name(x - u.ux, y - u.uy));
            else
                pline("The nearest town lies %d paces to the %s.",
                      tech_dist(x - u.ux, y - u.uy),
                      dir_name(x - u.ux, y - u.uy));
            found = TRUE;
        }
    } else if (find_way_out(&x, &y, &what)) {
        map_location(x, y, 1);
        if (u_at(x, y))
            pline("You are standing on %s.", what);
        else
            pline("The nearest way out is %s, %d %s to the %s.", what,
                  tech_dist(x - u.ux, y - u.uy),
                  (tech_dist(x - u.ux, y - u.uy) == 1) ? "pace" : "paces",
                  dir_name(x - u.ux, y - u.uy));
        found = TRUE;
    }
    if (!found)
        pline("But there seems to be no way anywhere from here.");
    return 1;
}

/* can the hero land at <x,y> when returning to the waymark? */
staticfn boolean
waymark_spot_ok(coordxy x, coordxy y)
{
    struct trap *t;

    if (!isok(x, y) || u_at(x, y))
        return FALSE;
    if (!In_overworld)
        return teleok(x, y, FALSE);
    /* the open world: the mark can be far away, beyond the reach of an
       ordinary teleport, but not on the far side of the Gehennom barrier
       until the hero has been there */
    if (!ow_generated(x, y)
        || (ow_past_barrier(u.ux, u.uy) != ow_past_barrier(x, y)
            && !u.uevent.gehennom_entered))
        return FALSE;
    if ((t = t_at(x, y)) != 0 && t->ttyp != VIBRATING_SQUARE
        && !((is_pit(t->ttyp) || is_hole(t->ttyp)) && (Levitation || Flying)))
        return FALSE;
    return (boolean) (goodpos(x, y, &gy.youmonst, 0) && in_out_region(x, y));
}

/* Cartographer: teleport to the waymark; TRUE if it happened */
staticfn boolean
waymark_teleport(void)
{
    coord cc;
    coordxy x = u.uwaymark_x, y = u.uwaymark_y;

    if (noteleport_level(&gy.youmonst)) {
        You_feel("your waymark tugging at you, but something holds you "
                 "in place.");
        return FALSE;
    }
    if (u.uhave.amulet) {
        You_feel("your waymark calling, but the Amulet keeps you here.");
        return FALSE;
    }
    if (u_at(x, y)) {
        You("are already standing on your waymark.");
        return FALSE;
    }
    if (In_overworld)
        ow_ensure_generated(x, y); /* the mark may be far away */
    if (!isok(x, y))
        return FALSE;
    /* land on the mark, or as close to it as is safe */
    cc.x = cc.y = 0;
    if (waymark_spot_ok(x, y)) {
        cc.x = x, cc.y = y;
    } else {
        int r, dx, dy;

        for (r = 1; r <= 4 && !cc.x; r++)
            for (dx = -r; dx <= r && !cc.x; dx++)
                for (dy = -r; dy <= r; dy++) {
                    if (max(abs(dx), abs(dy)) != r)
                        continue;
                    if (waymark_spot_ok(x + dx, y + dy)) {
                        cc.x = x + dx, cc.y = y + dy;
                        break;
                    }
                }
    }
    if (!cc.x) {
        You_feel("disoriented for a moment.");
        return FALSE;
    }
    You("step back along your own trail...");
    teleds(cc.x, cc.y, TELEDS_TELEPORT);
    if (In_overworld)
        ow_maintain();
    if (!u_at(x, y))
        You("arrive beside your waymark.");
    return TRUE;
}

/* Cartographer: set, or return to, a waymark */
staticfn int
tech_waymark(int *teleported)
{
    *teleported = 0;
    if (u.uswallow) {
        You("can't mark anything from in here.");
        return 0;
    }
    if (!u.uwaymark_x) {
        u.uwaymark_lev = u.uz;
        u.uwaymark_x = u.ux, u.uwaymark_y = u.uy;
        You("fix this spot firmly in your memory as a waymark.");
        return 1;
    }
    if (!on_level(&u.uwaymark_lev, &u.uz)) {
        if (y_n("Your waymark is on another level.  Move it here?") != 'y')
            return 0;
        u.uwaymark_lev = u.uz;
        u.uwaymark_x = u.ux, u.uwaymark_y = u.uy;
        You("fix this spot firmly in your memory as your new waymark.");
        return 1;
    }
    if (waymark_teleport()) {
        *teleported = 1;
        return 1;
    }
    return 0;
}

/* ghost: an unearthly wail that sends the living fleeing in terror */
staticfn int
tech_haunt(void)
{
    struct monst *mtmp;
    int radius = 3 + u.ulevel / 3, nfled = 0;

    if (u.uswallow) {
        You("wail, but only the walls of %s hear you.",
            mon_nam(u.ustuck));
        return 1;
    }
    You("let out a dreadful, unearthly wail!");
    wake_nearto(u.ux, u.uy, radius * radius);
    for (mtmp = fmon; mtmp; mtmp = mtmp->nmon) {
        if (DEADMONSTER(mtmp) || mtmp->mtame || mtmp == u.usteed)
            continue;
        if (distu(mtmp->mx, mtmp->my) > radius * radius)
            continue;
        if (!m_canseeu(mtmp) || helpless(mtmp))
            continue;
        /* the mindless, the dead and the unique aren't impressed; nor are
           those with a job to do */
        if (mindless(mtmp->data) || is_undead(mtmp->data)
            || unique_corpstat(mtmp->data) || mtmp->isshk
            || mtmp->ispriest || mtmp->isgd || mtmp->iswiz
            || is_rider(mtmp->data))
            continue;
        if (resist(mtmp, SPBOOK_CLASS, 0, NOTELL)
            || mtmp->m_lev > u.ulevel + rn2(8))
            continue;
        if (mtmp->mpeaceful && humanoid(mtmp->data) && !rn2(2)
            && !Deaf) {
            if (canseemon(mtmp))
                pline("%s screams!", Monnam(mtmp));
            else
                You_hear("a scream.");
        }
        monflee(mtmp, d(2, u.ulevel), FALSE, TRUE);
        nfled++;
    }
    if (!nfled)
        pline("Nobody seems frightened.");
    return 1;
}

/* Convict: slip out of restraints */
staticfn int
tech_slipfree(void)
{
    boolean did = FALSE;

    if (u.uswallow) {
        pline("There's no slipping out of this one.");
        return 0;
    }
    if (Punished) {
        You("work your way out of your shackles!");
        unpunish();
        did = TRUE;
    }
    if (u.utrap) {
        switch (u.utraptype) {
        case TT_BEARTRAP:
            You("slip your %s out of the bear trap.", body_part(FOOT));
            break;
        case TT_PIT:
            You("scramble nimbly out of the pit.");
            break;
        case TT_WEB:
            You("wriggle free of the web.");
            break;
        case TT_LAVA:
            You("pull yourself free of the lava.");
            break;
        case TT_INFLOOR:
        case TT_BURIEDBALL:
            You("work yourself loose from the %s.", surface(u.ux, u.uy));
            break;
        default:
            You("slip free.");
            break;
        }
        reset_utrap(TRUE);
        did = TRUE;
    }
    if (u.ustuck && !u.uswallow) {
        if (sticks(gy.youmonst.data)) {
            You("release %s.", mon_nam(u.ustuck));
        } else {
            You("twist out of %s grip!", s_suffix(mon_nam(u.ustuck)));
        }
        set_ustuck((struct monst *) 0);
        did = TRUE;
    }
    if (!did) {
        You("aren't restrained.");
        return 0;
    }
    return 1;
}

/* illithid: a psychic blast at nearby minds */
staticfn int
tech_mindblast(int tech_no)
{
    struct monst *mtmp;
    int radius = 4 + techlev(tech_no) / 3, dmg, nhit = 0;

    You("unleash a wave of psychic energy!");
    /* strikes the hostile minds around you; you keep it away from your
       pets and from peaceful folk */
    for (mtmp = fmon; mtmp; mtmp = mtmp->nmon) {
        if (DEADMONSTER(mtmp) || mtmp->mpeaceful || mtmp == u.usteed)
            continue;
        if (distu(mtmp->mx, mtmp->my) > radius * radius)
            continue;
        if (mindless(mtmp->data) || mtmp->data->mlet == S_EYE
            || is_mind_flayer(mtmp->data))
            continue;
        dmg = d(2, 6) + techlev(tech_no) / 2;
        if (telepathic(mtmp->data))
            dmg *= 2; /* open minds are hurt the most */
        if (resist(mtmp, SPBOOK_CLASS, 0, NOTELL))
            dmg = (dmg + 1) / 2;
        else if (!mtmp->mstun)
            mtmp->mstun = 1;
        nhit++;
        if (canspotmon(mtmp))
            pline("%s %s!", Monnam(mtmp),
                  mtmp->mstun ? "reels from the blast" : "winces");
        wakeup(mtmp, FALSE);
        (void) tech_damage_mon(mtmp, dmg);
    }
    if (!nhit)
        You("sense no minds to strike.");
    return 1;
}

/* tortle: hold your breath for a long, long time */
staticfn int
tech_holdbreath(int tech_no)
{
    int dur;

    if (Breathless || (HMagical_breathing & ~TIMEOUT)
        || EMagical_breathing || amphibious(gy.youmonst.data)) {
        You("have no need to hold your breath.");
        return 0;
    }
    dur = 50 + 10 * techlev(tech_no);
    You("take a long, deep breath.");
    techt_inuse(tech_no) = dur + 1;
    incr_itimeout(&HMagical_breathing, dur);
    return 1;
}

/*tech.c*/
