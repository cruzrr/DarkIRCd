CC=gcc
OBJECTS=build/objects/*.o
SORUCES=src/server.c src/main.c
EXECUTABLE=build/bin/darkircd
IDIR=lib
OBJDIR=build/objects
SAY=echo

all:
	@mkdir -p build
	@mkdir -p build/objects
	@mkdir -p build/bin/
	@$(SAY) "Buidling DarkIRCd..."
	@$(CC) -c -I$(IDIR) src/main.c -o $(OBJDIR)/main.o
	@$(CC) -c -I$(IDIR) src/server.c -o $(OBJDIR)/server.o

	@$(CC) -o $(EXECUTABLE) $(OBJECTS)
	@$(SAY) "Done. Executable: $(pwd)$(EXECUTABLE)"

clean:
	@rm -rf build/
	@$(SAY) "Done."

uninstall: clean
