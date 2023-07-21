#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*
 * Functions that read or write to config files used by the app
*/

//path to port config file. The port inside the file is the one set by -lock and will be used for I/O
#define PORT_CONFIG_PATH "/home/alex/.config/usbb/port.config"

extern char* read_config(const char* path);
extern void write_config(const char* path, char* data);

#endif
