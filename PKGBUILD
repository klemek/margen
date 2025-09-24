pkgname=margen
pkgver=1.2.6
pkgrel=1
pkgdesc="Generate a marble-like pattern bitmap image, blazing fast."
arch=('i686' 'pentium4' 'x86_64' 'arm' 'armv7h' 'armv6h' 'aarch64' 'riscv64')
url="https://github.com/klemek/margen"
source=("${pkgname}-${pkgver}.tar.gz::https://github.com/klemek/margen/releases/download/v${pkgver}/${pkgname}-${pkgver}.tar.gz")
sha256sums=('e35368e963dbc81e94c4fab50cf2aa5d0f56caf6079e204ca4608eb9835670bc')
srcdir=build

build() {
  cd "$srcdir/$pkgname-$pkgver"
  ./configure --prefix=/usr
  make
}

package() {
  cd "$srcdir/$pkgname-$pkgver"
  sudo make DESTDIR="$pkgdir" install
}
