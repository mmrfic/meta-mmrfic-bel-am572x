/*
*******************************************************************************
This Program is used to test the i2c protocol in MMRFIC Board. 
REFRENCE :: Linux-5.14.0/DOCUMENTATION/i2c/dev-interface 
It gets the data from the slave in the specific address and checks whether
the data is present.
USAGE :
      i2c <device_name>

*******************************************************************************
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <string.h>


#define I2C_SMBUS_BYTE_DATA     2
#define I2C_SMBUS_BLOCK_MAX	    32	    /* As specified in SMBus standard */
#define I2C_SMBUS       	    0x0720	/* SMBus transfer */
#define I2C_SMBUS_READ	        1       /* smbus_access read or write markers */
#define I2C_SMBUS_WRITE	        0       /* smbus_access read or write markers */
#define I2C_SLAVE	            0x0703	/* Use this slave address */

__u8 reg_addr = 0x08; 
char data[10];



union i2c_smbus_data {
	__u8 byte;
	__u16 word;
	__u8 block[I2C_SMBUS_BLOCK_MAX + 2]; /* block[0] is used for length */
	                                            /* and one more for PEC */
};

/* This is the structure as used in the I2C_SMBUS ioctl call */
struct i2c_smbus_ioctl_data {
	__u8 read_write;
	__u8 command;
	__u32 size;
	union i2c_smbus_data *data;
};

static inline __s32 i2c_smbus_access(int file, char read_write, __u8 command,
                                     int size, union i2c_smbus_data *data)
{
	struct i2c_smbus_ioctl_data args;

	args.read_write = read_write;
	args.command = command;
	args.size = size;
	args.data = data;
	return ioctl(file,I2C_SMBUS,&args);
}




 /* user readable statement*/
void help(int argc, char *argv[])
{
	if (argc != 2) {
		printf("use: i2c <device_name>\n");
		printf("Ex: i2c  </dev/i2c-0>\n");
		exit(0);
	}
}

/* i2c device opening */
int i2c_open(char *i2c)
{
	int fd = open(i2c,O_RDWR);
	if(fd == -1)
		error(1,ENOENT,"Error while Opening the Device");
return fd;
}

/*Used to configure the i2c device*/	
void i2c_config(int fd)
{
	int ret;
	if (ioctl(fd, I2C_SLAVE, 0x65) == -1)
		error(1,EFAULT,"Error While Setting Slave Address for PLL chip");
}

static inline __s32 i2c_smbus_read_byte_data(int file, __u8 command)
{
	union i2c_smbus_data data;
	if (i2c_smbus_access(file,I2C_SMBUS_READ,command,
	                     I2C_SMBUS_BYTE_DATA,&data))
		return -1;
	else
		return 0x0FF & data.byte;
}

static inline __s32 i2c_smbus_write_byte_data(int file, __u8 command, __u8 dataByte)
{
	union i2c_smbus_data data;
	data.byte = dataByte;
	if (i2c_smbus_access(file,I2C_SMBUS_WRITE,command,
	                     I2C_SMBUS_BYTE_DATA,&data))
		return -1;
	else
		return 0x0FF & data.byte;
}


/*It is used to write the file descriptor to access the i2c device*/
void i2c_write(int fd, __u8 addr, __u8 dataByte)
{

	printf("Writing..I2C slave: 0x65, addr: %2x, data: %2x....\n", addr, dataByte);
	
	memset(data, 0, sizeof(data));
	printf("Data confirmation = %d\n",i2c_smbus_write_byte_data(fd, addr, dataByte));
}

/*It is used to read the file descriptor to access the i2c device*/
void i2c_read(int fd)
{

printf("Reading...I2C slave: 0x65....\n");
	
		memset(data, 0, sizeof(data));
		printf("Data = %d\n",i2c_smbus_read_byte_data(fd,0x08));
}

/* i2c device closing */
void i2c_close(int fd)
{
	close(fd);
}
 
