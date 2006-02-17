bin_PROGRAMS = gbhed

gbhed_SOURCES = gbhed.c translation_fork.c translation_fork.h
gbhed_LDADD = $(DEPS_LIBS)

AM_CPPFLAGS = $(DEPS_CFLAGS) \
	      -DPIXMAPS_DIR=\""$(datadir)/pixmaps"\"
