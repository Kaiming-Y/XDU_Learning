#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma pack(1) //ʹ�ṹ���Ա��1�ֽڶ���

//λͼ�ļ�ͷ�ṹ��
typedef struct tagBITMAPFILEHEADER{
	unsigned short bfType; //ͼƬ���ͣ�1-2�ֽڣ� 'BM' 
	unsigned long bfSize; //�ļ���С���ֽ�����3-6�ֽڣ���λ��ǰ��
	unsigned short bfReserved1; //�����֣�7-8�ֽڣ�������Ϊ0 
	unsigned short bfReserved2; //�����֣�9-10�ֽڣ�������Ϊ0
	unsigned long bfOffBits; //RGB����ƫ�Ƶ�ַ��11-14�ֽڣ���λ��ǰ��
							 //λͼ�ļ�ͷ+λͼ��Ϣͷ+��ɫ��Ĵ�С�� 
}BITMAP_FILE_HEADER;  

//λͼ��Ϣͷ�ṹ��
typedef struct tagBITMAPINFOHEADER{
	unsigned long biSize; //���ṹ����ռ���ֽ�����15-18�ֽڣ� 
	unsigned long biWidth; //λͼ�Ŀ�ȣ�19-22�ֽڣ���������Ϊ��λ 
	unsigned long biHeight; //λͼ�ĸ߶ȣ�23-26�ֽڣ���������Ϊ��λ 
	unsigned short biPlanes; //Ŀ���豸�ļ���27-28�ֽڣ�������Ϊ1 
	unsigned short biBitCount; //ÿ����������Ҫ��λ����29-30�ֽڣ� 
	unsigned long biCompression; //λͼѹ�����ͣ�31-34�ֽڣ���������0/1/2֮һ 
	unsigned long biSizeImage; //λͼ�Ĵ�С��35-38�ֽڣ����ֽ����� 
	unsigned long biXPelsPerMeter; //λͼˮƽ�ֱ��ʣ�39-42�ֽڣ� 
	unsigned long biYPelsPerMeter; //λͼ��ֱ�ֱ��ʣ�43-46�ֽڣ� 
	unsigned long biClrUsed; //λͼʵ��ʹ�õ���ɫ���е���ɫ����47-50�ֽڣ� 
	unsigned long biClrImportant; //λͼ��ʾ��������Ҫ����ɫ����51-54�ֽڣ� 
}BITMAP_INFO_HEADER;  

//��ɫ�̽ṹ�� 
typedef struct tagRGBQUAND{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char rgbReserved;
}RGB_QUAND;

//�ļ����ź��� 
void BMP_ZOOM(char *in, char *out, double prop);
 
int main(int argc, char* argv[]){

	double proportion = atof(argv[2])/100.0; 
	BMP_ZOOM(argv[1],argv[3],proportion);
	
	return 0;
	
}

