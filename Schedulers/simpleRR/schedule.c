/*
*
*
* Akshay Deo 006939024
*/

#include "schedule.h"
#include <stdlib.h>
#include <stdio.h>

struct node
{
  int pid;
  struct node *next;
  struct node *previous;
};

struct node *head;
struct node *tail;
struct node *immediate;

/**
 * Function to initialize any global variables for the scheduler.
 */
void init()
{
	head = (struct node*) malloc( sizeof(struct node));
	immediate=(struct node*) malloc( sizeof(struct node));
	head->pid=-111;
	tail=(struct node*) malloc( sizeof(struct node));
	tail=head;
}

/**
 * Function to add a process to the scheduler
 * @Param pid - the ID for the process/thread to be added to the
 *      scheduler queue
 * @return true/false response for if the addition was successful
 */
int addProcess(int pid)
{
	if(head->pid==-111)
  {
    head->pid=pid;
    head->next=head;
		head->previous=head;
    tail=head;
    immediate=tail;
    return 1;
  }
  else if(immediate==tail)
  {
    tail->next=(struct node*) malloc( sizeof(struct node));
		tail->previous=(struct node*) malloc( sizeof(struct node));
    tail=tail->next;
		immediate->next=tail;
		tail->previous=immediate;
    tail->pid=pid;
    tail->next=head;
    immediate=tail;
    return 1;
  }
  else
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
	struct node *temp;
	immediate=head;
	if(immediate!=NULL)
	{
  while(immediate!=NULL)
	{
		if(immediate->pid==pid)
		{
        break;
		}
    immediate=immediate->next;

	}
	if(immediate==head && head->next!=head)
	{
    tail=tail->next;
    head=head->next;
		head->previous=tail;
    immediate->next=NULL;
    immediate->previous=NULL;
		free(immediate);
	}
  else if(immediate==head && head->next==head)
	{
     head=NULL;
     free(head);
	}
	else if(immediate==tail)
	{
     tail=tail->previous;
		 tail->next=head;
     immediate->next=NULL;
     immediate->previous=NULL;
     free(immediate);
	}
	else
	{
		  temp=immediate->previous;
      temp->next=immediate->next;
			immediate->next->previous=temp;
      immediate->next=NULL;
      immediate->previous=NULL;
      free(immediate);
	}
return 1;
}
else
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
  *time=4;
  if(head!=NULL)
  {
     int pid;
     pid=head->pid;
     immediate=head;
     tail->next=immediate;
     immediate->previous=tail;
     tail=immediate;
     head=head->next;
     return pid;
  }
  else
  {
    return -1;
  }
}

/**
 * Function that returns a boolean 1 True/0 False based on if there are any
 * processes still scheduled
 * @Return 1 if there are processes still scheduled 0 if there are no more
 *		scheduled processes
 */
int hasProcess()
{
  if(head!=NULL)
  {
    return 1;
  }
  else
  {

	  return 0;
  }
}
