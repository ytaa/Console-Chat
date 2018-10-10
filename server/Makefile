CC = gcc
CC_FLAGS = -I ./headers -I ../common/headers
#CFLAGS = -Wall -g

SOURCES = $(wildcard ./src/*.c ../common/src/*.c)
OBJECTS = $(SOURCES:.c=.o)
DEPS = $(wildcard ./headers/*.h ../common/headers/*.h)
EXEC = server
LIBS = -lpthread

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $(EXEC)

%.o: %.c $(DEPS)
	$(CC) -c $(CC_FLAGS) $< -o $@
