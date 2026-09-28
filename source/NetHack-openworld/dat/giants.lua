-- NetHack: Open World  giants.lua
-- the Giant caves
-- Converted from Slash'EM giants.des (level "cav2fill") for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel")

des.map({ halign = "center", valign = "center", map = [[
                 ----------|    |---|                                  
                 |.........|    |...|         |---------|              
 -----------|    |.........|    |...|         |.........|              
 |..........|    |.........|    |...|         |.........|              
 |..........|   |----+------------+----------------+------|            
 |..........|   |.........................................|            
 |..........|   |.........................................|-----------|
 |--|.......|   |----+------+----------------+-----------+|...........|
    |---+--------.......|...........|....|......|    |................|
    |...................|...........|....|......|    |................|
    |...................|-----------|....|......|    |................|
    |\..................S...........|....|......|    |................|
    |...................|-------------+--|......|    |----------------|
    |-------+-----------|......|................|                      
        |...............|......|................|                      
        |...............+......|................|                      
        |...............|-----------------------|                      
        |...............|                                              
        |---------------|                                              
]] });

-- Arrival point (Slash'EM also put the up stairs here; the branch is the
-- way back out)
des.levregion({ region = {34,02,34,02}, type = "branch" })
--
des.door("closed", 34, 04)
des.door("closed", 21, 04)
des.door("closed", 51, 04)
des.door("closed", 57, 07)
des.door("closed", 45, 07)
des.door("closed", 28, 07)
des.door("closed", 21, 07)
des.door("closed", 08, 08)
des.door("closed", 38, 12)
des.door("closed", 12, 13)
des.door("closed", 24, 15)
--
-- the king's hidden treasure
des.object("chest", 35, 11)
for i = 1, 7 do
   des.gold({ x = 35, y = 11 })
end
for i = 1, 5 do
   des.object({ class = "*", x = 35, y = 11 })
end
des.object({ class = "\"", x = 35, y = 11 })
des.object({ class = "\"", x = 35, y = 11 })
des.object({ x = 35, y = 11 })
des.object({ x = 35, y = 11 })
des.object({ x = 35, y = 11 })
-- stuff scattered around
for i = 1, 10 do
   des.object()
end
--
for i = 1, 20 do
   des.monster({ id = "giant", peaceful = 0 })
end
for i = 1, 7 do
   des.monster({ class = "H", peaceful = 0 })
end
-- on the throne
des.monster({ id = "Largest Giant", x = 05, y = 11, peaceful = 0 })
for i = 1, 8 do
   des.monster({ class = "O", peaceful = 0 })
end
for i = 1, 4 do
   des.monster({ class = "T", peaceful = 0 })
end
--
des.trap()
des.trap()
des.trap()
des.trap()
