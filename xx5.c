#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define PI 3.1415926535
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
    double t;
	double y;
	
	

	for(i=0;i<sample;i++)
	{
		t=(i/r)/10;
		y=(sqrt(0.5*0.5-pow(t-0.5,2)))+0.5;
		fprintf(fp,"%.4f\t%.6f\n",t,y);
		y=-(sqrt(0.5*0.5-(t-0.5)*(t-0.5)))+0.5;
		fprintf(fp,"%.4f\t%.6f\n",t,y);
		
		y=pow(t,3);
		fprintf(fp,"%.4f\t%.6f\n",t,y);
		y=pow(-t,3);
		fprintf(fp,"%.4f\t%.6f\n",-t,y);
	}
	fclose(fp);	
	int j;
	int f1 = 1000;//信号频率
	int num=65536;//采样点个数
	int fs=44100;//采样率
    double pr[num],pi[num],fr[num],fi[num],tt[num];
	double vol[num];
	int qs;
    for (i=0; i<=num; i++)  //生成输入信号
    { 
		tt[i] = (i*0.1)/(fs*0.1);
		pr[i]=0.5+0.5*cos(2*PI*f1*tt[i]);//+1*cos(2*PI*200*tt[i]+PI/2);
		pr[i]=pr[i]*pow(2,24);
		pr[i]=round(pr[i]);
		 pi[i]=0.0;
	}
	//********************use exit data***************
	#if USEEX==1
	FILE *sl;sl=fopen("../sound/srdata.dat","rt+");
		if(sl==NULL)
		{printf("Open file erro!");}
		else
		{
		for(i=0;i<num;i++)
			{
			fscanf(sl,"%x",&qs);
			printf("[%d]rdata= %x    ",i,qs);
			if((qs>>15)==1)
				qs =qs|0xffff0000;
			else ;
			printf("[%d]rdata= %x\n",i,qs);
			pr[i]=qs*0.1*10;
			}
		}
	fclose(sl);
	#endif
	//*************************************************
	int ttt=-3;
	printf("%x\n",ttt);
	FILE *fp2;fp2=fopen("./muisc.dat","w");
	for(i=0;i<num/2;i++)
	{
		fprintf(fp2,"%.16f\t%.16f\n",tt[i],pr[i]);
	}
	fclose(fp2);	

		vol[i]=pr[i];
	printf("***fft start %d*****\n",(int)log2(1024));	
    kfft(pr,pi,num,(int)log2(num),fr,fi);  //调用FFT函数
	FILE *fp1;fp1=fopen("./fft.dat","w");
	for(i=0;i<num/2;i++)
	{
		fprintf(fp1,"%.16f\t%.16f\n",i*0.1*10*fs/num,pr[i]);
	}
	fclose(fp1);	
	//**************************************************
	double max=pr[1];//必须等于a[0],只有这样比较出来的才是数组里面的最小数
	double min=pr[1];
	int sm=0;
	for(i=1;i<num;i++)
	{
		if(pr[i]>max)
		{
			max=pr[i];
		}
	}
	for(i=1;i<num/2;i++)
	{
		if(max-pr[i]<5)
			sm=i;
	}
		double thd,add,add1;
	for(i=1;i<6;i++)
	{
		printf("##[%d]  %.6f db\n",i,20*log10(pr[sm*i]/pr[sm]));
	}
	printf("*****sm=%d  max-sample = %.6f\n\n",sm,sm*0.1*10*fs/num);
	printf("*****max=%.6f\n",max);

	add=pow(pr[sm*2],2)+pow(pr[sm*3],2)+pow(pr[sm*4],2)+pow(pr[sm*5],2);
	add1=add-pow(sm,2);
	thd=(sqrt(add))/pr[sm];
	printf("**thd = %.12f--->%.6fdb\n",thd,20*log10(thd));
	printf("**my 83db ==>thd = 0.00001278--->%.6fdb\n",20*log10(0.00001278));
	//*****************************************************************


	}
