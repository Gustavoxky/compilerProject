#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definindo os tipos de tokens
enum TokenType {
    NUMBER,
    PLUS,
    MINUS,
    TIMES,
    DIVIDE,
    MODULO,
    LPAREN,
    RPAREN,
    LBRACKET,
    RBRACKET,
    LBRACE,
    RBRACE,
    EQUALS,
    NOTEQUALS,
    LESSTHAN,
    GREATERTHAN,
    LESSTHANEQ,
    GREATERTHANEQ,
    AND,
    OR,
    NOT,
    INCREMENT,
    DECREMENT,
    ASSIGN,
    SEMICOLON,
    COMMA,
    IF,
    THEN,
    ELSE,
    WHILE,
    DO,
    FOR,
    FUNCTION,
    STRING,
    IDENTIFIER,
};

// Estrutura para armazenar informações sobre um token
struct Token {
    enum TokenType type;
    union {
        int number_value;
        char string_value[100]; // Ajuste conforme necessário
        char identifier_value[100]; // Ajuste conforme necessário
    } value;
};

// Função para imprimir informações sobre um token
void print_token(struct Token token) {
    switch (token.type) {
        case NUMBER:
            printf("NUMBER: %d\n", token.value.number_value);
            break;
        case STRING:
            printf("STRING: %s\n", token.value.string_value);
            break;
        case IDENTIFIER:
            printf("IDENTIFIER: %s\n", token.value.identifier_value);
            break;
        default:
            printf("TOKEN: %d\n", token.type);
    }
}

// Função para analisar a entrada e gerar tokens
void lexer(char *input) {
    char *current = input;

    while (*current != '\0') {
        // Ignorar espaços em branco
        if (isspace(*current)) {
            current++;
            continue;
        }

        struct Token token;  // Mova a declaração da variável para este ponto

        // Verificar tokens simples
        if (strncmp(current, "++", 2) == 0) {
            token = (struct Token){INCREMENT};
            print_token(token);
            current += 2;
        } else if (strncmp(current, "--", 2) == 0) {
            token = (struct Token){DECREMENT};
            print_token(token);
            current += 2;
        } else if (strncmp(current, "==", 2) == 0) {
            token = (struct Token){EQUALS};
            print_token(token);
            current += 2;
        } else if (strncmp(current, "!=", 2) == 0) {
            token = (struct Token){NOTEQUALS};
            print_token(token);
            current += 2;
        } else if (strncmp(current, "<=", 2) == 0) {
            token = (struct Token){LESSTHANEQ};
            print_token(token);
            current += 2;
        } else if (strncmp(current, ">=", 2) == 0) {
            token = (struct Token){GREATERTHANEQ};
            print_token(token);
            current += 2;
        } else {
            // Verificar tokens de um caractere
            switch (*current) {
                case '+':
                    token = (struct Token){PLUS};
                    print_token(token);
                    break;
                case '-':
                    token = (struct Token){MINUS};
                    print_token(token);
                    break;
                case '*':
                    token = (struct Token){TIMES};
                    print_token(token);
                    break;
                case '/':
                    token = (struct Token){DIVIDE};
                    print_token(token);
                    break;
                case '%':
                    token = (struct Token){MODULO};
                    print_token(token);
                    break;
                case '(':
                    token = (struct Token){LPAREN};
                    print_token(token);
                    break;
                case ')':
                    token = (struct Token){RPAREN};
                    print_token(token);
                    break;
                case '[':
                    token = (struct Token){LBRACKET};
                    print_token(token);
                    break;
                case ']':
                    token = (struct Token){RBRACKET};
                    print_token(token);
                    break;
                case '{':
                    token = (struct Token){LBRACE};
                    print_token(token);
                    break;
                case '}':
                    token = (struct Token){RBRACE};
                    print_token(token);
                    break;
                case '<':
                    token = (struct Token){LESSTHAN};
                    print_token(token);
                    break;
                case '>':
                    token = (struct Token){GREATERTHAN};
                    print_token(token);
                    break;
                case '&':
                    if (*(current + 1) == '&') {
                        token = (struct Token){AND};
                        print_token(token);
                        current++;
                    } else {
                        // Tratar erro
                    }
                    break;
                case '|':
                    if (*(current + 1) == '|') {
                        token = (struct Token){OR};
                        print_token(token);
                        current++;
                    } else {
                        // Tratar erro
                    }
                    break;
                case '!':
                    token = (struct Token){NOT};
                    print_token(token);
                    break;
                case '=':
                    token = (struct Token){ASSIGN};
                    print_token(token);
                    break;
                case ';':
                    token = (struct Token){SEMICOLON};
                    print_token(token);
                    break;
                case ',':
                    token = (struct Token){COMMA};
                    print_token(token);
                    break;
                default:
                    // Verificar números
                    if (isdigit(*current)) {
                        char *endptr;
                        int value = strtol(current, &endptr, 10);
                        token = (struct Token){NUMBER, .value.number_value = value};
                        print_token(token);
                        current = endptr;
                    }
                    // Verificar strings
                    else if (*current == '\"') {
                        char *start = ++current;
                        while (*current != '\"' && *current != '\0') {
                            current++;
                        }
                        if (*current == '\"') {
                            size_t length = current - start;
                            if (length < sizeof(token.value.string_value)) {
                                strncpy(token.value.string_value, start, length);
                                token.value.string_value[length] = '\0';
                                token.type = STRING;
                                print_token(token);
                                current++;
                            } else {
                                // Tratar erro: string muito longa
                            }
                        } else {
                            // Tratar erro: string não fechada
                        }
                    }
                    // Verificar identificadores
                    else if (isalpha(*current) || *current == '_') {
                        char *start = current;
                        while (isalnum(*current) || *current == '_') {
                            current++;
                        }
                        size_t length = current - start;
                        if (length < sizeof(token.value.identifier_value)) {
                            strncpy(token.value.identifier_value, start, length);
                            token.value.identifier_value[length] = '\0';
                            if (strcmp(token.value.identifier_value, "if") == 0) {
                                token.type = IF;
                            } else if (strcmp(token.value.identifier_value, "then") == 0) {
                                token.type = THEN;
                            } else if (strcmp(token.value.identifier_value, "else") == 0) {
                                token.type = ELSE;
                            } else if (strcmp(token.value.identifier_value, "while") == 0) {
                                token.type = WHILE;
                            } else if (strcmp(token.value.identifier_value, "do") == 0) {
                                token.type = DO;
                            } else if (strcmp(token.value.identifier_value, "for") == 0) {
                                token.type = FOR;
                            } else if (strcmp(token.value.identifier_value, "function") == 0) {
                                token.type = FUNCTION;
                            } else {
                                token.type = IDENTIFIER;
                            }
                            print_token(token);
                        } else {
                            // Tratar erro: identificador muito longo
                        }
                    }
                    // Tratar erro: caractere desconhecido
            }
        }
        current++;
    }
}

int main() {
    // Teste do analisador léxico
    char data[] = "var x = 10; var y = 20; var result = x + y;"
                  "if result > 30 then print(\"Result is greater than 30\");"
                  "else print(\"Result is not greater than 30\");";

    lexer(data);

    return 0;
}
