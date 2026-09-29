# Lineage and credits

[Home](Home.md) · [Differences from the source variants](Variant_differences.md)

NetHack: Open World is a **variant of NetHack 5.0.0**. Its parent is the
DevTeam's own source; it is not a fork of any other variant. Several
variants contributed features, which were **ported from their source
code** at the versions listed below. None of their code was merged in
directly, because each variant is built on an older NetHack than 5.0, so
every feature was rewritten against 5.0's code.

## Parent: NetHack 5.0.0

| | |
|---|---|
| Project | NetHack, by the NetHack DevTeam |
| Repository | [github.com/NetHack/NetHack](https://github.com/NetHack/NetHack), branch `NetHack-5.0` |
| Commit | `c1b1b08e95dc5e5ad55760e20affd45de5dd7e90`, dated 2026-09-26 (5.0.0, shortly after release) |

The first commit in this build's history ("NetHack 5.0 baseline") is
that source unchanged, apart from hooks for automated testing. Everything
after it is this build's own work.

## Feature sources

| Variant | Version | Repository | Commit | What this build took from it |
|---|---|---|---|---|
| Slash'EM | 0.0.8 | [k21971/SlashEM](https://github.com/k21971/SlashEM) | `aae9ef2` (2024-02-10) | Necromancer, Flame Mage and Ice Mage; the vampire, werewolf (lycanthrope) and doppelganger races; techniques; special levels |
| SlashTHEM | 0.9.7 | [Soviet5lo/SlashTHEM](https://github.com/Soviet5lo/SlashTHEM) | `d828e64` (2023-01-05) | Jedi; Pirate; techniques |
| SpliceHack | 1.2.0 | [NullCGT/SpliceHack](https://github.com/NullCGT/SpliceHack) | `8d70ade` (2022-09-19) | Pirate; Convict |
| Hack'EM | 1.3.0 | [elunna/hackem](https://github.com/elunna/hackem) | `cebe2f3` (2025-02-11) | Hack'EM's versions of most of the roles, races and techniques above; drain and psychic resistance; `#enhance` training percentages; inventory weights; special levels |
| EvilHack | 0.9.3 | [k21971/EvilHack](https://github.com/k21971/EvilHack) | `c444f6a` (2026-07-12) | Infidel; Convict; the giant, centaur, illithid, tortle and draugr races; vampire; the rules for material hatred and wishing; Goblin Town and other special levels |
| xNetHack | 10.0 | [copperwater/xNetHack](https://github.com/copperwater/xNetHack) | `6eef394` (2026-05-26) | the object materials system |

Where a role, race or level exists in more than one of these, [Differences
from the source variants](Variant_differences.md) says which version was
followed and where this build departs from it.

## Original to this build

* **The open world**: the Dungeons of Doom and Gehennom as one outdoor
  world of concentric rings, with every branch behind a ring of portals.
  See [The open world](Open_world.md).
* **The [Cartographer](Cartographer.md)** role, its
  [quest](Cartographer_quest.md), the [Celestial
  Sextant](Celestial_Sextant.md), [Pathfinder](Pathfinder.md) and the
  [sextant](Sextant.md).
* **The [ghost](Ghost_race.md)** race.
* The techniques survey, triangulate, waymark, haunt, slip free, mind
  blast and hold breath (see [Techniques](Techniques.md)), and the
  adaptations of the imported features to the open world.

## Other components

* **Lua 5.4.8** ([lua.org](https://www.lua.org/), MIT license) runs the
  level scripts, as in NetHack 5.0. It isn't in this repository: the build
  downloads it from lua.org if `lib/` doesn't have it.

## License

NetHack is distributed under the **NetHack General Public License**
(`source/NetHack-openworld/dat/license`, shown in the game by `?`). So are
Slash'EM, SlashTHEM, SpliceHack, Hack'EM, EvilHack and xNetHack, and so is
this build. Thanks to the NetHack DevTeam and to the authors of all six
variants, whose work much of this game is.
