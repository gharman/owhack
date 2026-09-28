-- NetHack Cartographer Car-loca.lua
--	Copyright (c) 2026 by the NetHack: Open World contributors
-- NetHack may be freely redistributed.  See license for details.
--
--	The "locate" level for the Cartographer quest.
--
--	The Edge of the Map: the country here is coming unmoored.  West of
--	the river it is still honest woodland, but beyond it the ground is
--	split by rifts that open onto nothing, and further east the land
--	breaks up altogether into a maze.  The way down into the Labyrinth
--	is somewhere in that maze.
--
des.level_init({ style="mazegrid", bg ="-" });

des.level_flags("mazelevel", "noflip")

des.map({ x = 1, y = 0, map = [[
......T...T.T..T....}}.....  ......  ......  ......|xxxxxxxxxxxxxxxxxxxxxxxxxx
TT.TT.T..............}}.T..  .....  .......  ......|xxxxxxxxxxxxxxxxxxxxxxxxxx
...T......T.....T....}}..........  ....T...  ......|xxxxxxxxxxxxxxxxxxxxxxxxxx
T...---.---..........}}.....       ................|xxxxxxxxxxxxxxxxxxxxxxxxxx
....|.....|....TT....}}......  ..  .........  .....|xxxxxxxxxxxxxxxxxxxxxxxxxx
....|.....|.................  ...............  ....|xxxxxxxxxxxxxxxxxxxxxxxxxx
T...--.----.......T.}}.....  ..T...  .......  .T...|xxxxxxxxxxxxxxxxxxxxxxxxxx
.T...........TT...T}}.....  ........   ...------...|xxxxxxxxxxxxxxxxxxxxxxxxxx
....T..............}}.....  .......  ..   |.....|..|xxxxxxxxxxxxxxxxxxxxxxxxxx
....T.........T.T..}}.....  .......  .....|.---.|..|xxxxxxxxxxxxxxxxxxxxxxxxxx
.....T.............}}.............  ......|.|.|.|...xxxxxxxxxxxxxxxxxxxxxxxxxx
...................}}......         ......|.|..-|..|xxxxxxxxxxxxxxxxxxxxxxxxxx
..TT.T....T..T...T..}}......  ....  ............|..|xxxxxxxxxxxxxxxxxxxxxxxxxx
........T...........}}.....  ..............  ...T..|xxxxxxxxxxxxxxxxxxxxxxxxxx
.T...................}}....  ...T...  ......  .....|xxxxxxxxxxxxxxxxxxxxxxxxxx
..........T....T.T.........  ........  ....  ......|xxxxxxxxxxxxxxxxxxxxxxxxxx
...........T.........}}....  .......  . ...........|xxxxxxxxxxxxxxxxxxxxxxxxxx
.............T.......}}.............  ...  ........|xxxxxxxxxxxxxxxxxxxxxxxxxx
.T.................T.}}.....  .....  ..T.  ........|xxxxxxxxxxxxxxxxxxxxxxxxxx
....................}}...T...  ...........  ..T....|xxxxxxxxxxxxxxxxxxxxxxxxxx
...................}}.........  ...  ......  ......|xxxxxxxxxxxxxxxxxxxxxxxxxx
]] });
-- Dungeon Description: the open country is lit, the maze is not
des.region(selection.area(00,00,50,20), "lit")
-- the ruined camp of the last survey party
des.region({ region={05,04,09,05}, lit=1, type="ordinary", irregular=1 })
-- the maze begins where the land gives out
des.mazewalk({ x = 51, y = 10, dir = "east", stocked = false })
-- Stairs
des.stair("up", 02,10)
des.levregion({ region = {62,03,77,19}, region_islev=1, type="stair-down" })
-- the rifts open onto nothing; neither they nor the barrier can be dug
des.non_diggable(selection.area(00,00,51,20))
-- the survey party's camp
des.object({ id = "corpse", x=06, y=04, montype="surveyor" })
des.object({ id = "corpse", x=09, y=05, montype="surveyor" })
des.object("scroll of blank paper", 07, 05)
des.object("?", 08, 04)
des.object("(", 06, 05)
des.engraving({ coord = {07,03}, type = "engrave",
                text = "The road east goes round in circles.  Turn back." })
-- the heart of the little maze in the rocks
des.object("*", 45, 10)
des.object("?", 46, 11)
-- Objects
for i = 1, 10 do
   des.object()
end
-- Random traps
for i = 1, 8 do
   des.trap()
end
-- Random monsters
des.monster({ id = "umber hulk", x = 30, y = 10, peaceful = 0 })
des.monster({ id = "umber hulk", x = 40, y = 5, peaceful = 0 })
des.monster({ id = "umber hulk", x = 47, y = 16, peaceful = 0 })
des.monster({ id = "umber hulk", peaceful = 0 })
des.monster({ class = "q", x = 12, y = 8, peaceful = 0 })
des.monster({ class = "q", x = 25, y = 16, peaceful = 0 })
des.monster({ class = "q", x = 33, y = 2, peaceful = 0 })
des.monster({ class = "q", x = 38, y = 13, peaceful = 0 })
des.monster({ class = "q", x = 46, y = 3, peaceful = 0 })
des.monster({ class = "q", peaceful = 0 })
des.monster({ class = "q", peaceful = 0 })
des.monster({ class = "q", peaceful = 0 })
des.monster({ peaceful = 0 })
des.monster({ peaceful = 0 })
