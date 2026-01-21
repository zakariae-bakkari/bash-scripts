#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
typedef struct
{
   long mtype;
   char msg[10];
} msg;

int main()
{

   key_t cle = ftok("example2", 65);
   if (cle == -1)
   {
      perror("error ftok");
      exit(-1);
   }

   int msgid = msgget(cle, 0666 | IPC_CREAT);
   if (msgid == -1)
   {
      perror("errors msgget");
      exit(-1);
   }
   msg msg1;
   msg1.mtype = getpid();
   strcpy(msg1.msg, "Hello");

   if (msgsnd(msgid, &msg1, strlen(msg1.msg) + 1, 0) == -1)
   {
      perror("errors du msgsnt");
      exit(EXIT_FAILURE);
   }
   printf("%s was sent \n", msg1.msg);

   msg message_recv;
   if (msgrcv(msgid, &message_recv, 10, getpid(), 0) == -1)
   {
      perror("errors du msgrcv");
      exit(EXIT_FAILURE);
   }
   printf("Message reçu : %s\n", message_recv.msg);

   return 0;
}