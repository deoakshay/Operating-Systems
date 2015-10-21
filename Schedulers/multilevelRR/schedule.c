/*
*
*
* Akshay Deo 006939024
*/

#include "schedule.h"
#include <stdlib.h>
/**
 * Function to initialize any global variables for the scheduler.
 */
void init()
{
	int i;
   for(i=0;i<4;i++)
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
}

/**
 * Function to add a process to the scheduler
 * @Param pid - the ID for the process/thread to be added to the
 *      scheduler queue
 * @Param priority - priority of the process being added
 * @return true/false response for if the addition was successful
 */
int addProcess(int pid, int priority)
{
	priority=priority-1;

	 if(tempp[priority]->next==NULL)
	  {
	    tempp[priority]->next=(struct node*)malloc(sizeof(struct node));
	    tempp[priority]->next->pid=pid;
	    tempp[priority]->next->previous=tempp[priority]->next;
	    tempp[priority]->next->next=tempp[priority]->next;
	    tail=head=tempp[priority]->next;
	    tempp[priority]->previous=NULL;
	  int p=priority;
	  priority=priority+1;
	  tempp[p]->priority=priority;
	   max_p=priority;
	   min_p=priority;
	   tempp[p]->pid=0;
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
	    tail->next=head;
	    tail->previous=immediate;
	priority=priority+1;
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
int removeProcess(int pid)
{
	int flag=0;
  int a=0;
for(a=0;a<min_p;a++)
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
if(immediate==head&&immediate->next!=head)
{
  head=head->next;
  tempp[a]->next=head;
  immediate->previous->next=head;
  head->previous=immediate->previous;
  immediate->next=NULL;
  immediate->previous=NULL;
  free(immediate);
  return 1;
}
else if(immediate==head&&immediate->next==head)
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
 * 		the scheduled process should run for
 * @Return returns the thread id of the next process that should be
 *      executed, returns -1 if there are no processes
 */
int nextProcess(int *time)
{
	if(mn>3)
	{
	mn=0;
	}
	int pid;
int a=min_p-1;

if(tempp[a]->next==NULL)
return -1;

if(tempp[mn]->next==NULL)
{
   while(tempp[mn]->next==NULL)
{
	 mn++;
}
}
	immediate=tempp[mn]->next;
	pid=immediate->pid;
	head=immediate;
	tail=immediate;
	while(tail->next!=head)
	{
		tail=tail->next;
	}
	temp=tail;
	tail=head;
	head=head->next;
	head->previous=tail;
	tail->previous=temp;
	tempp[mn]->next=head;
	if(mn==0)
	{
	 *time=4;
	}
	else if(mn==1)
	{
	 *time=3;
	}
	else if(mn==2)
	{
	*time=2;
	}
	else if(mn==3)
	{
	*time=1;
	}
	mn++;
	return pid;

}

/**
 * Function that returns a boolean 1 True/0 False based on if there are any
 * processes still scheduled
 * @Return 1 if there are processes still scheduled 0 if there are no more
 *		scheduled processes
 */
int hasProcess()
{
	int i;
  int flag=0;
  for(i=0;i<min_p;i++)
  {
     if(tempp[i]->next==NULL)
      flag++;
  }
 if(flag==min_p)
  return 0;
 else
 return 1;
}