void BMP_ZOOM(char *in, char *out, double prop){
	
/*���ļ�*/
	FILE *fin, *fout; // fin:�����ͼƬ�ļ�   fout:������ļ�ͼƬ 
	fin = fopen(in,"rb"); //����ʽ�򿪶���ͼƬ�ļ� 
	fout = fopen(out,"wb"); //д��ʽ�����ͼƬ�ļ�
	//�ж��Ƿ�ɹ����ļ������ļ�Ϊ����������� 
	if(fin == NULL || fout == NULL){
		printf("Open file error!\n");
		fclose(fin);
		fclose(fout);
		exit(EXIT_FAILURE); //�˳����� 
	}
	
/*��ȡλͼ�ļ����ļ�ͷ����Ϣͷ*/
	BITMAP_FILE_HEADER file_head; //λͼ�ļ�ͷ 
	BITMAP_INFO_HEADER info_head; //λͼ��Ϣͷ 
	//��սṹ�壺 
	memset(&file_head, 0, sizeof(BITMAP_FILE_HEADER));
	memset(&info_head, 0, sizeof(BITMAP_INFO_HEADER));
	//��ȡ�ļ�ͷ����Ϣͷ���ṹ���� 
	fread(&file_head, sizeof(BITMAP_FILE_HEADER), 1, fin);
	fread(&info_head, sizeof(BITMAP_INFO_HEADER), 1, fin);
	long byte = info_head.biBitCount / 8; //ÿ�����ص��ֽ��� 
	RGB_QUAND *palette = (RGB_QUAND*)malloc((int)pow(2, info_head.biBitCount) * 4);//�����ɫ��ռ�
	//24λ�޵�ɫ�̣���24λҪ�����õ�ɫ�̲��� 
	if(info_head.biBitCount != 24){
		fread(palette, sizeof(RGB_QUAND), (int)pow(2, info_head.biBitCount), fin);
	}
	long srcWidth = info_head.biWidth; //Դ�ļ�ͼ��� 
	long srcHeight = info_head.biHeight; //Դ�ļ�ͼ���
	long srcSize =  info_head.biWidth*info_head.biHeight*byte; //Դ�ļ�ͼ��ߴ��С 
	
	
/*��ȡͼ���������*/ 
	unsigned char *srcData = (unsigned char*) malloc(srcSize); //Դ�ļ�ͼ�����ݶ�ȡ���ڴ����׵�ַ  
	if(info_head.biBitCount == 24){
		fseek(fin, 54, SEEK_SET); //��λ��Դ�ļ��ֽڵ�54λ
		fread(srcData, srcSize, 1, fin); //�����ݵ����������ָ��srcData 
	}
	else if(info_head.biBitCount == 8){
		fseek(fin, 1078, SEEK_SET); //�ļ�ָ��ָ���ļ��ĵ�54+2^8*4=1078���ֽ� 
		fread(srcData, srcSize, 1, fin); //�����ݵ����������ָ��srcData 
	}
	
	
/*���ź�ͼ����Ϣ����*/
	long newWidth = ( (int)(srcWidth*prop) + 3) / 4 * 4; //���ź�ͼ��� 
	long newHeight = ( (int)(srcHeight*prop) + 3) / 4 * 4; //���ź�ͼ��� 
	long newSize = newWidth*newHeight*byte; //���ź�ͼ��ߴ��С 
	//���ĳ��Ϳ� 
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
	//�����º����Ϣд�����ͼ����ļ� 
	fwrite(&file_head, sizeof(BITMAP_FILE_HEADER), 1, fout);
	fwrite(&info_head, sizeof(BITMAP_INFO_HEADER), 1, fout); 
	if(info_head.biBitCount != 24)	{
		fwrite(palette, sizeof(RGB_QUAND), pow(2,info_head.biBitCount),fout);
	}
	
/*λͼͼ�����Ŵ���*/
	//ʹ�����ڽ���ֵ�㷨����ͼƬ���� 
	unsigned long x, y;						//ԭͼ�������ص�Ŀ��
	unsigned long X, Y; 						//��ͼ�������ص�Ŀ�� 
 	unsigned char *pDest; 			//�޸����ص�λ�ã����ֽ�ƫ������ 
	unsigned char *pSrc;					//��ȡ���ص�λ�ã����ֽ�ƫ������ 
	unsigned char *destData = (unsigned char*)malloc(newSize); //������ͼƬ��λͼ��������ռ�
	for(Y = 0; Y < newHeight; Y++){
		y = Y / prop;				
		pDest = destData + Y * newWidth * byte;
		pSrc = srcData + y * srcWidth * byte;
		for(X = 0; X < newWidth; X++){
 			x = X / prop;
			memcpy(pDest + X * byte, pSrc + x * byte, byte);
		}
	}
	
/*��λͼ����д���µ�ͼƬ*/
	fwrite(destData, newSize, 1, fout);
	printf("Suceess!");
	
/*�ͷſռ� �ر��ļ�*/
	free(palette);
	free(srcData);
	free(destData);
	fclose(fin);
	fclose(fout);
}

