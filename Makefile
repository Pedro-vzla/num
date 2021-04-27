CC = cc

# Compiler flags: all warnings + debugger meta-data
CFLAGS = -Wall -std=gnu89
CFLAGS_DEBUG = -Wall -g -std=gnu89

# External libraries
LIBDIR=$(wildcard lib/*.c)
HEADERS=$(wildcard lib/*.h)

# Pre-defined macros for conditional compilation
DEFS = -D

BIN = num
BIN_DEBUG = num_dbg

OBJECTS= *.o
SOURCES= *.c
#VPATH=lib

# The final executable program file, i.e. name of our program


$(BIN): libraries
	$(CC) $(CFLAGS) lib/obj/$(OBJECTS) -o $(BIN)

debug: libraries_dbg
	@echo compiling binary whit debuggin symbols...
	$(CC) $(CFLAGS_DEBUG) lib/obj/$(OBJECTS) -o $(BIN_DEBUG)

libraries: $(LIBDIR) $(HEADERS)
	@echo compiling libraries...
	@if [ ! -d lib/obj ]; then \
		mkdir "lib/obj";\
	fi;
	@for file in $(LIBDIR); do \
		gcc $(CFLAGS) -c lib/$(SOURCES) -I lib/obj; \
		mv $(OBJECTS) lib/obj ; \
	done

libraries_dbg:
	@echo compiling libraries...
	@if [ ! -d lib/obj ]; then \
		mkdir "lib/obj";\
	fi;
	@for file in $(LIBDIR); do \
		gcc $(CFLAGS_DEBUG) -c lib/$(SOURCES) -I lib/obj; \
		mv $(OBJECTS) lib/obj ; \
	done
clean:
	rm -f $(BIN) $(BIN_DEBUG)
	rm -rfd lib/obj
