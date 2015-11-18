void pass1()
{
    FILE *fp1,*fp2;

    fp1=fopen("inputfile.txt","r");
    fp2=fopen("intermediatefile.txt","w");
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
  checkLabel(&labelCount,locationCounter);
}
printf("%x\t%s\t%s\t%s\n",locationCounter,label,opcode,operand);
fprintf(fp2,"%x\t%s\t%s\t%s\n",locationCounter,label,opcode,operand);

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
