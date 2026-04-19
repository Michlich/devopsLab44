CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -I. -pthread
LDFLAGS = -pthread
TARGET = programm
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
all: httplib.h $(TARGET)
httplib.h:
	wget -q https://raw.githubusercontent.com/yhirose/cpp-httplib/v0.15.3/httplib.h
 $(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS) $(TARGET) httplib.h
.PHONY: all clean
