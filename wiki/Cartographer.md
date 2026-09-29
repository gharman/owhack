# Cartographer

[Home](Home.md) · [Quest](Cartographer_quest.md) · [Techniques](Techniques.md)

The **Cartographer** is the role new to NetHack: Open World: a mapmaker and
explorer, made for a world of compass, rings and portals. Cartographers see
the lie of the land around them, always know where they are, find their
way to portals and towns, and can step straight back to a place they have
marked.

| | |
|---|---|
| Abbreviation | Car |
| Alignments | lawful, neutral or chaotic |
| Races | human, elf, dwarf, gnome, centaur, tortle, [ghost](Ghost_race.md) |
| Genders | male or female |
| Gods | Janus (lawful; doorways and journeys), Terminus (neutral; boundaries and boundary stones), Trivia (chaotic, female; crossroads) |
| Starting pet | pony (saddled, unless your race can't ride) |
| Spellcasting stat | Intelligence |
| Special spell | magic mapping |
| Quest leader | [Anaximander](Cartographer_quest.md#anaximander), Master of the Society of Cartographers |
| Quest nemesis | [Asterion](Cartographer_quest.md#asterion), the Minotaur of the Labyrinth |
| Quest artifact | [The Celestial Sextant](Celestial_Sextant.md) |
| Gift artifact | [Pathfinder](Pathfinder.md) |

## Starting inventory

* +1 quarterstaff (wielded)
* +0 sling, and 10–19 flint stones (quivered)
* +0 leather armor and +0 low boots
* an oil lamp
* a magic marker (19–22 charges) and 3 scrolls of blank paper
* 2 scrolls of magic mapping
* a blessed spellbook of light
* 2 food rations
* a [sextant](Sextant.md)

Cartographers start knowing the sextant, the magic marker, and the scroll
and spellbook of magic mapping, so blank paper plus the marker means more
maps. Centaurs and tortles can't wear the boots (and tortles not the
armor), so they start without them; ghosts leave their heaviest things
behind, see [Ghost](Ghost_race.md#starting-out).

## Attributes and growth

* Initial attributes are rolled from a base of St 7, In 10, Wi 9, Dx 9,
  Co 8, Ch 7, weighted toward Intelligence, Wisdom, Dexterity and
  Constitution.
* Hit points: 12 at level 1, then d8 per level to level 12 and 1 per
  level after (plus the race's share).
* Energy: 2 + d2 at level 1, then d2 per level (plus the race's share).
* Spellcasting is moderate: a base penalty of 4, between the
  Archeologist's and the Priest's; +2 for a shield, +10 for metallic body
  armor; magic mapping, the special spell, gets the usual special-spell
  bonus.

## Ranks

| XL | Title |
|---|---|
| 1–2 | Scribbler |
| 3–5 | Draughtsman / Draughtswoman |
| 6–9 | Wayfinder |
| 10–13 | Explorer |
| 14–17 | Chartmaker |
| 18–21 | Pathfinder |
| 22–25 | Geographer |
| 26–29 | Cosmographer |
| 30 | Master Cartographer |

## Skills

| Skill | Max |
|---|---|
| quarterstaff, sling, riding, divination spells | Expert |
| dagger, short sword, crossbow, dart, boomerang, pick-axe, escape spells | Skilled |
| knife, club, unicorn horn, bare hands, matter spells, enchantment spells | Basic |

Divination starts at Basic, and so does riding, thanks to the pony.

## Intrinsics

| XL | |
|---|---|
| 1 | **Surveyor's eye** (below) |
| 3 | automatic searching ("You feel perceptive!") |
| 7 | speed ("You feel quick!") |
| 11 | clairvoyance, as from donating to a priest: every 15 to 45 turns you glimpse the map around you ("You feel clairvoyant!") |
| 15 | warning ("You feel sensitive!") |

### Surveyor's eye

As you travel, the lie of the land within **2 + XL/6 squares** of you (a
rough circle) goes onto your map, even where you can't actually see it: in
the dark, round corners, on the far side of walls. Only terrain is mapped;
secret doors and passages stay hidden, and it doesn't touch what you
remember of objects and traps. It works on every level, in the open world
too (but not on land that hasn't been made yet), and not while you are
blind, hallucinating, under water or engulfed.

It is small at first (radius 2) and grows to 7 at level 30. In the
open world it quietly fills in mountain faces and cave mouths you walk
past; in a dark cave or maze it keeps the walls around you on the map.

## Techniques

See [Techniques](Techniques.md#cartographer) for full details.

| XL | Technique | In short |
|---|---|---|
| 1 | **survey** | maps the terrain within 8 + XL/2 squares, and traps within half that; recharges in 250 − 5×XL turns (at least 50) |
| 3 | **triangulate** | tells you the direction and distance of the nearest magic portal (and where it leads) and the nearest town, and marks them on your map; in a branch, the nearest way out; recharges in 300 turns |
| 8 | **waymark** | sets a waymark where you stand; later, use it again to step straight back to it from anywhere on the same level (the open world is one level); recharges in 1000 − 20×XL turns (at least 200) after a return |

## Artifacts

* **[The Celestial Sextant](Celestial_Sextant.md)** (quest artifact): a
  perfect sextant that works anywhere. Carried, it gives magic resistance
  and marks nearby magic portals on your map; invoked, it maps the
  neighbourhood and marks every portal of your ring and the rings on
  either side.
* **[Pathfinder](Pathfinder.md)** (gift artifact, quarterstaff): +d5 to
  hit, +d6 damage, makes you fast while wielded; invoked, a controlled
  level teleport (in the open world, pick a ring).

## Strategy

* **Getting around.** The open world is big. The
  [sextant](Sextant.md) tells you where the portals of every ring you know
  about are; *triangulate* finds the nearest portal and town even on a ring
  you haven't charted; `_` travel does the walking. Set a *waymark* at a
  town, or at the plaza, before a long trip out, and you have a way home
  that doesn't need a scroll.
* **The waymark doesn't work while you carry the Amulet**, so the walk
  home from Gehennom is still a walk.
* **Early fighting.** The sling and flint stones are your ranged attack;
  the quarterstaff is your melee weapon and a skill you can take to Expert.
  Riding goes to Expert too, and a pony is faster than you are.
* **Magic.** Divination is your school: light at first, detect monsters
  and clairvoyance later, and magic mapping as your special spell. With the
  marker and the known scroll of magic mapping you can write more maps.
* **The quest.** [Asterion](Cartographer_quest.md#asterion) ignores
  Elbereth, as every minotaur does, and his umber hulks confuse with their
  gaze. See the [quest page](Cartographer_quest.md).

## Player-monster cartographers

Hostile cartographers turn up in the Adventurers' Guild and as random
player-monsters, usually with a quarterstaff (or a short sword or dagger),
often a helm of brilliance, and sometimes a sextant and scrolls of magic
mapping. The Society's surveyors carry quarterstaves or short swords,
leather armor, low boots, sometimes a sling with flint, and now and then a
sextant.
