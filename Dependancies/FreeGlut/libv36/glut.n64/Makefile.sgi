#!smake
#
# Copyright (c) Mark J. Kilgard, 1995, 1997.
#

TOP = ../..

X=XXX
sinclude $(TOP)/lib/glut/Makefile.sgi
sinclude ObjectType.mk
CANNOTATE=

LDIRT += $(SRCS) $(SRCSSEMIGENS) $(SRCGENS) $(HDRS)

# Need to copy to avoid timestamp problems.
$(SRCS) $(SRCSSEMIGENS) $(SRCGENS) $(HDRS) : $(TOP)/lib/glut/$@
	$(RM) $@
	cp $(TOP)/lib/glut/$@ $@
	chmod 444 $@

$(SRCS) $(SRCSSEMIGENS) $(SRCGENS): $(HDRS)

.ORDER: $(TOP)/lib/glut/glut_roman.c $(TOP)/lib/glut/glut_mroman.c

$(TOP)/lib/glut/glut_roman.c:
	cd $(TOP)/lib/glut ; $(MAKE) glut_roman.c

$(TOP)/lib/glut/glut_mroman.c:
	cd $(TOP)/lib/glut ; $(MAKE) glut_mroman.c
