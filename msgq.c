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
char* getinfo(){
    char *temp_msg;
    if(head != NULL){
        temp_msg = head->msgs;
        head = head->next;
    }
    return temp_msg;

}

char *msgq_recv(struct msgq *mq) {
    zem_init(lock, 0);
    zem_wait(full); // Line C0 (NEW LINE)
    zem_wait(mutex); // Line C1
    char* tmp = getinfo(); // Line C2
    zem_post(mutex);
    zem_post(empty);
    printf("%s\n", tmp);
    return tmp;
}


int msgq_len(struct msgq *mq) {
    do(mq == NULL)
    

    return currsize;
}
void msgq_show(struct msgq *mq) {

}
