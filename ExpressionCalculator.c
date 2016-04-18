#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayStack.h"
#include "ExpressionCalculator.h"

char firPriOper[] = {'(',')','*','/'};//�����ȼ�������� 
char secPriOper[] = {'+','-'};//�����ȼ�������� 
CalElementType calExp[100];//�������ʽ�洢 
int calExpIndex = 0;//�������ʽ���� 

int GetPri(char c) {
	int i;
	for (i = 0; i < 4; i++) {
		if (c == firPriOper[i])
			return 1;
	}
	return 0;
}


/**
*	��׺���ʽת���ɺ�׺���ʽ 
*/
void ConvetToSuffix(char * exp) {
	
	Pstack stack = CreatStack();
	CalElementType tmpData;
	 
	char* pstr = exp;
	while (pstr < (exp + strlen(exp))) {
		
		if ( (*pstr) >= '0' && (*pstr) <= '9') {//������ֵ 
			tmpData.data.value = (*pstr) - '0';
			tmpData.tar = 0;
			Push(stack,tmpData);
			printf("������ֵ\n"); 
		} else {//�������� 
			
			CalElementType ele = Pop(stack);//�ȵ���һ�� 
			double value = 0;
			int i = 1;
			
			tmpData.tar = 1;
			tmpData.data.sign = *pstr;
			
			if (ele.tar == 0) {//�������ֵ�Ž���,ջΪ�յ��� -1 
				while (ele.tar == 0) {
					value = value + i * ele.data.value;
					i = i * 10;
					ele = Pop(stack);
				}
				calExp[calExpIndex].tar = 0;
				calExp[calExpIndex ++].data.value = value;
			}
			
			
			if (ele.tar == 1 && (*pstr)!= '\0') { //����Ƿ��� 
				
				if (GetPri(ele.data.sign) >= GetPri(*pstr) && (ele.data.sign != '(')
					&& (ele.data.sign != ')') && (*pstr != '(') && (*pstr != ')'))
				{
					calExp[calExpIndex ++] = ele;
					Push(stack,tmpData);
				} else {
					Push(stack,ele);
					Push(stack,tmpData);
				}
				
				if ( *pstr == ')') {
					Pop(stack);//�Ȱѣ�����
					ele = Pop(stack);
					while (ele.data.sign != '(') {
						calExp[calExpIndex ++] = ele;
						ele = Pop(stack);	
					} 
				}
			}
			
			if (ele.tar == -1 && (*pstr)!= '\0') { //���ջ�ѿ� 
				tmpData.tar = 1;
				tmpData.data.sign = *pstr;
				Push(stack,tmpData);
			}	
		}
		pstr ++;
	}
	
	//�����ķ��ų�ջ
	tmpData = Pop(stack);
	while (tmpData.tar != -1) {
		calExp[calExpIndex++] = tmpData;
		tmpData = Pop(stack);	
	}
}

/**
*	�������� 
*/
double SingleCal(char c,double var1,double var2) {
	
	switch(c) {
		case '+':
			return var1 + var2;
		case '-':
			return var1 - var2;
		case '*':
			return var1 * var2;
		case '/':
			return var1 / var2;
	}
}

/*
*	�Ժ�׺���ʽ�������� 
*/
double Operation() {
	
	int i;
	Pstack stack = CreatStack();
	double var1,var2;
	CalElementType result;
	for (i = 0; i < calExpIndex; i ++) {
		
		if (calExp[i].tar == 0) {//�������ֵ����ջ 
			Push(stack,calExp[i]);		
		} else {
			var2 = Pop(stack).data.value;
			var1 = Pop(stack).data.value;
			result.tar = 0;
			result.data.value = SingleCal(calExp[i].data.sign,var1,var2);
			Push(stack,result);//�ѽ����ջ	
			//printf("\nvar1:%.2f , var2:%.2f\n",var1,var2);
		}
	}
	
	return Pop(stack).data.value;
}

/**
*	������
*	���ô˺�����ȡ��� 
*/
double CalExp(char * str) {
	calExpIndex = 0;
	ConvetToSuffix(str);
	return Operation();
}

int main() {
	
	printf("\n%.2f\n",CalExp("20+9*2"));
	printf("\n%.2f\n",CalExp("(20+9)*(2/2)+1"));
		
	return 0;
}
