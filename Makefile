CC = g++
CFLAGS = -g -Wall
TARGET = main
OBJS = main.o parser.o object.o npc.o map.o

all: $(TARGET) $(MAP)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

parser.o: parser.cpp parser.h
	$(CC) $(CFLAGS) -c parser.cpp

map.o: map.cpp map.h
	$(CC) $(CFLAGS) -c map.cpp

object.o: object.cpp object.h
	$(CC) $(CFLAGS) -c object.cpp

npc.o: npc.cpp npc.h
	$(CC) $(CFLAGS) -c npc.cpp

main.o: main.cpp parser.h object.h npc.h
	$(CC) $(CFLAGS) -c main.cpp

clean: 
	rm -f $(TARGET) $(OBJS)
