#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "zemaphore.h"
#include "msgq.h"
#include <string.h>
struct msgq *tail;
int maxmsgqsize;
int currsize = 0;

//initialize the zemophores
zem_t full, empty, mutex;

struct msgq *msgq_init(int num_msgs) {
    struct msgq *m = malloc(sizeof(struct msgq));
    maxmsgqsize = num_msgs;
    tail = m;
    //initialize
    zem_init(&empty, num_msgs);
    zem_init(&full, 0);
    zem_init(&mutex, 1);
    //printf("Current size of message queue: %d\n", currsize);




    /*The new code*/
    zem_init(&m->empty, num_msgs);
    zem_init(&m->full, 0);
    zem_init(&m->mutex, 1);
    m->num_msgs = 0;
    m->max_msgs = num_msgs;
    m->head = m->tail = 0;
    
    return m;
}
int msgq_send(struct msgq *mq, char *msg) { //the producer in this case
    zem_wait(&empty);
    zem_wait(&mutex);
    struct msg *m = malloc(sizeof(struct msg));
    m->msg = strdup(msg);
    printf("msg: %s\n", m->msg);
    if(tail->msg == NULL){
        tail->msg = strdup(msg);
    }
    else{
        struct msgq *nm = malloc(sizeof(struct msgq));
        nm->msg = strdup(msg);
        tail->next = nm;
        tail = tail->next;
    }

    zem_post(&mutex);
    zem_post(&full);
    


    /*New Code*/
    zem_wait(&mq->empty);
    zem_wait(&mq->mutex);
    //create msg struct
    //call method and pass in the mq and the msg
    mput(mq, msg);
    printf("msg: %s", mq->tail->msg);
    zem_post(&mq->mutex);
    zem_post(&mq->full);

    return 1;
}

void mput(struct msgq *mq, char *msg) {
    struct msg *m = malloc(sizeof(struct msg));
    m->msg = strdup(msg);
    if(mq->num_msgs < mq->max_msgs) {
        //head is null
        if(mq->head == NULL) {
            mq->head = m;
            mq->tail = mq->head;
        }
        else {
            mq->tail->next = m;
            mq->tail = mq->tail->next;
        }
        mq->num_msgs++;
    }
}

char* getinfo(struct msgq *mq){
    char *temp_msg;
    if(mq != NULL) {
        temp_msg = mq->msg;
        //free(head->msg);
        //mq = mq->next;
    }


    return temp_msg;

}

char *msgq_recv(struct msgq *mq) {
    zem_wait(&full); // Line C0 (NEW LINE)
    zem_wait(&mutex); // Line C1
    //char* tmp = getinfo(mq); // Line C2
    //printf("%s\n", mq->msg);
    char *tmp;
    tmp = mq->msg;
    mq = mq->next;
    zem_post(&mutex);
    zem_post(&empty);
   // printf("%s\n", mq->msg);


    return tmp;
}


int msgq_len(struct msgq *mq) {
    int count = 0;
    struct msgq *temp_mq = mq;
    do{
        count = count + 1;
        temp_mq = temp_mq->next;

    }while(temp_mq != NULL);
    

    return count;
}
void msgq_show(struct msgq *mq) {
    struct msgq *temp_mq = mq;
    /*do{
        printf("%s\n", temp_mq->msg);
        temp_mq = temp_mq->next;
    }while(temp_mq != NULL);*/
    while(temp_mq != NULL) {
        printf("%s\n", temp_mq->msg);
        temp_mq = temp_mq->next;
        
    }
}
