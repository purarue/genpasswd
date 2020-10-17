CXX=g++
CXXFLAGS=-std=c++17 -Wall -O2
EXECUTABLE_NAME=genpasswd
SOURCE=genpasswd.cpp
OBJECT=genpasswd.o

all: genpasswd

install: genpasswd
	sudo cp ./genpasswd /usr/local/bin/

genpasswd: $(OBJECT)
	$(CXX) $(OBJECT) -o $(EXECUTABLE_NAME)

genpasswd.o: $(SOURCE)
	$(CXX) $(CXXFLAGS) -c $(SOURCE)

dist: all  # creates the binary and removes the object file
	rm $(OBJECT)

clean:
	rm $(EXECUTABLE_NAME) $(OBJECT)
