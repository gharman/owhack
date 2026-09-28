-- NetHack Pirate Pir-loca.lua
--	Copyright (c) 1989 by Jean-Christophe Collet
--	Copyright (c) 1991-2 by M. Stephenson
-- NetHack may be freely redistributed.  See license for details.
--
--	Welcome to Shipwreck Island
--
--	The "locate" level for the quest.
--
--	Here you make landfall on Shipwreck Island and
--	move inland towards the center of the island.
--
--	Ported from SpliceHack's Pir-loca.lua and SlashTHEM's Pirate.des.
--	The original level is drawn as five stacked maps, the first four
--	of which only serve to confine the random placement of what lies
--	on the level: the flotsam and the sharks to the sea, the Yendorian
--	troops to the wreck of their ship, the first undead to the beaches
--	and the rest to the caves in the east.  Here the final map is
--	drawn once and the same placement is done with selections.
--
des.level_init({ style = "solidfill", fg = " " });

des.level_flags("mazelevel", "noteleport", "hardfloor")

--0         1         2         3         4         5         6         7
--0123456789012345678901234567890123456789012345678901234567890123456789012345
des.map([[
}}}}}}}}}......         }}}}}}PP}}}}}}}}}}}}}}  }} }}}}}}}}}        }}}}}}}}
}}}  }..........}}   }}}}}}}}PP}}}}P}}}}}}}}   }   }}}}}}        }}}}       
}}}} .}}}......}}}}}}}}}}}}}.}}}}P.   }}}}}}}}  }}}}} }}}}}  } }}}   #######
}}}}.}..}}...}}   }}}}}}PPP}}}}}P.     }}   }}}}}}}} }}}   } }}       ##### 
}}}. .}}  }.}}}}}   }}}}}PPPP}}}}P. }}}}     }}}}}   }} }}      ########### 
}}.}.}....  }..}}}}}} .PP}PPP}}}}}}}}}}}}}   }}}}}} }}  }}}}}}}}   ###  ## #
}}}.}}.... }}}.}.}  ...-----------------++-------}}}}----}---|}     ## #### 
}}}.}.}...P...}.}...--H|..........................}.}}.....}}--|}}   #####  
}}}}..}}}.   }}}}}--|..............................}}}}}.......-|}}  #######
}.}.}}..}...  }}--|......................---...........}}}..}}.}   HH#######
.}.}..}}...}}}}-|........................| |......}}}}}}...}..  HHH  ##  ###
}.}}}.}..} }}}}}--|......................---.....}}}}}}}}..}..}.|   ########
}}.}.....  }}.....--|.................................}}}}.....-| ##########
}}}.}.... }}}}.....}---|...........................}}}}...}}.-++} ##  ###  #
}}}}..}}..P ..}}}}}}PP}--------------------------++--}}----}-|}}  ####  ####
}}}}}.}.....  ....PPPPP}}}}}}}}PPP}}}}   }}}}}}}}}}}}}}}}}}}}}}  ######## ##
}}}}}}.....P }  }...PP}}}}}}}}P...P}} }  }}}}}}}}}}}}}}}}}}}}}}} ###########
}}}}}}}}...PP}}}}...P}}}}}}}}}   .P}}}   }}}}}}}}}}}}}}}}}}}}}}}  ####   ## 
}}}  ....   .P}}  }}}}}}}}}}}   ..P}}}}}}}}}}}}}}}}}}}}}}}}}}       #### #  
}}}}}  }..}   .}}}}}}}}}}}}}  }}}P}}}}}}}}}}}}}}}}}}}}}}}}}}      #   ### # 
}}}}}}}.} }}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}    #####     
]]);
--0123456789012345678901234567890123456789012345678901234567890123456789012345
--0         1         2         3         4         5         6         7
-- Dungeon Description
des.region(selection.area(00,00,15,20), "lit")

-- Stairs
des.stair("up", 00,10)
des.levregion({ region = {64,00,75,20}, type="stair-down" })

-- Non diggable walls
des.non_diggable(selection.area(56,00,75,05))
des.non_diggable(selection.area(64,06,75,14))
des.non_diggable(selection.area(56,15,75,20))

-- Captain Ketch, who led the attack on Tortuga
des.monster({ id = "captain", x=58, y=10, name = "Captain Ketch", peaceful = 0 })
des.object({ id = "crossbow", x=58, y=10 })
des.object({ id = "crossbow bolt", x=58, y=10, buc="blessed", spe=3 })

-- Where things are
local whole = selection.area(00,00,75,20)
local sea = whole:filter_mapchar("}")
local pools = whole:filter_mapchar("P")
local wreck = selection.area(17,07,63,13) - selection.area(17,07,19,07)
wreck = (wreck - selection.area(17,12,18,13)):filter_mapchar(".")
local beach = whole:filter_mapchar(".") - wreck
local caves = whole:filter_mapchar("#")

-- Sharks in the shallows
for i = 1, 6 do
   des.monster({ id = "shark", coord = pools:rndcoord(1), peaceful = 0 })
end

-- Objects (lost flotsam).
for i = 1, 15 do
   des.object({ coord = sea:rndcoord() })
end
for i = 1, 9 do
   des.object({ id = "scimitar", coord = sea:rndcoord() })
end

-- The Yendorian troops, stranded in the wreck of Ketch's ship
for i = 1, 9 do
   des.object({ id = "crossbow", coord = wreck:rndcoord() })
   des.object({ id = "crossbow bolt", coord = wreck:rndcoord() })
end
for i = 1, 5 do
   des.object({ id = "knife", coord = wreck:rndcoord() })
end
des.object({ id = "spear", coord = wreck:rndcoord() })
des.object({ id = "spear", coord = wreck:rndcoord() })
des.monster({ id = "lieutenant", coord = wreck:rndcoord(1), peaceful = 0 })
for i = 1, 9 do
   des.monster({ id = "soldier", coord = wreck:rndcoord(1), peaceful = 0 })
end

-- More lost flotsam on the beaches, and the first of the ghostly
-- minions of Blackbeard
for i = 1, 5 do
   des.object({ coord = beach:rndcoord() })
end
des.monster({ id = "ghost", coord = beach:rndcoord(1), peaceful = 0 })
for i = 1, 8 do
   des.monster({ id = "skeletal pirate", coord = beach:rndcoord(1), peaceful = 0 })
end

-- ... and in the caves leading to the heart of the island
for i = 1, 3 do
   des.monster({ id = "ghost", coord = caves:rndcoord(1), peaceful = 0 })
end
des.monster({ id = "damned pirate", coord = caves:rndcoord(1), peaceful = 0 })
for i = 1, 11 do
   des.monster({ id = "skeletal pirate", coord = caves:rndcoord(1), peaceful = 0 })
end
