# This makefile works with Microsoft Visual C.  If you aren't using that
# environment, you just need a C compiler that generates an executable from
# a single C file.
# ==================================================================================================

build=build
cOptions=-nologo -W3 -I"%VCINSTALLDIR%/include" -Fo$(build)\obj\ -EHsc
cppOptions=-nologo -W4
objDir=$(build)\obj

all: createOutputDir epsilon-bad fp hexfloat specials

#-------------------------------------------------------------------------------
createOutputDir:
    -mkdir 2>nul $(build)\obj

clean:
	-rmdir 2>nul /s /q $(objDir)

clobber:
    -rmdir 2>nul /s /q $(build)

fresh: clobber all

#-------------------------------------------------------------------------------
epsilon-bad: $(build)\epsilon-bad.exe
fp: $(build)\fp.exe
hexfloat: $(build)\hexfloat.exe
specials: $(build)\specials.exe


$(build)\epsilon-bad.exe: epsilon-bad.cpp
    cl $(cppOptions) $? -Fe$@ -Fo$(objDir)\epsilon-bad.obj

$(build)\specials.exe: specials.cpp
    cl $(cppOptions) $? -Fe$@ -Fo$(objDir)\specials.obj

$(build)\hexfloat.exe: hexfloat.cpp
    cl $(cppOptions) $? -Fe$@ -Fo$(objDir)\hexfloat.obj

$(build)\fp.exe: fp.cpp fp.h
    cl $(cppOptions) fp.cpp -Fe$@ -Fo$(objDir)\fp.obj
