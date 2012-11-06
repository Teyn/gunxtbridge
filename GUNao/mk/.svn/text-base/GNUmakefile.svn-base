#
#	$Id: e08d8f3b1db59a08cae2131d70860c26f453ffe8 $
#
# make file wrapper for gnumake
#
bmake=$(shell which nbmake bmake bsdmake pmake freebsd-make 2>/dev/null | head -n 1)
E?=@
PARALLEL?=-j4

all:
	$E${bmake} ${PARALLEL} ${MAKEFLAGS}

clean:
	$E${bmake} ${PARALLEL} ${MAKEFLAGS} $@

host:
	$E${bmake} ${PARALLEL} ${MAKEFLAGS} $@

host-local:
	$E${bmake} ${PARALLEL} ${MAKEFLAGS} $@

robot:
	$E${bmake} ${PARALLEL} ${MAKEFLAGS} $@

robot-local:
	$E${bmake} ${PARALLEL} ${MAKEFLAGS} $@

local:
	$E${bmake} ${PARALLEL} ${MAKEFLAGS} $@

install:
	$E${bmake} ${PARALLEL} ${MAKEFLAGS} $@

install-local:
	$E${bmake} ${PARALLEL} ${MAKEFLAGS} $@

echo:
	$Eecho "${bmake} ${PARALLEL} ${MAKEFLAGS} $@"

%:
	$E${bmake} ${MAKEFLAGS} $@
