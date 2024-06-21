#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//�жϸ������Ƿ��ظ� 
int isRepetition(unsigned char *inarr, int left);

//�õ��ظ����������ظ��ĸ��� 
int getRepetitionCnt(unsigned char *inarr, int left);

//�õ����ظ��������ݵĸ��� 
int getNonRepetitionCnt(unsigned char *inarr, int left);

//ѹ������ 
int Compression(char* infile, char* outfile);

//��ѹ���� 
int Decompression(char* infile, char* outfile);

//ѹ���㷨 
int encode(unsigned char* srcdata, unsigned char* destdata, int length);

//��ѹ�㷨 
int decode(unsigned char* srcdata, unsigned char* destdata, int length);

//������ 
int main(int argc, char* argv[])
{
	if(strcmp(argv[2],"-c") == 0){
		Compression(argv[1], argv[3]);
	}
	else if(strcmp(argv[2],"-d") == 0){
		Decompression(argv[1], argv[3]);
	}
	else{
		printf("Please enter a correct command!");
	}
	return 0;
}

int isRepetition(unsigned char *inarr, int left){
	int ret = 0;
	//��ʣ�಻��3λ��϶����ظ� 
	if(left<3){
		ret = 0;
	}
	else if(inarr[0] == inarr[1] && inarr[1] == inarr[2]){
		ret = 1; ////������3��������ȼ����ж�Ϊ�����ظ����� 
	} 
	return ret;
}

int getRepetitionCnt(unsigned char *inarr, int left){
	int length = 0;
	unsigned char temp = *inarr; //��ǵ�һ�����ݵ�ֵ�������жϺ����ظ����� 
	while( *inarr == temp && length<left && length<0x7f ){
		length++;
		inarr++;
	}
	return length;
}

int getNonRepetitionCnt(unsigned char *inarr, int left){
	if(left<3){
		return left;
	}
	int length = 2;
	int a = inarr[0], b = inarr[1];
	while( (a != b || b != inarr[length]) && length<left && length<0x7f ){
		a = b;
		b = inarr[length];
		length++;
	}
	return length;
}

int Compression(char* infile, char* outfile){
	FILE* fin = fopen(infile, "rb"); //�Զ����ƶ��ķ�ʽ���ļ� 
	FILE* fout = fopen(outfile, "wb"); //�Զ�����д�ķ�ʽ���ļ� 
	//�ж��Ƿ�ɹ����ļ������ļ�Ϊ�����������
	if(fin == NULL || fout == NULL){
		printf("Open file error!\n");
		fclose(fin);
		fclose(fout);
		exit(EXIT_FAILURE); //�˳����� 
	}
	//���ö�̬�ڴ濪���ַ����飬�����洢ԭ���ݺ�ѹ��������� 
	unsigned char* srcdata= (unsigned char*)malloc((sizeof(unsigned char))*1024*1024*1024);
	unsigned char* destdata = (unsigned char*)malloc((sizeof(unsigned char))*1024*1024*1024);
	int size = 0, length = 0;
	while((length=fread(srcdata, sizeof(unsigned char), 1024, fin)) != 0){
		size = encode(srcdata, destdata, length); //����ѹ���㷨��������ѹ������ַ��� 
		if(size == -1) return -2;
		fwrite(destdata, sizeof(unsigned char), size, fout); //д���ѹ�������ļ� 
	}
	//��֪ѹ���ɹ��������ռ�õĶ�̬�ڴ棬�ر��ļ� 
	printf("Success!");
	free(srcdata);
	free(destdata);
	fclose(fin);
	fclose(fout);
}

int Decompression(char* infile, char* outfile){
	FILE* fin = fopen(infile, "rb"); //�Զ����ƶ��ķ�ʽ���ļ�
	FILE* fout = fopen(outfile, "wb"); //�Զ�����д�ķ�ʽ���ļ�
	//�ж��Ƿ�ɹ����ļ������ļ�Ϊ�����������
	if(fin == NULL || fout == NULL){
		printf("Open file error!\n");
		fclose(fin);
		fclose(fout);
		exit(EXIT_FAILURE); //�˳����� 
	}
	//���ö�̬�ڴ濪���ַ����飬�����洢ԭ���ݺͽ�ѹ��������� 
	unsigned char* srcdata= (unsigned char*)malloc((sizeof(unsigned char))*1024*1024*1024);
	unsigned char* destdata = (unsigned char*)malloc((sizeof(unsigned char))*1024*1024*1024);
	int size = 0, length = 0;
	while((length=fread(srcdata, sizeof(unsigned char), 1024*1024*1024, fin)) != 0){
		size = decode(srcdata, destdata, length); //�����ѹ���㷨�������ؽ�ѹ������ַ��� 
		if(size == -1) return -2;
		fwrite(destdata, sizeof(unsigned char), size, fout); //д���ѹ�������ļ� 
	}
	//��֪��ѹ���ɹ��������ռ�õĶ�̬�ڴ棬�ر��ļ� 
	printf("Success!");
	free(srcdata);
	free(destdata);
	fclose(fin);
	fclose(fout);
}
int encode(unsigned char* srcdata, unsigned char* destdata, int length){
	int size = 0, cnt = 0, left = length;
	while(left>0){
		cnt = 0;
		//�ظ����ݱ��1����д���ظ����� 
		if(isRepetition(srcdata, left)){
			if((size+2)>1024*1024*1024){      
                return -1;
            } 
			cnt = getRepetitionCnt(srcdata, left); //�ظ����� 
			destdata[size++] = cnt|0x80;
			destdata[size++] = *srcdata;
			srcdata += cnt; //ԭ����ָ��ָ�������һ����ͬ������ 
			left -= cnt;
		}
		//���ظ����ݱ��0����д����ظ����� 
		else{
			int i;
			cnt = getNonRepetitionCnt(srcdata, left); //���ظ����� 
			if((size+cnt+1)>1024*1024*1024){      
                return -1;
            } 
			destdata[size++] = cnt;
			for(i=0; i<cnt; i++){
				destdata[size++] = *srcdata++; //ÿ��¼һ�����ظ�������ָ�������һλ 
			}
			left -= cnt;
		} 
	}
	return size;
}

int decode(unsigned char* srcdata, unsigned char* destdata, int length){
	unsigned char* in = srcdata;
	int i;
	int size = 0;
	int cnt = 0;
	while(in<(srcdata+length)){
		unsigned char sign = *in++; //����ָ�������������
		int cnt = sign & 0x7F; //λ�����㣬��ȡ���ȱ�ʶ�� 
		if((size+cnt)>1024*1024*1024){      
                return -1;
        } 
		//�����ظ����ݴ��� 
		if((sign & 0x80) == 0x80){
			for(i=0; i<cnt; i++){
				destdata[size++] = *in;
			}
			in++; 
		}
		//�������ظ����ݴ��� 
		else{
			for(i=0; i<cnt; i++){
				destdata[size++] = *in++; 
			}
		}
	}
	return size;
}
