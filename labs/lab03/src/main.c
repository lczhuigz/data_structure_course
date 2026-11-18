#include <stdio.h>
#include <stdlib.h>


#define elemtype int


typedef struct _queuenode{
    int data;
    struct _queuenode *next;
}queuenode;

typedef struct{
    queuenode *front;
    queuenode *rear;
}linkqueue;

// 初始化队列
void init_queue(linkqueue *Q){
    Q->front = Q->rear = (queuenode *)malloc(sizeof(queuenode));
    if (!Q->front) {
        printf("内存分配失败！\n");
        exit(1);
    }
    Q->front->next = NULL;
    printf("队列初始化成功。\n");
}
// 入队
void en_queue(linkqueue *Q, elemtype x){
    queuenode *s = (queuenode *)malloc(sizeof(queuenode));
    if (!s) {
        printf("内存分配失败！\n");
        return;
    }
    s->data = x;
    s->next = NULL;
    
    Q->rear->next = s;
    Q->rear = s;
    printf("元素 %d 入队成功。\n", x);
}
// 出队
int de_queue(linkqueue *Q, elemtype *x){
    if (Q->front == Q->rear) {
        printf("队列为空，出队失败。\n");
        return 0;
    }
    
    queuenode *p = Q->front->next;
    *x = p->data;
    Q->front->next = p->next;
    
    if (Q->rear == p) {
        Q->rear = Q->front;
    }
    
    free(p);
    return 1;
}
// 销毁队列
void destroy_queue(linkqueue *Q){
    queuenode *p = Q->front;
    while (p != NULL) {
        queuenode *temp = p;
        p = p->next;
        free(temp);
    }
    Q->front = Q->rear = NULL;
    printf("队列已销毁。\n");
}


int main(int argc, char **argv){

    linkqueue Q;
    elemtype e;
    
    init_queue(&Q);
    
    en_queue(&Q, 10);
    en_queue(&Q, 20);
    en_queue(&Q, 30);
    
    if (de_queue(&Q, &e)){
        printf("出队元素为: %d\n", e);
    }
    if (de_queue(&Q, &e)){
        printf("出队元素为: %d\n", e);
    }
    
    en_queue(&Q, 40);
    
    while (de_queue(&Q, &e)){
        printf("出队元素为: %d\n", e);
    }
    
    destroy_queue(&Q);
    
    return 0;
}