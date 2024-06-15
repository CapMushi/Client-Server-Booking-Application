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



void update(char info[])
{
	char content[1000];
	int fd=open("bookinginfo.txt",O_RDONLY);
	if (fd==-1)
	{
		perror("error in opening the file");
		exit(1);
	}
	
	ssize_t bytesRead = read(fd, content, sizeof(content) - 1); // Read up to sizeof(content) - 1 characters
    if (bytesRead == -1) {
	perror("error in reading the file");
	exit(1);
    }
    content[bytesRead] = '\0';
    close(fd);
    if(content[0]=='0')//file is empty
    {
    	content[0]='1';
    	content[1]='\n';
    	for(int i=2;info[i-2]!=0;i++)
    	{
    		content[i]=info[i-2];
    		content[i+1]='\0';
		}	
	}
	else
	{
		content[bytesRead] = '\n';
		int idx=bytesRead+1;
		for(int i=0;info[i]!=0;i++)
		{
		content[idx]=info[i];
		content[idx+1]='\0';
		idx++;
		}
		content[0]+=1;
		
		
	}
	
	fd=open("bookinginfo.txt",O_WRONLY);
	if (fd==-1)
	{
		perror("error in opening the file");
		exit(1);
	}
	
	
	if (write(fd,content,strlen(content))==-1)
	{
		perror("error in writing in the file");
		exit(1);
	}
	close(fd);
	cout<<"BOOKING INFO updated"<<endl;
	
}






