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

On top of that, the world holds the extra special levels of Slash'EM,
Hack'EM and EvilHack: One-eyed Sam's black market, Grund's Stronghold, the
lairs of the Rat King and the Kobold King, the Wyrm Caves, the Spider
Caves, the Sunless Sea, the Lost Tomb, the Giant Caverns, the Temple of
Moloch, the Guild of Disgruntled Adventurers, the Mall, the Storerooms,
the nymphs' garden, Goblin Town, Slash'EM's three alignment key quests,
the Gnome King's level at the bottom of the Mines, the dungeon beneath
Fort Ludios, Frankenstein's Lab and lairs for Yeenoghu, Demogorgon, Geryon
and Dispater, with the monsters and artifacts that belong to them (see
[Extra special levels](#extra-special-levels)).

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
| 2-4 | the Gnomish Mines (Minetown, Mines' End, the Gnome King's level) |
| 2-3 | Goblin Town (2 levels) |
| 5-6 | the Mall (only in some games) |
| 5-9 | the Oracle |
| Oracle+1 | Sokoban (entered at the bottom, as usual) |
| 8 to Medusa-1 | Aphrodite's Garden, the nymph level (only in some games) |
| 10-11 | the Rat King's Lair (only in some games) |
| 10-12 | the Big Room (only in some games) |
| 11-12 | the Kobold King's Lair (only in some games) |
| 12-13 | Grund's Stronghold |
| Oracle+6 or +7 | your Quest (the leader's call comes when you first reach that ring) |
| 11 to Medusa-1 | Fort Ludios: a portal inside one of the mountain vaults (2 levels) |
| 15-19 | the Nightmare's, the Beholder's and Vecna's lairs (the alignment key quests) |
| 14 to Medusa-1 | in about this order: the Storerooms (only in some games), the Wyrm Caves (2 levels), the Lost Tomb, One-eyed Sam's Market, the Spider Caves, the Adventurers' Guild (only in some games), the Sunless Sea, the Temple of Moloch, the Giant Caverns |
| 21-24 | Medusa's Island; the Castle is below it |
| Medusa+2 | the Barrier: impassable, undiggable mountains ringing Gehennom |
| beyond | Gehennom: scorched plains, lava fields, obsidian mazes, caverns |
| in Gehennom | Asmodeus, Juiblex, Baalzebub, Orcus Town, Vlad's Tower, the Wizard's Tower, the two fake wizard towers, the Gates of Moloch; Yeenoghu's and Demogorgon's lairs near the Valley, Geryon's and Dispater's deep down, Frankenstein's Lab in between |

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

## New roles

Besides NetHack's thirteen roles, four roles from Slash'EM (in the form
Hack'EM gives them; the Jedi comes from SlashTHEM) can be chosen, each with
its own quest (entered, like every quest here, through the portals on its
ring), quest artifact, sacrifice gift and pet.

* **Necromancer** (chaotic).  A caster of the dark arts who starts with
  the spells of summon undead, command undead and drain life, wands of
  draining and fear, and a pick-axe for digging up graves.  Undead are
  sometimes peaceful to a necromancer and are the only creatures one can
  tame; zombies can be charmed with an ancient chant (#chat).
  Necromancers see whether things are blessed or cursed, resist level
  drain and sickness, and are warned of undead.  The quest: recover the
  Great Dagger of Glaurgnaa from the demon Maugneshaagar for the Dark Lord.
  Gift: Serpent's Tongue, a poisonous dagger.
* **Flame Mage** (lawful or neutral).  A master of fire: fire resistant
  (which also protects the flame mage's belongings), casts fire bolt,
  fireball and flame sphere more easily, carries a wand of fire and a fire
  bomb; from experience level 5 on vulnerable to cold, and unable to learn
  cold spells.  The quest: retrieve the Candle of Eternal Flame from the
  Water Mage for the High Flame Mage.  Gift: Firewall, a burning staff.
* **Ice Mage** (neutral or chaotic).  The cold counterpart: cold resistant,
  casts freeze sphere and cone of cold, reads scrolls of ice, walks on
  water from level 15 on and never slips on ice; vulnerable to fire from
  level 5.  The quest: take the Storm Whistle back from Ragnaros, lord of
  fire elementals, for the High Ice Mage.  Gift: Deep Freeze, an icy staff.
* **Jedi** (lawful).  A warrior of the Force armed with a lightsaber,
  which has to be applied to switch it on, lights the area, uses up its
  charge while lit (a scroll of charging refills it, and from experience
  level 5 so does the charge saber technique, which pours the Jedi's
  energy into it) and only cuts when lit; it can melt locks and cut
  through doors (#force).  A skilled Jedi deflects missiles, cuts foes'
  weapons in half and can throw the lit lightsaber and call it back with
  the Force.  Jedi fight in robes, not armor, and must not attack the
  peaceful.  The quest: find the Lightsaber Prototype in the Outer Rim
  before Lord Sidious does.
  Gift: the cloak Deluder.

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
* **Extra special levels** from Slash'EM, Hack'EM and EvilHack are added
  (below).  Slash'EM places many of them deeper than our Medusa, which is
  at depth 21-24 with Gehennom beyond it, so they are squeezed, in their
  Slash'EM order, into the rings between depth 14 and Medusa's; Slash'EM's
  Gehennom levels are spread over our Gehennom rings.

## Extra special levels

Each is a branch behind its own ring of portals, like the vanilla special
levels; leaving it (by its up stairs or its portal) brings you back to the
portal you used.  Those marked "(some games)" exist only in some games, as
in their home variants.  The levels are faithful conversions of the
originals to NetHack 5.0's Lua level format; features 5.0 lacks (Hack'EM
grass, sewage and dead trees, EvilHack forges, Slash'EM "killer coins") are
replaced by the nearest thing 5.0 has.

* **One-eyed Sam's Market** (Slash'EM): Sam's black market, the biggest
  shop in the game, stocked with every kind of object, laid out class by
  class, at 25 times the usual price (50 times for anything magical).  Sam
  is a formidable fighter (Thiefbane, reflection, speed, life saving); he
  welcomes invisible customers but not ones who have polymorphed into
  something inhuman.  Pets and steeds
  can't enter, taming and Conflict don't work, and you can't level
  teleport out.  Shoplift and his assistants (the named monsters of the
  market) turn on you, while soldiers gather at the way out.
* **Grund's Stronghold** (Slash'EM, 3 versions): Grund the Orc King's
  fortress, full of orcs and ogres.
* **The Rat King's Lair** (Slash'EM, and Hack'EM's sewer; some games),
  **the Kobold King's Lair** (Kroo; Slash'EM, 2 versions; some games),
  **Aphrodite's Garden** (the nymph level; some games), **the Storerooms**
  (3 versions; some games), **the Mall** (a town of shops; 2 versions; some
  games) and **the Adventurers' Guild** (the Guild of Disgruntled
  Adventurers: hostile player monsters of every role; some games).
* **The Wyrm Caves** (Hack'EM, 2 levels): an orc-guarded entrance and a
  dragon pit with a hoard.  **The Spider Caves** (Shelob and Girtab),
  **the Sunless Sea** (sharks, crabs and treasure island), **the Lost
  Tomb**, **the Giant Caverns** (the Largest Giant) and **the Temple of
  Moloch** (Slash'EM).
* **Goblin Town** (EvilHack, 2 levels): the Goblin King's town under the
  mountains, with his prisoners; a trap door leads down to Gollum's cave.
* **The Nightmare's Lair, the Beholder's Lair and Vecna's Lair**:
  Slash'EM's alignment key quests.  Their masters leave the artifacts
  Nighthorn, the Eye of the Beholder and the Hand of Vecna.
* **The Gnome King's level** (Slash'EM / Hack'EM, 2 versions) is now the
  bottom of the Gnomish Mines, below Mines' End; **Fort Ludios** has
  Hack'EM's dungeon beneath the fort.
* In Gehennom: **Frankenstein's Lab** (Doctor Frankenstein and his
  Monster) and Slash'EM's lairs for **Yeenoghu, Demogorgon, Geryon and
  Dispater**, the demon lords that vanilla NetHack gives no lair.

## Files

    play.sh                 launcher
    game/                   the installed game (not tracked by git): nethack,
                            nhdat, sysconf, high scores, save/ directory
    source/NetHack-openworld/
                            full source
    source/NetHack-openworld/build.sh
                            rebuilds and reinstalls into ../../game (creates
                            game/sysconf if it is missing; saves and scores
                            are never touched)

This directory is a git repository.  The source history begins with stock
NetHack 5.0 plus a few small hooks for the automated test harness (tagged
`nethack-5.0-baseline`), so

    git diff nethack-5.0-baseline HEAD:source/NetHack-openworld

shows every change made for this variant.

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
* The extra special levels: wizard-mode tours into and out of every new
  branch through its portal (and down to the lower levels of the
  two-level branches, the Gnome King's level and the dungeon beneath
  Fort Ludios), checking the monsters of each level; every level file
  regenerated repeatedly with sanity checking; buying, selling and
  shoplifting in One-eyed Sam's market; save and restore inside the new
  branches; and fuzzing with games that start inside them.
* Performance: roughly 60 ms per move in a 200x60 terminal, world generation
  a few milliseconds per 32x32 area as you explore; save files are around
  0.5 MB early on and grow as you explore.
