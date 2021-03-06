CC = g++
CFLAGS = -g -Wall -std=c++11
TARGET = main
OBJS = main.o parser.o object.o npc.o map.o character.o

all: $(TARGET) $(MAP)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

parser.o: parser.cpp parser.h
	$(CC) $(CFLAGS) -c parser.cpp

map.o: map.cpp map.h
	$(CC) $(CFLAGS) -c map.cpp

character.o: character.cpp character.h
	$(CC) $(CFLAGS) -c character.cpp

object.o: object.cpp object.h
	$(CC) $(CFLAGS) -c object.cpp

npc.o: npc.cpp npc.h
	$(CC) $(CFLAGS) -c npc.cpp

main.o: main.cpp parser.h object.h npc.h character.h
	$(CC) $(CFLAGS) -c main.cpp

clean: 
	rm -f $(TARGET) $(OBJS)
