OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.obj,$(wildcard $(SRCDIR)/*.c)) 
DEPS = $(patsubst $(SRCDIR)/%.c,$(INCDIR)/%.h,$(wildcard $(INCDIR)/*.h)) 
OBJDIR = .
INCDIR = include
SRCDIR = src
OUTPUTDIR = .
RESDIR = resources
LIBDIR = lib
CC = cl.exe
LINK = link.exe
CFLAGS = /D "_CRT_SECURE_NO_WARNINGS" /MT /O2 /TC /c -I$(INCDIR) /W3 /GS- 
LFLAGS = /INCREMENTAL /SUBSYSTEM:CONSOLE /MACHINE:X86 /VERBOSE:LIB
LIBS = SDL.lib SDLmain.lib glu32.lib opengl32.lib ./lib/soil.lib ./lib/physfs.lib
DEL = del /F /Q
COPY = copy /Y

cano: $(OBJ)
	$(LINK) $(LFLAGS) /OUT:"$(OUTPUTDIR)\$@.exe" $(OBJ) $(LIBS)
	 
$(OBJDIR)/%.obj : $(SRCDIR)/%.c $(DEPS) 
	$(CC) $(CFLAGS) $(CPPFLAGS) $<

install: cano
	$(COPY) $(LIBDIR)\*.dll $(OUTPUTDIR)\ 
	$(DEL) $(OUTPUTDIR)\*.ilk
	$(DEL) $(OUTPUTDIR)\*.obj
	
clean:
	$(DEL) $(OBJDIR)\*.obj
	$(DEL) $(OUTPUTDIR)\*.exe
	$(DEL) $(OUTPUTDIR)\*.manifest
	$(DEL) $(OUTPUTDIR)\*.ilk
