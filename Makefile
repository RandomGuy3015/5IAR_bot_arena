CXX = g++
CXXFLAGS = -Wextra -Wall -pedantic -std=c++20 -O2 -g  -fsanitize=undefined  -fsanitize=address
HEADERS = $(wildcard *.hpp)
OBJECTS = $(addsuffix .o, $(basename  $(filter-out $(EXCLUDED) %Test.cpp %Main.cpp, $(wildcard *.cpp))))

all: compile run #draw

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

%Main: %Main.cpp $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

compile: 5IARMain

run: 
	./5IARMain

draw:
	display image.ppm

clean:
	rm -f *Main *Test *.o *.ppm

format:
	clang-format -i *.cpp *.hpp

.PRECIOUS: %.o
