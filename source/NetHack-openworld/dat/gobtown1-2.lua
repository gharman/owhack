-- NetHack: Open World  gobtown1-2.lua
-- NetHack 3.6 goblintown.des $NHDT-Date: 1649428422 2022/04/08 14:33:42 $  $NHDT-Branch: master $:$NHDT-Revision: 1.9 $
--	Copyright (c) 2022 by Keith Simpson
-- Converted from EvilHack goblintown.des (level "goblintown-1-2") for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.
--
--	Goblin Town - the player must defeat the Goblin King
--	to open up access to Mine Town and Mines' End in the
--	Gnomish Mines.
--
des.level_init({ style = "solidfill", fg = " " });

-- As in EvilHack, the floor is hard but the trap doors of Goblin Town
-- still work (see Can_fall_thru()): they are the only way down to
-- Gollum's Cave.
des.level_flags("mazelevel", "noteleport", "hardfloor", "solidify",
                "shortsighted")

-- EvilHack dead trees ('t') are ordinary trees ('T') here.
des.map({ halign = "left", valign = "center", map = [[
  ..T                                     ..T.               ...............
 ....                                  ........BBBBBBBBBBBBB..   ..    ....T
......               BBBBBBBBBBBBBBBBB..  FF.F             ..          ....T
..........BBBBBBBBBBBBB               .    ..             ..            T...
 TT..    ..                           .     ..           ..              ...
  ..      .T                         -+-                 .                ..
          .                         .....                .
         ..                      ...........            ...T.
          .-------              .\............         .......
         ..|.....|               ............            ...T..    ..
         ..|.....|                 .......            ........    ...
      .....+.....|                   -+-             ..  ......  FF.F
     ..  ..-------                    .                 TT....  ......
    ..    ...                         .                  ..........
   ..                                ..                   ..
   .                           ..T   .                     .         TT.
  ..T             BBBBBBBBBBBB........BBBBBB               .        ......
 .....BBBBBBBBBBBBBB            F.F      BBBBBBBBBBBBBBBBBB..       ...T...
.......                        ....                         ................
 TT.T                                                              .TT....

]] });

des.region(selection.area(00,00,75,19), "unlit")
des.region(selection.area(31,18,34,18), "lit")
des.region(selection.area(43,03,44,04), "lit")
des.region(selection.area(66,09,68,10), "lit")
des.region(selection.area(32,06,45,10), "lit")

-- random trap door that leads to Gollum's Cave
local gollum_cave = { {45,04},{31,18},{68,09},{12,13},{02,05} }
shuffle(gollum_cave)

-- random other traps
local traps = { {69,00},{64,18},{58,09},{38,03},
                {37,15},{35,08},{07,11},{03,02},
                {03,17},{39,07} }
shuffle(traps)

-- Make the arrival, exit, and paths somewhat unpredictable
if percent(50) then
   des.teleport_region({ region = {75,18,75,18} })
   des.levregion({ region = {02,00,02,00}, type = "branch" })
   des.terrain(selection.line(10,03, 22,03), " ")
   des.terrain(selection.line(21,02, 37,02), " ")
   des.terrain(selection.line(06,17, 19,17), "B")
   des.terrain(selection.line(18,16, 29,16), "B")
   des.terrain(selection.line(38,16, 43,16), " ")
   des.terrain(selection.line(41,17, 58,17), " ")
   des.terrain(selection.line(47,01, 59,01), "B")
else
   des.teleport_region({ region = {75,05,75,05} })
   des.levregion({ region = {00,18,00,18}, type = "branch" })
   des.terrain(selection.line(10,03, 22,03), "B")
   des.terrain(selection.line(21,02, 37,02), "B")
   des.terrain(selection.line(06,17, 19,17), " ")
   des.terrain(selection.line(18,16, 29,16), " ")
   des.terrain(selection.line(38,16, 43,16), "B")
   des.terrain(selection.line(41,17, 58,17), "B")
   des.terrain(selection.line(47,01, 59,01), " ")
end

-- Shop (maybe?)
if percent(50) then
   if percent(50) then
      des.region({ region = {12,09,16,11}, lit = 1, type = "armor shop", filled = 1 })
   else
      des.region({ region = {12,09,16,11}, lit = 1, type = "weapon shop", filled = 1 })
   end
end

-- Door to jail cells?
if percent(35) then
   des.terrain(67,11, "F")
else
   des.door("locked",67,11)
end
if percent(50) then
   des.terrain(44,02, "F")
else
   des.door("locked",44,02)
end
if percent(50) then
   des.terrain(33,17, "F")
else
   des.door("locked",33,17)
end

-- Forge: EvilHack's forge at (59,11) is dropped (5.0 has no forges).

-- Magic chest: 5.0 has no magic chests; an ordinary chest stands in for it.
des.object({ id = "chest", x = 32, y = 08 })

