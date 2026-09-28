-- NetHack Cartographer Car-filb.lua
--	Copyright (c) 2026 by the NetHack: Open World contributors
-- NetHack may be freely redistributed.  See license for details.
--
--	The second filler level for the Cartographer quest: the Shifting
--	Ways, the outskirts of the Labyrinth, where roads that once went
--	somewhere have been folded into a maze.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noflip");

des.level_init({ style = "maze", corrwid = math.random(1, 2), wallthick = 1,
                 deadends = percent(50) });

--
des.stair("up")
des.stair("down")
--
for i = 1, 12 do
   des.object()
end
des.object("boulder")
des.object("boulder")
--
for i = 1, 8 do
   des.trap()
end
--
des.monster({ id = "umber hulk", peaceful = 0 })
des.monster({ id = "umber hulk", peaceful = 0 })
des.monster({ id = "umber hulk", peaceful = 0 })
for i = 1, 6 do
   des.monster({ class = "q", peaceful = 0 })
end
des.monster({ peaceful = 0 })
des.monster({ peaceful = 0 })
