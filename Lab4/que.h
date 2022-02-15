#include<stdio.h> 

typedef struct queuenode * Queuenode; 
struct queuenode{
    int ele; 
    Queuenode next; 
};

typedef struct{
    int count; 
    Queuenode front;
    Queuenode rear; 
}Queue; 

Queue newQ(); 
int isEmptyQ(Queue q); 
Queue delQ(Queue q); 
Queuenode front(Queue q); 
Queue addQ(Queue q, Queuenode node); 
int lengthQ(Queue q); 