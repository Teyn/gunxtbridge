#	$Id$
#
# MiPAL cross platform make infrastructure

.if !defined(PREFS_MK)
PREFS_MK=1

PREFIX?=/usr/local
SRCDIR!=pwd
MODULE_BASE!=basename ${SRCDIR:Q}
BIN_BASE!=echo ${MODULE_BASE:Q} | sed 's/module$$//'
BIN?=${BIN_BASE}
MODULE!=echo "${BIN}" | tr '[:lower:]' '[:upper:]'

ALL_TARGETS?=host
TEST_TARGETS?=test

UNAME!=uname
OS!=if [ -z "${TARGET}" ]; then echo "${UNAME}" ; else echo "${TARGET}" ; fi

.ifdef VERBOSE
E?=
SAY=@echo >/dev/null
.else
E?=@
SAY=@echo
.endif

DEFAULT_TARGET?=nao
DEFAULT_TARGET_BUILDDIR?=build.${DEFAULT_TARGET}${LOCALEXT}

DBG?=${CFLAGS}
WFLAGS?=-Werror -Wno-unknown-pragmas

USE_READLINE?=no
READLINE_CPPFLAGS?=	-DUSE_READLINE=1
READLINE_LIB?=		-lreadline

GMAKE!=which gnumake gmake make | head -n1 || true
GMAKEFLAGS=${MAKEFLAGS:C/-J//g:C/[0-9][0-9]*,[0-9][0-9]*//g}

RM?=rm -f
LN?=ln
MKDIR?=mkdir -p
TOUCH?=touch
HDOC?=headerdoc2html
GDOC?=gatherheaderdoc
DOXY?=doxygen
DOXYGEN_CONFIG?=Doxyfile
HDOC_DEFAULT_CONFIG?=headerdoc.conf

.if exists(${HDOC_DEFAULT_CONFIG})
HDOC_CONFIG?=${HDOC_DEFAULT_CONFIG}
.endif

DOCUMENTATION?=documentation

DOC_HDRS?=${HDRS}

HDOC_FLAGS?=-q -j -t -C
.ifdef HDOC_CONFIG
HDOC_FLAGS+=-c ${HDOC_CONFIG}
.endif

HOUT?=${DOCUMENTATION}/`basename ${HDOC}`.out
GOUT?=${DOCUMENTATION}/`basename ${GDOC}`.out
DOUT?=${DOCUMENTATION}/`basename ${DOXY}`.out

ROBOT_TARGET=robot
ROBOT_LOCAL_TARGET=robot-local

.ifdef LOCAL
LOCALEXT=-local
LOCAL_CPPFLAGS=-D${MODULE}_IS_REMOTE_OFF -D${MODULE}_IS_LOCAL_ON -DIS_REMOTE_OFF -DIS_LOCAL_ON
.else
LOCAL=
LOCAL_CPPFLAGS=-D${MODULE}_IS_REMOTE_ON -D${MODULE}_IS_LOCAL_OFF -DIS_REMOTE_ON -DIS_LOCAL_OFF
.endif

.ifdef TARGET_PLATFORM
BUILD_CATEGORY=-${TARGET_PLATFORM}
.endif

.ifdef TARGET
BUILDDIR=build.${TARGET}${BUILD_CATEGORY}${LOCALEXT}
.  include "${TARGET}.mk"
.else
BUILDDIR=build.host${LOCALEXT}
.  include "${DEFAULT_TARGET}.mk"
.endif
.include "${UNAME}.mk"

LANGFL?=-std=c99 -Wall
CXXLANGFL?=-std=c++11

BD=${BUILDDIR}/.cookie
PB=${BUILDDIR}/.pre-build-cookie
DD=${DOCUMENTATION}/.documentation-cookie

COMMON_SUBDIR=Common
GUNAO_DIR_SEARCH=.. ../.. ../../.. ../../../.. ../../../../..

MIPAL_DIR!=( for i in ${GUNAO_DIR_SEARCH} ; do				\
	( if cd $$i/GUNao/${COMMON_SUBDIR} 2>/dev/null && [ -e DONT_PUT_FILES_HERE ] ; then cd ../.. 2>/dev/null && ( pwd -P 2>/dev/null || pwd ) ; fi ); done ) |\
       	head -n 1
GUNAO_DIR=${MIPAL_DIR}/GUNao
COMMON_DIR=${GUNAO_DIR}/${COMMON_SUBDIR}
MK_DIR=${GUNAO_DIR}/mk
POSIX_DIR=${GUNAO_DIR}/posix
NAO_DIR=${GUNAO_DIR}/nao
MACOSX_DIR=${GUNAO_DIR}/macosx
MODULE_RELDIR!=echo ${SRCDIR:Q} | sed 's|.*GUNao/||'

.ifndef DONT_INCLUDE_COMMON_DIR
HOST_CPPFLAGS+=-I${COMMON_DIR}
.endif

OUTFLAGS+=${HOST${LOCAL}_OUTFLAGS}

NEED_SOAP?=no
.if ${NEED_SOAP:M[yY][eE][sS]}
SPECIFIC_CFLAGS+=${HOST_SOAP_CFLAGS}
SPECIFIC_LDFLAGS+=${HOST_SOAP_LDFLAGS}
SPECIFIC_LIBS+=${SOAPLIB}
.endif

.if ${USE_READLINE:M[yY][eE][sS]}
SPECIFIC_CPPFLAGS+=${READLINE_CPPFLAGS}
SPECIFIC_LIBS+=${READLINE_LIB}
.endif

.endif # PREFS_MK
