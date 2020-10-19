CXX=g++
CXXFLAGS=-Wall -std=c++11 -g

all:
	$(CXX) $(CXXFLAGS) -o shopping shopping.cpp

clean:
	@rm -f shopping shopping.out
	@rm -f *.o
format:
	clang-format --verbose --sort-includes -i *.cpp *.hpp
