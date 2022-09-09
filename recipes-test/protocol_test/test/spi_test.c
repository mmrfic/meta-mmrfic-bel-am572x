/*
**************************************************************************
This program is used to test the spi protocol in the MMRFIC Board.
REFRENCE :: Linux-5.14.0/DOCUMENTATION/spi/dev-interface
This program checks whether the spi is working on the specific board by
sending and receiving data through the protocol.
This program takes the address of the spi device as an argument and 
configure the spi to desired modes to transfer and receive data through it.

USAGE :
	spi <device_name>

**************************************************************************
*/




#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <error.h>
#include <errno.h>


#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

static uint8_t mode;
static uint8_t bits = 8;
static uint32_t speed = 50000;
static uint16_t delay;

uint8_t tx_data[] = {0xAB, 0xCD, 0xFF, 0XEF, 0xBA};
uint8_t rx_data[ARRAY_SIZE(tx_data)] = {0, };


//This function checks the command-line arguments of the program.
void arguments(int argc, char *argv[])
{
	if(argc != 2) {
		puts("use: spi <device_name>");
		puts("Ex: spi </dev/spidev1.0>");
		exit(1);
	}
}

//It opens the file descriptor to access spi device.
int spi_open(char *file_name)
{
	int fd;
	fd = open(file_name,O_RDWR);
	if(fd == -1) {
		error(1,ENOENT,"Error occur while Opening the Device\n");
	}	
	return fd;
}


// It is used to configure the spi device in the desired modes using ioctl functions.
void spi_configure(int fd)
{
	mode = SPI_MODE_3;
	
	// SPI mode
	if(ioctl(fd, SPI_IOC_RD_MODE, &mode) == -1)
		error(1,EIO,"Error While getting SPI mode\n");

	if(ioctl(fd, SPI_IOC_WR_MODE, &mode) == -1)
		error(1,EIO,"Error While setting SPI mode\n");

	//Bits per word
	if(ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits) == -1)
		error(1,EIO,"Error Occured while Getting bits per word\n");

	if(ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits) == -1)
		error(1,EIO,"Error Occured while Setting bits per word\n");

	// Max speed in hz
	if(ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed) == -1)
		error(1,EIO,"Error Occured while Getting Maximum speed of SPI in Hz\n");

	if(ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1)
		error(1,EIO,"Error Occured while Setting Maximum speed of SPI in Hz\n");

	printf("Spi mode: %d\n",mode);
	printf("Bits per word: %d\n",bits);
	printf("Max speed : %d Hz\n",speed);

}

//This function receives the file descriptor associated with the spi device as an argument and transfers data through the device.
void spi_transfer(int fd)
{
	int len = sizeof(tx_data);

	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)tx_data,
		.rx_buf = (unsigned long)rx_data,
		.len = len,
		.delay_usecs = delay,
		.speed_hz = speed,
		.bits_per_word = bits,
	};

	if(ioctl(fd, SPI_IOC_MESSAGE(1), &tr) == -1)
		error(1,EIO,"Can not transfer the message\n");

	for(int ret = 0; ret < ARRAY_SIZE(tx_data); ret++) {
		if(!(ret % 6))
			puts("");
		printf("%.2X ",rx_data[ret]);
	}
	puts("");
}

//It closes the file descriptor which was opened to access spi device.
void spi_close(int fd)
{
	close(fd);
}
	
int main(int argc, char *argv[])
{
	int fd = 0;

	arguments(argc, argv);	
	fd = spi_open(argv[1]);
	spi_configure(fd);	
	spi_transfer(fd);
	spi_close(fd);
}

