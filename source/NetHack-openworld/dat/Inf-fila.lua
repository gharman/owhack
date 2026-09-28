-- NetHack Infidel Inf-fila.lua
--	Infidel role by Tomsod, for EvilHack.
--	Ported from EvilHack's Infidel.des (cross-checked with Hack'EM's).
-- NetHack may be freely redistributed.  See license for details.
--
--
--	The "fill" levels for the quest.
--
--	These levels are used to fill out any levels not occupied by specific
--	levels as defined above. "fila" is the upper filler, between the
--	start and locate levels, and "filb" the lower between the locate
--	and goal levels.
--
--	The upper filler is the underground complex that leads to the Forest.
--	It's a standard room-and-corridor dungeon populated with hkO.
--
des.level_flags("hardfloor")

des.room({ type = "ordinary",
           contents = function()
              des.stair("up")
              des.object()
              des.monster("k")
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.stair("down")
              des.object()
              des.trap()
              des.monster("h")
              des.monster("k")
           end
})

-- Quest dungeons always seem so empty, so here's a fountain.
des.room({ type = "ordinary",
           contents = function()
              des.feature("fountain")
              des.object()
              des.monster("h")
           end
})

-- Throne monsters roughly suit the hkO theme.
des.room({ type = "throne", chance = 25,
           contents = function()
              des.object()
              des.trap()
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.trap()
              des.monster("k")
              des.monster("k")
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.object()
              des.trap()
              des.trap()
              des.monster("O")
              des.monster("h")
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.object()
              des.trap()
              des.trap()
              des.monster("O")
              des.monster("k")
           end
})

des.random_corridors()