-- Various objects
des.object({ id = "chest", x = 67, y = 09, trapped = 0,
             contents = function()
                des.object({ id = "novel", buc = "uncursed",
                             name = "The Blacksmith's Cookbook" })
                -- EvilHack's blacksmith hammer
                des.object("war hammer")
                if percent(50) then
                   des.object({ id = "acid", class = "!", buc = "uncursed" })
                end
             end
})

-- Doors
des.door("locked",11,11)
des.door("locked",38,05)
des.door("locked",38,11)

-- Traps - eight out of ten possible locales
des.trap("board", traps[1][1], traps[1][2])
des.trap("board", traps[2][1], traps[2][2])
des.trap("board", traps[3][1], traps[3][2])
des.trap("arrow", traps[4][1], traps[4][2])
des.trap("arrow", traps[5][1], traps[5][2])
-- EvilHack's crossbow bolt traps are arrow traps here
des.trap("arrow", traps[6][1], traps[6][2])
des.trap("arrow", traps[7][1], traps[7][2])
des.trap("bear", traps[8][1], traps[8][2])

des.trap("trap door", gollum_cave[1][1], gollum_cave[1][2])

-- Prisoners
-- (EvilHack's rock gnome, gnome noble and mountain dwarf are the vanilla
-- gnome, gnome lord and dwarf.)
des.monster({ id = "Woodland-elf", x = 66, y = 10, peaceful = 1 })
des.monster({ id = "gnome", x = 68, y = 10, peaceful = 1 })
des.monster({ id = "Woodland-elf", x = 43, y = 03, peaceful = 1 })
des.monster({ id = "dwarf", x = 67, y = 10, peaceful = 1 })
des.monster({ id = "Green-elf", x = 44, y = 03, peaceful = 1 })
des.monster({ id = "gnome lord", x = 44, y = 04, peaceful = 1 })
des.monster({ id = "gnome", x = 31, y = 18, peaceful = 1 })
des.monster({ id = "Grey-elf", x = 32, y = 18, peaceful = 1 })
des.monster({ id = "gnome", x = 34, y = 18, peaceful = 1 })

-- Residents of Goblin Town
des.monster({ id = "goblin", x = 72, y = 01, peaceful = 0 })
des.monster({ id = "goblin", x = 66, y = 00, peaceful = 0 })
des.monster({ id = "goblin", x = 70, y = 17, peaceful = 0 })
des.monster({ id = "goblin", x = 66, y = 18, peaceful = 0 })
des.monster({ id = "goblin", x = 38, y = 06, peaceful = 0 })
des.monster({ id = "goblin", x = 38, y = 10, peaceful = 0 })
des.monster({ id = "goblin", x = 04, y = 01, peaceful = 0 })
des.monster({ id = "goblin", x = 03, y = 03, peaceful = 0 })
des.monster({ id = "goblin", x = 05, y = 17, peaceful = 0 })
des.monster({ id = "goblin", x = 03, y = 19, peaceful = 0 })
des.monster({ id = "goblin", x = 09, y = 07, peaceful = 0 })
des.monster({ id = "goblin", x = 10, y = 12, peaceful = 0 })
des.monster({ id = "goblin", x = 38, y = 02, peaceful = 0 })
des.monster({ id = "goblin", x = 38, y = 13, peaceful = 0 })
-- EvilHack's goblin shaman
des.monster({ id = "orc shaman", x = 42, y = 08, peaceful = 0 })
des.monster({ id = "hobgoblin", x = 53, y = 11, peaceful = 0 })
des.monster({ id = "hobgoblin", x = 61, y = 09, peaceful = 0 })
des.monster({ id = "hobgoblin", x = 45, y = 00, peaceful = 0 })
des.monster({ id = "hobgoblin", x = 31, y = 15, peaceful = 0 })
des.monster({ id = "bugbear", x = 69, y = 12, peaceful = 0 })

-- The Goblin King and his treasure
des.monster({ id = "Goblin King", x = 33, y = 08, peaceful = 0 })

des.object({ id = "chest", x = 33, y = 07,
             contents = function()
                if percent(10) then
                   des.object({ id = "magic marker", buc = "uncursed" })
                end
                des.object("*")
                des.object("*")
                des.object("*")
                des.object("=")
                des.object({ id = "gold piece", quantity = 100 })
             end
})

-- None shall pass
des.non_diggable(selection.area(00,00,31,19))
des.non_diggable(selection.area(32,00,41,16))
des.non_diggable(selection.area(42,00,75,01))
des.non_diggable(selection.area(46,00,75,10))
des.non_diggable(selection.area(35,03,64,19))
des.non_diggable(selection.area(35,12,75,19))
des.non_diggable(selection.area(69,00,75,19))
des.non_passwall(selection.area(00,00,75,19))
