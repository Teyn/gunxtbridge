#	$Id$
#
# MiPAL cross platform make infrastructure
.include "prefs.mk"

RBASE!=echo ${ROBOT:Q} | cut -f1 -d.
RMODEL!=grep -i ${RBASE:Q} ${NAO_DIR}/models.conf | cut -f2
.if ${RMODEL} != atom && ${RMODEL} != geode
RMODEL:=${TARGET_PLATFORM}
.endif

CUSTOM_LINKING?=no

.ifndef TARGET
CC=${HOST_CC}
GCC=${HOST_GCC}
CXX=${HOST_CXX}
GXX=${HOST_GXX}
.else
GXX=${CXX}
GCC=${CC}
.endif

HOST_CXXFLAGS?=${HOST_CFLAGS}
SPECIFIC_CXXFLAGS?=${SPECIFIC_CFLAGS}
LOCAL_CXXFLAGS?=${LOCAL_CFLAGS}

USING_CLANG!=if echo ${HOST_CC:Q} | grep -q clang ; then echo YES ; else echo NO ; fi

.if ${USING_CLANG:M[yY][eE][sS]}
HOST_CFLAGS+=${CLANG_CFLAGS}
.else
HOST_CFLAGS+=${GCC_CFLAGS}
.endif

.if ${USING_CLANG:M[yY][eE][sS]}
HOST_CXXFLAGS+=${CLANG_CXXFLAGS}
.else
HOST_CXXFLAGS+=${GCC_CXXFLAGS}
.endif

.ifdef PROFILING
PROFILING_CFLAGS=${HOST_PROFILE_CFLAGS}
PROFILING_LDFLAGS=${HOST_PROFILE_LDFLAGS}
.endif

CFLAGS:=${SPECIFIC_CFLAGS} ${DBG} ${PROFILING_CFLAGS} ${HOST_CFLAGS}
CXXFLAGS+=${SPECIFIC_CXXFLAGS} ${HOST_CXXFLAGS} ${LOCAL_CXXFLAGS}
CPPFLAGS+=${SPECIFIC_CPPFLAGS} ${HOST_CPPFLAGS} ${LOCAL_CPPFLAGS}
LDFLAGS+=${SPECIFIC_LDFLAGS} ${DBG} ${PROFILING_LDFLAGS} ${HOST_LDFLAGS}
LIBS+=${SPECIFIC_LIBS} ${HOST_LIBS}

RUNDIR?=.

.PHONY: all all-real
all: all-real
all-real: ${ALL_TARGETS} ${TEST_TARGETS}

.c.o:
	${SAY} "compiling C    $*.c"
	$E${CC} ${CPPFLAGS} ${CFLAGS} ${LANGFL} ${WFLAGS} -c -o $*.o $*.c

.SUFFIXES: .o .cpp
.cpp.o:
	${SAY} "compiling C++  $*.cpp"
	$E${CXX} ${CPPFLAGS} ${CXXFLAGS} ${CXXLANGFL} ${WFLAGS} -c -o $*.o $*.cpp

.SUFFIXES: .o .m
.m.o:
	${SAY} "compiling ObjC $*.m"
	$E${CC} ${CPPFLAGS} ${CFLAGS} ${LANGFL} ${WFLAGS} -c -o $*.o $*.m

.SUFFIXES: .pdf .tex .syntrax
.tex.pdf:
	${SAY} "running LaTeX: $*.tex"
	$Epdflatex ${LATEXFLAGS} $*
	$E[ ! -e $*.bib ] || bibtex $*
	$Epdflatex ${LATEXFLAGS} $*
	$Epdflatex ${LATEXFLAGS} $*

.syntrax.tex:
	${SAY} "proc. Syntrax: $*.syntrax"
	$Esyntrax -meta purpose.tex $*.syntrax

DOTATTR?=

