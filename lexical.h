 enum token_types {SN, NUMBER, eOF};
 typedef enum token_types TokenType;

 struct Token {
    char  categ;
    char cValue;
    float nValue;
 };

//accept constants
const char TAB = '\t';
const char ENTER = '\n';
const char SPACE = ' ';
const char UNDERLINE = '_';
const char BAR = '/';
const char ADD = '+';
const char SUB = '-';
const char MULT = '*';
const char DIV = '/';
const char PAREN_OPEN = '(';
const char PAREN_CLOSED = ')';
const char EQUAL = '=';
const int HAS_TOKEN = 2;
const char* ERROR_PASS_FILE = "Você deve indicar um arquivo para ser analisado. Ex: lexical namefile.cmm";
const char* ERROR_NOT_FOUND_FILE = "Arquivo não encontrado!";
const char* ERROR_NUMBER_FLOAT_FORMAT = "Esperado um número após ";

void readFile(char *file);
void errorMessage(const char *error);
int checkState(char c, FILE *f);
int isLetter(char letter);
void addLetter(char c);
void justCleanBuffer();
void addStringFinal();
void printToken(TokenType tp, char value);
void cleanBuffer(FILE *f, char c);
float getFloat();
struct Token getToken();
void startParser();