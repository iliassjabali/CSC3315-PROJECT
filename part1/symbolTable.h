#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TABLE_SIZE 17
#define oprand_SIZE 3
#define upcode_SIZE 2

typedef struct {
    char* oprand; //key
    char* upcode;
} symboliclabels;

symboliclabels SymTable[TABLE_SIZE]; 

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
    if ( !strcmp(SymTable[index].oprand, key)) {
        return &SymTable[index];
    }
    else{ 
        printf("can't find the symbol\n");
        return NULL;
    }
}

symboliclabels* gennerate_label(char* Oprand, char* Upcode){
    symboliclabels* tmp;
    tmp->oprand = (char*)malloc(sizeof(oprand_SIZE));
    tmp->upcode = (char*)malloc(sizeof(upcode_SIZE));
    memcpy(tmp->oprand,Oprand, sizeof(char)*oprand_SIZE);
    memcpy(tmp->upcode,Upcode, sizeof(char)*upcode_SIZE);
    return tmp;
}//makes a node with allocated space 


int insert_table(symboliclabels* node){
    //printf("\nInserting into hash table\n");
    //if is the slot empty
    int index = hash(node->oprand);
    if (!strcmp(SymTable[index].oprand, node->oprand)){
        SymTable[index]= *node;

        return 1;
    }
    return 0;
}

void display_table(void){
    for (int i=0; i<TABLE_SIZE; i++) {
            printf("oprand: \t%s\tupcode: \t%s\n",SymTable[i].oprand,SymTable[i].upcode);
        }
    //printf("No Hash Entry at index %d\n",i);//just for empty entries
}
void initialise_table(void){
    insert_table(gennerate_label("ASG", "+0"));
    insert_table(gennerate_label("ADD", "+1"));
    insert_table(gennerate_label("SUB", "+0"));
    insert_table(gennerate_label("MUL", "+0"));
    insert_table(gennerate_label("DIV", "+0"));
    insert_table(gennerate_label("SQR", "+0"));
    insert_table(gennerate_label("SQT", "+0"));
    insert_table(gennerate_label("EQL", "+0"));
    insert_table(gennerate_label("NEQ", "+0"));
    insert_table(gennerate_label("NEQ", "+0"));
    insert_table(gennerate_label("GTE", "+0"));
    insert_table(gennerate_label("LSS", "+0"));
    insert_table(gennerate_label("RDA", "+0"));
    insert_table(gennerate_label("WTA", "+0"));
    insert_table(gennerate_label("ITJ", "+0"));
    insert_table(gennerate_label("STP", "+0"));
    insert_table(gennerate_label("INP", "+8"));
    insert_table(gennerate_label("OUT", "-8"));
}