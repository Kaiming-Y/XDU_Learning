#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//判断该数据是否重复 
int isRepetition(unsigned char *inarr, int left);

//得到重复连续数据重复的个数 
int getRepetitionCnt(unsigned char *inarr, int left);

//得到非重复连续数据的个数 
int getNonRepetitionCnt(unsigned char *inarr, int left);

//压缩函数 
int Compression(char* infile, char* outfile);

//解压函数 
int Decompression(char* infile, char* outfile);

//压缩算法 
int encode(unsigned char* srcdata, unsigned char* destdata, int length);

//解压算法 
int decode(unsigned char* srcdata, unsigned char* destdata, int length);

//主函数 
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
	//若剩余不足3位则肯定不重复 
	if(left<3){
		ret = 0;
	}
	else if(inarr[0] == inarr[1] && inarr[1] == inarr[2]){
		ret = 1; ////有连续3个数据相等即可判定为连续重复数据 
	} 
	return ret;
}

int getRepetitionCnt(unsigned char *inarr, int left){
	int length = 0;
	unsigned char temp = *inarr; //标记第一个数据的值，便于判断后续重复数据 
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
	FILE* fin = fopen(infile, "rb"); //以二进制读的方式打开文件 
	FILE* fout = fopen(outfile, "wb"); //以二进制写的方式打开文件 
	//判断是否成功打开文件，若文件为空则结束程序：
	if(fin == NULL || fout == NULL){
		printf("Open file error!\n");
		fclose(fin);
		fclose(fout);
		exit(EXIT_FAILURE); //退出程序 
	}
	//调用动态内存开辟字符数组，用来存储原数据和压缩后的数据 
	unsigned char* srcdata= (unsigned char*)malloc((sizeof(unsigned char))*1024*1024*1024);
	unsigned char* destdata = (unsigned char*)malloc((sizeof(unsigned char))*1024*1024*1024);
	int size = 0, length = 0;
	while((length=fread(srcdata, sizeof(unsigned char), 1024, fin)) != 0){
		size = encode(srcdata, destdata, length); //进入压缩算法，并返回压缩后的字符数 
		if(size == -1) return -2;
		fwrite(destdata, sizeof(unsigned char), size, fout); //写入解压后的输出文件 
	}
	//告知压缩成功，并清空占用的动态内存，关闭文件 
	printf("Success!");
	free(srcdata);
	free(destdata);
	fclose(fin);
	fclose(fout);
}

int Decompression(char* infile, char* outfile){
	FILE* fin = fopen(infile, "rb"); //以二进制读的方式打开文件
	FILE* fout = fopen(outfile, "wb"); //以二进制写的方式打开文件
	//判断是否成功打开文件，若文件为空则结束程序：
	if(fin == NULL || fout == NULL){
		printf("Open file error!\n");
		fclose(fin);
		fclose(fout);
		exit(EXIT_FAILURE); //退出程序 
	}
	//调用动态内存开辟字符数组，用来存储原数据和解压缩后的数据 
	unsigned char* srcdata= (unsigned char*)malloc((sizeof(unsigned char))*1024*1024*1024);
	unsigned char* destdata = (unsigned char*)malloc((sizeof(unsigned char))*1024*1024*1024);
	int size = 0, length = 0;
	while((length=fread(srcdata, sizeof(unsigned char), 1024*1024*1024, fin)) != 0){
		size = decode(srcdata, destdata, length); //进入解压缩算法，并返回解压缩后的字符数 
		if(size == -1) return -2;
		fwrite(destdata, sizeof(unsigned char), size, fout); //写入解压后的输出文件 
	}
	//告知解压缩成功，并清空占用的动态内存，关闭文件 
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
		//重复数据标记1，并写入重复数量 
		if(isRepetition(srcdata, left)){
			if((size+2)>1024*1024*1024){      
                return -1;
            } 
			cnt = getRepetitionCnt(srcdata, left); //重复数量 
			destdata[size++] = cnt|0x80;
			destdata[size++] = *srcdata;
			srcdata += cnt; //原数据指针指向后续第一个不同的数据 
			left -= cnt;
		}
		//非重复数据标记0，并写入非重复数量 
		else{
			int i;
			cnt = getNonRepetitionCnt(srcdata, left); //非重复数量 
			if((size+cnt+1)>1024*1024*1024){      
                return -1;
            } 
			destdata[size++] = cnt;
			for(i=0; i<cnt; i++){
				destdata[size++] = *srcdata++; //每记录一个非重复数据则指针向后移一位 
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
		unsigned char sign = *in++; //定义指针遍历输入数据
		int cnt = sign & 0x7F; //位与运算，获取长度标识符 
		if((size+cnt)>1024*1024*1024){      
                return -1;
        } 
		//连续重复数据处理 
		if((sign & 0x80) == 0x80){
			for(i=0; i<cnt; i++){
				destdata[size++] = *in;
			}
			in++; 
		}
		//连续不重复数据处理： 
		else{
			for(i=0; i<cnt; i++){
				destdata[size++] = *in++; 
			}
		}
	}
	return size;
}
