/* NetHack 5.0	objclass.h	$NHDT-Date: 1781973084 2026/06/20 16:31:24 $  $NHDT-Branch: NetHack-5.0 $:$NHDT-Revision: 1.43 $ */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/*-Copyright (c) Pasi Kallinen, 2018. */
/* NetHack may be freely redistributed.  See license for details. */
/* Modified for NetHack: Open World in 2026; dates are in the git log. */

#ifndef OBJCLASS_H
#define OBJCLASS_H

/* [misnamed] definition of a type of object; many objects are composites
   (liquid potion inside glass bottle, metal arrowhead on wooden shaft)
   and object definitions only specify one type on a best-fit basis */
/*
 * Materials.
 *
 * Every object has a material, obj->material (see obj.h).  It defaults to
 * the oc_material given for its type in objects.h, and many weapons, armor
 * pieces, tools and amulets can instead be generated in some other material
 * (a "mithril chain mail", a "silver long sword", a "wooden dagger").
 * The material affects weight, armor class, damage and to-hit, erosion,
 * price, which monsters are hurt by the object (silver, cold iron, copper),
 * how the object is named and whether it stacks with others.
 *
 * New object types:
 *  - an object's default material is simply its oc_material in objects.h
 *    (so objects[].oc_material is the default; always look at
 *    obj->material for an actual object);
 *  - the lists of alternative materials and their probabilities are in
 *    mkobj.c; material_list() picks the list for an object.  NOTE: every
 *    weapon, armor piece and tool whose default is IRON, STEEL, WOOD, CLOTH
 *    or LEATHER, and all elven, dwarvish and orcish gear and amulets, get a
 *    list automatically.  Add a "case" for the object's otyp in
 *    material_list() to give it a different list, or add it to the list of
 *    fixed-material objects at the top of material_list() when it must
 *    always be made of its default material (a lightsaber or a firearm,
 *    an object whose name or description states a material like "iron
 *    shoes", or one that shares a shuffled description with such an
 *    object);
 *  - nonsensical_obj_material() vetoes individual combinations (glass
 *    pick-axes, paper armor, iron elven gear, ...).
 * Nothing else is needed: generation, wishing (a material prefix, "a
 * mithril chain mail"), polymorph, bones, level files (des.object({
 * material = "..." })) and the sanity checker all use valid_obj_material()
 * and init_obj_material().  Artifacts with a fixed material are listed in
 * artimaterials[] in artilist.h.  Monsters and races that hate a material
 * are in hates_material() in mondata.c.
 *
 * Don't reorder these without also changing materialnm[] in decl.c and the
 * per-material tables in mkobj.c (matdensities[], matac[]), shk.c
 * (matprices[]), display.c (materialclr[]) and eat.c (foodwords[]); the
 * relative order also matters for is_organic() and is_metallic() below.
 */
enum obj_material_types {
    NO_MATERIAL =  0,
    LIQUID      =  1, /* currently only for venom */
    WAX         =  2,
    VEGGY       =  3, /* foodstuffs */
    FLESH       =  4, /*   ditto    */
    PAPER       =  5,
    CLOTH       =  6,
    LEATHER     =  7,
    WOOD        =  8,
    BONE        =  9,
    DRAGON_HIDE = 10, /* not leather! */
    IRON        = 11, /* Fe - plain (cold, rusting) iron */
    STEEL       = 12, /* stainless steel and other hard alloys: doesn't
                       * rust; called METAL in vanilla NetHack */
    COPPER      = 13, /* Cu - includes brass and bronze */
    SILVER      = 14, /* Ag */
    GOLD        = 15, /* Au */
    PLATINUM    = 16, /* Pt */
    MITHRIL     = 17,
    PLASTIC     = 18,
    GLASS       = 19,
    GEMSTONE    = 20,
    MINERAL     = 21,
    NUM_MATERIAL_TYPES
};
/* vanilla's name for STEEL; object definitions may use either */
#define METAL STEEL

