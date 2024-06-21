#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*编码算法从数据的起始位置开始向后搜索，
如果发现后面是重复数据且重复次数超过 2，则设置连续重复数据的标志并继续向后查找，
直到找到第一个与之不相同的数据为止，将这个位置记为下次搜索的起始位置，
根据位置差计算重复次数，最后长度属性字节以及一个字节的原始重复数据一起写入压缩数据；
如果后面数据不是连续重复数据，则继续向后搜索查找连续重复数据，
直到发现连续重复的数据且重复次数大于 2 为止，然后设置不重复数据标志，将新位置记为下次搜索的起始位置，
最后将长度属性字节写入压缩数据并将原始数据逐字节复制到压缩数据。
然后从上一步标记的新的搜索起始位开始，一直重复上面的过程，直到原始数据结束。*/
int IsrepetitionStart(unsigned char *src,int srcLeft){	//判断是否为有重复数超过3的重复数据 
    if(srcLeft<3){	//剩余数据数不足3返回0 
        return 0;
    }
    if((src[0]==src[1])&&(src[1]==src[2])){	
        return 1;
    }
    return 0;
}
int  GetRepetitionCount(unsigned char *src,int srcLeft){	//获得重复数据个数 
    int repeatedbuf=src[0];		//repeatedbuf表示重复的值 
    int length=1;	//	长度 
    while(length<srcLeft&&length<0x7f&&src[length]==repeatedbuf){	//长度标识占一字节，高位表示 重复与否，因此length最大为127 
        length++;
    }
    return length;	//返回的length<=127，important 
}
int GetNonRepetitionCount(unsigned char *src,int srcLeft){	//获得不重复数据个数 
    if(srcLeft<3){
        return srcLeft;
    }
    int length=2;
    int a=src[0],b=src[1];
    while(length<srcLeft&&length<0x7f&&((a!=b)||(b!=src[length]))){	//三个连续数不全相等 
        a=b;
        b=src[length];
        length++;
    }
    return length;
}
int Rle_Encode(unsigned char *inbuf,int inSize,unsigned char *outbuf,int onuBufSize)	//压缩算法，返回压缩后数据大小 
{	//传入：输入数据缓冲区首地址，输入数据大小， 输出缓冲区首地址， 输出数据大小 
    unsigned char *src=inbuf; //定义指针遍历输入数据 
    int i;
    int encSize=0;	//输出缓冲区大小 
    int srcLeft=inSize;       
    while(srcLeft>0){         
        int count=0;
        if(IsrepetitionStart(src,srcLeft)){ //有重复 
            if((encSize+2)>onuBufSize){	//输出缓冲区空间不够了
                return -1;
            } 
            count=GetRepetitionCount(src,srcLeft); 
            outbuf[encSize++]=count|0x80;  //按位或运算，保证高位为1，传入输出缓冲区，（即为长度标识）   
            outbuf[encSize++]=*src;    //   即为数据标识      
            src+=count;  //设置新的搜索位置                          
            srcLeft-=count;	//更新剩余数据数
        }
		else{	//无重复 
            count=GetNonRepetitionCount(src,srcLeft); 
            if((encSize+count+1)>onuBufSize){ 
                return -1;
            }
            outbuf[encSize++]=count;
            for(i=0;i<count;i++){	//逐个复制这些数据      
                outbuf[encSize++]=*src++;
            }
            srcLeft-=count;
        }
    }
    return encSize;
}
int Rle_Decode(unsigned char *inbuf,int inSize,unsigned char *outbuf,int onuBufSize){	//解压算法 
    unsigned char *src=inbuf;
    int i;
    int decSize=0;	//输出缓冲区大小 
    int count=0;
    while(src<(inbuf+inSize)){
        unsigned char sign=*src++;	//定义指针遍历输入数据 
        int count=sign & 0x7F;	//获取长度标识，按位与运算，保留常量（转换为二进制形式）的后7位数
        if((decSize+count)>onuBufSize){ //输出缓冲区空间不够了
            return -1;	
        }
        if((sign&0x80)==0x80){ //连续重复数据标志         
            for(i=0;i<count;i++){
                outbuf[decSize++]=*src;
            }
            src++;
        }else{
            for(i=0;i<count;i++){
                outbuf[decSize++]=*src++;
            }
        }           
    }
    return decSize;
}
int Compression(char*Inputfilename,char*Outputfilename){	//文件压缩	
    FILE *Input=fopen(Inputfilename, "rb");	//源文件 
    FILE *Output=fopen(Outputfilename, "wb");	//目标文件 
    if (Input==NULL||Output==NULL){
        printf("We can't open the file successfully!");
    }
    unsigned char*inbuf;	//输入缓存区 
    unsigned char*outbuf;	//输出缓存区 
    inbuf =(unsigned char*)malloc((sizeof(unsigned char))*1024*1024*1024);
    outbuf=(unsigned char*)malloc((sizeof(unsigned char))*1024*1024*1024);
    int length;
    while ((length=fread(inbuf, sizeof(unsigned char),1024,Input))!= 0){	//length表示读入的数据块数目 ，这块用while我不太明白 
            int tmp=Rle_Encode(inbuf,length,outbuf,1024*1024*1024);
            if(tmp==-1){
                return -2;
            }
            fwrite(outbuf, sizeof(unsigned char),tmp,Output);	//输出缓冲区数据写入目标文件 
    }
    fclose(Input);
    fclose(Output);
}

int Decompression(char*Inputfilename,char*Outputfilename){	//文件解压 
    FILE *Input=fopen(Inputfilename, "rb");
    FILE *Output=fopen(Outputfilename, "wb");
    if (Input==NULL||Output==NULL){
         printf("We can't open the file successfully!");
    }
    unsigned char*inbuf;	//输入缓存区 
    unsigned char*outbuf;	//输出缓存区 
    inbuf=(unsigned char*)malloc((sizeof(unsigned char))*1024*1024*1024);
    outbuf=(unsigned char*)malloc((sizeof(unsigned char))*1024*1024*1024);
    int length;
    while((length=fread(inbuf, sizeof(unsigned char),1024*1024*1024,Input))!=0){
            int tmp=Rle_Decode(inbuf,length,outbuf,1024*1024*1024);
            if(tmp==-1){
                return -2;
            }
            fwrite(outbuf, sizeof(unsigned char),tmp,Output);
    }
    fclose(Input);
    fclose(Output);
}
int main(int argc,char**argv)
{
    if(strcmp(argv[2],"-c")==0){
       Compression(argv[1],argv[3]);
    }else if(strcmp(argv[2],"-d")==0){
       Decompression(argv[1],argv[3]);
    }  
    return 0;
}


