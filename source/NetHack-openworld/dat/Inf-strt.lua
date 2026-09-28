-- NetHack Infidel Inf-strt.lua
--	Infidel role by Tomsod, for EvilHack.
--	Ported from EvilHack's Infidel.des (cross-checked with Hack'EM's).
-- NetHack may be freely redistributed.  See license for details.
--
--
--	The "start" level for the quest.
--
--	Here you meet your class leader, the Archbishop of Moloch,
--	and receive an invitation to a duel with the Paladin.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noteleport", "hardfloor")

--         1         2         3         4         5         6
--12345678901234567890123456789012345678901234567890123456789012
des.map({ halign = "right", valign = "center", map = [[
                                    |.........................
                                    |.........................
                  -----             --........................
   ----         ---...-----         --........................
   |..|        --.........|         |.........................
   |..|        |..........|        --.........................
   -+--      ---..........----     |..........................
    #      ---...............|     --.........................
    #      |.................---    |.........................
 ---S-   ---...................|    |-........................
 |...|   |.....................+####S.........................
 |...+###+.....................|    |.........................
 |...|   |....................--    |.........................
 -----   ----.................|    --.........................
            |.................|    |..........................
     ---- ##S...............---   --..........................
     |..| # ---............--     |...........................
     |..+##   |........-----      --..........................
     |..|     ----------           |..........................
     |..|                          |-.........................
     ----                          |..........................
]] });
des.non_diggable(selection.area(00,00,37,20))

-- You arrive at a sparsely wooded cliffside.
des.replace_terrain({ region = {35,00,61,20},
                      fromterrain = ".", toterrain = "T", chance = 1 })
-- Portal arrival point
des.levregion({ region = {38,00,61,20}, type = "branch" })
local outside = selection.filter_mapchar(selection.area(35,00,61,20), ".")
for i = 1, d(3,4) do
   des.monster({ class = "d", coord = outside:rndcoord() })
end
if percent(20) then
   des.monster({ id = "black unicorn", coord = outside:rndcoord() })
end

-- The Hidden Temple is behind a secret door.
-- The altar is coaligned, but haunted,
-- presumably having been forcibly converted in the past.
des.trap("dart", 37, 10)
des.door("locked", 31, 10)
des.region({ region = {20,10,20,10}, lit = 1, type = "temple",
             irregular = 1 })
des.altar({ x = 20, y = 10, align = "coaligned", type = "altar" })
-- Magic chest
-- (EvilHack's MAGIC_CHEST, a shared-storage dungeon feature, doesn't
-- exist in this game; an empty ordinary chest stands in for it)
des.object({ id = "chest", x = 18, y = 10, contents = function() end })

-- Archbishop and his entourage
des.monster("Archbishop of Moloch", 20, 10)
des.monster("cultist", 20, 07)
des.monster("cultist", 23, 08)
des.monster("cultist", 24, 10)
des.monster("cultist", 23, 12)
des.monster("cultist", 20, 13)
des.monster("cultist", 17, 12)
des.monster("cultist", 16, 10)
des.monster("cultist", 17, 08)

-- Some "decorations".
local around_altar = selection.ellipse(20, 10, 4, 3)
des.object({ id = "corpse", montype = "elf", coord = around_altar:rndcoord() })
des.object({ id = "corpse", montype = "elf", coord = around_altar:rndcoord() })
des.object({ id = "corpse", montype = "elf", coord = around_altar:rndcoord() })
des.object({ id = "corpse", montype = "human", coord = around_altar:rndcoord() })
des.object({ id = "corpse", montype = "human", coord = around_altar:rndcoord() })
local statues = { {20,04}, {24,05}, {27,08}, {28,13},
                  {25,15}, {19,16}, {14,14}, {13,09} }
shuffle(statues)
des.object({ id = "statue", montype = "horned devil", coord = statues[1],
             contents = function() end })
des.object({ id = "statue", montype = "barbed devil", coord = statues[2],
             contents = function() end })
des.object({ id = "statue", montype = "marilith", coord = statues[3],
             contents = function() end })
des.object({ id = "statue", montype = "vrock", coord = statues[4],
             contents = function() end })
des.object({ id = "statue", montype = "hezrou", coord = statues[5],
             contents = function() end })
des.object({ id = "statue", montype = "bone devil", coord = statues[6],
             contents = function() end })
des.object({ id = "statue", montype = "ice devil", coord = statues[7],
             contents = function() end })
des.object({ id = "statue", montype = "pit fiend", coord = statues[8],
             contents = function() end })

-- Entrance to the underground complex leading to the Howling Forest.
des.door("closed", 09, 11)
des.door("closed", 05, 11)
des.region(selection.area(02,10,04,12), "lit")
des.stair("down", 03, 11)

-- Unholy water supply.
des.door("locked", 04, 06)
des.region(selection.area(04,04,05,05), "lit")
des.object({ id = "water", class = "!", buc = "cursed", quantity = d(1,2),
             x = 04, y = 04 })
des.object({ id = "water", class = "!", buc = "cursed", quantity = d(1,2),
             x = 05, y = 04 })

-- A small cache of valuables.
des.door("locked", 08, 17)
des.region(selection.area(06,16,07,19), "lit")
des.object({ coord = {06,16} })
des.object({ coord = {06,17} })
des.object("axe", 06, 18)
des.object({ coord = {06,19} })

-- Traps
des.trap({ coord = outside:rndcoord() })
des.trap({ coord = outside:rndcoord() })
des.trap({ coord = outside:rndcoord() })
