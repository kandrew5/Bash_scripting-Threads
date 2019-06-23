#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
	int i, tmp;
	pid_t pid[4];
	pid_t father=getpid(); //krataei to pid tou patera

    for (i=0;i<4;i++) {
        pid[i] = fork();
        if (pid[i] == 0) {//ta paidia kanoun break
            break;
        }
    }

    if (getpid()==father) {
        // an einai o pateras
        for(i=0;i<4;i++) {
            wait(&tmp);//perimene ta paidia
        }
	printf("Eimai o pateras [pid: %d, ppid: %d]\n",getpid(),getppid());
    } else {
        // paidi
        printf("Eimai to paidi me pid: %d,kai exw patera me ppid: %d]\n",getpid(),getppid());
    }

    return 0;
}
