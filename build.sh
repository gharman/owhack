#!/bin/sh
# Rebuild NetHack: Open World and update the installed game in ../../game.
# Saved games, high scores and sysconf in the game directory are left alone.
set -e
here=$(cd "$(dirname "$0")" && pwd)
game=$(cd "$here/../.." && pwd)/game
cd "$here"
if [ ! -f Makefile ]; then
    sh sys/unix/setup.sh sys/unix/hints/macOS.500
fi
make WANT_SOURCE_INSTALL=1 HACKDIR="$game" \
     INSTDIR="$here/playground" VARDIR="$here/playground" \
     POSTINSTALL= SYSCONFINSTALL= all
mkdir -p "$game/save"
for f in nethack nhdat recover symbols license; do
    cp -p "playground/$f" "$game/$f"
done
echo "Installed into $game"
