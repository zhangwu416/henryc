INCLUDES=-I$(top_srcdir)/henrylib/myutility

#CXXFLAGS = -Wall -g -O2 -fPIC
AM_CPPFLAGS = -Wall -O2  -fPIC

noinst_LTLIBRARIES = libmythread.la
libmythread_la_LIBFLAGS =
libmythread_la_LIBADD =

libmythread_la_SOURCES = \
			lock.cpp \
			thread.cpp \
			thread_group.cpp
