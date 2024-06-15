#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>
#include<fcntl.h>
#include <cstring>
#include <string>
#include <string.h>
#include<iostream>
using namespace std;
#include <semaphore.h>

int main()
{
	
	  char *buffer;
	
	  int id_sem=shmget(316, 1024, 0);
	  int id_cs= shmget(317, 1024, 0);
	  
	  int id_sem1=shmget(318, 1024, 0);
	
	  sem_t *semaphore;
	  sem_t *semaphore1;
	 
	  if (id_sem==-1 || id_cs==-1 || id_sem1==-1)
	  {
	   
	    perror("ERROR IN SHMGET");
	    exit(1);
	    
	  }
  
	if ((semaphore= (sem_t*) shmat(id_sem, NULL, 0)) == (sem_t*) -1)
	{
	    perror("SHMAT");
	    exit(1);
	}
   
  
  	if ((buffer= (char*) shmat(id_cs, NULL, 0))== (char *) -1)
  	{
  	    perror("SHMAT");
            exit(1);
        }
        
        if ((semaphore1= (sem_t*) shmat(id_sem1, NULL, 0)) == (sem_t*) -1)
	{
	    perror("SHMAT");
	    exit(1);
	}
    
    
  
  
    char movieno,totaltickets;
    
    while(1)
    {
                sem_wait(semaphore);
		cin>>movieno;
		cin>>totaltickets;
		
		buffer[0]=movieno;
		buffer[1]=totaltickets;
		sem_post(semaphore1); 
		sem_wait(semaphore);
		cout<<"Your Bill is : ";
		
		for(int i=2;buffer[i]!='*';i++)
		{
		   cout<<buffer[i];
		}
		cout<<endl;
		char l;
		cout<<"Do you wish to continue? Press y for YES n for NO"<<endl;
		cin>>l;
		buffer[0]=l;
		sem_post(semaphore1); 
		sem_wait(semaphore);
		string cnic;
		cin>>cnic;
		for(int i=0;i<4;i++)
		{
		   buffer[i]=cnic[i];
		}
		sem_post(semaphore1); 
    
    }
    
		
		
		
		
			
	
	

  
  
  
  

    system("pause");
    return 0;
}

