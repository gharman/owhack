# Sextant

[Home](Home.md) · [Cartographer](Cartographer.md)

The **sextant** is a new tool in NetHack: Open World: a navigator's
instrument for taking sightings of the sun or stars. Anyone can find, buy
or use one; [Cartographers](Cartographer.md) start with one.

| | |
|---|---|
| Class | tool (`(`) |
| Material | copper |
| Weight | 10 |
| Cost | 100 zm |
| Probability | 5 (uncommon) |
| Appearance | "sextant" (always identified) |

## Using it

Apply it to **take a sighting** (one turn). In the open world you learn:

* **your ring**, which is your depth, and whether you are in Gehennom;
* **how far away the centre of the world is**, in paces, and its bearing
  in degrees and as a compass point (e.g. *bearing 212 (SSW)*);
* for **each ring of portals you know about**, the distance and bearing
  of its nearest portal, and where it leads.

For example:

```
You are in ring 9 of the world (depth 9).
The centre of the world lies 139 paces away, bearing 212 (SSW).

Nearest portals:
  the Gnomish Mines (ring 3): 97 paces, bearing 222 (SW).
  the Oracle (ring 7): 31 paces, bearing 190 (S).
```

### It needs the sky

A sighting fails if you are **blind**, **engulfed**, **under water**, or
**under a roof** (inside a building or a cave). **In a branch there is no
sky**: the sextant can only tell you which level of which branch you are
on, and its depth.

### Accuracy

Cartographers always read a sextant exactly, and so does anyone whose Luck
is zero or better. With negative Luck, other roles get a reading that is
somewhat off: distances by up to a fifth or so (plus or minus 2), bearings
by up to 30°.

## The Celestial Sextant

The Cartographer's quest artifact, [the Celestial
Sextant](Celestial_Sextant.md), is a perfect sextant that works anywhere,
underground or blind, and tells you where a branch's way out lies in the
world.
