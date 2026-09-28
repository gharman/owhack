-- NetHack Convict Con-goal.lua
--	Convict role by Karl Garrison (Convict patch); quest levels as in
--	SLASH'EM/SLASH'EM Extended, EvilHack, Hack'EM and SpliceHack.
--	Ported from SpliceHack's Con-goal.lua (cross-checked with the
--	EvilHack and Hack'EM Convict.des).
-- NetHack may be freely redistributed.  See license for details.
--
--
--	The "goal" level for the quest.
--
--	Here you meet Warden Arianna, your nemesis monster.  You have to
--	defeat Warden Arianna in combat to gain the artifact you have
--	been assigned to retrieve.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "hardfloor")
--123456789012345678901234567890123456789012345678901234567890123456789012345
des.map({ halign = "left", valign = "top", map = [[
---------------------------------------------------------
|...|        |............................|             |
|...|       --............................|             |
|...|       |.............................|             |
|...|      --.............................|             |
|...|      |..............................|             |
|...|     --...................L..........|             |
|...|     |....................L..........|             |
|...|    --...................L.L.........|             |
|...|    |..............L.L.L.L.L.L.L.L...|             |
|...|-----................L..L...L..L.....|             |
|...........................L.L.L.L.......|             |
|...........................L.L.L.L.......|             |
|..........................L.L...L.L......|             |
|.........................................|-------------|
|.........................................|.............|
|.........................................S.............|
|.........................................|.............|
|.........................................|.............|
---------------------------------------------------------
]] });
-- Dungeon Description
des.region({ region = {00,00,56,19}, lit=1 })
-- Stairs
des.stair("up", 02,02)
-- Non diggable walls
des.non_diggable(selection.area(00,00,56,19))
-- Random traps
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
des.trap("fire")
-- Lava demons
-- (EvilHack and Hack'EM also add two salamanders at (29,10) and (33,10);
-- SpliceHack and SlashTHEM do not.)
des.monster({ id = "lava demon", x=30, y=05, peaceful=0, asleep=0 })
des.monster({ id = "lava demon", x=23, y=09, peaceful=0, asleep=0 })
des.monster({ id = "lava demon", x=39, y=09, peaceful=0, asleep=0 })
des.monster({ id = "lava demon", x=36, y=14, peaceful=0, asleep=0 })
des.monster({ id = "lava demon", x=26, y=14, peaceful=0, asleep=0 })
-- Elite guard
des.monster({ id = "iron golem", x=04, y=13, peaceful=0 })
-- Objects
-- (the references have "The Iron Ball of Liberation", a heavy iron ball,
-- or EvilHack's "The Striped Shirt of Liberation"; this game's Convict
-- quest artifact is The Iron Spoon of Liberation, placed as Hack'EM does)
des.object({ id = "spoon", x=31, y=10, buc="blessed", spe=0,
             name="The Iron Spoon of Liberation" })
des.object({ id = "chest", x=55, y=18, buc="blessed" })
-- Warden Arianna
des.monster({ id = "Warden Arianna", x=31, y=10, peaceful=0 })
