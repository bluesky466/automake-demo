AM_CPPFLAGS = -I$(top_srcdir)/src \
			  -std=c++11

bin_PROGRAMS = example
example_SOURCES = example.cpp

example_LDADD = -L$(top_builddir)/src \
				-leasylog
