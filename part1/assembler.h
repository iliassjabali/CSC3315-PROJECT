#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 100
#define oprand_SIZE 3
#define upcode_SIZE 2

typedef struct {
    /*
    char oprand[oprand_SIZE]; //key
    char upcode[upcode_SIZE];
    */
    char* oprand; //key
    char* upcode;
} symboliclabels;

extern symboliclabels* SymTable[TABLE_SIZE]; 
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

symboliclabels* search_table( int index ){
    if ( SymTable[index] != NULL) {
        return SymTable[index];
    }
    else{ 
        printf("can't find the symbol\n");
        return NULL;
    }
}

symboliclabels* gennerate_label(char* Oprand, char* Upcode){
    //printf("Oprand:\t%s\tUpcode:\t%s\n",Oprand,Upcode );
    symboliclabels* tmp = (symboliclabels*)malloc(sizeof(symboliclabels));
    tmp->oprand = (char*) malloc(sizeof(char)*oprand_SIZE);
    tmp->upcode = (char*) malloc(sizeof(char)*upcode_SIZE);
    strncpy(tmp->upcode,Upcode, upcode_SIZE);
    strncpy(tmp->oprand,Oprand,oprand_SIZE);
    //printf("Oprand:\t%s\tUpcode:\t%s\n",tmp->oprand, tmp->upcode);
    return tmp;
}//makes a node with allocated space 

int insert_table(symboliclabels* node){
    //printf("\nInserting into hash table\n");
    //if is the slot empty
    int index = hash(node->oprand);
    if (SymTable[index] == NULL){
        SymTable[index] = node;
        //printf("\nInserting into hash table at index %d, the node: %s\n", index, SymTable[index]->oprand);
        return 1;
    }
    return 0;
}
void display_table(void){
    for (int i=0; i<TABLE_SIZE; i++) {
        if( SymTable[i] != NULL)
            printf("Index:\t %d\toprand: \t%s\tupcode: \t%s\n",i,SymTable[i]->oprand,SymTable[i]->upcode);
    }
    //printf("No Hash Entry at index %d\n",i);//just for empty entries
}
void initTable(void){
    insert_table(gennerate_label("ASG", "+0"));
    insert_table(gennerate_label("ADD", "+1"));
    insert_table(gennerate_label("SUB", "-1"));
    insert_table(gennerate_label("MUL", "+2"));
    insert_table(gennerate_label("DIV", "-2"));
    insert_table(gennerate_label("SQR", "+3"));
    insert_table(gennerate_label("SQT", "-3"));
    insert_table(gennerate_label("EQL", "+4"));
    insert_table(gennerate_label("NEQ", "-4"));
    insert_table(gennerate_label("GEQ", "+5")); // greter than or equal
    insert_table(gennerate_label("LES", "-5")); // less 
    insert_table(gennerate_label("LES", "+6"));
    insert_table(gennerate_label("LES", "-6"));
    insert_table(gennerate_label("ITJ", "+7")); // incr, test, jump
    insert_table(gennerate_label("LBL", "-7")); //label 
    insert_table(gennerate_label("REE", "+8")); //read
    insert_table(gennerate_label("OUT", "-8")); //print
    insert_table(gennerate_label("STP", "+9")); //stop

}
