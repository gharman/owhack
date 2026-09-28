/* NetHack 5.0	tech.h */
/* Original code by Warren Cheung (Slash'EM); Hack'EM additions.        */
/* Copyright 1986, M. Stephenson                                        */
/* NetHack may be freely redistributed.  See license for details.       */

#ifndef TECH_H
#define TECH_H

/*
 * Techniques: special abilities that a hero learns from their role and
 * race as they gain experience levels (Slash'EM style), used with the
 * #technique command.  Each technique has a timeout before it can be
 * used again, and some stay "active" for a number of turns.
 *
 * Technique ids are stored in save files: only ever add new ones at the
 * end of the list (just before NUM_TECHS).
 */
enum tech_id {
    NO_TECH = 0,
    T_BERSERK,
    T_KIII,
    T_RESEARCH,
    T_SURGERY,
    T_REINFORCE,
    T_FLURRY,
    T_PRACTICE,
    T_EVISCERATE,
    T_HEAL_HANDS,
    T_TURN_UNDEAD,
    T_VANISH,
    T_CUTTHROAT,
    T_BLESSING,
    T_E_FIST,
    T_PRIMAL_ROAR,
    T_LIQUID_LEAP,
    T_CRIT_STRIKE,
    T_RAISE_ZOMBIES,
    T_REVIVE,
    T_TINKER,
    T_RAGE,
    T_CHI_STRIKE,
    T_DRAW_ENERGY,
    T_CHI_HEALING,
    T_DISARM,
    T_DAZZLE,
    T_BLITZ,
    T_PUMMEL,
    T_G_SLAM,
    T_DASH,
    T_POWER_SURGE,
    T_SPIRIT_BOMB,
    T_APPRAISAL,
    T_SOULEATER,
    T_JEDI_JUMP,
    T_TELEKINESIS,
    T_WHISTLE_UNDEAD,
    T_SPIRIT_TEMPEST,
    T_FORCE_PUSH,
    T_CURSE,
    T_PICKPOCKET,
    T_TUMBLE,
    T_SUNDER,
    T_BLOOD_MAGIC,
    T_BREAK_ROCK,
    T_UPPERCUT,
    T_ICEARMOR,
    /* NetHack: Open World */
    T_SURVEY,
    T_TRIANGULATE,
    T_WAYMARK,
    T_HAUNT,
    T_SLIP_FREE,
    T_MIND_BLAST,
    T_HOLD_BREATH,
    T_CHARGE_SABER, /* Jedi (Slash'EM/SlashTHEM, as in Hack'EM) */
    T_DRAW_BLOOD,   /* vampire (Slash'EM) */
    NUM_TECHS
};

/* number of technique slots the hero has (enough for every technique) */
#define MAXTECH 72

/* one known technique; an array of these is kept in struct you */
struct tech {
    short t_id;       /* technique (T_xxx); NO_TECH for an unused slot */
    xint16 t_lev;     /* technique level = u.ulevel - t_lev */
    int t_tout;       /* turns until the technique can be used again */
    int t_inuse;      /* turns until an active technique wears off;
                         0: not active */
    long t_intrinsic; /* where it came from: FROMEXPER (role), FROMRACE,
                         FROMOUTSIDE; the OUTSIDE_LEVEL bits hold t_lev
                         for the FROMOUTSIDE source */
#define OUTSIDE_LEVEL TIMEOUT
};

/* a technique conferred by role or race at a given experience level */
struct innate_tech {
    schar ulevel;  /* learned at this experience level */
    short tech_id; /* T_xxx */
    int tech_lev;  /* technique level when learned */
};

#endif /* TECH_H */
