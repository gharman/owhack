-- NetHack Flame Mage Fla-strt.lua
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991-2 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
--
--	The "start" level for the quest.
--
--	Here you meet your (besieged) class leader, the High Flame Mage,
--	and receive your quest assignment.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noteleport", "hardfloor")

des.map([[
LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
LLL........LLLLLLLL....LLLLLLLLLLLLL......................LLLLLLLLL.LLLLLLLL
LLL.LLLLLLL.LLLLLL.L...LLLLLLLLLLLLL.LLLLLLLLLLLLLLLLLLLLL.LLLLLLL...LLLLLLL
LLL.LLLLLLLL.LLLL.LLLLLLLLLLLLLLLLLL.LLLLLLLLLLLLLLLLLLLLLL.LLLLL.L.LLLLLLLL
LLL.LLLLLLLLL.LL.LLLLLLLLLLLLLLLLLLL.LLLLLLLLLLLLLLLLLLLLLLL.LLL.LLLLLLLLLLL
LLL.LLLLLLLLLL..LLLLLLLLLLLLLLLL..........LLLLLLLLLLLLLLLLLLL.L.LLLLLLLLLLLL
LLL.LLL.LLLLLLL.LLLLLLLLLLLLLL...LLLLLLLL...LLLLLLLLLLLLLLLLLL.LLLLLLLLLLLLL
LPL.LLPPLLLLLLLLL.LLLLLLLLLL...LLL......LLL...LLLLLLLLLLLLLLLL.LLLLLLLLLLLLL
LLPP.PPPLPLLLLLLLL....LLLLL...LL..........LL...LLLLLLLLLLLLLLL.LLLLLLLLLLLLL
LLPP...PPLLLLLLLL.LLLL.......LL............LL........LLLLLLLLL.LLLLLLLLLLLLL
LPP.....PPPLLLLL.LLLLLLLLLL...LL..........LL...LLLLLL.LLLLLLLL.LLLLLLLLLLLLL
LPPP...PPPLLLLL.LLLLLLLLLLLL...LLL......LLL...LLLLLLLL.LLLLLLLL.LLLLLLLLLLLL
LLLPP.PPPLLLLL.LLLLLLLLLLLLLLL...LLLLLLLL...LLLLLLLLLLL.LLLLLLLL.LLLLLLLLLLL
L.LLPPPPLLLLLL.LLLLLLLLLLLLLLLLL..........LLLLLLLLLLLL.LLLLLLLLLL.LL..LLLLLL
LLLLLLLPLLLLLLL.LLLLLLLLLLLLLLLLLLLL.LLLLLLLLLLLLLLLL.LLLLLLLLLLLL.....LLLLL
LL.LLL.PPLLLLLLL.LLLLLLLLLLLLLLLLLLL.LLLLLLLLL.......LLLLLLLLLLLLLL....LLLLL
LLLLLL.LLLLLLLLLL.............................LLLLLLLLLLLLLLLLLLLLLL..LLLLLL
LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
]]);
-- Dungeon Description
des.region(selection.area(00,00,75,19), "lit")
des.non_diggable(selection.area(00,00,75,19))
-- Portal arrival point
des.levregion({ region = {69,17,69,17}, type="branch" })
-- Stairs
des.stair("down", 05,12)
-- High Flame Mage
des.monster("High Flame Mage", 36, 11)
-- The treasure of the High Flame Mage
des.object("chest", 40, 11)
-- guards for the audience chamber
des.monster("igniter", 34, 09)
des.monster("igniter", 34, 10)
des.monster("igniter", 34, 11)
des.monster("igniter", 34, 12)
des.monster("igniter", 34, 13)
des.monster("igniter")
des.monster("igniter")
des.monster({ id = "baby red dragon", peaceful = 1 })
des.monster({ id = "red dragon", peaceful = 1 })
des.monster({ id = "red dragon", peaceful = 1 })
-- Random traps
-- (Hack'EM uses its "cold" trap here; 5.0 has none, so use Slash'EM's rust traps)
for i = 1, 8 do
   des.trap("rust")
end
-- Monsters on siege duty.
for i = 1, 6 do
   des.monster({ id = "ice elemental", peaceful = 0 })
end
des.monster({ id = "ice troll", peaceful = 0 })
des.monster({ id = "ice troll", peaceful = 0 })
des.monster({ id = "ice troll", peaceful = 0 })
des.monster({ id = "water demon", peaceful = 0 })
des.monster({ id = "ice devil", peaceful = 0 })
des.monster({ id = "ice nymph", peaceful = 0 })
des.monster({ id = "ice nymph", peaceful = 0 })
des.monster({ id = "rust monster", peaceful = 0 })
