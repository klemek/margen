# margen

> generate a marble-like pattern bitmap image, blazing fast.

<p align="center">
  <img width="960" height="360" src="./images/sample.gif">
</p>

Written in pure C without librairies.

## Install

You only need **gcc** and **make**.

```bash
git clone https://github.com/klemek/margen
cd margen
make clean build install
# margen is now installed in ~/.local/bin
```

## CLI arguments

```txt
usage: margen [--help] [-v] [-q] [-w=WIDTH] [-h=HEIGHT] [-o=PATH] [--seed=SEED][-p=PIXEL_SIZE] [-s=SLOPE] [-c=R,G,B] [-va=R,G,B] [-vr=VAR_RANGE] [-r=ROTATION]

generate a marble-like pattern bitmap image, blazing fast.

options:
  --help             show this help message and exit
  -q, --quiet        do not print to console
  -w, --width        image width (default: 1920)
  -h, --height       image height (default: 1080)
  -o, --output       output file (default: output.bmp)
  -seed              random seed (default: time based)
  -p, --pixel        pixel size (default: random)
  -s, --slope        slope [0-255] (default: random)
  -c, --color        base color [0-255,0-255,0-255] (default: random)
  -va, --variation   fixed variation [0-255,0-255,0-255] (default: random)
  -vr, --var-range   random variation range [0-255] (default: 30)
  -r, --rotation     start corner rotation [0-3] (default: random)
```

## TODO

- fix monochrome