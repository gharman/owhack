# Ghost (race)

[Home](Home.md) · [Techniques](Techniques.md#ghost)

The **ghost** is the race new to NetHack: Open World: a restless spirit that
drifts through walls and rock, frightens the living, and has a hard time
with the physical world. It is not the ghost monster (see
[nethackwiki](https://nethackwiki.com/wiki/Ghost)), though ghost monsters
are always peaceful to a ghost hero.

| | |
|---|---|
| Abbreviation | Gho |
| Alignments | any |
| Roles | Archeologist, [Cartographer](Cartographer.md), Convict, Necromancer, Pirate, Priest, Rogue, Samurai, Tourist, Wizard |
| Attribute maxima | St 16, In 18, Wi 20, Dx 20, Co 14, Ch 14 |
| Hit points | the race adds +1 at level 1 and +1 per level up to the role's cut-off level (weak) |
| Energy | the race adds +3 at level 1 and +3 every level (strong) |
| Always peaceful | ghosts |
| Technique | [haunt](Techniques.md#haunt) (XL 1) |

## Intrinsics

| XL | |
|---|---|
| 1 | flying (you float); cold resistance; sleep resistance; drain resistance; magical breathing (you don't breathe, so you can't drown or be strangled); see invisible; infravision |
| 5 | stealth |
| 9 | poison resistance |
| 13 | warning |

## Drifting through solid matter

A ghost **passes through walls, rock, trees, closed doors, iron bars and
boulders**, but:

* **Only while unburdened.** Burdened or worse: *Your possessions are too
  heavy to pass through solid matter.*
* **It costs energy.** Each move that ends inside solid matter costs 1
  point of power (Pw). With no power left you can't enter solid matter
  (*You lack the energy to pass into solid matter.*). If you are already
  inside it, you can keep going, but each step costs 1d2 hit points
  (*Your essence frays as you strain through solid matter!*), so you can
  never be trapped.
* **Most walls that stop xorns and other wall-walkers don't stop a
  ghost**: Goblin Town's rock, the black market's walls, the Nightmare's
  lair. **Only these resist it**: Sokoban's walls (*The Sokoban walls
  resist your ability.*), the Barrier and the edge of the world, the
  Wizard's Tower, Vlad's Tower, the Sanctum and the endgame.
* **Travel (`_`) never plans a route through solid matter**, so it won't
  burn your power by surprise.

In the open world this means mountains are no obstacle, as long as your
power lasts: a ghost can cut straight through a range that everyone else
walks round, or slip into a vault. Power regenerates as usual.

## Incorporeal

* **Ordinary physical blows and missiles do half damage** (rounded up) to
  a ghost, unless the weapon or missile is **silver** or **blessed**, or the
  attacker is itself incorporeal (another ghost, a shade).
* **Grabs slip through you**, and **your brain can't be eaten** (*Your
  brain is unharmed.*).
* **You can't ride** (*You would pass right through the saddle.*).

## Clumsy with material things

"Hard to work with physical items, but not impossible":

* **Half the usual carrying capacity.**
* **Worn armor gives only half its base AC** (rounded down; material and
  erosion count before halving), while **enchantment counts in full**. A +3
  cloak is worth more to a ghost than plain plate mail.
* **Wielded weapons are at −2 to hit.**
* In exchange, **bare hands deliver a chilling touch**: an extra
  rnd(4 + XL/3) cold damage, unless the target resists cold (and not
  against shades): *You chill the jackal.*

### Starting out

A ghost can't carry everything a living member of its role would. Before
the game begins, **the heaviest things in the starting kit are left on the
ground where you start** until you are unburdened: *Too insubstantial to
bear all that you owned in life, you have left some of it on the altar.*
You can pick them up if you want to carry them. A ghost Cartographer
usually leaves its leather armor, a ghost Samurai its splint mail, a ghost
Necromancer its pick-axe. Food is left out of the kit altogether, and so
are things a ghost has no use for (a ring of see invisible or of slow
digestion, a spellbook of detect food).

## No food, no hunger

A ghost **never eats and never gets hungry**. `#eat` refuses: *You have
no need to eat; you are a spirit, beyond hunger.* So a ghost gains nothing
from corpses: no intrinsics from eating, no telepathy from floating eyes.
The race's own intrinsics are meant to make up for it. Prayer never finds
hunger to fix.

## Fear

* **Your blows frighten.** Each melee hit has a 1 in 4 chance to make the
  target flee for up to 10 turns, unless it is mindless, undead or
  unique, or resists.
* **The living fear you.** Now and then an ordinary peaceful human who
  sees you close by flees (*The watchman shrieks in terror at the sight of
  a ghost!*, the first time). Shopkeepers, priests, guards, the town
  watch, quest leaders and guardians and other special people know better.
* **The [haunt](Techniques.md#haunt) technique** (XL 1): an unearthly wail
  that sends everything nearby that can see you fleeing, unless it resists.

## Undead

A ghost counts as undead (as the draugr and vampire races do):

* holy water and blessed weapons hurt it;
* turn undead (a wand of undead turning, or a priest's turning) frightens
  and stuns it;
* the touch of death has no effect, and a wand of death or finger of death
  restores it instead of killing it;
* it can't catch lycanthropy; nurses won't heal it; bones' rattling
  doesn't scare it;
* **unlike the draugr and vampire races, a ghost may pray to any god**:
  the rule that lawful gods (and sometimes neutral ones) smite an
  undead-race hero's prayer spares ghosts, since a ghost is a spirit rather
  than walking dead flesh. (It exists so that a lawful ghost Priest or
  Samurai isn't cut off from prayer.)
* a ghost Priest can't turn undead itself (*You shudder at the thought.*).

## Death and polymorph

* A ghost dies with *You fade away...* and leaves no corpse.
* **Polymorphed into a solid form, a ghost has that form's body and
  needs**: it can eat and gets hungry, carries normally, wears armor
  normally, and can't phase. Everything above returns when it reverts.

## Strategy

* **Keep your Pw for phasing**, and keep your load light. A ghost that
  picks up everything is a ghost that walks like everyone else.
* **Enchanted armor over heavy armor**: you get half the base AC but all
  the enchantment. An elven cloak, a +2 helmet and good gloves beat a
  suit of plate.
* **Fight with your hands or with magic**: the chilling touch is strong
  early, and the Wizard, Priest and Necromancer ghosts have spells.
  Weapons are at −2.
* **Silver and blessed weapons** get through your half-damage, and ghosts
  and shades hit you fully. Holy water hurts.
* **Mountains are shortcuts** in the open world, and vaults are a few
  squares of rock away. Mind the guard.
