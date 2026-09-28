-- NetHack: Open World  cavebegn.lua
--       SCCS Id: @(#)caves.des  3.4     1993/02/23
--       Copyright (c) 1989 by Jean-Christophe Collet
--       Copyright (c) 1991 by M. Stephenson
-- Converted from Hack'EM caves.des ("cavebegn") for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.
--
-- Cave entrance (inspired by dnh Erebor goal level)
--
des.level_init({ style = "solidfill", fg = " ", lit = 0 })

des.level_flags("mazelevel", "noteleport", "hardfloor")

-- Hack'EM's dead trees ('t') are ordinary trees ('T') here.
des.map({ halign = "center", valign = "center", map = [[
                                      ..
                                     ....
                                     .....
                                    .....
                                   .....
                                    .T....
                                    .....T
                                 .......T
                                 ...T....
                                  .........
                                .....T....
                                   ..........
                                  ..........
                               ...........
                                 ....T........
                             ...............
                            ................
                              .....T...........
                                ......T..........
                                 .................
]] })

-- Dungeon Description
des.region(selection.area(00,00,74,19), "lit")
-- des.teleport_region({ region = {00,00,70,01}, region_islev = 1, exclude = {0,0,0,0}, exclude_islev = 1, dir = "down" })

des.engraving({ x = 38, y = 2, type = "burn", text = "No entry! Stay oot!! Orderz uv Grund!" })

-- Stairs
-- The source also had an up staircase on the branch spot; only the branch
-- is kept (it is the way back to the open world).
des.stair("down", 49, 19)
des.levregion({ region = {38,1,38,1}, type = "branch" })

-- Downstairs blocked by a few boulders

des.object("boulder", 44, 19)
des.object("boulder", 45, 18)
des.object("boulder", 48, 19)
des.object("boulder", 48, 18)
des.object("boulder", 49, 19)
des.object("rock", 43, 18)
des.object("rock", 40, 18)
for i = 1, 12 do
   des.object("rock")
end

-- Some random debris
-- Some cave guards
des.monster("orc-captain", 41, 19)
des.monster("orc shaman", 41, 19)

for i = 1, 4 do
   des.monster("hill orc", 41, 19)
end
