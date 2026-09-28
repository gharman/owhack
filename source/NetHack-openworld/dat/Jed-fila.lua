-- NetHack Jedi Jed-fila.lua
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991,92 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
--
--	The "fill" levels for the quest.
--
--	These levels are used to fill out any levels not occupied by specific
--	levels as defined above. "filla" is the upper filler, between the
--	start and locate levels, and "fillb" the lower between the locate
--	and goal levels.
--
des.level_init({ style = "solidfill", fg = "." });

des.level_flags("mazelevel")

des.level_init({ style="mines", fg=".", bg=".", smoothed=false, joined=true, lit=0, walled=false })

--
des.stair("up")
des.stair("down")
--
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
--
des.monster({ id = "jedi trainer", peaceful = 1 })
des.monster({ id = "jedi trainer", peaceful = 1 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
des.monster({ id = "stormtrooper", peaceful = 0 })
--
des.trap()
des.trap()
des.trap()
des.trap()
