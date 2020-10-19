CXX=g++
CXXFLAGS=-Wall -std=c++11 -g

all:
	$(CXX) $(CXXFLAGS) -o stoogesort stoogesort.cpp

clean:
	@rm -f stoogesort stooge.out
	@rm -f *.o
format:
	clang-format --verbose --sort-includes -i *.cpp *.hpp
