#! smake
#
# Copyright (c) Mark J. Kilgard, 1997.
#
include $(ROOT)/usr/include/make/commondefs

TOP = ../..

TARGETS = libmui.a

LN = ln -s
MV = mv
RM = -rm -rf

LCOPTS = -I$(TOP)/include -fullwarn 
LWOFF = ,813,852,827,826
LDIRT = *~ *.bak

SRCS = gizmo.c glutmui.c displaylist.c uicolor.c miscui.c mui.c vslider.c \
	 textlist.c button.c pulldown.c hslider.c

OBJS = $(SRCS:.c=.o)

default: $(TARGETS)

sinclude ObjectType.mk

libmui.a: $(OBJS)
	$(RM) $@
	$(AR) crl $@ $(OBJS)

include $(COMMONRULES)
