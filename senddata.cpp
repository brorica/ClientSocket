#include "senddata.h"
#include <pthread.h>

static const int BUFFER_SIZE = 256;
void *receive_data(void *sd);

void *receive_data(void *sd)
{
    ssize_t res;
    char get_response[BUFFER_SIZE];
    // read data
    while(1)
    {
        memset(get_response,'\0',BUFFER_SIZE);
        if((res = recv(*(int*)sd,get_response,BUFFER_SIZE-1,0)) == -1)
        {
            cout << errno;
            cout << strerror(errno) << endl;
        }
        else
        {
            if(strlen(get_response)>0)
            {
                 get_response[strlen(get_response)] = '\0';
                 cout << get_response;
            }
        }
    }
}


    
int senddata(int sd)
{
    char send_request[BUFFER_SIZE];
    pthread_t thread;
    int thread_id;
    int thread_status;

    thread_id = pthread_create(&thread,NULL,receive_data,(void *)&sd);
    if(thread_id <0)
    {
        cout << "pthread error!" << endl;
        exit(0);
    }

    while(1)
    {
        fgets(send_request,BUFFER_SIZE,stdin);
        // send data
        if((send(sd,send_request,BUFFER_SIZE-1,0)) == -1)
        {
            cout << errno;
            cout << strerror(errno) << endl;
            return 0;
        }
        if(strncmp(send_request,"quit",4) == 0)
        {
            cout << "diconnected" << endl;
            exit(0);
        }
    }
    pthread_join(thread,(void**)thread_status);

    return 0;
}
