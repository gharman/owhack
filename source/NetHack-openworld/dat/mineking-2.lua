-- NetHack: Open World  mineking-2.lua
-- NetHack 3.6	mines.des	$NHDT-Date: 1548631704 2019/01/27 23:28:24 $  $NHDT-Branch: NetHack-3.6.2-beta01 $:$NHDT-Revision: 1.30 $
--	Copyright (c) 1989-95 by Jean-Christophe Collet
--	Copyright (c) 1991-95 by M. Stephenson
-- Converted from Hack'EM mines.des (level "mineking-2") for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.
--
--    Ruggo the Gnome King's own special level
--    Deluxe version from the Mines2 patch.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel")

-- Hack'EM puddles ('w') are floor ('.') here.
des.map({ halign = "center", valign = "center", map = [[
-------------------------------------------------------------------------
|............+....||.....|..+......+...........+.......}|...............|
|............|--.---.---.|..|-+--+-|...........|......}}--..--------....|
|............|........||...-|......|-----------|......}}}}}....|...|....|
|............|...|||.....|..|.....|-...........-|..............|...|....|
|-----------+|--------------------------------S--------------..--.--....|
    |.|----.....----|..........|......S.|..--|.........S....|.........-.|
 ----S-......{......----.......|......|-|....---.......|---|-.--..----|.|
 |.S........{.{........+.......+......................\S...|...-........|
 ----S-......{......----.......|......|-|....---.......|---|-.....----|.|
    |.|----.....----|..........|......|.|..--|.........S....|..-..|...--|
|----------..|-------------------------S---|....-------------..--.......|
|............|}}}}}}}}}}}.}}}}}}}}|-...........-|}}}}.............|.....|
|............|}}...}}}}}}.....}}}}}|--S--------|}}}}..}}}......}}}------|
|............|}}...}}}}}}}}}......}}}}......|}}}}}}..}}}}}.......}}.....|
|............|}}...}}}}}}}}}}}}}}......}}}}}|}}}}}}}}}}}.............}..|
--------------}}}}}}}}--------------------------------------------------|
]] });

-- (neither list is shuffled in the source)
local objects = { "*", "(", "%" }
local places = { {39,06},{39,10} }

des.region(selection.area(00,00,72,16), "lit")
des.teleport_region({ region = {1,1,71,16}, exclude = {1,1,61,16} })
des.non_diggable(selection.area(00,00,72,16))
des.stair("up", 71,08)
--des.stair("down", 68,08)

--des.levregion({ region = {35,06,35,06}, type = "branch" })

des.door("closed",47,01)
des.door("locked",35,01)
des.door("closed",28,01)
des.door("closed",30,02)
des.door("closed",33,02)
des.door("closed",13,01)
des.door("locked",12,05)
des.door("locked",23,08)
des.door("locked",31,08)
-- The secret doors
des.door("locked",46,05)
des.door("locked",05,07)
des.door("locked",05,09)
des.door("locked",03,08)
des.door("locked",38,06)
des.door("locked",39,11)
des.door("locked",55,08)
des.door("locked",55,06)
des.door("locked",55,10)
des.door("closed",38,13)

-- Checkpost guards
des.monster({ class = "G", x = 64, y = 03, peaceful = 0 })
des.monster({ class = "G", x = 64, y = 04, peaceful = 0 })
des.monster({ class = "G", x = 66, y = 03, peaceful = 0 })
des.monster({ id = "gnome warrior", x = 66, y = 04, peaceful = 0 })
des.monster({ id = "gnome warrior", x = 67, y = 10, peaceful = 0 })
des.monster({ id = "gnome warrior", x = 69, y = 10, peaceful = 0 })
des.monster({ id = "gnome warrior", x = 67, y = 12, peaceful = 0 })

-- 5 random gems all around + 1 luckstone
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("*")
des.object("luckstone")

--5 bunches of gold all around...
des.gold({ amount = d(200) })
des.gold({ amount = d(200) })
des.gold({ amount = d(200) })
des.gold({ amount = d(200) })
des.gold({ amount = d(200) })

-- Set about the fountains
-- (Hack'EM's "gnome royal" is the vanilla gnome king)
des.object({ id = "statue", x = 13, y = 08, montype = "gnome king", historic = 1 })
des.engraving({ x = 13, y = 08, type = "burn", text = "Ruggo the Magnificent" })

-- Barracks 1 (1,1)-(12,4) - 10 warriors
des.monster({ id = "gnome warrior", x = 01, y = 01, peaceful = 0 })
des.monster({ id = "gnome warrior", x = 08, y = 03, peaceful = 0 })
des.monster({ id = "gnome warrior", x = 03, y = 02, peaceful = 0 })
des.monster({ id = "gnome warrior", x = 10, y = 02, peaceful = 0 })
des.monster({ id = "gnome warrior", x = 12, y = 04, peaceful = 0 })
des.monster({ class = "G", x = 01, y = 04, peaceful = 0 })
des.monster({ class = "G", x = 10, y = 01, peaceful = 0 })
des.monster({ class = "G", x = 06, y = 03, peaceful = 0 })
des.monster({ class = "G", x = 09, y = 03, peaceful = 0 })
des.monster({ class = "G", x = 04, y = 04, peaceful = 0 })

