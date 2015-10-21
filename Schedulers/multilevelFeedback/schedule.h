#ifndef _schedule_h_
#define _schedule_h_


void init();
int addProcess(int pid, int priority);
int removeProcess(int pid);
int nextProcess(int *time);
void age();
int hasProcess();
int *time;
int max_p;
int min_p;
int mn;
struct node
{
  int pid;
  int age1;
  int priority;
  struct node *next;
  struct node *previous;
};

struct node *head;
struct node *tail;
struct node *immediate;
struct node *temp;
struct node *tempp[3];
int lp;

#endif
