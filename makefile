# This makefile works with Microsoft Visual C.  If you aren't using that
# environment, you just need a C compiler that generates an executable from
# a single C file.
# ==================================================================================================

cOptions=-nologo -W3 -I"%VCINSTALLDIR%/include" -Fo.\out\obj\ -EHsc
cppOptions=-nologo -W4
outDir=out
objDir=$(outDir)\obj

all: createOutputDir epsilon-bad fp hexfloat specials

#-------------------------------------------------------------------------------
createOutputDir:
    -mkdir 2>nul $(outDir)\obj

clean:
	-rmdir 2>nul /s /q $(objDir)

clobber:
    -rmdir 2>nul /s /q $(outDir)

fresh: clobber all

#-------------------------------------------------------------------------------
epsilon-bad: $(outDir)\epsilon-bad.exe
fp: $(outDir)\fp.exe
hexfloat: $(outDir)\hexfloat.exe
specials: $(outDir)\specials.exe


$(outDir)\epsilon-bad.exe: epsilon-bad.cpp
    cl $(cppOptions) $? -Fe$@ -Fo$(objDir)\epsilon-bad.obj

$(outDir)\specials.exe: specials.cpp
    cl $(cppOptions) $? -Fe$@ -Fo$(objDir)\specials.obj

$(outDir)\hexfloat.exe: hexfloat.cpp
    cl $(cppOptions) $? -Fe$@ -Fo$(objDir)\hexfloat.obj

$(outDir)\fp.exe: fp.cpp fp.h
    cl $(cppOptions) fp.cpp -Fe$@ -Fo$(objDir)\fp.obj
