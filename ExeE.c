#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */
#include <unistd.h>

typedef sem_t Semaphore;

Semaphore *synch1;
Semaphore *synch2;

int main()
{
   int child[5];
   int p=getpid();/*pid tou patera*/
   int i=0,j=0;
   pid_t pid[5];
   int status;

   synch1 = sem_open ("Sem1", O_CREAT | O_EXCL, 0644, 0);//arxikopoihsh semaphorwn
   synch2 = sem_open ("Sem2", O_CREAT | O_EXCL, 0644, 0);


	for(i=0;i<5;i++)
	{
   		pid[i] = fork ();
		if(pid[i] == 0)
		{
			child[i]=getpid();//apo8hkeuoume ta pid  twn paidiwn
			break;
		}
	}
	if(getpid()==p)//o pateras 8a perimenei na teleiwsoun ta paidia
	{
		for(j=0;j<5;j++)
		{
			waitpid(pid[j],&status,0);
		}
	sem_unlink ("Sem1");//diagrafei tous semaphorous
      	sem_close(synch1);
       	sem_unlink ("Sem2");
        sem_close(synch2);
	return 0;
	}

	else if(getpid()<0)//ama prokupsei kati la8os sthn fork diegrapse tous semaphores
	{
		sem_unlink ("Sem1");
        	sem_close(synch1);
        	sem_unlink ("Sem2");
        	sem_close(synch2);
       		printf ("Fork error.\n");
	}
//ka8e if  ka8orizei se poio paidi briskomaste
	if(getpid()==child[0])
	{
		printf("d1 is here\n");
		system("ls");
		sem_post (synch1);
		return 0;
	}
	if(getpid()==child[1])
	{
		printf("d2 is here\n");
		system("pwd");
		sem_post (synch1);
		return 0;
	}
	if(getpid()==child[2])
        {
                printf("d3 is here\n");
		system("pwd");
		sem_post (synch2);
		return 0;
        }
	if(getpid()==child[3])
        {
		sem_wait (synch1);
		sem_wait (synch1);
                printf("d4 is here\n");
		system("ls");
		sem_post (synch2);
		return 0;
        }
	if(getpid()==child[4])
        {
		sem_wait (synch2);
		sem_wait (synch2);
                printf("d5 is here\n");
		system("pwd");
		return 0;
        }
}
