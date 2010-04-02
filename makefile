
# This makefile works with Microsoft Visual C.  If you aren't using that
# environment, you just need a C compiler that generates an executable from
# a single C file.

.c.exe:
	cl /W4 /nologo $?

all: hexfloat specials

hexfloat: hexfloat.exe

specials: specials.exe

specials.exe: specials.c

hexfloat.exe: hexfloat.c

clean:
	del 2>nul hexfloat.obj specials.obj

clobber: clean
	del 2>nul hexfloat.exe specials.exe
