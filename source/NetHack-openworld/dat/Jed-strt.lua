-- NetHack Jedi Jed-strt.lua
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991,92 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
--
--	The "start" level for the quest.
--
--	Here you meet your (besieged) class leader, the Jedi Master
--	and receive your quest assignment.
--
des.level_init({ style = "solidfill", fg = "A" });

des.level_flags("mazelevel", "noteleport", "hardfloor")

des.level_init({ style="mines", fg=".", bg="A", smoothed=false, joined=false, lit=0, walled=false })

--          1         2         3         4         5         6         7
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAA--------AAAAAAAAAAAAAAAAAAAAAAAAAAA--------AAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAA|......|AAAAAAAAAAAAAAAAAAAAAAAAAAA|......|AAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAA|......|AA-----------------------AA|......|AAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAA|......|AA|.....................|AA|......|AAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAA|......|AA|.-------------------.|AA|......|AAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAA---+----AA|.|.................|.|AA----+---AAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAA|.|AAAAA|.|.................|.|AAAAA|.|AAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAA|.------|.|..}...........}..|.|------.|AAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAS.......+.+.................+.+.......SAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAA|.------|.|..}...........}..|.|------.|AAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAA|.|AAAAA|.|.................|.|AAAAA|.|AAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAA---+----AA|.|.................|.|AA----+---AAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAA|......|AA|.-------------------.|AA|......|AAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAA|......|AA|.....................|AA|......|AAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAA|......|AA-----------------------AA|......|AAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAA|......|AAAAAAAAAAAAAAAAAAAAAAAAAAA|......|AAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAA--------AAAAAAAAAAAAAAAAAAAAAAAAAAA--------AAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
]]);

local places = { {57,3}, {17,14}, {57,14} }

-- according to starwars.com the Jedi temple is a tall building high up into
-- the sky. So it seems right to have it being surrounded by Air

des.teleport_region({ region = {26,05,46,15} })

-- Dungeon Description
des.region(selection.area(00,00,75,20), "unlit")
des.region(selection.area(16,02,23,07), "lit")
des.region(selection.area(51,02,63,07), "lit")
des.region(selection.area(16,13,23,18), "lit")
des.region(selection.area(51,13,63,18), "lit")
des.region(selection.area(29,07,45,14), "lit")

-- Portal arrival point
des.levregion({ region = {17,03,17,03}, type="branch" })

-- Stairs
-- (Hack'EM: STAIR: $places[0]; the list is never shuffled, so this is
-- always the first entry)
des.stair("down", places[1])

-- Doors
des.door("closed",19,07)
des.door("closed",19,13)
des.door("locked",18,10)
des.door("locked",26,10)
des.door("locked",28,10)
des.door("locked",46,10)
des.door("locked",48,10)
des.door("locked",56,10)
des.door("closed",55,13)
des.door("closed",55,07)

-- The Jedi Master
des.monster("Jedi Master", 37, 10)

-- The treasure of the Jedi Master
des.object("chest", 37, 07)

-- the remaining Jedi
des.monster({ id = "padawan", x=38, y=11, peaceful = 1 })
des.monster({ id = "padawan", x=38, y=09, peaceful = 1 })
des.monster({ id = "padawan", x=36, y=11, peaceful = 1 })
des.monster({ id = "padawan", x=36, y=09, peaceful = 1 })
des.monster({ id = "jedi trainer", x=18, y=04, peaceful = 1 })
des.monster({ id = "jedi trainer", x=19, y=04, peaceful = 1 })
des.monster({ id = "jedi", x=18, y=15, peaceful = 1 })
des.monster({ id = "jedi", x=19, y=15, peaceful = 1 })
des.monster({ id = "jedi", x=56, y=04, peaceful = 1 })
des.monster({ id = "jedi", x=57, y=04, peaceful = 1 })
des.monster({ id = "padawan", x=56, y=15, peaceful = 1 })
des.monster({ id = "padawan", x=57, y=15, peaceful = 1 })
des.monster({ id = "padawan", x=33, y=10, peaceful = 1 })

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,20))

-- Monsters on siege duty.
des.monster({ id = "stormtrooper", x=27, y=05, peaceful = 0 })
des.monster({ id = "stormtrooper", x=47, y=05, peaceful = 0 })
des.monster({ id = "stormtrooper", x=27, y=15, peaceful = 0 })
des.monster({ id = "stormtrooper", x=47, y=15, peaceful = 0 })
des.monster({ id = "stormtrooper", x=19, y=10, peaceful = 0 })
des.monster({ id = "stormtrooper", x=20, y=10, peaceful = 0 })
des.monster({ id = "stormtrooper", x=50, y=10, peaceful = 0 })
des.monster({ id = "stormtrooper", x=51, y=10, peaceful = 0 })
