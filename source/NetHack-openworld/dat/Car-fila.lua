-- NetHack Cartographer Car-fila.lua
--	Copyright (c) 2026 by the NetHack: Open World contributors
-- NetHack may be freely redistributed.  See license for details.
--
--	The first filler level for the Cartographer quest: the uncharted
--	country between the Hall of Charts and the Edge of the Map, open
--	woodland and meadows with the odd lake.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noflip");

des.level_init({ style="mines", fg=".", bg="T", smoothed=true, joined=true,
                 lit=1, walled=false })

-- a few meres and ponds among the trees
des.replace_terrain({ region={01,01,78,19}, fromterrain="T", toterrain="}",
                      chance=12 })
--
des.stair("up")
des.stair("down")
--
for i = 1, 8 do
   des.object()
end
--
for i = 1, 5 do
   des.trap()
end
--
des.monster({ id = "umber hulk", peaceful = 0 })
des.monster({ class = "q", peaceful = 0 })
des.monster({ class = "q", peaceful = 0 })
des.monster({ class = "q", peaceful = 0 })
des.monster({ class = "q", peaceful = 0 })
des.monster({ peaceful = 0 })
des.monster({ peaceful = 0 })
