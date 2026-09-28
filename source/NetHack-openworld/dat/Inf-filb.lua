-- NetHack Infidel Inf-filb.lua
--	Infidel role by Tomsod, for EvilHack.
--	Ported from EvilHack's Infidel.des (cross-checked with Hack'EM's).
-- NetHack may be freely redistributed.  See license for details.
--
--
--	The lower fillers are some nondescript areas of the Howling Forest.
--	There's a lot of werewolves and other d and perhaps a woodchuck.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "hardfloor")

des.level_init({ style = "mines", fg = ".", bg = "T", smoothed = true,
                 joined = true, lit = 0, walled = true })

-- (the reference's stair regions (45,00,79,20) and (00,00,34,20), which
-- are relative to its NOMAP, are given here in absolute level coordinates,
-- clipped to the level)
des.levregion({ region = {46,00,79,20}, region_islev = 1, type = "stair-up" })
des.levregion({ region = {01,00,35,20}, region_islev = 1, type = "stair-down" })

des.monster("werewolf")
des.monster("werewolf")
des.monster("werewolf")
des.monster("werewolf")
des.monster("werewolf")
for i = 1, d(6,4) do
   des.monster("d")
end
des.monster("u")
des.monster("u")
des.monster("u")
des.monster("u")
des.monster("forest centaur")
if percent(60) then
   des.monster("woodchuck")
end

des.object()
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
des.trap()
