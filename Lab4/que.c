#include "que.h"

Queue newQ()
{
    Queue q; 
    q.front = NULL; 
    q.rear = NULL; 
    q.count =0; 
    return q; 
}

int isEmptyQ(Queue q)
{
    if(q.front == NULL && q.rear == NULL)
    {
        return 0; 
    }
    else 
    {
        return 1; 
    }
}

Queue delQ(Queue q)
{
    Queue q1; 
    if(q.rear != q.front || (isEmptyQ(q) == 1))
    { 
        q1.rear = q.rear;  
        q1.front = q.front -> next; 
        q1.count = q.count-1;   
    } 
    else
    {
        q1.front = NULL; 
        q1.rear = NULL; 
        q1.count = 0; 
    }
    return q1; 
}

Queuenode front(Queue q)
{
    return q.front; 
} 

Queue addQ(Queue q, Queuenode node)
{
    Queue q1; 
    q1.front = q.front; 
    q1.count = q.count+1; 
    q1.rear = node;  
    return q1; 
} 

int lengthQ(Queue q)
{
    return q.count; 
}