-- Barracks 2 (1,12)-(12,15)
des.monster({ id = "gnome warrior", x = 12, y = 15, peaceful = 0 })
des.monster({ id = "gnome warrior", x = 05, y = 13, peaceful = 0 })
des.monster({ id = "gnome warrior", x = 10, y = 14, peaceful = 0 })
des.monster({ id = "gnome warrior", x = 03, y = 14, peaceful = 0 })
des.monster({ id = "gnome warrior", x = 01, y = 12, peaceful = 0 })
des.monster({ class = "G", x = 12, y = 12, peaceful = 0 })
des.monster({ class = "G", x = 03, y = 15, peaceful = 0 })
des.monster({ class = "G", x = 07, y = 13, peaceful = 0 })
des.monster({ class = "G", x = 04, y = 13, peaceful = 0 })
des.monster({ class = "G", x = 09, y = 12, peaceful = 0 })

--Chance of healthstone on the island
des.object({ id = "rock", x = 17, y = 14, spe = 0 })
des.object({ id = "rock", x = 17, y = 14, spe = 0 })
des.object({ id = "rock", x = 17, y = 14, spe = 0 })
if percent(90) then
   des.object({ id = "rock", x = 17, y = 14, spe = 0 })
end
if percent(65) then
   des.object({ id = "rock", x = 17, y = 14, spe = 0 })
end

-- Random amulet to keep folks interested
des.object('"', 17,14)

-- And some citrines
des.object("citrine", 17,14)
des.object("citrine", 17,14)
des.object("citrine", 17,14)
des.object("worthless piece of yellow glass", 17,14)
des.object("worthless piece of yellow glass", 17,14)
des.object("worthless piece of yellow glass", 17,14)
des.object("citrine", 17,14)
des.object("worthless piece of yellow glass", 17,14)

-- Couple of random wands - is this laying it on too thick?
des.object("/", 17,14)
des.object("/", 17,14)

-- The island's guardian - the friendly neighbourhood demilich
-- and up to 4 companions
des.monster({ id = "demilich", x = 17, y = 14, peaceful = 0 })
if percent(50) then
   des.monster({ id = "lich", x = 18, y = 14, peaceful = 0 })
end
if percent(50) then
   des.monster({ id = "lich", x = 16, y = 14, peaceful = 0 })
end
if percent(50) then
   des.monster({ id = "lich", x = 17, y = 15, peaceful = 0 })
end
if percent(50) then
   des.monster({ id = "lich", x = 17, y = 13, peaceful = 0 })
end

if percent(90) then
   des.monster({ id = "electric eel", x = 22, y = 14, peaceful = 0 })
end
des.monster({ id = "shark", x = 20, y = 13, peaceful = 0 })
if percent(75) then
   des.monster({ id = "giant eel", x = 48, y = 14, peaceful = 0 })
end

des.gold({ amount = d(40,200), x = 17, y = 14 })

