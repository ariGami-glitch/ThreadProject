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
char* getinfo(){
    char *temp_msg;
    if(head != NULL){
        temp_msg = head->msgs;
        head = head->next;
    }
    return temp_msg;

}

char *msgq_recv(struct msgq *mq) {
    zem_t *mutex = malloc(sizeof(zem_t));
    zem_t *empty = malloc(sizeof(zem_t));
    zem_t *full = malloc(sizeof(zem_t));
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
    return 10;
}
void msgq_show(struct msgq *mq) {

}
