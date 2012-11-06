.if !defined(UTIL_MK)
UTIL_MK=1

.include "prefs.mk"

UTIL_DIR?=${COMMON_DIR}
UTIL_HDRS=gu_util.h
UTIL_SRCS=gu_util.cpp

UTIL=${BUILDDIR}/.util-cookie

.for hdr in ${UTIL_HDRS}
UTIL_HFILES+=${UTIL_DIR}/${hdr}
.endfor

all: all-real		# make sure all is the first target

.for src in ${UTIL_SRCS}
OBJS+=${BUILDDIR}/${src:.cpp=.o}
${BUILDDIR}/${src:.cpp=.o}: ${BD} ${UTIL_DIR}/${src} ${UTIL_HFILES}
	${SAY} "compiling C++  ${src} (util)"
	$E${CXX} ${UTIL_CPPFLAGS} ${CPPFLAGS} ${CXXFLAGS} ${WFLAGS} \
		-c -o ${BUILDDIR}/${src:.cpp=.o} ${UTIL_DIR}/${src}
.endfor

.endif # UTIL_MK
