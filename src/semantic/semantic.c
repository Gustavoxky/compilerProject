#include "../../include/semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Symbol symbolTable[MAX_SYMBOLS];
int symbolCount = 0;

void declareVariable(char *name, char *type) {
    // Verificar se a variável já foi declarada
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            printf("Erro semântico: Variável '%s' já declarada.\n", name);
            exit(1);
        }
    }

    // Adicionar a variável à tabela de símbolos
    Symbol newSymbol;
    strcpy(newSymbol.name, name);
    strcpy(newSymbol.type, type);
    symbolTable[symbolCount++] = newSymbol;
}

void useVariable(char *name) {
    // Verificar se a variável foi declarada
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            // A variável foi encontrada, pode ser usada
            return;
        }
    }

    // Se não foi encontrada, gerar erro
    printf("Erro semântico: Variável '%s' não declarada.\n", name);
    exit(1);
}

int main() {
    // Exemplo de código onde a análise semântica pode ser aplicada
    declareVariable("x", "int");
    declareVariable("y", "float");

    useVariable("x");
    useVariable("z");  // Erro semântico: Variável 'z' não declarada.

    return 0;
}
