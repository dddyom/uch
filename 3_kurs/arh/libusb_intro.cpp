/*
Ознакомиться с началами низкоуровневого программирования периферийных устройств на примере получения информации о доступных USB-устройствах с помощью библиотеки libusb.
#include <stdio.h>
#include <libusb-1.0/libusb.h>
#include <iostream>

using namespace std;
void printdev(libusb_device* dev,libusb_context* ctx );
int main() { 
	
	libusb_device** devs;
	
	libusb_context* ctx = NULL;
	int r;
	ssize_t cnt;
	ssize_t i;
	
	r = libusb_init(&ctx);
	if(r<0){
		fprintf(stderr, "Error! code: %d.\n", r);
	}
	
	//libusb_set_debug(ctx, 3);
	
	cnt = libusb_get_device_list(ctx, &devs);
	if(cnt < 0) {
		cout << "Error: USB list not found.\n" << endl;
		return 1;
	}
	
	printf("Found devices: %ld\n", cnt);
	
	printf("==================================================\n");

	printf("* count possible configuration\n");
	printf("|  * class device\n");
	printf("|  |  * indentity manufacturer\n");
	printf("|  |  |  * identity device\n");
	printf("|  |  |  |  * count interfaces\n");
	printf("|  |  |  |  |  * count alternative settings\n");
	printf("|  |  |  |  |  |  * class device\n");
	printf("|  |  |  |  |  |  |  * number interfaces\n");
	printf("|  |  |  |  |  |  |  |  * count end points\n");
	printf("|  |  |  |  |  |  |  |  |  * type of description\n");
	printf("|  |  |  |  |  |  |  |  |  | * addres end point\n");
	printf("+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+\n");
	
	for(i =0; i < cnt; i++) {
		printdev(devs[i], ctx);
	}
	
	printf("===================================================\n");
	
	libusb_free_device_list(devs, 1);
	libusb_exit(ctx);
	
	return 0;
}


void printdev(libusb_device* dev, libusb_context * ctx) {
	libusb_device_descriptor desc;
	libusb_config_descriptor* config;
	const libusb_interface* inter;
	const libusb_interface_descriptor* interdesc;
	const libusb_endpoint_descriptor *epdesc;
	int r = libusb_get_device_descriptor(dev, &desc);
	
	if(r < 0){
		
		cout << "Error: descriptor not found, code: %d.\n" << endl;
		return;
	}
	
	libusb_get_config_descriptor(dev, 0, & config);
	printf("%.2d  %.2d  %.4d  %.4d  %.3d  |  |  |  |  |  |\n",
	(int)desc.bNumConfigurations,
	(int)desc.bDeviceClass,
	desc.idVendor,
	desc.idProduct,
	(int)config->bNumInterfaces
	);
	
	for(int i = 0; i < (int)config->bNumInterfaces; i++) {
		inter = &config->interface[i];
		printf("|  |  |  |  |  %.2d  %.2d  |  |  |  |\n",
		inter->num_altsetting,
		(int)desc.bDeviceClass
		);
	
		for(int j =0; j < inter->num_altsetting; j++) {
			interdesc = &inter->altsetting[j];
			printf("|  |  |  |  |  |  |  %.2d  %.3d  |  |\n",
			(int)interdesc->bInterfaceNumber,
			(int)interdesc->bNumEndpoints
			);
			
			for(int k =0; k < (int)interdesc->bNumEndpoints; k++) {
				epdesc = &interdesc->endpoint[k];
				printf("|  |  |  |  |  |  |  |  |  %.2d  %.9d\n",
				(int)epdesc->bDescriptorType,
				(int)(int)epdesc->bEndpointAddress
				);
			}
		}
	}
	
	libusb_device_handle* handle;
	handle = libusb_open_device_with_vid_pid(ctx,desc.idVendor,desc.idProduct);
 
	if(libusb_open(dev, &handle) == 0) {
		
		unsigned char uSerialNumber[255] = {};
		
		int iSerialNumber = libusb_get_string_descriptor_ascii(
			handle, desc.iSerialNumber, 
			uSerialNumber, sizeof(uSerialNumber)
		);
		
		
		printf("SERIAL NUMBER %d \n", iSerialNumber);
		printf("uSerialNumber %s\n", uSerialNumber);
		libusb_close(handle);
	}

	libusb_free_config_descriptor(config);
}

*/