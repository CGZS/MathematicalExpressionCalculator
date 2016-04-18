#include "ArrayStack.h"


/**
*	错误处理信息 
*/
int ERROR = 0;
const ElementType error = {-1,0};

/**
*	创建空栈 
*/
Pstack CreatStack() {
	Pstack stack = (Pstack)malloc(sizeof(Stack));
	stack -> top = -1;
	return stack;
}

/**
*	判断该栈是已满
*	若满返回1，未满返回0 
*/
int IsFull(Pstack stack) {
	return stack->top == MAX_SIZE -1;
}


/**
*	判断该栈是为空 
*	若为空返回1，非空返回0 
*/
int IsEmpty(Pstack stack) {
	return stack->top == -1;
}

/**
*	入栈
*   成功返回0，失败返回 -1 
*/
int Push (Pstack stack, ElementType x) {
	if (IsFull(stack)){//栈满 
		printf("栈已满\n"); 
		return -1;
	}
	stack->data[stack->top + 1] = x;
	stack->top ++;
	return 0;
}

/**
*	出栈 
*/ 
ElementType Pop(Pstack stack) {
	
	ElementType item;
	if (IsEmpty(stack) == 1) {//栈为空 
		 printf("栈为空\n");
		 ERROR = -1;
		 return error;
	}
	item = stack->data[stack->top];
	stack->top --;
	ERROR = 0;
	return item;
}

/**
*	查看栈顶的元素，但并不删除 
*/
ElementType CheckTop(Pstack stack) {
	if (IsEmpty(stack) == 1 ) {
		printf("栈为空\n");
		ERROR = -1;
		return error;
	}
	ERROR = 0;
	return stack->data[stack->top]; 		
}

