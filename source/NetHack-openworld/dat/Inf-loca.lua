-- NetHack Infidel Inf-loca.lua
--	Infidel role by Tomsod, for EvilHack.
--	Ported from EvilHack's Infidel.des (cross-checked with Hack'EM's).
-- NetHack may be freely redistributed.  See license for details.
--
--
--	The "locate" level for the quest.
--
--	This is the edge of the Howling Forest.
--	Somewhere in here the Paladin awaits you.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "hardfloor")

des.level_init({ style = "mines", fg = ".", bg = "T", smoothed = true,
                 joined = true, lit = 0, walled = true })

-- (the reference's GEOMETRY:(49,00) is relative to column 1, so the map
-- goes at level column 50, flush with the right edge of the level)
--         1         2
--123456789012345678901234567890
des.map({ x = 50, y = 00, map = [[
xxxx.|            ----        
xxx..--           |..|        
x.....---         |..|        
...}}...|         -+--        
...}}}..--         #          
..}}}....|         #          
...}}....|       --S-         
.........--      |..|         
..........--     |..|         
...........|     |..+####     
...........+#####+..|   #     
...........|     |..|   #     
...........|     ----   #     
..........--            #     
.........--             #     
.........|              #     
........-|            --+--   
.........|            |...|   
x......---            |...|   
xxx.----              -----   
xxxx|                         
]], contents = function()
   des.non_diggable(selection.area(05,00,29,20))

   -- Upstairs to (rest of) the underground complex.
   des.region({ region = {23,17,25,18}, type = "ordinary" })
   des.stair("up", 24, 18)
   des.monster({ class = "k",
                 coord = selection.area(23,17,25,18):rndcoord() })
   des.door("random", 24, 16)

   -- The last room before the Forest!
   des.door("random", 20, 09)
   des.region({ region = {18,07,19,11}, type = "ordinary" })
   des.monster({ class = "h",
                 coord = selection.area(18,07,19,11):rndcoord() })
   des.door("random", 17, 10)
   des.door("random", 11, 10)

   -- An ogre guards some treasure.
   des.door("locked", 19, 03)
   des.region({ region = {19,01,20,02}, type = "ordinary" })
   des.monster("O", 19, 02)
   des.object("chest", 19, 01)
   des.object("chest", 20, 01)

   -- The lake.
   des.monster("piranha", 03, 03)
   des.monster("piranha", 04, 04)
   des.monster("piranha", 04, 05)

   -- The forest's edge.
   des.replace_terrain({ region = {00,00,10,20},
                         fromterrain = ".", toterrain = "T", chance = 5 })
end });

-- (from here on, as after the reference's NOMAP, coordinates are relative
-- to the whole level again; the reference's stair region (00,00,39,20)
-- is given here in absolute level coordinates)
des.levregion({ region = {01,00,40,20}, region_islev = 1, type = "stair-down" })
local forest = selection.filter_mapchar(selection.area(00,00,60,20), ".")
des.monster({ id = "werewolf", coord = forest:rndcoord() })
des.monster({ id = "werewolf", coord = forest:rndcoord() })
des.monster({ id = "werewolf", coord = forest:rndcoord() })
for i = 1, d(4,4) do
   des.monster({ class = "d", coord = forest:rndcoord() })
end
des.monster({ class = "u", coord = forest:rndcoord() })
des.monster({ class = "u", coord = forest:rndcoord() })
if percent(65) then
   des.monster({ id = "forest centaur", coord = forest:rndcoord() })
end
if percent(40) then
   des.monster({ id = "woodchuck", coord = forest:rndcoord() })
end

-- Some traps and a little loot.
des.object()
des.object()
des.object()
des.object()
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
