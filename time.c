#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>


long long gettime()
{
    struct timeval crrent;
    gettimeofday(&crrent,NULL); 
    long long start_time = (crrent.tv_sec * 1000) + (crrent.tv_usec / 1000);
    return start_time;
}


void    1(time_t time_stamps)
{
    long long current = gettime();
    while (gettime()  - current < time_stamps)
    {
        usleep(50);
    }
    
}

int main()
{
    
    long long start = gettime();
    while (1)
    {
        printf("After some delay %lld\n",gettime() - start);
        my_own_usleep(250);
    }
}