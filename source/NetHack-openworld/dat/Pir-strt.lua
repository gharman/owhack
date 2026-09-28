-- NetHack Pirate Pir-strt.lua
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991-2 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
--	Tortuga, The Turtle Island
--
--	The "start" level for the quest.
--
--	Here you meet your (besieged) class leader, Mayor Cummerbund
--	(the Dread Pirate, retired), and receive your quest assignment.
--
--	Ported from SpliceHack's Pir-strt.lua and SlashTHEM's Pirate.des.
--	The original level is drawn as three stacked maps: the first two
--	only serve to confine the random placement of the siege troops
--	(to the fort east of the town) and of the undead (to the streets
--	of the town).  Here the final map is drawn once and the same
--	placement is done with selections.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noteleport", "hardfloor")

--0         1         2         3         4         5         6         7
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
}}}}}}}}}}}}}}......................................}}}}}}}}}}}}}}}}}}}}}}}}
}}}}}}}}}}}}...+---.----.----.----.----.----.--+-.--+-}}}}F-F-}}}}}}}-F-F}}}
}}}}}}}}}}}....+..|.|##|.|##|.|##|.|##|.|##|.|..|.|..+.}}}|..F-F-F-F-F..|}}}
}}}}}}}}}......+..|.|##|.|##|.|##|.|##|.|##|.|..|.+..|...}F.............F}.}
}}}}}}}}.......-++-.--+-.--+-.--+-.--+-.--+-.-+--.-++-...}-|.FFFFFFFFF.F-}.}
}}}}}}}....................................................|.F#######F.|}}.}
}}}}}}}.-++-..-----....                              ......|.F#-F+F-#F.F}}.}
}}}}}}..+..+..+...+..    .......................  ..   ....|.F#F...|---|}}.}
}}}}}...+..|..|...+.    .........................H...   ...|.+#|...+...+....
}}}}}}..-+----+...|..  H .......................  ..   ....|.F#F...|---|}}.}
}}}}}}}....+..++---....                          -----.....|.F#-F+F-#F.F}}.}
}}}}}}}....+...|.....-----..-----..-----..-----..|.|.|.....|.F#######F.|}}.}
}}}}}}}}...|...|.....|...|..|...|..|...|..|...|..|.|.|...}--.FFFFFFFFF.F-}.}
}}}}}}}}}..-----.....|...|..|...|..|...|..|...|..|+-+|...}F.............F}.}
}}}}}}}}}}}..........|...|..|...|..|...|..|...|..S...|..}}|..F-F-F-F-F..|}}}
}}}}}}}}}}}}.........-+---..-+---..-+---..-+---..-----.}}}F-F-}}}}}}}-F-F}}}
}}}}}}}}}}}}}}.......................................}}}}}}}}}}}}}}}}}}}}}}}
}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
]]);
--0123456789012345678901234567890123456789012345678901234567890123456789012345
--0         1         2         3         4         5         6         7
-- Dungeon Description
des.region(selection.area(00,00,75,20), "lit")
-- Portal arrival point: the west end of the town.  (SpliceHack and
-- SlashTHEM use {05,00,58,20}, which lets the portal land inside a shop
-- or a locked cell of the brothel; this is Hack'EM's region.)
des.levregion({ region = {07,07,20,16}, exclude = {24,09,52,11}, type="branch" })
-- Stairs
des.stair("down", 65,10)
-- Doors
des.door("closed",22,06)
des.door("closed",27,06)
des.door("closed",32,06)
des.door("closed",37,06)
des.door("closed",42,06)

des.door("locked",67,10)
des.door("locked",71,10)

des.door("closed",22,17)
des.door("closed",29,17)
des.door("closed",36,17)
des.door("closed",43,17)

des.door("locked",49,16)
des.door("locked",50,15)
des.door("locked",52,15)

