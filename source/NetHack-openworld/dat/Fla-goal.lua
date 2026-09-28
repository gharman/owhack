-- NetHack Flame Mage Fla-goal.lua
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991-2 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
--
--	The "goal" level for the quest.
--
--	Here you meet the Water Mage, your nemesis monster.  You
--	have to defeat him in combat to gain the artifact you have
--	been assigned to retrieve.
--
des.level_init({ style = "solidfill", fg = "P" });

des.level_flags("mazelevel");

des.level_init({ style="mines", fg=".", bg="P", smoothed=true, joined=true, lit=1, walled=false })

des.map([[
.....PPPPPPPPPPPPPPPPPPPPPPPPP.....
...PPPPPPPPPPPPPP.PPPPPPPPPPPPPP...
..PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP..
.PPPPPPPPPPP|---------|PPPPPPPPPPP.
.PPPPPPPPP|--.........--|PPPPPPPPP.
PPPPPPPPP|-...PPPPPPP...-|PPPPPPPPP
PPPPPPPPP|...PP.....PP...|PPPPPPPPP
PPPPPPPP|-..PP.......PP..-|PPPPPPPP
PPPPPPPP|...PP.......PP...|PPPPPPPP
PPPPPPPP|-..PP.......PP..-|PPPPPPPP
PPPPPPPPP|...PP.....PP...|PPPPPPPPP
PPPPPPPPP|-...PPPPPPP...-|PPPPPPPPP
.PPPPPPPPP|--.........--|PPPPPPPPP.
.PPPPPPPPPPP|---------|PPPPPPPPPPP.
..PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP..
...PPPPPPPPPPPPPP.PPPPPPPPPPPPPP...
.....PPPPPPPPPPPPPPPPPPPPPPPPP.....
]]);
-- Dungeon Description
des.region(selection.area(00,00,34,16), "lit")
-- Stairs
-- Note:  The up stairs are *intentionally* off of the map.
des.stair("up", 45,10)
-- Non diggable walls
des.non_diggable(selection.area(00,00,34,16))
-- Drawbridges
des.drawbridge({ dir="south", state="closed", x=17, y=02 })
des.drawbridge({ dir="north", state="closed", x=17, y=14 })
-- Quest Artifact
des.object({ id = "magic candle", x=17, y=08, buc="blessed", spe=0, name="The Candle of Eternal Flame" })
-- Objects
for i = 1, 7 do
   des.object()
end
-- Random traps
-- (Hack'EM uses its "cold" trap here; 5.0 has none, so use Slash'EM's rust traps)
for i = 1, 10 do
   des.trap("rust")
end
des.trap()
des.trap()
-- KMH, balance patch 2 -- all quests now have an altar
des.altar({ x=17, y=08, align="noalign", type="altar" })
-- Random monsters.
des.monster("Water Mage", 17, 08)
des.monster({ id = "white dragon", x=17, y=09, asleep = 1, peaceful = 0 })
for i = 1, 6 do
   des.monster({ id = "ice elemental", peaceful = 0 })
end
for i = 1, 3 do
   des.monster({ id = "ice vortex", peaceful = 0 })
end
des.monster({ id = "rust monster", peaceful = 0 })
des.monster({ id = "ice devil", peaceful = 0 })
des.monster({ id = "ice devil", peaceful = 0 })
des.monster({ id = "ice devil", peaceful = 0 })
des.monster({ id = "ice devil", peaceful = 0 })
des.monster({ id = "ice troll", peaceful = 0 })
des.monster({ id = "ice troll", peaceful = 0 })
des.monster({ id = "ice nymph", peaceful = 0 })
des.monster({ id = "ice nymph", peaceful = 0 })
des.monster({ id = "electric eel", peaceful = 0 })
des.monster({ id = "electric eel", peaceful = 0 })
des.monster({ id = "kraken", peaceful = 0 })
des.monster({ id = "kraken", peaceful = 0 })
des.monster({ id = "giant eel", peaceful = 0 })
des.monster({ id = "giant eel", peaceful = 0 })
des.monster({ id = "giant eel", peaceful = 0 })
des.monster({ id = "giant eel", peaceful = 0 })
