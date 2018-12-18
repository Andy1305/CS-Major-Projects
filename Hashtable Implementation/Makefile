CFLAGS= /nologo /c


build: tema1.exe

tema1.exe: tema1.obj ht.obj list.obj
	$(CPP) $** /Fe$@ hash.lib

tema1.obj: tema1.c
	$(CPP) $(CFLAGS) $** /Fo$@

ht.obj: ht.c
	$(CPP) $(CFLAGS) $** /Fo$@

list.obj: list.c
	$(CPP) $(CFLAGS) $** /Fo$@

clean:
	del *.obj tema1.exe
