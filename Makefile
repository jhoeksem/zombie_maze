CC = g++
CFLAGS = -Wall
TARGET = main
OBJS = main.o parser.o object.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp parser.h object.h
	$(CC) $(CFLAGS) -c main.cpp

parser.o: parser.cpp parser.h
	$(CC) $(CFLAGS) -c parser.cpp

object.o: object.cpp object.h
	$(CC) $(CFLAGS) -c object.cpp

clean: 
	rm -f $(TARGET) $(OBJS)
