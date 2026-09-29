# Techniques

[Home](Home.md)

**Techniques** are special abilities learned at experience levels, as in
Slash'EM, SlashTHEM and Hack'EM (see nethackwiki's
[Technique](https://nethackwiki.com/wiki/Technique) page for the
originals). This page covers how they work in this build, which roles and
races get which, and the techniques that are unique to NetHack: Open
World.

## Using them

* **`#technique`, or `M-x`**, lists the techniques you know and lets you use
  one. The menu shows each one's **level** and **status**:

  | Status | Meaning |
  |---|---|
  | Prepared | ready to use |
  | Active | in effect right now |
  | Soon | recharging, 100 turns or less to go |
  | Not Ready | recharging, more than 100 turns to go |
  | Beyond recall | you have been drained below the level where you learned it |

* `^A` repeats the last technique.
* A technique's **level** is how many experience levels you have had it
  for; many grow stronger with it.
* **Learning and losing.** You learn techniques automatically as you gain
  levels, from your role's table and your race's. Drained below a
  technique's level, you lose it again, except the ones you started with.
* Reaching **Skilled in any melee weapon skill** teaches **disarm**; losing
  the skill loses it.
* NetHack's own **`#turn` is the *turn undead* technique**: Knights and
  Priests know it, and the technique does exactly what `#turn` does, with
  no timeout, as in Slash'EM.
* Techniques appear in enlightenment (`^X`) and the dumplog. Using one
  breaks a conduct of its own ("never used a technique").
* Wizard mode: `#wiztechnique` learns or forgets any technique, or resets
  all timeouts.

## Who gets what

The number is the experience level at which it is learned.

### Roles

| Role | Techniques |
|---|---|
| Archeologist | appraisal (1), research (3) |
| Barbarian | berserk (1), rage eruption (5) |
| **Cartographer** | **survey (1), triangulate (3), waymark (8)** |
| Caveman | primal roar (1) |
| Convict | pickpocket (1), **slip free (5)** |
| Flame Mage | reinforce memory (1), power surge (3), draw energy (5) |
| Healer | surgery (1) |
| Ice Mage | reinforce memory (1), ice armor (3), draw energy (5), power surge (12) |
| Infidel | curse (1), reinforce memory (1), draw energy (5) |
| Jedi | jedi jump (1), charge saber (5), telekinesis (8), force push (14) |
| Knight | turn undead (1), healing hands (1); a chaotic knight gets souleater (1) instead |
| Monk | pummel (1), air dash (1), chained blitz (1), break rock (1), chi strike (2), chi healing (4), elemental fist (6), draw energy (8), ground slam (10), uppercut (13), spirit bomb (17), power surge (20) |
| Necromancer | reinforce memory (1), whistle undead (2), raise zombies (3), blood magic (5), souleater (8), power surge (10), revivification (14), spirit tempest (17) |
| Pirate | tumble (1), **hold breath (3)**, sunder (5) |
| Priest | turn undead (1), blessing (1), healing hands (10), revivification (30) |
| Ranger | missile flurry (1) |
| Rogue | pickpocket (1), critical strike (1), cutthroat (15) |
| Samurai | kiii (1) |
| Tourist | none |
| Valkyrie | weapon practice (1) |
| Wizard | reinforce memory (1), draw energy (3), power surge (5) |

### Races

| Race | Techniques |
|---|---|
| human, elf, orc, tortle | none |
| dwarf | rage eruption (1) |
| gnome | vanish (1), tinker (7) |
| giant | primal roar (1), berserk (10) |
| centaur | missile flurry (5) |
| illithid | **mind blast (1)** |
| draugr | berserk (1) |
| vampire | dazzle (1), draw blood (1) |
| werewolf | eviscerate (1), berserk (10) |
| doppelganger | liquid leap (1) |
| **ghost** | **haunt (1)** |

The role tables follow Hack'EM (which takes them from Slash'EM and
SlashTHEM); Hack'EM has no Convict table, so the Convict's is this
build's own. The race tables follow Hack'EM and Slash'EM (the werewolf's
is Slash'EM's lycanthrope's, the giant's SlashTHEM's ogre's); the
centaur's, illithid's, draugr's and ghost's are this build's own.
Tortles have their shell (`#monster`) instead.

## Techniques unique to this build

### Cartographer

#### Survey

