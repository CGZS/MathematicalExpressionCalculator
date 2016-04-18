#include "ArrayStack.h"


/**
*	��������Ϣ 
*/
int ERROR = 0;
const ElementType error = {-1,0};

/**
*	������ջ 
*/
Pstack CreatStack() {
	Pstack stack = (Pstack)malloc(sizeof(Stack));
	stack -> top = -1;
	return stack;
}

/**
*	�жϸ�ջ������
*	��������1��δ������0 
*/
int IsFull(Pstack stack) {
	return stack->top == MAX_SIZE -1;
}


/**
*	�жϸ�ջ��Ϊ�� 
*	��Ϊ�շ���1���ǿշ���0 
*/
int IsEmpty(Pstack stack) {
	return stack->top == -1;
}

/**
*	��ջ
*   �ɹ�����0��ʧ�ܷ��� -1 
*/
int Push (Pstack stack, ElementType x) {
	if (IsFull(stack)){//ջ�� 
		printf("ջ����\n"); 
		return -1;
	}
	stack->data[stack->top + 1] = x;
	stack->top ++;
	return 0;
}

/**
*	��ջ 
*/ 
ElementType Pop(Pstack stack) {
	
	ElementType item;
	if (IsEmpty(stack) == 1) {//ջΪ�� 
		 printf("ջΪ��\n");
		 ERROR = -1;
		 return error;
	}
	item = stack->data[stack->top];
	stack->top --;
	ERROR = 0;
	return item;
}

/**
*	�鿴ջ����Ԫ�أ�������ɾ�� 
*/
ElementType CheckTop(Pstack stack) {
	if (IsEmpty(stack) == 1 ) {
		printf("ջΪ��\n");
		ERROR = -1;
		return error;
	}
	ERROR = 0;
	return stack->data[stack->top]; 		
}