-- Shops
des.region({ region={22,14,24,16}, lit=1, type="potion shop", filled=1 })
des.object("booze", 22, 14)
des.object("booze", 23, 14)
des.object("booze", 24, 14)
des.object("booze", 24, 15)
des.object("booze", 23, 15)
des.object("booze", 22, 15)
des.object("booze", 23, 16)
des.object("booze", 24, 16)
des.region({ region={29,14,31,16}, lit=1, type="weapon shop", filled=1 })
des.region({ region={36,14,38,16}, lit=1, type="weapon shop", filled=1 })
des.region({ region={43,14,45,16}, lit=1, type="tool shop", filled=1 })
-- The brothel
des.monster({ id = "succubus", x=50, y=13, peaceful=0 })
des.object({ id = "scare monster", x=50, y=14, buc="cursed" })
des.monster({ id = "incubus", x=52, y=13, peaceful=0 })
des.object({ id = "scare monster", x=52, y=14, buc="cursed" })

-- Mayor Cummerbund, the Dread Pirate (ret.)
des.monster({ id = "Mayor Cummerbund", x=51, y=10, inventory = function()
   des.object({ id = "scimitar", spe = 4, buc = "cursed" });
   des.object({ id = "leather jacket", spe = 2 });
   des.object({ id = "small shield", spe = 2 });
   des.object({ id = "high boots", spe = 2 });
   des.object({ id = "leather gloves", spe = 2 });
end })
-- The treasure of the Dread Pirate
des.object("chest", 52, 10)
-- Guards for the audience chamber
-- ("pirate brother" in the references; the species' neutral name gives
-- a mix of pirate brothers and pirate sisters)
des.monster("pirate crewmate", 22, 05)
des.monster("pirate crewmate", 27, 05)
des.monster("pirate crewmate", 32, 05)
des.monster("pirate crewmate", 37, 05)
des.monster("pirate crewmate", 42, 05)
des.monster("pirate crewmate", 27, 09)
des.monster("pirate crewmate", 37, 11)
des.monster("pirate crewmate", 47, 10)

-- Used cannon balls, lodged in the walls and rock where they struck
des.object("heavy iron ball", 13, 15)
des.object("heavy iron ball", 16, 12)
des.object("heavy iron ball", 21, 09)
des.object("heavy iron ball", 21, 16)
des.object("heavy iron ball", 45, 08)
des.object("heavy iron ball", 51, 08)
des.object("heavy iron ball", 52, 08)

-- Non diggable walls
des.non_diggable(selection.area(00,00,75,20))

-- The fort east of the town, held by the siege troops
local fort = selection.area(59,04,71,16)
fort = fort:filter_mapchar(".") | fort:filter_mapchar("#")
-- The streets of the town, where the undead roam: not the leader's
-- hidden hall, the shops or the brothel
local town = selection.area(00,00,58,20) | selection.area(72,00,75,20)
town = town:filter_mapchar(".") - selection.area(24,09,52,11)
town = town - selection.area(22,14,24,16) - selection.area(29,14,31,16)
town = town - selection.area(36,14,38,16) - selection.area(43,14,45,16)
town = town - selection.area(50,13,52,16)

-- Monsters on siege duty, and their weapons.
for i = 1, 9 do
   des.object({ id = "crossbow", coord = fort:rndcoord() })
   des.object({ id = "crossbow bolt", coord = fort:rndcoord() })
end
for i = 1, 5 do
   des.object({ id = "knife", coord = fort:rndcoord() })
end
des.object({ id = "spear", coord = fort:rndcoord() })
des.object({ id = "spear", coord = fort:rndcoord() })
des.monster({ id = "sergeant", coord = fort:rndcoord(1), peaceful = 0 })
for i = 1, 9 do
   des.monster({ id = "soldier", coord = fort:rndcoord(1), peaceful = 0 })
end

-- The dead that the Yendorians have disturbed.
for i = 1, 3 do
   des.monster({ id = "ghost", coord = town:rndcoord(1), peaceful = 0 })
end
for i = 1, 12 do
   des.monster({ id = "skeletal pirate", coord = town:rndcoord(1), peaceful = 0 })
end
