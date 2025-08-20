pkgname=margen
pkgver=1.2.4
pkgrel=1
pkgdesc="Generate a marble-like pattern bitmap image, blazing fast."
arch=('i686' 'pentium4' 'x86_64' 'arm' 'armv7h' 'armv6h' 'aarch64' 'riscv64')
url="https://github.com/klemek/margen"
source=("${pkgname}-${pkgver}.tar.gz::https://github.com/klemek/margen/releases/download/v${pkgver}/${pkgname}-${pkgver}.tar.gz")
sha256sums=('38fc6a66be97f6f77f9dffdbf75c214c7aa3ee8d1600b28506e943e6bfb93870')
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
