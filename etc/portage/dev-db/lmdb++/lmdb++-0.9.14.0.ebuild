# Copyright 1999-2015 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

EAPI=5

DESCRIPTION="C++11 wrapper for the LMDB database library"
HOMEPAGE="http://lmdbxx.sourceforge.net/"
MY_P=${P/lmdb++/lmdbxx}
SRC_URI="mirror://sourceforge/lmdbxx/${PV}/${MY_P}.tar.gz"
S=${WORKDIR}/${MY_P}

LICENSE="public-domain"
SLOT="0"
KEYWORDS="~amd64 ~x86"

RDEPEND="dev-db/lmdb"

src_configure() {
	:
}

src_install() {
	emake PREFIX=/usr DESTDIR="${D}" install
	dodoc AUTHORS CREDITS INSTALL README TODO UNLICENSE VERSION
}
