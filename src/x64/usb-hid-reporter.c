// USB-HID-Reporter - v1
// Author: Mario Baldini - 2015/05
// https://github.com/mariobaldini/usb-hid-reporter
// Usage (with root privileges): usb-hid-reporter vendor_id product_id report_length 


#include <stdio.h>
#include <stdlib.h>
#include "hidapi.h"
// #include <hidapi/hidapi.h>  // Instead of "hidapi.h"; if building against openwrt sdk 

#define PROGRAM_VERSION   1.0
#define SERIAL_NUMBER     NULL  // Uses the first VID/PID match found in the USB BUS. 
// SERIAL_NUMBER scan not implemented -- for differentiating multiple products of same VID/PID


int main(int argc, char* argv[])
{
    int res, i;
    hid_device *handle;
    unsigned char buf[256];
    for (i = 0; i < 256; i++) {
        buf[i] = 0;
    }

    if (argc != 4){
        printf("\n\tUSB-HID-Reporter -- Ver. %.1f\n\n", PROGRAM_VERSION);
        printf("Author: Mario Baldini - 2015/05\n");
        printf("https://github.com/mariobaldini/usb-hid-reporter\n\n");
        printf("Usage:\tsudo %s VENDOR_ID PRODUCT_ID REPORT_SIZE\n", argv[0]);
        printf("  VENDOR_ID/PRODUCT_ID: Hexadecimal - Find with 'dmesg' command. More info: www.linux-usb.org\n");
        printf("  REPORT_SIZE: Decimal - Length of USB Report in bytes. \n");
        printf("  OUTPUT: Decimal, CSV, brackets enclosing each report. \n\n");
        printf("Ex:\n");
        printf("  sudo %s 0x1111 0x2222 64\n", argv[0]);
        printf("  while(true); do sudo %s 0x1111 0x2222 64; done;\n\n", argv[0]);

        return 0;
    }


    unsigned int VENDOR_ID   = strtol(argv[1], NULL, 16);
    unsigned int PRODUCT_ID  = strtol(argv[2], NULL, 16);
    unsigned int REPORT_SIZE = strtol(argv[3], NULL, 10);

    if (VENDOR_ID   < 0 || VENDOR_ID   > 0xFFFF ||
        PRODUCT_ID  < 0 || PRODUCT_ID  > 0xFFFF ||
        REPORT_SIZE < 1 || REPORT_SIZE > 64) {

        printf("usb-hid-reporter: argument out of range.\n");
        return 1;
    }
    


    res = hid_init();
    if (res)
        printf("usb-hid-reporter: hid_init() error %d\n", res);

    handle = hid_open(VENDOR_ID, PRODUCT_ID, SERIAL_NUMBER);
    if (handle == NULL)
        printf("usb-hid-reporter: hid_open() error\n");

  
    res = hid_read(handle, buf, REPORT_SIZE);


    printf("{");
    for (i = 0; i < REPORT_SIZE-1; i++) {
        printf("%d,", buf[i]);
    }
    printf("%d", buf[ REPORT_SIZE-1 ]); //last element without tailing comma
    printf("}\n");


    res = hid_exit();
    if (res)
        printf("usb-hid-reporter: hid_exit() error %d\n}", res);
    
    return 0;
}
    

