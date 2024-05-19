#include "player.h"

Node* aloca_node(char* name_team,int nr){
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node)
    {
        printf("Eroare\n");
        return NULL;
    }
    
    strcpy(new_node->team.name_team, name_team);
    new_node->team.number_players = nr;

    new_node->team.player = malloc(sizeof(struct Player)*nr);
    if(!new_node->team.player){
        printf("Eroare\n");
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

void add_player_to_team(Team *team, int player_index,char* firstName,char* secondName, int points) {
    team->player[player_index].firstName = strdup(firstName);
    team->player[player_index].secondName = strdup(secondName);
    team->player[player_index].points = points;
}





int main(int argc, char* argv[]){
    int nr_echipe = 0;
    //Citire argument
    if (argc < 4) {
        printf("Eroare\n");
        return 1;
    }
     // Citire cerinte
    FILE *fin1 = fopen(argv[1], "r");
    if (fin1 == NULL) {
        printf("Eroare\n");
        return 1;
    }
    int cerinte[5];
    for (int i = 0; i < 5; i++) {
        fscanf(fin1, "%d", &cerinte[i]);
    }
    fclose(fin1);
    
    FILE *fin2 = fopen(argv[2], "r");
    if (fin2 == NULL) {
        printf("Eroare\n");
        return 1;
    }
    
    fscanf(fin2, "%d", &nr_echipe);
    fgetc(fin2);

    Node* head = NULL;

    for (int i = 0; i < nr_echipe; i++){
        int nr = 0 ;
        char name_team[100];
        fscanf(fin2,"%d",&nr);
        fgetc(fin2);
        fgets(name_team,100,fin2);

        Node* new = aloca_node(name_team,nr);

        for(int j = 0 ; j < nr ; j++){
            char firstName[100],secondName[100];
            int points;
            fscanf(fin2,"%s %s %d",firstName,secondName,&points);
            add_player_to_team(&new->team,j,firstName,secondName,points);
        }

        new->next = head;
        head = new;
       
     }
    
    fclose(fin2);

    FILE *fout = fopen(argv[3], "w");
    if(fout == NULL){
        printf("erroar\n");
        return 1;
    }

    //CERINTA 2

    if(cerinte[0] == 1 && cerinte[1] == 0){

        Node* current = head;

        while (current != NULL) {
            fprintf(fout,"%s", current->team.name_team);
            current = current->next;
        }
    }
     
   fclose(fout);




    return 0;
}