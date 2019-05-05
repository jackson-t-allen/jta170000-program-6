/*
 * Filename     .cc
 * Date         1//2019
 * Author       Jackson Allen
 * Email        jta170000@utdallas.edu
 * Course No.   CS 3377.502 Spring 2019
 * Version      1.0
 * Copyright    2019, All Rights Reserved
 *
 * Description  
 *              
 *              
*/


#ifndef PROGRAM_6
#define PROGRAM_6
#include "cdk.h"

class BinaryFileHeader
{
 public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

const int maxRecordStringLength = 25;

class BinaryFileRecord
{
 public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};


void fillMatrix(CDKMATRIX*);

#endif
