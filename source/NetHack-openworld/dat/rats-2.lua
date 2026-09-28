-- NetHack: Open World  rats-2.lua
--
--    WIP revised rat king level
--    Modification of the old mineking level.
--
-- Converted from Hack'EM rats.des (level "rats-2") for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.

des.level_init({ style = "solidfill", fg = " " })
des.level_flags("mazelevel")

-- Hack'EM puddles ('w') are plain floor ('.') here: 5.0 has no puddles.
-- The source map starts with an empty line; it is kept as a row of solid
-- rock so that all coordinates below match the original.
des.map({ halign = "center", valign = "center", map = [[
                                                                          
                 ....                  .......        .........           
                 .}}.                  .}}}}}.        .}}}}}}}.           
   ......................         ..........}.    .....}....}.........    
   .}}}}}}}}}}}}}....}}}.         .}}}}}}. .}.    .}}}}}.  ..}}}}}}}}.    
   .}...............}}.............}........}..  ..}......................
  ..}.......  .}}........}}}}}}}}}}}}}}}}}}}}..  .}}. -----------     .}}.
  .}}}}}}}}.  .}....}}}}}}.........}...........  ..}. |....\....|  .......
  .......}..  .............  ...}}}}.    ..........}. |.........| ..}.... 
       .}}.   ...... ...     ..........  ........}}}. |.........| .}}.... 
       .}..   ...}}. .}.........}}}}}}.  ..........}. ----+F+---- ... ... 
       ............. .}}}}}}}........}.  ....}.............}.     ....... 
         .}}}}}...  .......}.....}}}}}.  ....}}}}}}}}}...}}}.     .}}}}}. 
         .}..}....  .}}}}}}}}....}..... ..}....}...................}...}. 
         ....}.     .}........}}}}}}.   .}}}}}}}}}.  ....}}}}}}}}}}}. ... 
            ...     .}.   .}}}}......   .}.......}.  ........}.......     
                    ...   .....         ...     ...         ...           
]] })

-- The source had a commented-out
-- RANDOM_PLACES:(19,1),(42,1),(61,1),(21,15),(41,15),(61,16)
-- (only place[0] was ever meant to be used) and a commented-out
-- BRANCH:(35,06,35,06),(0,0,0,0); neither is used.
des.stair("up", 02,07)
des.stair("down", 61,16)

des.door("closed", 58,10)
des.door("closed", 60,10)

-- Potion of invulerability along with some other junk - it's a sewer after all.
-- (5.0 has no potion of invulnerability: potion of full healing instead.)
if percent(20) then
   des.object({ id = "full healing", class = "!" })
end
for i = 1, 3 do
   des.object()
end
for i = 1, 5 do
   des.gold({ amount = d(200) })
end

-- The Rat King's Throne Room
des.monster({ id = "Rat King", x = 59, y = 7, peaceful = 0 })
des.object({ id = "long sword", x = 59, y = 7 })
des.object({ class = "/", x = 59, y = 7 })
des.object({ class = "!", x = 59, y = 7 })
-- Hack'EM cheese -> cream pie (5.0 has no cheese)
des.object({ id = "cream pie", x = 59, y = 7 })
des.object({ id = "cream pie", x = 59, y = 7 })
des.object({ id = "elven boots", x = 59, y = 7 })

des.monster({ id = "pack rat", x = 55, y = 7, peaceful = 0 })
des.monster({ id = "pack rat", x = 56, y = 7, peaceful = 0 })
des.monster({ id = "pack rat", x = 57, y = 7, peaceful = 0 })
des.monster({ id = "pack rat", x = 58, y = 7, peaceful = 0 })
des.monster({ id = "black rat", x = 60, y = 7, peaceful = 0 })
des.monster({ id = "black rat", x = 61, y = 7, peaceful = 0 })
des.monster({ id = "black rat", x = 62, y = 7, peaceful = 0 })
des.monster({ id = "black rat", x = 63, y = 7, peaceful = 0 })
des.monster({ id = "black rat", x = 55, y = 8, peaceful = 0 })
des.monster({ id = "black rat", x = 56, y = 8, peaceful = 0 })
des.monster({ id = "black rat", x = 57, y = 8, peaceful = 0 })
des.monster({ id = "black rat", x = 58, y = 8, peaceful = 0 })
des.monster({ id = "giant rat", x = 59, y = 8, peaceful = 0 })
des.monster({ id = "giant rat", x = 60, y = 8, peaceful = 0 })
des.monster({ id = "giant rat", x = 61, y = 8, peaceful = 0 })
des.monster({ id = "giant rat", x = 62, y = 8, peaceful = 0 })
des.monster({ id = "giant rat", x = 63, y = 8, peaceful = 0 })
des.monster({ id = "sewer rat", x = 55, y = 9, peaceful = 0 })
des.monster({ id = "sewer rat", x = 56, y = 9, peaceful = 0 })
des.monster({ id = "sewer rat", x = 57, y = 9, peaceful = 0 })
des.monster({ id = "sewer rat", x = 58, y = 9, peaceful = 0 })
des.monster({ id = "sewer rat", x = 59, y = 9, peaceful = 0 })
des.monster({ id = "sewer rat", x = 60, y = 9, peaceful = 0 })
des.monster({ id = "sewer rat", x = 61, y = 9, peaceful = 0 })
des.monster({ id = "sewer rat", x = 62, y = 9, peaceful = 0 })
des.monster({ id = "rabid rat", x = 63, y = 9, peaceful = 0 })
-- rats in the sewers...
for i = 1, 20 do
   des.monster({ id = "sewer rat", peaceful = 0 })
end
for i = 1, 11 do
   des.monster({ class = "r", peaceful = 0 })
end

-- And of course one of these...
des.monster({ id = "brown pudding", peaceful = 0 })
