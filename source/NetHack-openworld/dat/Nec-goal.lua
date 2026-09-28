-- NetHack Necromancer Nec-goal.lua
--	Copyright (c) 1992 by David Cohrs
-- NetHack may be freely redistributed.  See license for details.
--
--
--	The "goal" level for the quest.
--
--	Here you meet Maugneshaagar, your nemesis monster.  You have to
--	defeat Maugneshaagar in combat to gain the artifact you have
--	been assigned to retrieve.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel");

des.map([[
                                                                            
                                                                            
                                                                            
                   -------------                 -------------              
                   |...........|                 |...........|              
            -------|...........-------------------...........|              
            |......S...........|..|..|..|..|..|..|...........|              
            |......|...........|..|..|..|..|..|..|...........|              
            |......|...........--+--+--+--+--+--+-...........|              
            --S----|...........S.................+...........|              
            |......|...........--+--+--+--+--+--+-...........|              
            |......|...........|..|..|..|..|..|..|...........|              
            |......|...........|..|..|..|..|..|..|...........|              
            -------|...........-------------------...........|              
                   |...........|                 |...........|              
                   -------------                 -------------              
                                                                            
                                                                            
                                                                            
                                                                            
]]);
-- Dungeon Description
des.region({ region={13,10,18,12}, lit=0, type="temple", filled=2 })
des.region(selection.area(13,06,18,08), "lit")
des.region(selection.area(20,04,30,14), "unlit")
des.region(selection.area(32,06,33,07), "unlit")
des.region(selection.area(35,06,36,07), "unlit")
des.region(selection.area(38,06,39,07), "unlit")
des.region(selection.area(41,06,42,07), "unlit")
des.region(selection.area(44,06,45,07), "unlit")
des.region(selection.area(47,06,48,07), "unlit")
des.region(selection.area(32,09,48,09), "unlit")
des.region(selection.area(32,11,33,12), "unlit")
des.region(selection.area(35,11,36,12), "unlit")
des.region(selection.area(38,11,39,12), "unlit")
des.region(selection.area(41,11,42,12), "unlit")
des.region(selection.area(44,11,45,12), "unlit")
des.region(selection.area(47,11,48,12), "unlit")
des.region(selection.area(50,04,60,14), "lit")
-- Doors
des.door("locked",19,06)
des.door("locked",14,09)
des.door("locked",31,09)
des.door("locked",33,08)
des.door("locked",36,08)
des.door("locked",39,08)
des.door("locked",42,08)
des.door("locked",45,08)
des.door("locked",48,08)
des.door("locked",33,10)
des.door("locked",36,10)
des.door("locked",39,10)
des.door("locked",42,10)
des.door("locked",45,10)
des.door("locked",48,10)
des.door("locked",49,09)
-- Stairs
des.stair("up", 55,05)
-- Non diggable walls
des.non_diggable(selection.area(00,00,75,19))
-- The altar of Moloch.  This is not a shrine.
des.altar({ x=16, y=11, align="noalign", type="altar" })
-- Objects
des.object({ id = "great dagger", x=16, y=11, buc="blessed", spe=0, name="The Great Dagger of Glaurgnaa" })
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
des.object()
-- Random traps
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
-- Random monsters.
des.monster("Maugneshaagar", 16, 11)
des.monster({ id = "mongbat", peaceful = 0 })
des.monster({ id = "mongbat", peaceful = 0 })
des.monster({ id = "mongbat", peaceful = 0 })
des.monster({ id = "mongbat", peaceful = 0 })
des.monster({ class = "&", peaceful = 0 })
des.monster({ class = "&", peaceful = 0 })
des.monster({ class = "&", peaceful = 0 })
des.monster({ class = "&", peaceful = 0 })
des.monster({ class = "&", peaceful = 0 })
des.monster({ class = "&", peaceful = 0 })
des.monster({ class = "&", peaceful = 0 })
des.monster({ class = "&", peaceful = 0 })
des.monster({ class = "&", peaceful = 0 })
des.monster({ id = "nupperibo", peaceful = 0 })
des.monster({ id = "nupperibo", peaceful = 0 })
des.monster({ id = "nupperibo", peaceful = 0 })
des.monster({ id = "nupperibo", peaceful = 0 })
des.monster({ id = "nupperibo", peaceful = 0 })
des.monster({ id = "nupperibo", peaceful = 0 })
des.monster({ id = "nupperibo", peaceful = 0 })
des.monster({ id = "nupperibo", peaceful = 0 })
des.monster({ id = "blood imp", peaceful = 0 })
des.monster({ id = "blood imp", peaceful = 0 })
des.monster({ id = "blood imp", peaceful = 0 })
des.monster({ id = "blood imp", peaceful = 0 })
des.monster({ id = "blood imp", peaceful = 0 })
des.monster({ id = "blood imp", peaceful = 0 })
des.monster({ id = "blood imp", peaceful = 0 })
