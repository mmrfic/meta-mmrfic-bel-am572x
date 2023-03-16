/*
*******************************************************************************
This program is used to check the UART protocol presen in the MMRFIC Board.
REFRENCE :: Linux-5.14.0/DOCUMENTATION/uart/dev-interface 
Usage: It takes the Device names as an arguments and check their count for its operational mode.
When one argument(uart device) is provided, it checks the device in loopback mode.
When two arguments are provided,  it checks the device in duplex mode. By settng the devices as sender and receiver.

USAGE :
       uart_test device_name OR uart_test <device_name1> <device_name2>

*******************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>

//It opens the file descriptor to access uart device.
int uart_open(char *uart)
{
	int fd;
	fd = open(uart, O_RDWR | O_NOCTTY | O_SYNC);
	if(fd == -1)
		error(1, ENOENT, "Error occur while Opening the Device\n");
	return fd;
}

// It is used to configure the uart device in the desired modes.
void uart_config(int fd, int speed)
{
	struct termios serial;

	if(tcgetattr(fd,&serial) == -1)
		error(1,EBADF,"Error while reading Confnguration of the Device");
	cfsetospeed(&serial, (speed_t)speed); 
	cfsetispeed(&serial, (speed_t)speed); 


	serial.c_cflag |= (CLOCAL | CREAD);   
	serial.c_cflag &= ~CSIZE;
	serial.c_cflag |= CS8;         
	serial.c_cflag &= ~PARENB;    
	serial.c_cflag &= ~CSTOPB;     
	serial.c_cflag &= ~CRTSCTS;   

	serial.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR
			 | ICRNL | IXON);
	serial.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	serial.c_oflag &= ~OPOST;

	serial.c_cc[VMIN] = 1;
	serial.c_cc[VTIME] = 1;

	if (tcsetattr(fd, TCSANOW, &serial) != 0)
		error(1,EBADF,"Error while writing Configuration of the Device");
}

//It is used to transfer the data to the device.
void  uart_transfer(int fd)
{
	if(write(fd, "hello mmrf", 10) < 10)
		error(1,EIO,"Error while Transfering Data in the device");
	printf("Writting Data.....\n");

}

//It is used to receive data from the device.
void uart_receive(int fd)
{
	unsigned char buffer[10];
	printf("Device Reading .....\n");
	if(read(fd,buffer,sizeof(buffer)) != sizeof(buffer))
		error(1,EIO,"Error while Reading data from the Device");
	printf("%s\n",buffer);
}


//It closes the file descriptor which was opened to access uart device.
void uart_close(int fd)
{
	close(fd);
}

//It is used to test the uart devices in the loopback mode.
int loop_back(char *uart)
{
	int lb;

	lb = uart_open(uart);
	uart_config(lb , B115200);
	uart_transfer(lb);
	tcdrain(lb);
	uart_receive(lb);
	uart_close(lb);
	printf("Loopback Test Success\n");
}

//It is used to test the uart devices in the duplex mode.
void duplex(char *uart1, char *uart2)
{
	int lb1, lb2;
	lb1 = uart_open(uart1);
	lb2 = uart_open(uart2);
	uart_config(lb1,B115200);
	uart_config(lb2,B115200);
	uart_transfer(lb1);
	tcdrain(lb1);
	uart_receive(lb2);
	uart_close(lb1);
	uart_close(lb2);
	printf("Duplex Test Success\n");
}
	


int main(int argc , char *argv[])
{

	switch(argc)
	{
	case 2:
		loop_back(argv[1]);
		break;
	case 3:
	  duplex(argv[1],argv[2]);
		break;
	default:
	  error(1,EINVAL,"Usage : uart_test device_name OR uart_test <device_name1> <device_name2>");
	}
	return 0;
}

