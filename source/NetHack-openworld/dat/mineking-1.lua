-- NetHack: Open World  mineking-1.lua
--	SCCS Id: @(#)mines.des	3.4	2002/05/02
--	Copyright (c) 1989-95 by Jean-Christophe Collet
--	Copyright (c) 1991-95 by M. Stephenson
-- Converted from Slash'EM mines.des (level "mineking") for NetHack 5.0,
-- with additions from Hack'EM's "mineking-1".
-- NetHack may be freely redistributed.  See license for details.
--
--    Ruggo the Gnome King's own special level
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel")

des.map({ halign = "center", valign = "center", map = [[

                   #                      #                  #
                  ##                    #####          #######
                  #                         #          #     #
    ###############  ###           ######   #      #####     ########
    #             ####             #        #      #
    #          ####      #####################    ##  -----------      ###
  #########    #  ########         #         #     #  |....\....|      #
         #     #              ######       ###     #  |.........|   ####
        ##     #              #           ## #######  |.........|  ##  #
        #      ####   #       ########    #  #     #  -----+-----      #
               #      #########      #    #  #             #           #
          #######          #  #  #####       ###############       #####
          #  #       ########    #        #    #       #           #   #
             #       #        ######     #########    ##############
                     #     ####  #       #       #           #
                           #                                 #
]] });
local place = { {19,1},{42,1},{61,1},{21,15},{41,15},{61,16} }
shuffle(place)
-- only place[1] is currently used
des.stair("up", 35,06)
--des.levregion({ region = {35,06,35,06}, type = "branch" })
des.door("closed",59,10)
-- 40 random gems all around...
for i = 1, 24 do
   des.object("*")
end
des.object("luckstone")
for i = 1, 15 do
   des.object("*")
end
-- (Hack'EM adds a healthstone here; 5.0 has no healthstones.)
--Pickaxe in case of trappedness on Wine Cellar Mine's end
des.object("pick-axe", place[1][1], place[1][2])
--20 bunches of gold all around...
for i = 1, 20 do
   des.gold()
end

-- throne room
des.monster({ id = "Ruggo the Gnome King", x = 59, y = 7, peaceful = 0 })
des.object(")",59,7)
des.object("/",59,7)
des.object("!",59,7)
des.object("!",59,7)
des.object("[",59,7)
des.monster({ class = "G", x = 55, y = 7, peaceful = 0 })
des.monster({ class = "G", x = 56, y = 7, peaceful = 0 })
des.monster({ class = "G", x = 57, y = 7, peaceful = 0 })
des.monster({ class = "G", x = 58, y = 7, peaceful = 0 })
des.monster({ class = "G", x = 60, y = 7, peaceful = 0 })
des.monster({ class = "G", x = 61, y = 7, peaceful = 0 })
des.monster({ class = "G", x = 62, y = 7, peaceful = 0 })
des.monster({ class = "G", x = 63, y = 7, peaceful = 0 })
des.monster({ class = "G", x = 55, y = 8, peaceful = 0 })
des.monster({ class = "G", x = 56, y = 8, peaceful = 0 })
des.monster({ class = "G", x = 57, y = 8, peaceful = 0 })
des.monster({ class = "G", x = 58, y = 8, peaceful = 0 })
des.monster({ class = "G", x = 59, y = 8, peaceful = 0 })
des.monster({ class = "G", x = 60, y = 8, peaceful = 0 })
des.monster({ class = "G", x = 61, y = 8, peaceful = 0 })
des.monster({ class = "G", x = 62, y = 8, peaceful = 0 })
des.monster({ class = "G", x = 63, y = 8, peaceful = 0 })
des.monster({ class = "G", x = 55, y = 9, peaceful = 0 })
des.monster({ class = "G", x = 56, y = 9, peaceful = 0 })
des.monster({ class = "G", x = 57, y = 9, peaceful = 0 })
des.monster({ class = "G", x = 58, y = 9, peaceful = 0 })
des.monster({ class = "G", x = 59, y = 9, peaceful = 0 })
des.monster({ class = "G", x = 60, y = 9, peaceful = 0 })
des.monster({ class = "G", x = 61, y = 9, peaceful = 0 })
des.monster({ class = "G", x = 62, y = 9, peaceful = 0 })
des.monster({ class = "G", x = 63, y = 9, peaceful = 0 })
-- the mine workers
for i = 1, 20 do
   des.monster({ id = "gnome", peaceful = 0 })
end
for i = 1, 11 do
   des.monster({ id = "gnome warrior", peaceful = 0 })
end
-- From Hack'EM: six deep gnomes (gnome lords here) and two gnomish wizards
for i = 1, 6 do
   des.monster({ id = "gnome lord", peaceful = 0 })
end
des.monster({ id = "gnomish wizard", peaceful = 0 })
des.monster({ id = "gnomish wizard", peaceful = 0 })
