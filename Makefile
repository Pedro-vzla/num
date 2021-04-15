# Makefile
CC = cc
# Compiler flags: all warnings + debugger meta-data
CFLAGS = -Wall -g

# External libraries: only math in this example
#LIBS = -l

# Pre-defined macros for conditional compilation
DEFS = -DDEBUG_FLAG -DEXPERIMENTAL=0

# The final executable program file, i.e. name of our program
BIN = num

# Object files from which $BIN depends
OBJS = num.o

# This default rule compiles the executable program
$(BIN): $(OBJS) $(BIN).c
	$(CC) $(CFLAGS) $(DEFS) $(BIN).c -o $(BIN)

# This rule compiles each module into its object file
#%.o: %.c %.h
#	$(CC) -c $(CFLAGS) $(DEFS) $< -o $@

clean:
	rm -f *~ *.o $(BIN)

depend:
	makedepend -Y -- $(CFLAGS) $(DEFS) -- *.c

# DO NOT DELETE

#module1.o: module4.h
#module2.o: module3.h
#program_name.o: module1.h module2.h module3.h module4.h


