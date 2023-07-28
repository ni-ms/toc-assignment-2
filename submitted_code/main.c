#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char parseString[10000];
int numVar = 0;
char existing_variables_list[50][50];
char keywords[4][100] = {"for", "int", "read", "write"};
void parseExpression(char* expression);
void parse_for_loop(char* stmnt);
void parseVariable(char* stmnt);
void parseVariableString(char* stmnt);

char* sliceString(const char* str, int start, int end)
{
    char* slice = (char*)malloc(sizeof(char) * (end - start + 1));
    int i;
    for(i = 0; i < end - start; i++){
        slice[i] = str[start + i];
    }
    slice[i] = '\0';
    return slice;
}

int charindex(char *str, char c){
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == c) return i;
    }
    return -1;
}

int strindex(char *str, char *substr){
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == substr[0]){
            int j;
            for(j = 0; j < strlen(substr); j++){
                if(str[i + j] != substr[j]) break;
            }
            if(j == strlen(substr)) return i;
        }
    }
    return -1;
}


void parse_alphanumeric_char(char var){
    strcat(parseString, "ANC[");
    parseString[strlen(parseString)] = var;
    strcat(parseString, "]");
}
void parseVariable(char* var){
    int flag = 0;
    for(int i = 0; i < numVar; i++){
      if(strcmp(existing_variables_list[i], var) == 0){
        flag = 1;
        break;
      }
    }

    if(flag == 1){
        parseVariableString(var);
    }else{
        fprintf(stderr, "Error: Variable %s not declared\n", var);
        exit(1);
    }
}

void parseVariableString(char* variable){

    strcat(parseString, "V[");
    //remove space
    if(strlen(variable) == 1){
        parse_alphanumeric_char(variable[0]);
    } else{
        parse_alphanumeric_char(variable[0]);
        parseVariableString(sliceString(variable, 1, strlen(variable)));
    }

    strcat(parseString, "]");
}

void parseVariableList(char* variableList) {



    strcat(parseString, "VL[");
    int commaIndex = charindex(variableList, ',');
    if(commaIndex == -1){
        strcpy(existing_variables_list[numVar++], variableList);
        parseVariable(variableList);
    }else{
        int comma_index2 = charindex(variableList, ',');
        char* first_variable = sliceString(variableList, 0, comma_index2);
        char* remaining_variable_list;
        if(variableList[comma_index2 + 1] == ' ') {
            remaining_variable_list = sliceString(variableList, comma_index2 + 2, strlen(variableList));
        }else{
            remaining_variable_list = sliceString(variableList, comma_index2 + 1, strlen(variableList));
        }

        for(int i = 0; i < 4; i++){
            if(strcmp(first_variable, keywords[i]) == 0){
                fprintf(stderr, "Error: Invalid variable name %s. Variable is a keywords\n", first_variable);
                exit(1);
            }
        }

//        existing_variables_list[numVar++][] = first_variable;
        strcpy(existing_variables_list[numVar++], first_variable);
       // parseVariable(first_variable);

        strcat(parseString, ",");
        parseVariableList(remaining_variable_list);


    }
    strcat(parseString, "]");

}


void ParseDeclaration(char *inp){
    if(strstr(inp, "int") == -1){
        fprintf(stderr, "Invalid Input!");
        return;
     } else{
        strcat(parseString, "D[int ");

        int firstSpaceIndex = charindex(inp, ' ');

        char* variableList = sliceString(inp, firstSpaceIndex+1, strlen(inp));
        //CHECK IF THERE IS A NUMBER
        for(int i = 0; i <= 9; i++){
          if(strchr(variableList, i + 48) != NULL){
            fprintf(stderr, "Invalid Input!");
            return;
          }
        }
        parseVariableList(variableList);
        strcat(parseString, "]");

    }

}
void parseReadStatement(char* stmnt){
    strcat(parseString, "RS[read ");

    int spInd = charindex(stmnt, ' ');

    parseVariable(stmnt + spInd + 1);

    strcat(parseString, "]");
}

