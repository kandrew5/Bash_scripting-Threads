
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>

void nothing();
#define N 100 // N einai o ari8mos twn diergasiwn
int main()
{
	int p=getpid();//pid tou patera
	time_t start, end;//arxikos kai telikos xronos
	start = time(NULL); //xronos pou arxizei to programma
	int i=0,j=0,status,pid[N];
	printf("Starting time=%ld\n",start);
	while(i<100)
	{
		pid[i]=fork();
		if(pid[i]==0)//an einai paidi
		{
			nothing();
			break;
		}
		i++;
	}
	if(getpid()==p)//pateras
	{
		for(j=0;j<100;j++)
		{
			waitpid(pid[j],&status,0);//pateras perimenei ola ta paidia
		}
	end = time(NULL);//telikos xronos
	printf("End time=%ld\n",end);
	printf("Total time=%ld\n",(end-start));
	printf("Average time=%ld\n",(end-start)/100);
	}
return(0);
}


void nothing()
{

	int x=0;
	x=x+1;
}
