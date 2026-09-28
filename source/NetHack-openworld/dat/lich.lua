-- NetHack: Open World  lich.lua
--
-- Vecna's dungeon
--
-- Converted from Slash'EM lich.des for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.
--
--des.message("You feel deathly cold.")
-- (the source's RANDOM_MONSTERS line is not needed: every monster below
-- names its class)

des.room({ type = "ordinary", lit = 0, w = 5, h = 5,
           contents = function()
              des.stair("up")
              des.object()
           end
})

des.room({ type = "ordinary", lit = 0, w = 20, h = 10,
           contents = function()
              for i = 1, 8 do
                 des.object("chest")
              end
              for i = 1, 9 do
                 des.object("*")
              end
              for i = 1, 28 do
                 des.object()
              end
              for i = 1, 10 do
                 des.object("!")
              end
              for i = 1, 9 do
                 des.object("?")
              end
              for i = 1, 6 do
                 des.object("+")
              end
              for i = 1, 4 do
                 des.trap()
              end
              des.monster({ id = "Vecna", peaceful = 0 })
              for i = 1, 13 do
                 des.monster({ class = "L", peaceful = 0 })
              end
              for i = 1, 5 do
                 des.monster({ class = "W", peaceful = 0 })
              end
              for i = 1, 7 do
                 des.monster({ class = "V", peaceful = 0 })
              end
              for i = 1, 10 do
                 des.monster({ class = "Z", peaceful = 0 })
              end
           end
})

des.room({ type = "ordinary",
           contents = function()
              --des.stair("down")
              des.object()
              des.trap()
              des.monster({ class = "L", peaceful = 0 })
              des.monster({ class = "V", peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.object()
              des.monster({ class = "L", peaceful = 0 })
              des.monster({ class = "W", peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.trap()
              des.monster({ class = "L", peaceful = 0 })
              des.monster({ class = "Z", peaceful = 0 })
              des.monster({ class = "Z", peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.object()
              des.trap()
              des.monster({ class = "L", peaceful = 0 })
              des.monster({ class = "Z", peaceful = 0 })
              des.monster({ class = "Z", peaceful = 0 })
           end
})

des.random_corridors()
