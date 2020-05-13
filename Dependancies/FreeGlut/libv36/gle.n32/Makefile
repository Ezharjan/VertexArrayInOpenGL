#!smake
#
# Copyright (c) Mark J. Kilgard, 1995, 1997.
#

TOP = ../..

X=XXX
sinclude $(TOP)/lib/gle/Makefile.sgi
sinclude ObjectType.mk
CANNOTATE=

LDIRT += $(SRCS) $(HDRS)

# Need to copy to avoid timestamp problems.
$(SRCS) $(SRCSSEMIGENS) $(SRCGENS) $(HDRS) : $(TOP)/lib/gle/$@
	$(RM) $@
	cp $(TOP)/lib/gle/$@ $@
	chmod 444 $@

$(SRCS) : $(HDRS)
