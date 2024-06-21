#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX 128 //������ɣ�4λ��*32��=128λ ��127λ�����Լ�1λ���� �� 

struct number{
	int num[33]; //����������ÿ��Ԫ�ر�ʾ4λ��ʵ���Ǹô�λ���ľ���ֵ�� 
	int cnt; //��¼ռ���˼���num������� 
	char numstr[MAX+2]; //���ַ���numstr��ȡ�������λ��
	int sign; //sign��ʾ���ֵķ���--0Ϊ���� 1Ϊ���� 
	int length; //length��ʾ�����ֵĳ��� 
};  //��ʾ���ֵĽṹ�� 

int main ()
{
	int i=0,j=0,k=0,flag=0;
	struct number x,y,sum,dif;  //����x��y ��sum(����ֵ) ��dif(����ֵ) 
	
	memset(&x,0,sizeof(struct number));
	memset(&y,0,sizeof(struct number));
	memset(&sum,0,sizeof(struct number));
	memset(&dif,0,sizeof(struct number));
	
	//���ַ�����ʽ�����λ���� ������fgets����ȫ�� 
	puts("������X��ֵ��");
	fgets(x.numstr,MAX+2,stdin);
	puts("������y��ֵ��"); 
	fgets(y.numstr,MAX+2,stdin);
	
	//�����ַ������ȣ� 
	
	x.length=strlen(x.numstr);
	y.length=strlen(y.numstr);
	
	//�Ƴ�fgets¼��Ļ��з��� 
	
	if(x.numstr[x.length-1]=='\n'){
		x.numstr[x.length-1]='\0';
		x.length--; //��Ӧ�����ֳ���-1 
	}
	if(y.numstr[y.length-1]=='\n'){
		y.numstr[y.length-1]='\0';
		y.length--; //��Ӧ�����ֳ���-1 
	}
	
	//�ж������ֵķ��ţ�
	
	if(x.numstr[0]=='-'){
		x.sign=1; //��¼�����ķ���Ϊ�� 
		//ɾ�����ţ� 
		for(i=1;i<x.length;i++){
			x.numstr[i-1]=x.numstr[i]; 
		}
		x.numstr[x.length-1]='\0';
		x.length--; //��Ӧ�����ֳ���-1
	}
	if(y.numstr[0]=='-'){
		y.sign=1; //��¼�����ķ���Ϊ�� 
		//ɾ�����ţ� 
		for(i=1;i<y.length;i++){
			y.numstr[i-1]=y.numstr[i]; 
		}
		y.numstr[y.length-1]='\0';
		y.length--; //��Ӧ�����ֳ���-1
	}
	
	//���ַ��������������飺 
	
	for(i=x.length-1;i>=0;x.cnt++){
		//��ÿ4λ����һ������Ԫ���У�������4λ��ÿһλ�����ѷ������������� 
		for(k=0;k<4&&i>=0;k++){
			x.num[x.cnt]+=(x.numstr[i--]-48)*pow(10,k);
		}
	}
	
	
	for(i=y.length-1;i>=0;y.cnt++){
		//��ÿ4λ����һ������Ԫ���У�������4λ��ÿһλ�����ѷ������������� 
		for(k=0;k<4&&i>=0;k++){
			y.num[y.cnt]+=(y.numstr[i--]-48)*pow(10,k);
		}
	}
	
	int bigger = x.cnt > y.cnt ? x.cnt : y.cnt; //��¼��ʾX��Y����������ռ��Ԫ�ظ����ߵ�Ԫ������ 
	
	//�Դ�λ��X��Y����ֵ���мӼ����� �� 
	
	//|X|+|Y|:
	
	for(i=0;i<x.cnt || i<y.cnt;i++){
		sum.num[i]+=(x.num[i]+y.num[i]); //����x��y֮�� 
		sum.cnt++; //ÿ��������һ�����Ӽ�¼һ�� 
		//�ж���Ҫ��λ������� 
		if(sum.num[i]/(int)pow(10,4)==1) {
			sum.num[i+1]++;
			sum.num[i]-=(int)pow(10,4);			
			//�����㵽���������нϴ��ߵ������������һ��ʱ����Ҳ���λ����͵Ľ�����Ӽ�1�� 
			if(i==bigger-1 || (x.cnt==y.cnt && i==x.cnt-1) ){
				sum.cnt++; 
			}
		}
	}
	//����������תΪ�ַ�����
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
	
	//����x��y��ռ��������������ж϶��ߴ�С�� 
	int isZero = 0;
	if(x.cnt==y.cnt){
		//ȥѰ�Ҷ�������Ԫ�ز���ȵĸ��� 
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
	//��x>yʱ����x������>y������  ��  x������=y������ʱ xĳ����Ԫ��>yĳ����Ԫ�أ� 
	XGreaterThanY: 	
		for(i=0;i<x.cnt || i<y.cnt;i++){
			//�ж���Ҫ��λ������� 
			if(x.num[i]<y.num[i]){
				x.num[i+1]--;
				x.num[i]+=(int)pow(10,4); 
			}
			dif.num[i]=x.num[i]-y.num[i]; //����x��y֮�� 
			if (dif.num[i]!=0) dif.cnt++;
		}
		goto XminusYfinished; //��������y>x����� 
	//��y>xʱ�� ��x������<y������  ��  x������=y������ʱ xĳ����Ԫ��<yĳ����Ԫ�أ� 
	YGreaterThanX:
		dif.sign=1; //���|X|-|Y|Ϊ�� 
		for(i=0;i<x.cnt || i<y.cnt;i++){
			//�ж���Ҫ��λ�������
			if(y.num[i]<x.num[i]){
				y.num[i+1]--;
				y.num[i]+=(int)pow(10,4);
			}
			dif.num[i]=y.num[i]-x.num[i]; //����y��x֮��
			if (dif.num[i]!=0) dif.cnt++;
		}
	XminusYfinished:
		//����������תΪ�ַ�����
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
	//���X+Y�Ľ����
	
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
	 
	//��� X-Y�Ľ����
	
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
