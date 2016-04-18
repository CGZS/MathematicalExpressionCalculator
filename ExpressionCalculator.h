#ifndef EXPRESSIONCALCULATOR_H
#define EXPRESSIONCALCULATOR_H



typedef struct {
	char opear;//符号 
	int pri;//优先级
	double (*count)(double n1,double n2);//运算方法 
}Sign;

typedef struct {
	int tar;// 0数值，1符号
	union {
		double value;
		char sign;
	}data;	
}CalElementType;


#endif
