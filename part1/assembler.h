#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 17
#define oprand_SIZE 3
#define upcode_SIZE 2

typedef struct {
    char oprand[oprand_SIZE]; //key
    char upcode[upcode_SIZE];
} symboliclabels;

symboliclabels* SymTable[TABLE_SIZE]; 
//FILE* InFile = fopen("assemblycode.txt", "r");
//FILE* OutFIle = fopen("output.txt", "w");

int hash(char *s){
    //a better one with less colisions
    //source stackoverflow
    int i;
    for (i = 0; *s != '\0'; s++)
      i = *s + 31 * i;
    return i % TABLE_SIZE;
}

symboliclabels* search_table( char* key ){
    int index = hash(key);
    if ( !strcmp(SymTable[index]->oprand, key)) {
        return SymTable[index];
    }
    else{ 
        printf("can't find the symbol\n");
        return NULL;
    }
}

symboliclabels* gennerate_label(char* Oprand, char* Upcode){
    symboliclabels* tmp = (symboliclabels*)malloc(sizeof(symboliclabels));
    strcpy(tmp->oprand,Oprand);
    strcpy(tmp->upcode,Upcode);
    return tmp;
}//makes a node with allocated space 


int insert_table(symboliclabels* node){
    //printf("\nInserting into hash table\n");
    //if is the slot empty
    int index = hash(node->oprand);
    printf("\nInserting into hash table at index %d, the node: %s\n", index, node->oprand);
    if (SymTable[index] != NULL){
        SymTable[index] = node;
        return 1;
    }
    return 0;
}

void display_table(void){
    for (int i=0; i<TABLE_SIZE; i++) {
        // if( SymTable[i] != NULL)
            printf("Index:\t %d\toprand: \t%s\tupcode: \t%s\n",i,SymTable[i]->oprand,SymTable[i]->upcode);
    }
    //printf("No Hash Entry at index %d\n",i);//just for empty entries
}
