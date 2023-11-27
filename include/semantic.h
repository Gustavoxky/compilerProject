#ifndef SEMANTIC_H
#define SEMANTIC_H

#define MAX_SYMBOLS 100

typedef struct {
    char name[50];
    char type[20];
} Symbol;

extern Symbol symbolTable[MAX_SYMBOLS];
extern int symbolCount;

void declareVariable(char *name, char *type);
void useVariable(char *name);

#endif
