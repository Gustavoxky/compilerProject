#ifndef INTERMEDIATE_CODE_H
#define INTERMEDIATE_CODE_H


#include <stdio.h>

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
void printToken(Token token);

// Função para imprimir código intermediário
void printIntermediateCode(IntermediateCode *code, int length);

// Função para realizar a análise léxica
Token getNextToken(char **expression);

// Função para realizar a análise sintática e geração de código intermediário
int generateIntermediateCode(char **expression, IntermediateCode *code);

#endif


