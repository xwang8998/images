#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <stdlib.h>
 
#define	 RGB888(r,g,b)	 ((r & 0xff) <<16 | (g & 0xff) << 8 | (b & 0xff))
#define	 RGB565(r,g,b)	 ((r & 0x1f) <<11 | (g & 0x3f) << 5 | (b & 0x1f))
 
int main()
{
	int fd = open("/dev/fb0", O_RDWR);
	if(fd < 0){
		perror("open err. \n");
		exit(EXIT_FAILURE);
	}
	struct fb_var_screeninfo info; 
 
	if ( (ioctl(fd, FBIOGET_VSCREENINFO, &info)) < 0){
		perror("ioctl err. \n");
		exit(EXIT_FAILURE);
	}
	
	printf("xres: %d\n", info.xres);
	printf("yres: %d\n", info.yres);
	printf("bits_per_pixel: %d\n", info.bits_per_pixel);
	
	size_t len = info.xres*info.yres*info.bits_per_pixel >> 3;	
	
	unsigned long* addr = NULL;
	addr = mmap(NULL, len, PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
	if(addr == (void*)-1){
		perror("mmap err. \n");
		exit(EXIT_FAILURE);
	}
 
	int i,j;
	for(i=0; i<768; i++){						//不同的电脑和系统像素不同，可以根据情况改变1366*768两个数的大小。
		for(j=0; j<1366; j++)
			//*(addr+i*1366+j) = RGB888(255, 0, 0);		//此处为画图位置，根据不同的数学公式，就可以给1366*768个像素上色。形成不一样的颜色！
			*(addr+i*1366+j) = RGB565(255, 0, 0);		//此为两种规格的像素。3个数分别带面红绿蓝的色彩深度。
	}	
	printf("hello main \n");
 
	int ret = munmap(addr, len);
	if(ret < 0){
		perror("munmap err. \n");
		exit(EXIT_FAILURE);
	}
 
	return 0;
}
