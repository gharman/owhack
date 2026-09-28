-- NetHack Jedi Jed-goal.lua
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991,92 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
--
--	The "goal" level for the quest.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel");

--         1         2         3         4         5         6         7
--123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
.......PP......                                                             
......P......     .............................    ...............          
.....P.PP....    .......L................L.....     .......L.......         
..PPPPP.....   ........L.L..............L.....    ........LL........        
...P.PP......    ....LL...L..L.....LL..LL....   ........L....L........      
...PP.P....    ............LLL...L..L.LL....      .....L......L.......      
...P...P....   ......LL....L..L.L....LL........     ...............         
...PPPPP..............L...L..L.L....LL........   ......L....LL.....         
..P.P................L..LL....L....L.L.......     .........L.L......        
........................L......L..L.L........HHH......L..LL..L.......       
....P....    ..........LL....L.L.L..L........   ......LL..LL.L.....         
....PPP...    .........LL...L.L.L..LL........   .....L..LL..LL.....         
....PP......    ............L.L....L.......   .......LLL.L..........        
....P..P.....   ........L.....L.....L.....   .......L.L...LLLLL......       
...PP..PP.....  ........L....L.L..L........   .....LL..LL.L..L......        
..PP..P.P....    ........L..L...L.L.........   ....LLLLLLLLL.L.........     
...PPP..P.....     ........LL....L..........  ........LL.LL.........        
....PP.P.......     .........................    ................           
....P.PP.......       .........................    ...........              
..............                                                              
]]);
-- yeah, it's the slightly modified knight quest

-- Stairs
des.stair("up", 03,08)

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))

-- Objects
des.object({ id = "red lightsaber", x=60, y=06, buc="blessed", spe=0, name="The Lightsaber Prototype" })
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
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()

-- Random traps
des.trap("spiked pit",13,07)
des.trap("spiked pit",12,08)
des.trap("spiked pit",12,09)
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()

-- Random monsters.
des.monster({ id = "Lord Sidious", x=60, y=06, peaceful = 0 })
des.monster({ id = "jedi trainer", peaceful = 1 })
des.monster({ id = "jedi trainer", peaceful = 1 })
des.monster({ id = "jedi trainer", peaceful = 1 })
des.monster({ id = "jedi trainer", peaceful = 1 })
des.monster({ id = "padawan", peaceful = 1 })
des.monster({ id = "padawan", peaceful = 1 })
des.monster({ id = "padawan", peaceful = 1 })
des.monster({ id = "padawan", peaceful = 1 })
des.monster({ id = "jedi", peaceful = 1 })
des.monster({ id = "jedi", peaceful = 1 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
