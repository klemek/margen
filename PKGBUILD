pkgname=margen
pkgver=1.2.2
pkgrel=1
pkgdesc="Generate a marble-like pattern bitmap image, blazing fast."
arch=('i686' 'pentium4' 'x86_64' 'arm' 'armv7h' 'armv6h' 'aarch64' 'riscv64')
url="https://github.com/klemek/margen"
source=("${pkgname}-${pkgver}.tar.gz::https://github.com/klemek/margen/releases/download/v${pkgver}/${pkgname}-${pkgver}.tar.gz")
sha256sums=('41523e3c1250c4026e4914e757c4e137397d115568ed3f72691631ddd97777a1')
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
