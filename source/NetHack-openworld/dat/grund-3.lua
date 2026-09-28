-- NetHack: Open World  grund-3.lua
-- Copyright (c) Tina Hall, 2002
-- Modifications copyright (c) Slash'EM Development Team, 2003
-- Converted from Slash'EM grund.des ("grund-3") for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.
--
-- Grund's Stronghold
--
-- The names for the soldiers are what the orcs understood,
-- 'mercenary', 'trouble shooter' and 'deserter' are simply
-- too much for them to comprehend.
--
-- (grund-1, grund-2 and grund-3 are alternative versions of this level;
-- they differ only in some of the contents of two chests.)
--

-- INIT_MAP:' ',' ',false,false,lit,false: with both the foreground and the
-- background being solid rock, "lit" lit nothing in Slash'EM, so the level
-- starts out unlit and only the REGIONs below light it.
des.level_init({ style = "solidfill", fg = " ", lit = 0 })

des.level_flags("mazelevel", "noteleport", "hardfloor", "nommap", "shortsighted")

des.map({ halign = "right", valign = "center", map = [[
........           .....         
........         .........       
.........      .............     
.........     ......-F-......    
..........   .....---.---.....   
..........   ....--- . ---....   
........... ....-----------....  
........... ...--- - - - ---...  
...............-------------.... 
..............-- - - - - - --... 
..............F..---------..F... 
..............-- - - -.- - --... 
...............-------------.... 
........... ...--- - - - ---...  
........... ....-----------....  
..........   ....--- . ---....   
..........   .....---.---.....   
.........     ......-F-......    
.........      .............     
........         .........       
........           .....         
]] })
local place = { {21,03}, {14,10}, {28,10}, {21,17} }
shuffle(place)
des.door("locked", place[1][1], place[1][2])
-- The source also had an up staircase levregion identical to the branch
-- one; only the branch is kept (it is the way back to the open world).
des.levregion({ region = {18,07,24,13}, type = "branch" })
des.teleport_region({ region = {18,07,24,13} })
-- MAZEWALK:(22,11),east is done at the end of this part of the level:
-- Slash'EM carved its mazes after everything else had been placed.

des.region(selection.area(00,00,32,20), "lit")
des.region(selection.area(15,04,27,16), "unlit")
des.region(selection.area(15,04,16,05), "lit")
des.region(selection.area(26,04,27,05), "lit")
des.region(selection.area(15,15,16,16), "lit")
des.region(selection.area(26,15,27,16), "lit")
des.non_diggable(selection.area(00,00,17,20))
des.non_diggable(selection.area(25,00,32,20))
des.non_diggable(selection.area(18,00,24,06))
des.non_diggable(selection.area(18,14,24,20))

des.trap("statue", 11, 10)
-- (CONTAINER in the source, so the statue is empty)
des.object({ id = "statue", x = 11, y = 10, montype = "winged gargoyle", contents = 0 })

-- monsters (Fussvolk)
des.monster({ id = "orc-captain", peaceful = 0 })
for i = 1, 8 do
   des.monster({ id = "orc", peaceful = 0 })
end

if percent(60) then des.monster({ id = "orc-captain", peaceful = 0 }) end
for i = 1, 8 do
   if percent(60) then des.monster({ id = "orc", peaceful = 0 }) end
end

-- objects
if percent(80) then des.object({ id = "create monster", class = "/" }) end
-- wand of create horde (not in this game) -> wand of create monster
if percent(40) then des.object({ id = "create monster", class = "/" }) end
if percent(80) then des.object({ id = "speed monster", class = "/" }) end
if percent(40) then des.object({ id = "speed monster", class = "/" }) end
if percent(80) then des.object({ id = "make invisible", class = "/" }) end
if percent(40) then des.object({ id = "make invisible", class = "/" }) end
if percent(80) then des.object({ id = "invisibility", class = "!" }) end
if percent(40) then des.object({ id = "invisibility", class = "!" }) end
if percent(80) then des.object({ id = "speed", class = "!" }) end
if percent(40) then des.object({ id = "speed", class = "!" }) end
if percent(40) then des.object({ id = "full healing", class = "!" }) end
if percent(20) then des.object({ id = "full healing", class = "!" }) end
if percent(60) then des.object({ id = "extra healing", class = "!" }) end
if percent(30) then des.object({ id = "extra healing", class = "!" }) end
if percent(80) then des.object({ id = "healing", class = "!" }) end
if percent(40) then des.object({ id = "healing", class = "!" }) end
if percent(40) then des.object({ id = "gain level", class = "!" }) end
if percent(20) then des.object({ id = "gain level", class = "!" }) end
-- potion of invulnerability (not in this game) -> potion of full healing
if percent(20) then des.object({ id = "full healing", class = "!" }) end
if percent(10) then des.object({ id = "full healing", class = "!" }) end

