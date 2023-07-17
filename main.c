#include <stdio.h>
#include "device/device.h"

/*
 * A basic communication app for USB connected development boards.
 * Can be used to debug reading/writing on dev/ttyACM* ports
*/

int main(int argc, char **argv)
{
    if(argc == 1)
    {    
        printf("Error: invalid number of arguments. See usbb -help\n");
        return 0;
    }

    //checks which command to run
    if(strcmp(argv[1], "-help") == 0)
    {
        printf("How to use: usbb [option] ...\n");
        printf("List of options:\n");
        printf("-find -> gets a list of all valid ports or 'None' if the aren't any.\n");
    }
    else if(strcmp(argv[1], "-find") == 0)
    {
        uint8_t size;
        char **ports = get_ports("ACM", get_udev_devices("tty"), &size);

        if(size == 0)
        {
            printf("None\n");
            return 0;
        }

        for(uint8_t i = 0; i < size; i++)
            printf("Found device: %s\n", ports[i]);
    
        for(uint8_t i = 0; i < size; i++)
            free(ports[i]);

        free(ports);
    }

    return 0;
}
