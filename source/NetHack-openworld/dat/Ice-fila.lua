-- NetHack Ice Mage Ice-fila.lua
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991-2 by M. Stephenson
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
des.level_init({ style = "solidfill", fg = "I" });

des.level_flags("mazelevel")

des.level_init({ style="mines", fg=".", bg="I", smoothed=true, joined=true, lit=1, walled=false })

--
des.stair("up")
des.stair("down")
--
for i = 1, 6 do
   des.object()
end
--
for i = 1, 4 do
   des.monster({ id = "fire elemental", peaceful = 0 })
end
des.monster({ id = "magma elemental", peaceful = 0 })
des.monster({ id = "steam vortex", peaceful = 0 })
des.monster({ id = "steam vortex", peaceful = 0 })
des.monster({ id = "fire vortex", peaceful = 0 })
des.monster({ id = "fire vortex", peaceful = 0 })
des.monster({ id = "hell hound", peaceful = 0 })
des.monster({ id = "hell hound", peaceful = 0 })
des.monster({ id = "hell hound pup", peaceful = 0 })
des.monster({ id = "hell hound pup", peaceful = 0 })
des.monster({ id = "fire giant", peaceful = 0 })
des.monster({ id = "fire giant", peaceful = 0 })
--
for i = 1, 7 do
   des.trap()
end
