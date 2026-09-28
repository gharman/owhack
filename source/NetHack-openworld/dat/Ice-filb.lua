-- NetHack Ice Mage Ice-filb.lua
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
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel")

des.level_init({ style="mines", fg=".", bg=" ", smoothed=true, joined=true, lit=1, walled=false })

--
des.stair("up")
des.stair("down")
--
for i = 1, 5 do
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
des.monster({ id = "red naga", peaceful = 0 })
des.monster({ id = "red naga", peaceful = 0 })
des.monster({ id = "hell hound", peaceful = 0 })
des.monster({ id = "hell hound", peaceful = 0 })
des.monster({ class = "&", peaceful = 0 })
des.monster({ class = "&", peaceful = 0 })
des.monster({ id = "demon orc", peaceful = 0 })
des.monster({ id = "demon orc", peaceful = 0 })
des.monster({ id = "demon orc", peaceful = 0 })
--
for i = 1, 5 do
   des.trap("falling rock")
end
des.trap()
des.trap()
