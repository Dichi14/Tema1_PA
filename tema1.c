
#include "player.h"



void eliminareSpatii(char* str)
{
    int idx = strlen(str) - 1;
    while (strchr(" \t\n\r\v\f", str[idx]) != NULL)
        idx--;

    str[idx + 1] = 0;
    
}


Node* aloca_node(char* name_team,int nr){
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node)
    {
        printf("Eroare\n");
        return NULL;
    }

    new_node->team.name_team = (char*)malloc((strlen(name_team)+1)*sizeof(char));
    
    
    strcpy(new_node->team.name_team, name_team);
    eliminareSpatii(new_node->team.name_team);
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

void insertNode(Node** head , Team echipa )
{
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->team = echipa;
    newNode->next = NULL;

    if(*head == NULL ){
        *head = newNode;
    }else{
        newNode->next= *head;
        *head = newNode;
    }
}


//CERINTA 2
int puterea2(int echipe){ 
    int n = 1;
    while (n*2 <= echipe)
    {
        n = n*2; 
    }
    return n;
}


float find_min(Node* a){
   
    if(a == NULL) return -1;
    Node* i = a;
    float minim = i->team.score;
    while(i != NULL){
        if(i->team.score < minim) minim = i->team.score;

        i = i->next;



    }
    return minim;
}

void deleteNode(Node** head , float point) {
    if(*head == NULL) return;

    Node* headcopy = *head ;
    if(headcopy->team.score == point){ *head = (*head)->next;
    free(headcopy);
    return;
    }
    Node*prev = *head;
    while (headcopy!= NULL)
    {
        if(headcopy->team.score != point){
            prev=headcopy;
            headcopy = headcopy->next;
        }
        else{
            prev->next = headcopy->next;
            free(headcopy);
            return;
        }
    }
    
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
        while (fgetc(fin2)==' ' );
        fseek(fin2,-1,SEEK_CUR);
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
            fprintf(fout,"%s\n", current->team.name_team);
            current = current->next;
        }
    }
     
    if (cerinte[0]== 1 && cerinte[1] == 1){
        int n = puterea2(nr_echipe);
  
        Node* current = head;

        while (current != NULL)
        {
            for(int i = 0 ; i < current->team.number_players; i++)
            {
                current->team.score += current->team.player[i].points;
            }

            current->team.score /= current->team.number_players;
            current = current->next;
        }

   
    for(int i = nr_echipe ; i > n ; i--){
        float nr_minimpct = find_min(head);
        deleteNode(&head,nr_minimpct);

    }

    current = head;

        while (current != NULL) {
            fprintf(fout,"%s\n", current->team.name_team);
            current = current->next;
        }   

    }

    //cerinta 3
     Node* lista_8 = NULL;

      if(cerinte[2] == 1){
      Queue* q;
      q = createQueue();
     
      Node *winners = NULL ;
      Node *losers = NULL;

      Team echipa1;
      Team echipa2;
        
      for (Node* i = head ; i != NULL ; i = i->next)
      {
            enQueue(q,i->team);

      }
      
        int echipe_active = puterea2(nr_echipe);

        int nr_runda = 1;
      while (echipe_active > 1)
      {
     
        fprintf(fout,"\n--- ROUND NO:%d\n",nr_runda);
    
        
        while (!isEmptyq(q))
        {   
            echipa1 = deQueue(q);
            echipa2 = deQueue(q);

            fprintf(fout,"%-33s-%33s\n", echipa1.name_team , echipa2.name_team);
            
            if(echipa1.score > echipa2.score){
                (echipa1.score)++;
                push(&winners, echipa1);
                push(&losers, echipa2);
            }
            else {
                (echipa2.score)++;
                push(&winners, echipa2);
                push(&losers, echipa1);
            }
        }
        fprintf(fout,"\nWINNERS OF ROUND NO:%d\n",nr_runda);
        
        while (!isEmpty(winners))
        {
            echipa1 = pop(&winners);
            if(echipe_active == 16){
                insertNode(&lista_8, echipa1);
            }
           
            fprintf(fout,"%-34s-  %.2f\n",echipa1.name_team,echipa1.score);
            enQueue(q,echipa1);
        }
        
        echipe_active/=2;
        nr_runda++;

        
      }
      

    }   


     
     if (cerinte[3] == 1) {
        BST* root = NULL;
        Node* current = lista_8;
        int count = 0;
        while (current != NULL && count < 8) {
            root = inserare(root, current->team);
            current = current->next;
            count++;
        }
        fprintf(fout, "\r\nTOP 8 TEAMS:\r\n");
        printBST(root, fout);
    }
    fclose(fout);

    

    return 0;
}