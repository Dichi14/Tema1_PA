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
    char name_team[100];
    int number_players;
    struct Player *player;
    float score;
    
}Team;

typedef struct Node
{
    Team team;
    struct Node *next;

}Node;
Node* aloca_node(char* name_team,int nr);