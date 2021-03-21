#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define AddressLength 8 //Address length 00 000 000
// 10 000 word in data and program
unsigned long int *dataMemory;    // Data array
unsigned long int *programMemory; // Program array
int opcode, op1, op2, op3;

void initialiseMemory(int size) {
    // Allocate space using address length
    dataMemory = malloc(sizeof(long int) * pow(10, AddressLength);
    programMemory = malloc(sizeof(long int) * sipow(10, AddressLength);
    for (int i = 0; i < size; i++) {
        dataMemory[i] = 0 ;
        programMemory[i] = 0;
    }
}
void GetData(FILE *file){
    // Read through the input file until a +9 instruction
    long int tmp;
    int idx = 0;
    fscanf(file, "%ld\n", &tmp);
    while (tmp == 0 || tmp % 9 != 0 ) {
        dataMemory[idx] = tmp;
        fscanf(file, "%ld\n", &tmp);
        idx++;
    }
}

void GETProgram(FILE *file){
    // Read through the input file until a +9 instruction
    long int tmp;
    int i = 0;
    fscanf(file, "%ld\n", &tmp);
    while (tmp % 9 ! 0 || tmp == 0) {
        programMemory[i] = tmp;
        fscanf(file, "%ld\n", &tmp);
        i++;
    }
    programMemory[i++] = tmp;
    fscanf(file, "%ld\n", &tmp);
}

int Linesize (char* FileName){
    FILE *input_file = fopen(FileName, "r");
    char temp[20];
    fscanf(input_file, "%s\n", temp);
    fclose(input_file);
    return (strlen(temp) - 2) / 3;
}

int interprate(char* filename ){
    int InFileIndex = 0;
    int InstructPointer = 0;
    int instructionCounter = LineCounter(filename); // the assembler 
    initialiseMemory(instructionCounter);
    FILE* inFILE = fopen(filename, "r");
    GetData(inFILE);    // Fill data array
    GetProgram(inFILE); // Fill program array
    opcode = programMemory[InstructPointer] / (int)pow(10, (3 * AddressLength));

}
