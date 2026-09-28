-- NetHack: Open World  mtemple.lua
--       SCCS Id: @(#)mtemple.des  3.4     1993/02/23
--       Copyright (c) 1989 by Jean-Christophe Collet
--       Copyright (c) 1991 by M. Stephenson
-- Converted from Slash'EM mtemple.des for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.
--
-- This is the Temple of Moloch.
-- Within lie priests, demons, and, most importantly.... candles!
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel")

des.map({ halign = "center", valign = "center", map = [[
            ----- ----- ----- ----- -----               
            |...| |...| |...| |...| |...|               
   ----------...---...---...---...---...|-|        -----
   |...|..................................|        |...|
   |...+..................................S########S...|
   |...|..................................|        |...|
   ----------...---...---...---...---...|-|        -----
            |...| |...| |...| |...| |...|               
            ----- ----- ----- ----- -----               
]] });

des.region(selection.area(00,00,55,08), "unlit")
-- des.region({ region = {39,03,41,05}, lit = 0, type = "temple", filled = 1 })
des.region({ region = {08,01,41,07}, lit = 0, type = "temple", filled = 1 })
-- Arrival point (Slash'EM also put the up stairs here; the branch is the
-- way back out)
des.levregion({ region = {05,04,05,04}, type = "branch" })
des.door("locked", 07, 04)
-- the altar of Moloch (making four will make four priests....)
des.altar({ x = 40, y = 04, align = "noalign", type = "shrine" })
des.altar({ x = 40, y = 04, align = "noalign", type = "shrine" })
des.altar({ x = 40, y = 04, align = "noalign", type = "shrine" })
des.altar({ x = 40, y = 04, align = "noalign", type = "shrine" })
-- flanking the doorway....
des.trap("spiked pit", 06, 03)
des.trap("spiked pit", 06, 05)
-- the treasure chamber!
for y = 03, 05 do
   for x = 52, 54 do
      des.object("chest", x, y)
      des.object("wax candle", x, y)
      des.gold({ x = x, y = y })
      des.gold({ x = x, y = y })
      des.object({ x = x, y = y })
      des.object({ x = x, y = y })
      des.object({ x = x, y = y })
   end
end
-- five gargoyles on either side, in the niches of the temple
des.monster({ id = "statue gargoyle", x = 14, y = 01, peaceful = 0, asleep = 1 })
des.monster({ id = "statue gargoyle", x = 20, y = 01, peaceful = 0, asleep = 1 })
des.monster({ id = "statue gargoyle", x = 26, y = 01, peaceful = 0, asleep = 1 })
des.monster({ id = "statue gargoyle", x = 32, y = 01, peaceful = 0, asleep = 1 })
des.monster({ id = "statue gargoyle", x = 38, y = 01, peaceful = 0, asleep = 1 })
des.monster({ id = "statue gargoyle", x = 14, y = 07, peaceful = 0, asleep = 1 })
des.monster({ id = "statue gargoyle", x = 20, y = 07, peaceful = 0, asleep = 1 })
des.monster({ id = "statue gargoyle", x = 26, y = 07, peaceful = 0, asleep = 1 })
des.monster({ id = "statue gargoyle", x = 32, y = 07, peaceful = 0, asleep = 1 })
des.monster({ id = "statue gargoyle", x = 38, y = 07, peaceful = 0, asleep = 1 })
-- demons down by the altar...
des.monster({ id = "bone devil", x = 37, y = 02, peaceful = 0, asleep = 1 })
des.monster({ id = "babau", x = 38, y = 02, peaceful = 0, asleep = 1 })
des.monster({ id = "barbed devil", x = 39, y = 02, peaceful = 0, asleep = 1 })
des.monster({ id = "vrock", x = 37, y = 06, peaceful = 0, asleep = 1 })
des.monster({ id = "horned devil", x = 38, y = 06, peaceful = 0, asleep = 1 })
des.monster({ id = "hezrou", x = 39, y = 06, peaceful = 0, asleep = 1 })
-- a horde of zombies is also inside....
for y = 03, 05 do
   for x = 17, 23 do
      des.monster({ class = "Z", x = x, y = y, peaceful = 0, asleep = 1 })
   end
end
des.engraving({ x = 06, y = 04, type = "burn", text = "Those Not of Moloch, Begone!" })
