#!/bin/sh
# Rebuild NetHack: Open World and update the installed game in ../../game.
# Saved games, high scores and sysconf in the game directory are left alone
# (a missing sysconf is created, with wizard mode allowed for you).
set -e
here=$(cd "$(dirname "$0")" && pwd)
game=$(cd "$here/../.." && pwd)/game
cd "$here"
# Compile with the system's C compiler (or $CC): whatever is called "cc"
# first on PATH may be something else entirely.
: "${CC:=/usr/bin/cc}"
if [ ! -f Makefile ]; then
    sh sys/unix/setup.sh sys/unix/hints/macOS.500
fi
make CC="$CC" WANT_SOURCE_INSTALL=1 HACKDIR="$game" \
     INSTDIR="$here/playground" VARDIR="$here/playground" \
     POSTINSTALL= SYSCONFINSTALL= all
mkdir -p "$game/save"
if [ ! -f "$game/sysconf" ]; then
    sh sys/unix/hints/macosx.sh editsysconf sys/unix/sysconf "$game/sysconf"
    sed -i '' "s/^WIZARDS=.*/WIZARDS=$(id -un)/" "$game/sysconf"
fi
for f in perm record logfile xlogfile livelog; do
    [ -f "$game/$f" ] || : > "$game/$f"
done
# replace each file by renaming a fresh copy over it, so that a game that
# is running keeps the files it started with
for f in nethack nhdat recover symbols license; do
    cp -p "playground/$f" "$game/$f.new"
    mv -f "$game/$f.new" "$game/$f"
done
# the supplemental wiki (../../wiki/*.md) as HTML pages beside the game
if command -v python3 >/dev/null 2>&1; then
    python3 "$here/wiki2html.py" "$here/../../wiki" "$game/wiki"
else
    echo "python3 not found: skipping the wiki's HTML pages"
fi
echo "Installed into $game"
