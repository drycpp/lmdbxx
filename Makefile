DESTDIR  :=
PREFIX   := /usr/local

CPPFLAGS := -I.
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

help:
	@echo 'Install the <lmdb++.h> header file using `make install`.'

check: check.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDADD) && ./$@

example: example.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDADD) && ./$@

%.o: %.cc lmdb++.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

install: lmdb++.h
	$(INSTALL_HEADER) $^ $(DESTDIR)$(includedir)

uninstall:
	$(RM) $(DESTDIR)$(includedir)/lmdb++.h

clean:
	$(RM) README.html README.md check example *.o *~

doxygen: README.md
	doxygen Doxyfile

README: README.html README.md

README.html: README.rst
	pandoc -s -f rst -t html5 -S -o $@ $<

README.md: README.rst
	pandoc -s -f rst -t markdown_github -o - $< | tail -n +5 > $@

.PHONY: help check example install uninstall clean doxygen