--traps
-- (the source lists each square: 50% rust traps at x=0 on the odd rows,
-- 50% arrow traps zigzagging over x=1,2 and 50% spiked pits over x=3,4)
for y = 01, 19, 2 do
   if percent(50) then des.trap("rust", 00, y) end
end

for y = 00, 20 do
   if percent(50) then des.trap("arrow", 01 + y % 2, y) end
end

for y = 00, 20 do
   if percent(50) then des.trap("spiked pit", 03 + y % 2, y) end
end

des.trap("rust")
des.trap("rust")
if percent(50) then des.trap("rust") end
if percent(50) then des.trap("rust") end
des.trap("arrow")
des.trap("arrow")
if percent(50) then des.trap("arrow") end
if percent(50) then des.trap("arrow") end
des.trap("spiked pit")
des.trap("spiked pit")
if percent(50) then des.trap("spiked pit") end
if percent(50) then des.trap("spiked pit") end

for i = 1, 12 do
   des.trap("land mine")
end
for i = 1, 4 do
   if percent(50) then des.trap("land mine") end
end

if percent(50) then des.trap("level teleport") end
if percent(50) then des.trap("level teleport") end

des.monster({ id = "hobgoblin", x = 10, y = 11, peaceful = 0 })
des.object({ id = "fire", class = "/", buc = "cursed", spe = 1 })

des.engraving({ type = "burn", text = "Us wanna no veeseetohs!" })
des.engraving({ type = "burn", text = "boogrr ohf! GRR!" })
des.engraving({ type = "burn", text = "keap Us ohr Gohld!!" })
des.engraving({ type = "burn", text = "Me Preeeteee!" })
des.engraving({ type = "burn", text = "dee no preeeteee" })
des.engraving({ type = "burn", text = "veesetoohs gohd eet!" })

-- MAZEWALK:(22,11),east (see above).  Slash'EM only stocks a maze with
-- extra random objects when the maps leave much of the level empty,
-- which the two maps here do not, hence stocked = 0.
des.mazewalk({ x = 22, y = 11, dir = "east", stocked = 0 })

-- GEOMETRY:left,center.  Slash'EM put a left-aligned map at x=3, right
-- next to the map above, so the moat borders the courtyard; 5.0 would put
-- it at x=1 and leave two columns of rock in between, so it is placed
-- explicitly.
des.map({ x = 03, y = 00, map = [[
-----------------------------------------}
-...SH.----..-----...---..--------.+.-..-}
-...----..F..-..-....-.+..+.--..--.-.-..F}
-...--....--+-.---..--.----.-...--.-.-..-}
--S--......S#-.---..+..----.+....+.-.-.--}
-##-.......---.---F----------....---.-..F}
-#--.......-...---.-----..-----.----.-..-}
##-.......--.----...+.-...-------..+.-..F}
H--......---.-..-..--.--...---..-.--.-..-}
H-......----S-S---..F.+..-.F....+.--.-..F}
HS\........S...S.-------+---....----.-..-}
H-......----S-S----..---..--+-.-----.-..F}
H--......---.-..-....----....----..+.-..-}
##-.......--.----.....+.--F----...--.-..F}
-#--.......-...---...--.-..--...----.-..-}
-##-.......---.---F----.--..+.---..+.-..F}
--S--......S#-.---..---...+--F---+--.-.--}
-...--....--+-.--....--------.-...--.-..-}
-...----..F..-..-....+..-...+....---.-..F}
-...SH.----..------.---...---....---.S..-}
-----------------------------------------}
]] })
place = { {16,02}, {16,08}, {16,12}, {16,18}, {31,07} }
shuffle(place)
des.region(selection.area(00,00,39,20), "unlit")
des.region(selection.area(41,00,41,20), "lit")
des.non_diggable(selection.area(00,00,37,20))

des.drawbridge({ dir = "west", state = "closed", x = 41, y = 10 })

