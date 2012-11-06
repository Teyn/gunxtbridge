PORTSDIR?=/usr
CXXLANGFL?=
SOAPDIR?=${AL_DIR}/include/gsoap
SOAPCXX?=${AL_DIR}/bin/soapcpp2
.ifndef SOAPLIB
SOAPLIB=-L${AL_DIR}/lib -Wl,-R${AL_DIR}/lib
.if exists(${AL_DIR}/lib/libalsoap.so)
SOAPLIB+=-lalsoap
.else
SOAPLIB+=-llibsoap
.endif
SOAPLIB+=-ltinyxml -lalvalue ${AL_DIR}/lib/_inaoqi.so -lboost_serialization-mt -lboost_system-mt -lboost_date_time-mt -lboost_thread-mt -lboost_signals-mt
.if exists(${AL_DIR}/lib/libaltools.so)
SOAPLIB+=-laltools
.else
SOAPLIB+=-ltools
.endif
SOAPLIB+=-lboost_system-mt -lboost_filesystem-mt
.if exists(${AL_DIR}/lib/libalcore.so)
SOAPLIB+=-lalcore
.else
SOAPLIB+=-llibcore
.endif
.if exists(${AL_DIR}/lib/libalutil.so)
SOAPLIB+=-lalutil
.else
SOAPLIB+=-lutil
.endif
.endif
CORESERVICES?=-lavahi-client -lavahi-common
ZEROCONF_LIBS?=${CORESERVICES}
JPEG_LIBS?=-ljpeg

DISPATCH_LIBS?=-ldispatch -lpthread_workqueue -lkqueue
OUTFILE=${BIN}
OUTFILE_LOCAL?=lib${BIN}.so
OUT=${OUTFILE${LOCAL}}
OUTPATH=${BUILDDIR}/${OUT}
COMMON_OFLAGS=-o ${OUTPATH}
COMMON_ALOFLAGS+=-Wl,-rpath,${AL_DIR}/lib ${COMMON_OFLAGS}
COMMON_ALLDFLAGS=
HOST_ARCH?=-m32 -march=i586
HOST_CPPFLAGS?=-I${SOAPDIR}
HOST_SOAP_CFLAGS?=${HOST_ARCH}
HOST_SOAP_LDFLAGS?=${HOST_ARCH} -L${AL_DIR}/lib 
HOST_ALCPPFLAGS?=-DNO_GLOBAL_NAMESPACES -DTIXML_USE_STL -DTIXML_USE_STL	\
		 -DTIXML_USE_STL -DTIXML_USE_STL
HOST_OUTFLAGS?=-rdynamic ${COMMON_OFLAGS}
HOST_LDFLAGS?=-lrt
HOST_ALCFLAGS?=
HOST_ALLDFLAGS?=${COMMON_ALLDFLAGS}
HOST_ALALIBS+=alvalue
HOST_ALALIBS+=alcommon
.if exists(${AL_DIR}/lib/libalippc.so)
HOST_ALALIBS+=alippc
.else
HOST_ALALIBS+=ippc
.endif
HOST_ALALIBS+=pthread
.if exists(${AL_DIR}/lib/libalfindippc.so)
HOST_ALALIBS+=alfindippc
.else
HOST_ALALIBS+=findippc
.endif
HOST_ALALIBS+=dl
HOST_ALALIBS+=rttools
HOST_ALALIBS+=rt
.if exists(${AL_DIR}/lib/libalthread.so)
HOST_ALALIBS+=althread
.else
HOST_ALALIBS+=libthread
.endif
HOST_ALALIBS+=boost_program_options-mt
.if exists(${AL_DIR}/lib/libalfactory.so)
HOST_ALALIBS+=alfactory
.else
HOST_ALALIBS+=libfactory
.endif
HOST_ALALIBS+=python2.6
HOST_ALALIBS+=boost_date_time-mt
HOST_ALALIBS+=boost_thread-mt
.if exists(${AL_DIR}/lib/libalcore.so)
HOST_ALALIBS+=alcore
.else
HOST_ALALIBS+=libcore
.endif
HOST_ALALIBS+=pthread
HOST_ALALIBS+=boost_signals-mt
.if exists(${AL_DIR}/lib/libaltools.so)
HOST_ALALIBS+=altools
.else
HOST_ALALIBS+=tools
.endif
HOST_ALALIBS+=boost_filesystem-mt
#HOST_ALALIBS+=findippc
HOST_ALALIBS+=dl
HOST_ALALIBS+=rttools
#HOST_ALALIBS+=libthread
HOST_ALALIBS+=boost_program_options-mt
#HOST_ALALIBS+=libfactory
#HOST_ALALIBS+=python2.6
.ifndef HOST_ALLIBS
HOST_ALLIBS=-Wl,-R${AL_DIR}/lib -Wl,-rpath,${AL_DIR}/lib ${SOAPLIB}
.for alib in ${HOST_ALALIBS}
HOST_ALLIBS+=-l${alib}
.endfor
.endif
HOST_LOCAL_ALCPPFLAGS?=${HOST_ALCPPFLAGS} -D${BIN}_EXPORTS
HOST_LOCAL_ALCFLAGS?=${HOST_ALCFLAGS} -fPIC
HOST_LOCAL_ALLDFLAGS+=${HOST_ARCH} -L${AL_DIR}/lib ${COMMON_ALLDFLAGS}
HOST_LOCAL_ALLIBS?=${HOST_ALLIBS}
HOST_LOCAL_ALOFLAGS?=${COMMON_ALOFLAGS}
HOST_LOCAL_OUTFLAGS?=-fPIC -shared -Wl,-soname,${OUTFILE_LOCAL} ${COMMON_OFLAGS}
.ifndef HOST_GCC
HOST_GCC!=which gcc
.endif
.ifndef HOST_CC
.  ifdef PROFILING
HOST_CC=${HOST_GCC}
.  else
HOST_CC!=which clang 2> /dev/null || which gcc
.  endif
.endif
.ifndef HOST_GXX
HOST_GXX!=which g++
.endif
.ifndef HOST_CXX
.  ifdef PROFILING
HOST_CXX=${HOST_GXX}
.  else
HOST_CXX!=which clang++ 2> /dev/null || which g++
.  endif
.endif

HOST_PROFILE_FLAGS?=-pg
HOST_PROFILE_CFLAGS?=${HOST_ARCH} ${HOST_PROFILE_FLAGS}
HOST_PROFILE_LDFLAGS?=${HOST_ARCH} ${HOST_PROFILE_FLAGS}

