
ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = \
	lgpl3_0.txt

####################################
# Some helper targets

astyle:
	astyle -A1 -T4 -K -N -w -U -c -n -R $(srcdir)/*.h
	astyle -A1 -T4 -K -N -w -U -c -n -R $(srcdir)/*.inl
	astyle -A1 -T4 -K -N -w -U -c -n -R $(srcdir)/*.cpp

####################################
# Hook to make the ChangeLog
dist-hook:
	@if test -d "$(top_srcdir)/.git"; \
	then \
		echo Creating ChangeLog && \
		( cd "$(top_srcdir)" && \
		  echo '# Generated by Makefile. Do not edit.'; echo; \
		  build-aux/missing --run git log --shortstat ) > ChangeLog.tmp \
		&& mv -f ChangeLog.tmp $(top_distdir)/ChangeLog \
		|| ( rm -f ChangeLog.tmp ; \
		     echo Failed to generate ChangeLog >&2 ); \
	else \
		echo A git clone is required to generate a ChangeLog >&2; \
	fi

######################################

noinst_LTLIBRARIES = liboogl.la

# Hack below...
liboogl_la_CPPFLAGS = -I./oobase/include -I../oobase/include
# Hack above

liboogl_la_CFLAGS = $(PTHREAD_CFLAGS)
liboogl_la_CXXFLAGS = $(PTHREAD_CFLAGS)
liboogl_la_LDFLAGS = $(PTHREAD_LIBS)

liboogl_la_LIBADD = -lglfw -lGL

if WIN32
liboogl_la_CPPFLAGS += -D_WIN32_WINNT=0x0502
else
liboogl_la_LIBADD += -lX11 -lXrandr -lXi -lXxf86vm -lXcursor -lXinerama -lrt
endif

liboogl_la_SOURCES = \
	src/Window.cpp \
	src/Framebuffer.cpp \
	src/State.cpp \
	src/StateFns.cpp \
	src/Shader.cpp \
	src/Texture.cpp \
	src/BufferObject.cpp \
	src/VertexArrayObject.cpp
