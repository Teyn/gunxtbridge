.include "whiteboard_flags.mk"
.include "util.mk"
.include "prefs.mk"
.include "dependencies.mk"

WHITEBOARD_COMMON_HDRS=Whiteboard.h WBMsg.h WBFunctor.h WhiteboardConstants.h RemoteWhiteboard.h
.ifdef USE_REMOTE_WHITEBOARD
WHITEBOARD_REMOTE_HDRS=guudpBridgeBroadcaster.h guudpBridgeListener.h guudpBridgeManager.h guudpbridgenetworkutil.h guudpbridgenetworkconfig.h
.endif #USE_REMOTE_WHITEBOARD


WB_DIR?=${GUNAO_DIR}/posix/gusimplewhiteboard

WHITEBOARD_PRIVATE_CCS=Whiteboard.cc WhiteboardConstants.cc
.ifdef USE_REMOTE_WHITEBOARD
WHITEBOARD_PRIVATE_CCS+=RemoteWhiteboard.cc
WHITEBOARD_REMOTE_SRCS+=guudpBridgeBroadcaster.cpp guudpBridgeListener.cpp guudpBridgeManager.cpp guudpbridgenetworkutil.cpp
.endif #USE_REMOTE_WHITEBOARD
WHITEBOARD_PRIVATE_CS=gusimplewhiteboard.c
WHITEBOARD_PRIVATE_HDRS=gusimplewhiteboard.h
WHITEBOARD_PRIVATE_CPPFLAGS=-D_SVID_SOURCE -I${COMMON_DIR}
WHITEBOARD_PRIVATE_WFLAGS=-Wno-unknown-pragmas

SPECIFIC_LIBS+=${DISPATCH_LIBS}


HOST_CPPFLAGS:=-I${WB_DIR} -I${COMMON_DIR} ${HOST_CPPFLAGS}

SPECIFIC_LIBS+=-lpthread

.for hdr in ${WHITEBOARD_COMMON_HDRS}
WHITEBOARD_HDRS+=${WB_DIR}/${hdr}
.endfor
.for hdr in ${WHITEBOARD_PRIVATE_HDRS}
WHITEBOARD_P_HDRS+=${WB_DIR}/${hdr}
.endfor
.for hdr in ${WHITEBOARD_REMOTE_HDRS}
WHITEBOARD_P_HDRS+=${WB_DIR}/guudpbridge/${hdr}
.endfor

WB=${BUILDDIR}/.whiteboard-cookie

all: all-real		# make sure all is the first target



.for src in ${WHITEBOARD_COMMON_SRCS}
OBJS+=${BUILDDIR}/${src:.cpp=.o}
${BUILDDIR}/${src:.cpp=.o}: ${BD} ${WB_DIR}/${src} ${WHITEBOARD_HDRS}
	${SAY} "compiling G++  ${src} (whiteboard common)"
	$E${GXX} ${WHITEBOARD_CPPFLAGS} ${CPPFLAGS} ${CXXFLAGS} ${WFLAGS} \
		-c -o ${BUILDDIR}/${src:.cpp=.o} ${WB_DIR}/${src}
.endfor
.for src in ${WHITEBOARD_PRIVATE_SRCS}
OBJS+=${BUILDDIR}/${src:.cpp=.o}
${BUILDDIR}/${src:.cpp=.o}: ${BD} ${WB_DIR}/${src} ${WHITEBOARD_HDRS} ${WHITEBOARD_P_HDRS}
	${SAY} "compiling G++  ${src} (whiteboard private)"
	$E${GXX} ${WHITEBOARD_PRIVATE_CPPFLAGS} ${WHITEBOARD_CPPFLAGS} ${CPPFLAGS} ${CXXFLAGS} ${WFLAGS} \
		-c -o ${BUILDDIR}/${src:.cpp=.o} ${WB_DIR}/${src}
.endfor
.for src in ${WHITEBOARD_PRIVATE_CCS}
OBJS+=${BUILDDIR}/${src:.cc=.o}
${BUILDDIR}/${src:.cc=.o}: ${BD} ${WB_DIR}/${src} ${WHITEBOARD_HDRS} ${WHITEBOARD_P_HDRS}
	${SAY} "compiling C++  ${src} (whiteboard)"
	$E${CXX} ${WHITEBOARD_PRIVATE_CPPFLAGS} ${WHITEBOARD_CPPFLAGS} ${CPPFLAGS} ${CXXFLAGS} ${WFLAGS} \
		-c -o ${BUILDDIR}/${src:.cc=.o} ${WB_DIR}/${src}
.endfor
.for src in ${WHITEBOARD_PRIVATE_CS}
OBJS+=${BUILDDIR}/${src:.c=.o}
${BUILDDIR}/${src:.c=.o}: ${BD} ${WB_DIR}/${src} ${WHITEBOARD_HDRS} ${WHITEBOARD_P_HDRS}
	${SAY} "compiling C    ${src} (whiteboard)"
	$E${CC} ${WHITEBOARD_PRIVATE_CPPFLAGS} ${WHITEBOARD_CPPFLAGS} ${CPPFLAGS} ${CFLAGS} ${LANGFL} ${WHITEBOARD_PRIVATE_WFLAGS} \
		-c -o ${BUILDDIR}/${src:.c=.o} ${WB_DIR}/${src}
.endfor
.for src in ${WHITEBOARD_REMOTE_SRCS}
OBJS+=${BUILDDIR}/${src:.cpp=.o}
${BUILDDIR}/${src:.cpp=.o}: ${BD} ${WB_DIR}/guudpbridge/${src} ${WHITEBOARD_HDRS} ${WHITEBOARD_P_HDRS}
	${SAY} "compiling G++  ${src} (whiteboard remote)"
	$E${GXX} ${WHITEBOARD_REMOTE_CPPFLAGS} ${WHITEBOARD_CPPFLAGS} ${CPPFLAGS} ${CXXFLAGS} ${WFLAGS} \
                -c -o ${BUILDDIR}/${src:.cpp=.o} ${WB_DIR}/guudpbridge/${src}
.endfor