enum obj_armor_types {
    ARM_SUIT   = 0,
    ARM_SHIELD = 1,        /* needed for special wear function */
    ARM_HELM   = 2,
    ARM_GLOVES = 3,
    ARM_BOOTS  = 4,
    ARM_CLOAK  = 5,
    ARM_SHIRT  = 6
};

struct objclass {
    short oc_name_idx;              /* index of actual name */
    short oc_descr_idx;             /* description when name unknown */
    char *oc_uname;                 /* called by user */
    Bitfield(oc_name_known, 1);     /* discovered */
    Bitfield(oc_merge, 1);          /* merge otherwise equal objects */
    Bitfield(oc_uses_known, 1);     /* obj->known affects full description;
                                     * otherwise, obj->dknown and obj->bknown
                                     * tell all, and obj->known should always
                                     * be set for proper merging behavior. */
    Bitfield(oc_encountered, 1);    /* hero has observed such an item at least
                                       once (perhaps without naming it) */
    Bitfield(oc_magic, 1);          /* inherently magical object */
    Bitfield(oc_charged, 1);        /* may have +n or (n) charges */
    Bitfield(oc_unique, 1);         /* special one-of-a-kind object */
    Bitfield(oc_nowish, 1);         /* cannot wish for this object */

    Bitfield(oc_big, 1);
#define oc_bimanual oc_big /* for weapons & tools used as weapons */
#define oc_bulky oc_big    /* for armor */
    Bitfield(oc_tough, 1); /* hard gems/rings */

    Bitfield(oc_spare1, 6);         /* padding to align oc_dir + oc_material;
                                     * can be cannibalized for other use;
                                     * aka 6 free bits */

    Bitfield(oc_dir, 3);
    /* oc_dir: zap style for wands and spells */
#define NODIR     1 /* non-directional */
#define IMMEDIATE 2 /* directional beam that doesn't ricochet */
#define RAY       3 /* beam that does bounce off walls */
    /* overloaded oc_dir: strike mode bit mask for weapons and weptools */
#define PIERCE    1 /* pointed weapon punctures target */
#define SLASH     2 /* sharp weapon cuts target */
#define WHACK     4 /* blunt weapon bashes target */
    Bitfield(oc_material, 5); /* one of obj_material_types */

    schar oc_subtyp;
#define oc_skill oc_subtyp  /* Skills of weapons, spellbooks, tools, gems */
#define oc_armcat oc_subtyp /* for armor (enum obj_armor_types) */

    uchar oc_oprop; /* property (invis, &c.) conveyed */
    char  oc_class; /* object class (enum obj_class_types) */
    schar oc_delay; /* delay when using such an object */
    uchar oc_color; /* color of the object */

    short oc_prob;            /* probability, used in mkobj() */
    unsigned oc_weight;       /* encumbrance (1 cn = 0.1 lb.) */
    short oc_cost;            /* base cost in shops */
    /* Check the AD&D rules!  The FIRST is small monster damage. */
    /* for weapons, and tools, rocks, and gems useful as weapons */
    schar oc_wsdam, oc_wldam; /* max small/large monster damage */
    schar oc_oc1, oc_oc2;
#define oc_hitbon oc_oc1 /* weapons: "to hit" bonus */

#define a_ac oc_oc1     /* armor class, used in ARM_BONUS in do.c */
#define a_can oc_oc2    /* armor: used in mhitu.c */
#define oc_level oc_oc2 /* books: spell level */

    unsigned short oc_nutrition; /* food value */

    unsigned long oc_sell_minseen;
    unsigned long oc_sell_maxseen;
    unsigned long oc_buy_minseen;
    unsigned long oc_buy_maxseen;
};

struct class_sym {
    char sym;
    const char *name;
    const char *explain;
};

struct objdescr {
    const char *oc_name;  /* actual name */
    const char *oc_descr; /* description when name unknown */
};

/*
 * All objects have a class. Make sure that all classes have a corresponding
 * symbol below.
 */

