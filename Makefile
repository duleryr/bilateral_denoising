PROG = main
CXX=g++
CXXFLAGS=-Wall -Wextra -std=c++11 -O3

SRCDIR=./src
CSOURCE=$(SRCDIR)/Data_structure.cpp $(SRCDIR)/file_stream.cpp $(SRCDIR)/Vertex.cpp
CSMAIN=$(SRCDIR)/main.cpp

$(PROG): 
	$(CXX) $(CSOURCE) $(CXXFLAGS) $(CSMAIN) -o $@ 
	
add_noise:
	$(CXX) $(CSOURCE) $(CXXFLAGS) $(SRCDIR)/add_noise.cpp -o $@ 

debug:
	$(CXX) $(CSOURCE) $(CXXFLAGS) -g -pg $(CSMAIN) -o $@ 

all: $(PROG) debug add_noise

clean :
	rm -f ./main
	rm -f ./debug
	rm -f ./add_noise

.PHONY: all debug clean 
