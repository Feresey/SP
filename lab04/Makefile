.PHONY: all clean
CXX = zapcc++ 
CFLAGS = -Wall -Wextra -Wpedantic -Wno-sign-compare -Wno-long-long -g3\
         -Wctor-dtor-privacy -Wnon-virtual-dtor -Wold-style-cast -Winit-self\
         -Wconversion -Wsign-conversion -Wunreachable-code -Wno-comment

all: cppid testadec

%: %.cpp
	pvs-studio-analyzer trace -- $(CXX) $(CFLAGS) $^ -o $@
	pvs-studio-analyzer analyze -o $@.log -C zapcc++
	plog-converter -t tasklist -o $@.tasks $@.log


clean:
	rm -f cppid testadec *.o *.gc*