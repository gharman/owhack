-- NetHack Infidel Inf-goal.lua
--	Infidel role by Tomsod, for EvilHack.
--	Ported from EvilHack's Infidel.des (cross-checked with Hack'EM's).
-- NetHack may be freely redistributed.  See license for details.
--
--
--	The "goal" level for the quest.
--
--	In this part of the Howling Forest the Paladin awaits you for a duel
--	amidst some ancient ruins.  Kill her to claim the Idol of Moloch!
--
--	Note: some may find the Paladin a tough opponent.  It's intentional!
--	You come here to duel her at HER behest, on HER conditions.
--	She expects to defeat you and came prepared.  To win, you need to
--	outwit her.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "hardfloor")

des.level_init({ style = "mines", fg = ".", bg = "T", smoothed = true,
                 joined = true, lit = 0, walled = true })

--         1         2
--1234567890123456789012345678
des.map({ halign = "half-left", valign = "center", map = [[
xxxxxxxxxx........xxxxxxxxxx
xxxxxxx..............xxxxxxx
xxxx....................xxxx
xx........--..-...........xx
x.........|.....|..........x
.............--.|...........
x........--................x
xx........|..|...--.......xx
xxxx.........|..........xxxx
xxxxxxx..............xxxxxxx
xxxxxxxxxx........xxxxxxxxxx
]], contents = function()
   -- The Paladin and her entourage.
   des.monster({ id = "Paladin", x = 13, y = 06, peaceful = 0 })
   des.object({ id = "figurine", x = 13, y = 06, buc = "cursed",
                montype = "horned devil", name = "The Idol of Moloch" })
   des.monster({ id = "templar", x = 13, y = 03, asleep = 1 })
   des.monster({ id = "templar", x = 15, y = 04, asleep = 1 })
   des.monster({ id = "templar", x = 17, y = 06, asleep = 1 })
   des.monster({ id = "aligned cleric", x = 16, y = 08, align = "law",
                 peaceful = 0, asleep = 1 })
   des.monster({ id = "templar", x = 13, y = 09, asleep = 1 })
   des.monster({ id = "templar", x = 10, y = 08, asleep = 1 })
   des.monster({ id = "templar", x = 09, y = 05, asleep = 1 })
   des.monster({ id = "aligned cleric", x = 11, y = 04, align = "law",
                 peaceful = 0, asleep = 1 })

   -- Just pretend they're tripwires.
   -- (circle/ellipse selections are outlines, as in the reference)
   local around = selection.filter_mapchar(selection.ellipse(13, 05, 9, 5)
                                  & selection.ellipse(13, 05, 4, 3):negate(),
                                           ".")
   des.trap("board", around:rndcoord())
   des.trap("board", around:rndcoord())
   des.trap("board", around:rndcoord())
   des.trap("board", around:rndcoord())

   -- There's still some treasure buried in the ruins.
   local ruins = selection.circle(13, 06, 4)
   des.object({ id = "gold piece", quantity = d(10,100), buried = true,
                coord = ruins:rndcoord() })
   des.object({ id = "gold piece", quantity = d(10,100), buried = true,
                coord = ruins:rndcoord() })
   des.object({ class = "*", buried = true, coord = ruins:rndcoord() })
   des.object({ class = "*", buried = true, coord = ruins:rndcoord() })
   des.object({ class = "*", buried = true, coord = ruins:rndcoord() })
   if percent(60) then
      des.object({ class = "=", buried = true, coord = ruins:rndcoord() })
   end
   if percent(50) then
      des.object({ class = "=", buried = true, coord = ruins:rndcoord() })
   end
   if percent(40) then
      des.object({ class = "\"", buried = true, coord = ruins:rndcoord() })
   end
end });

-- The surrounding woods.
-- (from here on, as after the reference's NOMAP, coordinates are relative
-- to the whole level again; the reference's stair region (45,00,79,20)
-- is given here in absolute level coordinates, clipped to the level)
des.levregion({ region = {46,00,79,20}, region_islev = 1, type = "stair-up" })
des.monster("werewolf")
des.monster("werewolf")
des.monster("werewolf")
des.monster("werewolf")
for i = 1, d(5,4) do
   des.monster("d")
end
des.monster("u")
des.monster("u")
des.monster("u")
if percent(80) then
   des.monster("forest centaur")
end
if percent(50) then
   des.monster("woodchuck")
end

-- And a bit of random junk.
des.object()
des.object()
des.object()
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
des.trap()
