#ifndef __MAGIC_H__
#define __MAGIC_H__

#include <stdio.h>
#include <stdlib.h>

//Scale of matrix
#define MAX 1000
#define MIN 3

//Data matrix
static int magic[MAX][MAX];

//Show magic matrix
void ShowMagic(int n);

//Initialize the magic
void InitMagic(int n);

//Odd-number scale method of magic square
void OddMagic(int offseti, int offsetj, int min, int n);

//Double-even-number scale method of magic square(4N)
void DoubleEvenMagic(int n);

//Single-even-number scale method of magic square(4N+2)
void SingleEvenMagic(int n);

//Check input whether legal and calculate
void GetMagic(int n);

#endif
