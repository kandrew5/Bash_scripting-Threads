#include <stdio.h>
#include <stdlib.h>

int main() {
int i,status;
int pid;


	for(i=0; i<5; i++) {
	pid=fork();

	if(pid!=0)//pateras
	{
		printf("Pateras %d Id %d Paidi %d\n",getppid(), getpid(), pid);
		wait(&status);//perimenei na teleiwsei to paidi
		break;
        }
	}
	return 0;
	}
