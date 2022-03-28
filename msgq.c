#include <stdlib.h>
#include <stdio.h>
#include "msgq.h"
#include <pthread.h>
#include "zemaphore.h"

struct msgq *msgq_init(int num_msgs) {
    struct msgq *m = malloc(sizeof(struct msgq));
    return m;
}
int msgq_send(struct msgq *mq, char *msg) {

}
char *msgq_recv(struct msgq *mq) {

}
int msgq_len(struct msgq *mq) {

}
void msgq_show(struct msgq *mq) {

}
