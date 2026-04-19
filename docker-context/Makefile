CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -I.
LDFLAGS = -lprometheus-cpp-pull -lcurl
TARGET = programm
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
all: httplib.h $(TARGET)
httplib.h:
    # Скачиваем единственный заголовочный файл для микро-HTTP сервера
    wget -q https://raw.githubusercontent.com/yhirose/cpp-httplib/v0.15.3/httplib.h
 $(TARGET): $(OBJECTS)
    $(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
%.o: %.cpp
    $(CC) $(CFLAGS) -c $< -o $@
clean:
    rm -f $(OBJECTS) $(TARGET) httplib.h
install: $(TARGET)
    install -d $(DESTDIR)/usr/bin
    install -m 755 $(TARGET) $(DESTDIR)/usr/bin/
.PHONY: all clean install
