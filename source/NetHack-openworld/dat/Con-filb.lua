-- NetHack Convict Con-filb.lua
--	Convict role by Karl Garrison (Convict patch); quest levels as in
--	SLASH'EM/SLASH'EM Extended, EvilHack, Hack'EM and SpliceHack.
--	Ported from SpliceHack's Con-filb.lua (cross-checked with the
--	EvilHack and Hack'EM Convict.des).
-- NetHack may be freely redistributed.  See license for details.
--
--
--	The lower filler levels for the quest: unlit mine tunnels.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "hardfloor")
des.level_init({ style="mines", fg="#", bg=" ", smoothed=true, joined=true, lit=0, walled=false })
des.message("This appears to be a prison level that is still under construction.")

--
des.stair("up")
des.stair("down")
-- Peaceful miners
des.monster({ id = "miner", peaceful=1 })
des.monster({ id = "miner", peaceful=1 })
des.monster({ id = "miner", peaceful=1 })
des.monster({ id = "miner", peaceful=1 })
des.monster({ id = "miner", peaceful=1 })
des.monster({ id = "miner", peaceful=1 })
des.monster({ id = "miner", peaceful=1 })
des.monster({ id = "miner", peaceful=1 })
-- Earth creatures
des.monster("xorn")
des.monster("earth elemental")
if percent(50) then
   des.monster("xorn")
end
if percent(50) then
   des.monster("earth elemental")
end
-- Other nasties
des.monster("lurker above")
des.monster("trapper")
if percent(50) then
   des.monster("lurker above")
end
if percent(50) then
   des.monster("trapper")
end
if percent(50) then
   des.monster("rock piercer")
end
if percent(50) then
   des.monster("rock piercer")
end
if percent(50) then
   des.monster("iron piercer")
end
if percent(50) then
   des.monster("iron piercer")
end
if percent(50) then
   des.monster("glass piercer")
end
if percent(50) then
   des.monster("glass piercer")
end
-- Tools and corpses
if percent(50) then
   des.object("pick-axe")
end
-- (the references' "lantern" is this game's "brass lantern")
if percent(75) then
   des.object("brass lantern")
end
if percent(50) then
   des.object("(")
end
-- (SpliceHack's des.object({"corpse", montype = "miner"}) would ignore
-- the unkeyed "corpse" and make a random object; use id = "corpse")
if percent(25) then
   des.object({ id = "corpse", montype = "miner" })
end
if percent(25) then
   des.object({ id = "corpse", montype = "miner" })
end
if percent(25) then
   des.object({ id = "corpse", montype = "miner" })
end
if percent(25) then
   des.object({ id = "corpse", montype = "miner" })
end
-- Natural cavern hazards
des.trap("pit")
des.trap("pit")
des.trap("pit")
des.trap("pit")
des.trap("pit")
des.trap("pit")
des.trap("falling rock")
des.trap("falling rock")
des.trap("falling rock")
des.trap("falling rock")
des.trap("web")
des.trap("web")
