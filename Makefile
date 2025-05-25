CC = gcc
CFLAGS = -Wall -Wextra \
	-I./DataStructures/Common \
	-I./DataStructures/Dictionary \
	-I./DataStructures/Lists \
	-I./DataStructures/Trees \
	-I./Networking/Nodes

SRCS := $(wildcard main.c) \
        $(wildcard DataStructures/Common/*.c) \
        $(wildcard DataStructures/Dictionary/*.c) \
        $(wildcard DataStructures/Lists/*.c) \
        $(wildcard DataStructures/Trees/*.c) \
		$(wildcard Networking/Nodes/*.c) 

OBJS := $(SRCS:.c=.o)

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)