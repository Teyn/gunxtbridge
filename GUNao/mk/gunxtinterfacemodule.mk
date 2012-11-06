.include "prefs.mk"
NXTHOME=${HOME}/bin/nxtpp0-5.d
NXT_DIR?=${GUNAO_DIR}/nxt/gunxtbridge
NXT_WB_HDRS=${NXT_WB_SRCS:.c=.h}

NXT_CPPFLAGS?=-I${NXTHOME}/include -I${NXT_DIR}

.for hdr in ${NXT_WB_HDRS}
NXT_HDRS+=${NXT_DIR}/${hdr}
.endfor


SPECIFIC_CPPFLAGS+=${NXT_CPPFLAGS}
SPECIFIC_LIBS+= -lstdc++ -lnxtpp -lusb

all: all-real		# make sure all is the first target

.for src in ${NXT_WB_SRCS}
OBJS+=${BUILDDIR}/${src:.c=.o}
${BUILDDIR}/${src:.c=.o}: ${NXT_DIR}/${src} ${NXT_HDRS}
	${SAY} "compiling C    ${src} (nxt whiteboard messages)"
	$E${CC} ${NXT_CPPFLAGS} ${CPPFLAGS} ${CFLAGS} ${LFLAGS} ${WFLAGS} \
		-c -o ${BUILDDIR}/${src:.c=.o} ${NXT_DIR}/${src}
.endfor