int main(int argc, char *argv[])
{
  int fd;

	help(argc, argv);
	fd = i2c_open(argv[1]);
	i2c_config(fd);
	//reg_addr = 0x0;
	//echo "i2cset -y 1 0x65 0x83 0x08"
	//i2cset -y 1 0x65 0x83 0x08
	i2c_write(fd, 0x83, 0x08);        
	//echo "i2cset -y 1 0x65 0x90 0x00"
	//i2cset -y 1 0x65 0x90 0x00
	i2c_write(fd, 0x90, 0x00);    
        //echo "i2cset -y 1 0x65 0x91 0x00"
        //i2cset -y 1 0x65 0x91 0x00
        i2c_write(fd, 0x91, 0x00);
       //echo "i2cset -y 1 0x65 0x92 0x00"
       //i2cset -y 1 0x65 0x92 0x00
       i2c_write(fd, 0x92, 0x00);
       //echo "i2cset -y 1 0x65 0x93 0x00"
       //i2cset -y 1 0x65 0x93 0x00
       i2c_write(fd, 0x93, 0x00);
       //echo "i2cset -y 1 0x65 0x94 0x6D"
       //i2cset -y 1 0x65 0x94 0x6D
       i2c_write(fd, 0x94, 0x6D);
       //echo "i2cset -y 1 0x65 0x95 0x02"
       //i2cset -y 1 0x65 0x95 0x02
       i2c_write(fd, 0x95, 0x02);
      //echo "i2cset -y 1 0x65 0x96 0x00"
      //i2cset -y 1 0x65 0x96 0x00
      i2c_write(fd, 0x96, 0x00);
      //echo "i2cset -y 1 0x65 0x97 0x32"
     //i2cset -y 1 0x65 0x97 0x32
     i2c_write(fd, 0x97, 0x32);
    //echo "i2cset -y 1 0x65 0x98 0xFA" 
     //i2cset -y 1 0x65 0x98 0xFA
     i2c_write(fd, 0x98, 0xFA);
     //echo "i2cset -y 1 0x65 0x99 0x0A"
     //i2cset -y 1 0x65 0x99 0x0A
     i2c_write(fd, 0x99, 0x0A);
    //echo "i2cset -y 1 0x65 0x9a 0x02"
     //i2cset -y 1 0x65 0x9a 0x02
     i2c_write(fd, 0x9a, 0x02);
     //echo "i2cset -y 1 0x65 0x9b 0x87"
     //i2cset -y 1 0x65 0x9b 0x87
     i2c_write(fd, 0x9b, 0x87);
     //echo "i2cset -y 1 0x65 0x9c 0xFA"
     //i2cset -y 1 0x65 0x9c 0xFA
     i2c_write(fd, 0x9c, 0xFA);
     //echo "i2cset -y 1 0x65 0x9d 0x0A"
    //i2cset -y 1 0x65 0x9d 0x0A
    i2c_write(fd, 0x9d, 0x0A);
     //echo "i2cset -y 1 0x65 0x9e 0x02"
     //i2cset -y 1 0x65 0x9e 0x02
     i2c_write(fd, 0x9e, 0x02);
     //echo i2cset -y 1 0x65 0x9F 0x84"
     //i2cset -y 1 0x65 0x9F 0x84
     i2c_write(fd, 0x9f, 0x84); 


       /*
	i2c_write(fd, reg_addr++,0x01);     //i2c_write(0x00,0x01);   
	i2c_write(fd, reg_addr++,0x00);     //i2c_write(0x01,0x00);   
	i2c_write(fd, reg_addr++,0xB4);     //i2c_write(0x02,0xB4);
	i2c_write(fd, reg_addr++,0x08);     //i2c_write(0x03,0x08);
	i2c_write(fd, reg_addr++,0x02);     //i2c_write(0x04,0x02);
	i2c_write(fd, reg_addr++,0x50);     //i2c_write(0x05,0x50);
	i2c_write(fd, reg_addr++,0x40);     //i2c_write(0x06,0x40);
	i2c_write(fd, reg_addr++,0x00);     //i2c_write(0x07,0x00);
	i2c_write(fd, reg_addr++,0x00);     //i2c_write(0x08,0x00);
	i2c_write(fd, reg_addr++,0x00);     //i2c_write(0x09,0x00);
	i2c_write(fd, reg_addr++,0x00);     //i2c_write(0x0a,0x00);
	i2c_write(fd, reg_addr++,0x00);     //i2c_write(0x0b,0x00);
	i2c_write(fd, reg_addr++,0x00);     //i2c_write(0x0c,0x00);
	i2c_write(fd, reg_addr++,0x00);     //i2c_write(0x0d,0x00);
	i2c_write(fd, reg_addr++,0x00);     //i2c_write(0x0e,0x00);
	i2c_write(fd, reg_addr++,0x00);     //i2c_write(0x0f,0x00);
	i2c_write(fd, reg_addr++,0x00);     //i2c_write(0x10,0x00);
	i2c_write(fd, reg_addr++,0x00);     //i2c_write(0x11,0x00);
	i2c_write(fd, reg_addr++,0x00);     //i2c_write(0x12,0x00);
	i2c_write(fd, reg_addr++,0x00);     //i2c_write(0x13,0x00);
	i2c_write(fd, reg_addr++,0x6d);     //i2c_write(0x14,0x6d);
	i2c_write(fd, reg_addr++,0x02);     //i2c_write(0x15,0x02);
	i2c_write(fd, reg_addr++,0x00);     //i2c_write(0x16,0x00);
	i2c_write(fd, reg_addr++,0x32);     //i2c_write(0x17,0x32);
	i2c_write(fd, reg_addr++,0xfa);     //i2c_write(0x18,0xfa);
	i2c_write(fd, reg_addr++,0x0a);     //i2c_write(0x19,0x0a);
	i2c_write(fd, reg_addr++,0x02);     //i2c_write(0x1a,0x02);
	i2c_write(fd, reg_addr++,0x87);     //i2c_write(0x1b,0x87);
	i2c_write(fd, reg_addr++,0x7a);     //i2c_write(0x1c,0x7a);
	i2c_write(fd, reg_addr++,0x0a);     //i2c_write(0x1d,0x0a);
	i2c_write(fd, reg_addr++,0x02);     //i2c_write(0x1e,0x02);
	i2c_write(fd, reg_addr++,0x84);     //i2c_write(0x1f,0x84);
	*/
	i2c_close(fd);                  
	return 0;                       
                                    
}                                   
