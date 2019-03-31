LINKER        = g++
LINKERFLAGS   =  -s
COMPILER      = g++
COMPILERFLAGS =  -std=gnu++14 -Wall
BIN           = musya128
LIBS          = -lboost_filesystem -lboost_system -lquadmath
vpath %.cpp src
vpath %.o build
OBJ           = eparsing.o file_contents.o fsize.o musya128.o parsing_result_t.o
LINKOBJ       = build/eparsing.o build/file_contents.o build/fsize.o build/musya128.o build/parsing_result_t.o 

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom 
	rm -f ./build/*.o
	rm -f ./build/$(BIN)

.cpp.o:
	$(COMPILER) -c $< -o $@ $(COMPILERFLAGS) 
	mv $@ ./build

$(BIN):$(OBJ)
	$(LINKER) -o $(BIN) $(LINKOBJ) $(LIBS) $(LINKERFLAGS)
	mv $(BIN) ./build
