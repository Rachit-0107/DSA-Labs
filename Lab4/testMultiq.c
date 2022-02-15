#include <stdlib.h> 
#include <time.h> 
#include <unistd.h> 
#include <sys/time.h> 
#include "multiq.c"

MultiQ loadData(FILE * fp);
MultiQ testDel(int num, MultiQ mq);

int main()
{
    struct timeval t1, t2,t3,t4;
    double elapsedTimeLoad, elapsedTimeDel; 
    MultiQ mq = (MultiQ)malloc(sizeof(struct MultiQue)); 

    FILE * fpa = fopen("input10.txt", "r"); 
    // start timer
    gettimeofday(&t1, NULL);
    // do something or call a function 
    mq = loadData(fpa); 
    // stop timer
    gettimeofday(&t2, NULL);
    // compute and print the elapsed time in millisec
    elapsedTimeLoad = (t2.tv_sec - t1.tv_sec) * 1000.0;             // sec to ms
    elapsedTimeLoad += (t2.tv_usec - t1.tv_usec) / 1000.0;          // us to ms
    printf("Total time is %lf ms for the file loadData operation.\n", elapsedTimeLoad);  

    int num;
    printf("Please enter the number of delete operations you wish to execute\n"); 
    scanf("%d", &num);

    // start timer
    gettimeofday(&t3, NULL);
    // do something or call a function 
    mq = testDel(num, mq); 
    // stop timer
    gettimeofday(&t4, NULL);
    // compute and print the elapsed time in millisec
    elapsedTimeDel = (t4.tv_sec - t3.tv_sec) * 1000.0;            // sec to ms
    elapsedTimeDel += (t4.tv_usec - t3.tv_usec) / 1000.0;         // us to ms
    printf("Total time is %lf ms.\n", elapsedTimeDel); 

    FILE * fp; 
    if( access("observations.xlsx", F_OK ) == 0 ) 
    {
        // file exists
        fp = fopen("observations.xlsx", "a+"); 
        fprintf(fp, "%lf,%d,%lf\n", elapsedTimeLoad, num, elapsedTimeDel);
        fclose(fp);
    } 
    else 
    {
        // file doesn't exist 
        fp = fopen("observations.xlsx", "w+"); 
        fprintf(fp, "Time to Load into MQ, Number of Delete Operations, Time to perform delete Operations\n"); 
        fclose(fp);
        fp = fopen("observations.xlsx", "a+");
        fprintf(fp, "%lf,%d,%lf\n", elapsedTimeLoad, num, elapsedTimeDel); 
        fclose(fp); 
    } 
    return 0; 
} 

MultiQ loadData(FILE * fp)
{ 
    MultiQ mq = createMQ(10); 
	int a,b; 
	struct Task t; 
	while(!feof(fp)){
		fscanf(fp,"%d,%d",&a,&b);
		fgetc(fp); 
		t.Priority = b; 
        Queuenode temp = (Queuenode) malloc(sizeof(struct queuenode)); 
        t.q = addQ(t.q,temp);
		mq = addMQ(mq,t);
	}; 
    fclose(fp); 
    return mq; 
}

MultiQ testDel(int num, MultiQ mq) 
{ 
    for(int i =0; i<num; i++)
    {
        mq = delNextMQ(mq); 
    } 
    // else
    // {
    //     for(int i =0; i<sizeMQ(mq); i++)
    //     {
    //         mq = delNextMQ(mq); 
    //     }
    // }
    return mq; 
}