void parseWriteStatement(char* stmnt){
    strcat(parseString, "W[write ");

    int spInd = charindex(stmnt, ' ');
    parseVariable(stmnt + spInd + 1);

    strcat(parseString, "]");
}
//get all index array
void get_all_index_array(int* arr, char* str, char* ch){
    int i = 0;

    char* occ = strchr(str, ch[0]);

    while(occ != NULL){

        int t = occ - str;
        arr[i] = t;
        i++;

        occ = strchr(occ + 1, 108);
    }
    arr[i] = -1;
    i++;
}
int enclosedChar(char* str, int index){
    char* temp = (char*)malloc(sizeof(char) * 50);
    strncpy(temp, str, index);

    char* open = strchr(temp, 40); //40 is ( 41 is )
    int forw = 0;
    while(open != NULL){
        forw+=1;
        open = strchr(open + 1, 40);
    }

    char* close = strchr(temp, 41); //40 is ( 41 is )
    int back = 0;
    while(close != NULL){
        back+=1;
        close = strchr(close + 1, 41);
    }
    int ret = forw == back ? 0 : 1;

    return ret;
}
void parse_digit(char* dig){
    strcat(parseString, "DIG[");
    int le = strlen(parseString);
    parseString[le] = dig[0];
    //parseString[le + 1] = '\0';
    strcat(parseString, "]");
}

void parse_integer_constant(char* int_val){
    strcat(parseString, "I[");
    if(strlen(int_val) == 1){
        parse_digit(int_val);
    } else {
        parse_digit(&int_val[0]);
        parse_integer_constant(int_val + 1);
    }
    strcat(parseString, "]");
}
void parseFactor(char* factor){
    strcat(parseString, "F[");

    if(factor[0] == '('){
    /*    char* internalExpr = (char*) malloc(50*sizeof(char));
        strncpy(internalExpr, factor + 1, strlen(factor) - 2);
        strcat(parseString, "(");
        parseExpression(internalExpr);
        strcat(parseString, ")");*/

    char* internalExpr = (char*) malloc(50*sizeof(char));
    internalExpr = sliceString(factor, 1, strlen(factor) - 1);
        strcat(parseString, "(");
        parseExpression(internalExpr);
        strcat(parseString, ")");
    }
    else if(factor[0] >= 48 && factor[0] <  58){

        parse_integer_constant(factor);
    } else {
        parseVariable(factor);
    }

    strcat(parseString, "]");

}
//Parse Term 2
void parseTerm2(char* text2){
    strcat(parseString, "T2[");
    int mulIndex = charindex(text2, '*');
    int divIndex = charindex(text2, '/');
    if(mulIndex != -1){
        int* mulIndexList = (int*)malloc(sizeof(int) * 50);
        get_all_index_array(mulIndexList, text2, "*");
        int breakFlag = 0;
        for(int i = 0; mulIndexList[i] != -1; i++){
            if(!enclosedChar(text2, mulIndexList[i])){
                breakFlag = 1;
                break;
            }
        }
        if(breakFlag == 0){
            char *factor = text2;
            parseFactor(factor);
            return;
        }
        int factor2EndIndex;
        if(text2[mulIndex - 1] == ' '){
            factor2EndIndex = mulIndex - 2;
        } else{
            factor2EndIndex = mulIndex - 1;
        }
        char *factor2 = sliceString(text2, 0, factor2EndIndex + 1);
        parseFactor(factor2);
        strcat(parseString, "*");
        int internalTerm2StartIndex;
        if(text2[mulIndex + 1] == ' '){
            internalTerm2StartIndex = mulIndex + 2;
        } else{
            internalTerm2StartIndex = mulIndex + 1;
        }
        char *internalTerm2 = sliceString(text2, internalTerm2StartIndex, strlen(text2));
        parseTerm2(internalTerm2);
    } else if(divIndex != -1){
        int* divIndexList = (int*)malloc(sizeof(int) * 50);
        get_all_index_array(divIndexList, text2, "/");
        int breakFlag = 0;
        for(int i = 0; divIndexList[i] != -1; i++){
            if(!enclosedChar(text2, divIndexList[i])){
                breakFlag = 1;
                break;
            }
        }
        if(breakFlag == 0){
            char *factor = text2;
            parseFactor(factor);
            return;
        }
        int factor2EndIndex;
        if(text2[divIndex - 1] == ' '){
            factor2EndIndex = divIndex - 2;
        } else{
            factor2EndIndex = divIndex - 1;
        }
        char *factor2 = sliceString(text2, 0, factor2EndIndex + 1);
        parseFactor(factor2);
        strcat(parseString, "/");
        int internalTerm2StartIndex;
        if(text2[divIndex + 1] == ' '){
            internalTerm2StartIndex = divIndex + 2;
        } else{
            internalTerm2StartIndex = divIndex + 1;
        }
        char *internalTerm2 = sliceString(text2, internalTerm2StartIndex, strlen(text2));
        parseTerm2(internalTerm2);
    } else {
        char *factor = text2;
        parseFactor(factor);
    }
    strcat(parseString, "]");

}

