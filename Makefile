DESTDIR :=
PREFIX  := /usr/local

includedir = $(PREFIX)/include

MKDIR         := mkdir -p
RM            := rm -f
INSTALL       := install -c
INSTALL_DATA   = $(INSTALL) -m 644
INSTALL_HEADER = $(INSTALL_DATA)

default: help

check:

install: lmdb++.h
	$(INSTALL_HEADER) $^ $(DESTDIR)$(includedir)

uninstall:
	$(RM) $(DESTDIR)$(includedir)/lmdb++.h

clean:
	$(RM) *~

help:
	@echo 'Install the <lmdb++.h> header file using `make install`.'

.PHONY: check install uninstall clean help
