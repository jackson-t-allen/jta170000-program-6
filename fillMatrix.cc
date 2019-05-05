/*
 * Filename        fillMatrix.cc
 * Date            5/5/19
 * Author          Jackson Allen
 * Email           jackson.allen@utdallas.edu
 * Course          CS 3377.502, 2019 Spring
 * Version         1.0
 * Copyright 2019, All Rights Reserved
 *
 * Description
 *           Functions to read from bin file
 *            into CDK matrix.
 */


#include "cdk.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "program6.h"

using namespace std;


void reverse(char*);

void toHexR(unsigned int i, char* str)
{
  if (i==0)
    {
      str[0]='\0';
      return;
    }
  char* map="0123456789ABCDEF";
  str[0]=map[i%16];
  toHexR(i/16,str+1);
}

void toHex(int i,char* str)
{
  str[0]='0';
  str[1]='x';
  char* num = new char[20];
  toHexR(i,num);
  reverse(num);
  strcat(str,num);
}

void reverse(char *str)
{
  int len = strlen(str);
  char swap;

  for (int i = 0; i < len/2; i++)
    {
      swap = str[i];
      str[i] = str[len-i-1];
      str[len-i-1] = swap;
    }
}

void fillMatrix(CDKMATRIX *myMatrix)
{
  //open infile
  ifstream infile("cs3377.bin",ios::in | ios::binary);

  char* currentString = new char[20];
  char* contentString = new char[20];
  BinaryFileHeader *head = new BinaryFileHeader;
  BinaryFileRecord *record = new BinaryFileRecord;



  //Header 1
  infile.read((char*)head,sizeof(BinaryFileHeader));

  toHex(head->magicNumber,contentString);
  
  strcpy(currentString,"Magic: ");
  strcat(currentString,contentString);
  contentString[19]='\0';
  setCDKMatrixCell(myMatrix,1,1,currentString);

  //Header 2
  strcpy(currentString,"Version: ");
  strcpy(contentString,to_string(head->versionNumber).c_str());
  strcat(currentString,contentString);
  contentString[19]='\0';
  setCDKMatrixCell(myMatrix,1,2,currentString);

  //Header 3
  strcpy(currentString,"NumRecords: ");
  strcpy(contentString,to_string(head->numRecords).c_str());
  strcat(currentString,contentString);
  contentString[19]='\0';
  setCDKMatrixCell(myMatrix,1,3,currentString);

    for (int i = 0; i < 4; i++)
    {
      infile.read((char*)&(record->strLength),1);
      infile.read((char*)(record->stringBuffer),25);

  strcpy(currentString,"strlen: ");
  strcpy(contentString,to_string(record->strLength).c_str());
  strcat(currentString,contentString);
  contentString[19]='\0';
  setCDKMatrixCell(myMatrix,i+2,1,currentString);
  
  strcpy(currentString,record->stringBuffer);
  setCDKMatrixCell(myMatrix,i+2,2,currentString);
  
  }
}
