-- NetHack: Open World  nymph.lua
-- NetHack 3.6  nymph.des  $NHDT-Date: 1595116228 2020/07/18 23:50:28 $  $NHDT-Branch: master $:$NHDT-Revision: 1.9 $
--
-- Nymph level (from UnNetHack, which came from Slash'EM)
-- Level is slightly modified from the original
--
-- Converted from Hack'EM nymph.des for NetHack 5.0.
-- NetHack may be freely redistributed.  See license for details.

-- TERRAIN: random, 'T' -- a tree on a random spot of the current room
local function random_tree()
   local c = selection.room():rndcoord(1)
   des.terrain(c.x, c.y, "T")
end

des.room({ type = "ordinary", lit = 0, w = 12, h = 7,
           contents = function()
              random_tree()
              random_tree()
              if percent(30) then random_tree() end
              if percent(30) then random_tree() end
              if percent(30) then random_tree() end
              if percent(30) then random_tree() end
              des.feature("fountain")
              des.trap("board")
              des.trap("board")

              -- Hack'EM turned 50% of this room's floor into grass;
              -- 5.0 has no grass, so that REPLACE_TERRAIN is dropped.

              des.object("chest")
              des.object("chest")
              des.object("chest")
              -- Hack'EM crystal chest -> chest (5.0 has no crystal chest)
              des.object("chest")
              des.object("=")
              des.object("=")
              des.object("=")
              des.object("=")
              des.object("*")
              des.object("*")
              des.object("*")
              des.object("*")
              des.object("*")
              des.object()
              des.object()
              des.object()
              des.object()
              des.monster({ class = "n", peaceful = 0 })
              des.monster({ class = "n", peaceful = 0 })
              des.monster({ class = "n", peaceful = 0 })
              des.monster({ class = "n", peaceful = 0 })
              des.monster({ class = "n", peaceful = 0 })
              des.monster({ id = "Aphrodite", peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              random_tree()
              des.trap("board")
              des.stair("up")
              des.object()
              des.monster({ class = "n", peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              if percent(30) then random_tree() end
              if percent(30) then random_tree() end
              des.trap("board")
              des.trap()
              des.stair("down")
              des.object()
              des.monster({ class = "n", peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              if percent(40) then random_tree() end
              if percent(30) then random_tree() end
              des.trap("board")
              des.object()
              des.object()
              des.monster({ class = "n", peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              -- Hack'EM dead tree ('t') -> tree (5.0 has no dead trees)
              if percent(30) then random_tree() end
              if percent(30) then random_tree() end
              des.trap("board")
              des.trap()
              des.object()
              des.monster({ class = "n", peaceful = 0 })
           end
})

des.room({ type = "ordinary",
           contents = function()
              des.trap("board")
              des.object()
              des.trap()
              des.monster({ class = "n", peaceful = 0 })
           end
})

des.random_corridors()