.SUFFIXES: .svg .dot
.dot.svg:
	$Edot ${DOTATTR} -Tsvg < $*.dot | awk "/^..xml/ { o++; } { if (o < 2) print; }" > $*.svg

.SUFFIXES: .fig .dot
.dot.fig:
	$Edot ${DOTATTR} -Tfig $*.dot > $*.fig

.SUFFIXES: .pdf .dot
.dot.pdf:
	$Edot ${DOTATTR} -Tpdf $*.dot > $*.pdf

.SUFFIXES: .png .dot
.dot.png:
	$Edot ${DOTATTR} -Tpng $*.dot > $*.png

.SUFFIXES: .ps .dot
.dot.ps:
	$Edot ${DOTATTR} -Tps $*.dot > $*.ps

.SUFFIXES: .pdf .ps
.ps.pdf:
	$Eps2pdf $*.ps

.SUFFIXES: .pdf .eps
.eps.pdf:
	$Eps2pdf $*.eps

.for src in ${CPP_SRCS}
OBJS+=${BUILDDIR}/${src:.cpp=.o}
${BUILDDIR}/${src:.cpp=.o}: ${BD} ${src} ${HDRS}
	${SAY} "compiling C++  ${src}"
	$E${CXX} ${CPPFLAGS} ${CXXFLAGS} ${CXXLANGFL} ${WFLAGS}		\
		-c -o ${BUILDDIR}/${src:.cpp=.o} ${src}
.endfor
.for src in ${CC_SRCS}
OBJS+=${BUILDDIR}/${src:.cc=.o}
${BUILDDIR}/${src:.cc=.o}: ${BD} ${src} ${HDRS}
	${SAY} "compiling C++  ${src}"
	$E${CXX} ${CPPFLAGS} ${CXXFLAGS} ${CXXLANGFL} ${WFLAGS}		\
		-c -o ${BUILDDIR}/${src:.cc=.o} ${src}
.endfor
.for src in ${C_SRCS}
OBJS+=${BUILDDIR}/${src:.c=.o}
${BUILDDIR}/${src:.c=.o}: ${BD} ${src} ${HDRS}
	${SAY} "compiling C    ${src}"
	$E${CC} ${CPPFLAGS} ${CFLAGS} ${LANGFL} ${WFLAGS}		\
		-c -o ${BUILDDIR}/${src:.c=.o} ${src}
.endfor
.for src in ${OBJC_SRCS}
OBJS+=${BUILDDIR}/${src:.m=.o}
${BUILDDIR}/${src:.m=.o}: ${BD} ${src} ${HDRS}
	${SAY} "compiling ObjC ${src}"
	$E${CC} ${CPPFLAGS} ${CFLAGS} ${LANGFL} ${WFLAGS}		\
		-c -o ${BUILDDIR}/${src:.m=.o} ${src}
.endfor
.for src in ${MM_SRCS}
OBJS+=${BUILDDIR}/${src:.mm=.o}
${BUILDDIR}/${src:.mm=.o}: ${BD} ${src} ${HDRS}
	${SAY} "compiling OC++ ${src}"
	$E${CC} ${CPPFLAGS} ${CFLAGS} ${CXXLANGFL} ${WFLAGS}		\
		-c -o ${BUILDDIR}/${src:.mm=.o} ${src}
.endfor

.PHONY: host host-local local
host: ${OUTPATH}
host-local:
	$E${MAKE} ${MAKEFLAGS} LOCAL=_LOCAL ALL_TARGETS=host

local: robot robot-local

.PHONY: robot robot-local
robot:
.for rarch in ${ARCHS}
	$Eenv PATH=${TARGET_PATH:Q}					\
		${MAKE} ${MAKEFLAGS} TARGET=${DEFAULT_TARGET}		\
		TARGET_PLATFORM=${rarch} ALL_TARGETS=target
.endfor

