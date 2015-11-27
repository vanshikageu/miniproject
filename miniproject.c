#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

struct operationTable
{
char mnemonics[50];
char code[50];
}optab[50]={{"LDA","00"},{"J","3C"},{"STA","0C"},{"LDCH","50"},{"STCH","54"},{"RSUB","4C"},{"JSUB","48"},{"JEQ","30"},{"COMP","28"},{"ADD","18"},
{"JLT","38"},{"LDB","68"},{"LDF","70"},{"LDL","08"},{"LDT","74"},{"LDX","04"},{"STL","14"},{"STX","10"}};

struct symbolTable
{
    int address;
    char labelName[50];
}symtab[100];


char opcode[100],operand[100],label[100],programName[20];
char temp[50];
int startAddress=0,locationCounter=0,programLength=0,labelCount=0;


  unsigned long HexConvertToDecimal(char Hex[])
   {
    char *HexString;
    int length=0;
    const int base=16; //base of HEX
    unsigned long decimalNumber=0;
    int k;

    for(HexString=Hex;*HexString!='\0';HexString++)
    {
        length++;
    }
    HexString=Hex;

    for(k=0;*HexString!='\0' && k<length;k++,HexString++)
    {
        if(*HexString>=48 && *HexString<=57)
        {
            decimalNumber+=(((int)(*HexString))-48)*pow(base,length-k-1);
        }
        else if((*HexString>=65 && *HexString<=70))
        {
            decimalNumber+=(((int)(*HexString))-55) * pow(base,length-k-1);
        }
        else if(*HexString>=97 && *HexString<=102)
        {
            decimalNumber+=(((int)(*HexString))-87)*pow(base,length-k-1);
        }
        else
        {
            printf("INVALID HEXADECIMAL NUMBER\n");
        }
    }

    return decimalNumber;
}

checkLabel(int *lc,int locationCounter)
{
    int temp,i;
    temp=(*lc);
    for(i=0;i<temp;i++)
    {
        if(strcmp(symtab[i].labelName,label)==0)
        {
            printf("no label");
            exit(0);
        }
    }

(*lc)=(*lc)+1;
strcpy(symtab[temp].labelName,label);
symtab[temp].address=locationCounter;
}


