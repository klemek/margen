pkgname=margen
pkgver=1.2.3
pkgrel=1
pkgdesc="Generate a marble-like pattern bitmap image, blazing fast."
arch=('i686' 'pentium4' 'x86_64' 'arm' 'armv7h' 'armv6h' 'aarch64' 'riscv64')
url="https://github.com/klemek/margen"
source=("${pkgname}-${pkgver}.tar.gz::https://github.com/klemek/margen/releases/download/v${pkgver}/${pkgname}-${pkgver}.tar.gz")
sha256sums=('6922843b9cd1bcbca1dc65ca2cac1e4bf590487e77a06e21969a3432dc74963b')
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
