-- NetHack Pirate Pir-fila.lua
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991-2 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
--	The "fill" levels for the quest.
--
--	These levels are used to fill out any levels not occupied by specific
--	levels as defined above. "filla" is the upper filler, between the
--	start and locate levels, and "fillb" the lower between the locate
--	and goal levels.
--
--	Ported from SpliceHack's Pir-fila.lua and SlashTHEM's Pirate.des:
--	islets in the open sea.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noteleport", "shortsighted")

des.level_init({ style="mines", fg=".", bg="}", smoothed=false, joined=false, lit=1, walled=false })

-- The way on is somewhere east of the landing.
des.levregion({ region = {20,00,75,20}, exclude = {00,00,20,20}, type="stair-down" })

des.monster({ id = "ghost", peaceful = 0 })
des.monster({ id = "skeletal pirate", peaceful = 0 })
des.monster({ id = "skeletal pirate", peaceful = 0 })
des.monster({ id = "skeletal pirate", peaceful = 0 })
des.monster({ id = "skeletal pirate", peaceful = 0 })

des.monster({ id = "soldier", peaceful = 0 })
des.monster({ id = "soldier", peaceful = 0 })
des.monster({ id = "soldier", peaceful = 0 })

des.monster({ id = "parrot", peaceful = 0 })
des.monster({ id = "parrot", peaceful = 0 })
des.monster({ id = "parrot", peaceful = 0 })
des.monster({ id = "parrot", peaceful = 0 })

des.monster({ id = "monkey", peaceful = 0 })
des.monster({ id = "monkey", peaceful = 0 })

des.region(selection.area(00,00,75,20), "lit")
-- The landing, with the way back up
des.map({ halign = "left", valign = "bottom", map = [[
}.}}
....
}.}.
]] });
des.stair("up", 01,01)
des.region(selection.area(00,00,03,02), "lit")
