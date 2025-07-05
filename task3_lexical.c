#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char keywords[32][10] = {
    "auto","break","case","char","const","continue","default","do","double",
    "else","enum","extern","float","for","goto","if","int","long",
    "register","return","short","signed","sizeof","static","struct","switch",
    "typedef","union","unsigned","void","volatile","while"
};

int isKeyword(char *word) {
    for (int i = 0; i < 32; i++) {
        if (strcmp(keywords[i], word) == 0)
            return 1;
    }
    return 0;
}

int isOperatorChar(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
            ch == '=' || ch == '%' || ch == '<' || ch == '>' || ch == '!');
}

void createInputFile() {
    FILE *fp = fopen("input.txt", "w");
    if (fp == NULL) {
        printf(" Error creating input.txt\n");
        exit(1);
    }

    char buffer[1000];
    printf(" Enter your code (type 'END' to stop):\n");

    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        if (strcasecmp(buffer, "END") == 0)
            break;

        fprintf(fp, "%s\n", buffer);
    }

    fclose(fp);
    printf(" input.txt created successfully.\n");
}

void lexicalAnalysis() {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf(" Cannot open input.txt\n");
        return;
    }

    char ch, buffer[100];
    int i = 0;

    printf("\n Lexical Analysis Result:\n");

    while ((ch = fgetc(fp)) != EOF) {
        // Skip string literals
        if (ch == '"') {
            printf(" String Literal: \"");
            while ((ch = fgetc(fp)) != '"' && ch != EOF) {
                putchar(ch);
            }
            printf("\"\n");
            continue;
        }

        // Build words/numbers
        if (isalnum(ch) || ch == '_') {
            buffer[i++] = ch;
        } else {
            if (i > 0) {
                buffer[i] = '\0';
                i = 0;

                if (isKeyword(buffer)) {
                    printf(" Keyword: %s\n", buffer);
                } else if (isdigit(buffer[0])) {
                    printf(" Number: %s\n", buffer);
                } else {
                    printf(" Identifier: %s\n", buffer);
                }
            }

            // Handle operator (possibly double-char like ==, !=)
            if (isOperatorChar(ch)) {
                char next = fgetc(fp);
                if (next == '=') {
                    printf(" Operator: %c%c\n", ch, next);
                } else {
                    printf(" Operator: %c\n", ch);
                    ungetc(next, fp);
                }
            }
        }
    }

    fclose(fp);
}
    
int main() {
    createInputFile();
    lexicalAnalysis();
    return 0;
}
