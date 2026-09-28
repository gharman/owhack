-- NetHack Jedi Jed-loca.lua
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991,92 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
--
--	The "locate" level for the quest.
--
des.level_init({ style = "solidfill", fg = "." });

des.level_flags("mazelevel", "hardfloor")

des.level_init({ style="mines", fg=".", bg=".", smoothed=false, joined=false, lit=0, walled=false })

--         1         2         3         4         5         6         7
--123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
................L...........................................................
...............LLL..........................................................
..............LLLLL...................  ....................................
.............LLLLLLL..................  ....................................
............LLLLLLLLL.............................................. ........
.............LLLLLLL..............................................   .......
..............LLLLL..............................................     ......
...............LLL..............................................   .........
................L.............................. ...............    .    ....
...............................................  .............     .     ...
..............................................     ............    .    ....
...............................................  ...............       .....
.............P.................................. ................     ......
............PPP.....................P.............................   .......
...........PPPPP...................PPP............................. ........
............PPP...................PPPPP.....................................
.............P...................PPPPPPP....................................
..................................PPPPP.....................................
...................................PPP......................................
....................................P.......................................
............................................................................
]]);

-- supposed to designate a sun, two water planets, two asteroids and
-- a barren planet made mostly of rock. Yeah, bite me!
-- Stairs
des.stair("up", 00,00)
des.stair("down", 67,10)

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
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()

-- Random monsters.
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
