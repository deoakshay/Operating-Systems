//Akshay Deo 006939024

#include "schedule.h"
#include <stdlib.h>
#include <stdio.h>


/**
 * Function to initialize any global variables for the scheduler.
 */
void init(){
	int i;
	 for(i=0;i<3;i++)
	 {
	 tempp[i]=(struct node*) malloc( sizeof(struct node));
	 tempp[i]->next=NULL;
	}

	 head = (struct node*) malloc( sizeof(struct node));
	immediate=(struct node*) malloc( sizeof(struct node));
	temp=(struct node*) malloc( sizeof(struct node));
	head->pid=-111;
	tail=(struct node*) malloc( sizeof(struct node));
	tail=head;
	mn=0;
	max_p=0;
	min_p=0;
}

/**
 * Function called every simulated time period to provide a mechanism
 * to age the scheduled processes and trigger feedback if needed.
 */
void age()
{
int pid;

		if(tempp[1]->next!=NULL)
		{
			head=tempp[1]->next;
			immediate=head;
			while(immediate->next!=head)
			immediate=immediate->next;
			tail=immediate;
			immediate=head;
			while(immediate!=tail)
			{
				immediate->age1++;

				if(immediate->age1>=1000)
				{
					pid=immediate->pid;
					immediate=immediate->next;
					removeProcess(pid);
					addProcess(pid,0);
				}

				immediate=immediate->next;
			}
			if(immediate->age1>=1000)
			{
				pid=immediate->pid;

				removeProcess(pid);
				addProcess(pid,0);
			}
			else
			{
				immediate->age1++;


		}
		}


		if(tempp[2]->next!=NULL)
		{
			head=tempp[2]->next;
			immediate=head;
			while(immediate->next!=head)
			immediate=immediate->next;
			tail=immediate;
			immediate=head;
			while(immediate!=tail)
			{
				if(immediate->age1>=1000)
				{
					pid=immediate->pid;
					immediate=immediate->next;

					removeProcess(pid);
					addProcess(pid,1);
				}
				immediate->age1++;

				immediate=immediate->next;
			}
			if(immediate->age1>=1000)
			{
				pid=immediate->pid;

				removeProcess(pid);
				addProcess(pid,1);
			}
			else
			{
			immediate->age1++;

		}
		}


}

/**
 * Function to add a process to the scheduler
 * @Param pid - the ID for the process/thread to be added to the
 *      scheduler queue
 * @Param priority - priority of the process being added
 * @return true/false response for if the addition was successful
 */
int addProcess(int pid, int priority){
	if(priority>min_p)
	   {
	     min_p=priority;
	   }
	   else
	   {
	     if(priority<max_p)
	     {
	       max_p=priority;
	     }
	   }

	 if(tempp[priority]->next==NULL)
	  {
	    tempp[priority]->next=(struct node*)malloc(sizeof(struct node));
	    tempp[priority]->next->pid=pid;
			tempp[priority]->next->age1=0;
	    tempp[priority]->next->previous=tempp[priority]->next;
	    tempp[priority]->next->next=tempp[priority]->next;
	    tail=head=tempp[priority]->next;
	    tempp[priority]->previous=NULL;
	  tempp[priority]->priority=priority;

	    return 1;
	 }
	  else
	  {
	    immediate=tempp[priority]->next;
	     head=immediate;
	    while(immediate->next!=head)
	    {
	      immediate=immediate->next;
	    }
	    tail=immediate;
	    tail->next=(struct node*)malloc(sizeof(struct node));
	    tail->previous=(struct node*)malloc(sizeof(struct node));
	    tail=tail->next;
	    tail->pid=pid;
			tail->priority=priority;
			tail->age1=0;
	    tail->next=head;
	    tail->previous=immediate;

	return 1;
	  }

	return 0;

}

/**
 * Function to remove a process from the scheduler queue
 * @Param pid - the ID for the process/thread to be removed from the
 *      scheduler queue
 * @Return true/false response for if the removal was successful
 */
int removeProcess(int pid){
	int flag=0;
  int a;
for(a=0;a<=min_p;a++)
{
  if(tempp[a]->next!=NULL)
  {
    immediate=tempp[a]->next;
    head=immediate;
    while(immediate->next!=head)
    {
     if(immediate->pid==pid)
     {

flag=1;
     break;
    }
     else
     immediate=immediate->next;
   }
   if(immediate->pid==pid)
   {

flag=1;
   break;
  }

   if(flag==1)
   {
     break;
   }
   else
   continue;
  }

}

head=immediate;
temp=immediate;
while(temp->next!=head)
{
  temp=temp->next;
}
tail=temp;
if(immediate==head&&tail!=head)
{
  head=head->next;
  tail->next=head;
  head->previous=tail;
  immediate->next=NULL;
  immediate->previous=NULL;
	tempp[a]->next=head;
  free(immediate);
  return 1;
}
else if(immediate==head&&tail==head)
{

 head=NULL;
 tempp[a]->next=NULL;
 free(head);
 return 1;
}
else if(immediate==tail)
{
   tail=tail->previous;
   tail->next=head;
   immediate->next=NULL;
   immediate->previous=NULL;
   free(immediate);
   return 1;
}
else
{
    temp=immediate->previous;
    temp->next=immediate->next;
    immediate->next->previous=temp;
    immediate->next=NULL;
    immediate->previous=NULL;
    free(immediate);
    return 1;
}
  return 0;
}
/**
 * Function to get the next process from the scheduler
 * @Param time - pass by pointer variable to store the quanta of time
 * 		the scheduled process should run for, returns -1 if should run to completion.
 * @Return returns the thread id of the next process that should be
 *      executed, returns -1 if there are no processes
 */
int nextProcess(int *time){
	int i;
	int pid=0;
	int flag=0;
	for(i=0;i<=min_p;i++)
	{
		if(tempp[i]->next==NULL)
		flag++;
	}
	if(flag>min_p)
	return -1;
	if(tempp[0]->next!=NULL)
		mn=0;
	else if(tempp[0]->next==NULL && tempp[1]->next!=NULL)
	mn=1;
	else if(tempp[0]->next==NULL&&tempp[1]->next==NULL)
	mn=2;

	head=tempp[mn]->next;
	if(mn==0)
  {
		pid=head->pid;
		removeProcess(pid);
	}
	else if(mn==1)
	{
		*time=4;
		immediate=head;
		while(immediate->next!=head)
		immediate=immediate->next;
		tail=immediate;
		pid=head->pid;
		immediate=head;
		tail->next=immediate;
		immediate->previous=tail;
		tail=immediate;
		tail->age1=-4;
		head=head->next;
		tempp[mn]->next=head;

	}
	else if(mn==2)
	{
		*time=1;
		immediate=head;
		while(immediate->next!=head)
		immediate=immediate->next;
		tail=immediate;
		pid=head->pid;
		immediate=head;
		tail->next=immediate;
		immediate->previous=tail;
		tail=immediate;
		head=head->next;
		tail->age1=-1;
		tempp[mn]->next=head;

	}
	return pid;
}

/**
 * Function that returns a boolean 1 True/0 False based on if there are any
 * processes still scheduled
 * @Return 1 if there are processes still scheduled 0 if there are no more
 *		scheduled processes
 */
int hasProcess(){
	int i;
	int flag=0;
	for(i=0;i<=min_p;i++)
	{
		 if(tempp[i]->next==NULL)
			flag++;
	}
	if(flag>min_p)
	return 0;
	else
	return 1;
	//return 0;
}
