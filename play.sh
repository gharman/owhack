#!/bin/sh
# Launch NetHack: Open World.
#
# The game's data, sysconf, high scores and save files live in ./game.
# Any arguments are passed on to nethack, e.g.
#     ./play.sh -u Name          play as "Name"
#     ./play.sh -s               show the high score list
#     ./play.sh -D               wizard (debug) mode, if sysconf's WIZARDS allows
#
# Options: if there is a file called "nethackrc" next to this script (it
# is not part of the repository; see .gitignore), it is used instead of
# ~/.nethackrc.  A --nethackrc=FILE argument, or NETHACKOPTIONS naming a
# file, still takes precedence.
here=$(cd "$(dirname "$0")" && pwd)
NETHACKDIR="$here/game"
export NETHACKDIR
cd "$NETHACKDIR" || exit 1
rc=
if [ -f "$here/nethackrc" ]; then
    case "$NETHACKOPTIONS" in
    /* | @*) ;;
    *)  rc="--nethackrc=$here/nethackrc"
        for arg in "$@"; do
            case "$arg" in
            --nethackrc* | -nethackrc* | --no-nethackrc | -no-nethackrc)
                rc= ;;
            esac
        done ;;
    esac
fi
exec ./nethack ${rc:+"$rc"} "$@"
