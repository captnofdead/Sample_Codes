#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


#define MAXSIZE 10000
int a[MAXSIZE];
int currthread = 0;
int n;


struct dataThread
{
    int Skey;
    int Kidx;
};
    
int initt()
{
    for(int i=0;i<MAXSIZE;i++)
    {
        a[i] = i;
    }
    printf("Enter the Key to be Searched(Key should be less than 10000)\n");
    scanf("%d", &n);
    return 1;
}       

void *threadLinearSearch( void *thdargs)
{
    struct dataThread *data;
    data = (struct dataThread *) thdargs;
    int start = (MAXSIZE/2)*currthread;
    int end = MAXSIZE/2 + start;
    currthread++;
    for(int i=start; i<=end; i++)
    {
        if(a[i] == data->Skey)
        {
            data->Kidx = i;
            pthread_exit(NULL);
        }
    }
    data->Kidx = -1;
    pthread_exit(NULL);
}


int main()
{
    initt();
    pthread_t lthread, rthread;
    struct dataThread LeThd, RiThd;
    LeThd.Skey = n;
    RiThd.Skey = n;
    int temp;
    temp = pthread_create(&lthread, NULL, threadLinearSearch, (void*) &LeThd);
    temp = pthread_create(&rthread, NULL, threadLinearSearch, (void*) &RiThd);
    pthread_join(lthread, NULL);
    pthread_join(rthread, NULL);
    
    if(LeThd.Kidx!=-1)
    {
        printf("The index of the key %d is %d\n", n, LeThd.Kidx);
        pthread_exit(NULL);
    }
    if(RiThd.Kidx!=-1)
    {
        printf("The index of the key %d is %d\n", n, RiThd.Kidx);
        pthread_exit(NULL);
    }
    printf("Key not found\n");
    pthread_exit(NULL);
    return 0;
}