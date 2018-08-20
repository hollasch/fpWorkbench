
# This makefile works with Microsoft Visual C.  If you aren't using that
# environment, you just need a C compiler that generates an executable from
# a single C file.

.c.exe:
	cl /W4 /nologo $?

.cpp.exe:
    cl /W4 /nologo $?

all: hexfloat specials fp

hexfloat: hexfloat.exe

specials: specials.exe

fp: fp.exe

specials.exe: specials.c

hexfloat.exe: hexfloat.c

fp.exe: fp.cpp

clean:
	del 2>nul hexfloat.obj specials.obj fp.obj

clobber: clean
	del 2>nul hexfloat.exe specials.exe fp.exe

fresh: clobber all