checkOpcode(int *locationCounter)
{
int i,operandLength=0,flag=0;
for(i=0;i<18;i++)
{
if(strcmp(opcode,optab[i].mnemonics)==0)
{
    flag=1;
}
}

if(flag!=1)
{
 if(strcmp(opcode,"WORD")==0)
(*locationCounter)=(*locationCounter)+3;
  else if(strcmp(opcode,"RESW")==0)
{
(*locationCounter)=(*locationCounter)+(3*(atoi(operand)));
}
 else if(strcmp(opcode,"RESB")==0)
{
itoa(atoi(operand),temp,10);
(*locationCounter)=(*locationCounter)+atoi(temp);
}
else if(strcmp(opcode,"BYTE")==0)
{
    operandLength=strlen(operand);
    if(operand[0]=='c')
    {
        (*locationCounter)=(*locationCounter)+(operandLength-3);
    }

    else
    {
     for(i=2;operand[i]!='\0';i++)
     {
         flag++;
     }
     (*locationCounter)=(*locationCounter)+(flag/2);
    }
}
else
{
    printf("error");
    exit(0);
}
}
else
{
    (*locationCounter)+=3;
}
}

 void pass1()
 {

    FILE *fp1,*fp2,*sym;
    fp1=fopen("inputfile.txt","r");
    fp2=fopen("intermediatefile.txt","w");
    sym=fopen("symtab.txt","w");
    fscanf(fp1,"%s%s%s",label,opcode,operand);

    if(strcmp(opcode,"START")==0)
    {
    startAddress=HexConvertToDecimal(operand);
    locationCounter=startAddress;
    strcpy(programName,label);
    printf("\t%s\t%s\t%s\n",label,opcode,operand);
    fprintf(fp2,"\t%s\t%s\t%s\n",label,opcode,operand);
    fscanf(fp1,"%s%s%s",label,opcode,operand);
}
    while(strcmp(opcode,"END")!=0)
{
  if(strcmp(label,"*")!=0)
{
    fprintf(sym,"\n%04x\t%s\n",locationCounter,label);
  checkLabel(&labelCount,locationCounter);
}
printf("%04x\t%s\t%s\t%s\n",locationCounter,label,opcode,operand);
fprintf(fp2,"%04x\t%s\t%s\t%s\n",locationCounter,label,opcode,operand);

if(strcmp(opcode,"*")!=0)
{
checkOpcode(&locationCounter);
}
fscanf(fp1,"%s%s%s",label,opcode,operand);
}
printf("*\t%s\t%s\t%s\n",label,opcode,operand);
fprintf(fp2,"*\t%s\t%s\t%s\n",label,opcode,operand);
fclose(fp1);
fclose(fp2);
}
void pass2()
{
    FILE *fp3,*fp4;
    char actualAddress[50],address[40],record[50],byteValue[50],charValue[50],textValue[50],op[50],xy[10],val[20];
    int byteLen=0,recordLength,value,top;
     int i=0,j=0,k=0,m=0,p=0,char_value[50];

    fp3=fopen("intermediatefile.txt","r");
    fp4=fopen("objectfile.txt","w");

    fscanf(fp3,"%s%s%s",label,opcode,operand);

    if(strcmp(opcode,"START")==0)
    {
            printf("OBJECT FILE \n\n");
            printf("HEADER RECORD\n ");
            printf(" H^%s^%06x^%06x\n",programName,startAddress,programLength);
            fprintf(fp4,"\n H^%s^%06x^%06x\n",programName,startAddress,programLength);
            fscanf(fp3,"%s%s%s%s",address,label,opcode,operand);
    }

    printf("TEXT RECORD\n");
   while(strcmp(opcode,"END")!=0)
   {
       recordLength=0;
       record[0]='\0';
       strcpy(actualAddress,address);
        while((recordLength<30)&&(strcmp(opcode,"END")!=0))
       {
           for(i=0;i<18;i++)
           {
               if(strcmp(opcode,optab[i].mnemonics)==0)
               {
                   recordLength+=3;
                   strcat(record,"^");
                   strcpy(op,optab[i].code);
                   strcat(record,op);
                if(strcmp(operand,"*")!=0)
                {
                     for(j=0;j<labelCount;j++)
                     {
                           if(strcmp(operand,symtab[j].labelName)==0)
                           {
                               value=symtab[j].address;
                               itoa(value,textValue,16);
                            strcat(record,textValue);
                           }
                     }
                }
                   else
                   {
                       strcat(record,"0000");
                   }
          fscanf(fp3,"%s%s%s%s",address,label,opcode,operand);
               }
           }
                 if(strcmp(opcode,"WORD")==0)
               {
                   int x;
                   x=atoi(operand);
                   itoa(x,xy,16);
                   top=strlen(xy);
                   j=0;
                   for(i=0;i<(6-top);i++)
                   {
                     val[j]='0';
                      j++;
                    }
                    recordLength+=3;
                   strcat(val,xy);
                   strcat(record,"^");
                   strcat(record,val);


                   fscanf(fp3,"%s%s%s%s",address,label,opcode,operand);
               }
                 if(strcmp(opcode,"BYTE")==0)
               {
                   byteLen=strlen(operand);
                   byteLen-=3;
                   strcat(record,"^");
                      if(operand[0]=='c')
                      {
                         for(k=2,m=0;k<(byteLen+2);m++,k++)
                         {
                        char_value[m]=operand[k];
                        itoa(char_value[m],charValue,16);
                        strcat(record,charValue);
                         }
                       recordLength+=m;
                     }
                      else
                      {

                            for(m=2;m<(byteLen+2);m++)
                            {
                             byteValue[p]=operand[m];
                              p++;
                            }
                            if(p%2==0)
                            {
                              recordLength+=p;
                            }
                            else
                            {
                              recordLength+=p+1;
                            }
                           strcat(record,byteValue);
                      }
                      fscanf(fp3,"%s%s%s%s",address,label,opcode,operand);
                }
            if((strcmp(opcode,"RESW")==0)||(strcmp(opcode,"RESB")==0))
            {
                fscanf(fp3,"%s%s%s%s",address,label,opcode,operand);
                   break;
            }

       }

       printf("T^%06s^%02x%s\n",actualAddress,recordLength,record);
       fprintf(fp4,"T^%06s^%02x%s\n",actualAddress,recordLength,record);
   }

       printf("END RECORD\n");
       printf("E^%06x\n",startAddress);
       fprintf(fp4,"E^%06x\n",startAddress);
       fclose(fp3);
       fclose(fp4);
}

int main()
{
    pass1();
    programLength=locationCounter-startAddress;
    printf("\nprogram length is =%06x\n\n",programLength);
    pass2();
    return(0);
}












