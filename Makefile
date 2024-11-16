CC = g++

srcDir := src/
includeDir := include/

srcfiles := main.cpp processor.cpp instruction.cpp rob.cpp trace.cpp utils.cpp 
src_files := $(addprefix $(srcDir), $(srcfiles))
executable_file := ooosim

all: $(executable_file)

$(executable_file) : $(src_files)
	$(CC) -g $^ -I $(includeDir) -o $@

clean:
	rm -f $(executable_file)