-- NetHack 5.0	dungeon dungeon.lua	(open world variant)
-- Copyright (c) 1990-95 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
-- The dungeon description file.
--
-- Open world: the first dungeon is the Overworld, a single enormous
-- outdoor level.  Its depth (difficulty) increases with distance from its
-- center.  Every other dungeon is a branch reached through a ring of
-- evenly spaced magic portals placed at the appropriate distance from the
-- center (see overworld.c); the ring distances play the role of the
-- 'base'/'range' values that normally position branches, so all branches
-- of the Overworld are nominally attached to its only level.
--
-- The Elemental Planes are not part of this variant: the game is won by
-- offering the Amulet of Yendor at the high altar in the Overworld's center.
dungeon = {
   {
      name = "The Overworld",
      bonetag = "D",
      base = 1,
      alignment = "unaligned",
      branches = {
         { name = "The Gnomish Mines", base = 1 },
         { name = "The Oracle", base = 1 },
         { name = "Sokoban", base = 1, direction = "up" },
         { name = "The Big Room", base = 1 },
         { name = "The Quest", base = 1, branchtype = "portal" },
         { name = "Fort Ludios", base = 1, branchtype = "portal" },
         { name = "Medusa's Island", base = 1 },
         { name = "Asmodeus' Lair", base = 1 },
         { name = "Juiblex's Swamp", base = 1 },
         { name = "Baalzebub's Lair", base = 1 },
         { name = "Orcus Town", base = 1 },
         { name = "The Wizard's Tower", base = 1 },
         { name = "The Black Tower", base = 1 },
         { name = "The Hollow Tower", base = 1 },
         { name = "Vlad's Tower", base = 1, direction = "up" },
         { name = "The Gates of Moloch", base = 1 },
         -- the extra special levels of Slash'EM, Hack'EM and EvilHack
         { name = "Goblin Town", base = 1, branchtype = "portal" },
         { name = "The Mall", base = 1 },
         { name = "The Rat King's Lair", base = 1 },
         { name = "The Kobold King's Lair", base = 1 },
         { name = "Grund's Stronghold", base = 1 },
         { name = "Aphrodite's Garden", base = 1 },
         { name = "The Nightmare's Lair", base = 1, branchtype = "portal" },
         { name = "The Beholder's Lair", base = 1, branchtype = "portal" },
         { name = "Vecna's Lair", base = 1, branchtype = "portal" },
         { name = "The Storerooms", base = 1 },
         { name = "The Wyrm Caves", base = 1 },
         { name = "The Lost Tomb", base = 1 },
         { name = "One-eyed Sam's Market", base = 1, branchtype = "portal" },
         { name = "The Spider Caves", base = 1 },
         { name = "The Adventurers' Guild", base = 1 },
         { name = "The Sunless Sea", base = 1 },
         { name = "The Temple of Moloch", base = 1 },
         { name = "The Giant Caverns", base = 1 },
         { name = "Frankenstein's Lab", base = 1 },
         { name = "Yeenoghu's Lair", base = 1 },
         { name = "Demogorgon's Lair", base = 1 },
         { name = "Geryon's Lair", base = 1 },
         { name = "Dispater's Lair", base = 1 },
      },
   },
   {
      name = "The Gnomish Mines",
      bonetag = "M",
      base = 8,
      range = 2,
      alignment = "lawful",
      flags = { "mazelike" },
      lvlfill = "minefill",
      levels = {
         {
            name = "minetn",
            bonetag = "T",
            base = 3,
            range = 2,
            nlevels = 7,
            flags = "town"
         },
         {
            -- Slash'EM and Hack'EM put the Gnome King's level below
            -- Mines' End
            name = "minend",
            base = -2,
            nlevels = 3
         },
         {
            name = "mineking",
            bonetag = "M",
            base = -1,
            nlevels = 2
         },
      }
   },
   {
      name = "The Oracle",
      bonetag = "O",
      base = 1,
      alignment = "neutral",
      levels = {
         {
            name = "oracle",
            bonetag = "O",
            base = 1,
            alignment = "neutral"
         },
      }
   },
   {
      name = "Sokoban",
      base = 4,
      alignment = "neutral",
      flags = { "mazelike" },
      entry = -1,
      levels = {
         { name = "soko1", base = 1, nlevels = 2 },
         { name = "soko2", base = 2, nlevels = 2 },
         { name = "soko3", base = 3, nlevels = 2 },
         { name = "soko4", base = 4, nlevels = 2 },
      }
   },
   {
      name = "The Big Room",
      bonetag = "B",
      base = 1,
      chance = 40,
      levels = {
         { name = "bigrm", bonetag = "B", base = 1, nlevels = 13 },
      }
   },
   {
      name = "The Quest",
      bonetag = "Q",
      base = 5,
      range = 2,
      levels = {
         { name = "x-strt", base = 1, range = 1 },
         { name = "x-loca", bonetag = "L", base = 3, range = 1 },
         { name = "x-goal", base = -1 },
      }
   },
   {
      name = "Fort Ludios",
      base = 2, -- the fort, and Hack'EM's dungeon beneath it
      bonetag = "K",
      flags = { "mazelike" },
      alignment = "unaligned",
      levels = {
         { name = "knox", bonetag = "K", base = 1 },
         -- Hack'EM: the dungeon beneath the fort
         { name = "ucastle", bonetag = "U", base = 2 }
      }
   },
   {
      name = "Medusa's Island",
      base = 2,
      alignment = "chaotic",
      branches = {
         {
            name = "Gehennom",
            chainlevel = "castle",
            base = 0,
            branchtype = "no_down"
         },
      },
      levels = {
         { name = "medusa", base = 1, nlevels = 4, alignment = "chaotic" },
         { name = "castle", base = 2 }
      }
   },
   {
      name = "Gehennom",
      bonetag = "G",
      base = 1,
      flags = { "mazelike", "hellish" },
      lvlfill = "hellfill",
      alignment = "noalign",
      levels = {
         { name = "valley", bonetag = "V", base = 1 },
      }
   },
   {
      name = "Asmodeus' Lair",
      bonetag = "A",
      base = 1,
      flags = { "mazelike", "hellish" },
      lvlfill = "hellfill",
      alignment = "noalign",
      levels = {
         { name = "asmodeus", bonetag = "A", base = 1 },
      }
   },
   {
      name = "Juiblex's Swamp",
      bonetag = "J",
      base = 1,
      flags = { "mazelike", "hellish" },
      lvlfill = "hellfill",
      alignment = "noalign",
      levels = {
         { name = "juiblex", bonetag = "J", base = 1 },
      }
   },
   {
      name = "Baalzebub's Lair",
      bonetag = "Z", -- not "B": its bones would clash with the Big Room's
      base = 1,
      flags = { "mazelike", "hellish" },
      lvlfill = "hellfill",
      alignment = "noalign",
      levels = {
         { name = "baalz", bonetag = "B", base = 1 },
      }
   },
   {
      name = "Orcus Town",
      bonetag = "U", -- not "O": its bones would clash with the Oracle's
      base = 1,
      flags = { "mazelike", "hellish" },
      lvlfill = "hellfill",
      alignment = "noalign",
      levels = {
         { name = "orcus", bonetag = "O", base = 1 },
      }
   },
   {
      name = "The Wizard's Tower",
      base = 3,
      flags = { "mazelike", "hellish" },
      lvlfill = "hellfill",
      alignment = "noalign",
      levels = {
         { name = "wizard1", base = 1 },
         { name = "wizard2", bonetag = "X", base = 2 },
         { name = "wizard3", bonetag = "Y", base = 3 },
      }
   },
   {
      name = "The Black Tower",
      bonetag = "F",
      base = 1,
      flags = { "mazelike", "hellish" },
      lvlfill = "hellfill",
      alignment = "noalign",
      levels = {
         { name = "fakewiz1", bonetag = "F", base = 1 },
      }
   },
   {
      name = "The Hollow Tower",
      bonetag = "G",
      base = 1,
      flags = { "mazelike", "hellish" },
      lvlfill = "hellfill",
      alignment = "noalign",
      levels = {
         { name = "fakewiz2", bonetag = "G", base = 1 },
      }
   },
   {
      name = "Vlad's Tower",
      base = 3,
      bonetag = "T",
      protofile = "tower",
      alignment = "chaotic",
      flags = { "mazelike" },
      entry = -1,
      levels = {
         { name = "tower1", base = 1 },
         { name = "tower2", base = 2 },
         { name = "tower3", base = 3 },
      }
   },
   {
      -- the vibrating square is on the first (filler) level; performing
      -- the invocation there opens the way down into Moloch's Sanctum
      name = "The Gates of Moloch",
      base = 2,
      flags = { "mazelike", "hellish" },
      lvlfill = "hellfill",
      alignment = "noalign",
      levels = {
         { name = "sanctum", base = -1 },
      }
   },
   --
   -- The extra special levels of Slash'EM, Hack'EM and EvilHack.  Each is
   -- a branch of the open world reached through a ring of portals (see
   -- ow_init() in overworld.c, which also sets their depths).  Dungeon
   -- bones tags must be unique: bones file names are built from the
   -- dungeon's tag and the level's tag.
   --
   {
      -- EvilHack: the goblins' caverns under the Misty Mountains
      name = "Goblin Town",
      bonetag = "1",
      base = 2,
      flags = { "mazelike" },
      alignment = "chaotic",
      levels = {
         { name = "gobtown1", bonetag = "1", base = 1, nlevels = 2 },
         { name = "gobtown2", bonetag = "2", base = 2 },
      }
   },
   {
      -- Slash'EM: a town of shops (only in some games)
      name = "The Mall",
      bonetag = "2",
      base = 1,
      chance = 75,
      alignment = "lawful",
      levels = {
         { name = "mall", bonetag = "T", base = 1, nlevels = 2,
           flags = "town" },
      }
   },
   {
      -- Slash'EM: the Rat King's level (only in some games)
      name = "The Rat King's Lair",
      bonetag = "3",
      base = 1,
      chance = 50,
      levels = {
         { name = "rats", bonetag = "R", base = 1, nlevels = 2 },
      }
   },
   {
      -- Slash'EM: Kroo the Kobold King's level (only in some games)
      name = "The Kobold King's Lair",
      bonetag = "4",
      base = 1,
      chance = 50,
      levels = {
         { name = "kobold", bonetag = "K", base = 1, nlevels = 2 },
      }
   },
   {
      -- Slash'EM: Grund the Orc King's fortress
      name = "Grund's Stronghold",
      bonetag = "5",
      base = 1,
      flags = { "mazelike" },
      alignment = "chaotic",
      levels = {
         { name = "grund", bonetag = "Z", base = 1, nlevels = 3 },
      }
   },
   {
      -- Slash'EM: the nymph level, with Aphrodite (only in some games)
      name = "Aphrodite's Garden",
      bonetag = "6",
      base = 1,
      chance = 45,
      levels = {
         { name = "nymph", bonetag = "N", base = 1 },
      }
   },
   {
      -- Slash'EM: the lawful key quest
      name = "The Nightmare's Lair",
      base = 1,
      flags = { "mazelike" },
      alignment = "lawful",
      levels = {
         { name = "nightmar", base = 1 },
      }
   },
   {
      -- Slash'EM: the neutral key quest
      name = "The Beholder's Lair",
      base = 1,
      flags = { "mazelike" },
      alignment = "neutral",
      levels = {
         { name = "beholder", base = 1 },
      }
   },
   {
      -- Slash'EM: the chaotic key quest
      name = "Vecna's Lair",
      base = 1,
      flags = { "mazelike" },
      alignment = "chaotic",
      levels = {
         { name = "lich", base = 1 },
      }
   },
   {
      -- Slash'EM: treasure storerooms (only in some games)
      name = "The Storerooms",
      bonetag = "7",
      base = 1,
      chance = 66,
      levels = {
         { name = "stor", bonetag = "S", base = 1, nlevels = 3 },
      }
   },
   {
      -- Slash'EM / Hack'EM: the dragons' caves
      name = "The Wyrm Caves",
      bonetag = "8",
      base = 2,
      flags = { "mazelike" },
      alignment = "chaotic",
      levels = {
         { name = "cavebegn", bonetag = "C", base = 1 },
         { name = "caveend", bonetag = "D", base = 2 },
      }
   },
   {
      name = "The Lost Tomb",
      bonetag = "9",
      base = 1,
      flags = { "mazelike" },
      alignment = "chaotic",
      levels = {
         { name = "tomb", bonetag = "L", base = 1 },
      }
   },
   {
      -- Slash'EM: One-eyed Sam's black market
      name = "One-eyed Sam's Market",
      bonetag = "0",
      base = 1,
      flags = { "mazelike" },
      alignment = "chaotic",
      levels = {
         { name = "blkmar", bonetag = "D", base = 1 },
      }
   },
   {
      name = "The Spider Caves",
      bonetag = "S",
      base = 1,
      flags = { "mazelike" },
      alignment = "chaotic",
      levels = {
         { name = "spiders", bonetag = "S", base = 1 },
      }
   },
   {
      -- Slash'EM: the Guild of Disgruntled Adventurers (only in some games)
      name = "The Adventurers' Guild",
      bonetag = "I",
      base = 1,
      chance = 50,
      levels = {
         { name = "guild", bonetag = "G", base = 1 },
      }
   },
   {
      name = "The Sunless Sea",
      base = 1,
      flags = { "mazelike" },
      alignment = "chaotic",
      levels = {
         { name = "sea", base = 1 },
      }
   },
   {
      name = "The Temple of Moloch",
      base = 1,
      flags = { "mazelike" },
      alignment = "chaotic",
      levels = {
         { name = "mtemple", base = 1 },
      }
   },
   {
      name = "The Giant Caverns",
      bonetag = "H",
      base = 1,
      flags = { "mazelike" },
      alignment = "chaotic",
      levels = {
         { name = "giants", bonetag = "H", base = 1 },
      }
   },
   {
      -- Slash'EM: Doctor Frankenstein's laboratory; its portals are in
      -- Gehennom but, as in Slash'EM, the lab itself isn't part of it
      name = "Frankenstein's Lab",
      base = 1,
      flags = { "mazelike" },
      alignment = "chaotic",
      levels = {
         { name = "frnknstn", base = 1 },
      }
   },
   {
      -- Slash'EM: lairs for demon lords that vanilla gives none
      name = "Yeenoghu's Lair",
      bonetag = "E",
      base = 1,
      flags = { "mazelike", "hellish" },
      lvlfill = "hellfill",
      alignment = "noalign",
      levels = {
         { name = "yeenoghu", bonetag = "E", base = 1 },
      }
   },
   {
      name = "Demogorgon's Lair",
      bonetag = "C",
      base = 1,
      flags = { "mazelike", "hellish" },
      lvlfill = "hellfill",
      alignment = "noalign",
      levels = {
         { name = "demogorg", bonetag = "D", base = 1 },
      }
   },
   {
      name = "Geryon's Lair",
      bonetag = "R",
      base = 1,
      flags = { "mazelike", "hellish" },
      lvlfill = "hellfill",
      alignment = "noalign",
      levels = {
         { name = "geryon", bonetag = "R", base = 1 },
      }
   },
   {
      name = "Dispater's Lair",
      bonetag = "P",
      base = 1,
      flags = { "mazelike", "hellish" },
      lvlfill = "hellfill",
      alignment = "noalign",
      levels = {
         { name = "dispater", bonetag = "S", base = 1 },
      }
   },
   {
      name = "The Tutorial",
      base = 2,
      flags = { "mazelike", "unconnected" },
      levels = {
         { name = "tut-1", base = 1, },
         { name = "tut-2", base = 2, },
      }
   },
}
