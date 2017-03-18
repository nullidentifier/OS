#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<pthread.h>
#include<unistd.h>
int main(int argc, char *argv[])
{
        int height=0, childno=0,new_height=0,i=0,j=0;
        pid_t pid;
	if(argc!=4)
	{
		printf("\n invalid no of arguments\n");
		exit(0);
	}
        height=atoi(argv[1]);
        childno=atoi(argv[2]);
	int indent= atoi(argv[3]);
        new_height=height-1;
	printf("\n");
	for(j=0;j<indent;j++)
	{
		printf("\t");
	}
	printf("%d: Process starting\n",getpid());
	for(j=0;j<indent;j++)
	{
        	printf("\t");
	}

        printf("%d: Parent's id = (%d)\n",getpid(),getppid());
	for(j=0;j<indent;j++)
	{
	        printf("\t");
        }

        printf("%d: Height in the tree = %d\n", getpid(),height);
	for(j=0;j<indent;j++)
	{
        	printf("\t");
        }

        printf("%d: Creating %d  children at height %d\n",getpid(),childno,new_height);
	
	fflush(stdout);
        if(height==1)
        {
		printf("\n");
        	for(j=0;j<indent;j++)
		{
			printf("\t");
		 }
                printf("%d: Terminating at Height:%d\n",getpid(),height);
		printf("\n");
//		indent=0;
		
                exit(0);
        }

        for(i=0;i<childno;i++)
        {
                pid=fork();
                if(pid<0)
                {
                        perror("\nFork error..!!");
                        exit(1);
                }
                if(pid==0)
                {
			indent=indent+1;
                        printf("\nChild process created with id: %d", getpid());
                        sprintf(argv[1],"%d",new_height);
			sprintf(argv[3],"%d",indent);
                        execl("./process.out","./process.out",argv[1],argv[2],argv[3],NULL);
	
                 }
                

        }

          
              for(i=0;i<childno;i++)
		wait(NULL);
            
                printf("\n%d: Terminating at height=%d\n",getpid(),height);


        return 0;
}
