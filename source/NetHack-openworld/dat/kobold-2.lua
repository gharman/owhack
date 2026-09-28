-- NetHack: Open World  kobold-2.lua
-- Kobold level
-- Converted from Slash'EM kobold-2.des for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.

des.level_init({ style = "solidfill", fg = " " })
des.level_flags("mazelevel")

des.map({ halign = "center", valign = "center", map = [[
|--------------------------------------    -------------------|  ----|
|....|...|.|...|......|.|......|......|----|............+.....S##+...|
|S---|...|.+...|......|.+......|......|....|.|---+------|.....|  |...|
|....|...+.|...|......+.|......|......|....+.|..|.......|.....|  |---|
|....|...|.|...|......|.|......|......|....|.|..--|.....|.....S####   
|--+------+------------+----------+---------.+....|.....---+--|   #   
|.......................|.....|..............|....|.....|.....|   ### 
|+--------------------|.|.....+.|---+-----S------------+|.....|     # 
|.......+.+.....|.....|.|.....|.|......|  #           |.|.....|     # 
|.---+---.|----.+.....|.|.....|.|......|  ##          |.+.....|     # 
|.|.....|.|...|.|.....|.-------.|------|   #          |.|.....|  #### 
|.|.....|.+...|+|-----|.|...|...|....|     ###        |+------|  #    
|.|-----|.|...|.......|.|...|.|-|....|     ###        |.......| |+--| 
|.|.....|.|...|.......|.|...|.+K|....|                |.......| |...| 
|.|.....|.----|...\...|.--+--.-----+------------------|.......| |...| 
|.+.....|.....+.......+..............S................S.......| |---| 
|--------------------------------------------------------------       
]] })
-- (The source's RANDOM_MONSTERS: 'k' is not needed: every monster below
-- names its class or type explicitly.)
-- ROOM: "ordinary" , lit, random, random, (11,9)   (commented out in the source)

des.stair("up", 23,06)
des.stair("down", 19,14)

des.door("closed", 01,07)
des.door("closed", 02,15)
des.door("closed", 03,05)
des.door("closed", 05,09)
des.door("closed", 08,08)
des.door("closed", 09,03)
des.door("closed", 10,05)
des.door("closed", 10,11)
des.door("closed", 10,08)
des.door("closed", 11,02)
des.door("closed", 14,15)
des.door("closed", 15,11)
des.door("closed", 16,09)
des.door("closed", 22,15)
des.door("closed", 22,03)
des.door("closed", 23,05)
des.door("closed", 24,02)
des.door("closed", 26,14)
des.door("closed", 30,07)
des.door("closed", 30,13)
des.door("closed", 34,05)
des.door("closed", 35,14)
des.door("closed", 36,07)
des.door("closed", 43,03)
des.door("closed", 45,05)
des.door("closed", 49,02)
des.door("closed", 55,07)
des.door("closed", 55,11)
des.door("closed", 56,01)
des.door("closed", 56,09)
des.door("closed", 59,05)

des.trap()
des.trap()
des.trap()
for i = 1, 7 do
   des.gold()
end

des.monster({ id = "rhumbat", x = 43, y = 11, peaceful = 0, asleep = 1 })
des.object({ id = "chest", x = 45, y = 12 })
des.gold({ x = 45, y = 12 })
des.gold({ x = 45, y = 12 })
des.gold({ x = 45, y = 12 })
des.object({ class = "*", x = 45, y = 12 })
des.object({ class = "/", x = 45, y = 12 })
des.object({ class = "*", x = 45, y = 12 })

des.monster({ id = "rhumbat", x = 65, y = 13, peaceful = 0, asleep = 1 })
des.object({ id = "chest", x = 65, y = 13 })
des.gold({ x = 65, y = 13 })
des.gold({ x = 65, y = 13 })
des.object({ class = "*", x = 65, y = 13 })
des.object({ class = "*", x = 65, y = 13 })
des.object({ class = "*", x = 65, y = 13 })

des.monster({ id = "giant spider", x = 67, y = 01, peaceful = 0, asleep = 1 })
des.gold({ x = 68, y = 02 })
des.gold({ x = 68, y = 02 })
des.gold({ x = 68, y = 02 })
des.object({ class = "*", x = 68, y = 02 })
des.object({ class = "*", x = 68, y = 02 })
des.object({ class = "*", x = 68, y = 02 })
des.object({ id = "chest", x = 68, y = 02 })

des.object({ id = "chest", x = 02, y = 01 })
des.object({ id = "chest", x = 03, y = 01 })
des.object({ id = "chest", x = 04, y = 01 })

des.object({ id = "chest", x = 18, y = 14 })
des.object({ class = ")", x = 18, y = 14 })
des.object({ class = ")", x = 18, y = 14 })
des.object({ class = "/", x = 18, y = 14 })
des.object({ class = "[", x = 18, y = 14 })
des.object({ class = "[", x = 18, y = 14 })
des.object({ class = "!", x = 18, y = 14 })
des.object({ class = "!", x = 18, y = 14 })

for i = 1, 30 do
   des.monster({ id = "kobold", peaceful = 0 })
end
for i = 1, 5 do
   des.monster({ class = "k", peaceful = 0 })
end

-- Kroo's court, around the throne
des.monster({ id = "large kobold", x = 15, y = 12, peaceful = 0 })
des.monster({ class = "k", x = 17, y = 12, peaceful = 0 })
des.monster({ id = "large kobold", x = 19, y = 12, peaceful = 0 })
des.monster({ id = "rock kobold", x = 20, y = 12, peaceful = 0 })
des.monster({ class = "k", x = 21, y = 12, peaceful = 0 })
des.monster({ id = "swamp kobold", x = 16, y = 13, peaceful = 0 })
des.monster({ class = "k", x = 18, y = 13, peaceful = 0 })
des.monster({ id = "large kobold", x = 19, y = 13, peaceful = 0 })
des.monster({ class = "k", x = 21, y = 13, peaceful = 0 })
des.monster({ id = "swamp kobold", x = 15, y = 14, peaceful = 0 })
des.monster({ id = "swamp kobold", x = 17, y = 14, peaceful = 0 })
des.monster({ id = "Kroo the Kobold King", x = 18, y = 14, peaceful = 0 })
des.monster({ id = "rock kobold", x = 20, y = 14, peaceful = 0 })
des.monster({ id = "kobold shaman", x = 15, y = 15, peaceful = 0 })
des.monster({ id = "kobold shaman", x = 16, y = 15, peaceful = 0 })
des.monster({ class = "k", x = 20, y = 15, peaceful = 0 })
des.monster({ class = "k", x = 21, y = 15, peaceful = 0 })
