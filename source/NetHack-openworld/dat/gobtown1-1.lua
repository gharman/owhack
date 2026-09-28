-- NetHack: Open World  gobtown1-1.lua
-- NetHack 3.6 goblintown.des $NHDT-Date: 1649428422 2022/04/08 14:33:42 $  $NHDT-Branch: master $:$NHDT-Revision: 1.9 $
--	Copyright (c) 2022 by Keith Simpson
-- Converted from EvilHack goblintown.des (level "goblintown-1-1") for NetHack 5.0.
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
..... ..                                                         .----------
....T..                                                         ..|........|
......       -------            .TT..   ...                     T.|........|
.T...        |.....|    .............. F..                     ...|..|...\.|
 ....        |.....|.....     ..  .....FF.                      .....|.....|
    ..       |.....+.        ..     .......         ...          ....----S--
     ..      -------        ..        .T....       ..T..        ...T   ...  
      ..                   ..             ................     ..       .   
       ..                 ..                         ... ..   ..        .   
      ....             ....                           .   .....         .   
     .........       ..T....                          .                ..   
     ......................TT                         .             .. .    
      .T..           .......                         ...           F....    
       ..             .......                      ..T...    ..........
                       ...........                ........  ..     F..
                     ........    ..       ............TT.....               
                      FFFF.F      ..........        ......T..               
                      ......                                                
                       ...                                                  
                                                                            
                                                                            
]] });

des.teleport_region({ region = {00,00,04,03} })
des.levregion({ region = {01,01,01,01}, type = "branch" })
des.region(selection.area(00,00,75,19), "unlit")
des.region(selection.area(22,17,27,18), "lit")
des.region(selection.area(40,02,42,03), "lit")
des.region(selection.area(68,11,69,14), "lit")
des.region(selection.area(71,01,74,04), "lit")

-- random trap door that leads to Gollum's Cave
local gollum_cave = { {25,18},{42,02},{70,13},{07,00},{64,01} }
shuffle(gollum_cave)

-- random other traps
local traps = { {06,06},{07,08},{19,11},{61,09},
                {62,13},{72,08},{38,16},{46,15},
                {49,07},{29,06} }
shuffle(traps)

-- Shop (maybe?)
if percent(50) then
   if percent(50) then
      des.region({ region = {14,03,18,05}, lit = 1, type = "shop", filled = 1 })
   else
      des.region({ region = {14,03,18,05}, lit = 1, type = "armor shop", filled = 1 })
   end
end

-- Door to jail cells?
if percent(35) then
   des.terrain(26,16, "F")
else
   des.door("locked",26,16)
end
if percent(50) then
   des.terrain(41,04, "F")
else
   des.door("locked",41,04)
end
if percent(50) then
   des.terrain(67,13, "F")
else
   des.door("locked",67,13)
end

-- Forge: EvilHack's forge at (24,12) is dropped (5.0 has no forges).

-- Magic chest: 5.0 has no magic chests; an ordinary chest stands in for it.
des.object({ id = "chest", x = 74, y = 03 })

-- Various objects
des.object({ id = "chest", x = 23, y = 18, trapped = 0,
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
des.object("boulder",28,03)
des.object("boulder",71,11)

-- Doors
des.door("locked",19,05)
des.door("locked",73,05)

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
des.monster({ id = "Woodland-elf", x = 23, y = 17, peaceful = 1 })
des.monster({ id = "gnome", x = 24, y = 18, peaceful = 1 })
des.monster({ id = "Woodland-elf", x = 25, y = 17, peaceful = 1 })
des.monster({ id = "dwarf", x = 27, y = 17, peaceful = 1 })
des.monster({ id = "Green-elf", x = 40, y = 03, peaceful = 1 })
des.monster({ id = "gnome lord", x = 41, y = 02, peaceful = 1 })
des.monster({ id = "gnome", x = 42, y = 02, peaceful = 1 })
des.monster({ id = "Grey-elf", x = 69, y = 12, peaceful = 1 })
des.monster({ id = "gnome", x = 68, y = 14, peaceful = 1 })
des.monster({ id = "gnome", x = 69, y = 14, peaceful = 1 })

-- Residents of Goblin Town
des.monster({ id = "goblin", x = 07, y = 11, peaceful = 0 })
des.monster({ id = "goblin", x = 08, y = 12, peaceful = 0 })
des.monster({ id = "goblin", x = 24, y = 13, peaceful = 0 })
des.monster({ id = "goblin", x = 25, y = 10, peaceful = 0 })
des.monster({ id = "goblin", x = 27, y = 12, peaceful = 0 })
des.monster({ id = "goblin", x = 35, y = 03, peaceful = 0 })
des.monster({ id = "goblin", x = 36, y = 04, peaceful = 0 })
des.monster({ id = "goblin", x = 42, y = 05, peaceful = 0 })
des.monster({ id = "goblin", x = 52, y = 06, peaceful = 0 })
des.monster({ id = "goblin", x = 52, y = 13, peaceful = 0 })
des.monster({ id = "goblin", x = 54, y = 05, peaceful = 0 })
des.monster({ id = "goblin", x = 54, y = 14, peaceful = 0 })
des.monster({ id = "goblin", x = 56, y = 15, peaceful = 0 })
des.monster({ id = "goblin", x = 67, y = 05, peaceful = 0 })
-- EvilHack's goblin shaman
des.monster({ id = "orc shaman", x = 64, y = 03, peaceful = 0 })
des.monster({ id = "hobgoblin", x = 26, y = 12, peaceful = 0 })
des.monster({ id = "hobgoblin", x = 38, y = 06, peaceful = 0 })
des.monster({ id = "hobgoblin", x = 55, y = 16, peaceful = 0 })
des.monster({ id = "hobgoblin", x = 65, y = 05, peaceful = 0 })
des.monster({ id = "bugbear", x = 64, y = 13, peaceful = 0 })

-- The Goblin King and his treasure
des.monster({ id = "Goblin King", x = 73, y = 03, peaceful = 0 })

des.object({ id = "chest", x = 70, y = 04,
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
des.non_diggable(selection.area(00,00,38,15))
des.non_diggable(selection.area(00,00,21,19))
des.non_diggable(selection.area(00,00,75,02))
des.non_diggable(selection.area(42,00,75,11))
des.non_diggable(selection.area(28,05,66,19))
des.non_diggable(selection.area(00,17,75,19))
des.non_diggable(selection.area(68,00,75,19))
des.non_passwall(selection.area(00,00,75,19))
