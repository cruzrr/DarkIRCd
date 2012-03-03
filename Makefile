CC=gcc
LINKER=ld
OBJECTS=build/objects/*.o
SORUCES=src/server.c src/main.c
EXECUTABLE=build/darkircd
IDIR=src/includes
OBJDIR=build/objects
SAY=echo

all:
	@mkdir -p build
	@mkdir -p build/objects
	@$(SAY) "Buidling DarkIRCd"
	@$(CC) -I$(IDIR) src/main.c src/server.c -o $(EXECUTABLE)
	@$(SAY) "Done."

clean:
	@rm -rf build/
	@$(SAY) "Done."
