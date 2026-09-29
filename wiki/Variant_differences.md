# Differences from the source variants

[Home](Home.md)

Much of this build is ported from other variants. The ports are meant to
be faithful, so nethackwiki's pages for
[Slash'EM](https://nethackwiki.com/wiki/Slash%27EM),
[SlashTHEM](https://nethackwiki.com/wiki/SlashTHEM),
[Hack'EM](https://nethackwiki.com/wiki/Hack%27EM),
[EvilHack](https://nethackwiki.com/wiki/EvilHack),
[SpliceHack](https://nethackwiki.com/wiki/SpliceHack) and
[xNetHack](https://nethackwiki.com/wiki/XNetHack) apply. This page lists
where this build differs, mostly because of the open world.

## Roles

| Role | Source | Notes |
|---|---|---|
| Necromancer | Slash'EM, as in Hack'EM | Quest: Maugneshaagar and the Great Dagger of Glaurgnaa. Gift: Serpent's Tongue. Undead are sometimes peaceful and are the only creatures a necromancer can tame. Pet: ghoul. |
| Flame Mage | Slash'EM, as in Hack'EM | Quest: the Water Mage and the Candle of Eternal Flame. Gift: Firewall. Cold-vulnerable from XL 5. `#youpoly` into a baby red dragon (XL 8) or a red dragon (XL 15). |
| Ice Mage | Slash'EM, as in Hack'EM | Quest: Ragnaros and the Storm Whistle. Gift: Deep Freeze. Fire-vulnerable from XL 5; `#youpoly` into white dragons. |
| Jedi | SlashTHEM, as in Hack'EM | Quest: Lord Sidious and the Lightsaber Prototype. Gift: Deluder. Pet: a droid. Lightsabers must be lit to cut and drain their charge; the charge saber technique refills them. |
| Pirate | SpliceHack / Hack'EM / SlashTHEM | Quest: Blackbeard's Ghost and the Treasury of Proteus. Firearms (flintlock and bullets) are a new skill. Every message in pirate speech. Gets the *hold breath* technique here. |
| Convict | EvilHack / SpliceHack / Hack'EM | Quest: Warden Arianna and the Iron Spoon of Liberation (as Hack'EM chose). Always chaotic, whatever the race's usual alignment. Starts punished, hungry, with Nicodemus the rat. |
| Infidel | EvilHack | Quest: the Paladin and the Idol of Moloch. Gift: Secespita. **Wins differently: see below.** |
| **Cartographer** | new | see [Cartographer](Cartographer.md) |

### Infidel

The Infidel worships Moloch and, as in EvilHack, **starts with the Amulet
of Yendor**. EvilHack's Infidel wins on the Astral Plane; here the rule
moves to the centre of the world:

1. Take the Amulet to **Moloch's Sanctum** and offer it on Moloch's high
   altar **while carrying the Idol of Moloch**. Moloch takes the Amulet and
   imbues the Idol with its power (without the Idol you are refused).
2. Carry the imbued Idol back to the **sacred plaza** at the centre of the
   world and `#invoke` it on the high altar of the god of heaven Moloch
   means to overthrow. That altar becomes Moloch's, and you ascend as the
   Archfiend of Moloch. Invoking it on either of the other two high altars
   brings that god's wrath; the quest leader and the Sanctum's high priest
   hint which altars to avoid.

Other open-world notes for Infidels:

* An Infidel starts in the plaza two squares south of the middle altar,
  since none of the three is theirs.
* Offering the Amulet anywhere too early gives *You feel an urge to descend
  deeper.*
* **Infidels are spared the mysterious force**, as in EvilHack.
* Carrying the Amulet from the start means no level teleporting all game;
  that is EvilHack's rule too.

## Races

| Race | Source |
|---|---|
| giant, centaur, illithid, tortle, draugr | EvilHack (EvilHack calls the draugr race "zombie") |
| vampire | EvilHack / Hack'EM / Slash'EM |
| werewolf | Slash'EM's lycanthrope race |
| doppelganger | Slash'EM / Hack'EM |
| **ghost** | new: see [Ghost](Ghost_race.md) |

* **Which roles each race can take** is a table of this build's own (see
  the README's race table). Pairs with no alignment in common are never
  offered: Knight with centaur or draugr, Valkyrie with draugr, Caveman
  with werewolf, Flame Mage with elf, Jedi with elf, Necromancer with
  gnome.
* **Starting kits respect racial armor limits for every role**: giants and
  tortles never start with body armor, cloaks or shirts, and centaurs and
  tortles never with boots. EvilHack substitutes an item for some of
  these; this build does too where EvilHack does, and otherwise leaves them
  out.
* **Centaurs and ghosts can't ride**, so a Cartographer or Knight pony
  starts unsaddled for them.
* The **undead races' prayer rule** (lawful gods smite an undead hero's
  prayer, neutral ones now and then; stock NetHack's rule for polymorphed
  undead) applies to draugr and vampires but not to ghosts.
* **Illithid psionics**: the `#monster` psychic blast is the mind flayer's
  (10 Pw, across the level); the *mind blast* technique is a separate
  short-range burst. A heavy metal helmet (not mithril, not the Mitre of
  Holiness) blocks both, and psychic-resistant monsters ignore both.

## Drain and psychic resistance

Both are full resistances here, for monsters and heroes, as in Hack'EM:

* **Drain resistance**: the undead, demons, lycanthropes and Death resist
  level drain. Heroes get it from being a Necromancer (XL 1), a draugr,
  vampire or ghost, and from the usual artifacts.
* **Psychic resistance** protects against mind flayers' psychic blasts
  and their memory-stealing tentacles, and against amnesia. Heroes get it
  from being an illithid, from the **tinfoil hat** (which also blocks
  telepathy, clairvoyance and tentacles) and the **ring of psychic
  resistance**, and from polymorph forms. Mind flayers and other psionic
  monsters have it.

## Materials

Ported from xNetHack, with EvilHack's rules for material hatred and
wishing:

* **METAL is shown as "steel"**, a material in its own right beside iron.
* **Mithril coats are gone.** Mithril is a material for body armor.
  *Elven chain mail* is mithril by default and takes the elven coat's
  place (same stats). *Dwarvish chain mail* is iron by default; in mithril
  it matches the old dwarvish coat. Any chain, splint, banded, plate or
  other metal mail may turn up in mithril. Wishing for an "elven" or
  "dwarvish mithril-coat" still works, and so do the old names of the
  renamed dwarvish helm ("dwarvish iron helm"), orcish helm ("iron skull
  cap") and shield of reflection ("polished silver shield").
* **You can wish for a material** ("mithril plate mail") whenever that
  material is valid for the object (EvilHack's rule; xNetHack allows it
  only in wizard mode). Otherwise you get the default material.
* **Mithril body armor or cloaks give at least MC2.**
* **Cold iron harms elves and the fae** (nymphs, imps), undead ones
  excepted; **copper harms fungi and bringers of disease**. Heroes of those
  races take the same harm, including when wielding or wearing the
  material (gloves protect the hands). **An elf's starting kit switches to
  copper** where that is valid. **Worn copper armor wards off sickness.**
* **Objects whose name states a material never change material** (leather
  armor, iron shoes, oilskin cloak, and so on), nor does anything that
  shares an unidentified description with one, so a material can't give
  an object away.
* **Left out**: xNetHack's golems dropping items and transparent crystal
  chests, EvilHack's mithril-vs-orc hatred, and the cracking of glass
  armor in combat (to keep crystal plate mail as strong as it was).

## Special levels

See [Portal rings](Portal_rings.md) for where they are.

* Slash'EM's levels deeper than Medusa are squeezed into the rings before
  her, in order, because everything beyond Medusa + 2 is Gehennom here.
* **The Gnome King's level** is the bottom of the Gnomish Mines, below
  Mines' End, and **Fort Ludios** has Hack'EM's dungeon beneath the fort as
  a second level.
* **The alignment keys** from the Nightmare's, Beholder's and Vecna's lairs
  are left out: they only open Slash'EM's reworked Vlad's Tower. Their
  masters still drop Nighthorn, the Eye of the Beholder and the Hand of
  Vecna.
* **The Adventurers' Guild** includes this build's new roles.
* **EvilHack's Goblin King doesn't lock** Minetown and Mines' End.
* **Left out, with reasons**:
  * duplicates of what we have: Hack'EM's qlawful, qneutral and qchaos, and
    Slash'EM's one-level dragon caves;
  * Hack'EM's Angband town, village and townfill: the open world already
    has towns;
  * levels their own variants never use: Slash'EM's newmall, Hack'EM's
    cave filler levels, lethe and nkai;
  * levels that need big systems of their own: EvilHack's Ice Queen realm,
    hdgn and forest;
  * a second Vecna: EvilHack's Vecna's Domain;
  * Purgatory: an endgame level that clashes with the central-altar win;
  * alternative layouts of levels we already have.

## `#enhance`

As in Hack'EM, `#enhance` (and the dumplog's skill list) shows each skill
as `[current / maximum]` plus its training toward the next level as a
percentage, where every 100% is one level, or `MAX` when there is nothing
left to train. (Hack'EM's cross-training multipliers aren't part of this
game.)

## Character selection

With 21 roles and 14 races, first letters collide (Cartographer, Caveman,
Convict; gnome, giant, ghost), so each menu entry gets the first free
letter of its name.
