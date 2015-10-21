/*
*
*
* Akshay Deo 006939024
*/


#include "schedule.h"
#include <stdlib.h>
#include <stdio.h>

struct node{
  int pid;
  struct node *next;
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
    head->next=NULL;
    tail=head;
    immediate=tail;
    return 1;
  }
  else if(immediate==tail)
  {
    tail->next=(struct node*) malloc( sizeof(struct node));
    tail=tail->next;
    tail->pid=pid;
    tail->next=NULL;
    immediate=tail;
    return 1;
  }
  else
    return 0;
}

/**
 * Function to get the next process from the scheduler
 *
 * @Return returns the thread id of the next process that should be
 *      executed, returns -1 if there are no processes
 */
int nextProcess()
{
  int pid;
  immediate=head;
  if(head!=NULL)
  {
    pid = head->pid;
    head=head->next;
    free(immediate);
    immediate=head;
    return pid;
  }
  else
	return -1;
}

/**
 * Function that returns a boolean 1 True/0 False based on if there are any
 * processes still scheduled
 * @Return 1 if there are processes still scheduled 0 if there are no more
 *		scheduled processes
 */
int hasProcess()
{
  immediate=head;
  if(immediate!=NULL)
  {
    return 1;
  }
  else
	return 0;
}
