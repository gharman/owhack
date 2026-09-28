-- NetHack: Open World  ucastle.lua
-- The dungeon under Fort Ludios.
-- Converted from Hack'EM ucastle.des for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.
--
des.level_init({ style = "mazegrid", bg = "-" });

des.level_flags("mazelevel", "noteleport", "hardfloor")

-- Hack'EM terrain that 5.0 lacks is floor ('.') here: puddles ('w'),
-- sewage ('s'), the forge ('U') and the toilet ('Z').
des.map({ halign = "center", valign = "center", map = [[
                                         # # # # # # # # # # #
   -----                                -+-+-+-+-+-+-+-+-+-+-+-
   |...+###          ########           |.....................|
   -----  #          #------+------     |.....................|
      ----+----      #|...........|     |.......PPPPPPP.......|
      |.......|      #|...........+#####+.....................|
      |.......+#######|...........|     |.....................|
      |.......|       -------------     |.....................|
      ----+----                         |.....................|
          #         ----------  -----   -+-+-+-+-+-+-+-+-+-+-+- 
          #         |.....{..|  |...|    # # # # # # # # # # # 
          ##########+........+##S..K|
                    |........|  -----
                    ----------
]] });

--  Regions
des.region(selection.area(04,02,06,02), "lit")
des.region({ region = {07,05,13,07}, lit = 1, type = "barracks", filled = 1 })
des.region(selection.area(21,10,28,12), "unlit")
des.region(selection.area(23,04,33,06), "unlit")
des.region(selection.area(32,10,34,11), "unlit")
des.region({ region = {41,02,61,08}, lit = 0, type = "swamp", filled = 1 })

-- Stairs
--des.levregion({ region = {04,02,04,02}, type = "branch" })
des.stair("up", 04,02)
des.teleport_region({ region = {41,02,61,08} })

--  Doors
des.door("closed",07,02)
des.door("closed",10,04)
des.door("locked",10,08)
des.door("locked",20,11)
des.door("locked",14,06)
des.door("locked",28,03)
des.door("locked",34,05)
des.door("locked",40,05)

-- Cells top row
des.door("random",41,01)
des.door("random",43,01)
des.door("random",45,01)
des.door("random",47,01)
des.door("random",49,01)
des.door("random",51,01)
des.door("random",53,01)
des.door("random",55,01)
des.door("random",57,01)
des.door("random",59,01)
des.door("random",61,01)
-- Cells bottom row
des.door("random",41,09)
des.door("random",43,09)
des.door("random",45,09)
des.door("random",47,09)
des.door("random",49,09)
des.door("random",51,09)
des.door("random",53,09)
des.door("random",55,09)
des.door("random",57,09)
des.door("random",59,09)
des.door("random",61,09)

-- Traps
des.trap("board", 33,05)
des.trap("board", 13,06)
des.trap("fire", 30,04)
des.trap("magic", 30,06)

-- Guardians
des.monster("'", 26,04)
des.monster("'", 25,05)
des.monster("'", 26,06)
if percent(50) then des.monster("'", 24,04) end
if percent(50) then des.monster("'", 24,06) end

-- Jellies and Puddings
if percent(50) then des.monster("j", 44,04) end
if percent(50) then des.monster("j", 56,06) end
if percent(80) then des.monster("F", 44,06) end
if percent(80) then des.monster("F", 57,04) end
if percent(80) then des.monster("F", 49,06) end
if percent(50) then des.monster("P", 51,07) end
if percent(50) then des.monster("P", 43,03) end
des.monster("green slime", 59,10)
des.monster("green slime", 51,10)
if percent(50) then des.monster("green slime", 43,10) end

-- Wine Celler
-- (Hack'EM's potion of amnesia is a potion of booze here)
des.object({ id = "booze", class = "!", x = 21, y = 10 })
des.object({ id = "booze", class = "!", x = 23, y = 10 })
des.object({ id = "booze", class = "!", x = 25, y = 10 })
des.object({ id = "booze", class = "!", x = 28, y = 10 })
des.object({ id = "booze", class = "!", x = 22, y = 12 })
des.object({ id = "booze", class = "!", x = 24, y = 12 })
des.object({ id = "booze", class = "!", x = 26, y = 12 })
des.object("!", 22,10)
des.object("!", 24,10)
des.object("!", 26,10)
des.object("!", 27,10)
des.object("!", 21,12)
des.object("!", 23,12)
des.object("!", 25,12)
des.object("!", 27,12)
des.object("!", 28,12)
