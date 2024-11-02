CC = g++
OPT = -O3
#OPT = -g
WARN = -Wall
CFLAGS = $(OPT) $(WARN) $(INC) $(LIB)

# List all your .cc files here (source files, excluding header files)
SIM_SRC = proj_tomasulo.cpp

# List corresponding compiled object files here (.o files)
SIM_OBJ = proj_tomasulo.o
 
#################################

# default rule

all: ooosim
	@echo "Done with make ..."


# rule for making ooosim

ooosim: $(SIM_OBJ)
	$(CC) -o ooosim $(CFLAGS) $(SIM_OBJ) -lm
	@echo "-----------DONE WITH OOOSIM-----------"


# generic rule for converting any .cc file to any .o file
 
.cc.o:
	$(CC) $(CFLAGS)  -c $*.cc


# type "make clean" to remove all .o files plus the ooosim binary

clean:
	rm -f *.o ooosim


# type "make clobber" to remove all .o files (leaves ooosim binary)

clobber:
	rm -f *.o


