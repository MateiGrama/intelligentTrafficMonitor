#include <unistd.h>
#include<stdio.h>
#include <fcntl.h>
FILE *fd;
int main() {
	char c;
	int ok=1;
        system("stty -F /dev/ttymxc3 cs8 115200");
	fd = fopen("/dev/ttymxc3", "r");
	if(fd==NULL)
	{
		printf("error oppening file\n");
		return 1;
	}
	while(ok){
		fscanf(fd, "%c", &c);
		printf("%c\n",c);
		usleep(1000000L);

		if(c == '1' ){
			system("gst-launch-0.10 mfw_v4lsrc ! ffmpegcolorspace ! ximagesink");
			ok=0;
		}
	}
	return 0;
}
