#! smake
#
# Copyright (c) Mark J. Kilgard, 1995.
#
include $(ROOT)/usr/include/make/commondefs

# NOTE:  In my GLUT development tree, many of the C source files for
# GLUT are generated.  For this reason, "make full_clobber" will remove
# these generated C files, while "make clobber" will not.

TOP = ../..

TARGETS = libgle.a

LN = ln -s
MV = mv
RM = -rm -rf

HDRS = \
	copy.h \
	extrude.h \
	gutil.h \
	intersect.h \
	port.h \
	rot.h \
	segment.h \
	tube_gc.h \
	vvector.h

SRCS = \
	ex_angle.c \
	ex_cut_round.c \
	ex_raw.c \
	extrude.c \
	intersect.c \
	round_cap.c \
	segment.c \
	texgen.c \
	\
	rot_prince.c \
	rotate.c \
	urotate.c \
	view.c

OBJS = $(SRCS:.c=.o)

LCDEFS = -DOPENGL_10 -DAUTO_TEXTURE -D__GUTIL_DOUBLE

LCOPTS = -I$(TOP)/include -fullwarn 
LWOFF = ,813,852,827,826
LDIRT = *~ *.bak

default: $(TARGETS)

sinclude ObjectType.mk

$(SRCS) : $(HDRS)

libgle.a : $(OBJS)
	$(RM) $@
	$(AR) crl $@ $(OBJS)

symcheck: libglut.a
	-nm -Bo libgle.a | grep -v ' d ' | grep -v ' T gle' | grep -v ' D gle' | grep -v ' U ' | grep -v ' T __gle' | grep -v ' t ' | grep -v ' b ' | grep -v ' D __gle' | grep -v ' B __gle'

include $(COMMONRULES)
