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
os=$(uname -s)
# (re)generate the Makefiles if they are missing or older than the
# templates and hints they are made from
if [ ! -f Makefile ] || [ -n "$(find sys/unix/Makefile.* sys/unix/hints \
        -newer Makefile -type f | head -n 1)" ]; then
    case $os in
    Darwin) hints=macOS.500 ;;
    Linux)  hints=linux.500 ;;
    *)  echo "build.sh knows macOS and Linux; see sys/unix/NewInstall.unx" >&2
        exit 1 ;;
    esac
    sh sys/unix/setup.sh "sys/unix/hints/$hints"
fi
# Lua isn't in git: fetch it on the first build. make fetch-lua exits 0
# even when every download fails, so check for the result ourselves.
if [ ! -f lib/lua-5.4.8/src/lua.h ]; then
    make fetch-lua
    if [ ! -f lib/lua-5.4.8/src/lua.h ]; then
        echo "build.sh: couldn't download Lua 5.4.8 (needs curl or wget and" >&2
        echo "access to lua.org); see 'make fetch-lua' above" >&2
        exit 1
    fi
fi
make CC="$CC" WANT_SOURCE_INSTALL=1 HACKDIR="$game" \
     INSTDIR="$here/playground" VARDIR="$here/playground" \
     POSTINSTALL= SYSCONFINSTALL= all
mkdir -p "$game/save"
if [ ! -f "$game/sysconf" ]; then
    if [ "$os" = Darwin ]; then
        sh sys/unix/hints/macosx.sh editsysconf sys/unix/sysconf \
            "$game/sysconf.new"
    else
        cp sys/unix/sysconf "$game/sysconf.new"
    fi
    sed "s/^WIZARDS=.*/WIZARDS=$(id -un)/" "$game/sysconf.new" > "$game/sysconf"
    rm -f "$game/sysconf.new"
fi
for f in perm record logfile xlogfile livelog; do
    [ -f "$game/$f" ] || : > "$game/$f"
done
# replace each file by renaming a fresh copy over it, so that a game that
# is running keeps the files it started with
for f in owhack nhdat recover symbols license; do
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
