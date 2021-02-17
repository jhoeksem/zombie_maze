# compiler
CC = g++

# compiler flags
CFLAGS = -Wall

# build target
TARGET = parser

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean: 
	rm -f $(TARGET)
