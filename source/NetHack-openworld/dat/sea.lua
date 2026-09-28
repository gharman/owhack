-- NetHack: Open World  sea.lua
--       SCCS Id: @(#)sea.des  3.4     1993/02/23
--       Copyright (c) 1989 by Jean-Christophe Collet
--       Copyright (c) 1991 by M. Stephenson
-- Converted from Slash'EM sea.des for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.
--
-- This is the Sunless Sea... home of sharks, squids, and underwater
-- treasure. Hope you brought your amulet of magical breathing!
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel")

des.message("You hear the roar of the sea. That can't be right....")

des.map({ halign = "center", valign = "center", map = [[
                            }}}}}}}}        }}}}}}}}}}              
                       }}}}}}}}}}}}}}}}   }}}}}}}}}}}}}}}}}}}       
      .......}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}     
   ...........}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}} 
  .............}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}  
  .............}}}}}}}}}}}}}}}}}}}}}}}}}}}}}...}}}}}}}}}}}}}}}}}    
  ..............}}}}}}}}}}}}}}}}}}}}}}}}}}}.....}}}}}}}}}}}}}}}}}}} 
    ...........}}}}}}}}}}}}}}}}}}}}}}}}}}}}}.....}}}}}}}}}}}}}}}}}} 
   ............}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}...}}}}}}}}}}}}}}}    
     ...........}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}   
     ..........}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}   
       ........}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}  
     ..........}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}   
      .......}}}}}}}}}}}}}}}}}}}}}}}}}}}}     }}}}}}}}}}}}}}}}}     
         ....}}}}}}}}  }}}  }}}}}}}}}}}       }}}}}}}}}}}}}}}}      
                             }}}}}}}              }}}}}}}           
]] });

-- possible resting places of the missing magic lamp
local place = { {40,06}, {49,05}, {46,10}, {30,07} }
shuffle(place)

des.region(selection.area(00,00,66,15), "unlit")
-- Arrival point (Slash'EM also put the up stairs here; the branch is the
-- way back out)
des.levregion({ region = {05,12,05,12}, type = "branch" })
-- the treasure island!
des.object("chest", 45, 06)
des.object({ x = 45, y = 06 })
des.object({ x = 45, y = 06 })
des.object({ x = 45, y = 06 })
des.object({ class = "/", x = 45, y = 06 })
des.object({ class = "/", x = 45, y = 06 })
des.object({ class = "\"", x = 45, y = 06 })
des.object({ class = "\"", x = 45, y = 06 })
des.object({ class = "=", x = 45, y = 06 })
des.object({ class = "=", x = 45, y = 06 })
des.object({ class = "*", x = 45, y = 06 })
des.object({ class = "*", x = 45, y = 06 })
des.object({ class = "*", x = 45, y = 06 })
-- beach junk...
des.object()
des.object()
des.object()
des.object()
-- the missing magic lamp!
des.object({ id = "magic lamp", coord = place[1] })
-- the beach-combing committee
des.monster({ id = "giant crab", x = 10, y = 06, peaceful = 0 })
des.monster({ id = "giant crab", x = 11, y = 07, peaceful = 0 })
des.monster({ id = "giant crab", x = 10, y = 08, peaceful = 0 })
des.monster({ id = "giant crab", x = 12, y = 09, peaceful = 0 })
des.monster({ id = "giant crab", x = 10, y = 11, peaceful = 0 })
-- lurking offshore...
des.monster({ id = "shark", x = 26, y = 05, peaceful = 0 })
des.monster({ id = "shark", x = 28, y = 05, peaceful = 0 })
des.monster({ id = "shark", x = 30, y = 06, peaceful = 0 })
des.monster({ id = "shark", x = 27, y = 07, peaceful = 0 })
des.monster({ id = "shark", x = 26, y = 09, peaceful = 0 })
des.monster({ id = "shark", x = 30, y = 09, peaceful = 0 })
des.monster({ id = "shark", x = 31, y = 11, peaceful = 0 })
for i = 1, 6 do
   des.monster({ id = "shark", peaceful = 0 })
end
for i = 1, 7 do
   des.monster({ class = ";", peaceful = 0 })
end
des.engraving({ x = 11, y = 03, type = "burn", text = "The lamp washed into the sea while I slept! Woe and damnnation!" })
des.object({ x = 11, y = 03 })