int main()
{
	
	  char *buffer;
	
	  int id_sem=shmget(316, 1024, 0666 | IPC_CREAT | IPC_EXCL);
	  int id_cs= shmget(317, 1024, 0666 | IPC_CREAT | IPC_EXCL);
	  
	  int id_sem1=shmget(318, 1024, 0666 | IPC_CREAT | IPC_EXCL);
	
	  sem_t *semaphore;
	  sem_t *semaphore1;
	 
	  if (id_sem==-1 || id_cs==-1 || id_sem1==-1)
	  {
	   
	    perror("ERROR IN SHMGET");
	    exit(1);
	    
	    shmctl(id_sem, IPC_RMID, NULL);
	    shmctl(id_cs, IPC_RMID, NULL);
	    shmctl(id_sem1, IPC_RMID, NULL);
	    
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
    
       sem_init(semaphore, 1, 0); //1 means semaphore is used for process synchronization not needed in client
       sem_init(semaphore1, 1, 0); //1 means semaphore is used for process synchronization not needed in client
  
  
   bool run=true;
   while (run)
   {
   	 	cout<<"-----------------------------------------Welcome to Movie World-----------------------------------------"<<endl
	    <<"In theaters:"<<endl
		<<"[1]Donkey King"<<endl 
		<<"[2]Avengers"<<endl 
		<<"[3]Bohemian Rhapsody"<<endl 
		<<"[4]Halloween"<<endl 
		<<"[5]First Man"<<endl
		<<endl<<"ENTER MOVIE NO AND TICKET QUANTITY <=9: "<<endl; 
		sem_post(semaphore); 	
		sem_wait(semaphore1);
		
		cout<<buffer[0]<<" "<<buffer[1]<<endl;//buffer 0 movieno,buffer 1 quantity
		
		char content[1000];
		int fd=open("movieinfo.txt",O_RDONLY);
		if (fd==-1)
		{
			perror("error in opening the file");
			exit(1);
		}
		
		ssize_t bytesRead = read(fd, content, sizeof(content) - 1); // Read up to sizeof(content) - 1 characters
		    if (bytesRead == -1) {
			perror("error in reading the file");
			exit(1);
		    }
		    content[bytesRead] = '\0';
		cout<<"File read"<<endl;
		close(fd);
		int idx=0,stopidx=0,dash=0;
		char gotilldashcount=buffer[0];
		
		for(;(content[idx]!=0) && (dash<(2*atoi(&gotilldashcount)));idx++)
		{
			if(content[idx]=='/')
			 dash++;
			
		}
		
		
		
		int count=0;
		for(int i=idx;content[i]!='\n';i++)
		{
			if(content[i+1]=='\n')
			 stopidx=i+1;
			count++;
		}
		
		
	       
	
	    char *tq=new char[count+1];
	    for(int i=idx,j=0;content[i]!='\n';i++)
		{
			tq[j]=content[i];
			j++;
		}
		
		tq[count]='\0'; 
	
		
		
		if(atoi(&buffer[1])<=(atoi(tq))) //quantity less than or equal to tickets
		{
			int bill=(500*atoi(&buffer[1]));
			
			string sb=to_string(bill);
			
			for(int i=2;sb[i-2]!=0;i++)
			{
			    buffer[i]=sb[i-2];
			    buffer[i+1]='*';
	
			}
			
			
			sem_post(semaphore); 
			sem_wait(semaphore1);
			if (buffer[0]=='y')
			{
			        char qt=buffer[1];
				int newremaining=(atoi(tq)-atoi(&qt));
			
				string nr=to_string(newremaining);
				char content2[1000];
				
				int i=0,k=0;
				while(content[i]!=0)
				{
					if(i==idx)
					{
						for(int j=0;nr[j]!=0;j++)
						{
							content2[k++]=nr[j];
						}
						i=stopidx;
					}
					else
					{
						content2[k++]=content[i];
						i++;
					}
				}
				content2[k]='\0';
				cout<<endl;
				i=0;
				//while(content2[i]!=0)
				//{
					//cout<<content2[i];
					//i++;
				//}
				//cout<<endl;
				
				fd=open("movieinfo.txt",O_WRONLY);
				if (fd==-1)
				{
					perror("error in opening the file");
					exit(1);
				}
				
				
				if (write(fd,content2,strlen(content2))==-1)
				{
					perror("error in writing in the file");
					exit(1);
				}
				
				cout<<"Enter 4 digit CNIC: "<<endl;
				char info[9];
				info[4]='/';info[5]=gotilldashcount;info[6]='/';info[7]=buffer[1];info[8]='\0';
				sem_post(semaphore); 
				sem_wait(semaphore1);
				for(int j=0;j<4;j++)
				{
				   info[j]=buffer[j];
				
				}
				
				for(int j=0;j<8;j++)
				{
				   cout<<info[j];
				
				}
				cout<<endl;
				update(info);
				
				
				
				
				cout<<"Reservation booked"<<endl;
				close(fd);
	        }
	        else {
	        	cout<<"Booking cancelled by customer"<<endl;
			}
				
		}
			
			
		else
		{
			cout<<"Reservation Cancelled as entered quantity is more than avaiailable tickets"<<endl;
		}
		
		
		free(tq);
		memset(buffer, 0, 1024);
		
		char ans;
		cout<<"Are there more clients?";
		cin>>ans;
		if (ans=='n')
		 run=false;
   }
   
	    
	    
		
	
	

	
		
		
		
		
		
    	
    	
    	
    	
    	
	
	
    if (sem_destroy(semaphore) == -1) {
        perror("sem_destroy");
        exit(1);
    }
    
    if (sem_destroy(semaphore1) == -1) {
        perror("sem_destroy");
        exit(1);
    }
    
  
  
  //not needed in client
    if (shmdt(semaphore) == -1) {
        perror("shmdt");
        exit(1);
    }
    
    if (shmdt(buffer) == -1) {
        perror("shmdt");
        exit(1);
    }
    
    if (shmctl(id_sem, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }
    
    if (shmctl(id_cs, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }
    
    if (shmdt(semaphore1) == -1) {
        perror("shmdt");
        exit(1);
    }
    
    if (shmctl(id_sem1, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }
    
    cout<<"SERVER OFFLINE"<<endl;
    
  

    system("pause");
    return 0;
}

