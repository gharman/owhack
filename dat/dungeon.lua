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
            name = "minend",
            base = -1,
            nlevels = 3
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
      base = 1,
      bonetag = "K",
      flags = { "mazelike" },
      alignment = "unaligned",
      levels = {
         { name = "knox", bonetag = "K", base = -1 }
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
      bonetag = "B",
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
      bonetag = "O",
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
