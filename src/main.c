#include <stdio.h>
#include <stdlib.h>
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/semantic.h"
#include "../include/intermediateCode.h"

int main() {
    // Teste do analisador léxico
    char data[] = "var x = 10; var y = 20; var result = x + y;"
                  "if result > 30 then print(\"Result is greater than 30\");"
                  "else print(\"Result is not greater than 30\");";

    printf("Analisador Léxico:\n");
    lexer(data);

    // Teste do analisador sintático e geração de código intermediário
    char expression[] = "3 + 5 - 2 * 4 / 2";
    char *ptr = expression;

    IntermediateCode intermediateCode[50];
    int codeLength = generateIntermediateCode(&ptr, intermediateCode);

    if (codeLength != -1) {
        printIntermediateCode(intermediateCode, codeLength);
    } else {
        printf("Erro na expressao.\n");
    }


    // Teste do analisador semântico
    printf("\nAnalisador Semântico:\n");
    declareVariable("x", "int");
    declareVariable("y", "float");

    useVariable("x");
    useVariable("z");  // Erro semântico: Variável 'z' não declarada.

    return 0;
}
