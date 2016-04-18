#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayStack.h"
#include "ExpressionCalculator.h"

char firPriOper[] = {'(',')','*','/'};//高优先级运算符号 
char secPriOper[] = {'+','-'};//低优先级运算符号 
CalElementType calExp[100];//后续表达式存储 
int calExpIndex = 0;//后续表达式索引 

int GetPri(char c) {
	int i;
	for (i = 0; i < 4; i++) {
		if (c == firPriOper[i])
			return 1;
	}
	return 0;
}


/**
*	中缀表达式转换成后缀表达式 
*/
void ConvetToSuffix(char * exp) {
	
	Pstack stack = CreatStack();
	CalElementType tmpData;
	 
	char* pstr = exp;
	while (pstr < (exp + strlen(exp))) {
		
		if ( (*pstr) >= '0' && (*pstr) <= '9') {//遇到数值 
			tmpData.data.value = (*pstr) - '0';
			tmpData.tar = 0;
			Push(stack,tmpData);
			printf("遇到数值\n"); 
		} else {//遇到符号 
			
			CalElementType ele = Pop(stack);//先弹出一个 
			double value = 0;
			int i = 1;
			
			tmpData.tar = 1;
			tmpData.data.sign = *pstr;
			
			if (ele.tar == 0) {//如果是数值才进行,栈为空的是 -1 
				while (ele.tar == 0) {
					value = value + i * ele.data.value;
					i = i * 10;
					ele = Pop(stack);
				}
				calExp[calExpIndex].tar = 0;
				calExp[calExpIndex ++].data.value = value;
			}
			
			
			if (ele.tar == 1 && (*pstr)!= '\0') { //如果是符号 
				
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
					Pop(stack);//先把）弹出
					ele = Pop(stack);
					while (ele.data.sign != '(') {
						calExp[calExpIndex ++] = ele;
						ele = Pop(stack);	
					} 
				}
			}
			
			if (ele.tar == -1 && (*pstr)!= '\0') { //如果栈已空 
				tmpData.tar = 1;
				tmpData.data.sign = *pstr;
				Push(stack,tmpData);
			}	
		}
		pstr ++;
	}
	
	//将最后的符号出栈
	tmpData = Pop(stack);
	while (tmpData.tar != -1) {
		calExp[calExpIndex++] = tmpData;
		tmpData = Pop(stack);	
	}
}

/**
*	单步运算 
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
*	对后缀表达式进行运算 
*/
double Operation() {
	
	int i;
	Pstack stack = CreatStack();
	double var1,var2;
	CalElementType result;
	for (i = 0; i < calExpIndex; i ++) {
		
		if (calExp[i].tar == 0) {//如果是数值，入栈 
			Push(stack,calExp[i]);		
		} else {
			var2 = Pop(stack).data.value;
			var1 = Pop(stack).data.value;
			result.tar = 0;
			result.data.value = SingleCal(calExp[i].data.sign,var1,var2);
			Push(stack,result);//把结果入栈	
			//printf("\nvar1:%.2f , var2:%.2f\n",var1,var2);
		}
	}
	
	return Pop(stack).data.value;
}

/**
*	主函数
*	调用此函数获取结果 
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
