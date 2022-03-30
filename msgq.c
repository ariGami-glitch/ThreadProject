#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "msgq.h"
#include "zemaphore.h"

struct msgq *head;
struct msgq *tail;
int maxmsgqsize;
int currsize = 0;

//initialize the zemophores
zem_t full, empty, mutex;

struct msgq *msgq_init(int num_msgs) {
    struct msgq *m = malloc(sizeof(struct msgq));
    maxmsgqsize = num_msgs;
    head = m;
    tail = m;
    //initialize
    zem_init(&empty, num_msgs);
    zem_init(&full, 0);
    zem_init(&mutex, 1);
    printf("Current size of message queue: %d\n", currsize);
    return m;
}
int msgq_send(struct msgq *mq, char *msg) { //the producer in this case
    int i;
    for(i = 0; i < maxmsgqsize; i++) {
        zem_wait(&empty);
        zem_wait(&mutex);
        mq->msg = strdup(msg);
        tail = mq;
        struct msgq *nm = malloc(sizeof(struct msgq));
        tail->next = nm;
        currsize++;
        zem_post(&mutex);
        zem_post(&full);
    }
    return 1;
}
char *msgq_recv(struct msgq *mq) {
    //char *msg = mq->msgs[mq->current_num];
    //free(mq->msgs[mq->current_num]);
    
    //return msg;
    return "hello";
}
int msgq_len(struct msgq *mq) {
    return 10;
}
void msgq_show(struct msgq *mq) {

}
