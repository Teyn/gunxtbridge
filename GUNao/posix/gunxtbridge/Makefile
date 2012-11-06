#
#	$Id: 8a9634944be7f33518663c9a51a1da0c5fc8fec5 $
#
# gu nxt make interface Makefile
#
#
BIN=gunxtinterfacemodule

ALL_TARGETS=host 

CPP_SRCS=gunxtinterfacemodule.cpp gunxtinterface.cpp
C_SRCS=gunxtbridge_wbmsg.c 
HDRS=gunxtinterface.h gunxtbridge_wbmsg.h gumessagecontent.h 

.include "../../mk/whiteboard.mk" 
.include "../../mk/gunxtinterfacemodule.mk"	# required for whiteboard clients
.include "../../mk/mipal.mk"		# comes last!
