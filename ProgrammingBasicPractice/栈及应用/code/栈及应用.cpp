#include <stdio.h>
#include <ctype.h>
#include <stack>
using namespace std;

#define SIZE 100

//ö�ٱ��ʽ�е�Ԫ�����ͣ� 
enum token_type{
	PLUS, MINUS, MUL, DIV, LP, RP, NUM, END, ERROR
//   +	    -     *    /   (   )  ���� ����  ���� 
//	 0      1     2    3   4   5    6    7     8
};
int cur_num = 0; //��ǰ������ 
std::stack<int> num; //�ݴ��������ջ����ʼΪ�� 
std::stack<token_type> op; //�ݴ��������ջ����ʼΪ�� 
//�ж�������������ȼ���0 С��  1 ����  
//�ñȽ���i��j���� 
int judge[6][6]={ {1,1,0,0,0,2},
				  {1,1,0,0,0,2},
				  {1,1,1,1,0,2},
				  {1,1,1,1,0,2},
				  {0,0,0,0,0,2},
				  {0,0,0,0,0,2}, };

//���ڱ��ʽ�������� 
void getValue(char *exp);
//��ȡ����
token_type getToken(char *exp);
//���м�����
int simpleCal(int num1, int num2, token_type token);
//��ջ��ȡ�����ֲ���ջ
int getNumfromStack();
//��ջ��ȡ��������Ų���ջ
token_type getOpfromStack();

int main ()
{
	char exp[SIZE];
	scanf("%s",&exp);
	printf("%s=",&exp);
	getValue(exp);
	printf("%d",getNumfromStack());
	return 0;
}

void getValue(char *exp){
	int flag = 0;
	char *p = exp;
	token_type token = getToken(p); //��ȡ���ʽ��һ��Ԫ�ص�Ԫ������ 
	while (token != END){
		if(getToken(p-1) != NUM && getToken(p-1) != RP && token == MINUS){
			flag = 1; //�����һ������ 
			p++;
		}
		else if(token == NUM){
			//��ȡ��ǰ���ֵ�int�� (�����Ƕ�λ���� 
			cur_num = 0;
			for(; isdigit(*p); p++){
				cur_num = cur_num*10 + (*p-'0') ;
			}
			if(flag == 1){
				cur_num *= -1;
				flag = 0; 
			}
			num.push(cur_num); //��ǰ������ջ 
		}
		else if(token == LP || op.empty()){
			op.push(token); //�������ջΪ�ջ�ǰ�����Ϊ�����ţ�ֱ����ջ 
			p++;
		}
		else if(judge[int(op.top())][token] == 0){
			op.push(token); //����ǰ��������ȼ���ǰ��һλ������ߣ�����ջ 
			p++;
		}
		else if(judge[int(op.top())][token] == 1){ //����ǰ��������ȼ���ǰ��һλ������ͣ����ȶ�ǰ���ʽ�����㣬�ٽ����������µķ��ŷֱ���ջ 
			cur_num = getNumfromStack(); //��ò�����ջջ�������ֲ���ջ��������ջ���ڶ�λ������λ��ջ�� 
			cur_num = simpleCal(getNumfromStack(), cur_num, getOpfromStack()); //����ջ����ǰ��λ���������㣬�����ؽ����cur_num��ͬʱ�����Ѳ�������Ĳ��������������ջ 
			num.push(cur_num); //���ڼ���Ľ��cur_num��ջ
			op.push(token); //����ɸ����ȼ������㣬�ʽ���ǰ���������ջ 
			p++;
		}
		else if(token == RP){
			int num1, num2;
			token_type OP = getOpfromStack();
			while(OP != LP){
				//ȡջ�����֣�����ջ 
				num2 = getNumfromStack();
				num1 = getNumfromStack();
				cur_num = simpleCal(num1, num2, OP);
				num.push(cur_num);
				OP = getOpfromStack();
			}
			p++;
		}
		token = getToken(p); //��ȡ���ʽ����һ��Ԫ�ص�Ԫ������ 
	}
	while (!op.empty()){
		token_type OP = getOpfromStack();
		int num1, num2;
		num2 = getNumfromStack();
		num1 = getNumfromStack();
		cur_num = simpleCal(num1, num2, OP);
		num.push(cur_num);
	}
}

token_type getToken(char *exp){
	char *p = exp;
	if (isdigit(*p)) return NUM;
	switch (*p){
		case '+': return PLUS;
		case '-': return MINUS;
		case '*': return MUL;
		case '/': return DIV;
		case '(': return LP;
		case ')': return RP;
		case '\0': return END;
		default: return ERROR;
	}
}

int simpleCal(int num1, int num2, token_type token){
	int res = 0;
	switch(token){
		case PLUS: res = num1 + num2; break; 
		case MINUS: res = num1 - num2; break;
		case MUL: res = num1 * num2; break;
		case DIV: 
			if(num2 != 0){
				res = num1 / num2;
			}
			else{
				printf("ERROR!'0' CAN NOT BE THE DENOMINATOR!\n");
			}
			break;
		default: printf("ERROR!OPERATOR IS INVALID!\n");
	}
	return res;
}

int getNumfromStack(){
	int number;
	if(!num.empty()){
		number = num.top();
		num.pop();
	}
	else{
		printf("ERROR!GET NOTHING FROM NUMBER STACK!\n");
	}
	return number;
} 

token_type getOpfromStack(){
	token_type OP;
	if(!op.empty()){
		OP = op.top();
		op.pop();
	}
	else{
		printf("ERROR!GET NOTHING FROM OPERATOR STACK!\n");
	}
	return OP;
} 
