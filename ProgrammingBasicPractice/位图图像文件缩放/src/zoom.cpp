#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma pack(1) //使结构体成员按1字节对齐

//位图文件头结构体
typedef struct tagBITMAPFILEHEADER{
	unsigned short bfType; //图片类型（1-2字节） 'BM' 
	unsigned long bfSize; //文件大小（字节数，3-6字节，低位在前）
	unsigned short bfReserved1; //保留字（7-8字节），必须为0 
	unsigned short bfReserved2; //保留字（9-10字节），必须为0
	unsigned long bfOffBits; //RGB数据偏移地址（11-14字节，低位在前）
							 //位图文件头+位图信息头+调色板的大小） 
}BITMAP_FILE_HEADER;  

//位图信息头结构体
typedef struct tagBITMAPINFOHEADER{
	unsigned long biSize; //本结构体所占用字节数（15-18字节） 
	unsigned long biWidth; //位图的宽度（19-22字节），以像素为单位 
	unsigned long biHeight; //位图的高度（23-26字节），以像素为单位 
	unsigned short biPlanes; //目标设备的级别（27-28字节），必须为1 
	unsigned short biBitCount; //每个像素所需要的位数（29-30字节） 
	unsigned long biCompression; //位图压缩类型（31-34字节），必须是0/1/2之一 
	unsigned long biSizeImage; //位图的大小（35-38字节）（字节数） 
	unsigned long biXPelsPerMeter; //位图水平分辨率（39-42字节） 
	unsigned long biYPelsPerMeter; //位图垂直分辨率（43-46字节） 
	unsigned long biClrUsed; //位图实际使用的颜色表中的颜色数（47-50字节） 
	unsigned long biClrImportant; //位图显示过程中重要的颜色数（51-54字节） 
}BITMAP_INFO_HEADER;  

//调色盘结构体 
typedef struct tagRGBQUAND{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char rgbReserved;
}RGB_QUAND;

//文件缩放函数 
void BMP_ZOOM(char *in, char *out, double prop);
 
int main(int argc, char* argv[]){

	double proportion = atof(argv[2])/100.0; 
	BMP_ZOOM(argv[1],argv[3],proportion);
	
	return 0;
	
}

void BMP_ZOOM(char *in, char *out, double prop){
	
/*打开文件*/
	FILE *fin, *fout; // fin:读入的图片文件   fout:输出的文件图片 
	fin = fopen(in,"rb"); //读方式打开读入图片文件 
	fout = fopen(out,"wb"); //写方式打开输出图片文件
	//判断是否成功打开文件，若文件为空则结束程序： 
	if(fin == NULL || fout == NULL){
		printf("Open file error!\n");
		fclose(fin);
		fclose(fout);
		exit(EXIT_FAILURE); //退出程序 
	}
	
/*读取位图文件的文件头和信息头*/
	BITMAP_FILE_HEADER file_head; //位图文件头 
	BITMAP_INFO_HEADER info_head; //位图信息头 
	//清空结构体： 
	memset(&file_head, 0, sizeof(BITMAP_FILE_HEADER));
	memset(&info_head, 0, sizeof(BITMAP_INFO_HEADER));
	//读取文件头和信息头到结构体中 
	fread(&file_head, sizeof(BITMAP_FILE_HEADER), 1, fin);
	fread(&info_head, sizeof(BITMAP_INFO_HEADER), 1, fin);
	long byte = info_head.biBitCount / 8; //每个像素的字节数 
	RGB_QUAND *palette = (RGB_QUAND*)malloc((int)pow(2, info_head.biBitCount) * 4);//分配调色板空间
	//24位无调色盘，非24位要先配置调色盘参数 
	if(info_head.biBitCount != 24){
		fread(palette, sizeof(RGB_QUAND), (int)pow(2, info_head.biBitCount), fin);
	}
	long srcWidth = info_head.biWidth; //源文件图像宽 
	long srcHeight = info_head.biHeight; //源文件图像高
	long srcSize =  info_head.biWidth*info_head.biHeight*byte; //源文件图像尺寸大小 
	
	
/*读取图像点阵数据*/ 
	unsigned char *srcData = (unsigned char*) malloc(srcSize); //源文件图像数据读取到内存后的首地址  
	if(info_head.biBitCount == 24){
		fseek(fin, 54, SEEK_SET); //定位到源文件字节第54位
		fread(srcData, srcSize, 1, fin); //将数据点阵读入数据指针srcData 
	}
	else if(info_head.biBitCount == 8){
		fseek(fin, 1078, SEEK_SET); //文件指针指向文件的第54+2^8*4=1078个字节 
		fread(srcData, srcSize, 1, fin); //将数据点阵读入数据指针srcData 
	}
	
	
/*缩放后图像信息更新*/
	long newWidth = ( (int)(srcWidth*prop) + 3) / 4 * 4; //缩放后图像宽 
	long newHeight = ( (int)(srcHeight*prop) + 3) / 4 * 4; //缩放后图像高 
	long newSize = newWidth*newHeight*byte; //缩放后图像尺寸大小 
	//更改长和宽： 
	info_head.biWidth = newWidth;
	info_head.biHeight = newHeight;
	if(info_head.biBitCount == 24){
		file_head.bfSize = 54 + newSize;
		info_head.biSizeImage = newSize;
	}
	else if(info_head.biBitCount == 8){
		file_head.bfSize = 1078 + newSize;
		info_head.biSizeImage = newSize;
	}
	//将更新后的信息写入输出图像的文件 
	fwrite(&file_head, sizeof(BITMAP_FILE_HEADER), 1, fout);
	fwrite(&info_head, sizeof(BITMAP_INFO_HEADER), 1, fout); 
	if(info_head.biBitCount != 24)	{
		fwrite(palette, sizeof(RGB_QUAND), pow(2,info_head.biBitCount),fout);
	}
	
/*位图图像缩放处理*/
	//使用最邻近差值算法进行图片缩放 
	unsigned long x, y;						//原图所在像素点的宽高
	unsigned long X, Y; 						//新图所在像素点的宽高 
 	unsigned char *pDest; 			//修改像素的位置（即字节偏移量） 
	unsigned char *pSrc;					//获取像素的位置（即字节偏移量） 
	unsigned char *destData = (unsigned char*)malloc(newSize); //开好新图片的位图数据所需空间
	for(Y = 0; Y < newHeight; Y++){
		y = Y / prop;				
		pDest = destData + Y * newWidth * byte;
		pSrc = srcData + y * srcWidth * byte;
		for(X = 0; X < newWidth; X++){
 			x = X / prop;
			memcpy(pDest + X * byte, pSrc + x * byte, byte);
		}
	}
	
/*将位图数据写入新的图片*/
	fwrite(destData, newSize, 1, fout);
	printf("Suceess!");
	
/*释放空间 关闭文件*/
	free(palette);
	free(srcData);
	free(destData);
	fclose(fin);
	fclose(fout);
}

