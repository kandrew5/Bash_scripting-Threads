#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>	    
#include <string.h>         /* strcat()                 */
#include <time.h>	    /* srand(time())            */
#include <sys/wait.h>	    /* waitpid()		*/
#include <unistd.h>	    /* fork()			*/

typedef sem_t      Semaphore;
Semaphore *mutex;

int main()
{
        //VARIABLES
        int i;			//used in loops
        int n; 			//number of children
        int status;		//status for father to wait
        int *nSeconds;		//pointer to array with random numbers
        pid_t pid;		//pid for fork
        key_t shmkey;		//key for shared memory
        int shmid;		//id for shared memory
        char *t;		//temporary pointer to string for concatenation
        char *p;		/* shared memory */ /*this will have the final result*/
	char temp[256]="";	//temporary string to use in strcat()

	t = temp;		//assining pointer t to string temp

        srand(time(NULL));  //random number generator for seconds

        shmkey = ftok ("/dev/null", 5);				//initializing shared memory key
        shmid = shmget (shmkey,sizeof(int), 0644 | IPC_CREAT);	//initializing shared memory id

        if (shmid < 0)	//if shared memory fails
	{
                perror ("shmget\n");
                exit (1);
        }

        p  = (char *) shmat(shmid,0, 0); //attaching p to shared memory

        printf ("How many children do you want to fork?\n");		// asking user for number of children
        printf ("Fork count: ");
        scanf  ("%u", &n);

        mutex = sem_open ("pSem", O_CREAT | O_EXCL, 0644, 1); //linking mutex to pSem

        nSeconds = (int*)malloc(n * sizeof(int));  	 //making space for nSeconds[]
        for (i=0; i<n; i++) nSeconds[i] = rand()%4 + 1;  //random number of seconds in nSeconds array

        for(i=0;i<n;i++)		//creating n children
        {
                pid = fork ();

                if (pid < 0)		//if fork fails
                {
                        sem_unlink ("pSem");
                        sem_close(mutex);
                        printf ("Fork error.\n");
                }
                else if (pid == 0)	//if it is a child
                {
                        break;
                }
	}



	if(pid > 0)			/*parent proccess*/
	{
		while(pid = waitpid(-1,NULL,0)) /*has to wait until all children are finished*/
		{
			if(errno == ECHILD)
				break;
		}

		printf("All children have exited\n");
		printf(" *p = %s \n\n\n",p);  			//final result

		shmdt(p);					//detaching p from shared memory
		shmctl(shmid,IPC_RMID,0);

		sem_unlink("pSem");				//unlinkin semaphore
		sem_close(mutex);
	}
	else
	{
                sem_wait(mutex);					//down(mutex)

                printf (" Child(%d) enters the critical section.\n", i);
                printf (" Waiting %d seconds.\n", nSeconds[i]);
                sleep(nSeconds[i]);

		printf("Enter text to concatenate\n");

		char c= getchar();					//clearing input buffer

		scanf("%[^\n]s",temp);					//scan with spaces ( until you reach a new line )
		t = p;							//temporary pointer t now has the text we have given up until now

                printf (" Concatenating text to p\n");
		strcat(t,temp);						//concatenating text to t

		p = t;							//setting pointer p to point to the concatenated text
		*p = *t;
                printf (" Child(%d) exits the critical region\n", i);
		printf (" new *p = %s\n\n\n",p);			//printing result until now
                sem_post(mutex);                       			//up(mutex)
        }


return 0;
}
