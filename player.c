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
//task  4 BST

BST* newNode(Team data){
    BST* node = (BST*)malloc(sizeof(BST));
    node->team =  data;
    node->left = node->right = NULL;
    return node;
}

BST* inserare(BST* node,Team key){
    if(node == NULL ) return newNode(key);

    if(key.score < node->team.score){
        node->left = inserare(node->left,key);
    }
    else if(key.score > node->team.score){
        node->right= inserare(node->right, key);
    }else if(key.score == node->team.score){
        if(strcmp(node->team.name_team,key.name_team ) > 0){
            node->left = inserare(node->left,key);

        }else{
            node->right = inserare(node->right,key);
        }
    }
        return node;
}

void printBST(BST* root, FILE* file) {
    if (root == NULL) {
        return;
    }

    printBST(root->right, file);
    fprintf(file, "%-34s-  %.2f\r\n", root->team.name_team, root->team.score);
    printBST(root->left, file);
}

