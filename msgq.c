#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "msgq.h"
//#include "zemaphore.h"

struct msgq *msgq_init(int num_msgs) {
    struct msgq *m = malloc(sizeof(struct msgq));
	m->num_msgs = num_msgs;
    //mq->msgs = calloc(num_msgs);
    return m;
}
int msgq_send(struct msgq *mq, char *msg) {
    
    return 10;
}
char *msgq_recv(struct msgq *mq) {
    return "lol";
}
int msgq_len(struct msgq *mq) {
    return 10;
}
void msgq_show(struct msgq *mq) {

}