-- (whatever it's called)
des.monster({ id = "war orc", x = 39, y = 02, peaceful = 0 })
if percent(80) then des.object({ id = "sleep", class = "/", x = 39, y = 02 }) end
des.object({ id = "orcish bow", x = 39, y = 02, buc = "uncursed", spe = 1 })
des.object({ id = "orcish arrow", x = 39, y = 02, buc = "uncursed", spe = 2 })

des.monster({ id = "war orc", x = 39, y = 05, peaceful = 0 })
-- wand of fireball (not in this game) -> wand of fire
if percent(40) then des.object({ id = "fire", class = "/", x = 39, y = 05 }) end
des.object({ id = "orcish bow", x = 39, y = 05, buc = "uncursed", spe = 2 })
des.object({ id = "orcish arrow", x = 39, y = 05, buc = "uncursed", spe = 1 })

des.monster({ id = "soldier", x = 39, y = 07, peaceful = 0 })
if percent(40) then des.object({ id = "cold", class = "/", x = 39, y = 07 }) end
des.object({ id = "orcish bow", x = 39, y = 07, buc = "uncursed", spe = 1 })
des.object({ id = "orcish arrow", x = 39, y = 07, buc = "uncursed", spe = 3 })
-- sniper rifle and bullets (no firearms in this game) -> crossbow and
-- crossbow bolts
if percent(40) then des.object({ id = "crossbow", x = 39, y = 07, buc = "uncursed", spe = 3 }) end
if percent(40) then des.object({ id = "crossbow bolt", x = 39, y = 07, buc = "uncursed", spe = 4 }) end
if percent(40) then des.object({ id = "crossbow bolt", x = 39, y = 07, buc = "uncursed", spe = 3 }) end

des.monster({ id = "war orc", x = 39, y = 09, peaceful = 0 })
if percent(80) then des.object({ id = "magic missile", class = "/", x = 39, y = 09 }) end
des.object({ id = "orcish bow", x = 39, y = 09, buc = "uncursed", spe = 2 })
des.object({ id = "orcish arrow", x = 39, y = 09, buc = "uncursed", spe = 1 })

des.monster({ id = "war orc", x = 39, y = 11, peaceful = 0 })
if percent(80) then des.object({ id = "striking", class = "/", x = 39, y = 11 }) end
des.object({ id = "orcish bow", x = 39, y = 11, buc = "uncursed", spe = 2 })
des.object({ id = "orcish arrow", x = 39, y = 11, buc = "uncursed", spe = 3 })

des.monster({ id = "soldier", x = 39, y = 13, peaceful = 0 })
if percent(60) then des.object({ id = "fire", class = "/", x = 39, y = 13 }) end
des.object({ id = "orcish bow", x = 39, y = 13, buc = "uncursed", spe = 1 })
des.object({ id = "orcish arrow", x = 39, y = 13, buc = "uncursed", spe = 2 })
-- grenade launcher and frag grenades (no firearms in this game) ->
-- crossbow and crossbow bolts
if percent(40) then des.object({ id = "crossbow", x = 39, y = 13, buc = "uncursed", spe = 1 }) end
if percent(40) then des.object({ id = "crossbow bolt", x = 39, y = 13, buc = "uncursed", spe = 3 }) end
if percent(40) then des.object({ id = "crossbow bolt", x = 39, y = 13, buc = "uncursed", spe = 2 }) end

des.monster({ id = "war orc", x = 39, y = 15, peaceful = 0 })
if percent(60) then des.object({ id = "lightning", class = "/", x = 39, y = 15 }) end
des.object({ id = "orcish bow", x = 39, y = 15, buc = "uncursed", spe = 2 })
des.object({ id = "orcish arrow", x = 39, y = 15, buc = "uncursed", spe = 2 })

des.monster({ id = "war orc", x = 39, y = 18, peaceful = 0 })
-- wand of draining (not in this game) -> wand of striking, the closest
-- directed attack wand
if percent(40) then des.object({ id = "striking", class = "/", x = 39, y = 18 }) end
des.object({ id = "orcish bow", x = 39, y = 18, buc = "uncursed", spe = 3 })
des.object({ id = "orcish arrow", x = 39, y = 18, buc = "uncursed", spe = 3 })

--
des.monster({ id = "hell hound", x = 36, y = 01, peaceful = 0 })
if percent(50) then des.monster({ id = "hell hound", x = 36, y = 07, peaceful = 0 }) end
if percent(50) then des.monster({ id = "hell hound", x = 36, y = 12, peaceful = 0 }) end
des.monster({ id = "hell hound", x = 36, y = 15, asleep = 1, peaceful = 0 })

-- caves

if percent(50) then des.monster({ id = "Uruk-hai", x = 18, y = 02, peaceful = 0 }) end
des.monster({ id = "Uruk-hai", x = 19, y = 02, peaceful = 0 })
des.monster({ id = "Uruk-hai", x = 20, y = 02, peaceful = 0 })
des.monster({ id = "Uruk-hai", x = 18, y = 03, peaceful = 0 })
des.monster({ id = "Uruk-hai", x = 19, y = 03, peaceful = 0 })

des.monster({ id = "orc shaman", x = 24, y = 02, peaceful = 0 })
if percent(50) then des.monster({ id = "orc shaman", x = 24, y = 02, peaceful = 0 }) end

des.monster({ id = "stone giant", x = 30, y = 04, peaceful = 0 })
if percent(50) then des.monster({ id = "stone giant", x = 31, y = 03, peaceful = 0 }) end

des.monster({ id = "rogue", x = 18, y = 07, peaceful = 0 })
-- rapier (not in this game) -> long sword
des.object({ id = "long sword", x = 18, y = 07, buc = "uncursed", spe = 1 })
if percent(50) then des.object({ id = "sickness", class = "!", x = 18, y = 07 }) end
if percent(50) then des.object({ id = "sack", x = 18, y = 07 }) end
des.monster({ id = "mugger", x = 18, y = 08, peaceful = 0 })
des.object({ id = "club", x = 18, y = 08, buc = "uncursed", spe = 2 })
if percent(40) then des.object({ id = "crossbow", x = 18, y = 08, buc = "uncursed", spe = 3 }) end
if percent(40) then des.object({ id = "crossbow bolt", x = 18, y = 08, buc = "uncursed", spe = 1 }) end
if percent(50) then des.object({ id = "paralysis", class = "!", x = 18, y = 08 }) end
des.monster({ id = "soldier", x = 18, y = 09, peaceful = 0 })
if percent(50) then des.object({ id = "booze", class = "!", x = 18, y = 09 }) end

des.monster({ id = "ogre", x = 24, y = 07, peaceful = 0 })
des.monster({ id = "ogre", x = 25, y = 07, peaceful = 0 })
if percent(50) then des.monster({ id = "ogre", x = 24, y = 08, peaceful = 0 }) end
des.monster({ id = "ogre", x = 25, y = 08, peaceful = 0 })

des.monster({ id = "hill orc", x = 29, y = 09, peaceful = 0 })
des.monster({ id = "hill orc", x = 30, y = 09, peaceful = 0 })
if percent(50) then des.monster({ id = "hill orc", x = 31, y = 09, peaceful = 0 }) end
des.monster({ id = "hill orc", x = 29, y = 10, peaceful = 0 })
if percent(50) then des.monster({ id = "hill orc", x = 30, y = 10, peaceful = 0 }) end
des.monster({ id = "hill orc", x = 31, y = 10, peaceful = 0 })

des.monster({ id = "snow orc", x = 18, y = 12, peaceful = 0 })
if percent(50) then des.monster({ id = "snow orc", x = 19, y = 12, peaceful = 0 }) end
des.monster({ id = "snow orc", x = 20, y = 12, peaceful = 0 })
if percent(50) then des.monster({ id = "snow orc", x = 18, y = 13, peaceful = 0 }) end
des.monster({ id = "snow orc", x = 19, y = 13, peaceful = 0 })
des.monster({ id = "snow orc", x = 20, y = 13, peaceful = 0 })

des.monster({ id = "orc shaman", x = 25, y = 14, peaceful = 0 })
if percent(50) then des.monster({ id = "orc shaman", x = 27, y = 15, peaceful = 0 }) end

if percent(50) then des.monster({ id = "great orc", x = 18, y = 17, peaceful = 0 }) end
des.monster({ id = "great orc", x = 19, y = 17, peaceful = 0 })
des.monster({ id = "great orc", x = 20, y = 17, peaceful = 0 })
des.monster({ id = "great orc", x = 18, y = 18, peaceful = 0 })
if percent(50) then des.monster({ id = "great orc", x = 19, y = 18, peaceful = 0 }) end
des.monster({ id = "great orc", x = 20, y = 18, peaceful = 0 })

des.monster({ id = "Mordor orc", x = 18, y = 17, peaceful = 0 })
if percent(50) then des.monster({ id = "Mordor orc", x = 19, y = 17, peaceful = 0 }) end
des.monster({ id = "Mordor orc", x = 18, y = 18, peaceful = 0 })
des.monster({ id = "Mordor orc", x = 19, y = 18, peaceful = 0 })

if percent(80) then des.monster({ id = "troll", peaceful = 0 }) end
if percent(60) then des.monster({ id = "rock troll", peaceful = 0 }) end
-- two-headed troll (not in this game) -> ice troll
if percent(40) then des.monster({ id = "ice troll", peaceful = 0 }) end
-- black troll (not in this game) -> Olog-hai
if percent(20) then des.monster({ id = "Olog-hai", peaceful = 0 }) end

-- slaves
-- (the source's trailing "random" parsed as an alignment, which made
-- Slash'EM's loader skip these goblins; they are created as intended)
des.monster("goblin")
des.monster("goblin")
des.monster("goblin")
des.monster("goblin")
if percent(50) then des.monster("goblin") end
if percent(50) then des.monster("goblin") end

--
des.trap("statue", 16, 10)
-- harpy (not in this game) -> vampire bat
des.object({ id = "statue", x = 16, y = 10, montype = "vampire bat", contents = 0 })

-- throneroom
des.monster({ id = "Grund the Orc King", x = 02, y = 10, peaceful = 0 })
des.object({ class = "/", x = 02, y = 10 })
des.object({ class = "\"", x = 02, y = 10 })
des.object({ class = "[", x = 02, y = 10 })

des.monster({ id = "demon orc", x = 03, y = 09, peaceful = 0 })
des.monster({ id = "demon orc", x = 03, y = 11, peaceful = 0 })
if percent(60) then des.monster({ id = "demon orc", x = 07, y = 09, peaceful = 0 }) end
if percent(60) then des.monster({ id = "demon orc", x = 07, y = 11, peaceful = 0 }) end

des.monster({ id = "orc shaman", x = 04, y = 08, peaceful = 0 })
des.monster({ id = "orc shaman", x = 04, y = 12, peaceful = 0 })

des.monster({ id = "ogre mage", x = 04, y = 10, peaceful = 0 })
if percent(50) then des.monster({ id = "ogre mage", x = 06, y = 10, peaceful = 0 }) end

-- shadow ogre (not in this game) -> ogre king
if percent(50) then des.monster({ id = "ogre king", x = 06, y = 07, peaceful = 0 }) end
if percent(50) then des.monster({ id = "ogre lord", x = 06, y = 13, peaceful = 0 }) end

des.monster({ id = "orc zombie", x = 07, y = 04, asleep = 1, peaceful = 0 })
des.monster({ id = "orc zombie", x = 09, y = 06, asleep = 1, peaceful = 0 })
des.monster({ id = "orc mummy", x = 08, y = 05, asleep = 1, peaceful = 0 })

des.monster({ id = "orc zombie", x = 07, y = 16, asleep = 1, peaceful = 0 })
des.monster({ id = "orc zombie", x = 09, y = 14, asleep = 1, peaceful = 0 })
des.monster({ id = "orc mummy", x = 08, y = 15, asleep = 1, peaceful = 0 })

-- prisons
-- (another "random" alignment, see the slaves above)
des.monster({ id = "skeleton", x = 11, y = 01 })
if percent(40) then des.monster({ id = "nurse", x = 12, y = 02, peaceful = 1 }) end
-- gypsy (not in this game) -> prisoner
if percent(10) then des.monster({ id = "prisoner", x = 12, y = 18, peaceful = 1 }) end
des.monster({ id = "ghost", x = 11, y = 19, peaceful = 1 })
des.object({ id = "corpse", x = 11, y = 19, montype = "human" })

-- treasury
des.object({ id = "chest", x = 02, y = 02 })
des.monster({ id = "giant spider", x = 02, y = 03, asleep = 1, peaceful = 0 })
des.monster({ id = "giant spider", x = 03, y = 01, asleep = 1, peaceful = 0 })
des.gold({ amount = 1200, x = 02, y = 02 })
des.gold({ x = 02, y = 02 })

des.object({ id = "chest", x = 06, y = 01, contents = function()
   -- amulet versus stone (not in this game) -> random amulet
   des.object({ class = "\"" })
   des.object({ id = "create monster", class = "+", buc = "blessed", spe = 4 })
   if percent(20) then des.object({ id = "magic marker", buc = "cursed", spe = 34 }) end
   des.object({ id = "enlightenment", class = "!", buc = "blessed", spe = 0 })
   des.object({ id = "enlightenment", class = "!", buc = "blessed", spe = 0 })
   if percent(50) then des.object({ id = "enlightenment", class = "!", buc = "blessed", spe = 0 }) end
   if percent(50) then des.object({ id = "enlightenment", class = "!", buc = "blessed", spe = 0 }) end
end })

des.gold({ amount = 8700, x = 06, y = 01 })
des.gold({ x = 06, y = 01 })

-- arms storage
des.object({ id = "chest", x = 02, y = 18 })
des.monster({ id = "orc", x = 03, y = 19, asleep = 1, peaceful = 0 })
if percent(40) then des.object({ id = "booze", class = "!", x = 02, y = 19 }) end

des.object({ id = "chest", x = 06, y = 19, contents = function()
   des.object({ id = "oilskin cloak", buc = "uncursed", spe = 0 })
   des.object({ id = "tin", montype = "spinach" })
   des.object({ id = "tin", montype = "spinach" })
   if percent(50) then des.object({ id = "tin", montype = "spinach" }) end
   if percent(50) then des.object({ id = "tin", montype = "spinach" }) end
end })

--traps
if percent(90) then des.trap("land mine", 08, 10) end
if percent(90) then des.trap("board", 09, 10) end
if percent(90) then des.trap("anti magic", 10, 10) end

des.trap("falling rock")
if percent(50) then des.trap("falling rock") end

des.trap("web")
if percent(50) then des.trap("web") end

des.trap("dart")
des.trap("dart")
if percent(50) then des.trap("dart") end
if percent(50) then des.trap("dart") end

-- goodies for the monsters:
des.object({ id = "speed", class = "!" })
des.object({ id = "speed", class = "!" })
if percent(50) then des.object({ id = "speed", class = "!" }) end
if percent(50) then des.object({ id = "speed", class = "!" }) end
des.object({ id = "invisibility", class = "!" })
des.object({ id = "invisibility", class = "!" })
if percent(50) then des.object({ id = "invisibility", class = "!" }) end
if percent(50) then des.object({ id = "invisibility", class = "!" }) end
-- wand of healing (not in this game) -> potion of healing
des.object({ id = "healing", class = "!" })
if percent(50) then des.object({ id = "healing", class = "!" }) end
des.object({ id = "create monster", class = "/" })
-- wand of create horde (not in this game) -> wand of create monster
if percent(20) then des.object({ id = "create monster", class = "/" }) end
if percent(20) then des.object({ id = "polymorph", class = "/" }) end
des.object({ id = "create monster", class = "?" })
if percent(40) then des.object({ id = "create monster", class = "?", buc = "cursed", spe = 0 }) end

-- doors

des.door("locked", place[1][1], place[1][2])
des.door("locked", place[2][1], place[2][2])

des.door("random", 35, 01)
des.door("random", 23, 02)
des.door("random", 26, 02)
des.door("random", 20, 04)
des.door("random", 28, 04)
des.door("random", 33, 04)
des.door("random", 20, 07)
des.door("random", 35, 07)
des.door("random", 22, 09)
des.door("random", 32, 09)
des.door("random", 24, 10)
des.door("random", 28, 11)
des.door("random", 35, 12)
des.door("random", 22, 13)
des.door("random", 28, 15)
des.door("random", 35, 15)
des.door("random", 26, 16)
des.door("random", 33, 16)
des.door("random", 21, 18)
des.door("random", 28, 18)

des.door("locked", 02, 04)
des.door("locked", 02, 16)

des.door("locked", 12, 03)
des.door("locked", 12, 17)

des.door("locked", 11, 04)
des.door("locked", 11, 16)

des.door("locked", 01, 10)
des.door("locked", 04, 01)
des.door("locked", 04, 19)

des.door("locked", 11, 10)
des.door("locked", 12, 09)
des.door("locked", 12, 11)
des.door("locked", 14, 09)
des.door("locked", 14, 11)
des.door("locked", 15, 10)
