-- NetHack: Open World  beholder.lua
--       SCCS Id: @(#)beholder.des  3.4     1993/02/23
--       Copyright (c) 1989 by Jean-Christophe Collet
--       Copyright (c) 1991 by M. Stephenson
-- Converted from Slash'EM beholder.des for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.
--
--	The Beholder's dungeon.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel")

des.map({ halign = "center", valign = "center", map = [[
                                                 |----
                |--------|                  |-----...|
                |........|------------------|........|
                |........+...........................|
                |........|---------|..|-----|........|
                |........|         |..|     -------|.|             ---
                ----------        -|..|            |.|         ----|.|
                                  |..-|     |--- ---.|---------|.....---
                      |---|   |---|..|     -|..|-|.....................|
                    -|-...----|......|-    |.......------------........|
                    |............--|..|-| -|....---|          |........|
                    |.....-------| -|...|--.....|-            --|...----
                    |-----|         -|...........|              ----|
                                     |-----|....|-
                                           ------
]] });
--ROOM: "ordinary" , lit, random, random, (11,09)
des.door("closed",25,03)
des.feature("fountain", 52,01)
-- The source has both an up staircase and the branch at (45,12); only the
-- branch is kept (it is the way back to the open world).
des.levregion({ region = {45,12,45,12}, type = "branch" })
des.trap("spiked pit",26,03)
des.trap("spiked pit",28,03)
des.trap("spiked pit",30,03)
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object("chest",17,04)
des.gold({ x = 17, y = 04 })
des.gold({ x = 17, y = 04 })
des.gold({ x = 17, y = 04 })
des.gold({ x = 17, y = 04 })
des.gold({ x = 17, y = 04 })
des.monster("Beholder", 17,04)
for i = 1, 37 do
   des.monster("gas spore")
end
des.monster()
des.monster()
des.monster()
des.monster()
