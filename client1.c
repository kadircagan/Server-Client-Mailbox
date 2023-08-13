#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#define MAX 10
int thisId;


struct mesg_buffer {
	long mesg_type;
    int  first_message;
	char mesg_text[100];
    char recieverId[100];
} message;

int resetStr(){
    strcpy(message.mesg_text,"");
    strcpy(message.recieverId,"");
    return 0;
}

int main(int argc, char** argv)
{
	int msgid;

	// msgget creates a message queue
	// and returns identifier
	msgid = msgget(1, 0666 | IPC_CREAT);
	message.mesg_type = 1;
    int  first_message=0;

	//printf("Write Data : ");
    strcpy(message.mesg_text,argv[1]);
	msgsnd(msgid, &message, sizeof(message), 0);

    thisId = atoi(message.mesg_text);
	//printf("Data send is : %s \n", message.mesg_text);
    resetStr();
while (1)
{
    char* doMailbox;
    printf("If you want to check your mails press 0. If you want to send a mail press 1 \n");

    fgets(doMailbox,MAX,stdin);

    int doMailBoxint = atoi(doMailbox);
    if(doMailBoxint==0){

        int msgid;
        int tempThisID=thisId;
        
        msgid = msgget(thisId, 0666 | IPC_CREAT);
        thisId=tempThisID;
        
        if(msgrcv(msgid, &message, sizeof(message), 1, IPC_NOWAIT)==-1){
            printf("There are no mail\n");
        }else{
            printf("Data Received is : %s \n",
                        message.mesg_text);

        }
        
        thisId=tempThisID;

        msgctl(msgid, IPC_RMID, NULL);
        resetStr();

    }
    if(doMailBoxint==1){
        printf("please write id of other client: ");
        fgets(message.recieverId,MAX,stdin);
        printf("\n");

        printf("please write your message: ");
        fgets(message.mesg_text,80,stdin);
        printf("\n");
        int msgid;

        msgid = msgget(1, 0666 | IPC_CREAT);
        message.mesg_type = 1;
        message.first_message=1;

        msgsnd(msgid, &message, sizeof(message), 0);

        printf("Data send is : %s \n", message.mesg_text);

     //   printf("%s  %s" ,message.recieverId,message.mesg_text);

    }
    doMailBoxint=2;


}

	return 0;
}



    //strcpy(message.mesg_text,"argv[1]");
