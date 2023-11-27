#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../../include/parser.h"

// Função para imprimir tokens
void printToken(Token token) {
    switch (token.type) {
        case NUM:
            printf("NUM: %d\n", token.value);
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
        case LPAREN:
            printf("LPAREN\n");
            break;
        case RPAREN:
            printf("RPAREN\n");
            break;
        case END:
            printf("END\n");
            break;
        case ERROR:
            printf("ERROR\n");
            break;
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
        }
        (*expression)++;
        return token;
    } else if (**expression == '(') {
        Token token;
        token.type = LPAREN;
        (*expression)++;
        return token;
    } else if (**expression == ')') {
        Token token;
        token.type = RPAREN;
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

// Função para realizar a análise sintática
int parseExpression(char **expression);

int parseTerm(char **expression);

int parseFactor(char **expression) {
    Token token = getNextToken(expression);

    if (token.type == NUM) {
        return token.value;
    } else if (token.type == LPAREN) {
        int result = parseExpression(expression);
        token = getNextToken(expression); // Expecting a closing parenthesis

        if (token.type != RPAREN) {
            return -1; // Error: Missing closing parenthesis
        }

        return result;
    } else {
        return -1; // Error: Unexpected token
    }
}

int parseTerm(char **expression) {
    int result = parseFactor(expression);

    Token token = getNextToken(expression);
    while (token.type == OP_MUL || token.type == OP_DIV) {
        int nextFactor = parseFactor(expression);

        if (token.type == OP_MUL) {
            result *= nextFactor;
        } else {
            if (nextFactor == 0) {
                return -1; // Error: Division by zero
            }
            result /= nextFactor;
        }

        token = getNextToken(expression);
    }

    // Put back the last token (not an operator) for the parent level parsing
    (*expression)--;

    return result;
}

int parseExpression(char **expression) {
    int result = parseTerm(expression);

    Token token = getNextToken(expression);
    while (token.type == OP_ADD || token.type == OP_SUB) {
        int nextTerm = parseTerm(expression);

        if (token.type == OP_ADD) {
            result += nextTerm;
        } else {
            result -= nextTerm;
        }

        token = getNextToken(expression);
    }

    // Put back the last token (not an operator) for the parent level parsing
    (*expression)--;

    return result;
}

// Função principal
int main() {
    char expression[] = "3 + 5 * (4 - 2)";
    char *ptr = expression;

    int result = parseExpression(&ptr);

    if (result != -1) {
        printf("Resultado da expressao: %d\n", result);
    } else {
        printf("Erro na expressao.\n");
    }

    return 0;
}
