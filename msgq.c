#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "msgq.h"
#include "zemaphore.h"

struct msgq *head;
struct msgq *tail;
int maxmsgqsize;
int currsize = 0;
struct msgq *msgq_init(int num_msgs) {
    struct msgq *m = malloc(sizeof(struct msgq));
    head = m;
    tail = m;
    printf("Current size of message queue: %d\n", currsize);
    return m;
}
int msgq_send(struct msgq *mq, char *msg) { //the producer in this case

    
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
