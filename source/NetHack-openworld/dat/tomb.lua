-- NetHack: Open World  tomb.lua
-- The Lost Tomb
--       SCCS Id: @(#)tomb.des  3.4     1993/02/23
--       Copyright (c) 1989 by Jean-Christophe Collet
--       Copyright (c) 1991 by M. Stephenson
-- Converted from Slash'EM tomb.des for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel")

des.map({ halign = "center", valign = "center", map = [[
                    --------                     
                    |......|                     
                    |......|                     
                    |---.--|                     
                        #                        
                        #                        
                   |----S---|           --------|
       |------|    |........|           |.......|
       |......------........|------------.......|
       |......+.............+...........+.......|
       |......+.............+...........+.......|
       |......------........|------------.......|
       |------|    |........|           |.......|
                   |---S----|           --------|
                       #                         
                       #                         
                    |--.---|                     
                    |......|                     
                    |......|                     
                    --------                     
]] });

-- Arrival point (Slash'EM also put the up stairs here; the branch is the
-- way back out)
des.levregion({ region = {08,09,08,09}, type = "branch" })
des.door("locked", 14, 09)
des.door("locked", 14, 10)
des.door("locked", 28, 09)
des.door("locked", 28, 10)
des.door("locked", 40, 09)
des.door("locked", 40, 10)
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("spiked pit")
des.object("chest", 47, 09)
for i = 1, 10 do
   des.gold({ x = 47, y = 09 })
end
des.object({ class = "?", x = 47, y = 09 })
des.object({ class = "?", x = 47, y = 09 })
des.object({ class = "?", x = 47, y = 09 })
des.object({ class = "?", x = 47, y = 09 })
des.object({ class = "!", x = 47, y = 09 })
des.object({ class = "!", x = 47, y = 09 })
des.object({ class = "!", x = 47, y = 09 })
des.object({ x = 47, y = 09 })
des.object({ x = 47, y = 09 })
des.object()
des.object("chest", 23, 01)
des.object({ x = 23, y = 01 })
des.object({ x = 23, y = 01 })
des.object({ x = 23, y = 01 })
des.object("chest", 24, 18)
des.object({ x = 24, y = 18 })
des.object({ x = 24, y = 18 })
des.object({ x = 24, y = 18 })
des.object("chest", 47, 10)
for i = 1, 10 do
   des.gold({ x = 47, y = 10 })
end
des.object({ class = "?", x = 47, y = 10 })
des.object({ class = "?", x = 47, y = 10 })
des.object({ class = "?", x = 47, y = 10 })
des.object({ class = "?", x = 47, y = 10 })
des.object({ class = "+", x = 47, y = 10 })
des.object({ class = "+", x = 47, y = 10 })
des.object({ class = "+", x = 47, y = 10 })
des.object({ class = "+", x = 47, y = 10 })
des.object({ x = 47, y = 10 })
des.object({ x = 47, y = 10 })
des.object({ x = 47, y = 10 })
des.object({ x = 47, y = 10 })
des.object({ x = 47, y = 10 })
des.monster("lich", 47, 09)
for i = 1, 14 do
   des.monster("shadow")
end
for i = 1, 19 do
   des.monster("Z")
end
for i = 1, 11 do
   des.monster("M")
end
