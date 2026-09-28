-- NetHack: Open World  nightmar.lua
--	SCCS Id: @(#)nightmar.des	0.0.7	2002/03/13
--	$Id$
-- Converted from Slash'EM nightmar.des for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.
--
-- Nightmare's Nightmare World
--
des.level_init({ style = "solidfill", fg = " " });

-- The source also has the Slash'EM flag "spooky", which has no 5.0
-- equivalent (and this is not a graveyard); it is dropped.
des.level_flags("mazelevel", "noteleport", "hardfloor", "nommap", "shortsighted")

-- The source draws this same map twice, in order to use two different sets
-- of RANDOM_PLACES; drawing it once is enough here.
des.map({ halign = "center", valign = "center", map = [[
  T.    T.T                    CC     CC    #######H#H                      
 T.... ......   ...T  LLL    CCCCCC  CCCC   #       H   #################H. 
   .T...TTTT.. ..T.. LL LL  CCCCCC   C CCC  # --+---+-- #                   
  ..TTTTT. TT...T..  LL    CCCCCCCC    CCC  # -...-...- #                   
 T.TTTT.TTTTTTTTT.  CCLL  CCCCCCCCCC CCCCC  # +...+...+ #                   
 ... TT. T T T .T.. CCCLLLCCCCCCCCCCCCCCC   # -...-...- #      .     .      
  .TTTTTTTTTTTTTTT.  CCCCLLLCCCCCCCCCCC     # --+---+-- #                   
  .T T T T TT. T T.. CCCCCCLL-S-CCCCCC  C   #     -...- #                   
 ..TTTTTTTTTTTTTTTT.  CCCCLL--.--CCCCC CCC  #H### +...+ #   .  H- - -H  .   
T.TT TTT T\T T . T.. CCCCLLL-.{.-CCCC  CC   #   # -...- #      -.}}}.-      
 .TTTT.TTTTTTTTTTT.  CCLLLLL--.--CCCC CCC   # .H# --+-- #       }.}.}       
..TT T T T T T TT.. CCLLCCCLL---LCCCCCCC    #   # -...- #      -}}.}}-      
.TTTTTTT.TTTTT.T..  LLL CCCCLLLLLLCCCCCCCC  ##### +...+ #       }.}.}       
.T T . TTT . TTT.. LL   CCCCCCLCCLLLCCCCC         -...- #      -.}}}.-      
.TTTTTTTTTTTTTTTT.  L. CCCCCCLLCCCCLLLCCC --+---+---+-- #   .  H- - -H  .   
.TT. T T T T T TT..     CCCLLLCCCCCCCLLC  -...-...-...- #                   
 .TTTTTTTTTTTT..TT.. . CCLLLCCCCCCCCCCLC  +...+...+...+H#                   
 ...TT T .TT TTTTTT... LLLCCCCCCCCC CCLC  -...-...-...- H      .     .      
  T..TTTTTT....T.TT. .LL  CCCCCCCC   LLCC --+---+---+--                     
    ....TT..  .....  LL    CCCCCC   LL CC               #H                  
       ....     T.  LL       CC     L   CH###############                   
]] });

-- (first RANDOM_PLACES of the source)
local ringplace = { {25,02},{21,14},{20,20},{36,20} }
shuffle(ringplace)
if percent(80) then
   des.object({ id = "fire resistance", class = "=", coord = ringplace[1] })
end

local place = { {48,04},{52,04},{52,08},{52,12},{44,16},{52,16} }
shuffle(place)
des.levregion({ region = {48,16,48,16}, type = "branch" })
des.teleport_region({ region = {47,15,49,17} })
des.non_diggable(selection.area(00,00,75,20))

des.non_passwall(selection.area(43,00,43,12))
des.non_passwall(selection.area(40,13,49,13))
des.non_passwall(selection.area(49,07,49,12))
des.non_passwall(selection.area(45,07,48,07))
des.non_passwall(selection.area(45,01,45,06))
des.non_passwall(selection.area(46,01,54,01))
des.non_passwall(selection.area(55,00,55,19))
des.non_passwall(selection.area(42,19,54,19))
des.non_passwall(selection.area(41,13,41,20))

des.non_passwall(selection.area(64,08,68,08))
des.non_passwall(selection.area(64,14,68,14))
des.non_passwall(selection.area(63,09,63,13))
des.non_passwall(selection.area(69,09,69,13))

-- (the source's two MAZEWALKs are at the end of this file: Slash'EM
-- always carved its mazes after placing everything else)

-- entrance
des.region(selection.area(47,15,49,17), "lit")
des.engraving({ x = 48, y = 16, type = "engrave", text = "Beware of Dreams come true!" })
des.monster({ id = "imp", x = 49, y = 15, peaceful = 0 })
if percent(60) then des.trap("sleep gas", 48,15) end
if percent(60) then des.trap("sleep gas", 47,16) end
if percent(60) then des.trap("sleep gas", 49,16) end
if percent(60) then des.trap("sleep gas", 48,17) end

-- false treasure
-- (Slash'EM's piles of killer coins are mimics pretending to be gold:
-- small mimic = pile, large mimic = large pile, giant mimic = huge pile)
des.monster({ id = "large mimic", coord = place[1], appear_as = "obj:gold piece", asleep = 1 })
if percent(80) then
   des.monster({ id = "small mimic", coord = place[1], appear_as = "obj:gold piece", asleep = 1 })
end
if percent(80) then
   des.monster({ id = "giant mimic", coord = place[1], appear_as = "obj:gold piece", asleep = 1 })
end
if percent(80) then
   des.monster({ id = "small mimic", coord = place[1], appear_as = "obj:gold piece", asleep = 1 })
end
if percent(80) then
   des.monster({ id = "giant mimic", coord = place[1], appear_as = "obj:gold piece", asleep = 1 })
end
if percent(80) then
   des.monster({ id = "large mimic", coord = place[1], appear_as = "obj:gold piece", asleep = 1 })
end
if percent(40) then
   des.monster({ id = "small mimic", coord = place[1], appear_as = "obj:gold piece", asleep = 1 })
end
if percent(40) then
   des.monster({ id = "large mimic", coord = place[1], appear_as = "obj:gold piece", asleep = 1 })
end
if percent(40) then
   des.monster({ id = "giant mimic", coord = place[1], appear_as = "obj:gold piece", asleep = 1 })
end
if percent(60) then
   des.object({ id = "worthless piece of white glass", coord = place[1], buc = "cursed", spe = 0 })
end
if percent(60) then
   des.object({ id = "worthless piece of white glass", coord = place[1], buc = "uncursed", spe = 0 })
end
if percent(60) then
   des.object({ id = "worthless piece of white glass", coord = place[1], buc = "blessed", spe = 0 })
end

-- bad food
-- (Slash'EM's killer food/tripe rations and bad eggs are mimics pretending
-- to be food: large mimic = food ration, small mimic = tripe ration or egg)
des.monster({ id = "large mimic", coord = place[2], appear_as = "obj:food ration", asleep = 1 })
if percent(80) then
   des.monster({ id = "large mimic", coord = place[2], appear_as = "obj:food ration", asleep = 1 })
end
if percent(80) then
   des.monster({ id = "large mimic", coord = place[2], appear_as = "obj:food ration", asleep = 1 })
end
if percent(40) then
   des.monster({ id = "large mimic", coord = place[2], appear_as = "obj:food ration", asleep = 1 })
end
if percent(40) then
   des.monster({ id = "large mimic", coord = place[2], appear_as = "obj:food ration", asleep = 1 })
end
if percent(80) then
   des.monster({ id = "small mimic", coord = place[2], appear_as = "obj:tripe ration", asleep = 1 })
end
if percent(80) then
   des.monster({ id = "small mimic", coord = place[2], appear_as = "obj:egg", asleep = 1 })
end
if percent(60) then
   des.monster({ id = "small mimic", coord = place[2], appear_as = "obj:egg", asleep = 1 })
end
if percent(40) then
   des.monster({ id = "small mimic", coord = place[2], appear_as = "obj:egg", asleep = 1 })
end
-- Slash'EM giant louse egg (spe 2 = "laid by you"); a soldier ant egg here
des.object({ id = "egg", coord = place[2], montype = "soldier ant", laid_by_you = true })
if percent(40) then
   -- Slash'EM giant flea egg; a giant ant egg here
   des.object({ id = "egg", coord = place[2], montype = "giant ant" })
end
if percent(20) then
   -- Slash'EM mushroom; a lichen corpse (the nearest fungus) here
   des.object({ id = "corpse", montype = "lichen", coord = place[2],
                buc = "cursed" })
end
-- The source asks for tins of "asphynx meat" and "green slime meat", which
-- Slash'EM's level compiler did not recognise, so they were tins of random
-- meat; they are kept as tins with random contents.
if percent(50) then
   des.object({ id = "tin", coord = place[2], spe = 0 })
end
if percent(50) then
   des.object({ id = "tin", coord = place[2], spe = 0 })
end

-- junk
if percent(40) then
   des.object({ id = "sickness", class = "!", coord = place[3], buc = "cursed", spe = 0 })
end
if percent(40) then
   des.object({ id = "sleeping", class = "!", coord = place[3], buc = "cursed", spe = 0 })
end
if percent(40) then
   des.object({ id = "confusion", class = "!", coord = place[3], buc = "cursed", spe = 0 })
end
if percent(40) then
   des.object({ id = "hallucination", class = "!", coord = place[3], buc = "cursed", spe = 0 })
end
if percent(40) then
   des.object({ id = "blindness", class = "!", coord = place[3], buc = "cursed", spe = 0 })
end
if percent(40) then
   des.object({ id = "polymorph", class = "!", coord = place[3], buc = "cursed", spe = 0 })
end
if percent(40) then
   des.object({ id = "sickness", class = "!", coord = place[3], buc = "cursed", spe = 0 })
end
if percent(40) then
   des.object({ id = "acid", class = "!", coord = place[3], buc = "cursed", spe = 0 })
end
if percent(40) then
   des.object({ id = "paralysis", class = "!", coord = place[3], buc = "cursed", spe = 0 })
end
if percent(40) then
   des.object({ id = "polymorph", class = "!", coord = place[3], buc = "cursed", spe = 0 })
end
if percent(40) then
   -- Slash'EM wand of draining; a wand of striking here
   des.object({ id = "striking", class = "/", coord = place[3], buc = "cursed", spe = 0 })
end
if percent(60) then
   des.object({ id = "opening", class = "/", coord = place[3], buc = "cursed", spe = 0 })
end
if percent(80) then
   des.object({ id = "nothing", class = "/", coord = place[3], buc = "cursed", spe = 0 })
end
if percent(60) then
   des.object({ id = "secret door detection", class = "/", coord = place[3], buc = "cursed", spe = 0 })
end
if percent(40) then
   des.object({ id = "fumble boots", coord = place[3], buc = "cursed", spe = -2 })
end
if percent(40) then
   des.object({ id = "gauntlets of fumbling", coord = place[3], buc = "cursed", spe = -4 })
end
if percent(40) then
   -- Slash'EM poisonous cloak ("dirty rag"); a mummy wrapping here
   des.object({ id = "mummy wrapping", coord = place[3], buc = "cursed", spe = -1 })
end
if percent(40) then
   -- Slash'EM robe of weakness; a plain robe here
   des.object({ id = "robe", coord = place[3], buc = "cursed", spe = 0 })
end
if percent(40) then
   -- Slash'EM fly swatter; a club here
   des.object({ id = "club", coord = place[3], buc = "cursed", spe = -2, name = "Bugshmasher" })
end
if percent(40) then
   des.object({ id = "worm tooth", coord = place[3], buc = "cursed", spe = -4, name = "Storm Brand" })
end
if percent(40) then
   des.object({ id = "short sword", coord = place[3], buc = "cursed", spe = -3, name = "Chaosbane" })
end
if percent(40) then
   des.object({ id = "amulet of strangulation", coord = place[3], buc = "cursed", spe = 0, name = "life saving" })
end
if percent(40) then
   -- Slash'EM ring of sleeping; a ring of aggravate monster here
   des.object({ id = "aggravate monster", class = "=", coord = place[3], buc = "cursed", spe = 0, name = "slow digestion" })
end
if percent(40) then
   des.object({ id = "hunger", class = "=", coord = place[3], buc = "cursed", spe = 0, name = "free action" })
end
if percent(40) then
   des.object({ id = "increase accuracy", class = "=", coord = place[3], buc = "blessed", spe = -9, name = "polymorph control" })
end
if percent(40) then
   des.object({ id = "oil lamp", coord = place[3], buc = "cursed", spe = 0 })
end
des.monster({ class = "@", coord = place[3], peaceful = 0 })
des.monster({ class = "@", coord = place[3], peaceful = 0 })
if percent(80) then
   des.monster({ class = "@", coord = place[3], peaceful = 1 })
end
if percent(60) then
   des.monster({ class = "@", coord = place[3], asleep = 1 })
end
if percent(60) then
   des.monster({ class = "@", coord = place[3], peaceful = 0 })
end
if percent(60) then
   des.monster({ class = "@", coord = place[3], peaceful = 1 })
end
if percent(60) then
   des.monster({ class = "@", coord = place[3], peaceful = 0 })
end
if percent(40) then
   des.monster({ class = "@", coord = place[3], peaceful = 0 })
end
if percent(40) then
   des.monster({ class = "@", coord = place[3], peaceful = 1 })
end

-- such a waste...
des.object({ id = "tinning kit", coord = place[4], buc = "cursed", spe = 0 })
des.object({ id = "corpse", coord = place[4], montype = "black dragon" })
-- (the source also has deep dragon and shimmering dragon corpses here;
-- 5.0 has no such dragons, so they are dropped)
des.object({ id = "corpse", coord = place[4], montype = "red dragon" })
des.object({ id = "corpse", coord = place[4], montype = "orange dragon" })
des.object({ id = "corpse", coord = place[4], montype = "yellow dragon" })
des.object({ id = "corpse", coord = place[4], montype = "green dragon" })
des.object({ id = "corpse", coord = place[4], montype = "blue dragon" })
des.object({ id = "corpse", coord = place[4], montype = "gray dragon" })
des.object({ id = "corpse", coord = place[4], montype = "white dragon" })
des.monster({ id = "maggot", coord = place[4], peaceful = 0 })
des.monster({ id = "maggot", coord = place[4], peaceful = 0 })
des.monster({ id = "maggot", coord = place[4], peaceful = 0 })
des.monster({ id = "maggot", coord = place[4], peaceful = 0 })
des.monster({ id = "maggot", coord = place[4], peaceful = 0 })
des.monster({ id = "maggot", coord = place[4], peaceful = 0 })
if percent(50) then
   des.monster({ id = "maggot", coord = place[4], peaceful = 0 })
end
if percent(50) then
   des.monster({ id = "maggot", coord = place[4], peaceful = 0 })
end
if percent(50) then
   -- Slash'EM carrion crawler; a centipede here
   des.monster({ id = "centipede", coord = place[4], asleep = 1 })
end

-- snake pit
des.trap("spiked pit", place[5][1], place[5][2])
if percent(90) then
   -- Slash'EM king cobra; a cobra here
   des.monster({ id = "cobra", coord = place[5], peaceful = 0 })
end
if percent(90) then
   des.monster({ id = "pit viper", coord = place[5], asleep = 1 })
end
if percent(90) then
   des.monster({ id = "pit viper", coord = place[5], peaceful = 0 })
end
des.monster({ class = "S", coord = place[5], peaceful = 0 })
des.monster({ class = "S", coord = place[5], asleep = 1 })
if percent(50) then
   des.monster({ class = "S", coord = place[5], peaceful = 0 })
end
if percent(50) then
   des.monster({ class = "S", coord = place[5], asleep = 1 })
end
des.monster({ class = "s", coord = place[5], asleep = 1 })
if percent(50) then
   des.monster({ class = "s", coord = place[5], peaceful = 0 })
end

-- no temple
des.altar({ coord = place[6], align = "coaligned", type = "altar" })
des.monster({ id = "aligned cleric", coord = place[6], align = "coaligned", peaceful = 1 })

-- boulder path
des.object("boulder", 44,00)
des.trap("rolling boulder", 44,01)
des.trap("rolling boulder", 44,07)
des.object({ id = "striking", class = "/", x = 46, y = 10, buc = "uncursed", spe = 2 })
des.object({ id = "runesword", x = 46, y = 10, buc = "cursed", spe = 0 })
if percent(60) then
   des.monster({ id = "ghost", x = 47, y = 00, peaceful = 0 })
end
if percent(60) then
   des.monster({ id = "ghost", x = 50, y = 00, peaceful = 0 })
end

-- maze
-- (Slash'EM rot worms are maggots here)
if percent(60) then des.monster({ id = "maggot", x = 63, y = 05, peaceful = 0 }) end
if percent(60) then des.monster({ id = "maggot", x = 69, y = 05, peaceful = 0 }) end
if percent(60) then des.monster({ id = "maggot", x = 60, y = 08, peaceful = 0 }) end
if percent(60) then des.monster({ id = "maggot", x = 72, y = 08, peaceful = 0 }) end
if percent(60) then des.monster({ id = "maggot", x = 60, y = 14, peaceful = 0 }) end
if percent(60) then des.monster({ id = "maggot", x = 72, y = 14, peaceful = 0 }) end
if percent(60) then des.monster({ id = "maggot", x = 63, y = 17, peaceful = 0 }) end
if percent(60) then des.monster({ id = "maggot", x = 69, y = 17, peaceful = 0 }) end

if percent(50) then des.monster({ id = "shade", x = 63, y = 05, peaceful = 0 }) end
if percent(50) then des.monster({ id = "shade", x = 69, y = 17, peaceful = 0 }) end

-- room
des.region({ region = {64,09,68,13}, lit = 0, type = "swamp", filled = 1 })
-- The statue trap comes before the statue, as it did in Slash'EM (which
-- made traps before objects): the arch-lich statue then lies on top of the
-- trap's own statue and is the one that comes to life, with its contents.
des.trap("statue", 66,11)
des.object({ id = "gray dragon scales", x = 66, y = 11, buc = "cursed", spe = -9 })
des.object({ id = "statue", x = 66, y = 11, montype = "arch-lich",
             contents = function()
                -- Slash'EM wand of fireball; a wand of fire here
                des.object({ id = "fire", class = "/" })
                -- Slash'EM wand of create horde; a wand of create monster here
                des.object({ id = "create monster", class = "/", buc = "uncursed", spe = 1 })
                des.object({ id = "speed monster", class = "/", buc = "uncursed", spe = 1 })
                des.object({ id = "make invisible", class = "/", buc = "uncursed", spe = 1 })
                des.object({ id = "corpse", montype = "cockatrice" })
                des.object({ id = "leather gloves", buc = "cursed", spe = -1 })
             end
})

des.monster({ id = "electric eel", x = 66, y = 10, peaceful = 0 })
des.monster({ id = "electric eel", x = 66, y = 12, peaceful = 0 })
des.monster({ id = "electric eel", x = 65, y = 11, peaceful = 0 })
des.monster({ id = "electric eel", x = 67, y = 11, peaceful = 0 })
if percent(50) then des.monster({ id = "electric eel", x = 64, y = 11, peaceful = 0 }) end
if percent(50) then des.monster({ id = "electric eel", x = 68, y = 11, peaceful = 0 }) end

-- cloud
des.monster({ id = "air elemental", x = 23, y = 07, peaceful = 0 })
if percent(60) then des.monster({ id = "air elemental", x = 24, y = 08, peaceful = 0 }) end
des.monster({ id = "fire elemental", x = 32, y = 15, peaceful = 0 })
if percent(60) then des.monster({ id = "fire elemental", x = 33, y = 16, peaceful = 0 }) end
des.monster({ id = "earth elemental", x = 40, y = 08, peaceful = 0 })
if percent(60) then des.monster({ id = "earth elemental", x = 39, y = 09, peaceful = 0 }) end
des.monster({ id = "water elemental", x = 31, y = 02, peaceful = 0 })
if percent(60) then des.monster({ id = "water elemental", x = 32, y = 03, peaceful = 0 }) end
des.monster({ id = "stalker", x = 40, y = 03, peaceful = 0 })
if percent(60) then des.monster({ id = "stalker", x = 39, y = 04, peaceful = 0 }) end
if percent(40) then des.monster({ class = "E", x = 33, y = 07, peaceful = 0 }) end
if percent(40) then des.monster({ class = "E", x = 34, y = 08, peaceful = 0 }) end
if percent(40) then des.monster({ class = "E", x = 25, y = 13, peaceful = 0 }) end
if percent(40) then des.monster({ class = "E", x = 26, y = 14, peaceful = 0 }) end

des.monster({ id = "gremlin", x = 38, y = 12, name = "Clown", peaceful = 0 })

des.monster({ id = "mind flayer", x = 29, y = 09, name = "Ginger", peaceful = 0 })
if percent(80) then
   des.monster({ id = "mind flayer", x = 30, y = 09, name = "Victoria", peaceful = 0 })
end
if percent(80) then
   des.monster({ id = "mind flayer", x = 31, y = 09, name = "Emma", peaceful = 0 })
end
if percent(60) then
   des.monster({ id = "master mind flayer", x = 30, y = 08, name = "Mel C.", peaceful = 0 })
end
if percent(60) then
   des.monster({ id = "master mind flayer", x = 30, y = 10, name = "Mel B.", peaceful = 0 })
end
des.object({ id = "chest", x = 30, y = 09,
             contents = function()
                if percent(70) then
                   des.object("amulet of flying")
                end
                des.object({ id = "cold", class = "/", buc = "uncursed", spe = 16 })
                if percent(80) then
                   des.object({ id = "digging", class = "/" })
                end
             end
})

-- forest
des.monster({ id = "Nightmare", x = 10, y = 09, asleep = 1 })
if percent(60) then des.monster({ id = "pixie", x = 10, y = 09, asleep = 1 }) end
if percent(60) then des.monster({ id = "pixie", x = 10, y = 09, peaceful = 0 }) end
if percent(60) then des.monster({ id = "quickling", x = 10, y = 09, asleep = 1 }) end
if percent(60) then des.monster({ id = "quickling", x = 10, y = 09, peaceful = 0 }) end
if percent(60) then des.monster({ id = "pixie", x = 10, y = 09, asleep = 1 }) end
if percent(60) then des.monster({ id = "pixie", x = 10, y = 09, peaceful = 0 }) end
des.monster({ id = "black unicorn", x = 10, y = 09, peaceful = 0 })
des.monster({ id = "gray unicorn", x = 10, y = 09, peaceful = 0 })
des.monster({ id = "white unicorn", x = 10, y = 09, peaceful = 0 })
des.monster({ id = "wood nymph", x = 10, y = 09, peaceful = 0 })
des.monster({ id = "brownie", x = 10, y = 09, asleep = 1 })
des.monster({ id = "pixie", x = 10, y = 09, asleep = 1 })
des.monster({ id = "pixie", x = 10, y = 09, peaceful = 0 })
des.monster({ id = "pixie", x = 10, y = 09, asleep = 1 })
des.monster({ id = "pixie", x = 10, y = 09, peaceful = 0 })
des.monster({ id = "quickling", x = 10, y = 09, asleep = 1 })
des.monster({ id = "quickling", x = 10, y = 09, peaceful = 0 })

-- all around

-- Monsters
for i = 1, 8 do
   des.monster({ id = "black light", peaceful = 0 })
end
for i = 1, 8 do
   if percent(50) then
      des.monster({ id = "black light", peaceful = 0 })
   end
end
for i = 1, 4 do
   des.monster({ id = "shadow", peaceful = 0 })
end
for i = 1, 4 do
   if percent(40) then
      des.monster({ id = "shadow", peaceful = 0 })
   end
end

-- Traps
for i = 1, 8 do
   des.trap("sleep gas")
end
for i = 1, 4 do
   if percent(50) then
      des.trap("sleep gas")
   end
end
des.trap("anti magic")
des.trap("anti magic")
if percent(50) then des.trap("anti magic") end
if percent(50) then des.trap("anti magic") end

-- Engravings
-- (the source asks for a random engraving type)
local etypes = { "dust", "engrave", "burn", "mark", "blood" }
des.engraving({ type = etypes[math.random(#etypes)], text = "You can feel eyes on your back." })
des.engraving({ type = etypes[math.random(#etypes)], text = "I can see you..." })

-- doors
des.door("locked",30,07)

des.door("locked",48,02)
des.door("locked",52,02)
des.door("locked",46,04)
des.door("locked",50,04)
des.door("locked",54,04)
des.door("locked",48,06)
des.door("locked",52,06)
des.door("locked",50,08)
des.door("locked",54,08)
des.door("locked",52,10)
des.door("locked",50,12)
des.door("locked",54,12)
des.door("locked",44,14)
des.door("locked",48,14)
des.door("locked",52,14)
des.door("locked",42,16)
des.door("locked",46,16)
des.door("locked",50,16)
des.door("locked",54,16)
des.door("locked",44,18)
des.door("locked",48,18)
des.door("locked",52,18)

-- The mazes (see above)
des.mazewalk(74,01,"south")
des.mazewalk(10,09,"south")
