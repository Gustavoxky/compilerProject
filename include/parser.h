#ifndef PARSER_H
#define PARSER_H

// Definição de tipos de token
typedef enum {
    NUM,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    LPAREN,
    RPAREN,
    END,
    ERROR
} TokenType;

// Estrutura para armazenar tokens
typedef struct {
    TokenType type;
    int value; // Apenas usado se o tipo for NUM
} Token;

// Função para imprimir tokens
void printToken(Token token);

// Função para realizar a análise léxica
Token getNextToken(char **expression);

// Funções para realizar a análise sintática
int parseExpression(char **expression);
int parseTerm(char **expression);
int parseFactor(char **expression);

#endif
