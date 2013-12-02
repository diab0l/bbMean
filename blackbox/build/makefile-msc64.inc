# --------------------------------------------------------------------
# for VS2010 native 64bit compiler

include $(TOP)/build/makefile-msc.inc

BB64 = 1

ifndef ALWAYS_32
ifndef PASS_2
	LFLAGS += -MACHINE:AMD64
	DEFINES += -D_WIN64 -DWIN64
endif
endif

# --------------------------------------------------------------------
