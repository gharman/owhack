#!/bin/sh
# Launch NetHack: Open World.
#
# The game's data, sysconf, high scores and save files live in ./game.
# Any arguments are passed on to nethack, e.g.
#     ./play.sh -u Name          play as "Name"
#     ./play.sh -s               show the high score list
#     ./play.sh -D               wizard (debug) mode, if sysconf's WIZARDS allows
here=$(cd "$(dirname "$0")" && pwd)
NETHACKDIR="$here/game"
export NETHACKDIR
cd "$NETHACKDIR" || exit 1
exec ./nethack "$@"
