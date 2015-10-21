#ifndef _schedule_h_
#define _schedule_h_


int addProcess(int pid,int priority);
int removeProcess(int pid);
int nextProcess(int *time);
int hasProcess();
void init();
int *time;
int max_p;
int min_p;
int mn;
struct node
{
  int pid;
  int priority;
  struct node *next;
  struct node *previous;
};

struct node *head;
struct node *tail;
struct node *immediate;
struct node *temp;
struct node *tempp[4];
int lp;


#endif
