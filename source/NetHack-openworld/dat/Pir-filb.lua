-- NetHack Pirate Pir-filb.lua
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
--	Ported from SpliceHack's Pir-filb.lua (SlashTHEM's Pirate.des):
--	a dark cave of tunnels.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noteleport")

-- (SlashTHEM uses a walled cave of floor here; SpliceHack's version,
-- kept here, is a cave of bare tunnels.)
des.level_init({ style="mines", fg="#", bg=" ", smoothed=true, joined=true, lit=0, walled=false })

--
des.stair("up")
des.stair("down")
--
for i = 1, 7 do
   des.object()
   des.trap()
end

des.monster({ id = "ghost", peaceful = 0 })
des.monster({ id = "ghost", peaceful = 0 })
des.monster({ id = "ghost", peaceful = 0 })

des.monster({ id = "sergeant", peaceful = 0 })

des.monster({ id = "damned pirate", peaceful = 0 })
for i = 1, 11 do
   des.monster({ id = "skeletal pirate", peaceful = 0 })
end
