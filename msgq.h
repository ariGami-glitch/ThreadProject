#include <pthread.h> 

typedef struct msg {
    char *msg;
    struct msg *next;
} msg;
typedef struct msgq {
    char *msg;
    struct msgq *next;
    struct msg *m;
    
    zem_t empty;
    zem_t full;
    zem_t mutex;
    struct msg *head;
    struct msg *tail;
    int max_msgs;
    int num_msgs;
} msgq;

struct msgq *msgq_init(int num_msgs);
int msgq_send(struct msgq *mq, char *msg);
char *msgq_recv(struct msgq *mq);
int msgq_len(struct msgq *mq);
void msgq_show(struct msgq *mq);
