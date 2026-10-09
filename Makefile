CC = gcc

CPPFLAGS = $(shell sdl2-config --cflags)
CFLAGS = -Wall -Wextra -Wvla -Werror -std=c99 -pedantic -I..
LDLIBS = $(shell sdl2-config --libs)

SRCS = scr/window.c scr/main.c
OBJS = $(SRCS:.c=.o)

TARGET = troll

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(TARGET)
	$(RM) $(OBJS)

.PHONY: all clean