-- NetHack: Open World  rats-1.lua
-- Rat level
-- Converted from Slash'EM rats.des (level "rats") for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.
--
-- (The source's RANDOM_MONSTERS: 'r' is not needed: every monster below
-- names its class or type explicitly.)

des.room({ type = "ordinary", lit = 0, w = 16, h = 8,
           contents = function()
              des.object()
              des.object()
              des.object()
              -- Slash'EM potion of invulnerability; 5.0 has none, so a
              -- potion of full healing instead
              des.object({ id = "full healing", class = "!" })
              des.object({ id = "long sword", x = 8, y = 4 })
              des.object({ id = "elven boots", x = 8, y = 4 })
              -- Slash'EM cheese -> cream pie (5.0 has no cheese)
              des.object({ id = "cream pie", x = 8, y = 4 })
              des.object({ id = "cream pie", x = 8, y = 4 })
              des.object({ class = "/", x = 8, y = 4 })
              des.object({ class = "!", x = 8, y = 4 })

              for i = 1, 5 do
                 des.monster({ class = "r", peaceful = 0 })
              end
              for i = 1, 4 do
                 des.monster({ id = "pack rat", peaceful = 0 })
              end
              for i = 1, 8 do
                 des.monster({ id = "black rat", peaceful = 0 })
              end
              for i = 1, 5 do
                 des.monster({ id = "giant rat", peaceful = 0 })
              end
              for i = 1, 8 do
                 des.monster({ id = "sewer rat", peaceful = 0 })
              end
              des.monster({ id = "rabid rat", peaceful = 0 })
              -- The source put the Rat King at (8,8), which is on the
              -- bottom wall of this 16x8 room (floor rows are 0-7); he is
              -- placed on the bottom floor row instead.
              des.monster({ id = "Rat King", x = 8, y = 7, peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.stair("up")
              des.object()
              des.monster({ id = "giant rat", peaceful = 0 })
              des.monster({ id = "giant rat", peaceful = 0 })
              des.monster({ id = "giant rat", peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.stair("down")
              des.object()
              des.trap()
              des.monster({ id = "rabid rat", peaceful = 0 })
              des.monster({ id = "rabid rat", peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.object()
              des.monster({ id = "giant rat", peaceful = 0 })
              des.monster({ id = "giant rat", peaceful = 0 })
              des.monster({ id = "giant rat", peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.trap()
              des.monster({ id = "giant rat", peaceful = 0 })
              des.monster({ id = "giant rat", peaceful = 0 })
              des.monster({ id = "giant rat", peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.trap()
              des.monster({ id = "giant rat", peaceful = 0 })
              des.monster({ id = "giant rat", peaceful = 0 })
              des.monster({ id = "giant rat", peaceful = 0 })
           end
})

des.random_corridors()
