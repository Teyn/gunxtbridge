# this needs to come first

.ifdef USE_OLD_WHITEBOARD
NEED_SOAP?=YES
WFLAGS?=
.else
DONT_INCLUDE_COMMON_DIR?=no_I_dont_want_common_upfront
.endif # old WB
