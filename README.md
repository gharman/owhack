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

On top of that come eight more roles (the Necromancer, Flame Mage, Ice
Mage, Jedi, Pirate, Convict and Infidel of Slash'EM, SlashTHEM, SpliceHack,
Hack'EM and EvilHack, and a new one, the Cartographer), nine more races
(giant, centaur, illithid, tortle, draugr, vampire, werewolf, doppelganger
and a new one, the ghost), Slash'EM-style techniques for every role and
most races, an object materials system (mithril, steel, silver, gold,
platinum, wood, gemstone, dragonhide, plastic, ...), drain and psychic
resistance, and skill training percentages in #enhance (see [New
roles](#new-roles), [New races](#new-races), [Techniques](#techniques) and
[Materials](#materials)).

The world also holds the extra special levels of Slash'EM,
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
everything below.  The [wiki](wiki/Home.md) goes into more detail on what
is unique to this build: the open world, the Cartographer and its quest,
the ghost race, techniques, and how the imported features were adapted.

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

Besides NetHack's thirteen roles there are eight more: seven from other
variants (the Necromancer, Flame Mage and Ice Mage of Slash'EM, as Hack'EM
has them; the Jedi of SlashTHEM; the Pirate of SpliceHack and Hack'EM; the
Convict and Infidel of EvilHack) and one new one, the Cartographer.  Each
has its own quest (entered, like every quest here, through the portals on
its ring), quest artifact, sacrifice gifts, starting pet, skills,
intrinsics and techniques.

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

* **Pirate** (from SLASH'EM Extended / SlashTHEM, as in SpliceHack and
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
* **Convict** (the Convict patch, as in EvilHack and Hack'EM; any race of
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
* **Infidel** (by Tomsod, from EvilHack; human, elf, orc, giant, centaur,
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

### The Cartographer

A mapmaker and explorer, made for a world of compass, rings and portals
(filecode `Car`; any alignment; human, elf, dwarf, gnome, centaur,
tortle or ghost; gods Janus, Terminus and Trivia).  Cartographers start
with a +1 quarterstaff, a sling and flint stones, leather armor and low
boots, an oil lamp, a magic marker with three sheets of blank paper, two
scrolls of magic mapping, a spellbook of light, food, a **sextant** and a
saddled pony (unsaddled for centaurs and ghosts, who can't ride).  They reach expert in quarterstaff, sling, riding and
divination spells (their special spell is magic mapping), and cast
moderately well, using Intelligence.

* **Surveyor's eye:** from the first level, the lie of the land within
  2 + XL/6 squares goes onto the Cartographer's map as they travel, even
  in the dark or on the far side of a wall (not while blind or
  hallucinating).  Later levels bring automatic searching (3), speed (7),
  clairvoyance (11) and warning (15).
* **The sextant** (a new tool that anyone can find or buy): apply it
  outdoors to take a sighting of the sun or stars.  It tells you your
  ring (depth), how far away and in which direction the centre of the
  world lies, and the distance and bearing of the nearest portal of each
  ring of portals you know about.  It needs a clear sky: not while blind,
  not under a roof, and in a branch it can only tell you your level and
  depth.  Cartographers read it exactly; anyone else with negative Luck
  gets a reading that is somewhat off.
* **Techniques** (`#technique`): *survey* (XL 1) maps the terrain for
  eight or more squares around; *triangulate* (XL 3) finds the nearest
  magic portal and the nearest town (in a branch, the nearest way out);
  *waymark* (XL 8) fixes a spot in memory and later steps straight back
  to it.
* **The quest:** Asterion, the Minotaur of the Labyrinth, has stolen the
  Society of Cartographers' Celestial Sextant, the instrument that fixes
  the roads of the world in place, and is folding the roads into his
  maze.  Anaximander, Master of the Society, calls from the Hall of
  Charts, a library and observatory by the sea; beyond lie the Edge of
  the Map, where the land breaks into rifts and mazes, and the Labyrinth
  itself.  Like every minotaur, Asterion ignores Elbereth.
* **The Celestial Sextant** (quest artifact) is a perfect sextant that
  works anywhere, even underground (in a branch it shows where in the
  world the branch's way out lies).  Carried, it gives magic resistance
  and marks nearby magic portals on your map; invoked, it maps the
  neighbourhood and marks every portal of your ring and of the rings on
  either side.
* **Pathfinder** (gift artifact, a quarterstaff): +d5 to hit, +d6
  damage, and makes its wielder fast; invoked, a controlled level
  teleport (in the open world, pick a ring) with the usual limits.

## New races

Nine races join NetHack's five.  Eight come from other variants (giant,
centaur, illithid, tortle and draugr from EvilHack; vampire from EvilHack,
Hack'EM and Slash'EM; werewolf and doppelganger from Slash'EM); the ghost is
new.  Which roles each race can take:

| race | alignments | roles |
|---|---|---|
| giant | any | Barbarian, Caveman, Monk, Priest, Samurai, Valkyrie, Wizard, Convict, Flame Mage, Infidel, Necromancer |
| centaur | neutral, chaotic | Barbarian, Healer, Monk, Priest, Ranger, Valkyrie, Cartographer, Convict, Ice Mage, Infidel, Necromancer |
| illithid | chaotic | Priest, Wizard, Convict, Ice Mage, Infidel, Necromancer, Pirate |
| tortle | lawful, neutral | Archeologist, Barbarian, Healer, Monk, Priest, Samurai, Tourist, Wizard, Cartographer, Jedi, Pirate |
| draugr | chaotic | Barbarian, Rogue, Convict, Ice Mage, Infidel, Necromancer |
| vampire | neutral, chaotic | Archeologist, Barbarian, Rogue, Wizard, Convict, Ice Mage, Infidel, Necromancer, Pirate |
| werewolf | chaotic | Barbarian, Rogue, Ranger, Convict, Pirate |
| doppelganger | neutral, chaotic | Healer, Monk, Priest, Rogue, Wizard, Convict |
| ghost | any | Archeologist, Priest, Rogue, Samurai, Tourist, Wizard, Cartographer, Convict, Necromancer, Pirate |

* **Giant**: huge, strong and slow; carries more, and carries, throws and
  steps onto boulders; can't wear body armor or cloaks, ride, or be
  stealthy; digs fast, kicks doors open, shatters weapons.
* **Centaur**: fast (speed 18) and a strong kicker; no boots and no
  riding; extra shots with bows and crossbows, and uses lances and
  polearms as if mounted.
* **Illithid**: a mind flayer: telepathic and psychic resistant, with a
  brain-eating tentacle attack, a psychic blast (#monster) and the psionic
  wave spell only illithids can learn; a heavy metal helmet blocks its
  psionics; flies from level 12.
* **Tortle**: a turtle folk that hides in its shell (#monster), swims and
  breathes water; natural armor that improves with level, but no body
  armor or boots.
* **Draugr**: an undead Norse warrior that eats only rotten meat, returns
  from death a few times, and bites to zombify; fire does it extra harm,
  and shopkeepers, the watch and lawful or neutral priests shun it.
* **Vampire**: lives on blood (drains fresh corpses, drinks potions of
  blood, feeds by biting); shapechanges into a bat, fog cloud or warg
  (#monster) from level 3; hurt by silver, fire and holy water; flies from
  level 12 and regenerates from level 20.
* **Werewolf**: born a lycanthrope, which can't be cured; changes into its
  wolf form at will (#youpoly) from level 3, and fights with berserk fury.
* **Doppelganger**: polymorphs at will (#youpoly) for power, remembering
  the forms it has eaten, and gains polymorph control at level 9.
* The undead races (draugr, vampire, ghost) are harmed by holy water and
  blessed weapons, are healed rather than killed by death rays, and are
  often left alone by ordinary undead; lawful gods don't answer them.

### The ghost (new)

A restless spirit who can pass through things, frightens the living, and
has a hard time with the physical world:

* **Drifts through walls, rock, trees, doors, bars and boulders**, but only
  while unburdened, and each move into solid matter costs 1 power point.
  Out of power, a ghost can't enter solid matter (and if already inside,
  each step costs a little health, so it can never get stuck).  Levels
  whose walls resist phasing (Sokoban and others) stop it.
* **Incorporeal**: ordinary physical blows and missiles do half damage,
  unless silver or blessed, or struck by another incorporeal being;
  grabs slip through it.  Always floats; doesn't breathe; resists cold,
  sleep and level drain; sees invisible; later gains stealth (5), poison
  resistance (9) and warning (13).
* **Frightening**: its melee hits may send foes fleeing; ordinary peaceful
  folk sometimes run from it; the *haunt* technique terrifies everything
  nearby.
* **Clumsy with material things**: half the usual carrying capacity; worn
  armor gives only half its base AC (enchantment counts in full); wielded
  weapons are at -2 to hit.  In exchange, bare hands deliver a chilling
  touch (extra cold damage).
* **Never eats and never gets hungry**, so it gains nothing from corpses.
* Polymorphed into a solid form, a ghost has that form's body and needs.

## Techniques

Every role and most races have Slash'EM-style **techniques**, special
abilities learned at experience levels (and lost again if drained below
them).  `#technique` (or `M-x`) lists them with their status (Prepared,
Active, Soon, Not Ready) and uses one; each then needs time to recharge.
The tables follow Hack'EM (Slash'EM, SlashTHEM) for the roles and races
they cover:

* Archeologist: appraisal, research (3).  Barbarian: berserk, rage
  eruption (5).  Caveman: primal roar.  Healer: surgery.  Knight: turn
  undead, healing hands (a chaotic knight gets souleater instead).  Monk:
  twelve martial techniques from pummel to spirit bomb.  Priest: turn
  undead, blessing, healing hands (10), revivification (30).  Rogue:
  pickpocket, critical strike, cutthroat (15).  Ranger: missile flurry.
  Samurai: kiii.  Valkyrie: weapon practice.  Wizard: reinforce memory,
  draw energy (3), power surge (5).
* Necromancer: reinforce memory, whistle undead, raise zombies,
  blood magic, souleater, power surge, revivification, spirit tempest.
  Flame and Ice Mages: reinforce memory, power surge, draw energy (and
  ice armor for the Ice Mage).  Jedi: jedi jump, charge saber (5),
  telekinesis (8), force push (14).  Pirate: tumble, hold breath (3),
  sunder (5).  Convict: pickpocket, slip free (5).  Infidel: curse,
  reinforce memory, draw energy (5).  Cartographer: survey, triangulate
  (3), waymark (8).
* Dwarf: rage eruption.  Gnome: vanish, tinker (7).  Giant: primal roar,
  berserk (10).  Centaur: missile flurry (5).  Illithid: mind blast.
  Draugr: berserk.  Vampire: dazzle, draw blood.  Werewolf: eviscerate,
  berserk (10).  Doppelganger: liquid leap.  Ghost: haunt.
* Reaching Skilled in a melee weapon teaches *disarm*.  NetHack's own
  `#turn` is the turn undead technique.

## Materials

Every object is made of a material, and many can come in several (ported
from xNetHack, with EvilHack's rules for material hatred): iron, steel,
mithril, copper, silver, gold, platinum, wood, bone, glass, gemstone,
leather, cloth, dragonhide, plastic, paper and others.  Names show it
("silver long sword", "mithril chain mail"), and you can wish for one
("wooden dagger") when it suits the object.

* Material changes weight, armor class (mithril +1 over iron; mithril body
  armor gives at least MC2), weapon damage and to-hit (glass and gemstone
  edges cut deeper, gold and platinum hit harder, wood and plastic
  weaker), erosion (only iron rusts, copper and iron corrode, wood burns,
  glass cracks and shatters, mithril, platinum and gems never erode) and
  price.  Elven gear tends to wood, copper, silver and mithril, dwarvish
  gear to iron, steel and mithril, orcish gear to iron and bone.
* **There are no mithril coats any more.**  Mithril is a material:
  elven chain mail comes in mithril, and any chain, splint, banded, plate
  or other metal mail may turn up made of it.  (Wishing for an "elven" or
  "dwarvish mithril-coat" still works.)
* Silver harms demons, vampires, werewolves and shades as always; **cold
  iron** harms elves and the fae; **copper** harms molds and bringers of
  disease.  Heroes of those races take the same harm, so an elf is better
  off with copper, wood or mithril (and gloves).

## Also new

* **#enhance** shows each skill as `[current / maximum]` and how far its
  training has come toward the next level, as a percentage (every 100% is
  a level, `MAX` when there is nothing left to train).
* **Drain resistance and psychic resistance** are full resistances, for
  monsters and heroes: undead, demons and lycanthropes resist level drain;
  mind flayers and other psychic monsters resist psionics; the hero can
  gain them from race, items (a tinfoil hat, a ring of psychic resistance)
  and polymorph.  Psychic resistance protects against mind flayers'
  psychic blasts and their memory-stealing tentacles.

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
    wiki/                   supplemental wiki: what is new or different in
                            this build (start at wiki/Home.md); build.sh
                            also makes HTML pages of it in game/wiki/
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
* The new roles, races, techniques and materials: character creation, a
  look at inventory, attributes, skills and techniques, a few turns of play
  and save/restore for every one of the 129 allowed role and race pairs;
  every new role's quest played through from its portal to the nemesis and
  back; wizard-mode checks of each technique, race mechanic, new object and
  artifact; normal-mode bot games with new role and race combinations; and
  many more hours of fuzzing, normal, wizard mode and AddressSanitizer,
  with every failure fixed except the one below.
* Known issue: once in the final 111 fuzzed games, the debug sanity check
  found a boulder resting on a lava square in a branch level (a boulder
  normally sinks into lava).  The cause wasn't found; it doesn't crash the
  game, and without sanity checking (which only wizard-mode debugging turns
  on) nothing is reported.
* Performance: roughly 60 ms per move in a 200x60 terminal, world generation
  a few milliseconds per 32x32 area as you explore; save files are around
  0.5 MB early on and grow as you explore.
