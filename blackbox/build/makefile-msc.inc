# --------------------------------------------------------------------
# for MS compilers (default MSVC 6,0)

USING_MSC = 1

SUBSYSTEM   ?= WINDOWS
_CFLAGS     = -Zi -MD
_CPPFLAGS   = -EHsc

CFLAGS      += -O1 -W3 $(_CFLAGS) -nologo
LFLAGS      += -SUBSYSTEM:$(SUBSYSTEM) -NOLOGO -OPT:REF,ICF

DEFINES		+= -D_CRT_SECURE_NO_WARNINGS

ifdef DEBUG
	LFLAGS += -Debug
endif

CPPFLAGS    += $(_CPPFLAGS)

CC          = cl
LINK        = link
RC          = rc

SYSLIBS += \
  kernel32.lib    \
  user32.lib      \
  gdi32.lib       \
  shell32.lib     \
  comctl32.lib    \
  comdlg32.lib    \
  shlwapi.lib     \
  advapi32.lib    \
  version.lib     \
  ole32.lib       \
  winmm.lib

# full source path for the debugger
SRCDIR = "$(CURDIR)"/

COMPILE.c   = $(CC) $(CFLAGS) -Fo$@ -c $(SRCDIR)$< $(DEFINES)
COMPILE.cpp = $(CC) $(CFLAGS) $(CPPFLAGS) -Fo$@ -c $(SRCDIR)$< $(DEFINES)
COMPILE.rc  = $(RC) $(DEFINES) -fo$@ $(SRCDIR)$<

define LINK.exe
 $(LINK) $(LFLAGS) -OUT:$@ $^ $(SYSLIBS)
 rm -f $(STUFF)
 $(MANIFEST_CMD.exe)
endef

define LINK.dll
 $(LINK) $(LFLAGS) -DLL -OUT:$@ $^ $(SYSLIBS)
 rm -f $(STUFF)
 $(MANIFEST_CMD.dll)
endef

define LINK.lib
 rm -f $@
 $(LINK) -lib -nologo -out:$@ $^
endef

STUFF = $*.exp
ifndef IMPLIB
STUFF += $*.lib
endif

LIBNAME = $1.lib

# --------------------------------------------------------------------