//Parse term 1
void parseTerm1(char* text) {
    strcat(parseString, "T1[");
    int plusIndex = charindex(text, '+');
    int minusIndex = charindex(text, '-');
    if (plusIndex != -1) {
        int *plus_index_list = malloc(50 * sizeof(int));
        get_all_index_array(plus_index_list, text, "+");
        int break_flag = 0;
        for (int i = 0; plus_index_list[i] != -1; i++) {
            if (!enclosedChar(text, plus_index_list[i])) {
                break_flag = 1;
                break;
            }
        }
        if (break_flag == 0) {
            char *term2 = text;
            parseTerm2(term2);
            return;
        }
        int term2EndIndex;
        if (text[plusIndex - 1] == ' ') {
            term2EndIndex = plusIndex - 2;
        } else {
            term2EndIndex = plusIndex - 1;
        }
        char *term2 = sliceString(text, 0, term2EndIndex + 1);
        parseTerm2(term2);
        strcat(parseString, "+");
        int internalTerm1StartIndex;
        if (text[plusIndex + 1] == ' ') {
            internalTerm1StartIndex = plusIndex + 2;

        } else {
            internalTerm1StartIndex = plusIndex + 1;
        }
        char *internalTerm1 = sliceString(text, internalTerm1StartIndex, strlen(text));
        parseTerm1(internalTerm1);


    } else if (minusIndex != -1) {
        int *minus_index_list = malloc(50 * sizeof(int));
        get_all_index_array(minus_index_list, text, "-");
        int break_flag = 0;
        for (int i = 0; minus_index_list[i] != -1; i++) {
            if (!enclosedChar(text, minus_index_list[i])) {
                break_flag = 1;
                break;
            }
        }
            if (break_flag == 0) {
                char *term2 = text;
                parseTerm2(term2);
                return;
            }
            int term2EndIndex;
            if (text[minusIndex - 1] == ' ') {
                term2EndIndex = minusIndex - 2;
            } else {
                term2EndIndex = minusIndex - 1;
            }
            char *term2 = sliceString(text, 0, term2EndIndex + 1);
            parseTerm2(term2);
            strcat(parseString, "-");
            int internalTerm1StartIndex;
            if (text[minusIndex + 1] == ' ') {
                internalTerm1StartIndex = minusIndex + 2;

            } else {
                internalTerm1StartIndex = minusIndex + 1;
            }
            char *internalTerm1 = sliceString(text, internalTerm1StartIndex, strlen(text));
            parseTerm1(internalTerm1);

        } else {
        char *term2 = text;
        parseTerm2(term2);
    }





    strcat(parseString, "]");

}

//Parse Expression
//
/*
 *
 * def parse_expression(expression: str):
    global parse_string
    parse_string += "E["

    if ">" in expression:
        gt_index = expression.index(">")

        if expression[gt_index - 1] == " ":
            term1_end_index = gt_index - 2
        else:
            term1_end_index = gt_index - 1

        term1 = expression[:term1_end_index + 1]

        parse_term1(term1)

        parse_string += ">"

        if expression[gt_index + 1] == " ":
            internal_expr_start_index = gt_index + 2
        else:
            internal_expr_start_index = gt_index + 1

        internal_expression = expression[internal_expr_start_index:]

        parse_expression(internal_expression)

    elif "==" in expression:
        gt_index = expression.index("==")

        if expression[gt_index - 1] == " ":
            term1_end_index = gt_index - 2
        else:
            term1_end_index = gt_index - 1

        term1 = expression[:term1_end_index + 1]

        parse_term1(term1)

        parse_string += "=="

        if expression[gt_index + 1] == " ":
            internal_expr_start_index = gt_index + 2
        else:
            internal_expr_start_index = gt_index + 1

        internal_expression = expression[internal_expr_start_index:]

        parse_expression(internal_expression)

    else:
        term1 = expression
        parse_term1(term1)

    parse_string += "]"
 */

