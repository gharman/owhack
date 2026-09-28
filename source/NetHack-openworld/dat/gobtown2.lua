-- NetHack: Open World  gobtown2.lua
-- NetHack 3.6 goblintown.des $NHDT-Date: 1649428422 2022/04/08 14:33:42 $  $NHDT-Branch: master $:$NHDT-Revision: 1.9 $
--	Copyright (c) 2022 by Keith Simpson
-- Converted from EvilHack goblintown.des (level "goblintown-2") for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.
--
--	Goblin Town - the player must defeat the Goblin King
--	to open up access to Mine Town and Mines' End in the
--	Gnomish Mines.
--	This is Gollum's Cave, below Goblin Town.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "hardfloor", "solidify")

-- EvilHack terrain that 5.0 lacks: dead trees ('t') are trees ('T') and
-- puddles ('w') are floor ('.') here.
des.map({ halign = "left", valign = "center", map = [[
}}.......}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
.........}}}}}}}}}}..}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
..T...}}...}}}}}}}....}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
.....}}}}}...}}}}}}...}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
.....}}}}}}..}}}}}}....}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
......}}}}}}..}}}}...}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
.......}}}}}}}.....}}}}}}}}}}}}}}}}}}}}}.}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
........}}}}}}}.}}}}}}}}}}}}}}}}}}}}}}}...}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
.......}}}}}}}}}.}}}}}}}}}}}}}}}}}}}}}..T...}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
.T.....}}}}}}}}}}.}}}}}}}}}}}}}}}}}...........}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
.T......}}}}}}}}}.}}}}}}}}}}}}}}}}........T..}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
.......}}}}}}}}}}...}}}}}}}}}}}}}}}}........}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
....}}}}}}}}}}}...}}}}}}}}}}}}}}}}}}}.....}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
...}}}}}}}}}}}}}....}}}}}}}}}}}}}}}}}}...}}}}}}}}}}}}}}}}}}}}}}...}}}}}}}}}}
....}}}}}}}}}}}}}..}}}}}}}}}}}}}}}}}}}.T...}}}}}}}}}}}}}}}}}}...T..}}}}}}}}}
.....}}}}}}}}}}}}...}}}}}}}}}}}}}}}}}}}....}}}}}}}}}}}}}}}}}}}....}}}}}}}}}}
.......}}}}}}}}}}}....}}}}}}}}}}}}}}}}}}..}}}}}}}}}}}}}}}}}}}}}...}}}}}}}}}}
........}}}}}}}}}}}}....}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}..}}}}}}}}}}
..TT....}}}}}}}}}}}.}}}..}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
...T.....}}}}}}}}}......}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
...................}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
]] });

des.teleport_region({ region = {00,05,07,10} })
des.stair("up", 02,19)
des.region(selection.area(00,00,75,20), "unlit")

-- random spots Gollum can spawn
local gollum_spawn = { {20,02},{01,13},{16,12},{34,10},{04,18},{02,01} }
shuffle(gollum_spawn)

-- Make the path to the center island a bit unpredictable
-- (the source lays down puddles, which are floor here)
if percent(50) then
   des.terrain(selection.line(25,18, 28,18), ".")
   des.terrain(selection.line(28,17, 31,17), ".")
   des.terrain(selection.line(31,18, 33,18), ".")
   des.terrain(selection.line(34,19, 36,19), ".")
   des.terrain(selection.line(36,18, 39,18), ".")
   des.terrain(selection.line(39,17, 40,17), ".")
else
   des.terrain(selection.line(23,04, 29,04), ".")
   des.terrain(selection.line(29,03, 31,03), ".")
   des.terrain(selection.line(32,02, 35,02), ".")
   des.terrain(selection.line(36,03, 37,03), ".")
   des.terrain(selection.line(37,04, 38,04), ".")
   des.terrain(selection.line(38,05, 40,05), ".")
end

-- Small chance to jump across to the far island
if percent(33) then
   des.terrain(47,09, ".")
   des.terrain(50,09, ".")
   des.terrain(52,11, ".")
   des.terrain(54,11, ".")
   des.terrain(57,11, ".")
   des.terrain(59,13, ".")
   des.terrain(61,13, ".")
end

-- various objects
-- EvilHack's "lustrous" ring (the base of The One Ring, which grants
-- invisibility) is a ring of invisibility here.
des.object({ id = "invisibility", class = "=", buc = "cursed", name = "The One Ring" })

des.object({ id = "chest", x = 40, y = 10,
             contents = function()
                -- (the source's 65% chance of uncursed goggles is dropped:
                -- 5.0 has no goggles)
                des.object("*")
                des.object("*")
                des.object("!")
             end
})

des.object({ id = "chest", x = 64, y = 15, trapped = 0, locked = 1,
             contents = function()
                if percent(35) then
                   -- EvilHack's elven chain mail
                   des.object("chain mail")
                end
                if percent(50) then
                   des.object("elven cloak")
                end
                des.object("elven dagger")
                -- EvilHack's magic key
                des.object({ id = "skeleton key", buc = "uncursed" })
                des.object("*")
                des.object("*")
                des.object("*")
                des.object({ id = "gold piece", quantity = 200 })
             end
})

-- Gollum's victims
des.object({ id = "corpse", x = 01, y = 01, montype = "goblin" })
des.object({ id = "corpse", x = 03, y = 03, montype = "hobgoblin" })
des.object({ id = "corpse", x = 02, y = 07, montype = "piranha" })
des.object({ id = "corpse", x = 06, y = 07, montype = "piranha" })
des.object({ id = "corpse", x = 05, y = 08, montype = "piranha" })
des.object({ id = "corpse", x = 02, y = 16, montype = "goblin" })
des.object({ id = "corpse", x = 37, y = 10, montype = "hobgoblin" })
des.object({ id = "corpse", x = 39, y = 12, montype = "goblin" })
des.object({ id = "corpse", x = 43, y = 09, montype = "goblin" })
des.object({ id = "corpse", x = 63, y = 13, montype = "elf" })
des.object({ id = "corpse", x = 64, y = 16, montype = "elf" })

-- Gollum
des.monster({ id = "Gollum", coord = gollum_spawn[1], peaceful = 0 })

-- random monsters
des.monster({ id = "piranha", peaceful = 0 })
des.monster({ id = "piranha", peaceful = 0 })
des.monster({ id = "piranha", peaceful = 0 })
des.monster({ id = "jellyfish", peaceful = 0 })
des.monster({ id = "jellyfish", peaceful = 0 })
des.monster({ id = "bat", peaceful = 0 })
des.monster({ id = "bat", peaceful = 0 })
des.monster({ id = "bat", peaceful = 0 })
des.monster({ id = "bat", peaceful = 0 })
des.monster({ id = "bat", peaceful = 0 })
des.monster({ id = "giant bat", peaceful = 0 })
des.monster({ id = "giant bat", peaceful = 0 })
