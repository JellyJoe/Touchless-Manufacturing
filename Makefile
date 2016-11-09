CXX = g++
CXXFLAGS = -std=c++11

all: Driver
	./Driver

rebuild: clean all

Driver: Driver.cpp Report.o TinyXML2Lib.a
	$(CXX) $(CXXFLAGS) Driver.cpp Report.o TinyXML2Lib.a -o Driver

Report.o: Report.cpp
	$(CXX) $(CXXFLAGS) -c Report.cpp

TinyXML2.o: TinyXML2.cpp
	$(CXX) $(CXXFLAGS) -c TinyXML2.cpp

TinyXML2Lib.a: TinyXML2.o
	$(AR) $(ARFLAGS)s $@ $^

clean:
	rm -rf *.o TinyXML2Lib.a Driver
