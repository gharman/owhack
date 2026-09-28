-- NetHack Necromancer Nec-strt.lua
--	Copyright (c) 1992 by David Cohrs
-- NetHack may be freely redistributed.  See license for details.
--
--
--	The "start" level for the quest.
--
--	[Tom] -- the necromancer quest
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noteleport", "hardfloor")

des.map([[
.LLLLLLLL...............................C...................................
...LLLLLLLL..........................C.C.CCC................................
....LLLLLLLLLL.........................C..CCCC..............................
......LLLLLLLLLL......LLLLLLLLLLLLLL........CC...............CCCCC..........
.....LLLLLLLLLLLLLL...L|----------|L.......CCCC............CCC...CC.........
.........LLLLLLLLLLLLLL|..........|LLLL...CCCCCC..........CCC.....CCC.......
..............LLLLLL|--|..........|--|L...C...............CC........CC......
..........LLLLLL...L|................|...CCC...............CC......CC.......
............LLL....L|....\...........S.....CCC............CCCC....C.........
.............LLL...L|................|..................C.CCCCC.CCC.........
..............LLL..L|--|..........|--|L...CC...........CCCCCCC..............
...................LLLL|..........|LLLL...CCCCC.........C...CCC.............
......................L|----------|L.........CCCCC......C...C...............
......................LLLLLLLLLLLLLL..........CC............................
.........................................CCC..................C.............
................................C....C.....CCC..............................
...........................CCCC........CCCCC................................
..............................C....CCCC.....................................
......................CCC...................................................
............................................................................
]]);
-- Dungeon Description
des.region(selection.area(00,00,75,19), "unlit")
-- Stairs
des.stair("down", 16,07)
-- Portal arrival point
des.levregion({ region = {63,06,63,06}, type="branch" })
-- Dark Lord
des.monster("Dark Lord", 25, 08)
-- The treasure of the Dark Lord
des.object("chest", 34, 08)
-- apprentice guards for the audience chamber
des.monster("embalmer", 24, 07)
des.monster("embalmer", 25, 07)
des.monster("embalmer", 26, 07)
des.monster("embalmer", 24, 09)
des.monster("embalmer", 25, 09)
des.monster("embalmer", 26, 09)
des.monster("embalmer", 24, 11)
des.monster("embalmer", 25, 11)
des.monster("embalmer", 26, 11)
-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))
-- Monsters on siege duty.
des.monster({ id = "mongbat", x=60, y=09, peaceful = 0 })
des.monster({ id = "mongbat", x=60, y=10, peaceful = 0 })
des.monster({ id = "mongbat", x=60, y=11, peaceful = 0 })
des.monster({ id = "mongbat", x=60, y=12, peaceful = 0 })
des.monster({ id = "nupperibo", x=60, y=13, peaceful = 0 })
des.monster({ id = "mongbat", x=61, y=10, peaceful = 0 })
des.monster({ id = "mongbat", x=61, y=11, peaceful = 0 })
des.monster({ id = "mongbat", x=61, y=12, peaceful = 0 })
des.monster({ class = "B", x=35, y=03, peaceful = 0 })
des.monster({ class = "i", x=35, y=17, peaceful = 0 })
des.monster({ class = "B", x=36, y=17, peaceful = 0 })
des.monster({ class = "B", x=34, y=16, peaceful = 0 })
des.monster({ class = "i", x=34, y=17, peaceful = 0 })
des.monster({ class = "B", x=10, y=19, peaceful = 0 })
