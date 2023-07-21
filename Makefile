CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -ludev

OBJS = main.o ./device/device.o ./device/board_io.h ./config/config.o

all: usbb 

usbb: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
