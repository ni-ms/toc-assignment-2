#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
//#include <sys/wait.h>


int main(int argc, char *argv[])
{

        FILE *myFile=fopen("input3.txt","r");
    if(myFile==NULL)
    {
        perror("Unable to open file");
        exit(1);
    }
    FILE *myFile1=fopen("Output1.c","w");
    fclose(myFile1);
     myFile1=fopen("Output1.c","a");
      fprintf(myFile1,"#include <stdio.h>  ");
      fprintf(myFile1,"\n ");
     fprintf(myFile1,"#include <stdlib.h> ");
      fprintf(myFile1,"\n ");
      fprintf(myFile1,"#include <string.h> ");
      fprintf(myFile1,"\n ");
        fprintf(myFile1," int main(int argc, char *argv[]){");
      fprintf(myFile1,"\n ");
        ///fprintf(myFile1,"int jamesBond77=0; ");


         //FILE *myFile=fopen("input1.txt","r");
       if(myFile==NULL)
    {
        perror("Unable to open file");
        exit(1);
    }

       char myF[7777];char *dec="int";char* re="read";char *wr="write";char *ap="=";char *fp="for";

    int c=1;
        while(fgets(myF,sizeof(myF),myFile))
    {
        if(strstr(myF,re)!=NULL)
        {
            char str[100];
            int val=atoi(argv[c++]);
           //int val=10;
          sprintf(str, "%d", val);
          int d=0;
          while(myF[d]!='d')
          d++;
          d++;
          int d1=0;char str1[1000];d++;
          while(myF[d]!=';')
          {
            str1[d1++]=myF[d++];
          }
          str1[d1]='=';int d3=0;d1++;
          while(str[d3]!='\0')
          {
            str1[d1++]=str[d3++];
          }
          str1[d1++]=';';
          str1[d1]='\0';
          fprintf(myFile1,str1);

        }
        else if(strstr(myF,wr)!=NULL)
        {
            char str[100];
            str[0]='p';str[1]='r';str[2]='i';str[3]='n';str[4]='t';str[5]='f';str[6]='(';str[7]='\"';str[8]='\0'; fprintf(myFile1,str);
            str[0]='%';str[1]='c';str[2]='\0';
            fflush(myFile1) ;
            fprintf(myFile1,str,37);
            str[0]='d';
            str[1]='\"';str[2]=',';
            int it=0;
            while(myF[it]!='e')
            it++;
            it++;it++;int it1=3;
            //printf("%s",str);
            while(myF[it]!=';')
            {
                str[it1++]=myF[it++];
            }
            str[it1++]=')';str[it1++]=';';str[it1]='\0';//printf("%s",str);
            fflush(myFile1) ;
            fprintf(myFile1,str);
        }
        else if(myF[0]=='}')
        fprintf(myFile1,"} ");
        else
        fprintf(myFile1,myF);


        fprintf(myFile1,"\n ");

    }


     fprintf(myFile1,"} ");
    fclose(myFile1);


}