DESTDIR  :=
PREFIX   := /usr/local

CPPFLAGS :=
CXXFLAGS := -g -O0 -std=c++11 -Wall -Werror
LDFLAGS  :=
LDADD    := -llmdb

includedir = $(PREFIX)/include

MKDIR         := mkdir -p
RM            := rm -f
INSTALL       := install -c
INSTALL_DATA   = $(INSTALL) -m 644
INSTALL_HEADER = $(INSTALL_DATA)

default: help

check: test.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDADD)

%.o: %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

install: lmdb++.h
	$(INSTALL_HEADER) $^ $(DESTDIR)$(includedir)

uninstall:
	$(RM) $(DESTDIR)$(includedir)/lmdb++.h

clean:
	$(RM) check *.o *~

help:
	@echo 'Install the <lmdb++.h> header file using `make install`.'

.PHONY: install uninstall clean help
