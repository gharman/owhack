-- NetHack: Open World  blkmar.lua
--
-- This is the black market
-- Massimo Campostrini (campo@sunthpi3.difi.unipi.it)
--
-- Converted from Slash'EM blkmar.des for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noteleport", "hardfloor")

des.map({ halign = "center", valign = "center", map = [[
---------------------------------------------------------------------------
|.|.......................................................................|
|.|.......................................................................|
|.|.......................................................................|
|.|.......................................................................|
|.|.......................................................................|
|.|.......................................................................|
|.|.......................................................................|
|.|.......................................................................|
|.|.......................................................................|
|.|.......................................................................|
|.|.......................................................................|
|.|.......................................................................|
|.|.......................................................................|
|.+.......................................................................|
|.|.......................................................................|
|.|.......................................................................|
---------------------------------------------------------------------------
]] });

des.non_diggable(selection.area(00,00,74,17))
des.non_passwall(selection.area(00,00,74,17))
-- One-eyed Sam's shop; the shopkeeper is created by the game
des.region({ region = {03,01,73,16}, lit = 1, type = "black market", filled = 1 })
-- Arrival point (the way back out of the market)
des.levregion({ region = {01,01,01,01}, type = "branch" })
des.door("open", 02, 14)
des.engraving({ x = 01, y = 03, type = "engrave", text = "Pets are not allowed in the shop" })
des.engraving({ x = 01, y = 05, type = "engrave", text = "Thieves will be killed." })
des.engraving({ x = 01, y = 07, type = "engrave", text = "Sorry about the mess. Remember, ask if you need help!" })
des.engraving({ x = 01, y = 09, type = "engrave", text = "Don't even think about stealing anything." })
-- black marketeer's assistants:
-- from The Hobbit (Tolkien)
des.monster({ id = "rock troll", x = 03, y = 03, name = "William", female = false, asleep = 1, peaceful = 1 })
des.monster({ id = "rock troll", x = 03, y = 12, name = "Thomas", female = false, asleep = 1, peaceful = 1 })
-- from the Bible
des.monster({ id = "frost giant", x = 03, y = 16, name = "Goliath", female = false, asleep = 1, peaceful = 1 })
-- from Greek mythology & high-energy physics
des.monster({ id = "wood nymph", x = 03, y = 09, name = "Daphne", asleep = 1, peaceful = 1 })
-- Add your favorite monsters here.  Make them peaceful and named,
-- otherwise they will not behave like assistants.
des.monster({ id = "balrog", x = 03, y = 04, name = "Njalnohaar", asleep = 1, peaceful = 1 })
des.monster({ id = "pit fiend", x = 03, y = 02, name = "Hilvuuloth", asleep = 1, peaceful = 1 })
des.monster({ id = "cockatrice", x = 03, y = 13, name = "Wilbur", female = false, asleep = 1, peaceful = 1 })
des.monster({ id = "cockatrice", x = 03, y = 08, name = "Simon", female = false, asleep = 1, peaceful = 1 })
des.monster({ id = "rhaumbusun", x = 03, y = 11, name = "Izzy", asleep = 1, peaceful = 1 })
