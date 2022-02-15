#include "multiq.h" 

MultiQ createMQ(int num)
{
    MultiQ mq = (MultiQ) malloc(sizeof(struct MultiQue));
    mq->size = num;
    mq->head = (task)malloc(sizeof(struct Task)); 
    mq->head -> Priority = 1; 
    mq->head -> next = NULL; 
    mq->head->q = newQ();  
    task temp = mq->head; 
    for(int i = 0; i<num-1; i++)
    {
        temp->next = (task) malloc(sizeof(struct Task)); 
        temp = temp->next; 
        temp->next = NULL; 
        temp->Priority = i+2; 
        temp->q = newQ(); 
    }  
    return mq; 
} 

MultiQ addMQ(MultiQ mq, struct Task t)
{
    task temp = mq->head; 
    while(temp != NULL)
    {
        if(temp->Priority == t.Priority)
        {
            temp->q = addQ(temp->q,(t.q).front); 
        } 
        temp = temp->next; 
    } 
    return mq; 
} 

Queuenode nextMQ(MultiQ mq)
{
    task temp = mq->head; 
    task target = mq->head;
    while(temp != NULL)
    {
        if(!isEmptyQ(temp->q))
        {
            if(target->Priority < temp->Priority)
            {
                target = temp; 
            }
        }
        temp = temp->next; 
    } 
    return front(target->q); 
} 

MultiQ delNextMQ(MultiQ mq)
{ 
    task temp = mq->head; 
    task target = mq->head;  
    while(temp->next != NULL)
    {
        if(!isEmptyQ(temp->q))
        {
            if(target->Priority < temp->Priority)
            {
                target = temp; 
            }
        } 
        temp = temp->next; 
    }  
    target->q = delQ(target->q); 
    return mq;
} 

int isEmptyMQ(MultiQ mq)
{
    task temp = mq->head; 
    while(temp->next == NULL)
    {
        if(!isEmptyQ(temp->q))
        {
            return 0; 
        }
    } 
    return 1; 
} 

int sizeMQ(MultiQ mq)
{
    int size=0; 
    task temp = mq->head;   
    while(temp != NULL)
    { 
        size += (temp->q).count;   
        temp = temp -> next;  
    } 
    return size;
} 

int sizeMQbyPriority(MultiQ mq, int p)
{
    task temp = mq->head; 
    while(temp->next != NULL)
    {
        if(temp->Priority == p)
        {
            return (temp->q).count;
        } 
        temp = temp->next; 
    } 
    printf("Given priority not present in MultiQueue\n");
    return 0; 
} 

Queue getQueueFromMQ(MultiQ mq, int p)
{
    task temp = mq->head; 
    while(temp != NULL)
    {
        if(temp->Priority == p)
        {
            return (temp->q);
        } 
        temp = temp->next; 
    } 
    printf("Given priority not present in MultiQueue returning head\n");
    return temp->q; 
}
