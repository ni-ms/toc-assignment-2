#include <stdio.h>
#include <ctype.h>
#include <string.h>

//All the tokens to be created along with their assigned ID
#define INT_VALUE 100          // -->for direct int value, like 1, 121, 48 etc
#define VAR 101                //For Variables like a, b, c
#define TO_ADD 102            // +
#define TO_SUB 103            // -
#define TO_MUL 104
#define TO_DIV 105
#define TO_ASSIGN 106        // =
#define GREATERTHAN 107     // >
#define LESSERTHAN 108
#define EQUALTO 109         // ==
#define COMMA 110           // ,
#define SEMICOLON 111       // ;
#define LOOP 112            // If keyword is "for"
#define INT_INST 113       // If keyword is 'int'
#define LEFTPAR 114         // (
#define RIGHTPAR 115
#define LEFTCURLY 116       // {
#define RIGHTCURLY 117

#define READ 120
#define WRITE 121

struct node
{
    int data;
    struct node* left;
    struct node* right;
};



char nextSymbol;      // For getting nextSymbol from the file
int symbolType;       //For symboltype like alphabet, number, notsure
int token;            //For token

char lexemeArr[1000];
char forArr[] = "for";
char readArr[] = "read", writeArr[] = "write";
char intArr[] = "int";

//Functions Used
void fetchNext();                   //To get next symbol and their type
int lexemeType();                   //To take appropriate actions based on the type of symbol
int addSymbol(int a);               //Add symbol in lexeme Array
void EvalOperators(char ch);        //To add operators like + - * / > < , ; ( ) { } EOF in the array and give them a token


FILE *input;
FILE *output;

char lexeme[1000][10];
int finalTokenArray[10000];
int indexing = 0;



int addSymbol(int a){                                //a here is the lexeme length
    lexemeArr[a] = nextSymbol;
    a++;
    lexemeArr[a] = 0;
    return a;
}

void EvalOperators(char ch){
    int lexemeLength = 0;
    if(ch == '+') {lexemeLength = addSymbol(lexemeLength); token = TO_ADD;}
    else if(ch == '-') {lexemeLength = addSymbol(lexemeLength); token = TO_SUB;}
    else if(ch == '*') {lexemeLength = addSymbol(lexemeLength); token = TO_MUL;}
    else if(ch == '/') {lexemeLength = addSymbol(lexemeLength); token = TO_DIV;}
    else if(ch == '>') {lexemeLength = addSymbol(lexemeLength); token = GREATERTHAN;}
    else if(ch == '<') {lexemeLength = addSymbol(lexemeLength); token = LESSERTHAN;}
    else if(ch == ',') {lexemeLength = addSymbol(lexemeLength); token = COMMA;}
    else if(ch == ';') {lexemeLength = addSymbol(lexemeLength); token = SEMICOLON;}
    else if(ch == '(') {lexemeLength = addSymbol(lexemeLength); token = LEFTPAR;}
    else if(ch == ')') {lexemeLength = addSymbol(lexemeLength); token = RIGHTPAR;}
    else if(ch == '{') {lexemeLength = addSymbol(lexemeLength); token = LEFTCURLY;}
    else if(ch == '}') {lexemeLength = addSymbol(lexemeLength); token = RIGHTCURLY;}
    else{
        lexemeLength = addSymbol(lexemeLength);
        token = EOF;
    }

}

int lexemeType(){
    int lexemeLength = 0;

    while(nextSymbol == ' ' || nextSymbol == '\n') fetchNext();

    if(symbolType == -10){                                    // -10 is for ALPHABET
        while(symbolType == -10){
            lexemeLength = addSymbol(lexemeLength);
            fetchNext();
        }
        if(!strcmp(lexemeArr,forArr)) token = LOOP;
        else if(!strcmp(lexemeArr,readArr)) token = READ;
        else if(!strcmp(lexemeArr, writeArr)) token = WRITE;
        else if(!strcmp(lexemeArr, intArr)) token = INT_INST;
        else token = VAR;
    }
    else if(symbolType == -11){                         // -11 is for NUMBER
        while (symbolType == -11)
        {
            lexemeLength = addSymbol(lexemeLength);
            fetchNext();
        }
        token = INT_VALUE;
    }
    else if(symbolType == -12){                     // -12 if for NOTSURE
        if(nextSymbol == '='){
            lexemeLength = addSymbol(lexemeLength);
            token = TO_ASSIGN;
            fetchNext();

            if(nextSymbol == '='){
                lexemeLength = addSymbol(lexemeLength);
                token = EQUALTO;
                fetchNext();
            }
        }
        else{
            EvalOperators(nextSymbol);
            fetchNext();
        }
    }
    else{
        token = EOF;
        lexemeArr[0] = 'E'; lexemeArr[1] = 'O'; lexemeArr[2] = 'F';
    }

    //printf("Token: %d, Lexeme: %s\n", token, lexemeArr);

    strcpy(lexeme[indexing],lexemeArr);
    finalTokenArray[indexing] = token;
    indexing++;
    return token;
}

void fetchNext(){
    nextSymbol = fgetc(input);

    if(nextSymbol != EOF){
        if(isalpha(nextSymbol))  symbolType = -10;
        else if(isdigit(nextSymbol))  symbolType = -11;
        else symbolType = -12;
    }
    else symbolType = EOF;
}


int main(int argc, char const *argv[])
{
    input = fopen("input1.txt", "r");
    output = fopen("output.txt", "w+");   //Might help in next part

    if(input == NULL) printf("There is no content in input.txt file\n Please recheck the input file.");
    else{
        fetchNext();
        do
        {
            lexemeType();
        } while (token != EOF);
    }

     for(int i = 0; i<indexing; i++){
         printf("%d  %s\n ", finalTokenArray[i], lexeme[i]);
     }
     printf("%s", lexeme[0]);


//    int sColon;       //to get first semicolon
//    for (int i = 0; i < indexing; i++)
//    {
//        if(lexeme[i][0] == ';'){
//            sColon = i;
//            break;
//        }
//    }
//    int noOfVar = (sColon/2);
//
//    printf("[<Start>[<Declare>[<Variable-List>[int");
//    if(noOfVar == 1){
//        printf("[<Variable[%s]]]]", lexeme[sColon-1]);
//    }
//    else{
//        for (int i = 0; i < noOfVar-2; i++)
//        {
//            printf("[<Variable>[<Variable>[%s]", lexeme[(2*i) + 1]);
//        }
//        printf("[<Variable>[%s]<Variable>[%s]", lexeme[sColon-3], lexeme[sColon-1]);
//        for (int i = 0; i < (noOfVar*2) ; i++)
//        {
//            printf("]");
//        }
//    }
//    printf("[<Statement>]]");

    return 0;
}
