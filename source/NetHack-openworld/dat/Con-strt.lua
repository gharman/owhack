-- NetHack Convict Con-strt.lua
--	Convict role by Karl Garrison (Convict patch); quest levels as in
--	SLASH'EM/SLASH'EM Extended, EvilHack, Hack'EM and SpliceHack.
--	Ported from SpliceHack's Con-strt.lua (cross-checked with the
--	EvilHack and Hack'EM Convict.des).
-- NetHack may be freely redistributed.  See license for details.
--
--
--	The "start" level for the quest.
--
--	Here you meet your (besieged) class leader, Robert the Lifer
--	and receive your quest assignment.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noteleport", "hardfloor")
--123456789012345678901234567890123456789012345678901234567890123456789012345
des.map({ halign = "left", valign = "top", map = [[
|--------------------------------------------------------|-----------------|
|....|...|...|...|...|...|...|...|...|...|...|...|...|...|................K|
|....|...|...|...|...|...|...|...|...|...|...|...|...|...|.................|
|---.---.---.---.---.---.---.---.---.---.---.---.---.---.|.................|
|..........................................................................|
|..........................................................................|
|....|.---.---.---.---.---.---.---.---.---.---.---.---.--------------..----|
|....|...|...|...|...|...|...|...|...|...|...|...|...|...|.................|
|....|...|...|...|...|...|...|...|...|...|...|...|...|...|.................|
|....|---------------------------------------------------|.................|
|....|...|...|...|...|...|...|...|...|...|...|...|...|...|.................|
|....|...|...|...|...|...|...|...|...|...|...|...|...|...|.................|
|....|--.---.---.---.---.---.---.---.---.---.---.---.---.|-----------------|
|..........................................................................|
|..........................................................................|
|..........................................................................|
|.----.---.---.---.---.---.---.---.---.---.---.---.---.--|.................|
|....|...|...|...|...|...|...|...|...|...|...|...|...|...|.................|
|....|...|...|...|...|...|...|...|...|...|...|...|...|...|.................|
|--------------------------------------------------------|-----------------|
]] });
-- Dungeon Description
des.region(selection.area(00,00,75,19), "lit")
-- Stairs
des.stair("down", 64,08)
-- Portal arrival point
des.levregion({ region = {71,03,71,03}, type="branch" })
-- Altar
des.altar({ x=70, y=16, align="chaos", type="shrine" })
-- (EvilHack and Hack'EM also put a magic chest at (71,16); this game has
-- no magic chests, and SpliceHack omits it too.)
-- Robert the Lifer
-- (SpliceHack places him twice, once plainly and once with this
-- inventory; he is unique, so only the second placement is kept.)
des.monster({ id = "Robert the Lifer", coord = {74, 18}, inventory = function()
   des.object({ id = "stiletto", spe = 4, buc = "cursed" });
   des.object({ id = "striped shirt", spe = 4, buc = "cursed" });
end })
-- fellow prisoners
des.monster("inmate")
des.monster("inmate")
des.monster("inmate")
des.monster("inmate")
des.monster("inmate")
des.monster("inmate")
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
if percent(50) then
   des.monster("prison guard")
end
if percent(50) then
   des.monster("prison guard")
end
-- Good `ol mimics
des.monster({ id = "giant mimic", x=74, y=05, appear_as = "ter:staircase up" })
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
if percent(50) then
   des.object("heavy iron ball")
end
if percent(50) then
   des.object("heavy iron ball")
end
-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))