void parseExpression(char* expression){
    strcat(parseString, "E[");
    int gtIndex = charindex(expression, '>');
    int eqIndex = strindex(expression, "==");
    if(gtIndex != -1){
        int term1_end_index;
        if(expression[gtIndex - 1] == ' '){
            term1_end_index = gtIndex - 2;
        }else{
            term1_end_index = gtIndex - 1;
        }
        char* term1 = sliceString(expression, 0, term1_end_index + 1);
        parseTerm1(term1);
        strcat(parseString, ">");
        int internal_expr_start_index;
        if(expression[gtIndex + 1] == ' '){
            internal_expr_start_index = gtIndex + 2;
        }else{
            internal_expr_start_index = gtIndex + 1;
        }
        char* internal_expression = sliceString(expression, internal_expr_start_index, strlen(expression));
        parseExpression(internal_expression);
    }else if(eqIndex != -1){
        int term1_end_index;
        if(expression[eqIndex - 1] == ' '){
            term1_end_index = eqIndex - 2;
        }else{
            term1_end_index = eqIndex - 1;
        }
        char* term1 = sliceString(expression, 0, term1_end_index + 1);
        parseTerm1(term1);
        strcat(parseString, "==");
        int internal_expr_start_index;
        if(expression[eqIndex + 1] == ' '){
            internal_expr_start_index = eqIndex + 2;
        }else{
            internal_expr_start_index = eqIndex + 1;
        }
        char* internal_expression = sliceString(expression, internal_expr_start_index, strlen(expression));
        parseExpression(internal_expression);
    }else{
        parseTerm1(expression);
    }
    strcat(parseString, "]");
}


//Parse assignment statement
void parseAssignmentStatement(char* stmnt){
    strcat(parseString, "AS[");

    int equalCharIndex = charindex(stmnt, '=');
    char* assignmentVariable;
    if(stmnt[equalCharIndex - 1] == ' '){
        assignmentVariable = sliceString(stmnt, 0, equalCharIndex - 1);
    }else{
        assignmentVariable = sliceString(stmnt, 0, equalCharIndex);
    }
    parseVariable(assignmentVariable);

    strcat(parseString, "=");

    char* expression;
    if(stmnt[equalCharIndex + 1] == ' '){
        expression = sliceString(stmnt, equalCharIndex + 2, strlen(stmnt));
    }else{
        expression = sliceString(stmnt, equalCharIndex + 1, strlen(stmnt));
    }
    parseExpression(expression);

    strcat(parseString, "]");
}



