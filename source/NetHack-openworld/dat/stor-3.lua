-- NetHack: Open World  stor-3.lua
-- Storage level (#1)
-- Converted from Slash'EM stor-3.des for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.

des.room({ type = "ordinary", lit = 0, w = 4, h = 4,
           contents = function()
              -- the other objects on the chest's spot lie beside it,
              -- not inside it
              des.object({ id = "chest", x = 2, y = 2 })
              des.object({ class = "/", x = 2, y = 2 })
              des.object({ class = "/", x = 2, y = 2 })
              des.object({ class = "(", x = 2, y = 2 })
              des.object({ class = "(", x = 2, y = 2 })
              des.object({ class = "(", x = 2, y = 2 })
              des.object({ class = "=", x = 2, y = 2 })
              des.engraving({ x = 2, y = 2, type = "burn", text = "Property of the Wizard! Do Not Touch!" })
              des.trap()
              des.trap()
              des.trap()
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.stair("up")
              des.object()
              des.monster({ peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.stair("down")
              des.object()
              des.trap()
              des.monster({ peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.object()
              des.monster({ peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.trap()
              des.monster({ peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.trap()
              des.monster({ peaceful = 0 })
           end
})

des.random_corridors()
