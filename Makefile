CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -ludev

OBJS = main.o ./device/device.o

all: app 

app: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
