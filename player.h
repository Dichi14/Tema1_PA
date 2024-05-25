#include <stdlib.h>
#include <stdio.h>
#include <string.h>



struct Player
{
    char* firstName;
    char* secondName;
    int points;
};

typedef struct Team
{
    char* name_team;
    int number_players;
    struct Player *player;
    float score;

}Team;

typedef struct Node
{
    Team team;
    struct Node *next;

}Node;

struct Q{
    Node *front,*rear;
};

typedef struct Q Queue;



//stive

int isEmpty(Node*top);

void push(Node**top, Team v);

Team pop(Node**top);

//cozi

int isEmptyq(Queue*q);

Queue* createQueue();

void enQueue (Queue*q,Team v);

Team deQueue(Queue*q);

Node* aloca_node(char* name_team,int nr);