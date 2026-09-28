-- NetHack: Open World  caveend.lua
--       SCCS Id: @(#)caves.des  3.4     1993/02/23
--       Copyright (c) 1989 by Jean-Christophe Collet
--       Copyright (c) 1991 by M. Stephenson
-- Converted from Hack'EM caves.des ("caveend") for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.
--
-- The dragon pit at the bottom of the Wyrm Caves
--
des.level_flags("noteleport")

-- Hack'EM terrain: dead trees ('t') are ordinary trees ('T') and sewage
-- ('s') is plain floor ('.') here.
des.map({ halign = "center", valign = "center", map = [[
         -TTTTT.......TTTTTTTTTT--     -T}}}}}}}}}.----TTTTTTTTTTTTT--      
-------  |TT.T..........TTTTT....----  |}}}}}}}}...||.TTTTTTTTTTTTT..---    
|.TTTT-- --................TT.......-----}}}}}}...---....TTTTTT........---  
|..TT..| --..........TT...............---}}}}}}...||.......T.............---
-..T...|--.....T........................}}}}}}....--.................T.....|
T.TT...--TT...TTT.........---...........}}}}}}.............................|
...TT..................TTT|--..........}}}}}}}........--............T......|
T...T...............-------|..........}}}}}}}}.......-------...............-
....T...TT---.....---      -----.....}}}}}}}}......--- -----...PPP......TT..
T.......T----.....------  -------...}}}}}}}}.......-----.........PPP.....T..
-T.......|--T........TT----...---...}}}}}}}}.............................TT.
|TT....---|..T.......TTTTT.........}}}}}}}}..----TT.........................
--------  --........TTT...........}}}}}}}}}-------........TTTT..............
-------    --.......T.P...........}}}}}}}}}----T----.....TTTT...............
-T....---------.....PPP..........}}}.}}}}}}.......|--....TT......--T......--
T.......--.TT--....PPPP.........}}}}.}}}}}}......----...........--|T......--
T.....................PP........}}}}..}}}}}......---............|--TT......-
.....--...............PPPTTT...}}}}}..}}}}.....................--|.T........
.....--...T............TTTTT..}}}}}...}}}}...........T........-- |..........
-.........TT..........TTTTT...}}}}...}}}}}..........TT.......--  --.........
---.....TTTTTT...TTTTTTTTT...}}}}...}}}}}}......TTTTTTTTTT.---    ----......
]] })


des.stair("up", 73, 18)

-- dragon hoard
des.object("*", 01, 02)
des.gold({ amount = 600 + d(12,100), x = 01, y = 02 })

if percent(60) then des.object({ id = "gain ability", class = "!", x = 01, y = 03 }) end
if percent(80) then des.object("=", 01, 03) end
if percent(40) then des.object("\"", 01, 03) end
des.object("*", 01, 03)
des.gold({ amount = 600 + d(10,100), x = 01, y = 03 })

if percent(60) then des.object({ id = "gain level", class = "!", x = 02, y = 03 }) end
if percent(80) then des.object("=", 02, 03) end
if percent(40) then des.object("\"", 02, 03) end
des.object("*", 02, 03)
des.gold({ amount = 600 + d(10,100), x = 02, y = 03 })

if percent(60) then des.object({ id = "full healing", class = "!", x = 01, y = 04 }) end
if percent(80) then des.object("=", 01, 04) end
if percent(40) then des.object("\"", 01, 04) end
des.object("*", 01, 04)
des.gold({ amount = 600 + d(10,100), x = 01, y = 04 })

if percent(60) then des.object({ id = "enlightenment", class = "!", x = 02, y = 04 }) end
if percent(80) then des.object("=", 02, 04) end
if percent(40) then des.object("\"", 02, 04) end
des.object("*", 02, 04)
des.gold({ amount = 600 + d(10,100), x = 02, y = 04 })
des.gold({ amount = 400 + d(10,100), x = 01, y = 05 })
des.gold({ amount = 200 + d(5,100), x = 00, y = 06 })
des.gold({ amount = 200 + d(5,100), x = 01, y = 06 })
des.gold({ amount = 200 + d(5,100), x = 02, y = 06 })
des.gold({ amount = 100 + d(5,100), x = 02, y = 07 })

for i = 1, d(2,10) do
   des.gold({ amount = d(100) })
end

des.object("boulder", 01, 05)

for i = 1, 12 do
   des.object("*")
end
for i = 1, 3 do
   des.object("(")
   des.object(")")
   des.object("!")
   des.object("?")
end
for i = 1, 5 do
   des.object()
end

-- (the source also had shimmering, deep, violet and sea dragons here,
-- 45% each; this game does not have them)
if percent(45) then des.monster({ id = "gray dragon", peaceful = 0 }) end
if percent(45) then des.monster({ id = "silver dragon", peaceful = 0 }) end
if percent(45) then des.monster({ id = "red dragon", peaceful = 0 }) end
if percent(45) then des.monster({ id = "white dragon", peaceful = 0 }) end
if percent(45) then des.monster({ id = "orange dragon", peaceful = 0 }) end
if percent(45) then des.monster({ id = "black dragon", peaceful = 0 }) end
if percent(45) then des.monster({ id = "blue dragon", peaceful = 0 }) end
if percent(45) then des.monster({ id = "green dragon", peaceful = 0 }) end
if percent(45) then des.monster({ id = "gold dragon", peaceful = 0 }) end
if percent(45) then des.monster({ id = "yellow dragon", peaceful = 0 }) end
if percent(45) then des.monster({ id = "wyvern", peaceful = 0 }) end
if percent(45) then des.monster({ id = "hydra", peaceful = 0 }) end

-- (the source has a commented-out Crassus the Young Ancient Dragon at
-- (01,06); this game does not have that monster)

-- (the source's list also had baby shimmering, sea, deep and violet
-- dragons, which this game does not have)
local mon_names = {
   "baby red dragon",           "baby white dragon",
   "baby yellow dragon",        "baby blue dragon",
   "baby green dragon",         "baby gold dragon",
   "baby gray dragon",          "baby silver dragon",
   "baby orange dragon",        "baby black dragon"
}


-- 15 baby dragons, each one picked at random from the above list
for i = 1, 15 do
   des.monster({ id = mon_names[math.random(#mon_names)], peaceful = 0 })
end

-- 20 random dragon eggs
for i = 1, 20 do
   des.object({ id = "egg", montype = "D" })
end

for i = 1, 6 do
   if percent(40) then des.monster({ class = "w", peaceful = 0 }) end
end

for i = 1, 4 do
   des.trap()
end