void parseStatement(char* statement){

    strcat(parseString, "S[");
    while(statement[0] == ' ') statement+=1;
    if(statement[strlen(statement) - 1] == '\n'){
        statement[strlen(statement) - 1] = '\0';
    }
    if(statement[strlen(statement) - 1] == ' '){
        statement[strlen(statement) - 1] = '\0';
    }

    if(statement[strlen(statement) - 1] == ';'){
        statement[strlen(statement) - 1] = '\0';
    }


    if(strstr(statement, "=") != NULL && strstr(statement, "for(") == NULL){
        parseAssignmentStatement(statement);
    }
    //if read in statement
    if(strstr(statement, "read") != NULL){
        parseReadStatement(statement);
    }
    //if write in statement
    if(strstr(statement, "write") != NULL){
        parseWriteStatement(statement);

    }

    strcat(parseString,"]");
}
//
//void parseStatementList(char** codeLines, int numLines){
//
//
//    strcat(parseString, "SL[");
//    if(numLines == 1){
//        parseStatement(codeLines[0]);
//    }
//    else{
//        parseStatement(codeLines[0]);
//        strcat(parseString, ";");
//        char** restCodeLines = (char**)malloc(sizeof(char*) * (numLines - 1));
//        for(int i = 1; i < numLines; i++){
//            restCodeLines[i - 1] = codeLines[i];
//        }
//        parseStatementList(restCodeLines, numLines - 1);
//    }
//
//}
void parseStatementList(char** statement_list, int lenStatementList){

    if(lenStatementList == 0){
        return;
    }
    strcat(parseString, "SL[");
    if(lenStatementList == 1){
        parseStatement(statement_list[0]);
    } else {
        if(strindex(statement_list[0], "for(") != -1){
            strcat(parseString, "S[");
            char* for_statement = statement_list[0];
            if(for_statement[strlen(for_statement) - 1] == '\n')
                for_statement[strlen(for_statement) - 1] = '\0';
                //strncpy(for_statement, for_statement, strlen(for_statement) - 1);

            parse_for_loop(for_statement);
            strcat(parseString, "{");
            int i = 2;
            for(; i < 100; i++)
                if(strchr(statement_list[i], 125) != NULL) break;
            char** temp1 = (char**)malloc(10000);
            for(int j = 2; j < i; j++) temp1[j - 2] = statement_list[j];
            parseStatementList(temp1, i - 2);
            strcat(parseString, "}");
            strcat(parseString, "];");

            char** temp2 = (char**)malloc(10000);
            for(int j = i + 1; j < lenStatementList; j++) temp2[j - i - 1] = statement_list[j];
            parseStatementList(temp2, lenStatementList - i - 1);
        } else {
            parseStatement(statement_list[0]);
            strcat(parseString, ";");

            char** temp1 = (char**)malloc(10000);
            for(int j = 1; j < lenStatementList; j++) temp1[j - 1] = statement_list[j];
            parseStatementList(temp1, lenStatementList - 1);
        }
    }

    strcat(parseString, "]");
}
void parse_for_loop(char* stmnt){
    int semicolon_index_list[2];

    strcat(parseString, "FL[(");

//    int open_para_index = strchr(stmnt, 40) - stmnt;
  int open_para_index = charindex(stmnt, '(');
 //   get_all_index_array(semicolon_index_list, stmnt, ";");
semicolon_index_list[0] = charindex(stmnt, ';');
char * stmtsliced = sliceString(stmnt, semicolon_index_list[0] + 1, strlen(stmnt));
semicolon_index_list[1] = charindex(stmtsliced, ';') + semicolon_index_list[0] + 1;

    int first_semicolon_index = semicolon_index_list[0];
    int second_semicolon_index = semicolon_index_list[1];

   // char* assignment_for1 = (char*)malloc(50 * sizeof(char));
    //strncpy(assignment_for1, stmnt + open_para_index + 1, first_semicolon_index - open_para_index - 1);
    char* assignment_for1 = sliceString(stmnt, open_para_index + 1, first_semicolon_index);

    parseAssignmentStatement(assignment_for1);
    strcat(parseString, ";");

   // char* expression_for2 = (char*)malloc(50 * sizeof(char));
   char * expression_for2;
    int expr_for2_SI, expr_for2_EI;

    if(stmnt[first_semicolon_index + 1] == ' '){
        expr_for2_SI  = first_semicolon_index + 2;
    } else {
        expr_for2_SI = first_semicolon_index + 1;
    }

    if(stmnt[second_semicolon_index - 1] == ' '){
        expr_for2_EI  = second_semicolon_index - 2;
    } else {
        expr_for2_EI = second_semicolon_index - 1;
    }
    expression_for2 = sliceString(stmnt, expr_for2_SI, expr_for2_EI + 1);
    //strncpy(expression_for2, stmnt + expr_for2_SI, expr_for2_EI - expr_for2_SI + 1);

    parseExpression(expression_for2);
    strcat(parseString, ";");

    char* statement_for3;
 //   strcpy(statement_for3, stmnt);

    if(stmnt[second_semicolon_index + 1] == ' '){
        statement_for3 = sliceString(stmnt, second_semicolon_index + 2, strlen(stmnt) - 1);
    } else {
        statement_for3 = sliceString(stmnt, second_semicolon_index + 1, strlen(stmnt) - 1);
    }

    if(strchr(statement_for3, '=') != NULL){
        parseAssignmentStatement(statement_for3);
    }else{
        parseExpression(statement_for3);
    }

    strcat(parseString, ")");
    strcat(parseString, "]");
}

void parseCode(char** codeLines, int lines){
   //Parse Declaration
   //remove semicolon form first line
    strcat(parseString, "[P[");
    //remove first semicolon
    codeLines[0][strlen(codeLines[0]) - 2] = '\0';

    ParseDeclaration(codeLines[0]);
    strcat(parseString, ";");
    //send the remaining codes

    parseStatementList(codeLines + 1, lines - 1);

    strcat(parseString, "]]");
    printf("Parse String: %s\n", parseString);


}

char** readFile(FILE *fp, int*n){
    char** codeLines = (char**)malloc(sizeof(char*) * 100);
    int i = 0;
    char line[1000];
    while(fgets(line, sizeof(line), fp) != NULL){
        (*n)++;
        codeLines[i] = (char*)malloc(sizeof(char) * 1000);
        strcpy(codeLines[i], line);
        i++;
    }
    return codeLines;
}

int main()
{
    char inp[1000];
    FILE *fp;
    fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        printf("Could not open file");
        return 0;
    }

    int countLines = 0;
    char **codeLines = readFile(fp, &countLines);

    parseCode(codeLines, countLines);
    fclose(fp);
    //STUFF

    FILE *myFile=fopen("input.txt","r");
    if(myFile==NULL){
        perror("Unable to open file");
        exit(1);
    }

    return 0;
}