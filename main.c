#include <stdio.h>
#include "device/device.h"

/*
* A basic communication app for USB connected development boards.
* Can be used to debug reading/writing on dev/ttyACM* ports
*/

int main()
{
    uint8_t size;
    get_ports("ACM", get_udev_devices("tty"), &size);
        
    return 0;
}
