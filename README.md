

# USB-HID-Reporter

Command-line utility to read HID Reports from USB devices.   
Tested with *NIX/x64 and OpenWRT/MIPS devices.



## Install instructions

A pre-compiled version is present in the dist folder.

### *NIX / x86-x64 Devices
(If running a 32bit machine, build from source)

- Install the libhidapi-libusb0 library. Debian/Ubuntu based: `sudo apt-get install libhidapi-libusb0`
- Plug the device to be inspected. Discover the VendorID/ProductID with the 'dmesg' command.
- Copy the file `usb-hid-reporter/dist/x64/usb-hid-reporter.x64.bin` to some working dir. 

**Usage**

`sudo ./usb-hid-reporter VENDOR_ID PRODUCT_ID REPORT_SIZE`

Ex:  
`sudo ./usb-hid-reporter 0x1111 0x2222 64`  
`while(true); do sudo ./usb-hid-reporter 0x1111 0x2222 64`

Expected output: (run without arguments to view help)  
`{38,198,102,192,1,28,54,0,0,0,0,0,0,0,0,0,0,0,0,0}`

VENDOR_ID/PRODUCT_ID: Hexadecimal - More info: www.linux-usb.org.  
REPORT_SIZE: Decimal - Length of USB Report in bytes.  
OUTPUT: Decimal, CSV, brackets enclosing each report.  

 

### Openwrt based devices 

Tested in MIPS/ar71xx (D-Link DIR505);  
Compatible with other devices/platforms as well, but may require rebuilding from source.  
The following steps assumes a device with internet connection and SSH access. 

- Enter the usb-hid-reporter folder in the host machine. 
(or appropriate folders of OpenwrtSDK if built from source)

- Copy the program binary to the device:  
`scp dist/mips_ar71xx/usb-hid-reporter.mips.bin root@192.168.1.1:/root`


- Install pre-requisites:  
```
opkg update  
opkg install libusb-compat libusb-1.0  
opkg install kmod-hid kmod-hid-generic kmod-usb-hid
```


- Copy required extra libs:  
```
scp dist/mips_ar71xx/usr/lib/libhidapi-libusb.so.0 root@192.168.1.1:/usr/lib  
ssh root@192.168.1.1 'ln -s libhidapi-libusb.so.0 /usr/lib/libhidapi-libusb.so'
```

- Reboot may be necessary

- Run:  `ssh root@192.168.1.1 '/root/usb-hid-reporter.mips.bin 0x1111 0x2222 64'`



## Building from source:

### Platform x64

- Working folder: `usb-hid-reporter/src/x64`  
Content description:  
Main program: chipcap-hidapi.c  
External lib: hidapi folder 

- If hidapi lib was downloaded from external source (ie. newer)   
```
cd hidapi  
make clean  
make all  
cd ..  
```

- Build and link:   
```
g++ -c -Ihidapi/hidapi usb-hid-reporter.c -o usb-hid-reporter.o  
g++ -Lhidapi/libusb/.libs usb-hid-reporter.o -lhidapi-libusb -o usb-hid-reporter.x64.bin  
rm usb-hid-reporter.o  
```

- Run:  `sudo ./usb-hid-reporter.x64.bin`  
Known issue: it's expected a segmentation fault in the Openwrt version if no device is found. 



### Platform Openwrt/MIPS/ar71xx/others

- Download the OpenWRT SDK:  
`https://downloads.openwrt.org/barrier_breaker/14.07/ar71xx/generic/OpenWrt-SDK-ar71xx-for-linux-x86_64-gcc-4.8-linaro_uClibc-0.9.33.2.tar.bz2`  
(or other appropriate SDK version, depending on your SO version / architecture)

- Extract indo a work dir. Ex: `/code/OpenwrtSDK`

- Copy the whole folder 'usb-hid-reporter'   
from: `src/mips_at71xx/OpenwrtSDK_complement/package/usb-hid-reporter` to: `workdir/OpenwrtSDK/package/`  
It's not necessary to add extra hidapi/usb libs; It will be used the ones from OpenwrtSDK. 

- Build (in the SDK root folder): `make V=99`

- Output will be in `OpenWrtSDK/build_dir/target-mips_34kc_uClibc-0.9.33.2/chipcap/ipkg-ar71xx/usb-hid-reporter/bin`

- Install into the device and run with the instructions above.  
Known issue: it's expected a segmentation fault in the Openwrt version if no device is found. 




## Known issues / TODO:  

- In MIPS/ar7xxx/OpenWRT program gives a segmentation fault if no devide is found. 
- Be able to run without root privileges. 
- Implement scan for SERIAL_NUMBER to differentiate products of same VID/PID.
- Verify if all libs listed in openwrt-install are really required. 
- Try some static linking to dismiss the installation of extra libs (usefull for openwrt devices with storage shortage)

## References

- Based upon the code of: http://www.signal11.us/oss/hidapi/
- https://github.com/torvalds/linux/blob/master/samples/hidraw/hid-example.c
- http://wiki.openwrt.org/doc/howto/obtain.firmware.sdk


## LICENSE

You are free to use this tool as you wish. Please attribute credit if you do so. 

```
/*
 * ----------------------------------------------------------------------------  
 * "THE BEER-WARE LICENSE":   
 * [http://en.wikipedia.org/wiki/Beerware]  
 * <mario.baldini@ieee.org> wrote this file. As long as you retain this notice you  
 * can do whatever you want with this stuff. If we meet some day, and you think  
 * this stuff is worth it, you can buy me a beer in return. -- Mario Baldini  
 * ----------------------------------------------------------------------------  
 */  
```





