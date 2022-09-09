/*
/******************************************************************************
It is a test program to test the GPIO pins present in the MMRFIC board.
REFRENCE :: Linux-5.14.0/DOCUMENTATION/gpio/dev-interface 
This program test the functionality of the board specific gpio pin with inbuilt export option enabled.
This program Takes integer as the command line arguments,the integer value is referenced to the gpio pin.

USAGE :
	gpio_test <pin_no>
      
/*****************************************************************************
*/


#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <errno.h>

//It is used to initialise the gpio pin or create the gpio pin.
void initialize_gpio(int fd , char *str, int gpio)
{

	fd = open("/sys/class/gpio/export", O_WRONLY);
	if(fd ==-1)
	  error(1,ENOENT,"Error while Initializing the pin\n");
	sprintf(str, "%d", gpio);
	if(write(fd, str, strlen(str)) < 0)
	   error(1,EIO,"Error while Writing in export file\n");
	close(fd);
}

//It is used to set the direction of the particular gpio pin as OUT or IN.
void direction_gpio(int fd, char *str, int gpio)
{
	sprintf(str, "/sys/class/gpio/gpio%d/direction", gpio);
	fd = open(str, O_WRONLY);
	if(fd ==-1)
	  error(1,ECONNREFUSED,"Error while accessing Device\n");
	if(write(fd, "out", 4) != 4)
	  error(1,EIO,"Error while Writing direction to gpio pin\n");
	close(fd);
}

//It is used to set the value of the particular gpio pin as 1 or 0
void value_gpio(int fd, char *str, int gpio)
{
	char buf[8];
	sprintf(str, "/sys/class/gpio/gpio%d/value", gpio);
	fd = open(str, O_RDWR);
	if (fd < 0) {
		fprintf(stderr, "Failed, gpio %d not exported.\n", gpio);
		exit(1);
	}
	
	if (write(fd, "1", 1) != 1)
	  error(1,EIO,"Error while Writing value to gpio pin\n");
	lseek(fd, 0, SEEK_SET);    
	if(read(fd, buf, sizeof(buf))<0)
	  error(1,EIO,"Error while Reading the data from gpio pin\n");
}
	
int main(int argc, char *argv[])
{
  	char str[256];
	struct pollfd pfd;
	int fd, gpio;
  
	if (argc == 2)
		gpio = atoi(argv[1]);
	else
	  error(1,EINVAL,"USAGE: test_gpio <pin_no>\n");
	
	initialize_gpio(fd, str,gpio);
	direction_gpio(fd,str,gpio);
	value_gpio(fd,str,gpio);
	
	printf("GPIO pin is enabled\n");
	close(fd);

	exit(0);
}

