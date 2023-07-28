#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    FILE *myFile=fopen("input1.txt","r");
    if(myFile==NULL)
    {
        perror("Unable to open file");
        exit(1);
    }
   // char oList[7777];
    int arr[200];
    //int aind=-1;
    int ind=0;
    
    char *dec="int";
    char *re="read";
    char *wr="write";
    char *ap="=";
    char *fp="for";

    char myF[7777];
    int c=0;
    int inl=0;
    while(fgets(myF,sizeof(myF),myFile))
    {
        if(ind==0)
        {
            arr[ind++]='[';arr[ind++]='P';c++;printf("[P");
        }
        else
        {
            arr[ind++]='[';arr[ind++]='K';c++;
              if(myF[0]=='}')
        {
            printf("%c ;]",myF[0]);
        }
            
            printf("[K");
        }
        
        if(strstr(myF,dec)!=NULL)
        {
            arr[ind++]='[';arr[ind++]='D';
            printf("[D[int C[");
            int d=0;int cc=0;int i4=0;
            while(myF[i4]!='\0')
            {
                if(myF[i4]==',')
                cc++;
                i4++;

            }
           // printf("%d",cc);
            while(myF[d]!=' ')
             {
                d++;
             }
             //printf("[");printf("%c",myF[++d]);int c1=1;++d;
             int c1=0;
             int f=0;int vb=0;int s1=0;d++;
             while(myF[d]!=';')
             {
                if(f==0)
                {
                    printf("V[");f=1;vb++;printf("%c",myF[d]);c1++;c1++;
                }
                else if(myF[d]==',')
                {
                    for(int i3=1;i3<=vb;i3++)
                    printf("]");
                    if(s1==0)
                    s1++;
                    else
                    printf("]]");
                    vb=0;f=0;

                    if(cc>0)
                    {printf(",[C[");cc--;}
                    else
                    printf("[");

                    c1=1;
                }
                else
                {
                    printf("M[");vb++;printf("%c",myF[d]);c1++;
                }

                
                d++;
             }

             for(int i5=1;i5<=c1;i5++)
             printf("]");
             

             printf("]];]");


            arr[ind++]=']';
        }
        else if(strstr(myF,re)!=NULL)
        {
            arr[ind++]='[';arr[ind++]='R';
        printf("[R[read V"); 
                int d=0;
             while(myF[d]!=' ')
             {
                d++;
             }
             printf("[");printf("%c",myF[++d]);int c1=1;++d;
             while(myF[d]!=';')
             {
                printf("M[");printf("%c",myF[d]);c1++;d++;
             }
             for(int i2=1;i2<=c1;i2++)
                    printf("]");

             printf("];]");
        
        arr[ind++]=']';
        }
        else if(strstr(myF,wr)!=NULL)
        {
             arr[ind++]='[';arr[ind++]='W';
             printf("[W[write V"); 
                int d=0;
             while(myF[d]!=' ')
             {
                d++;
             }
             printf("[");printf("%c",myF[++d]);int c1=1;++d;
             while(myF[d]!=';')
             {
                printf("M[");printf("%c",myF[d]);c1++;d++;
             }
             for(int i2=1;i2<=c1;i2++)
                    printf("]");

             printf("];]");arr[ind++]=']';
        }
        else if(strstr(myF,fp)!=NULL && strstr(myF,ap)==NULL)
        {
            arr[ind++]='[';arr[ind++]='F';
            printf("[F(");int it=0;
            while(myF[it]!='(')
            it++;

            it++;

            int ft=0;int c2=0;printf("[E");int st=0;
            while(myF[it]!=';')
            {
                if(((myF[it]>='a' && myF[it]<='z')||(myF[it]>='0' && myF[it]<='9'))==0)
                {
                    ft=0;
                    for(int i7=1;i7<=c2;i7++)
                    printf("]");

                    c2=0;printf("%c",myF[it]);

                }
                else if(st==0)
                {
                    printf("[V[");c2=2;ft=1;printf("%c",myF[it]);st=1;
                }
                else if(ft==0)
                {
                        printf("[E[V[");c2=3;ft=1;printf("%c",myF[it]);
                }
                else
                {
                    printf("M[");printf("%c",myF[it]);c2++;
                }
                it++;
            }

              for(int i7=1;i7<=c2;i7++)
                    printf("]");

                    c2=0;ft=0;st=0;printf(";]");it++;printf("[E");


                       while(myF[it]!=';')
            {
                if(((myF[it]>='a' && myF[it]<='z')||(myF[it]>='0' && myF[it]<='9'))==0)
                {
                    ft=0;
                    for(int i7=1;i7<=c2;i7++)
                    printf("]");

                    c2=0;printf("%c",myF[it]);
                }
                else if(st==0)
                {
                    printf("[V[");c2=2;ft=1;printf("%c",myF[it]);st=1;
                }
                else if(ft==0)
                {
                        printf("[E[V[");c2=3;ft=1;printf("%c",myF[it]);
                }
                else
                {
                    printf("M[");printf("%c",myF[it]);c2++;
                }
                it++;
            }

            for(int i7=1;i7<=c2;i7++)
                    printf("]");

            c2=0;ft=0;st=0;printf(";]");it++;printf("[E");


                       while(myF[it]!=')')
            {
                if(((myF[it]>='a' && myF[it]<='z')||(myF[it]>='0' && myF[it]<='9'))==0)
                {
                    ft=0;
                    for(int i7=1;i7<=c2;i7++)
                    printf("]");

                    c2=0;printf("%c",myF[it]);
                }
                else if(st==0)
                {
                    printf("[V[");c2=2;ft=1;printf("%c",myF[it]);st=1;
                }
                else if(ft==0)
                {
                        printf("[E[V[");c2=3;ft=1;printf("%c",myF[it]);
                }
                else
                {
                    printf("M[");printf("%c",myF[it]);c2++;
                }
                it++;
            }
            
            for(int i7=1;i7<=c2;i7++)
                    printf("]");
            
            
            printf("]){");
            inl=1;arr[ind++]=']';
        }
        else if(strstr(myF,ap)!=NULL)
        {
            arr[ind++]='[';arr[ind++]='A';
            printf("[A[V[");arr[ind++]=']';int it=0;
            printf("%c",myF[it++]);int c1=2;
            
            while(myF[it]!='=')
            {
                printf("V1[");printf("%c",myF[it]);c1++;it++;
            }
            for(int i2=1;i2<=c1;i2++)
                    printf("]");

                    printf("=");it++;
                //while((myF[it]>='a' && myF[it]<='z')==false)
            int ft=0;int c2=0;printf("[E");int st=0;
            while(myF[it]!=';')
            {
                if(((myF[it]>='a' && myF[it]<='z')||(myF[it]>='0' && myF[it]<='9'))==0)
                {
                    ft=0;
                    for(int i7=1;i7<=c2;i7++)
                    printf("]");

                    c2=0;printf("%c",myF[it]);
                }
                else if(st==0)
                {
                    printf("[V[");c2=2;ft=1;printf("%c",myF[it]);st=1;
                }
                else if(ft==0)
                {
                        printf("[E[V[");c2=3;ft=1;printf("%c",myF[it]);
                }
                else
                {
                    printf("M[");printf("%c",myF[it]);c2++;
                }
                it++;
            }

              for(int i7=1;i7<=c2;i7++)
                    printf("]");

                    c2=0;
            
            printf("];]");
        }
       
    }
    fclose(myFile);

    for(int b=1;b<=c;b++)
    {   arr[ind++]=']';
        printf("]");}

}