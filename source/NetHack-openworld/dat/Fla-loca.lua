-- NetHack Flame Mage Fla-loca.lua
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991-2 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
--
--	The "locate" level for the quest.
--
--	Here you have to find the cave of Surtur to go
--	further towards your assigned quest.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "hardfloor")

des.level_init({ style="mines", fg=".", bg="L", smoothed=true, joined=true, lit=1, walled=false })

des.map([[
PPPP....                      ....PPPPP.
PLP...                          .PPLLLPP
PPP    .......................    PPPLLP
..   ............................   PPPP
.  ...............................  ....
  .................................   ..
....................................   .
  ...................................   
.  ..................................  .
..   ..............................   PP
.PPP  ..........................     PLP
.PLLP                             ..PLLP
.PPPP..                         ....PPPP
]]);
-- Dungeon Description
des.region(selection.area(00,00,39,12), "lit")
des.non_diggable(selection.area(00,00,39,12))
-- Stairs
des.stair("up", 48,14)
des.stair("down", 20,06)
-- Objects
for i = 1, 9 do
   des.object()
end
-- Random traps
-- (Hack'EM uses its "cold" trap here; 5.0 has none, so use Slash'EM's rust traps)
for i = 1, 7 do
   des.trap("rust")
end
des.trap()
des.trap()
-- Random monsters.
for i = 1, 6 do
   des.monster({ id = "ice elemental", peaceful = 0 })
end
des.monster({ id = "ice devil", peaceful = 0 })
des.monster({ id = "water demon", peaceful = 0 })
des.monster({ id = "frost giant", peaceful = 0 })
des.monster({ id = "frost giant", peaceful = 0 })
des.monster({ id = "ice troll", peaceful = 0 })
des.monster({ id = "ice troll", peaceful = 0 })
des.monster({ id = "ice troll", peaceful = 0 })
for i = 1, 3 do
   des.monster({ id = "ice vortex", peaceful = 0 })
end
des.monster({ id = "disenchanter", peaceful = 0 })
