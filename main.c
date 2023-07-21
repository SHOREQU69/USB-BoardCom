#include <stdio.h>
#include "device/device.h"
#include "config/config.h"

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

    char* port = NULL;

    //checks which command to run
    if(strcmp(argv[1], "-help") == 0)
    {
        printf("How to use: usbb [option] ...\n");
        printf("List of options:\n");
        printf("-find -> gets a list of all valid ports or 'None' if the aren't any.\n");
        printf("-lock [PORT] -> locks a port that will be used for reading or writing. Overwrites if a port is already selected.\n");
        printf("-lock -u -> unlocks the port.(If you do not unlock the port after use, it will persist in time).\n");
        printf("-lock -g -> gets the locked port, or 'None' is the isn't any.\n");
    }
    
    if(strcmp(argv[1], "-find") == 0)
    {
        //generic maximum port length
        const size_t MAX_PORT_SIZE = 20;

        uint8_t size;

        char** ports = malloc(MAX_UDEV_LIST_SIZE * sizeof(char*));

        for(uint8_t i = 0; i < MAX_UDEV_LIST_SIZE; i++)
	    ports[i] = malloc(MAX_PORT_SIZE  * sizeof(char)); 

        get_ports("ACM", get_udev_devices("tty"), ports, &size);

        if(size == 0)
        {
            printf("None\n");
            return 0;
        }

        for(uint8_t i = 0; i < size; i++)
            printf("Found device: %s\n", ports[i]);
    
        for(uint8_t i = 0; i < MAX_UDEV_LIST_SIZE; i++)
            free(ports[i]);

        free(ports);
    }
    else if(argc == 3 && strcmp(argv[1], "-lock") == 0 && strstr(argv[2], "dev"))
    {
        //free already existing memory
        if(port != NULL)
            free(port);

        port = malloc((strlen(argv[2]) + 1) * sizeof(char));
        memcpy(port, argv[2], strlen(argv[2]) + 1);

        write_config(PORT_CONFIG_PATH, port);

        printf("%s\n", port);
    }
    else if(argc == 3 && strcmp(argv[1], "-lock") == 0 && strcmp(argv[2], "-u") == 0)
    {
        char* saved_port = read_config(PORT_CONFIG_PATH);

        if(saved_port == NULL)
        {
            printf("None already\n");
            return 0;
        }
        
        write_config(PORT_CONFIG_PATH, "");

        free(port);
        port = NULL;

        free(saved_port);
    }
    else if(argc == 3 && strcmp(argv[1], "-lock") == 0 && strcmp(argv[2], "-g") == 0)
    {
        char* saved_port = read_config(PORT_CONFIG_PATH);

        if(saved_port == NULL)
        {
            printf("None already\n");
            return 0;
        }

        printf("%s\n", saved_port);
    }

    if(port != NULL)
        free(port);

    return 0;
}
