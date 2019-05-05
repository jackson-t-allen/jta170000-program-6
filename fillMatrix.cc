

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

  unsigned int intIn;


  //Header 1
  infile.read((char*)&intIn,sizeof(int));

  toHex(intIn,contentString);
  
  strcpy(currentString,"Magic: ");
  strcat(currentString,contentString);
  contentString[19]='\0';
  setCDKMatrixCell(myMatrix,1,1,currentString);

  //Header 2
  infile.read((char*)&intIn,sizeof(int));
  strcpy(currentString,"Version: ");
  strcpy(contentString,to_string(intIn).c_str());
  strcat(currentString,contentString);
  contentString[19]='\0';
  setCDKMatrixCell(myMatrix,1,2,currentString);

  //Header 3
  infile.read((char*)&intIn,sizeof(int));
  strcpy(currentString,"NumRecords: ");
  strcpy(contentString,to_string(intIn).c_str());
  strcat(currentString,contentString);
  contentString[19]='\0';
  setCDKMatrixCell(myMatrix,1,3,currentString);



  
}
