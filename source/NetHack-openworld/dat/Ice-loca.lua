-- NetHack Ice Mage Ice-loca.lua
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991-2 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
--
--	The "locate" level for the quest.
--
--	Here you have to find the stairs to go
--	further towards your assigned quest.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "hardfloor")

des.level_init({ style="mines", fg=".", bg=" ", smoothed=true, joined=true, lit=1, walled=false })

des.map([[
    ....                      ....    .. 
   ...                          ..     . 
  .     ......................    .      
..   ... ........... ............  .   . 
.  ...... ......... . ......... ..  .... 
  ........ ....... ... ....... ....   .. 
........... ..... ..... ..... ......   . 
  .......... ... ....... ... ........    
.  .......... . ......... . .........  . 
..   ......... ........... ........   .. 
  .   ..........................     .   
   ..                             ...    
   ....                         ....   . 
]]);
-- Dungeon Description
des.region(selection.area(00,00,39,12), "lit")
-- Stairs
des.stair("up", 48,14)
des.stair("down", 20,06)
-- Objects
for i = 1, 9 do
   des.object()
end
-- Random traps
for i = 1, 4 do
   des.trap("fire")
end
des.trap("falling rock")
des.trap("falling rock")
des.trap()
des.trap()
-- Random monsters.
for i = 1, 4 do
   des.monster({ id = "fire elemental", peaceful = 0 })
end
for i = 1, 2 do
   des.monster({ id = "magma elemental", peaceful = 0 })
end
for i = 1, 3 do
   des.monster({ id = "steam vortex", peaceful = 0 })
end
for i = 1, 3 do
   des.monster({ id = "fire vortex", peaceful = 0 })
end
des.monster({ id = "salamander", peaceful = 0 })
des.monster({ id = "salamander", peaceful = 0 })
des.monster({ id = "red naga", peaceful = 0 })
des.monster({ id = "red naga", peaceful = 0 })
des.monster({ id = "hell hound", peaceful = 0 })
des.monster({ id = "hell hound", peaceful = 0 })
des.monster({ id = "demon orc", peaceful = 0 })
des.monster({ id = "demon orc", peaceful = 0 })
des.monster({ id = "fire giant", peaceful = 0 })
des.monster({ id = "fire giant", peaceful = 0 })
