CXX = g++
CXXFLAGS = -std=c++11

all: prog
	./prog

rebuild: clean all

prog: prog.cpp libtinyxml2.a
	$(CXX) $(CXXFLAGS) prog.cpp libtinyxml2.a -o prog

libtinyxml2.a: tinyxml2.o
	$(AR) $(ARFLAGS)s $@ $^

tinyxml2.o: tinyxml2.cpp
	$(CXX) $(CXXFLAGS) -c tinyxml2.cpp

clean:
	rm -rf *.o libtinyxml2.a prog
