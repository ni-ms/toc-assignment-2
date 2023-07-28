#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

    FILE *myFile=fopen("input1.txt","r");
    if(myFile==NULL){
        perror("Unable to open file");
        exit(1);
    }

    FILE *myFile1=fopen("Output.c","w+");
    fprintf(myFile1,"#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n\nint main(int argc, char *argv[]){\n");


    char *re="read";
    char *wr="write";
    //String tokenization
    char *token;
    char *temp;
    char line[1024];
    while(fgets(line,1024,myFile)){
        token=strtok(line," ");
        while(token!=NULL){
            if(strcmp(token,re)==0){
                token=strtok(NULL," ");
                //remove last character
                token[strlen(token)-1]='\0';
                fprintf(myFile1, "scanf(\"%%d\", &%s);", token);
            }
            else if(strcmp(token,wr)==0){
                token=strtok(NULL," ");
                //remove last character
                token[strlen(token)-1]='\0';
                fprintf(myFile1, "printf(\"%%d\\n\", %s);",token);
            }
            else{
                fprintf(myFile1, " ");
                fprintf(myFile1,"%s",token);
            }
            token=strtok(NULL," ");
        }
    }
    fprintf(myFile1,"return 0;\n}");
    fclose(myFile);
    fclose(myFile1);
    return 0;
}

