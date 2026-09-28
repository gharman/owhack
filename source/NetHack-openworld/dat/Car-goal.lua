-- NetHack Cartographer Car-goal.lua
--	Copyright (c) 2026 by the NetHack: Open World contributors
-- NetHack may be freely redistributed.  See license for details.
--
--	The "goal" level for the Cartographer quest.
--
--	The Labyrinth: a great maze that fills the whole level.  At its
--	heart lies the chamber of Asterion, the Minotaur of the Labyrinth,
--	whose walls wind round in rings, as the old labyrinths did, and in
--	it the stolen Celestial Sextant.
--
des.level_init({ style="mazegrid", bg ="-" });

des.level_flags("mazelevel");

des.map({ halign = "center", valign = "center", map = [[
-------------------------------
|..............|..............|
|.---------------------------.|
|.|.........................|.|
|.|.-----------------------.|.|
|.|.|.....................|.|.|
|.|.|.....................|.|.|
..|.+.....................|...|
|.|.|.....................|.|.|
|.|.|.....................|.|.|
|.|.-----------------------.|.|
|.|............|............|.|
|.---------------------------.|
|.............................|
-------------------------------
]], contents = function(rm)
   -- the only way in is through the maze, from the west
   des.mazewalk({ x = 00, y = 07, dir = "west", stocked = false })
   -- the heart of the Labyrinth
   des.region({ region={05,05,25,09}, lit=1, type="ordinary",
                irregular=1 })
   des.door("locked",04,07)
   -- Asterion and the Celestial Sextant
   des.monster("Asterion", 21, 07)
   des.object({ id = "sextant", x=24, y=07, buc="blessed",
                name="The Celestial Sextant" })
   -- the bones of those who came looking for it
   des.object({ id = "corpse", x=23, y=05, montype="surveyor" })
   des.object({ id = "corpse", x=22, y=09, montype="surveyor" })
   des.object({ id = "corpse", x=12, y=08, montype="cartographer" })
   des.object("chest", 25, 07)
   des.object("*", 24, 06)
   des.object("*", 24, 08)
   des.object("?", 23, 07)
   des.gold({ x=25, y=06, amount=math.random(300, 600) })
   des.gold({ x=25, y=08, amount=math.random(300, 600) })
   -- the winding rings are trapped
   des.trap("rolling boulder", 01, 11)
   des.trap("spiked pit", 20, 13)
   des.trap("magic", 29, 03)
   des.trap("rust", 12, 03)
   des.trap("anti magic", 03, 06)
   -- the Labyrinth's walls cannot be dug through, even by umber hulks
   des.non_diggable(selection.area(00,00,30,14))
   des.exclusion({ type = "teleport", region = { 00,00,30,14 } })
end
});

-- you come down into the far west of the Labyrinth
des.levregion({ region = {01,00,12,20}, region_islev=1, type="stair-up" })
des.teleport_region({ region = {01,00,12,20}, region_islev=1 })
des.non_diggable()

-- Objects
for i = 1, 14 do
   des.object()
end
des.object("boulder")
des.object("boulder")
des.object("boulder")
-- Random traps
for i = 1, 10 do
   des.trap()
end
-- Asterion's creatures roam the maze
des.monster({ id = "umber hulk", peaceful = 0 })
des.monster({ id = "umber hulk", peaceful = 0 })
des.monster({ id = "umber hulk", peaceful = 0 })
des.monster({ id = "umber hulk", peaceful = 0 })
des.monster({ id = "umber hulk", peaceful = 0 })
for i = 1, 10 do
   des.monster({ class = "q", peaceful = 0 })
end
for i = 1, 3 do
   des.monster({ peaceful = 0 })
end
