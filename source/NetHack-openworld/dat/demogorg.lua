-- NetHack: Open World  demogorg.lua
--	SCCS Id: @(#)gehennom.des	3.4	1996/11/09
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1992 by M. Stephenson and Izchak Miller
-- Converted from Slash'EM gehennom.des ("demogorg") for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.
--
-- [Tom]
-- The Demogorgon level
--
des.level_init({ style = "mazegrid", bg = "-" });

des.level_flags("mazelevel", "noteleport")

des.map({ halign = "right", valign = "center", map = [[
-------------------------------------------------
| ------------|------------------                
| |}}}}}}}}}}}|}...}......}}}}}}|--------------  
| |}}}}}}}}}}}|....}}...}...}}}}S...|.........|  
| |-----}}-----...}...}.......}}|--S-----S-...|  
---....}}}}...|.....}}....}..}}}|...|.....|--S-  
.......}}}}...|-S----------------...|.....|...|  
---..}}}}}}...|}..|      |...S..S...|.....|----  
| |-}}}--------...|      |...-------|--S-----    
| |}}}}|......S...|      |..........S.......|    
| |}}}}S......|..}|      |----------|.......|    
| ------------|----                 ---------    
-------------------------------------------------
]] });
-- The source also had an up staircase levregion identical to the branch
-- one; only the branch is kept (it is the way back to the open world).
des.levregion({ region = {01,00,15,20}, region_islev = 1, exclude = {15,1,70,16}, exclude_islev = 1, type = "branch" })
des.teleport_region({ region = {01,00,15,20}, region_islev = 1, exclude = {15,1,70,16}, exclude_islev = 1 })
des.non_diggable(selection.area(00,00,46,12))
des.mazewalk(00,06,"west")
des.stair("down", 44,06)
-- The fellow in residence
des.monster("Demogorgon", 06,06)
-- Some random weapons and armor.
des.object("*")
des.object("!")
des.object("!")
des.object("!")
des.object("!")
des.object("!")
des.object("!")
des.object("?")
des.object("?")
des.object("?")
-- Random monsters.
for i = 1, 9 do
   des.monster("P")
end
for i = 1, 7 do
   des.monster("j")
end
for i = 1, 5 do
   des.monster("F")
end
for i = 1, 10 do
   des.monster("hezrou")
end
for i = 1, 6 do
   des.monster("vrock")
end
