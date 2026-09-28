-- NetHack Pirate Pir-goal.lua
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991-2 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
--	Shipwreck Island center
--
--	The "goal" level for the quest.
--
--	Here you meet Blackbeard's Ghost, your nemesis monster.  You have
--	to defeat Blackbeard's Ghost in combat to gain the artifact you
--	have been assigned to retrieve.
--
--	Ported from SpliceHack's Pir-goal.lua and SlashTHEM's Pirate.des.
--	The original level is drawn as two stacked maps; the first one only
--	serves to put Blackbeard's hoard at the heart of the caves.  Here
--	the final map is drawn once and the hoard is placed with a selection.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noteleport")

--0         1         2         3         4         5         6         7
--01234567890123456789012345678901234567890123456789012345678901234567890
des.map([[
                        ###                                         #  
#                      ###                  #                       ## 
###                   ##            .        ##                      ##
 ###                 ##            ###       ###        #           ## 
  ###                #           #H#H#HH       #         ##         #  
    ##        #                 H#  #  ##       #         ###      #   
     #       ##                 H ##H## H                  ###         
            ##                 ## #H#H# ##                  ###        
           ##                 .#H#H###H#H#.                 ##         
          ###                  ## #H#H# ##                 ##          
           ###                  H ##H## H                 ##     #     
   #        ###         #       ##  #  #H                 #      ##    
  #           ##         #       HH#H#H#           #              ###  
 ##             #        ###       ###            ##               ### 
##                        ##        .            ##                 ###
 ##                         #                  ###                    #
  #                                           ###                      
]]);
--01234567890123456789012345678901234567890123456789012345678901234567890
--0         1         2         3         4         5         6         7
-- Dungeon Description
des.region(selection.area(34,06,38,10), "lit")
-- Stairs
des.levregion({ region = {00,00,70,16}, exclude = {20,00,50,16}, type="stair-up" })

-- The original stocks the maze once, after all four walks; 5.0 stocks
-- it after every stocked walk, so only the last one is stocked here.
des.mazewalk({ x=36, y=02, dir="north", stocked=false })
des.mazewalk({ x=30, y=08, dir="west", stocked=false })
des.mazewalk({ x=42, y=08, dir="east", stocked=false })
des.mazewalk(36,14,"south")

-- Blackbeard's hoard, at the heart of the caves
local heart = selection.area(34,06,38,10) | selection.area(33,08,39,08)
heart = heart | selection.area(36,05,36,11)

des.object({ id = "chest", coord = {35,08},
             contents = function()
                des.object("$")
                des.object("$")
                des.object("*")
                des.object("*")
                des.object("*")
                des.object("*")
             end
})
des.object({ id = "chest", coord = {36,07},
             contents = function()
                des.object("$")
                des.object("$")
                des.object("*")
                des.object("*")
                des.object("*")
                des.object("*")
             end
})
des.object({ id = "chest", coord = {36,08},
             contents = function()
                des.object("$")
                des.object("$")
                des.object("*")
                des.object("*")
                des.object("*")
                des.object("*")
             end
})
des.object({ id = "chest", coord = {36,09},
             contents = function()
                des.object("$")
                des.object("$")
                des.object("*")
                des.object("*")
                des.object("*")
                des.object("*")
             end
})
des.object({ id = "chest", coord = {37,08},
             contents = function()
                des.object("$")
                des.object("$")
                des.object("*")
                des.object("*")
                des.object("*")
                des.object("*")
             end
})
des.object("$", 35, 08)
des.object("$", 36, 07)
des.object("$", 36, 08)
des.object("$", 36, 09)
des.object("$", 37, 08)
des.object("$", 35, 08)
des.object("$", 36, 07)
des.object("$", 36, 08)
des.object("$", 36, 09)
des.object("$", 37, 08)

des.object("scimitar", 35, 08)
des.object("scimitar", 36, 07)
des.object("scimitar", 36, 08)
des.object("scimitar", 36, 09)
des.object("scimitar", 37, 08)

for i = 1, 6 do
   des.object({ class = "(", coord = heart:rndcoord() })
end
for i = 1, 6 do
   des.object({ class = ")", coord = heart:rndcoord() })
end
for i = 1, 10 do
   des.object({ class = "*", coord = heart:rndcoord() })
end
for i = 1, 8 do
   des.object({ class = "$", coord = heart:rndcoord() })
end

des.object({ id = "chest", coord = {35,08},
             contents = function()
                des.object("$")
             end
})

-- Objects
-- The Treasury of Proteus is not placed here: as in SpliceHack,
-- Blackbeard's Ghost is created carrying it (see m_initweap() in
-- makemon.c).  SlashTHEM put it on the floor at (36,08) instead:
-- des.object({ id = "chest", x=36, y=08, buc="cursed", spe=0,
--              name="The Treasury of Proteus" })
for i = 1, 14 do
   des.object()
end
-- Random monsters.
des.monster({ id = "Blackbeard's Ghost", x=36, y=08, peaceful = 0 })
for i = 1, 16 do
   des.monster({ id = "human zombie", peaceful = 0 })
end
des.monster({ class = "Z", peaceful = 0 })
des.monster({ class = "Z", peaceful = 0 })
for i = 1, 8 do
   des.monster({ id = "wraith", peaceful = 0 })
end
des.monster({ class = "W", peaceful = 0 })

for i = 1, 3 do
   des.monster({ id = "damned pirate", peaceful = 0 })
   des.monster({ id = "skeletal pirate", peaceful = 0 })
   des.monster({ id = "skeletal pirate", peaceful = 0 })
   des.monster({ id = "skeletal pirate", peaceful = 0 })
end
