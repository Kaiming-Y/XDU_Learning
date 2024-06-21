#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX 128 //最大容纳：4位数*32格=128位 （127位数字以及1位符号 ） 

struct number{
	int num[33]; //整型数组中每个元素表示4位（实质是该大位数的绝对值） 
	int cnt; //记录占用了几个num数组格子 
	char numstr[MAX+2]; //以字符串numstr读取和输出大位数
	int sign; //sign表示数字的符号--0为正数 1为负数 
	int length; //length表示该数字的长度 
};  //表示数字的结构体 

int main ()
{
	int i=0,j=0,k=0,flag=0;
	struct number x,y,sum,dif;  //数字x和y 和sum(绝对值) 差dif(绝对值) 
	
	memset(&x,0,sizeof(struct number));
	memset(&y,0,sizeof(struct number));
	memset(&sum,0,sizeof(struct number));
	memset(&dif,0,sizeof(struct number));
	
	//以字符串形式读入大位数： （采用fgets更安全） 
	puts("请输入X的值：");
	fgets(x.numstr,MAX+2,stdin);
	puts("请输入y的值："); 
	fgets(y.numstr,MAX+2,stdin);
	
	//计算字符串长度： 
	
	x.length=strlen(x.numstr);
	y.length=strlen(y.numstr);
	
	//移除fgets录入的换行符： 
	
	if(x.numstr[x.length-1]=='\n'){
		x.numstr[x.length-1]='\0';
		x.length--; //相应的数字长度-1 
	}
	if(y.numstr[y.length-1]=='\n'){
		y.numstr[y.length-1]='\0';
		y.length--; //相应的数字长度-1 
	}
	
	//判定该数字的符号：
	
	if(x.numstr[0]=='-'){
		x.sign=1; //记录该数的符号为负 
		//删除负号： 
		for(i=1;i<x.length;i++){
			x.numstr[i-1]=x.numstr[i]; 
		}
		x.numstr[x.length-1]='\0';
		x.length--; //相应的数字长度-1
	}
	if(y.numstr[0]=='-'){
		y.sign=1; //记录该数的符号为负 
		//删除负号： 
		for(i=1;i<y.length;i++){
			y.numstr[i-1]=y.numstr[i]; 
		}
		y.numstr[y.length-1]='\0';
		y.length--; //相应的数字长度-1
	}
	
	//把字符串换成整型数组： 
	
	for(i=x.length-1;i>=0;x.cnt++){
		//将每4位放入一个数组元素中，若放满4位或每一位数字已放置完毕则结束： 
		for(k=0;k<4&&i>=0;k++){
			x.num[x.cnt]+=(x.numstr[i--]-48)*pow(10,k);
		}
	}
	
	
	for(i=y.length-1;i>=0;y.cnt++){
		//将每4位放入一个数组元素中，若放满4位或每一位数字已放置完毕则结束： 
		for(k=0;k<4&&i>=0;k++){
			y.num[y.cnt]+=(y.numstr[i--]-48)*pow(10,k);
		}
	}
	
	int bigger = x.cnt > y.cnt ? x.cnt : y.cnt; //记录表示X和Y的整型数组占用元素更多者的元素数量 
	
	//对大位数X和Y绝对值进行加减计算 ： 
	
	//|X|+|Y|:
	
	for(i=0;i<x.cnt || i<y.cnt;i++){
		sum.num[i]+=(x.num[i]+y.num[i]); //计算x与y之和 
		sum.cnt++; //每求和数组的一个格子记录一次 
		//判定需要进位的情况： 
		if(sum.num[i]/(int)pow(10,4)==1) {
			sum.num[i+1]++;
			sum.num[i]-=(int)pow(10,4);			
			//当计算到两个数字中较大者的整型数组最后一格时，若也需进位，则和的结果格子加1： 
			if(i==bigger-1 || (x.cnt==y.cnt && i==x.cnt-1) ){
				sum.cnt++; 
			}
		}
	}
	//将整型数组转为字符串：
	for(i=sum.cnt-1,j=0;i>=0;i--){
		for(k=3;k>=0;k--){
			if(i!=sum.cnt-1){
				sum.numstr[j++]=sum.num[i]/(int)pow(10,k)+'0';
				sum.num[i]%=(int)pow(10,k);
			}
			else if(i==sum.cnt-1){
				if(sum.num[i]/(int)pow(10,k)!=0) flag=1;
				if(flag==1){
					sum.numstr[j++]=sum.num[i]/(int)pow(10,k)+'0';
					sum.num[i]%=(int)pow(10,k);
				}
			}
		}
	}
	sum.numstr[j]='\0';
	flag=0;
	
	//|X|-|Y|:
	
	//根据x和y所占整型数组格数，判断二者大小： 
	int isZero = 0;
	if(x.cnt==y.cnt){
		//去寻找二者数组元素不相等的格子 
		for(i=x.cnt-1;i>=0;i--){
			if(x.num[i]==y.num[i]) continue;
			if(x.num[i]<y.num[i]){
				isZero = -1;
				goto YGreaterThanX;
			}
			else if(x.num[i]>y.num[i]){
				isZero = 1;
				goto XGreaterThanY;
			} 
		}
	}
	else if(x.cnt>y.cnt) goto XGreaterThanY;
	else if(x.cnt<y.cnt) goto YGreaterThanX;
	if(isZero == 0){
		dif.num[0] = 0;
		dif.cnt = 1;
		dif.length = 1;
		dif.sign = 0;
		dif.numstr[0] = '0';
		dif.numstr[1] = '\0';
		goto Result;
	}
	//当x>y时：（x格子数>y格子数  或  x格子数=y格子数时 x某格子元素>y某格子元素） 
	XGreaterThanY: 	
		for(i=0;i<x.cnt || i<y.cnt;i++){
			//判定需要借位的情况： 
			if(x.num[i]<y.num[i]){
				x.num[i+1]--;
				x.num[i]+=(int)pow(10,4); 
			}
			dif.num[i]=x.num[i]-y.num[i]; //计算x与y之差 
			if (dif.num[i]!=0) dif.cnt++;
		}
		goto XminusYfinished; //避免运行y>x的情况 
	//当y>x时： （x格子数<y格子数  或  x格子数=y格子数时 x某格子元素<y某格子元素） 
	YGreaterThanX:
		dif.sign=1; //标记|X|-|Y|为负 
		for(i=0;i<x.cnt || i<y.cnt;i++){
			//判定需要借位的情况：
			if(y.num[i]<x.num[i]){
				y.num[i+1]--;
				y.num[i]+=(int)pow(10,4);
			}
			dif.num[i]=y.num[i]-x.num[i]; //计算y与x之差
			if (dif.num[i]!=0) dif.cnt++;
		}
	XminusYfinished:
		//将整型数组转为字符串：
		for(i=dif.cnt-1,j=0;i>=0;i--){
			for(k=3;k>=0;k--){
				if(i!=dif.cnt-1){
					dif.numstr[j++]=dif.num[i]/(int)pow(10,k)+'0';
					dif.num[i]%=(int)pow(10,k);
				}
				else if(i==dif.cnt-1){
					if(dif.num[i]/(int)pow(10,k)!=0) flag=1;
					if(flag==1){
						dif.numstr[j++]=dif.num[i]/(int)pow(10,k)+'0';
						dif.num[i]%=(int)pow(10,k);
					}
				}
			}
		}
		dif.numstr[j]='\0';
		
	
	Result:
	//输出X+Y的结果：
	
	printf("X+Y="); 
	if(x.sign==0){
		if(y.sign==0){
			//|X|+|Y|
			fputs(sum.numstr,stdout);
		}
		else if(y.sign==1){
			//|X|-|Y|
			if(dif.sign==1){
				printf("-");
			}
			fputs(dif.numstr,stdout);
		}	
	}
	else if(x.sign==1){
		if(y.sign==0){
			//|Y|-|X|
			if(dif.sign==0){
				printf("-");
			}
			fputs(dif.numstr,stdout);
		}
		else if(y.sign==1){
			//-|X|-|Y|
			printf("-");
			fputs(sum.numstr,stdout);
		}
	}
	printf("\n");
	 
	//输出 X-Y的结果：
	
	printf("X-Y=");
	if(x.sign==0){
		if(y.sign==0){
			//|X|-|Y|
			if(dif.sign==1){
				printf("-");
			}
			fputs(dif.numstr,stdout);		
		}
		else if(y.sign==1){
			//|X|+|Y|
			fputs(sum.numstr,stdout);
		}
	}
	else if(x.sign==1){
		if(y.sign==0){
			//-|X|-|Y|
			printf("-");
			fputs(sum.numstr,stdout);
		}
		else if(y.sign==1){
			//|Y|-|X|
			if(dif.sign==0){
				printf("-");
			}
			fputs(dif.numstr,stdout);
		}
	}
	printf("\n"); 
	 
	return 0;
}
