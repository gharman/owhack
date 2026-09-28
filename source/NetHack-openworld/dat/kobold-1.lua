-- NetHack: Open World  kobold-1.lua
-- Kobold level
-- Converted from Slash'EM kobold-1.des for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.
--
-- (The source's RANDOM_MONSTERS: 'k' is not needed: every monster below
-- names its class or type explicitly.)

des.room({ type = "ordinary", lit = 1, w = 11, h = 9,
           contents = function()
              des.object("chest")
              des.object("chest")
              des.object("chest")
              des.object("chest")
              des.object({ class = ")", x = 4, y = 4 })
              des.object({ class = ")", x = 4, y = 4 })
              des.object({ class = "/", x = 4, y = 4 })
              des.object({ class = "[", x = 4, y = 4 })
              des.object({ class = "[", x = 4, y = 4 })
              des.object({ class = "!", x = 4, y = 4 })
              des.object({ class = "!", x = 4, y = 4 })

              for i = 1, 5 do
                 des.monster({ class = "k", peaceful = 0 })
              end
              for i = 1, 3 do
                 des.monster({ id = "large kobold", peaceful = 0 })
              end
              for i = 1, 2 do
                 des.monster({ id = "kobold lord", peaceful = 0 })
              end
              for i = 1, 3 do
                 des.monster({ id = "swamp kobold", peaceful = 0 })
              end
              for i = 1, 3 do
                 des.monster({ id = "rock kobold", peaceful = 0 })
              end
              des.monster({ id = "Kroo the Kobold King", x = 4, y = 4, peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.stair("up")
              des.object()
              des.monster({ class = "k", peaceful = 0 })
              des.monster({ class = "k", peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.stair("down")
              des.object()
              des.trap()
              des.monster({ class = "k", peaceful = 0 })
              des.monster({ class = "k", peaceful = 0 })
              des.monster({ class = "k", peaceful = 0 })
              des.monster({ class = "k", peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.object()
              des.monster({ class = "k", peaceful = 0 })
              des.monster({ class = "k", peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.trap()
              des.monster({ class = "k", peaceful = 0 })
              des.monster({ class = "k", peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.trap()
              des.monster({ class = "k", peaceful = 0 })
              des.monster({ class = "k", peaceful = 0 })
           end
})

des.random_corridors()
