# margen

> generate a marble-like pattern bitmap image, blazing fast.

![](./images/sample.gif)

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
usage: margen [--help] [-v] [-q] [-w=WIDTH] [-h=HEIGHT] [-o=PATH] [--seed=SEED][-p=PIXEL_SIZE] [-s=SLOPE] [-c=R,G,B] [--var=R,G,B] [-vr=VAR_RANGE] [-m]

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
  -m, --monochrome   grayscale generation
```

## TODO

- fix monochrome
- select corner (currently bottom left)