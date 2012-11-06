#
# Cross compilation make file for nao's
#
ROBOT?=tuon.local.
CTC_DIR?=${OE_CROSS_DIR}
ARCH_i686=atom
ARCH_i586=geode
ARCHS?=${ARCH_i686} ${ARCH_i586}
CPUS=i686 i586
.for cpu in ${CPUS}
CPU_${ARCH_${cpu}}=${cpu}
.endfor
.for arch in ${ARCHS}
DEFAULT_TARGET_BUILDDIR_${arch}?=build.${DEFAULT_TARGET}-${arch}${LOCALEXT}
.endfor
TARGET_PLATFORM?=atom
TARGET_GCCARCH?=${TARGET_PLATFORM}-linux
TARGET_CPU?=${CPU_${TARGET_PLATFORM}}
CROSS?=${CTC_DIR}/cross/${TARGET_PLATFORM}
CROSS_GCCARCH=${TARGET_CPU}-linux
CROSS_BIN=${CROSS}/bin
CTC_LIN?=${CROSS}
CTC_BIN?=${CTC_LIN}/bin
CTC_LIB?=${CTC_LIN}/lib
STAGING?=${CTC_DIR}/staging/${TARGET_GCCARCH}	# sysroot
SOAPDIR=${AL_DIR}/include/gsoap
SOAPCXX=soapcpp2
.ifndef TARGET_GCC
TARGET_GCC=${CROSS_BIN}/${CROSS_GCCARCH}-gcc
TARGET_GXX=${CROSS_BIN}/${CROSS_GCCARCH}-g++
.endif
.ifndef TARGET_CC
.  ifndef TARGET_USE_CLANG
TARGET_CC=${TARGET_GCC}
.  else
TARGET_CC!=which {{,/Volumes/*}/Xcode4*/usr/{local/,}bin/,}clang ${TARGET_GCC} 2>/dev/null | head -n1
TARGET_TRIPLE?=-ccc-host-triple ${TARGET_CPU}-elf
.  endif
.endif
.ifndef TARGET_CXX
.  ifndef TARGET_USE_CLANG
TARGET_CXX=${TARGET_GXX}
.  else
TARGET_CXX!=which {/{,Volumes/*/}Xcode4*/usr/{local/,}bin/,}clang++ ${TARGET_GXX} 2>/dev/null | head -n1
.  endif
.endif
AL_ARCH?=i686-pc-linux-gnu
AL_GCC?=${CROSS}/lib/gcc/${AL_ARCH}/4.4.3
TARGET_LD=${CROSS_BIN}/${CROSS_GCCARCH}-ld
TARGET_LDFLAGS=--sysroot ${STAGING} -lgcc -L${STAGING}/lib -L${STAGING}/usr/lib\
		-L${CTC_LIB}/lib					\
		-L${CROSS}/lib/gcc/${CROSS_GCCARCH}/4.7.0		\
		-L${AL_GCC} -lc -lstdc++ -ldl -lrt			\
		-L${STAGING}/usr/local/lib				\
		-Wl,-R/usr/local/lib
TARGET_CPPFLAGS+=--sysroot ${STAGING}					\
		-I${STAGING}/usr/include				\
		-I${CROSS}/lib/gcc/${CROSS_GCCARCH}/4.7.0/include	\
		-I${AL_GCC}/include					\
		-I${AL_GCC}/include/g++-v4 				\
		-I${AL_GCC}/include/g++-v4/${AL_ARCH}	 		\
		-I${CROSS}/${AL_ARCH}/sys-include		\
		-I${CROSS}/${CROSS_GCCARCH}/sys-include			\
		-I${CROSS}/${CROSS_GCCARCH}/include			\
		-I${CROSS}/${CROSS_GCCARCH}/include/c++			\
		-I${STAGING}/usr/include/c++				\
		-I${STAGING}/usr/include/c++/${CROSS_GCCARCH}		\
		-I${STAGING}/usr/local/include				\
		-I${CTC_LIN}/include/c++				\
		-I${CTC_LIN}/include/c++/backward			\
		-I${CTC_LIN}/include/c++/${CROSS_GCCARCH}		\
		-I${CTC_LIN}/include					\
		-I${STAGING}/${CROSS_GCCARCH}/usr/include		\
		-I${STAGING}/${CROSS_GCCARCH}/usr/local/include		\
		-I${STAGING}/${CROSS_GCCARCH}/usr/include/bits		\
		-I${SOAPDIR}
TARGET_CONFIGURE_ARGS+=--target=${CROSS_GCCARCH} --host=${CROSS_GCCARCH} \
		       --with-sysroot=${STAGING:Q} LDFLAGS=${TARGET_LDFLAGS:Q} \
		       CPPFLAGS=${TARGET_CPPFLAGS:Q} CC=${TARGET_CC:Q}	\
		       CXX=${TARGET_CXX:Q} LD=${TARGET_LD:Q}
TARGET_CONFIGURE_FLAGS=PATH=${TARGET_PATH}
TARGET_BUILD_FLAGS=PATH=${TARGET_PATH}
TARGET_LANGFL?=-std=c99 -Wall
TARGET_CXXLANGFL?=
#.if exists(${AL_DIR}/lib/libalippc.a) || exists(${AL_DIR}/lib/libalippc.so)
#TARGET_ALALIBS+=alippc
#.else
#TARGET_ALALIBS+=ippc
#.endif
TARGET_ALALIBS+=boost_serialization-mt
TARGET_ALALIBS+=boost_system-mt
TARGET_ALALIBS+=boost_date_time-mt
TARGET_ALALIBS+=boost_thread-mt
.if exists(${AL_DIR}/lib/liblibcore.a) || exists(${AL_DIR}/lib/liblibcore.so) || exists(${AL_DIR}/lib/liblibcore.dylib)
TARGET_ALALIBS+=libcore
.else
#TARGET_ALALIBS+=alcore
.endif
.if exists(${AL_DIR}/lib/liballog.a) || exists(${AL_DIR}/lib/liballog.so) || exists(${AL_DIR}/lib/liballog.dylib)
TARGET_ALALIBS+=allog
.endif
TARGET_ALALIBS+=pthread
TARGET_ALALIBS+=boost_signals-mt
.if exists(${AL_DIR}/lib/libaltools.a) || exists(${AL_DIR}/lib/libaltools.so) || exists(${AL_DIR}/lib/libaltools.dylib)
TARGET_ALALIBS+=altools
.else
TARGET_ALALIBS+=tools
.endif
TARGET_ALALIBS+=boost_system-mt
TARGET_ALALIBS+=boost_filesystem-mt
#.if exists(${AL_DIR}/lib/libalfindippc.a) || exists(${AL_DIR}/lib/libalfindippc.so) || exists(${AL_DIR}/lib/libalfindippc.dylib)
#TARGET_ALALIBS+=alfindippc
#.else
#TARGET_ALALIBS+=findippc
#.endif
#.if exists(${AL_DIR}/lib/libalfactory.a) || exists(${AL_DIR}/lib/libalfactory.so) || exists(${AL_DIR}/lib/libalfactory.dylib)
#TARGET_ALALIBS+=alfactory
#.else
#TARGET_ALALIBS+=libfactory
#.endif
TARGET_ALALIBS+=python2.6
TARGET_ALALIBS+=boost_date_time-mt
TARGET_ALALIBS+=boost_thread-mt
#TARGET_ALALIBS+=libcore
TARGET_ALALIBS+=pthread
TARGET_ALALIBS+=boost_signals-mt
#TARGET_ALALIBS+=tools
TARGET_ALALIBS+=boost_filesystem-mt
#TARGET_ALALIBS+=findippc
TARGET_ALALIBS+=dl
TARGET_ALALIBS+=rttools
.if exists(${AL_DIR}/lib/libalthread.a) || exists(${AL_DIR}/lib/libalthread.so) || exists(${AL_DIR}/lib/libalthread.dylib)
TARGET_ALALIBS+=althread
.else
TARGET_ALALIBS+=libthread
.endif
.if exists(${AL_DIR}/lib/libalfile.a)
TARGET_ALALIBS+=alfile
.endif
TARGET_ALALIBS+=boost_program_options-mt
#TARGET_ALALIBS+=libfactory
TARGET_ALALIBS+=alasr
TARGET_ALALIBS+=alaudiotoolbox
TARGET_ALALIBS+=alaudiodevices
TARGET_ALALIBS+=albehavior
TARGET_ALALIBS+=albehaviorinfo
TARGET_ALALIBS+=albonjourdiscovery
TARGET_ALALIBS+=alerror
TARGET_ALALIBS+=alextractor
TARGET_ALALIBS+=allauncher
TARGET_ALALIBS+=alim
TARGET_ALALIBS+=allogremote
TARGET_ALALIBS+=almath
TARGET_ALALIBS+=almemoryfastaccess
TARGET_ALALIBS+=almodelutils
TARGET_ALALIBS+=almotionrecorder
TARGET_ALALIBS+=alparammanager
TARGET_ALALIBS+=alproject
TARGET_ALALIBS+=alresource
TARGET_ALALIBS+=alserial
TARGET_ALALIBS+=alsoundfilesplayer
TARGET_ALALIBS+=alstreamer
TARGET_ALALIBS+=althread
#TARGET_ALALIBS+=altts
TARGET_ALALIBS+=python2.6
.ifdef TARGET
SOAPLIB=-L${CTC_DIR}
.if exists(${AL_DIR}/lib/libalsoap.a) || exists(${AL_DIR}/lib/libalsoap.so)
SOAPLIB+=-lalsoap
.else
SOAPLIB+=-llibsoap
.endif
SOAPLIB+=-ltinyxml -lalvalue -lalcommon
.endif
.ifndef TARGET_ALLIBS
TARGET_ALLIBS=-Wl,-R/lib -Wl,-R/usr/lib -Wl,-R/home/nao/lib -Wl,-R/opt/naoqi/lib -Wl,-R/usr/local/lib -Wl,-R/opt/local/lib -Wl,-rpath,/home/nao/lib ${SOAPLIB}
.for alib in ${TARGET_ALALIBS}
TARGET_ALLIBS+=-l${alib}
.endfor
.endif

TARGET_ARCH?=-march=${TARGET_PLATFORM}
.if ${TARGET_CC} == ${TARGET_GCC}
TARGET_CC_ARCH?=${TARGET_ARCH}
.else
TARGET_CC_ARCH?=-march=${TARGET_CPU} ${TARGET_TRIPLE}
.endif

TARGET_SOAP_CFLAGS?=${TARGET_CC_ARCH}
TARGET_SOAP_LDFLAGS?=${TARGET_ARCH} -L${CTC_LIN}/lib ${COMMON_ALLDFLAGS}
TARGET_CFLAGS?=${TARGET_CC_ARCH}
TARGET_ALCFLAGS?=${TARGET_CC_ARCH}
TARGET_ALLDFLAGS=${TARGET_ARCH} -L${CTC_LIN}/lib ${COMMON_ALLDFLAGS}
TARGET_PATH?=${CROSS_BIN}:${CTC_BIN}:${CROSS}/libexec/gcc/i586-linux/4.3.3/:${PATH}
TARGET_OUTFLAGS=-rdynamic ${COMMON_OFLAGS}
TARGET_LOCAL_OUTFLAGS=-fPIC -shared -Wl,-soname,${OUTFILE_LOCAL} ${COMMON_OFLAGS}
TARGET_OUTFILE_LOCAL?=lib${BIN}.so

TARGET_PROFILE_FLAGS=-pg
TARGET_PROFILE_CFLAGS=${TARGET_CC_ARCH} ${TARGET_PROFILE_FLAGS}
TARGET_PROFILE_LDFLAGS=${TARGET_ARCH} ${TARGET_PROFILE_FLAGS}

.ifdef TARGET
OUTFILE_LOCAL=${TARGET_OUTFILE_LOCAL}

ZEROCONF_LIBS=-lavahi-client -lavahi-common
JPEG_LIBS?=-ljpeg
OPENCV_LIBS?=-lcxcore -lcv -lcvaux -lml
DISPATCH_LIBS?=-ldispatch -lpthread_workqueue -lkqueue
CC=${TARGET_CC}
CXX=${TARGET_CXX}
LD=${TARGET_LD}

LANGFL?=${TARGET_LANGFL}
CXXLANGFL?=${TARGET_CXXLANGFL}

COMMON_LDFLAGS=${TARGET_LDFLAGS}

HOST_ARCH=${TARGET_ARCH}
HOST_CC_ARCH=${TARGET_CC_ARCH}
HOST_LDFLAGS=${TARGET_LDFLAGS}
HOST_CFLAGS=${TARGET_CFLAGS}
HOST_CPPFLAGS=${TARGET_CPPFLAGS}
HOST_OUTFLAGS=${TARGET_OUTFLAGS}

HOST_SOAP_CFLAGS=${TARGET_SOAP_CFLAGS}
HOST_SOAP_LDFLAGS=${TARGET_SOAP_LDFLAGS}

HOST_ALLIBS=${TARGET_ALLIBS}
HOST_ALLDFLAGS=${TARGET_ALLDFLAGS}

HOST_LOCAL_ARCH=${TARGET_ARCH}
HOST_LOCAL_CC_ARCH=${TARGET_CC_ARCH}
HOST_LOCAL_LDFLAGS=${TARGET_LDFLAGS}
HOST_LOCAL_CFLAGS=${TARGET_CFLAGS}
HOST_LOCAL_CPPFLAGS=${TARGET_CPPFLAGS}
HOST_LOCAL_OUTFLAGS=${TARGET_LOCAL_OUTFLAGS}

HOST_LOCAL_ALLIBS=${TARGET_ALLIBS}
HOST_LOCAL_ALLDFLAGS=${TARGET_ALLDFLAGS}

HOST_PROFILE_FLAGS=${TARGET_PROFILE_FLAGS}
HOST_PROFILE_CFLAGS=${TARGET_PROFILE_CFLAGS}
HOST_PROFILE_LDFLAGS=${TARGET_PROFILE_LDFLAGS}

.ifdef TARGET_ALCPPFLAGS
HOST_ALCPPFLAGS=${TARGET_ALCPPFLAGS}
HOST_LOCAL_ALCPPFLAGS=${TARGET_ALCPPFLAGS}
.endif
.ifdef TARGET_ALCFLAGS
HOST_ALCFLAGS=${TARGET_ALCFLAGS}
HOST_LOCAL_ALCFLAGS=${TARGET_ALCFLAGS}
.endif
.ifdef TARGET_ALCXXFLAGS
HOST_ALCXXFLAGS=${TARGET_ALCXXFLAGS}
HOST_LOCAL_ALCXXFLAGS=${TARGET_ALCXXFLAGS}
.endif
.endif