*You survey your surroundings.* Maps the terrain within **8 + XL/2**
squares of you, as magic mapping would, and finds the traps within half
that distance. Works in the dark and while blind (*You pace out your
surroundings and feel your way around.*), not while engulfed or under
water. On levels that can't be magic-mapped the lie of the land defies
you (the technique is still used). **Recharges in 250 − 5 × XL turns**, at
least 50.

#### Triangulate

*You take your bearings.*

* **In the open world**: the direction and distance of the **nearest magic
  portal**, and where it leads, and of the **nearest town** (or the heart
  of the town you are in). Both are marked on your map, ready for `_`
  travel.
* **In a branch**: the **nearest way out** (up stairs, a ladder or a magic
  portal leading back toward where you came in; failing that, any way
  somewhere else).

Not while stunned, confused or hallucinating, nor engulfed.
**Recharges in 300 turns.**

#### Waymark

* **Setting a mark** (no timeout): *You fix this spot firmly in your memory
  as a waymark.*
* **Returning**: use it again and you step straight back to the mark, or as
  close to it as is safe (*You step back along your own trail...*). In the
  open world the mark can be anywhere in the whole world: it may be
  hundreds of squares away. **Recharges in 1000 − 20 × XL turns**, at
  least 200, after a return.
* **If the mark is on another level**, you are asked whether to move it
  here.
* **It won't take you** off a no-teleport level, nor while you carry the
  Amulet of Yendor (*You feel your waymark calling, but the Amulet keeps
  you here.*), nor across the Barrier into Gehennom before you have been
  there.

### Ghost

#### Haunt

*You let out a dreadful, unearthly wail!* Every monster within
**3 + XL/3** squares that can see you must resist or **flee in terror for
d(2, XL) turns**; it also wakes things up. A monster shrugs it off if it
passes a resistance check (as against a spell), or if its level is more
than yours plus a random 0 to 7.
Mindless monsters, the undead, uniques, shopkeepers, priests, guards, the
Wizard and the Riders are not impressed; nor are your pets. Peaceful
humanoids may scream. **Recharges in 200 − 3 × XL turns**, at least 50.

### Convict

#### Slip free

Wriggle out of whatever holds you: a **ball and chain** (*You work your
way out of your shackles!*), a bear trap, pit, web, lava, being stuck in
the floor, or a monster's grip. Not out of an engulfer. **Recharges in 500
to 999 turns.**

### Illithid

#### Mind blast

*You unleash a wave of psychic energy!* Strikes the **hostile** minds
within **4 + level/3** squares (it spares your pets and peaceful folk) for
**2d6 + level/2** damage, **doubled against telepathic monsters**, and
stuns them unless they resist (then half damage). Mindless monsters,
floating eyes and the other `e`, and mind flayers are unaffected, and psychic-resistant
monsters shrug it off. **A heavy metal helmet stops it** (mithril is too
light to matter; the Mitre of Holiness doesn't block), as it does the
illithid's `#monster` psychic blast, and then no time is used.
**Recharges in 500 to 999 turns.** (The `#monster` blast is different:
the mind flayer's own attack, for 10 Pw, across the level.)

### Pirate

#### Hold breath

*You take a long, deep breath.* For **50 + 10 × level turns** you can
breathe under water. If it runs out while you are still under water, you
start to drown. Useless if you don't need to breathe. **Recharges in 500
to 999 turns.** (Designed for tortles, who turned out to be amphibious
already, so it went to the Pirate.)

## Adapted from the source variants

* **Draw blood** (vampire): Slash'EM's needs a medical kit and a phial,
  which this game doesn't have. Here it turns a **potion of water** into a
  **potion of vampire blood** of the same blessedness, costing you an
  experience level. Only in your own form, and not at level 1 (*You can't
  find a vein!*). Recharges in 500 to 1499 turns. Vampire blood is food and
  strong healing for a vampire.
* **Charge saber** (Jedi): pours your energy into your lightsaber's power
  cell. It uses the same recharging as a scroll of charging, and does
  nothing for the Lightsaber Prototype.
* **Turn undead** is `#turn`; see above.
* **Disarm** is learned from weapon skill rather than from a table.
* Hack'EM's card techniques (for its Cartomancer), SLASH'EM Extended's
  *world fall*, *create ammo* and *booze*, and *power shield* (in no
  Hack'EM table) aren't here.
