#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#define MAX 10

struct mesg_buffer {
	long mesg_type;
    int  first_message;
	char mesg_text[100];
    char recieverId[100];
} message;

// A normal C function that is executed as a thread
// when its name is specified in pthread_create()
void *myThreadFun(void *vargp)
{
	int msgid;

	// msgget creates a message queue
	// and returns identifier
	msgid = msgget(atoi(message.recieverId), 0666 | IPC_CREAT);
	message.mesg_type = 1;

	// msgsnd to send message
	msgsnd(msgid, &message, sizeof(message), 0);

	// display the message
	printf("Data send from thread : %s and to %s \n", message.mesg_text,message.recieverId);


	return NULL;
}

int main()
{
	
    
    
    while(1){
        int msgid;
        msgid = msgget(1, 0666 | IPC_CREAT);
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        if(message.first_message ==0){
            

        }
        else{
            pthread_t thread_id;
	        
	        pthread_create(&thread_id, NULL, myThreadFun, NULL);
            pthread_join(thread_id, NULL);
         
        }
       // printf("Data Received is : %s \n",message.mesg_text);
       //sleep(3);
        
        msgctl(msgid, IPC_RMID, NULL);




        int keyid = atoi(message.mesg_text);
      //  printf("%d", keyid);


        
        
    }


}

