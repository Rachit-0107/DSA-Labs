#include "que.c"

typedef struct Task * task; 
struct Task{
    int Priority; 
    task next; 
    Queue q; 
}; 

typedef struct MultiQue * MultiQ; 
struct MultiQue{
    int size; 
    task head; 
};

MultiQ createMQ(int num); 
MultiQ addMQ(MultiQ mq, struct Task t); 
Queuenode nextMQ(MultiQ mq); 
MultiQ delNextMQ(MultiQ mq); 
int isEmptyMQ(MultiQ mq); 
int sizeMQ(MultiQ mq); 
int sizeMQbyPriority(MultiQ mq, int p); 
Queue getQueueFromMQ(MultiQ mp, int P);