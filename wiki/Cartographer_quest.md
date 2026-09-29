# The Cartographer quest

[Home](Home.md) · [Cartographer](Cartographer.md)

> *"Our greatest treasure, the Celestial Sextant, has been stolen. With it
> the first of our Society took the sightings that fixed every road of the
> world in its place, and with it we have kept them there ever since. Now
> it is in the hands of Asterion, the Minotaur of the Labyrinth. […] With
> the Celestial Sextant to guide him, he is folding the roads of the world
> into his Labyrinth, one by one."* — Anaximander

As with every quest in this build, you reach it through the portals on
the quest ring (Oracle + 6 or + 7), and the leader's call comes when you
first reach that ring. You need **experience level 14** and a good
alignment record to be given the quest, as usual.

| | |
|---|---|
| Home | the Hall of Charts |
| Locate | the Edge of the Map |
| Leader | Anaximander, Master of the Society of Cartographers |
| Guardians | surveyors |
| Nemesis | Asterion, the Minotaur of the Labyrinth |
| Enemies | umber hulks, and random `q` quadrupeds |
| Artifact | [The Celestial Sextant](Celestial_Sextant.md) |

## Levels

### Home: the Hall of Charts

The library and observatory of the Society of Cartographers, on the shore
of the western sea. You arrive by portal in the garden to the west; the
way down is at the landing stage at the end of the pier. The domed
observatory in the middle holds Anaximander, the Society's strongbox and
eight surveyors. The four library stacks, kept dark, hold scrolls,
spellbooks and blank paper; busts of great cartographers stand in the
halls.

The Society's motto is engraved at the door: *Terra cognita: that which
is mapped is ours*. At the end of the pier someone has burned
*Hic sunt dracones*.

The grounds are overrun: umber hulks have burrowed up out of the lost
roads, beasts have strayed in, and giant eels and a shark are in the sea.
The level is no-teleport, the floor can't be dug, and the walls are
non-diggable.

```
TT....T........................................................}}}}}}}}}}}}}
....T..........................................................}}}}}}}}}}}}}
........|------|------------------------------|------|.........}}}}}}}}}}}}}
..T.....|......|.........----....----.........|......|......}}}}}}}}}}}}}}}}
........|.|.|..|.......---..........---.......|..|.|.|.....}}}}}}}}}}}}}}}}}
T.......|.|.|..+......--..............--......+..|.|.|.....}}}}}}}}}}}}}}}}}
...T....|.|.|..|......-................-......|..|.|.|......}}}}}}}}}}}}}}}}
........|......|......-................-......|......|.........}}}}}}}}}}}}}
.T......-------|--+----................----+--|-------.........}}}.....}}}}}
........+............+..................+............+.................}}}}}
........-------|--+----................----+--|-------........}}}}.....}}}}}
........|......|......-................-......|......|......}}}}}}}}}}}}}}}}
.T......|.|.|..|......-................-......|..|.|.|......}}}}}}}}}}}}}}}}
....T...|.|.|..+......--..............--......+..|.|.|.....}}}}}}}}}}}}}}}}}
T.......|.|.|..|.......---..........---.......|..|.|.|......}}}}}}}}}}}}}}}}
........|......|.........----....----.........|......|........}}}}}}}}}}}}}}
..T.....|------|------------------------------|------|.........}}}}}}}}}}}}}
................................................................}}}}}}}}}}}}
.....T........................................................}}}}}}}}}}}}}}
T..T........................................................}}}}}}}}}}}}}}}}
```

### Filler 1: the uncharted country

Open woodland and meadows with the odd lake, between the Hall of Charts
and the Edge of the Map.

### Locate: the Edge of the Map

The country here is coming unmoored. West of the river it is still honest
woodland; beyond it the ground is split by rifts that open onto nothing;
further east the land breaks up altogether into a maze, and the way down
into the Labyrinth is somewhere in that maze. The ruined camp of the last
survey party lies in the west, with the bodies of two surveyors and a
warning engraved beside it: *The road east goes round in circles. Turn
back.* The rifts can't be dug.

### Filler 2: the Shifting Ways

The outskirts of the Labyrinth, where roads that once went somewhere have
been folded into a maze.

### Goal: the Labyrinth

A great maze fills the whole level. You come down into its far west. At
its heart is **Asterion's chamber**, whose walls wind round in rings as the
old labyrinths did; you can only walk the rings one way round to reach the
middle, where Asterion waits with the Celestial Sextant beside him, a
chest, gems, a scroll and gold, and the bones of those who came looking
for it (two surveyors and a cartographer).

```
-------------------------------
|..............|..............|
|.---------------------------.|
|.|.........................|.|
|.|.-----------------------.|.|
|.|.|.....................|.|.|
|.|.|.....................|.|.|
..|.+.....................|...|
|.|.|.....................|.|.|
|.|.|.....................|.|.|
|.|.-----------------------.|.|
|.|............|............|.|
|.---------------------------.|
|.............................|
-------------------------------
```

The chamber's only way in is from the west, through the maze; its door
is locked. **Its walls can't be dug, even by umber hulks, and you can't
teleport within it.** The winding rings are trapped (a rolling boulder, a
spiked pit, and magic, rust and anti-magic traps). Five umber hulks, ten
`q` beasts and a few other monsters roam the maze.

## Anaximander

Named for the Greek philosopher who drew the first map of the world. A
level 20 human (speed 15, AC 0, 90% magic resistance), with a weapon attack
(4d10) and spells (2d8), carrying a +4 quarterstaff, a +1 cloak of magic
resistance and a sextant. Peaceful, as leaders are.

## Asterion

The Minotaur of the Labyrinth, the Bull of Minos: a unique `H`.

| | |
|---|---|
| Level | 18 (difficulty 21) |
| Speed | 15 |
| AC | 0 |
| Magic resistance | 50 |
| Attacks | weapon 2d6, butt 3d6, claw 1d4 (steals the Amulet or your quest artifact, as nemeses do) |
| Resists | poison, petrification |
| Size | large |

He carries a battle-axe. Asterion is treated as a minotaur everywhere
NetHack special-cases minotaurs: **he ignores Elbereth and scrolls of
scare monster**, has horns (no helmet fits him), and smells like one. He was toned down
during testing: with his first attacks (3d10 weapon, 4d8 butt, 2d6 claw
plus the axe) he killed a level 14 Cartographer at AC −9 in two or three
turns.

## Tips

* Bring a way to deal with confusion: umber hulks confuse with their
  gaze. A blindfold or towel stops the gaze; a unicorn horn cures the
  confusion.
* The Labyrinth's walls can't be dug; the land at the Edge of the Map
  (outside the rifts) can be.
* *Survey* and the surveyor's eye map the maze as you go; *triangulate*
  finds the stairs back up. You can't teleport inside Asterion's chamber.
* Asterion doesn't respect Elbereth. Fight him at range if you can
  (sling, crossbow, spells), or from a doorway.
* You may sense the Celestial Sextant when you are near.
