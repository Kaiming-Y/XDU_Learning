#include <stdio.h>
#include <ctype.h>
#include <stack>
using namespace std;

#define SIZE 100

//枚举表达式中的元素类型： 
enum token_type{
	PLUS, MINUS, MUL, DIV, LP, RP, NUM, END, ERROR
//   +	    -     *    /   (   )  数字 结束  错误 
//	 0      1     2    3   4   5    6    7     8
};
int cur_num = 0; //当前的数字 
std::stack<int> num; //暂存操作数的栈，初始为空 
std::stack<token_type> op; //暂存运算符的栈，初始为空 
//判断两运算符的优先级：0 小于  1 大于  
//该比较是i对j而言 
int judge[6][6]={ {1,1,0,0,0,2},
				  {1,1,0,0,0,2},
				  {1,1,1,1,0,2},
				  {1,1,1,1,0,2},
				  {0,0,0,0,0,2},
				  {0,0,0,0,0,2}, };

//对于表达式进行运算 
void getValue(char *exp);
//获取符号
token_type getToken(char *exp);
//进行简单运算
int simpleCal(int num1, int num2, token_type token);
//从栈中取出数字并退栈
int getNumfromStack();
//从栈中取出运算符号并退栈
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
	token_type token = getToken(p); //获取表达式第一个元素的元素类型 
	while (token != END){
		if(getToken(p-1) != NUM && getToken(p-1) != RP && token == MINUS){
			flag = 1; //标记有一个负数 
			p++;
		}
		else if(token == NUM){
			//获取当前数字的int型 (可能是多位数） 
			cur_num = 0;
			for(; isdigit(*p); p++){
				cur_num = cur_num*10 + (*p-'0') ;
			}
			if(flag == 1){
				cur_num *= -1;
				flag = 0; 
			}
			num.push(cur_num); //当前数字入栈 
		}
		else if(token == LP || op.empty()){
			op.push(token); //若运算符栈为空或当前运算符为左括号，直接入栈 
			p++;
		}
		else if(judge[int(op.top())][token] == 0){
			op.push(token); //若当前运算符优先级比前面一位运算符高，则入栈 
			p++;
		}
		else if(judge[int(op.top())][token] == 1){ //若当前运算符优先级比前面一位运算符低，则先对前面的式子运算，再将运算结果和新的符号分别入栈 
			cur_num = getNumfromStack(); //获得操作数栈栈顶的数字并将栈顶数字退栈，第二位的数字位于栈顶 
			cur_num = simpleCal(getNumfromStack(), cur_num, getOpfromStack()); //对于栈顶的前两位数进行运算，并返回结果给cur_num，同时对于已参与运算的操作数和运算符退栈 
			num.push(cur_num); //对于计算的结果cur_num入栈
			op.push(token); //已完成高优先级的运算，故将当前的运算符入栈 
			p++;
		}
		else if(token == RP){
			int num1, num2;
			token_type OP = getOpfromStack();
			while(OP != LP){
				//取栈顶数字，并退栈 
				num2 = getNumfromStack();
				num1 = getNumfromStack();
				cur_num = simpleCal(num1, num2, OP);
				num.push(cur_num);
				OP = getOpfromStack();
			}
			p++;
		}
		token = getToken(p); //获取表达式的下一个元素的元素类型 
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
