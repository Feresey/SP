.PHONY :  all, clean
TARGET := ../mlispgen
SRC    := ../base-compiler.cpp ../basegramma.cpp ../baselexer.cpp ../code-gen.cpp ../kngramma.cpp ../slr.cpp ../mlispgen.cpp
HDR    := $(wildcard ../*.hpp ../*.h)
CXX    := g++ 
CFLAGS := -pipe -O3 -pedantic -Wall -Wextra -Wpedantic -W -Wno-sign-compare -Wno-long-long -g3\
          -Wctor-dtor-privacy -Wnon-virtual-dtor -Wold-style-cast -Winit-self\
          -Wconversion -Wsign-conversion -Wunreachable-code -Wno-comment#-fsanitize=address #-fprofile-arcs -ftest-coverage  

all: $(TARGET)

clean:
	rm -f $(TARGET) *.o *.gc*

mlispgen.o: ../mlispgen.cpp $(HDR)
	$(CXX) $(CFLAGS) -c $<

%.o: ../%.cpp $(HDR)
	$(CXX) $(CFLAGS) -c -o $@ $<

$(TARGET): $(SRC:../%.cpp=%.o)
	$(CXX) $(CFLAGS) -o $@ $^ -lm
