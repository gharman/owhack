-- NetHack: Open World  spiders.lua
-- The Spider Caves
--       SCCS Id: @(#)spiders.des  3.4     1993/02/23
--       Copyright (c) 1989 by Jean-Christophe Collet
--       Copyright (c) 1991 by M. Stephenson
-- Converted from Slash'EM spiders.des for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel")

des.map({ halign = "center", valign = "center", map = [[
                            -----               -----                
                         ----...-               |...|------          
            ------    ----.....--               ---.......|          
            -....------.....----                 -----..---          
            ----.........----       |-------------.....--            
              -...----......----|----..............-----             
              -.---  ------....--.......-----|------     -------     
              -.-  --------..................|-------- ---.....-     
      |------ ---  -........---...----|..............---...-----     
      |.....-- ---------.---- |...|   |------|...........-----       
      |----..---.........-    |...|          -----------.....--------
       |.........-------.-    |...|-|                  -------......-
       -----------     ---|---|.....|             --------......-----
                 ---------|.........---------------.........-----    
           ------|.............|-|....................-----.....---- 
        ---|..................---|...-----------.....---  -----....- 
        |....----|.-----------|......|         ----....-----  ------ 
        |----|   |..--      |-|...|--|            ---......-         
                 -|..| -----|...|--                 ---..---         
                  ---- |.......|-                     -.--           
                       |-------|                      ---            
]] });

-- Arrival point (Slash'EM also put the up stairs here; the branch is the
-- way back out)
des.levregion({ region = {32,10,32,10}, type = "branch" })
--
-- the stuff to find here
-- (Slash'EM's potions of invulnerability are potions of full healing here)
des.object({ id = "full healing", class = "!" })
des.object({ id = "full healing", class = "!" })
des.object({ id = "make invisible", class = "/" })
des.object("amulet versus poison")
des.object("speed boots")
des.object({ id = "conflict", class = "=" })
des.object({ id = "death", class = "/" })
for i = 1, 48 do
   des.object("egg")
end
des.gold()
des.gold()
des.gold()
des.gold()
des.gold()
--
for i = 1, 10 do
   des.monster({ class = "s", peaceful = 0 })
end
for i = 1, 22 do
   des.monster({ id = "giant spider", peaceful = 0 })
end
des.monster({ id = "Shelob", peaceful = 0 })
des.monster({ id = "Girtab", peaceful = 0 })
--
for i = 1, 48 do
   des.trap("web")
end
