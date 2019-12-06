# the compiler
CC = g++

# compiler flags:
# -Wall for compiler warnings
CFLAGS = -Wall -std=c++11

# build target exectuable
TARGET = sudosat


all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET)

