# The open world

[Home](Home.md)

There are no staircases leading down from level to level in this build.
The Dungeons of Doom and Gehennom have been replaced by **one vast outdoor
world**, and the further you wander from where you started, the more
dangerous it becomes.

## Layout

* The world is **1700 × 1700 squares**, generated lazily in 32 × 32
  chunks as you approach, so it costs nothing until you go there. It is
  all one "level" (dungeon 0, level 1), but the map you see scrolls: **you
  always stay in the middle of the screen** (option `centerview`, on by
  default; turn it off for classic half-screen scrolling). A bigger
  terminal shows more of the world.
* The land is divided into **concentric rings, 16 squares wide**, around
  the centre. **Your ring is your depth**: it is `Dlvl` on the status line
  and it drives monster and object generation, difficulty and everything
  else that dungeon depth drives in NetHack. Walking outward is like going
  downstairs.
* **The compass.** The status line shows `Home:NW 187`, the direction and
  distance to the centre, and a compass rose in the top-right corner of
  the map points home. Option `compass` turns both off.

## The centre: the sacred plaza

You begin standing on the **high altar of your own god**, in the middle of
a marble plaza. The high altars of the other two gods stand on either side.

* **Winning:** carry the Amulet of Yendor back here and `#offer` it on your
  god's high altar. A hero who converted can win at the altar of their new
  god. Offering the Amulet at another god's high altar goes the way it
  does on the Astral Plane in NetHack.
* The high altars accept nothing but the Amulet: **offering a corpse here
  just gives a message**, with no penalty and no time used.
* Offering the Amulet at an ordinary altar tells you to go home.
* Infidels win differently; see [the Infidel](Variant_differences.md#infidel).

## The lands

The world is made of zones, which get harsher with depth:

* **Meadows** near the centre; **woods** and **deep forest**; **hills**;
  **mountains** (solid stone you can dig through, walled by cliffs, with
  caves in the largest); **lakelands**; **swamps**; **frozen tundra**;
  **desert** with the occasional oasis; **ancient ruins**.
* **Roads** run outward from the plaza.
* **Towns** have shops, a temple with a priest, houses and townsfolk.
  Big towns in the first 14 rings also have a **town watch**, which reacts
  to the usual crimes (don't dip in their fountains); villages have none.
  Only the watch of the town you are in hears of trouble you cause there,
  not every watchman in the world. A town may grow up around a magic
  portal, leaving a small open square around it. Far out, towns are
  abandoned and haunted.
* **Walled compounds** hold what special rooms hold in NetHack (throne
  rooms, zoos, beehives, barracks, morgues, leprechaun halls, anthills,
  cockatrice nests), at the depths where those rooms would normally
  appear. There are also ruins, shrines, monster camps, graveyards and
  oases. A camp's band, a graveyard's dead and the like are never
  stronger than monsters wandering in at that depth would be.
* **Treasure vaults**, with their guards, are sealed inside mountains.
  Beyond depth 10 one of them may hold the portal to Fort Ludios.

## Monsters only act near you

Anything more than about 60 squares away across, or 30 up and down (about
a screen away), rests where it is: a depth-40 monster never wanders in to
find a depth-1 hero. The exceptions are the same as in NetHack: the Wizard
of Yendor, and covetous monsters when you carry what they want. Shopkeepers
and vault guards who are following you don't doze off either.

## Portals and branches

Every special level is its own small **branch**, reached through **magic
portals evenly spaced around the ring at the depth where that place
belongs**. Bigger rings have proportionally more portals. Each portal
stands in a circle of standing stones with its destination engraved beside
it.

* **Leaving a branch, by its up stairs or its portal, brings you back to
  the very portal you went in by.**
* Branches with several levels (the Mines, Sokoban, the Quest,
  Medusa/Castle, Vlad's Tower, the Wizard's Tower and others) keep their
  stairs between their own levels.
* `#overview` (Ctrl-O) lists the portal rings you have found.
* Depths are randomised per game, the way NetHack randomises branch
  levels. See [Portal rings](Portal_rings.md) for the table.
* Your **Quest** is a branch like any other; the leader's call comes when
  you first reach its ring.

## Gehennom

The outermost rings are Gehennom itself (scorched plains, lava fields,
obsidian mazes and caverns), walled off from the rest of the world by
**the Barrier**, a ring of impassable, undiggable mountains two rings
beyond Medusa's.

* **Getting in works as it always has:** take the portals to Medusa's
  Island, get past Medusa and the Castle, and drop through the Castle's
  trap doors into the Valley of the Dead. The Valley's way down (a portal
  where its down stairs used to be) opens onto the far side of the
  Barrier; gates there lead back into the Valley.
* You can't level-teleport past the Barrier until you have entered
  Gehennom.
* **One vibrating square.** The Gates of Moloch branch, two rings in from
  the outer edge of the world, is two levels: the invocation maze with
  the vibrating square, then Moloch's Sanctum. Its ring has dozens of
  portals, but they all lead to the same two levels.
* **The mysterious force.** While you carry the Amulet in Gehennom, it may
  push you back outward when you cross into a shallower ring: the
  open-world version of being pushed back down the stairs. Infidels are
  spared, as in EvilHack.

## What works differently

| NetHack | Here |
|---|---|
| Level teleport | Moves you between rings: pick a depth, arrive at that ring. |
| Cursed potion of gain level | Carries you one ring inward. |
| Monsters that level-teleport | Leave for another part of the world. |
| Digging down, trap doors, holes | **No "down" in the open world**: digging down makes a pit, and no trap doors or holes are generated there. They still exist in the branches (the Castle's still lead to the Valley). |
| "Whole level" effects | Magic mapping, object/gold/trap/monster detection, clairvoyance, the crystal ball, random in-level teleports and level sounds cover your surroundings (about 120 × 60 squares, several classic levels' worth). Taking the whole 1700 × 1700 world literally would map land that doesn't exist yet, or make these items vastly stronger than in NetHack. |
| Bones | Not left in the open world itself (it is the whole world); they work in the branches. |
| Scroll of earth outdoors | Boulders appear out of thin air instead of falling from a ceiling. |
| Ceiling hiders | Piercers and friends only hide where there is a roof (buildings, caves). |
| Elemental and Astral Planes | Omitted; you win at the centre instead. |
| Interfaces | tty (terminal) only. |
