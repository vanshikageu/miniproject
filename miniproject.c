#include<stdio.h>
#include<conio.h>
#include<string.h>


linebyline_read();
check_label();
check_opcode();

struct operation_table
{
    char mnemonics[100];
    char opcode[100];
}project_optab[100];

struct symbol_table
{
    int address[100];
    char label[100];
}project_symtab[100];


   int start_address,location_counter,final_address,program_length,label_count=0;
   char label[100],opcode[100],operand[100],program_name[100],line_no[100];


   int main()
   {
       pass1();
       program_length=location_counter-start_address;
       pass2();

   }




   void pass1()
   {
       FILE *fp1,*fp2;
       *fp1=fopen("inputfile.txt","r");
       *fp2=fopen("intermediatefile.txt","w");

       printf(" LABEL\tOPCODE\tOPERAND");
       fscanf(f1,"%s \t %s \t %s \n",label,opcode,operand);
       linebyline_read();\\


       if(strcmp(opcode,"START"))
       {
           start_address=atoi(operand);
           location_counter=start_address;
           printf("\n %d \t %s \t %s \t %s\n",location_counter,label,opcode,operand);
           fprintf(fp2,"\n %d \t %s \t %s \t %s\n",location_counter,label,opcode,operand);
       }

       else
       {
           location_counter=atoi(operand);

           while(strcmp(opcode,"END")!=0)
          {

               if(label=="*" && opcode!="*" && operand!="*")
               {
                   check_opcode();\\
                   printf("\n %d \t %s \t %s \t %s \n",location_counter,label,opcode,operand);
                   fprintf(fp2,"\n %d \t %s \t %s \t %s \n",location_counter,label,opcode,operand);\\
               }

                if(label=="*" && opcode!="*" && operand=="*")
               {

                   check_opcode();
                    printf("\n %d \t %s \t %s \t %s \n",location_counter,label,opcode,operand);
                   fprintf(fp2,"\n %d \t %s \t %s \t %s \n",location_counter,label,opcode,operand);
               }

                if(label!="*" && opcode!="*" && operand=="*")
               {
                   check_label();
                   check_opcode();
                    printf("\n %d \t %s \t %s \t %s \n",location_counter,label,opcode,operand);
                   fprintf(fp2,"\n %d \t %s \t %s \t %s \n",location_counter,label,opcode,operand);

               }

                if(label!="*" && opcode!="*" && operand!="*")
               {
                   check_label();
                   check_opcode();
                    printf("\n %d \t %s \t %s \t %s \n",location_counter,label,opcode,operand);
                   fprintf(fp2,"\n %d \t %s \t %s \t %s \n",location_counter,label,opcode,operand);
               }
           }
                   printf("\n %d \t %s \t %s \t %s \n",location_counter,label,opcode,operand);
                   fprintf(fp2,"\n %d \t %s \t %s \t %s \n",location_counter,label,opcode,operand);

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

        fscanf(fp3,"\n %d \t%s \t %s \t %s \n"location_counter,label,opcode,operand);



   }


   void check_label()
   {
       int j,flag=0;
       for(j=0;j<label_count;j++)
       {
           if(strcmp(label,project_symtab[j].label)==0)
           {
               project_symtab[j]=-1;
               flag=1;
               break;
           }
           if(flag==0)
           {
               strcpy(project_symtab[label_count].label,label);
               project_symtab[label_count++].address=location_counter;

           }

       }
   }


   void check_opcode()
   {
       int k,flag=0;

       for(k=0;k<3;k++)
       {
           if(strcmp(opcode,project_optab[k].mnemonics))
           {
               location_counter=location_counter+3;
               flag=1;
               break;
           }
           if(flag==0)
           {
               if(strcmp(opcode,"WORD")==0)
               {
                   location_counter+=3;
               }
               if(strcmp(opcode,"BYTE")==0)
               {
                   location_counter+=1;
               }
               if(strcmp(opcode,"RESB")==0)
               {
                   location_counter=location_counter+atoi(operand);
               }
               if(strcmp(opcode,"RESW")==0)
               {
                   location_counter=location_counter+3*atoi(operand);
               }

           }
       }
   }
