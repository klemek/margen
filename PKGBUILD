pkgname=margen
pkgver=1.2.5
pkgrel=1
pkgdesc="Generate a marble-like pattern bitmap image, blazing fast."
arch=('i686' 'pentium4' 'x86_64' 'arm' 'armv7h' 'armv6h' 'aarch64' 'riscv64')
url="https://github.com/klemek/margen"
source=("${pkgname}-${pkgver}.tar.gz::https://github.com/klemek/margen/releases/download/v${pkgver}/${pkgname}-${pkgver}.tar.gz")
sha256sums=('ff4375dacec14bce1f67bb6964232c54b184f820aaad02fda4313c58d78133c6')
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
