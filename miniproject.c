#include<stdio.h>
#include<conio.h>
#include<string.h>


 //void check_label();
 //void check_opcode();

struct operationTable
{
    char mnemonics[100];
    char opcode[100];
}projectOptab[100];

struct symbolTable
{
    int address[100];
    char label[100];
}projectSymtab[100];


   int startAddress,locationCounter,finalAddress,programLength,labelCount=0;
   char label[100],opcode[100],operand[100],programName[100],lineNo[100];


   int main()
   {
       pass1();
       programLength=locationCounter-startAddress;
       pass2();

   }




   void pass1()
   {
       FILE *fp1,*fp2;
       fp1=fopen("inputfile.txt","r");
       fp2=fopen("intermediatefile.txt","w");

       printf(" LABEL\tOPCODE\tOPERAND");
       fscanf(fp1,"%s \t %s \t %s \n",label,opcode,operand);



       if(strcmp(opcode,"START"))
       {
           startAddress=atoi(operand);
           locationCounter=startAddress;
           strcpy(programName,label);
           printf("\n %d \t %s \t %s \t %s\n",locationCounter,label,opcode,operand);
           fprintf(fp2,"\n %d \t %s \t %s \t %s\n",locationCounter,label,opcode,operand);
       }

       else
       {
           locationCounter=atoi(operand);

           while(strcmp(opcode,"END")!=0)
          {

               if(label=="*" && opcode!="*" && operand!="*")
               {
                   check_opcode();
                   printf("\n %d \t %s \t %s \t %s \n",locationCounter,label,opcode,operand);
                   fprintf(fp2,"\n %d \t %s \t %s \t %s \n",locationCounter,label,opcode,operand);
               }

                if(label=="*" && opcode!="*" && operand=="*")
               {

                   check_opcode();
                    printf("\n %d \t %s \t %s \t %s \n",locationCounter,label,opcode,operand);
                   fprintf(fp2,"\n %d \t %s \t %s \t %s \n",locationCounter,label,opcode,operand);
               }

                if(label!="*" && opcode!="*" && operand=="*")
               {
                   check_label();
                   check_opcode();
                    printf("\n %d \t %s \t %s \t %s \n",locationCounter,label,opcode,operand);
                   fprintf(fp2,"\n %d \t %s \t %s \t %s \n",locationCounter,label,opcode,operand);

               }

                if(label!="*" && opcode!="*" && operand!="*")
               {
                   check_label();
                   check_opcode();
                    printf("\n %d \t %s \t %s \t %s \n",locationCounter,label,opcode,operand);
                   fprintf(fp2,"\n %d \t %s \t %s \t %s \n",locationCounter,label,opcode,operand);
               }
           }
                   printf("\n %d \t %s \t %s \t %s \n",locationCounter,label,opcode,operand);
                   fprintf(fp2,"\n %d \t %s \t %s \t %s \n",locationCounter,label,opcode,operand);

       }
       fclose(fp1);
       fclose(fp2);
   }


   void pass2()
   {
       FILE * fp3,*fp4,*fp5;



       fp3=fopen("intermediatefile.txt","r");
       fp4=fopen("result.txt","w");
       fp5=fopen("optab.txt","r");

        fscanf(fp3,"\n %d \t%s \t %s \t %s \n",locationCounter,label,opcode,operand);



   }


   void check_label()
   {
       int j,flag=0;
       for(j=0;j<labelCount;j++)
       {
           if(strcmp(label,projectSymtab[j].label)==0)
           {
               printf("error in label");
               flag=1;
               break;
           }
       }
           if(flag==0)
           {
               strcpy(projectSymtab[labelCount].label,label);
               projectSymtab[labelCount++].address=locationCounter;

           }

       }



   void check_opcode()
   {
       int k,flag=0;

       for(k=0;k<3;k++)
       {
           if(strcmp(opcode,projectOptab[k].mnemonics))
           {
               locationCounter=locationCounter+3;
               flag=1;
               break;
           }
       }
           if(flag==0)
           {
               if(strcmp(opcode,"WORD")==0)
               {
                   locationCounter+=3;
               }
               if(strcmp(opcode,"BYTE")==0)
               {
                   locationCounter+=1;
               }
               if(strcmp(opcode,"RESB")==0)
               {
                   locationCounter=locationCounter+atoi(operand);
               }
               if(strcmp(opcode,"RESW")==0)
               {
                   locationCounter=locationCounter+3*atoi(operand);
               }

           }
       }

