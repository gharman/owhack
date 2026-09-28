# NetHack: Open World

A modified NetHack 5.0 (the successor to 3.7) in which the Dungeons of Doom
and Gehennom have been replaced by one enormous, open, outdoor world.  Every
other part of NetHack is still here: all the roles, races, alignments and
genders, character creation, every monster, object, spell, artifact and
trap, the gods with altars, prayer, sacrifice, crowning and gifts, shops and
shopkeepers, temples and priests, the Oracle, Sokoban, the Gnomish Mines,
Minetown, the Quest, Fort Ludios, Medusa, the Castle, the Valley, the demon
lords, Vlad's Tower, the Wizard's Tower, the invocation, Moloch's Sanctum and
the Amulet of Yendor.  The full command set (including every `#` extended
command) works as it does in NetHack.

## Playing

    ./play.sh              start (or resume) a game
    ./play.sh -u Name      play as Name
    ./play.sh -s           high scores
    ./play.sh -D           wizard (debug) mode (sysconf allows user "gharman")

Terminal (tty) only.  Colour is on.  **Number-pad movement is on by default**
(set `number_pad:0` in `~/.nethackrc` if you ever want vi-keys).  A bigger
terminal window shows more of the world; the map uses the whole window.

In the game, `?` then "About the open world (read this first)" explains
everything below.

### The world

* **You start at the centre of the world**, standing on the *high altar* of
  your own god in a marble plaza.  The high altars of the other two gods
  stand on either side.
* The land is divided into **concentric rings**, 16 squares wide.  **Your ring
  is your depth**: it is the `Dlvl` on the status line and it drives monster
  and object generation, difficulty, prizes and everything else exactly as
  dungeon depth does in NetHack.  Walking outward is like going downstairs.
* **Compass:** the status line shows `Home:NW 187` (direction and distance to
  the centre), and a compass rose in the top-right corner of the map points
  home.  Option `compass` turns both off.
* **The map scrolls; you stay in the middle of the screen.**  Option
  `centerview` (on by default) turns that off for classic half-screen
  scrolling.