robot-local:
.for rarch in ${ARCHS}
	$Eenv PATH=${TARGET_PATH:Q}					\
		${MAKE} ${MAKEFLAGS} LOCAL=_LOCAL			\
		TARGET=${DEFAULT_TARGET} TARGET_PLATFORM=${rarch}	\
		ALL_TARGETS=target
.endfor

.PHONY: atom atom-local
atom:
.for rarch in atom
	$Eenv PATH=${TARGET_PATH:Q}					\
		${MAKE} ${MAKEFLAGS} TARGET=${DEFAULT_TARGET}		\
		TARGET_PLATFORM=${rarch} ALL_TARGETS=target
.endfor

atom-local:
.for rarch in atom
	$Eenv PATH=${TARGET_PATH:Q}					\
		${MAKE} ${MAKEFLAGS} LOCAL=_LOCAL			\
		TARGET=${DEFAULT_TARGET} TARGET_PLATFORM=${rarch}	\
		ALL_TARGETS=target
.endfor

.PHONY: geode geode-local
geode:
.for rarch in geode
	$Eenv PATH=${TARGET_PATH:Q}					\
		${MAKE} ${MAKEFLAGS} TARGET=${DEFAULT_TARGET}		\
		TARGET_PLATFORM=${rarch} ALL_TARGETS=target
.endfor

geode-local:
.for rarch in geode
	$Eenv PATH=${TARGET_PATH:Q}					\
		${MAKE} ${MAKEFLAGS} LOCAL=_LOCAL			\
		TARGET=${DEFAULT_TARGET} TARGET_PLATFORM=${rarch}	\
		ALL_TARGETS=target
.endfor



.PHONY: target pre-build install install-local run kill
target: ${OUTPATH}

pre-build:
${PB}: ${BD}
	$E${MAKE} ${MAKEFLAGS} pre-build
	$E${TOUCH} ${PB}

${BD}:
	$E${MKDIR} ${BUILDDIR}
	$E${TOUCH} ${BD}

${OUTPATH}: ${PB} ${OBJS}
.if ${CUSTOM_LINKING:M[nN][oO]}
	${SAY} "linking output ${OUTPATH}"
	$E${CXX} ${SPECIFIC_OFLAGS} ${OUTFLAGS} ${LDFLAGS} ${OBJS} ${LIBS}
.ifdef LINK_FIXUP${TARGET}
	echo $E${LINK_FIXUP${TARGET}}
.endif
.endif

.if !target(install)
install: ${ROBOT${LOCAL}_TARGET}
	@chmod 0600 ${GUNAO_DIR:Q}/.ssh/id_${DEFAULT_TARGET}_rsa
	-ssh-add ${GUNAO_DIR:Q}/.ssh/id_${DEFAULT_TARGET}_rsa
.if defined(LOCAL) && ${LOCAL} == _LOCAL
	ssh nao@${ROBOT} mkdir -p naoqi/lib/naoqi ; \
	scp -p ${DEFAULT_TARGET_BUILDDIR_${RMODEL}:Q}/lib${BIN:Q}.so nao@${ROBOT}:naoqi/lib/naoqi/
.else
	scp -p ${MK_DIR:Q}/cdrun.sh nao@${ROBOT}:bin
	scp -p ${DEFAULT_TARGET_BUILDDIR_${RMODEL}:Q}/${BIN:Q} nao@${ROBOT}:bin
.endif
.endif

.if !target(install-local)
install-local:
	${MAKE} ${MAKEFLAGS} LOCAL=_LOCAL install
.endif

.if !target(run)
run:
	@chmod 0600 ${GUNAO_DIR:Q}/.ssh/id_${DEFAULT_TARGET}_rsa
	-ssh-add ${GUNAO_DIR:Q}/.ssh/id_${DEFAULT_TARGET}_rsa
	ssh nao@${ROBOT} /bin/sh /home/nao/bin/cdrun.sh ${RUNDIR:Q} /home/nao/bin/${BIN:Q} ${ARGS}