-- (5.0 has no healthstones; the chest's healthstones are luckstones here)
des.object({ id = "chest", x = 17, y = 14,
             contents = function()
                if percent(40) then
                   des.object({ id = "full healing", class = "!", buc = "blessed", spe = 0 })
                end
                if percent(40) then
                   des.object({ id = "gain level", class = "!" })
                end
                if percent(90) then
                   des.object({ id = "luckstone", buc = "uncursed", spe = 0 })
                end
                if percent(20) then
                   des.object({ id = "luckstone", buc = "blessed", spe = 0 })
                end
                -- Aha!
                if percent(30) then
                   des.object({ id = "loadstone", buc = "uncursed", spe = 0 })
                end
                if percent(45) then
                   des.object({ id = "flint", buc = "uncursed", spe = 0 })
                end
             end
})

-- Random ring each in the throneroom hallway closets
if percent(50) then
   des.object("=", 02,08)
end
if percent(50) then
   des.object("=", 05,10)
end
if percent(50) then
   des.object("=", 05,06)
end

-- And some skeletons in the closets as well
des.monster("skeleton", 02,08)
des.monster("skeleton", 05,10)
des.monster("skeleton", 05,06)

-- Chance of "oFly in one of the throneroom closets - one
-- of the nice amulets
if percent(15) then
   des.object({ id = "amulet of flying", coord = places[1], buc = "cursed", spe = 0 })
end
if percent(50) then
   des.object({ id = "amulet of restful sleep", coord = places[2], buc = "cursed", spe = 0 })
end

-- Shall they go unguarded? Niet
des.monster({ id = "stone golem", coord = places[1], asleep = 1 })
des.monster({ id = "stone golem", coord = places[2], asleep = 1 })

-- throne room
des.monster({ id = "Ruggo the Gnome King", x = 54, y = 8, peaceful = 0 })

--Ruggo's advisers
-- (Hack'EM deep gnomes are gnome lords here)
des.monster({ id = "gnome lord", x = 54, y = 07, peaceful = 0 })
des.monster({ id = "gnome lord", x = 54, y = 09, peaceful = 0 })

-- (Historic) artwork in the hallways
des.object({ id = "statue", x = 49, y = 07, montype = "gnome king", historic = 1 })
des.object({ id = "statue", x = 51, y = 07, montype = "gnome king", historic = 1 })
des.object({ id = "statue", x = 53, y = 07, montype = "gnome king", historic = 1 })
des.object({ id = "statue", x = 49, y = 09, montype = "gnome king", historic = 1 })
des.object({ id = "statue", x = 51, y = 09, montype = "gnome king", historic = 1 })
des.object({ id = "statue", x = 53, y = 09, montype = "gnome king", historic = 1 })

des.object(")", 54,8)
des.object("/", 54,8)

-- Give Ruggo some firepower?
if percent(75) then
   des.object("/", 54,8)
end
if percent(30) then
   des.object({ id = "sleep", class = "/", x = 54, y = 8 })
end
if percent(10) then
   -- Hack'EM wand of draining; a wand of striking here
   des.object({ id = "striking", class = "/", x = 54, y = 8 })
end
if percent(5) then
   des.object({ id = "lightning", class = "/", x = 54, y = 8 })
end

-- Things can get hairy very quickly...
if percent(5) then
   -- Hack'EM wand of create horde; a wand of create monster here
   des.object({ id = "create monster", class = "/", x = 54, y = 8 })
end

-- And give him a chance of being exasperating - better hope
-- he doesn't get all three...
if percent(25) then
   des.object("shield of reflection", 54,8)
end
if percent(25) then
   des.object({ id = "full healing", class = "!", x = 54, y = 8, buc = "blessed", spe = 0 })
end
if percent(15) then
   des.object("amulet of life saving", 54,8)
end

-- Give him a nasty weapon?
if percent(35) then
   des.object({ id = "dwarvish mattock", x = 54, y = 8, buc = "blessed", spe = 2 })
end
if percent(10) then
   des.object({ id = "short sword", x = 54, y = 8, buc = "blessed", spe = 4 })
end

des.object("!", 54,8)
des.object("!", 54,8)
des.object("[", 54,8)

-- The audience
des.monster({ class = "G", x = 46, y = 6, peaceful = 0 })
des.monster({ class = "G", x = 48, y = 6, peaceful = 0 })
des.monster({ class = "G", x = 50, y = 6, peaceful = 0 })
des.monster({ class = "G", x = 52, y = 6, peaceful = 0 })
des.monster({ class = "G", x = 54, y = 6, peaceful = 0 })
des.monster({ class = "G", x = 46, y = 10, peaceful = 0 })
des.monster({ class = "G", x = 48, y = 10, peaceful = 0 })
des.monster({ class = "G", x = 50, y = 10, peaceful = 0 })
des.monster({ class = "G", x = 52, y = 10, peaceful = 0 })
des.monster({ class = "G", x = 54, y = 10, peaceful = 0 })

--Throne room guards
des.monster({ id = "gnome warrior", x = 41, y = 07, peaceful = 0 })
des.monster({ id = "gnome warrior", x = 41, y = 09, peaceful = 0 })
des.monster({ id = "gnome warrior", x = 44, y = 07, peaceful = 0 })
des.monster({ id = "gnome warrior", x = 44, y = 07, peaceful = 0 })

for i = 1, 10 do
   des.monster({ id = "gnome", peaceful = 0 })
end

des.monster({ id = "gnome warrior", peaceful = 0 })
des.monster({ id = "gnome warrior", peaceful = 0 })

-- Random citizens
for i = 1, 5 do
   des.monster("h")
end

-- Insects are represented as well...
for i = 1, 5 do
   des.monster("a")
end

-- And to cater to a wider audience...
des.monster("'")
des.monster()
des.monster()
des.monster()

-- There was a random 'D' here, but it frequently resulted in out-of-depth adult dragons.
-- This is your reminder of those times.
-- (The source's reminder, a baby violet dragon, is dropped: 5.0 has no
-- violet dragons.)

-- A guardian...
des.object({ id = "statue", x = 56, y = 08, montype = "mumak" })
if percent(80) then
   des.trap("statue", 56,08)
end

-- ... of riches
des.gold({ amount = d(40,200), x = 57, y = 08 })

-- Somebody might just get lucky
if percent(5) then
   -- Hack'EM Planetar; an Archon here
   des.object({ id = "figurine", x = 58, y = 08, montype = "Archon", spe = 0 })
end

-- Store rooms
des.object(objects[1], 36,04)
des.object(objects[1], 37,04)
des.object(objects[1], 38,04)
des.object(objects[1], 39,04)
des.object(objects[1], 40,04)
des.object(objects[1], 41,04)
des.object(objects[1], 42,04)
des.object(objects[1], 43,04)
des.object(objects[1], 44,04)
des.object(objects[1], 45,04)

des.object(objects[2], 56,06)
des.object(objects[2], 57,06)
des.object(objects[2], 58,06)
des.object(objects[2], 59,06)

des.object(objects[3], 56,10)
des.object(objects[3], 57,10)
des.object(objects[3], 58,10)
des.object(objects[3], 59,10)

for i = 1, 6 do
   des.trap()
end

-- end mines.des
