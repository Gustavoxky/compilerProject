#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Definição de tipos de token
typedef enum {
    NUM,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    END,
    ERROR
} TokenType;

// Estrutura para armazenar tokens
typedef struct {
    TokenType type;
    int value; // Apenas usado se o tipo for NUM
} Token;

// Estrutura para armazenar instruções do código intermediário
typedef struct {
    TokenType operation;
    int operand; // Apenas usado se a operação for NUM
} IntermediateCode;

// Função para imprimir tokens
void printToken(Token token) {
    // Implementação da função printToken...
}

// Função para imprimir código intermediário
void printIntermediateCode(IntermediateCode *code, int length) {
    printf("Código Intermediário:\n");

    for (int i = 0; i < length; ++i) {
        switch (code[i].operation) {
            case NUM:
                printf("NUM(%d)\n", code[i].operand);
                break;
            case OP_ADD:
                printf("OP_ADD\n");
                break;
            case OP_SUB:
                printf("OP_SUB\n");
                break;
            case OP_MUL:
                printf("OP_MUL\n");
                break;
            case OP_DIV:
                printf("OP_DIV\n");
                break;
            default:
                printf("ERRO: Operação desconhecida\n");
                break;
        }
    }
}

// Função para verificar se um caractere é um operador
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Função para realizar a análise léxica
Token getNextToken(char **expression) {
    while (isspace(**expression)) {
        (*expression)++;
    }

    if (isdigit(**expression)) {
        Token token;
        token.type = NUM;
        token.value = 0;

        while (isdigit(**expression)) {
            token.value = token.value * 10 + (**expression - '0');
            (*expression)++;
        }

        return token;
    } else if (isOperator(**expression)) {
        Token token;
        switch (**expression) {
            case '+':
                token.type = OP_ADD;
                break;
            case '-':
                token.type = OP_SUB;
                break;
            case '*':
                token.type = OP_MUL;
                break;
            case '/':
                token.type = OP_DIV;
                break;
            default:
                token.type = ERROR;
                break;
        }
        (*expression)++;
        return token;
    } else if (**expression == '\0') {
        Token token;
        token.type = END;
        return token;
    } else {
        Token token;
        token.type = ERROR;
        return token;
    }
}

// Função para realizar a análise sintática e geração de código intermediário
int generateIntermediateCode(char **expression, IntermediateCode *code);

// Função principal
int main() {
    char expression[] = "3 + 5 - 2 * 4 / 2";
    char *ptr = expression;

    IntermediateCode intermediateCode[50]; // Um array para armazenar o código intermediário
    int codeLength = generateIntermediateCode(&ptr, intermediateCode);

    if (codeLength != -1) {
        printIntermediateCode(intermediateCode, codeLength);
    } else {
        printf("Erro na expressao.\n");
    }

    return 0;
}

// Implementação da função de análise sintática e geração de código intermediário
int generateIntermediateCode(char **expression, IntermediateCode *code) {
    int codeIndex = 0;

    // Inicialmente, esperamos um número
    Token token = getNextToken(expression);

    if (token.type == NUM) {
        // Adicionamos uma instrução para o número
        code[codeIndex].operation = NUM;
        code[codeIndex].operand = token.value;
        codeIndex++;

        // Agora, esperamos um operador ou o fim da expressão
        token = getNextToken(expression);

        while (token.type == OP_ADD || token.type == OP_SUB || token.type == OP_MUL || token.type == OP_DIV) {
            // Adicionamos uma instrução para o operador
            code[codeIndex].operation = token.type;
            codeIndex++;

            // Esperamos outro número
            token = getNextToken(expression);

            if (token.type == NUM) {
                // Adicionamos uma instrução para o próximo número
                code[codeIndex].operation = NUM;
                code[codeIndex].operand = token.value;
                codeIndex++;

                // Avançamos para o próximo token
                token = getNextToken(expression);
            } else {
                // Se não encontrarmos um número após o operador, há um erro na expressão
                return -1;
            }
        }

        // Verificamos se o loop terminou porque encontramos o fim da expressão
        if (token.type == END) {
            return codeIndex;
        }
    }

    // Se chegamos aqui, houve um erro na análise sintática
    return -1;
}
