#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

void intitArray(int a[]){
    for(int i=0;i<1000;i++){
		a[i]=i;		
	}
}
int main(){
	int parentSum[10], Arr[1000], pipearr[2];
	intitArray(Arr);
	for(int i=0;i<10;i++){
		if(pipe(pipearr)==-1){
			printf("pipe failed\n");
		}
			
		int cpid=fork();
		if(cpid==0){
			close(pipearr[0]);		
			int sum1=0;
			for(int j=i*100;j<i*100+100;j++){
				sum1=sum1+Arr[j];	
			}
			write(pipearr[1],&sum1,sizeof(sum1));
			close(pipearr[1]);	
			exit(0);
		}
		else{
			wait(NULL);
			close(pipearr[1]);
			parentSum[i]=0;
			read(pipearr[0],&parentSum[i],sizeof(parentSum[i]));
			printf("%d\n",parentSum[i]);
		}
	}
	int totalSum=0;
	for(int i=0;i<10;i++){
		totalSum+=parentSum[i];
	}
	printf("%d\n",totalSum);		
	return 0;
}
