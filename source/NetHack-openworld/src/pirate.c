/* NetHack 5.0  pirate.c */
/* Copyright (c) the SLASH'EM, SpliceHack and Hack'EM development teams. */
/* NetHack may be freely redistributed.  See license for details. */

/*
 * The Pirate role (SLASH'EM Extended, SlashTHEM, SpliceHack, Hack'EM):
 * pirate speech, the Pirate's names for things, and the Treasury of
 * Proteus, the Pirate quest artifact, which from time to time changes
 * whatever is kept inside it.
 */

#include "hack.h"

staticfn const char *pirate_replace(const char *, const char *,
                                    const char *);

/* names a pirate uses for some ordinary objects (like the Samurai's
   Japanese names for things) */
struct Pitem {
    int item;
    const char *name;
};

static const struct Pitem Pirate_items[] = {
    { POT_BOOZE, "rum" },
    { CRAM_RATION, "sea biscuit" },
    { SCIMITAR, "cutlass" },
    { SMALL_SHIELD, "buckler" },
    { SACK, "ditty bag" },
    { LARGE_BOX, "foot locker" },
    { CHEST, "coffer" },
    { CLUB, "belaying pin" },
    { QUARTERSTAFF, "oar" },
    { BLINDFOLD, "eye-patch" },
    { EGG, "cackle fruit" },
    { BULLWHIP, "cat o' nine tails" },
    { RIN_CONFLICT, "mutiny" },
    { AMULET_OF_STRANGULATION, "hempen halter" },
    { SCR_PUNISHMENT, "keelhaul" },
    { ROBE, "long clothes" },
    { 0, "" }
};

/* return a pirate's name for object type 'otyp', or 'ordinaryname' */
const char *
pirate_item_name(int otyp, const char *ordinaryname)
{
    const struct Pitem *j;

    for (j = Pirate_items; j->item; j++)
        if (otyp == j->item)
            return j->name;
    return ordinaryname;
}

/* find the object type with pirate name 'name' (for wishing) */
int
pirate_item_otyp(const char *name)
{
    const struct Pitem *j;

    for (j = Pirate_items; j->item; j++)
        if (!strcmpi(name, j->name))
            return j->item;
    return STRANGE_OBJECT;
}

/* replace every occurrence of 'orig' in 'st' with 'repl'; returns 'st'
   itself if there was nothing to replace, otherwise a static buffer
   (alternating between two so that the result can be fed back in) */
staticfn const char *
pirate_replace(const char *st, const char *orig, const char *repl)
{
    static char bufs[2][BUFSZ];
    static int which = 0;
    char *out;
    const char *pos, *hit;
    size_t olen = strlen(orig), rlen = strlen(repl), used = 0, len;

    if (!*orig || !strstr(st, orig))
        return st;
    which = !which;
    out = bufs[which];
    pos = st;
    while ((hit = strstr(pos, orig)) != 0) {
        len = (size_t) (hit - pos);
        if (used + len + rlen >= BUFSZ - 1)
            break;
        (void) memcpy(out + used, pos, len);
        used += len;
        (void) memcpy(out + used, repl, rlen);
        used += rlen;
        pos = hit + olen;
    }
    len = strlen(pos);
    if (used + len >= BUFSZ - 1)
        len = BUFSZ - 1 - used;
    (void) memcpy(out + used, pos, len);
    used += len;
    out[used] = '\0';
    return out;
}

