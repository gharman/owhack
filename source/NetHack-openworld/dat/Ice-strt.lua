-- NetHack Ice Mage Ice-strt.lua
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991-2 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
--
--	The "start" level for the quest.
--
--	Here you meet your (besieged) class leader, the High Ice Mage,
--	and receive your quest assignment.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noteleport", "hardfloor")

des.map([[
IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
IIIIIIIIIIIIIIIIIII                 IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
IIIIIIIIIIIIIIIIII  ...............  IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
IIIIIIIIIIIIIIIII  ..             ..  IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
IIIIIIIIIIIIIIII  ..   IIII    .....   IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
IIIII            ..  IIIII  .....         IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
IIII  ............  IIIII  ..     IIIIII    IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
III  ..            III    ..    IIIIIIIIII    IIIIIIIIIIIIIIIIIIIIIIIIIIIIII
II  ..  IIIIIIIIIIIII  ....    IIIPPPPPPIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
II ..  IIIIIIIIIIIII  ..      IIPPP....PPPII    IIIIIIIIIIIIIIIIIIIIIIIIIIII
I  ...  IIIIIIIIIIII ..   ...IIPP........PPII  IIIIIIIIIIIIIIIIIIIIIIIIIIIII
I  ....   IIIIIIIIII  .....   IIPPP....PPPII  IIIIIIIIIIIIIIIIIIIIIIIIIIIIII
II  ...  IIIIIIIIIIII          IIIPPPPPPIII  IIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
III     IIIIIIIIIIIIIIIIIIIIII  IIIIIIIII  IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
IIIIIIIIIIIIIIIIIIIIIIIIIIIIIII   IIIIII  IIIIIIIIIIIIIIIIIIIIII...IIIIIIIII
IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII        IIIIIIIIIIIIIIIIIIIIII.....IIIIIIII
IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII...IIIIIIIII
IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
]]);
-- Dungeon Description
des.region(selection.area(00,00,75,19), "lit")
-- Portal arrival point
des.levregion({ region = {65,16,65,16}, type="branch" })
-- Stairs
des.stair("down", 05,12)
-- High Ice Mage
des.monster("High Ice Mage", 36, 11)
-- The treasure of the High Ice Mage
des.object("chest", 39, 11)
-- guards for the audience chamber
des.monster("froster", 35, 10)
des.monster("froster", 35, 11)

for i = 1, 5 do
   des.monster("froster")
end
des.monster({ id = "baby white dragon", peaceful = 1 })
des.monster({ id = "white dragon", peaceful = 1 })
des.monster({ id = "white dragon", peaceful = 1 })
-- Non diggable
des.non_diggable(selection.area(00,00,75,19))
-- Random traps
for i = 1, 6 do
   des.trap("fire")
end
des.trap("falling rock")
des.trap("falling rock")
des.trap("magic")
des.trap("magic")
-- Monsters on siege duty.
for i = 1, 4 do
   des.monster({ id = "fire elemental", peaceful = 0 })
end
des.monster({ id = "magma elemental", peaceful = 0 })
for i = 1, 2 do
   des.monster({ id = "steam vortex", peaceful = 0 })
end
for i = 1, 2 do
   des.monster({ id = "fire vortex", peaceful = 0 })
end
des.monster({ id = "pyrolisk", peaceful = 0 })
des.monster({ id = "pyrolisk", peaceful = 0 })
des.monster({ id = "hell hound pup", peaceful = 0 })
des.monster({ id = "hell hound pup", peaceful = 0 })
