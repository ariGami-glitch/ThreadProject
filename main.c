#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "zemaphore.h"
#include "msgq.h"
#include <string.h>

static char *c1[100], *c2[100], *c3[100];

// SEE Labs/GdbLldbLab for more information on lldb - lowlevel debugger

struct msgq *mq;

//
// Main threads
//
char *messages[] = { "msg1", "msg2", "hellomsg", "gustymsg" };

// sends msgs in messages[]
void *promtAndSend(void *arg) {
    for (int i = 0; i < sizeof(messages)/sizeof(char*); i++) {
        char response[80];
        printf("Send? ");
        scanf("%s", response);
        if (response[0] == 'y' || response[0] == 'Y') {
            printf("sending: %s\n", messages[i]);
            msgq_send(mq, messages[i]);
        }
    }
    return NULL;
}

void *promtAndSendWithoutResponse(void *arg) {
    char **new_messages = (char**) arg;
    for (int i = 0; i < sizeof(messages)/sizeof(char*); i++) {
            printf("sending: %s\n", messages[i]);
            msgq_send(mq, messages[i]);
    }
    return NULL;
}


// consume messges in msgq
void *recvMsgs(void *arg) {
    sleep(5);
    int msg_count = msgq_len(mq);

    printf("mq msg_count: %d\n", msg_count);
    for (int i = 0; i < msg_count; i++) {

        char *m = msgq_recv(mq);
        printf("recvMsgs: %s\n", m);
        //mq = mq->next;

//       free(m);
    }
    return NULL;
}

void *passiton(void *arg) {
    int me = (int) arg;
    while (1) {
        sleep(1);
        printf("passiton%d initial msgq_len: %d\n", me, msgq_len(mq));
        char *m = msgq_recv(mq);
        printf("passiton%d: %p %p %s\n", me, &m, m, m);
        printf("passiton%d after recv msgq_len: %d\n", me, msgq_len(mq));
        msgq_send(mq, m);
        printf("passiton%d after send msgq_len: %d\n", me, msgq_len(mq));
        free(m);
    }
    return NULL;
} // done with function

void *passiton2(void *arg) {
    char **array = (char**) arg;

    int count = 0;
    while(msgq_len(mq) != 0) {

        char *m = msgq_recv(mq);

        array[count] = strdup(m);
        count++;


        printf("\nHERE %s", array[count - 1]);
        free(m);
    }
    return NULL;
} // done with function

#define MSGQLEN 100

int main(int argc, char *argv[]) {
    pthread_t p1, p2,p3, p4, p5;
    mq = msgq_init(MSGQLEN);
    char test = '1';
    if (argc == 2)
        test = argv[1][0];
    switch (test) {
      case '1':
        printf("test fill and empty msgq\n");
        pthread_create(&p1, NULL, promtAndSend, NULL);
        pthread_join(p1, NULL);
        printf("msgq_show() after filling for test 1:\n");
        msgq_show(mq);
        pthread_create(&p2, NULL, recvMsgs, NULL);
        pthread_join(p2, NULL);
        printf("msgq_show() after all consumed by test 1:\n");
        msgq_show(mq);
        break;
      case '2':
        printf("test fill msgs and pass it on\n");
        pthread_create(&p1, NULL, promtAndSend, NULL);
        pthread_join(p1, NULL);
        printf("msgq_show() after filling for test 2:\n");
        msgq_show(mq);
        pthread_create(&p1, NULL, passiton, (void *)1);
        pthread_create(&p2, NULL, passiton, (void *)2);
        pthread_join(p1, NULL);
        pthread_join(p2, NULL);
        break;
      case '3':
        printf("test that send_msg blocks when the message queue contains num_msgs\n");
        printf("test fill and empty msgq\n");
        pthread_create(&p1, NULL, promtAndSend, NULL);
        pthread_join(p1, NULL);
        printf("msgq_show() after filling for test 1:\n");
        msgq_show(mq);
        pthread_create(&p2, NULL, promtAndSend, NULL);
        pthread_join(p2, NULL);
        printf("msgq_show() after filling it again:\n");
        msgq_show(mq);
        break;
        
        break;
      case '4':
        printf("test that recv_msg blocks when the message queue is empty\n");
        pthread_create(&p2, NULL, recvMsgs, NULL);
        pthread_join(p2, NULL);
        printf("msgq_show() after all consumed by test 1:\n");
        msgq_show(mq);

        break;
      case '5':
        printf("solving the producer consumer problem");
            printf("test fill msgs and pass it on\n");
            char *messages[] = { "a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa",
                                  "b", "bb", "bbb", "bbbb", "bbbbb", "bbbbbb", "bbbbbbb","bbbbbbbb", "bbbbbbbbb", "bbbbbbbbbb"};
            pthread_create(&p1, NULL, promtAndSendWithoutResponse, NULL);
            pthread_join(p1, NULL);

            pthread_create(&p2, NULL, promtAndSendWithoutResponse, NULL);
            pthread_join(p2, NULL);
            sleep(5);
            printf("msgq_show() after filling for test 2:\n");
            msgq_show(mq);
            pthread_create(&p1, NULL, passiton2, (void *)&c1);
            pthread_create(&p2, NULL, passiton2, (void *)&c2);
            pthread_create(&p3, NULL, passiton2, (void *)&c3);

            pthread_join(p1, NULL);
            pthread_join(p2, NULL);
            pthread_join(p3, NULL);
            printf("\nc1\n\n");
            for (int i = 0; i < sizeof(c1)/sizeof(char*); i++) {
                if(c1[i] == NULL){
                    break;
                }
                printf("\n%s",c1[i] );

            }
            printf("\nc2\n\n");
            for (int i = 0; i < sizeof(c2)/sizeof(char*); i++) {
                if(c2[i] == NULL){
                    break;
                }
                printf("\n%s",c2[i] );
            }
            printf("\nc3\n\n");
            for (int i = 0; i < sizeof(c3)/sizeof(char*); i++) {
                if(c3[i] == NULL){
                    break;
                }
                printf("\n%s",c3[i] );
            }


                //message queue and 5 threads. Two threads are the producers and three are the consumers
        //producer generate 50 messages
        //argument passed to select messages generated
        //consumers save messages in static arrays, one for each consumer
        break;
      default:
        printf("invalid test selection!\n");
        break;
    }
    return 0;
}

