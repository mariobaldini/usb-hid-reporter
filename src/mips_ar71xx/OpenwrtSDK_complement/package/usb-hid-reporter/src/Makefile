# build helloworld executable when user executes "make"
usb-hid-reporter: usb-hid-reporter.o
	$(CC) $(LDFLAGS) usb-hid-reporter.o -o usb-hid-reporter -lhidapi-libusb
usb-hid-reporter.o: usb-hid-reporter.c 
	$(CC) $(CFLAGS) -c usb-hid-reporter.c

# remove object files and executable when user executes "make clean"
clean:
	rm *.o usb-hid-reporter


