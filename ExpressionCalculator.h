#ifndef EXPRESSIONCALCULATOR_H
#define EXPRESSIONCALCULATOR_H



typedef struct {
	char opear;//���� 
	int pri;//���ȼ�
	double (*count)(double n1,double n2);//���㷽�� 
}Sign;

typedef struct {
	int tar;// 0��ֵ��1����
	union {
		double value;
		char sign;
	}data;	
}CalElementType;


#endif
