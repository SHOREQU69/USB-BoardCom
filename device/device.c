#include "device.h"
#include <libudev.h>
#include <stdint.h>

static struct udev* get_udev()
{
    //basic udev sequence
    struct udev* udev = udev_new();

    if(!udev)
    {
        printf("Error: failed to create udev\n");
        exit(1);
    }
    
    return udev;
}

static struct udev_enumerate* get_udev_enumerate(struct udev *udev, const char *name)
{
    //basic udev_enumerate sequence
    struct udev_enumerate* enumerate = udev_enumerate_new(udev);

    udev_enumerate_add_match_subsystem(enumerate, name);
	udev_enumerate_scan_devices(enumerate);

    return enumerate;
}

struct udev_device** get_udev_devices(const char *name)
{
    //basic init
    struct udev* udev = get_udev();
    struct udev_enumerate* enumerate = get_udev_enumerate(udev, name);
    
    struct udev_list_entry *devices, *dev_list_entry;

    devices = udev_enumerate_get_list_entry(enumerate);

    //final list of devices
    struct udev_device** list = malloc(MAX_UDEV_LIST_SIZE * sizeof(struct udev_device*));
    uint8_t pos = 0;

    udev_list_entry_foreach(dev_list_entry, devices) 
    {
	const char *path;
		
	//Get the filename of the /sys entry for the device and create a udev_device object (dev) representing it 
	path = udev_list_entry_get_name(dev_list_entry);
	struct udev_device* dev = udev_device_new_from_syspath(udev, path);

	if(pos < MAX_UDEV_LIST_SIZE)
	{    
	    list[pos++] = dev;
	}
	else
	{
	    udev_enumerate_unref(enumerate);
	    udev_unref(udev);
	    
	    return list;
	}
    }

    //Free the enumerator object 
    udev_enumerate_unref(enumerate);
    udev_unref(udev);

    return list;
}

char** get_ports(const char* port_type, struct udev_device **entry, char** ports, uint8_t* size)
{
    uint8_t pos = 0;

    //gets all valid ports
    for(uint8_t i = 0; i < MAX_UDEV_LIST_SIZE; i++)
	if(strstr(udev_device_get_devnode(entry[i]), port_type))
	    strcpy(ports[pos++], udev_device_get_devnode(entry[i]));

    *size = pos; 

    //frees entry
    for(uint8_t i = 0; i < MAX_UDEV_LIST_SIZE; i++)
	free(entry[i]);

    free(entry);

    return ports;
}
