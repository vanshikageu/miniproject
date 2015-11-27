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
