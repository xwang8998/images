#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define pi 3.1415

int main(int argc,char *argv[])
{
	u_int32_t sample;
	sample =atoi(argv[1]);	
	printf("*******sample = %d********\n", sample);
	FILE *fp;
	fp=fopen("./sin1.dat","w");
    int i;
	double r;
	r=(sample*0.1);
    double t,y;
	for(i=0;i<sample;i++)
	{
		t=i/(r*10);
		y=0.6*sin(2*pi*50*t);
		if(i%10==0)
		fprintf(fp,"#%d",i);
		fprintf(fp,"%.4f\t%.6f\n",t,y);
	}
	fclose(fp);
}