/* a pirate hears everything in the speech of the sea (Hack'EM) */
const char *
piratesay(const char *orig)
{
#define R(a, b) orig = pirate_replace(orig, (a), (b))
#define rnd_word(n) (!rn2_on_display_rng(n))
    R("find it hard to breathe", "start dancing the hempen jig");
    R("succeed in locking the box", "batten down the hatches");
    R("You fall down the stairs.", "Blow the man down!");
    R("move the boulder", "heave ho");
    R("no longer feel sluggish", "got your sea legs back");
    R("suddenly seems weaker", "looks seasick");
    R("don't know", "dunno");
    R(" it is", " 'tis");
    R("It is ", "'Tis ");
    R("Is not ", "Ain't ");
    R("is not ", "ain't ");
    R("wipe off", "swab");
    R("wiped off", "swabbed");
    R("Your", "Yer");
    R("your", "yer");
    R("You", "Ye");
    R("you", "ye");
    R("His ", "'Is ");
    R(" his ", " 'is ");
    R(" him", " 'im");
    R("Her ", "'Er ");
    R(" her ", " 'er ");
    R(" my ", " me ");
    R("Are ", "Be ");
    R(" are ", " be ");
    R(" and ", " 'n' ");
    R(" is ", " be ");
    R(" is.", " be.");
    if (rnd_word(2))
        R(" of ", " o' ");
    if (rnd_word(5))
        R(" to ", " t' ");
    R(" for ", " fer ");
    R("What ", "Wha' ");
    R(" what ", " wha' ");
    R(" with ", " wit' ");
    R("With ", "Wit' ");
    R(" have", " 'ave");
    R(" eye ", " deadlight ");
    R(" eye.", " deadlight.");
    R(" eye!", " deadlight!");
    R(" eyes", " deadlights");
    R("zorkmid", "doubloon");
    R("Zorkmid", "Doubloon");
    R("gold pieces", "pieces of eight");
    R("Gold pieces", "Pieces of eight");
    R("gold piece", "piece of eight");
    R("Gold piece", "Piece of eight");
    R("treasure", "booty");
    R("potion", "bottle");
    R("Ouch!", "Arrr!");
    R("Wow!", "Avast!");
    R(" just ", " jus' ");
    R("before", "'afore");
    R("Before", "'Afore");
    R(" rear", " aft");
    R("nothing", "naught");
    R("Nothing", "Naught");
    R("careful", "handsome");
    R("terrible", "ghastly");
    R("noises", "racket");
    R(" lord", " cap'n");
    if (rnd_word(2))
        R(" killed", rnd_word(2) ? " scuttled" : " sunk");
    if (rnd_word(3))
        R(" dies", rnd_word(2) ? " walks the plank"
                               : " dances the hempen jig");
    R("probably", "prolly");
    R("music ", "chanties ");
    R("knapsack", "duffle");
    R("scoundrel", "picaroon");
    R("Gasp!", "Blimey!");
    R("Uh-oh.", "Sink me!");
    R("Oh my!", "Shiver me timbers!");
    R("What?", "Arr!");
    R("Hmmm", "Arr");
    R("Hmm", "Arr");
    R("Why?", "Scupper that!");
    R("Oh no!", "Avast ye!");
    R("being suffocated", "dancing with Jack Ketch");
    R("fall asleep", "take a chalk");
    R("falls asleep", "takes a chalk");
    R("wakes up", "shows a leg");
    R("wake up", "show a leg");
    if (rnd_word(3))
        R("steal ", "hornswaggle ");
    /* this catches a LOT of stuff */
    R("cing ", "cin' ");
    R("ding ", "din' ");
    R("ging ", "gin' ");
    R("king ", "kin' ");
    R("ming ", "min' ");
    R("ning ", "nin' ");
    R("oing ", "oin' ");
    R("ting ", "tin' ");
    R("ssing ", "ssin' ");
    R("ving ", "vin' ");
    R("wing ", "win' ");
    R("ying ", "yin' ");
#undef R
#undef rnd_word
    return orig;
}

/* The Treasury of Proteus polymorphs whatever is kept inside it now and
   then while its keeper carries it (SpliceHack, Hack'EM); called once per
   turn */
void
treasury_of_proteus(void)
{
    static const char *const seasounds[] = {
        "distant surf", "the distant sea", "the call of the ocean",
        "waves against the shore", "flowing water", "the sighing of waves",
        "quarrelling gulls", "the song of the deep", "rumbling in the deeps",
        "the singing of Eidothea", "the laughter of the protean nymphs",
        "rushing tides", "the elusive sea change",
        "the silence of the briny deep", "the passage of the albatross",
        "dancing raindrops", "coins rolling on the seabed",
        "treasure galleons crumbling in the depths",
        "waves lapping against a hull",
    };
    struct obj *chest, *otmp, *nextobj;

    if (!(chest = carrying_arti(ART_TREASURY_OF_PROTEUS)))
        return;
    if (u.uprotean > 0) {
        u.uprotean--;
        return;
    }
    u.uprotean = rnz(100) + d(3, 10);
    if (!chest->cobj)
        return;
    if (!Deaf)
        You_hear("%s.", ROLL_FROM(seasounds));
    for (otmp = chest->cobj; otmp; otmp = nextobj) {
        nextobj = otmp->nobj;
        if (obj_resists(otmp, 5, 95))
            continue;
        /* KMH, conduct */
        if (!u.uconduct.polypiles++)
            livelog_printf(LL_CONDUCT, "polymorphed %s first item",
                           uhis());
        /* any saved lock context will be dangerously obsolete */
        if (Is_box(otmp))
            (void) boxlock(otmp, chest);
        if (obj_shudders(otmp)) {
            obj_extract_self(otmp);
            obfree(otmp, (struct obj *) 0);
        } else {
            (void) poly_obj(otmp, STRANGE_OBJECT);
        }
    }
    chest->owt = weight(chest);
    update_inventory();
}

/*pirate.c*/
