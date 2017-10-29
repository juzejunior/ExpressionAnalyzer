#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "lexical.h"

char actual_char;
char last_char;
int STATE = 0;
char buffer[50];
int buffer_position = 0;
int line_number = 1;
struct Token token;
FILE *file;

int main(int argc, char **argv){
    if(argc > 1){
        readFile(argv[1]);
    }else{
        errorMessage(ERROR_PASS_FILE);
    }
}

/**
 * TODO: ADD Parser Logic, to test sintatic analyzer
 * */
void startParser() {
    /**
     * Example 
     * struct Token t = getToken();
     * if (t.categ == SN ) {
     *   //call R
     *   R();
     * }
     * */
    //DELETE THAT AFTER
    struct Token t = getToken();
    while(t.categ != '?') {
        if(t.categ == SN) {
            printf("SIGNAL: %c\n", t.cValue);
        } else if (t.categ == NUMBER) {
            printf("NUMBER: %.2f\n", t.nValue);
        }
        t = getToken();
    }
}

struct Token getToken() {
    int status;
    while((actual_char = fgetc(file)) != EOF && (status = checkState(actual_char, file)) != HAS_TOKEN);

    if(actual_char == EOF){
        printf("END OF FILE");
    }else if (status == HAS_TOKEN) {
        return token;
    }else {
        printf("ERROR na linha %d\n", line_number);
    }
    
    token.categ = '?';
    return token;
}

void readFile(char *file_name){
    file = fopen(file_name, "r");
    if(file != NULL){
        startParser();
    }else{
        errorMessage(ERROR_NOT_FOUND_FILE);
    }
}

int checkState(char c, FILE *f){
    switch(STATE){
        case 0:
           if(isdigit(c)){
                STATE = 4;
                addLetter(c);
            }else if(c == SPACE || c == TAB || c == ENTER){
                STATE = 0;
                if(c == ENTER){
                    line_number++;
                }
            }else if(c == EOF){
               STATE = 0;
               return -1;
            }else if(c == '+' || c == '-' || c == '*' || c == '=' || c == '/' || c == '(' || c == ')'){
                STATE = 0;
                addLetter(c);
                token.categ = SN;
                token.cValue = c;
                justCleanBuffer();
                return HAS_TOKEN;
            } else {
                printf("Symbol '%c' not recognized at line: %d\n",c,line_number);
                exit(0);
                return -1;
            }
            break;
        case 4:
            if(isdigit(c)){
                STATE = 4;
                addLetter(c);
            }else if(c == '.'){
                STATE = 5;
                addLetter(c);
            }else{//Outro
                addStringFinal();
                token.categ = NUMBER;
                token.nValue = getFloat();
                cleanBuffer(f, c);
                return HAS_TOKEN;
            }
            break;
        case 5:
            if(isdigit(c)){
                STATE = 6;
                ungetc(c, f);
            }else{
                errorMessage(ERROR_NUMBER_FLOAT_FORMAT);
            }
            break;
        case 6:
            if(isdigit(c)){
                STATE = 6;
                addLetter(c);
            }else{
                addStringFinal();
                token.categ = NUMBER;
                token.nValue = getFloat();
                cleanBuffer(f, c);
                return HAS_TOKEN;
            }
            break;
    }

    return 0;
}

int isLetter(char letter){
    if(isalpha(letter)){
        return 1;
    }
    return 0;
}

void errorMessage(const char *error){
    printf("Error: %s\n", error);
}

void addLetter(char c){
    buffer[buffer_position] = c;
    last_char = c;
    buffer_position++;
}

void addStringFinal(){
    buffer[buffer_position] = '\0';
}

void cleanBuffer(FILE *f, char c){
    buffer_position = 0;
    memset(&buffer[0], 0, sizeof(buffer));
    STATE = 0;
    if(c != EOF){
        ungetc(c, f);
    }
}

void justCleanBuffer(){
    buffer_position = 0;
    memset(&buffer[0], 0, sizeof(buffer));
    STATE = 0;
}

float getFloat(){
    float number = atof(buffer);
    return number;
}

