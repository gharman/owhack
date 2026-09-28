-- NetHack Cartographer Car-strt.lua
--	Copyright (c) 2026 by the NetHack: Open World contributors
-- NetHack may be freely redistributed.  See license for details.
--
--	The "start" level for the Cartographer quest.
--
--	The Hall of Charts, the library and observatory of the Society of
--	Cartographers, stands on the shore of the western sea.  Here you
--	meet your leader, Anaximander, and receive your quest assignment.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noteleport", "hardfloor")

des.map([[
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
]]);
-- Dungeon Description
des.region(selection.area(00,00,75,19), "lit")
-- the stacks of the four libraries are kept in the dark
des.region(selection.area(09,03,14,07), "unlit")
des.region(selection.area(09,11,14,15), "unlit")
des.region(selection.area(47,03,52,07), "unlit")
des.region(selection.area(47,11,52,15), "unlit")
-- Portal arrival point: the garden west of the Hall
des.levregion({ region = {01,09,01,09}, type="branch" })
-- Stairs: the landing stage at the end of the pier
des.stair("down", 69,09)
-- Doors
des.door("open",08,09)
des.door("closed",53,09)
des.door("closed",21,09)
des.door("closed",40,09)
des.door("closed",18,08)
des.door("closed",18,10)
des.door("closed",43,08)
des.door("closed",43,10)
des.door("locked",15,05)
des.door("closed",15,13)
des.door("closed",46,05)
des.door("locked",46,13)
-- the Society's motto over the door, and a warning at the pier
des.engraving({ coord = {07,09}, type = "engrave",
                text = "Terra cognita: that which is mapped is ours" })
des.engraving({ coord = {68,09}, type = "burn", text = "Hic sunt dracones" })
-- Anaximander, Master of the Society of Cartographers, in the dome of
-- the observatory
des.monster({ id = "Anaximander", coord = {30, 09}, inventory = function()
   des.object({ id = "quarterstaff", spe = 4 });
   des.object({ id = "cloak of magic resistance", spe = 1 });
   des.object("sextant");
end })
-- the Society's strongbox
des.object("chest", 31, 09)
-- surveyors keep watch in the observatory
des.monster("surveyor", 27, 07)
des.monster("surveyor", 34, 07)
des.monster("surveyor", 27, 11)
des.monster("surveyor", 34, 11)
des.monster("surveyor", 24, 09)
des.monster("surveyor", 37, 09)
des.monster("surveyor", 30, 05)
des.monster("surveyor", 30, 13)
-- the Society's collection: charts, globes and the busts of the great
des.object({ id = "statue", coord = {19, 05}, montype = "cartographer" })
des.object({ id = "statue", coord = {42, 05}, montype = "cartographer" })
des.object({ id = "statue", coord = {19, 13}, montype = "cartographer" })
des.object({ id = "statue", coord = {42, 13}, montype = "cartographer" })
des.object("?", 11, 04)
des.object("?", 13, 06)
des.object("scroll of blank paper", 09, 05)
des.object("scroll of magic mapping", 11, 13)
des.object("?", 13, 12)
des.object("+", 09, 14)
des.object("?", 50, 04)
des.object("scroll of blank paper", 52, 06)
des.object("+", 48, 05)
des.object("?", 50, 13)
des.object("scroll of magic mapping", 52, 12)
des.object("?", 48, 15)
-- fountains in the garden
des.feature("fountain", 04, 04)
des.feature("fountain", 04, 14)
-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))
-- Random traps
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
-- the Labyrinth's creatures have come as far as the Hall itself:
-- umber hulks, burrowing up out of the lost roads, and beasts gone astray
des.monster({ id = "umber hulk", coord = {05, 01}, peaceful = 0 })
des.monster({ id = "umber hulk", coord = {05, 18}, peaceful = 0 })
des.monster({ id = "umber hulk", coord = {56, 17}, peaceful = 0 })
des.monster({ class = "q", coord = {02, 06}, peaceful = 0 })
des.monster({ class = "q", coord = {02, 12}, peaceful = 0 })
des.monster({ class = "q", coord = {30, 00}, peaceful = 0 })
des.monster({ class = "q", coord = {30, 18}, peaceful = 0 })
des.monster({ class = "q", coord = {56, 02}, peaceful = 0 })
des.monster({ class = "q", coord = {57, 12}, peaceful = 0 })
des.monster({ class = "q", peaceful = 0 })
des.monster({ class = "q", peaceful = 0 })
-- and things in the sea
des.monster("giant eel", 66, 03)
des.monster("giant eel", 65, 15)
des.monster("shark", 73, 11)
