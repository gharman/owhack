-- NetHack Necromancer Nec-loca.lua
--	Copyright (c) 1992 by David Cohrs
-- NetHack may be freely redistributed.  See license for details.
--
--
--	The "locate" level for the quest.
--
--	Here you have to find the Entrance to the Lair of Maugneshaagar to go
--	further towards your assigned quest.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "hardfloor")

des.map([[
                                                                           
                           .....                                           
                         .........              .............              
                       ............           .................            
                     ..............        .......................         
     ...CC..       .................       .......................         
  ....C.......C    ..L...L..LLL.....        ......................         
  ..............   LLL.......LLL.....         ....................         
 ......L..L.....  ...................L       .....................         
 ............L..CC................L..L        ..................           
  ..............   .................L          ..................          
  ....L..L.....     ......C.C.......L              ..............          
    ........L..             ..CCC...       CCC....   ...........           
   ...   .....                  .C.C..C....C........     ........          
   ...                              .C..CCC...C.........  --S--            
  ....                                 ........................            
  .....                                 ......C.C............              
   ....                                     ..................             
                                                    ........               
                                                                           
                                                                           
]]);
-- Dungeon Description
des.region(selection.area(00,00,66,20), "unlit")
-- Stairs
des.stair("up", 03,17)
des.stair("down", 54,05)
-- Non diggable walls
des.non_diggable(selection.area(00,00,66,20))
-- Objects
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
-- Random traps
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("spiked pit")
des.trap("spiked pit")

des.trap("magic")
des.trap("dart")
des.trap("dart")
des.trap("dart")
-- Random monsters.
des.monster({ id = "mongbat", peaceful = 0 })
des.monster({ id = "mongbat", peaceful = 0 })
des.monster({ id = "mongbat", peaceful = 0 })
des.monster({ id = "mongbat", peaceful = 0 })
des.monster({ id = "mongbat", peaceful = 0 })
des.monster({ id = "mongbat", peaceful = 0 })
des.monster({ id = "mongbat", peaceful = 0 })
des.monster({ id = "mongbat", peaceful = 0 })
des.monster({ id = "mongbat", peaceful = 0 })
des.monster({ id = "mongbat", peaceful = 0 })
des.monster({ class = "B", peaceful = 0 })
des.monster({ class = "B", peaceful = 0 })
des.monster({ class = "B", peaceful = 0 })
des.monster({ id = "nupperibo", peaceful = 0 })
des.monster({ id = "nupperibo", peaceful = 0 })
des.monster({ id = "nupperibo", peaceful = 0 })
des.monster({ id = "nupperibo", peaceful = 0 })
des.monster({ id = "nupperibo", peaceful = 0 })
des.monster({ id = "nupperibo", peaceful = 0 })
des.monster({ id = "nupperibo", peaceful = 0 })
des.monster({ id = "nupperibo", peaceful = 0 })
des.monster({ id = "blood imp", peaceful = 0 })
des.monster({ id = "blood imp", peaceful = 0 })
des.monster({ id = "blood imp", peaceful = 0 })
des.monster({ id = "blood imp", peaceful = 0 })
des.monster({ id = "blood imp", peaceful = 0 })
des.monster({ id = "blood imp", peaceful = 0 })
des.monster({ id = "blood imp", peaceful = 0 })
des.monster({ class = "i", peaceful = 0 })
des.monster({ class = "i", peaceful = 0 })
des.monster({ class = "i", peaceful = 0 })
des.monster({ class = "i", peaceful = 0 })
des.monster({ class = "i", peaceful = 0 })
