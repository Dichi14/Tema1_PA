#include "player.h"

//stive

int isEmpty(Node*top){
    return  top == NULL;
}

void push(Node**top, Team v){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->team = v;
    newNode->next = *top;
    *top=newNode;
}

Team pop(Node**top){
    
    Node *temp =(*top);
    Team aux = temp->team;
    if(isEmpty(*top)) return aux;
    *top=(*top)->next;
    free(temp);
    return aux;

}

//cozi



int isEmptyq(Queue*q){
    return  (q->front==NULL);
}


Queue* createQueue(){
    Queue *q;
    q=(Queue *)malloc(sizeof(Queue));
    if (q == NULL) return NULL;
    q->front = q->rear=NULL;
    return q;
}


void enQueue (Queue*q,Team v){
    Node* newNode = (Node*)malloc (sizeof(Node));
    newNode->team= v;
    newNode->next=NULL;

    if(q->rear==NULL) q->rear=newNode;
    else{
        (q->rear)->next=newNode;
        (q->rear)=newNode;
    }

    if(q->front==NULL) q->front=q->rear;
}

Team deQueue(Queue*q){
    Node* aux; Team d;

    aux = q->front;
    d=aux->team;
    if(isEmptyq(q)) return d;
    q->front = (q->front)->next;
    if (q->front == NULL) q->rear = NULL;

    free(aux);
    return d;
}