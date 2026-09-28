-- NetHack: Open World  guild.lua
--
-- The guild of disgruntled adventurers.
--
-- Converted from Slash'EM guild.des for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.

-- Every role belongs in the guild.  The player monsters of the roles that
-- vanilla has are always created (see below).  The roles listed in this
-- table are not (all) in the game yet; two hostile members of each are
-- created only if a monster type of that name exists in the running game.
-- The check is made when the level is created, from the game's own monster
-- list, so when a new role and its player monster are added to the game,
-- its members turn up here automatically.  Names are the gender-neutral
-- monster names; add further roles to this table as needed.
local optional_roles = {
   "cartographer",
   "convict",
   "flame mage",       -- in Slash'EM's original guild
   "ice mage",         -- in Slash'EM's original guild
   "infidel",
   "jedi",
   "necromancer",      -- in Slash'EM's original guild
   "pirate",
   "undead slayer",    -- in Slash'EM's original guild
}

-- gender-neutral names of all monster types in the running game
local known = {}
for i = nhc.LOW_PM, nhc.HIGH_PM do
   known[nh.int_to_pmname(i)] = true
end

des.room({ type = "ordinary", lit = 1, w = 12, h = 6,
           contents = function()
              -- stuff for them to use on you...
              des.object("?")
              des.object("?")
              des.object("?")
              des.object("?")
              des.object("/")
              des.object("/")
              des.object("!")
              des.object("!")
              des.object("!")
              for i = 1, 10 do
                 des.object()
              end

              des.monster({ id = "archeologist", peaceful = 0 })
              des.monster({ id = "archeologist", peaceful = 0 })
              des.monster({ id = "barbarian", peaceful = 0 })
              des.monster({ id = "barbarian", peaceful = 0 })
              des.monster({ id = "caveman", peaceful = 0 })
              des.monster({ id = "cavewoman", peaceful = 0 })
              des.monster({ id = "doppelganger", peaceful = 0 })
              des.monster({ id = "doppelganger", peaceful = 0 })
              des.monster({ id = "elf", peaceful = 0 })
              des.monster({ id = "elf", peaceful = 0 })
              des.monster({ id = "healer", peaceful = 0 })
              des.monster({ id = "healer", peaceful = 0 })
              des.monster({ id = "knight", peaceful = 0 })
              des.monster({ id = "knight", peaceful = 0 })
              des.monster({ id = "monk", peaceful = 0 })
              des.monster({ id = "monk", peaceful = 0 })
              -- The player-monster priest and priestess are the "cleric"
              -- monster type in 5.0 (plain "priest" would name the aligned
              -- temple priest, which comes first in the monster list).
              des.monster({ id = "cleric", female = false, peaceful = 0 })
              des.monster({ id = "cleric", female = true, peaceful = 0 })
              -- Slash'EM's guild has no rangers, but every role belongs here
              des.monster({ id = "ranger", peaceful = 0 })
              des.monster({ id = "ranger", peaceful = 0 })
              des.monster({ id = "rogue", peaceful = 0 })
              des.monster({ id = "rogue", peaceful = 0 })
              des.monster({ id = "samurai", peaceful = 0 })
              des.monster({ id = "samurai", peaceful = 0 })
              des.monster({ id = "tourist", peaceful = 0 })
              des.monster({ id = "tourist", peaceful = 0 })
              des.monster({ id = "valkyrie", peaceful = 0 })
              des.monster({ id = "valkyrie", peaceful = 0 })
              des.monster({ id = "wizard", peaceful = 0 })
              des.monster({ id = "wizard", peaceful = 0 })

              -- the roles this game may or may not have (see top of file)
              for _, role in ipairs(optional_roles) do
                 if known[role] then
                    des.monster({ id = role, peaceful = 0 })
                    des.monster({ id = role, peaceful = 0 })
                 end
              end
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.stair("up")
              des.object()
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.stair("down")
              des.object()
              des.trap()
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.object()
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.trap()
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.trap()
           end
})

des.random_corridors()
