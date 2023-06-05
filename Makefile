CXX = g++
CXXFLAGS = -std=c++20 -mfpu=neon -O3

main: main.cpp tests.o genericMaths.o neonMaths.o 
	$(CXX) $(CXXFLAGS) -o main main.cpp tests.o genericMaths.o neonMaths.o

tests.o: tests.cpp tests.hpp 
	$(CXX) $(CXXFLAGS) -c tests.cpp 

genericMaths.o: genericMaths.cpp genericMaths.hpp maths.hpp
	$(CXX) $(CXXFLAGS) -c genericMaths.cpp 

neonMaths.o: neonMaths.cpp simdMaths.hpp maths.hpp
	$(CXX) $(CXXFLAGS) -c neonMaths.cpp

clean:
	rm -f main
	rm -f *.o
