#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define VFIFO_DEV_NAME "/dev/demo_dev"
int main()
{
	char buffer[64];
	int fd;
	fd = open(VFIFO_DEV_NAME, O_RDONLY);
	if(fd<0)
	{
		printf("open device %s failed.\n", VFIFO_DEV_NAME);
		return -1;
	}
	read(fd, buffer, 64);
	close(fd);
	return 0;
}
