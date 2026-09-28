-- NetHack: Open World  frnknstn.lua
--	SCCS Id: @(#)frnknstn.des	3.1	98/NOV/11
--	1998,  Robin Johnson
--	Copyright (c) 1991 by M. Stephenson
-- Converted from Slash'EM frnknstn.des for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.
--
-- Doctor Frankenstein's laboratory
--
des.level_init({ style = "mazegrid", bg = "-" });

des.level_flags("mazelevel", "hardfloor")
-- noteleport would render the quantummechs a bit useless here

des.map({ halign = "center", valign = "center", map = [[
----------------------------.
|..........................|.
|.-----------------------|.|.
|.|......................|.|.
|.|.--------------------.|.|.
|.|.|....|.............|.|.|.
|.S.|....S.............S.|.S.
|.|.|....|.............|.|.|.
|.|.--------------------.|.|.
|.|......................|.|.
|.------------------------.|.
|..........................|.
----------------------------.
]] });
-- The source also had an up staircase levregion identical to the branch
-- one; only the branch is kept (it is the way back to the open world).
des.levregion({ region = {01,00,79,20}, region_islev = 1, exclude = {0,0,28,12}, type = "branch" })
des.stair("down", 05,06)
des.mazewalk(28,05,"east")
-- Undiggable walls
des.non_diggable(selection.area(00,00,11,12))
des.non_diggable(selection.area(11,00,21,00))
des.non_diggable(selection.area(11,10,27,12))
des.non_diggable(selection.area(21,00,27,10))
-- Frankenstein and his bodyguard
des.monster({ id = "Doctor Frankenstein", x = 06, y = 06, asleep = 1 })
des.monster("flesh golem", 06,05)
des.monster("flesh golem", 06,07)
des.monster("flesh golem", 05,06)
des.monster("flesh golem", 07,06)
des.monster("genetic engineer", 05,05)
des.monster("genetic engineer", 05,07)
des.monster("quantum mechanic", 07,05)
des.monster("quantum mechanic", 07,07)
-- Golems guarding the lab
des.monster("'", 19,05)
des.monster("'", 20,06)
des.monster("'", 21,07)
des.monster("'", 19,05)
des.monster("'", 20,06)
des.monster("'", 21,07)
des.monster("'", 19,05)
des.monster("'", 20,06)
des.monster("'", 21,07)
-- Frankenstein's treasure
des.object("ice box", 06,06)
-- Geddit?
-- Some more roamers
des.monster("Frankenstein's Monster")
des.monster("genetic engineer")
des.monster("genetic engineer")
des.monster("quantum mechanic")
des.monster("quantum mechanic")
des.monster("'")
des.monster("'")
des.monster("'")
des.monster("'")
-- Some extra random monsters
des.monster()
des.monster()
des.monster()
des.monster()
-- Squeaky boards
des.trap("board", 08,05)
des.trap("board", 08,06)
des.trap("board", 08,07)
des.trap("board", 22,05)
des.trap("board", 22,06)
des.trap("board", 22,07)
-- Randomly-placed traps
des.trap("spiked pit")
des.trap("anti magic")
des.trap("magic")
des.trap("polymorph")
-- Some random treasure
des.object("!")
des.object("!")
des.object("?")
des.object("?")
des.object("/")
des.object("/")
des.object("+")
des.object("+")
