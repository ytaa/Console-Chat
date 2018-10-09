CC = gcc
CC_FLAGS = -I./headers
#CFLAGS = -Wall -g

SOURCES = $(wildcard ./src/*.c)
OBJECTS = $(SOURCES:.c=.o)
DEPS = $(wildcard ./headers/*.h)
EXEC = client
LIBS = -lpthread

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $(EXEC)

%.o: %.c $(DEPS)
	$(CC) -c $(CC_FLAGS) $< -o $@
