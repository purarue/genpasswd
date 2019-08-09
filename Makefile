CXX=g++
CXXFLAGS=-std=c++17 -Wall
EXECUTABLE_NAME=genpasswd
HEADER=genpasswd.h
SOURCE=genpasswd.cpp
OBJECT=genpasswd.o

all: genpasswd

genpasswd: $(OBJECT)
	$(CXX) $(OBJECT) -o $(EXECUTABLE_NAME)

genpasswd.o: $(SOURCE) $(HEADER)
	$(CXX) $(CXXFLAGS) -c $(SOURCE)

dist: all  # creates the binary and removes the object file
	rm $(OBJECT)

clean:
	rm $(EXECUTABLE_NAME)
