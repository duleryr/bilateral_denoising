PROG = main
CXX=g++
CXXFLAGS=-Wall -Wextra -std=c++11 -O3

SRCDIR=./src
CSOURCE=$(SRCDIR)/Face.cpp $(SRCDIR)/Vertex.cpp
CSMAIN=$(SRCDIR)/main.cpp

$(PROG): 
	$(CXX) $(CSOURCE) $(CXXFLAGS) $(CSMAIN) -o $@ 
	
debug:
	$(CXX) $(CSOURCE) $(CXXFLAGS) -g -pg $(CSMAIN) -o $@ 

doc:
	pdflatex -output-directory=Documentation/ Documentation/rapport.tex

all: $(PROG) debug doc 

clean :
	rm -f ./main
	rm -f Documentation/rapport.aux
	rm -f Documentation/rapport.log
	rm -f Documentation/rapport.dvi
	rm -f Documentation/rapport.pdf
	rm -f Output_Files/*.txt

.PHONY: all debug test clean 
