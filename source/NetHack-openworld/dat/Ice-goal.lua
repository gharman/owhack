-- NetHack Ice Mage Ice-goal.lua
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991-2 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
--
--	The "goal" level for the quest.
--
--	Here you meet Ragnaros, your nemesis monster.  You have
--	to defeat him in combat to gain the artifact you have
--	been assigned to retrieve.
--
des.level_init({ style = "solidfill", fg = "P" });

des.level_flags("mazelevel");

des.level_init({ style="mines", fg=".", bg=" ", smoothed=true, joined=true, lit=1, walled=false })

des.map([[
...................................
.....            .           ......
...        .............        ...
..       ...|---------|...       ..
.       ..|--.........--|..       .
        .|-...       ...-|.        
       ..|...  .....  ...|..       
       .|-..  .......  ..-|.       
       .|...  .......  ...|.       
       .|-..  .......  ..-|.       
       ..|...  .....  ...|..       
        .|-...       ...-|.        
.       ..|--.........--|..       .
..       ...|---------|...       ..
...        .............        ...
.....            .            .....
...................................
]]);
-- Dungeon Description
des.region(selection.area(00,00,34,16), "lit")
-- Stairs
-- Note:  The up stairs are *intentionally* off of the map.
des.stair("up", 45,10)
-- Drawbridges
des.drawbridge({ dir="south", state="closed", x=17, y=02 })
des.drawbridge({ dir="north", state="closed", x=17, y=14 })
-- Objects
des.object({ id = "magic whistle", x=17, y=08, buc="blessed", spe=0, name="The Storm Whistle" })
for i = 1, 7 do
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
-- KMH, balance patch 2 -- all quests now have an altar
des.altar({ x=17, y=08, align="noalign", type="altar" })
-- Random monsters.
des.monster("Ragnaros", 17, 08)
des.monster({ id = "red dragon", x=17, y=09, asleep = 1, peaceful = 0 })
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
for i = 1, 4 do
   des.monster({ id = "salamander", peaceful = 0 })
end
des.monster({ id = "red naga", peaceful = 0 })
des.monster({ id = "red naga", peaceful = 0 })
des.monster({ id = "hell hound", peaceful = 0 })
des.monster({ id = "hell hound", peaceful = 0 })
des.monster({ id = "fire vampire", peaceful = 0 })
des.monster({ id = "fire vampire", peaceful = 0 })
des.monster({ id = "lava blob", peaceful = 0 })
des.monster({ id = "lava blob", peaceful = 0 })
des.monster("&")
des.monster("&")
