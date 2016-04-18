#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include "ExpressionCalculator.h"

/*
*	存储类型及长度 
*/
#define 	MAX_SIZE 50
#define ElementType CalElementType

typedef struct {
	ElementType data[MAX_SIZE];
	int top;
}Stack;

typedef Stack * Pstack;

Pstack CreatStack();
int IsFull(Pstack stack);
int IsEmpty(Pstack stack);
int Push (Pstack stack, ElementType x);
ElementType Pop(Pstack stack);
ElementType CheckTop(Pstack stack);

#endif