#	ssh nao@${ROBOT} /home/nao/bin/${BIN:Q} ${ARGS}
#	ssh nao@${ROBOT} cd ${RUNDIR:Q} '&&' /home/nao/bin/${BIN:Q} ${ARGS}
.endif

.if !target(kill)
kill:
	@chmod 0600 ${GUNAO_DIR:Q}/.ssh/id_${DEFAULT_TARGET:Q}_rsa
	-ssh-add ${GUNAO_DIR:Q}/.ssh/id_${DEFAULT_TARGET:Q}_rsa
	ssh nao@${ROBOT} killall ${BIN:Q}
.endif

.PHONY: documentation pre-doc doc post-doc
documentation: doc
doc: pre-doc real-doc post-doc
real-doc: ${DD}
pre-doc:
post-doc:

${DD}: ${DOC_HDRS}
	$E${MKDIR} ${DOCUMENTATION}
.ifndef USE_HEADERDOC
	${SAY} "building documentation (${DOXY})"
	$Eif [ ! -e "${DOXYGEN_CONFIG}" ]; then ${DOXY} -g ; sed	\
		-e 's/\(OUTPUT_DIRECTORY.*=\)$$/\1 ${DOCUMENTATION}/'	\
		-e 's|\(INPUT[ 	]*=\)$$|\1 ${DOC_HDRS}|'		\
		-e 's/\(JAVADOC_AUTOBRIEF.*=\).*NO$$/\1 YES/'		\
		-e 's/\(UML_LOOK.*=\).*NO$$/\1 YES/'			\
		-e 's/\(HAVE_DOT.*=\).*NO$$/\1 YES/'			\
		-e 's/\(BUILTIN_STL.*=\).*NO$$/\1 YES/'			\
		< Doxyfile > ${DOXYGEN_CONFIG}.sed && ${RM} Doxyfile ;	\
		mv ${DOXYGEN_CONFIG}.sed ${DOXYGEN_CONFIG} ;		\
	fi
	$E${DOXY} ${$DOXYGEN_CONFIG} > ${DOUT} || cat ${DOUT}
.else
	${SAY} "building documentation (headerdoc)"
	$E${RM} -f ${HOUT}
.  for hdr in ${DOC_HDRS}
	$Eif ${HDOC} ${HDOC_FLAGS} -o ${DOCUMENTATION} ${hdr} > ${HOUT}.tmp ;\
	then								\
		cat ${HOUT}.tmp >> ${HOUT} ; ${RM} ${HOUT}.tmp ;	\
	else								\
		tee -a < ${HOUT}.tmp ${HOUT} ; ${RM} ${HOUT}.tmp ;	\
	fi
.  endfor
	$E${GDOC} ${DOCUMENTATION} > ${GOUT} || cat ${GOUT}
.endif
.for man in ${MAN}
	$Enroff -mandoc ${man}.[1-9] > ${DOCUMENTATION}/${man}.0 2>/dev/null ||\
	  nroff -man    ${man}.[1-9] > ${DOCUMENTATION}/${man}.0
.endfor
	$E${TOUCH} ${DD}

.PHONY: xcodebuild
xcodebuild:
	$Excodebuild

.PHONY: pre-targets
pre-targets: fsm-pre-targets

.PHONY: fsm-pre-targets
fsm-pre-targets: ${FSM_PRE_TARGETS}

.PHONY: clean do-clean pre-clean post-clean distclean
pre-clean:
do-clean: pre-clean
	${RM} ${CLEAN_FILES}
	${RM} -r ${DOCUMENTATION}
	${RM} -r ${BUILDDIR}
	${RM} -r build.*
	${RM} -r build

post-clean: do-clean

clean: post-clean

distclean: clean

.PHONY: test
.if !target(test)
test:
	${SAY} "please define a test target!"
.endif

.PHONY: show-var
show-var:
.for var in ${VARNAME}
	@echo '${var}=${${var}}'
.endfor