* **No stairs and no rooms-and-corridors.**  Instead there are zones:
  meadows, forests and deep woods, hills, mountain ranges (solid stone walled
  by cliffs, with caves, which you can dig through), lakes, swamps, tundra,
  deserts with oases, ruins, graveyards, monster camps and shrines.  Roads
  run outward from the plaza.  **Towns** have shops, a temple with a priest,
  houses, townsfolk and the town watch (don't mess with the fountains);
  far out, towns are abandoned and haunted.  Throne rooms, zoos, beehives,
  barracks, morgues, leprechaun halls, anthills and cockatrice nests appear
  as walled compounds at the depths where they would normally appear.
  Treasure vaults (with their guards) are sealed inside mountains.
* **Monsters only act near you.**  Anything more than about a screen away
  rests where it is, so a depth-40 monster never wanders in to find a
  depth-1 hero.  (The Wizard of Yendor, and covetous monsters when you carry
  what they want, are the exception, as in NetHack.)

### Branches and portals

Every special place is reached through **magic portals, evenly spaced around
the ring at the depth where that place belongs**.  Bigger rings have
proportionally more portals.  Each portal stands in a circle of standing
stones with its destination engraved beside it.  **Leaving a branch (by its
up stairs or its portal) brings you back out at the very portal you went
in by.**  `#overview` (Ctrl-O) lists the portal rings you have found.

Depths are randomised per game, the same way NetHack randomises branch
levels:

| Ring (depth) | Portals lead to |
|---|---|
| 2-4 | the Gnomish Mines (Minetown, Mines' End) |
| 5-9 | the Oracle |
| Oracle+1 | Sokoban (entered at the bottom, as usual) |
| 10-12 | the Big Room (only in some games) |
| Oracle+6 or +7 | your Quest (the leader's call comes when you first reach that ring) |
| 11 to Medusa-1 | Fort Ludios: a portal inside one of the mountain vaults |
| 21-24 | Medusa's Island; the Castle is below it |
| Medusa+2 | the Barrier: impassable, undiggable mountains ringing Gehennom |
| beyond | Gehennom: scorched plains, lava fields, obsidian mazes, caverns |
| in Gehennom | Asmodeus, Juiblex, Baalzebub, Orcus Town, Vlad's Tower, the Wizard's Tower, the two fake wizard towers, the Gates of Moloch |

**Getting into Gehennom** works as it always has: get past Medusa, then the
Castle, and drop through the Castle's trap doors into the Valley of the Dead.
The Valley's way down (a portal where its down stairs used to be) opens onto
the far side of the Barrier.  Gates there lead back into the Valley.  You
can't level-teleport past the Barrier until you have entered Gehennom.  The
vibrating square is at the Gates of Moloch; performing the invocation there
opens the stairs down to Moloch's Sanctum and the Amulet.

### Winning

Carry the Amulet of Yendor back to the centre of the world and `#offer` it
on the high altar of your god.  Since the three high altars cover all three
gods, a hero who converted can still ascend at the altar of their new god.
Offering the Amulet at another god's altar goes the way it does on the Astral
Plane.  The high altars accept nothing but the Amulet: offering a corpse
there just gives a message (no penalty, no time used).  Offering the Amulet
at an ordinary altar tells you to go home.

On the way back, the Wizard of Yendor harasses you as usual, and while you
are still in Gehennom the "mysterious force" may push you back outward when
you cross into a shallower ring (the open-world version of being pushed back
down the stairs).

## What changed, and why

Everything not listed here plays as it does in NetHack 5.0.

* **The Elemental Planes and Astral Plane are omitted** (as requested).  You
  win at the central high altar instead.
* **No filler levels.**  The random rooms-and-corridors levels of the
  Dungeons of Doom, and the random maze levels of Gehennom, are replaced by
  the overworld and its Gehennom rings.  The special levels are kept intact,
  each as a branch behind its ring of portals.  Branches with several levels
  (Mines, Sokoban, Quest, Medusa/Castle, Wizard's Tower, Vlad's Tower, Gates
  of Moloch) keep their stairs between their own levels.
* **Level teleportation** moves you between rings (you pick a depth, as
  usual, and arrive at that ring).  A cursed potion of gain level carries you
  one ring inward.  Monsters that level-teleport in the overworld leave for
  another part of the world.
* **There is no "down" in the open world.**  Digging down makes a pit, and
  no trap doors or holes are generated there.  Trap doors and holes still
  exist in the branches (the Castle's still lead to the Valley).
* **"Whole level" effects cover your surroundings** (about 120x60 squares,
  several classic levels' worth) rather than the whole 1700x1700 world:
  magic mapping, object, gold, trap and monster detection, clairvoyance, the
  crystal ball, random in-level teleports, and level sounds (you hear the
  fountain or the shopkeeper that is actually nearby).  Taking the literal
  whole world would either be meaningless (mapping land that doesn't exist
  yet) or would make these items vastly stronger than in NetHack.
* **No bones files for the overworld** itself, because it is the entire
  world rather than one level.  Bones still work on the levels of the
  branches.
* **The Wizard's Tower, Vlad's Tower and the demon lairs** are their own
  small branches in Gehennom's rings, rather than levels of one long
  Gehennom dungeon.
* **Scroll of earth outdoors** still works: the boulders appear out of thin
  air instead of falling from a ceiling.  Piercers and other ceiling
  hiders only hide where there is a roof (buildings and caves).
* **Only the tty interface** is supported (terminal, as requested; no tiles,
  X11, Qt or curses interfaces).
* **Wizard-mode `#wizmakemap`** regenerates the overworld around you; the
  Fort Ludios portal doesn't come back if it was already placed.

## New roles

**Pirate** (from SLASH'EM Extended / SlashTHEM, as in SpliceHack and
Hack'EM; human, gnome, orc, illithid, tortle, vampire, werewolf or ghost;
neutral or chaotic).  Starts with a cutlass (scimitar), a flintlock and
bullets, knives, a leather jacket, high boots, rum, sea biscuits, bananas,
an oilskin sack and a ring, a parrot (or a monkey) for a pet, and can swim.
Firearms are a new skill: a flintlock fires one bullet per turn at up to
eight squares, bullets are used up, a flintlock misfires now and then and
can jam (from curses, rust, clumsiness, bad luck or lack of skill; grease
wears off first, blessed guns resist); a jammed gun is unjammed with
grease, a greased towel, a dip in oil or enchant weapon, and a cursed gun
loaded with cursed bullets blows up.  Monsters use flintlocks the same way.
Pirates hear every message in pirate speech, know many things by pirate
names (rum, cutlass, sea biscuit, ditty bag, coffer, eye-patch, ...;
potions are bottles), find more artifacts, and rise as skeletal pirates
when they die.  Their only sacrifice gift is the Marauder's Map (read it
to map your surroundings, again and again; invoke it to detect objects);
crowning makes you the Pirate King (or Queen) with Reaver, the cutlass that
steals.  The quest (Tortuga, Shipwreck Island, Blackbeard's Ghost) is won
for the Treasury of Proteus, a sea chest that absorbs curses and
polymorphs what you keep in it, and brings undead pirates after you.

**Convict** (the Convict patch, as in EvilHack and Hack'EM; any race of
the role x race table, always chaotic).  Starts hungry, punished with a
heavy iron ball and chain, in a cursed striped shirt, with a spoon, some
rocks and a sewer rat for a pet.  Shopkeepers won't let anyone wearing a
visible striped prison shirt into their shops, and the town watch and vault
guards know a convict's face from the wanted posters (unless the convict is
polymorphed or has covered their face with a towel or blindfold).  Domestic
animals are wary of convicts, but rats can be soothed with chittering
(#chat); convicts stomach rotten and nasty food better and last twice as
long once hungry, are sickness and (later) poison resistant, feel no guilt over robbing shops or killing
guards, and make sneak attacks with a spoon on fleeing or helpless foes.
Their gods are Faerûnian (Ilmater, Grumbar, Tymora).  Sacrifice gifts
include the Luck Blade.  The quest (Castle Waterdeep Dungeon, the
Warden's Level, Warden Arianna) is for the Iron Spoon of Liberation
(chosen over SLASH'EM's Iron Ball and EvilHack's Striped Shirt, following
Hack'EM): it digs like a pick-axe and engraves like an athame, frees you
from a ball and chain, and can be invoked to walk through walls.

**Infidel** (by Tomsod, from EvilHack; human, elf, orc, giant, centaur,
illithid, draugr or vampire).  A cultist of Moloch: unaligned, with a
random role's pantheon as the three gods of heaven.  The Cult entrusts
the Infidel with the Amulet of Yendor from the start; Moloch demands
regular sacrifices and hears prayer outside Gehennom only now and then
(always while you carry the Idol of Moloch); Infidels shrug off curses,
are hated by lawful angels and liked by demons, and a crowned Infidel
becomes a demon with wings (folded under hard body armour) and a barbed
tail.  The quest (the Hidden Temple, the Howling Forest, the Paladin) is
for the Idol of Moloch.  *Winning, open-world style:* take the Amulet to
Moloch's Sanctum and offer it on Moloch's high altar while carrying the
Idol: Moloch takes the Amulet and imbues the Idol with its power (an
Infidel without the Idol is refused).  Then carry the imbued Idol back to
the centre of the world and `#invoke` it on the high altar of the one god
of heaven Moloch means to overthrow: the altar becomes Moloch's and you
ascend as the Archfiend of Moloch.  Invoking it on either of the other two
high altars brings that god's wrath; the quest leader and the Sanctum's
high priest hint which altars to avoid.  This is EvilHack's rule (there,
the three high altars are on the Astral Plane) moved to the three high
altars of the sacred plaza; an Infidel starts in the plaza, just south of
the middle altar, since no altar there is theirs.  Everyone else still
wins by offering the Amulet at their own god's high altar.

## Files

    play.sh                 launcher
    game/                   the installed game: nethack, nhdat, sysconf,
                            high scores, save/ directory
    source/NetHack-openworld/
                            full source, as a git repository; the first
                            commit is stock NetHack 5.0 plus a few small
                            hooks for the automated test harness, so
                            "git diff <first commit>" shows every change
    source/NetHack-openworld/build.sh
                            rebuilds and reinstalls into ../../game

The heart of the variant is `src/overworld.c` (world generation, rings,
portals, zones, towns, compass, monster dormancy) and `include/openworld.h`.
The rest is spread across about 60 NetHack source files, mainly
`display.c` and `win/tty/wintty.c` (the scrolling viewport),
`vision.c`, `teleport.c`, `do.c`, `mklev.c`, `dungeon.c`, `hack.c`
(travel), `save.c`/`restore.c` (compressed map saving) and
`dat/dungeon.lua` (the dungeon layout).

## Testing that was done

* Automated play through a pipe-driven terminal emulator: character creation
  for all roles, walking, fighting, shopping, the town watch, the temple
  priest, vault guards, the quest call and quest entry/expulsion, every
  portal ring and branch round trip (Mines, Oracle, Sokoban, Big Room, Quest,
  Ludios, Medusa, Castle to Valley by trap door, Valley to Gehennom, every
  Gehennom branch), the invocation and the Sanctum, the mysterious force,
  ascension at the central altar, save and restore.
* Several hours of NetHack's built-in `--debug:fuzzer` random-input play,
  in normal and wizard mode, including AddressSanitizer builds.  Every
  crash or sanity-check failure found was fixed.
* Performance: roughly 60 ms per move in a 200x60 terminal, world generation
  a few milliseconds per 32x32 area as you explore; save files are around
  0.5 MB early on and grow as you explore.
