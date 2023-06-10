#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
int data = 0;
pthread_mutex_t mutex;
int j = 0;


char *message;

void    routine1()
{
    int i = 0;  
    while (1)
    {   
        pthread_mutex_lock(&mutex);
        i++;
        if (i == 100)
        {
            break;
        }
        pthread_mutex_unlock(&mutex);
        printf("dd\n");
    }
    // return 0;
}
// void    routine2()
// {
//     int i = 0;  
//     while (i < 100)
//     {
//         pthread_mutex_lock(&mutex);
//         data++;
//         printf("ROUTINE 2 %d\n",data);
//         // usleep(5000);
//         i++;
//         if (data == 50)
//         {
//             break;
//         }
//         pthread_mutex_unlock(&mutex);
//     }
//     // return 0;
// }


int main()
{
    pthread_t t1;
    pthread_t t2;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&t1, NULL, (void *)&routine1, NULL);

    pthread_create(&t2, NULL, (void *)&routine1, NULL);
    // usleep(100);
    // pthread_join(t1,NULL);
    // pthread_join(t2,NULL);
    // while (1)
    // {
    //     usleep(500);
    //    printf("mIN THREAD\n");
    // }
    pthread_detach(t2);
    pthread_detach(t1);
    printf("ddd\n");
    // printf("This the main thread\n");
    // printf("%d\n", i);
}