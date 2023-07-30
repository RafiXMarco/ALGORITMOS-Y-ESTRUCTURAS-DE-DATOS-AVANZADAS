
CXX = g++
CXXFLAGS = -std=c++14 -w
LDFLAGS =

all: HashTable

HashTable: main.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean
	
	$(CXX) $(CXXFLAGS) -c $<

clean :
	rm -f *.o  HashTable ../doc
	rm -rf *~ basura b i
	rm -rf a.out
	find . -name '*~' -exec rm {} \;
	find . -name basura -exec rm {} \;