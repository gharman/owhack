-- NetHack: Open World  mall-2.lua
--       SCCS Id: @(#)mall-2.des  3.4     1993/02/23
--       Copyright (c) 1989 by Jean-Christophe Collet
--       Copyright (c) 1991 by M. Stephenson
-- Converted from Slash'EM mall-2.des for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.
--
-- (The source's RANDOM_MONSTERS: '@','r' is not needed: no monster below
-- uses it.)

des.message("You hear the sounds of civilization.")

-- The "town": a big lit room with shops as subrooms.  Subroom coordinates
-- are relative to the town room.  The subrooms are made first, so that the
-- town's own monsters are not placed where a shop is going to be (this is
-- also the order in which the 3.4 level loader built them).
des.room({ type = "ordinary", lit = 1, w = 48, h = 15,
           contents = function()
              -- from 2 to 48 across

              des.room({ type = "weapon shop", chance = 20, lit = 1,
                         x = 2, y = 2, w = 5, h = 4,
                         contents = function()
                            des.door({ state = "open", wall = "south" })
                         end
              })

              des.room({ type = "ring shop", chance = 12, lit = 1,
                         x = 8, y = 2, w = 4, h = 4,
                         contents = function()
                            des.door({ state = "open", wall = "south" })
                         end
              })

              des.room({ type = "candle shop", chance = 33, lit = 1,
                         x = 15, y = 3, w = 5, h = 3,
                         contents = function()
                            des.door({ state = "open", wall = "south" })
                         end
              })

              des.room({ type = "armor shop", chance = 22, lit = 0,
                         x = 25, y = 2, w = 6, h = 4,
                         contents = function()
                            des.door({ state = "open", wall = "south" })
                         end
              })

              des.room({ type = "food shop", chance = 40, lit = 1,
                         x = 32, y = 2, w = 14, h = 3,
                         contents = function()
                            des.door({ state = "open", wall = "south" })
                         end
              })

              des.room({ type = "scroll shop", chance = 20, lit = 0,
                         x = 2, y = 9, w = 6, h = 4,
                         contents = function()
                            des.door({ state = "open", wall = "north" })
                         end
              })

              des.room({ type = "potion shop", chance = 30, lit = 1,
                         x = 9, y = 9, w = 6, h = 4,
                         contents = function()
                            des.door({ state = "open", wall = "north" })
                         end
              })

              des.room({ type = "tool shop", chance = 20, lit = 1,
                         x = 19, y = 10, w = 5, h = 3,
                         contents = function()
                            des.door({ state = "open", wall = "north" })
                         end
              })

              des.room({ type = "book shop", chance = 12, lit = 1,
                         x = 25, y = 10, w = 4, h = 3,
                         contents = function()
                            des.door({ state = "open", wall = "north" })
                         end
              })

              -- WAC Changed chance from 20 to 100.  Should be at least 1 guaranteed shop
              des.room({ type = "shop", lit = 1,
                         x = 33, y = 9, w = 9, h = 4,
                         contents = function()
                            des.door({ state = "open", wall = "west" })
                         end
              })

              des.room({ type = "wand shop", chance = 17, lit = 1,
                         x = 43, y = 10, w = 3, h = 3,
                         contents = function()
                            des.door({ state = "open", wall = "north" })
                         end
              })

              des.feature("fountain", 22,07)
              --
              --       The Town Watch.
              --
              des.monster({ id = "watchman", peaceful = 1 })
              des.monster({ id = "watchman", peaceful = 1 })
              des.monster({ id = "watchman", peaceful = 1 })
              des.monster({ id = "watchman", peaceful = 1 })
              des.monster({ id = "watch captain", peaceful = 1 })
              des.monster({ id = "watch captain", peaceful = 1 })
              des.monster({ id = "watch captain", peaceful = 1 })
              des.monster({ id = "mugger", peaceful = 0 })
              des.monster({ id = "mugger", peaceful = 0 })
              des.monster({ id = "mugger", peaceful = 0 })
              des.monster({ id = "mugger", peaceful = 0 })
              des.monster({ id = "sewer rat", peaceful = 0 })
              des.monster({ id = "sewer rat", peaceful = 0 })
              des.monster({ id = "little dog", peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.stair("up")
              des.stair("down")
              des.monster()
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.monster()
              des.object()
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.monster()
              des.object()
              des.trap()
           end
})

des.random_corridors()