enum objclass_defchars {
#define OBJCLASS_DEFCHAR_ENUM
#include "defsym.h"
#undef OBJCLASS_DEFCHAR_ENUM
};

enum objclass_classes {
    RANDOM_CLASS =  0, /* used for generating random objects */
#define OBJCLASS_CLASS_ENUM
#include "defsym.h"
#undef OBJCLASS_CLASS_ENUM
    MAXOCLASSES
};

/* Default characters for object classes */
enum objclass_syms {
#define OBJCLASS_S_ENUM
#include "defsym.h"
#undef OBJCLASS_S_ENUM
};

/* for mkobj() use ONLY! odd '-SPBOOK_CLASS' is in case of unsigned enums */
#define SPBOOK_no_NOVEL (0 - (int) SPBOOK_CLASS)

#define BURNING_OIL (MAXOCLASSES + 1) /* Can be used as input to explode    */
#define MON_EXPLODE (MAXOCLASSES + 2) /* Exploding monster (e.g. gas spore) */
#define TRAP_EXPLODE (MAXOCLASSES + 3)

#if 0 /* moved to decl.h so that makedefs.c won't see them */
extern const struct class_sym
        def_oc_syms[MAXOCLASSES];       /* default class symbols */
extern uchar oc_syms[MAXOCLASSES];      /* current class symbols */
#endif

struct fruit {
    char fname[PL_FSIZ];
    int fid;
    struct fruit *nextf;
};
#define newfruit() (struct fruit *) alloc(sizeof(struct fruit))
#define dealloc_fruit(rind) free((genericptr_t)(rind))

enum objects_nums {
#define OBJECTS_ENUM
#include "objects.h"
#undef OBJECTS_ENUM
    NUM_OBJECTS
};

enum misc_object_nums {
    NUM_REAL_GEMS  = (LAST_REAL_GEM - FIRST_REAL_GEM + 1),
    NUM_GLASS_GEMS = (LAST_GLASS_GEM - FIRST_GLASS_GEM + 1),
    /* LAST_SPELL is SPE_BLANK_PAPER, guaranteeing that spl_book[] will
       have at least one unused slot at end to be used as a terminator */
    MAXSPELL       = (LAST_SPELL - FIRST_SPELL + 1),
};

extern NEARDATA struct objclass objects[NUM_OBJECTS + 1];
extern NEARDATA struct objdescr obj_descr[NUM_OBJECTS + 1];

#define OBJ_NAME(obj) (obj_descr[(obj).oc_name_idx].oc_name)
#define OBJ_DESCR(obj) (obj_descr[(obj).oc_descr_idx].oc_descr)

/* these all look at the individual object's material (obj->material),
   not at the default material for its type */
#define is_organic(otmp) ((otmp)->material <= WOOD)
#define is_metallic(otmp) \
    ((otmp)->material >= IRON && (otmp)->material <= MITHRIL)

/* primary damage: fire/rust/--- */
/* is_flammable(otmp), is_rottable(otmp) in mkobj.c */
#define is_rustprone(otmp) ((otmp)->material == IRON)
/* glass armor and weapons crack (and eventually shatter) instead of
   eroding; erosion_matters() */
#define is_crackable(otmp) \
    ((otmp)->material == GLASS                                         \
     && ((otmp)->oclass == ARMOR_CLASS || (otmp)->oclass == WEAPON_CLASS))
/* secondary damage: rot/acid/acid */
#define is_corrodeable(otmp) \
    ((otmp)->material == COPPER || (otmp)->material == IRON)
/* subject to any damage */
#define is_damageable(otmp) \
    (is_rustprone(otmp) || is_flammable(otmp)           \
     || is_rottable(otmp) || is_corrodeable(otmp)       \
     || is_crackable(otmp))

/* Always show the material in the object's name, even when it is the
 * default one, for types whose default material isn't what players would
 * assume from the name (elven chain mail is mithril unless stated
 * otherwise). */
#define force_material_name(typ) ((typ) == ELVEN_CHAIN_MAIL)

#endif /* OBJCLASS_H */
