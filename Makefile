CXX = g++
CXXFLAGS = -std=c++17

main: main.cpp testRunner.o tests.o genericMaths.o neonMaths.o 
	$(CXX) $(CXXFLAGS) -o main main.cpp testRunner.o tests.o genericMaths.o neonMaths.o

tests.o: tests.cpp tests.hpp 
	$(CXX) $(CXXFLAGS) -c tests.cpp 

genericMaths.o: genericMaths.cpp genericMaths.hpp maths.hpp
	$(CXX) $(CXXFLAGS) -c genericMaths.cpp

neonMaths.o: neonMaths.cpp simdMaths.hpp maths.hpp
	$(CXX) $(CXXFLAGS) -c neonMaths.cpp

testRunner.o: testRunner.cpp testRunner.hpp
	$(CXX) $(CXXFLAGS) -c testRunner.cpp

clean:
	rm -f main
	rm -f *.o