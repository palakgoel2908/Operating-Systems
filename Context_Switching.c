#include<stdio.h>
#include<stdlib.h>
#define STACK_SIZE 1024*1024

struct thread{ //Representation of Thread COntrol Block
  unsigned char* stack_pointer;
  void (*initial_function)(void*);//This is a variable that has void * as an argument
  void* initial_argument; //This is kind of generic variable for defining intitial functions for threads
};

typedef struct thread TCB;
void thread_switch(TCB * old, TCB * new);
void thread_start(TCB * old, TCB * new);
void yield();
int shared_var=10;

void increment(void *ptr){
printf("New Thread Started\n");
   int x=0;
   x=x+1;
   shared_var++; 
   printf("X is %d, shared var is %d \n",x,shared_var);
   yield();
   printf("New Thread Restarted and  shared var %d\n",shared_var);
   printf("New Thread Ended shared var %d\n",shared_var);
}

TCB * current_thread;//struct thread * current_thread
TCB * inactive_thread;

void thread_wrap(){
  current_thread->initial_function(current_thread->initial_argument); 
  yield();
}

int main(int argc, char **argv){
  //int shared_var=10;
 printf("Main thread started shared variable is %d\n",shared_var);
 TCB * threads[5];
 current_thread=(TCB *)malloc(sizeof(TCB *));//Allocate memory for the current thread
 int *random_ptr=(int *)malloc(sizeof(int *));
 *random_ptr=100;
 current_thread->initial_function=increment;//Initialize to a function of type void (void *)
 current_thread->initial_argument=random_ptr;//Initialize to pointer 
 current_thread->stack_pointer=(unsigned char *)malloc(STACK_SIZE)+STACK_SIZE;//Allocate memory for stack and move the pointer to end of the stack so that the stack will grow upwards.
 //current_thread->initial_function(current_thread->initial_argument);
 //printf("%d",current_thread->stack_pointer);
 inactive_thread=(TCB *) malloc(sizeof(TCB *));
 thread_start(inactive_thread,current_thread);
 printf("Main thread restarted shared var is %d\n",shared_var);  
 //yield();
 printf("Main thread ended and shared_var is %d\n",shared_var);
 return 0;
}

 void yield() {
   /* TCB * temp = current_thread;
    current_thread = inactive_thread;
    inactive_thread = temp;*/
    thread_switch(current_thread, inactive_thread);
  }
