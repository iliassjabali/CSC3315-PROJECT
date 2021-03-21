#include "assembler.h"

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

int main(void){
    initTable();
    display_table();
    return 0;
}