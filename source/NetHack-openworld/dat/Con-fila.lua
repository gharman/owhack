-- NetHack Convict Con-fila.lua
--	Convict role by Karl Garrison (Convict patch); quest levels as in
--	SLASH'EM/SLASH'EM Extended, EvilHack, Hack'EM and SpliceHack.
--	Ported from SpliceHack's Con-fila.lua (cross-checked with the
--	EvilHack and Hack'EM Convict.des).
-- NetHack may be freely redistributed.  See license for details.
--
--
--       The "fill" levels for the quest.
--
--       These levels are used to fill out any levels not occupied by specific
--       levels as defined above. "filla" is the upper filler, between the
--       start and locate levels, and "fillb" the lower between the locate
--       and goal levels.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "hardfloor")
--123456789012345678901234567890123456789012345678901234567890123456789012345
des.map({ halign = "left", valign = "top", map = [[
----------------------------------------------------------------------------
|....................---------.......................---------.............|
|....................F...|...|.......................F...|...|.............|
|....................|...|...F.......................|...|...F.............|
|....|---|---|.......|---|---|.......|---|---|.......|---|---|.............|
|....F...|...|.......F...|...|.......F...|...|.......F...|...|.............|
|....|...|...F.......|...|...F.......|...|...F.......|...|...F.............|
|....|---|---|.......|---|---|.......|---|---|.......|---|---|.............|
|....F...|...|.......F...|...|.......F...|...|.......F...|...|.............|
|....|...|...F.......|...|...F.......|...|...F.......|...|...F.............|
|....|---|---|.......|---|---|.......|---|---|.......|---|---|.............|
|........|...|.......F...|...|.......F...|...|.......F...|...|.............|
|....|...|...F.......|...|...F.......|...|...F.......|...|...F.............|
|....|---|---|.......|---|---|.......|---|---|.......|---|---|.............|
|....F...|...|.......F...|...|.......F...|...|.......F...|...|.............|
|....|...|...F.......|...|...........|...|...F.......|...|...F.............|
|....|---|---|.......|---|---|.......|---|---|.......|---|---|.............|
|........|...|.......................F...|...|.............................|
|....|...|...F.......................|...|...F.............................|
|--------------------------------------------------------------------------|
]] });
-- Dungeon Description
des.region(selection.area(00,00,75,19), "lit")
-- Stairs
des.stair("up", 74,03)
des.stair("down", 03,17)
-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))
-- "Regular" prisoners
des.monster({ id = "inmate", x=59, y=02 })
des.monster({ id = "inmate", x=55, y=08 })
des.monster({ id = "inmate", x=43, y=14 })
des.monster({ id = "inmate", x=38, y=05 })
des.monster({ id = "inmate", x=27, y=02 })
des.monster({ id = "inmate", x=23, y=08 })
des.monster({ id = "inmate", x=11, y=14 })
des.monster({ id = "inmate", x=06, y=05 })
-- Undead prisoners
des.monster({ id = "ghost", x=42, y=17, name="Orzo the Inmate" })
if percent(50) then
   des.monster({ id = "ghost", x=40, y=18, name="Fredgar the Inmate" })
end
if percent(50) then
   des.monster({ id = "ghost", x=06, y=12, name="Rastilon the Inmate" })
end
des.monster({ id = "skeleton", x=28, y=15, asleep=0 })
-- Bugs and snakes
des.monster({ id = "pit viper", x=06, y=17 })
des.monster("xan")
-- Corrupt guards
if percent(50) then
   des.monster("prison guard")
end
if percent(50) then
   des.monster("prison guard")
end
if percent(50) then
   des.monster("prison guard")
end
if percent(50) then
   des.monster("prison guard")
end
-- Random traps
des.trap("web")
des.trap("web")
des.trap("web")
des.trap("web")
-- Prison debris
if percent(75) then
   des.object("iron chain")
end
if percent(75) then
   des.object("iron chain")
end
if percent(75) then
   des.object("iron chain")
end
if percent(75) then
   des.object("iron chain")
end
if percent(75) then
   des.object("iron chain")
end
if percent(75) then
   des.object("heavy iron ball")
end
if percent(75) then
   des.object("heavy iron ball")
end
