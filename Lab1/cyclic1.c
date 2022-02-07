#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <unistd.h> 
#include <sys/time.h>
#include "cycle.h" 

int Heap; 


LIST createList(int N); 
LIST createCycle(LIST Ls); 

int main()
{
    srand(time(0)); 
    struct timeval t1, t2;
    double elapsedTime;
    int N, checkCycle; 

    N = rand()%1000000+1000000; 
    printf("%d\n",N);

    LIST Ls = createList(N); 
    Ls = createCycle(Ls); 

    gettimeofday(&t1, NULL);
    checkCycle = testCyclic(Ls); 
    gettimeofday(&t2, NULL); 

    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms 
    printf("Total time in ms: %lf\n", elapsedTime); 

    if (checkCycle)
    {
        printf("The Linked List is a cycle\n"); 
    } 
    else
    {
        printf("The Linked List is not a cycle\n"); 
    } 

    FILE * fp; 
    if( access("observations.xlsx", F_OK ) == 0 ) 
    {
        // file exists
        fp = fopen("observations.xlsx", "a+");
        fprintf(fp, "%d, %lf , %d\n",N, elapsedTime, Heap); 
        fclose(fp);
    } 
    else 
    {
        // file doesn't exist 
        fp = fopen("observations.xlsx", "w+"); 
        fprintf(fp, " N , Time to execute , Heap Size used\n"); 
        fclose(fp);
        fp = fopen("observations.xlsx", "a+");
        fprintf(fp, "%d, %lf , %d\n",N, elapsedTime, Heap);
    }

    return 0; 
} 

LIST createList(int N)
{
    LIST myList; 
    myList = (LIST) malloc(sizeof(struct linked_list)); 
    Heap += sizeof(struct linked_list); 
    myList->count = N; 
    myList -> head = NULL; 
    NODE myNode; 
    myNode = (NODE) malloc(sizeof(struct node)); 
    Heap += sizeof(struct node);  
    myNode -> ele = 50; 
    myNode -> next = NULL; 
    myList -> head = myNode;
    NODE temp; 
    temp = myList -> head; 
    for(int i = 1; i<N; i++)
    {
        NODE myNode_in; 
        myNode_in = (NODE) malloc(sizeof(struct node)); 
        Heap += sizeof(struct node); 
        myNode_in -> ele = rand()%100; 
        myNode_in -> next = NULL; 
        temp->next = myNode_in; // Link previous node with newNode 
        temp = temp->next;  

    } 
    return myList; 
} 

LIST createCycle(LIST Ls)
{
    int toss; 
    toss = rand()%2; // coin toss to decide to make circular or not
    if(toss)
    {
        printf("Linked List is left as Linear\n"); 
    } 
    else
    {
        printf("Linked List is converted to circular\n"); 
        int r = rand()%10 + 10; 
        NODE temp_r, temp_end; 
        temp_r = Ls -> head; 
        temp_end = Ls -> head; 
        for(int i = 0; i < r ; i++)
        {
            temp_r = temp_r -> next; 
        } 
        while(temp_end->next != NULL)
        {
            temp_end = temp_end -> next; 
        } 
        temp_end->next = temp_r; // making the linked list circular from the rth node
    } 
    return Ls; 
}

int testCyclic(LIST Ls)
{
    NODE hare, tort; 
    hare = Ls -> head; 
    tort = Ls -> head; 
    while (tort && hare && hare->next)
    {
        tort = tort->next;
        hare = hare->next->next;
        if (hare == tort)
        {
            return 1;
        }
    }
    return 0;
}