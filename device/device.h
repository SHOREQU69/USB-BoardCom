#ifndef DEVICE_H
#define DEVICE_H

#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

/*
 *  Gets a list of all devices connected under /dev/ttyACM*.
 *  TODO: support for serial port /dev/ttyS0 or other USB /dev/ttyUSB0
*/

#define MAX_UDEV_LIST_SIZE 10

//initialise the udev library that will be used to get the list of all required devices
extern struct udev_device** get_udev_devices(const char *name);
//filter only the ACM ports
extern char** get_ports(const char* port_type, struct udev_device** entry, char** ports, uint8_t* size); 

#endif
