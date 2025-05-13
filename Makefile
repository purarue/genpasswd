CXX=g++
CXXFLAGS=-std=c++17 -Wall -O2
EXECUTABLE_NAME=genpasswd
SOURCE=genpasswd.cpp
OBJECT=genpasswd.o
LOCAL_BIN="${HOME}/.local/bin"
LOCAL_MAN="${HOME}/.local/share/man/man1"

all: genpasswd

install: genpasswd
	mkdir -p $(LOCAL_BIN) $(LOCAL_MAN)
	cp ./genpasswd $(LOCAL_BIN)
	cp ./genpasswd.1 $(LOCAL_MAN)

genpasswd: $(OBJECT)
	$(CXX) $(OBJECT) -o $(EXECUTABLE_NAME)

genpasswd.o: $(SOURCE)
	$(CXX) $(CXXFLAGS) -c $(SOURCE)

dist: all  # creates the binary and removes the object file
	rm -f $(OBJECT)

clean:
	rm -f $(EXECUTABLE_NAME) $(OBJECT)
