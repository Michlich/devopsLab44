CC = g++
CFLAGS = -std=c++11 -Wall -Wextra
TARGET = programm
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS) $(TARGET)
    
install: $(TARGET)
	install -d $(DESTDIR)/usr/bin
	install -m 755 $(TARGET) $(DESTDIR)/usr/bin/
.PHONY: clean install
