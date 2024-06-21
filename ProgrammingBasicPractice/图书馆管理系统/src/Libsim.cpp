#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

//ͼ����Ϣ 
typedef struct {
	int code;         		//��ı�� 
	char name[50];    		//���� 
	int inventory;    		//�ڿ����� 
}BOOK;

//������Ϣ 
typedef struct {
	int id;           		 //�û����� 
	char name[20];    		 //����
	char key[20];			 //���� 
	int borrow_book_code[11];//����ͼ���� ��ÿ����������1��������10���飩
	int borrowAmount;		 //����ͼ������ 
}READER;

//����Ա��Ϣ 
typedef struct {
	int id;           		//�û����� 
	char name[20];    		//����
	char key[20];			//���� 
}MANAGER;

//�����鱾�����ߡ�����Ա���軹��¼���� 
BOOK book[MAX];	 						//MAX���� 
READER reader[MAX];  					//MAX������ 
MANAGER manager[10]; 					//10������Ա
char BorrowerList[MAX][MAX] = {{'\0'}}; //ÿ����Ľ�����
	
//ö���û����ࣨ����Ա�����ߡ������� 
enum ROLE{ Manager = 1, Reader = 2, Other };

//��¼ 
ROLE login(char* cmd, char* name);

//չʾ�˵� 
void dispMenu(const char* pmt[], int n);

//�����鱾��Ϣ����������Ϣ 
void loadBookInfo();
//���ض�����Ϣ 
void loadReaderInfo();
//���ع���Ա��Ϣ 
void loadManagerInfo();

//����ͼ����Ϣ 
void UpdateBookInfo();
//���¶�����Ϣ 
void UpdateReaderInfo();
//���¹���Ա��Ϣ 
void UpdateManagerInfo();
//���½�������Ϣ 
void UpdateBorrowerList();

//ͼ���ѯ 
void bookQuery();
//չʾͼ�� 
void showBook(int i);
//չʾ������Ϣ
void showReader(int i); 
//ͼ����� 
void bookRegister();
//ͼ���Ƴ�
void bookRemove();
//�û����� 
void userManagement();
//�û���Ϣ��ѯ 
void readerQuery();
//���� 
void bookBorrow(char* usrName);
//���� 
void bookReturn(char* usrName);
//�༭�û���Ϣ 
void editUsr();
//�����û� 
void addUsr();
//ɾ���û� 
void delUsr();
//�����û����
void UpdateUsrID(ROLE role);
//�����鱾���
void UpdateBookID(); 

//�˵� 
const char* ManagerMenu[] = {"1.ͼ���ѯ", "2.ͼ�����", "3.ͼ���Ƴ�", "4.�û�����", "5.�û���Ϣ��ѯ", "0.�˳�"};
const char* ReaderMenu[] = {"1.ͼ���ѯ", "2.����", "3.����", "0.�˳�"};

//ͼ�顢���ߡ�����Ա���� 
int BookAmount;
int ReaderAmount;
int ManagerAmount;

//Libsim -a(-u) xxxx
//��һ������Ϊ��ִ�г������ƣ��ڶ�������Ϊ�û���ݣ�-a��ʾ����Ա��-u��ʾ���ߣ�����������Ϊ�û���

//������ 
int main(int argc, char* argv[])
{
	int i,k;
	//��ʼ������սṹ�� 
	for(k=0; k<MAX; k++){
		memset(&book[k], 0, sizeof(BOOK));
		memset(&reader[k], 0, sizeof(READER));
	}
	for(k=0; k<10; k++){
		memset(&manager[k], 0, sizeof(MANAGER));
	}
	//��ʼ��ϵͳ�������鱾�����ߡ�����Ա��Ϣ 
	loadBookInfo();
	loadReaderInfo();
	loadManagerInfo(); 
	//����ϵͳ���û������� 
	int cmdNo = 0;
	printf("��ӭʹ��ͼ��ݹ���ϵͳ��\n") ;
	ROLE role = login(argv[1], argv[2]); 
	//����Ա�˵� 
	if( role == Manager ){
		while(1){
			//չʾ����Ա�˵� 
			dispMenu( ManagerMenu, sizeof(ManagerMenu) / sizeof(char*) );
			scanf("%d",&cmdNo);
			if( cmdNo == 0 ){
				printf("����Ա�˳���\n");
				break;
			}
			else{
				switch(cmdNo){
					case 1: bookQuery(); break;
					case 2: bookRegister(); break;
					case 3: bookRemove(); break;
					case 4: userManagement(); break;
					case 5: readerQuery(); break;
					default : printf("�������\n"); 
				}
			}
		} 
	}
	//���߲˵� 
	else if ( role == Reader ){
		while(1){
			//չʾ���߲˵� 
			dispMenu( ReaderMenu, sizeof(ReaderMenu) / sizeof(char*) );
			scanf("%d",&cmdNo);
			if( cmdNo == 0 ){
				printf("�����û��˳���\n");
				break;
			}
			else{
				switch(cmdNo){
					case 1: bookQuery(); break;
					case 2: bookBorrow(argv[2]); break;
					case 3: bookReturn(argv[2]); break;
					default : printf("�������\n"); 
				}
			} 
		} 
	}
	//other 
	else{
		printf("\n��Ҫ�˳�ϵͳ�𣿣�����y�˳���\n");
		char ch = getchar();
		if( ch == 'y' || ch == 'Y'){
			printf("�ټ�!\n");
			return 0;
		}
	}
	return 0; 
}

ROLE login(char* cmd, char* name){
	//�ж���� 
	ROLE identity;
	char usrName[20], usrKey[20];
	int i, flag = 0;
	strcpy(usrName, name);
	if(!strcmp(cmd, "-a")){
		identity = Manager;
		//�˶����
		CONFIRM_MANAGER_IDENTITY:
		printf("���������룺");
		scanf("%s",usrKey); 
		getchar();
		for(i=0; i<ManagerAmount; i++){
			if(!strcmp(usrName, manager[i].name) && !strcmp(usrKey, manager[i].key)){
				printf("��½�ɹ�\n");
				flag = 1;
				break;
			} 
		}
		if(flag == 0){
			printf("�û��������ڻ��������\n");
			goto CONFIRM_MANAGER_IDENTITY;
		} 
	}
	else if(!strcmp(cmd, "-u")){
		identity = Reader;
		//�˶����
		CONFIRM_READER_IDENTITY:
		printf("���������룺");
		scanf("%s",usrKey); 
		getchar();
		for(i=0; i<ReaderAmount; i++){
			if(!strcmp(usrName, reader[i].name) && !strcmp(usrKey, reader[i].key)){
				printf("��½�ɹ�\n");
				flag = 1;
				break;
			} 
		}
		if(flag == 0){
			printf("�û��������ڻ��������\n");
			goto CONFIRM_MANAGER_IDENTITY;
		} 
	}
	else{
		identity = Other;
	}
	return identity;
}

void dispMenu(const char* pmt[], int n){
	printf("\n------------------------------------\n");
	int i = 0;
	for(i=0; i<n; i++){
		printf("\t%s\n",pmt[i]);
	}
	printf("------------------------------------\n");
	printf("\n���������ѡ���ţ�");
}

void loadBookInfo(){
	FILE *fp = fopen("Books.txt","r");
	FILE *fp1 = fopen("BorrowerList.txt","r"); 
	if(fp == NULL || fp1 == NULL){
		printf("�ļ��򿪴���\n"); 
		fclose(fp);
		exit(EXIT_FAILURE); //�˳�����
	}
	char t[100];
	int i = 0, j = 0, cnt = 0;
	while(fgets(t, 100, fp) != NULL){
		if(t[strlen(t)-1]=='\n') t[strlen(t)-1]='\0';
		if(!strcmp(t, "end")) break;
		book[cnt].code = cnt+1;
		char left[10] = {'\0'};
		for(i=0,j=0; t[i] != '\0'; i++){
			if(t[i]!=':'){
				book[cnt].name[j++] = t[i];
			}
			else if(t[i] == ':'){
				book[cnt].name[j] = '\0';
				i++;
				for(j=0; t[i] != '\0'; i++,j++){
					left[j] = t[i];
				}
				book[cnt].inventory = atoi(left);
			}
		}
		cnt++;
	}
	BookAmount = cnt;
	i = 0;
	while(fgets(t, 100, fp1) != NULL && i<BookAmount){
		if(t[strlen(t)-1]=='\n') t[strlen(t)-1]='\0';
		if(!strcmp(t, "end")) break;
		if(strlen(t) != 0){
			strcpy(BorrowerList[i], t);
		}
		else{
			strcpy(BorrowerList[i], "null");
		}
		i++;
	}
	fclose(fp);
	fclose(fp1);
}

void loadReaderInfo(){
	FILE *fp = fopen("Readers.txt","r");
	if(fp == NULL){
		printf("�ļ��򿪴���\n"); 
		fclose(fp);
		exit(EXIT_FAILURE); //�˳�����
	}
	char t[100];
	int i = 0, j = 0, k = 0, cnt = 0, flag = 0;
	while(fgets(t, 100, fp) != NULL){
		flag = 0;
		i = 0;
		j = 0;
		k = 0;
		if(t[strlen(t)-1]=='\n') t[strlen(t)-1]='\0';
		if(!strcmp(t, "end")) break;
		reader[cnt].id = cnt+1;
		char brwbook[10];
		for(i=0,j=0; t[i] != '\0'; i++){
			if(t[i] != '-'){
				reader[cnt].name[j++] = t[i];
			}
			else if(t[i] == '-' && flag == 0){
				reader[cnt].name[j] = '\0';
				i++;
				flag++;
				for(j=0; t[i] != '-'; i++,j++){
					reader[cnt].key[j] = t[i];
				}
				if(t[i] == '-' && flag == 1){
					reader[cnt].key[j] = '\0';
					i++;
					flag++;
					for(; t[i] != '\0'; i++){
						for(j=0; t[i] != '.' && t[i] != '\0'; i++,j++){
							brwbook[j] = t[i];
						}
						brwbook[j] = '\0';
						reader[cnt].borrow_book_code[k] = atoi(brwbook);
						k++;
						if(t[i] == '\0') break;
					}
					reader[cnt].borrowAmount = k-1;
				}
			}
		}
		cnt++;
	}
	ReaderAmount = cnt;
	fclose(fp);
}

void loadManagerInfo(){
	FILE *fp = fopen("Managers.txt","r");
	if(fp == NULL){
		printf("�ļ��򿪴���\n"); 
		fclose(fp);
		exit(EXIT_FAILURE); //�˳�����
	}
	char t[100];
	int i = 0, j = 0, cnt = 0;
	while(fgets(t, 100, fp) != NULL){
		if(t[strlen(t)-1]=='\n') t[strlen(t)-1]='\0';
		if(!strcmp(t, "end")) break;
		manager[cnt].id = cnt+1;
		for(i=0,j=0; t[i] != '\0'; i++){
			if(t[i] != '-'){
				manager[cnt].name[j++] = t[i];
			}
			else if(t[i] == '-'){
				manager[cnt].name[j] = '\0';
				i++;
				for(j=0; t[i] != '\0'; i++, j++){
					manager[cnt].key[j] = t[i];
				}
				manager[cnt].key[j] = '\0';
			}
		}
		cnt++;
	}
	ManagerAmount = cnt;
	fclose(fp);
}

void UpdateBookInfo(){
	FILE *fw = fopen("Books.txt","w");
	if(fw == NULL){
		printf("�ļ��򿪴���\n"); 
		fclose(fw);
		exit(EXIT_FAILURE); //�˳�����
	}
	int i = 0, j = 0, k = 0;
//	for(i=0;i<BookAmount;i++){
//		showBook(i);
//	}
	char t[100];
	for(i=0, k=0; i<BookAmount; i++){
		k=0;
		char left[10] = {'\0'};
		for(j=0; book[i].name[j] != '\0'; j++){
			t[k] = book[i].name[j];
			k++;
		}
		t[k] = ':';
		k++;
		itoa(book[i].inventory, left, 10);
		if(left[strlen(left)] == NULL) left[strlen(left)] = '\0';
		for(j=0; j<strlen(left); j++){
			t[k] = left[j];
			k++;
		}
		t[k] = '\0';
		fputs(t,fw);
		fputc('\n',fw); 
	}
	fputs("end",fw);
	fclose(fw);
}

void UpdateReaderInfo(){
	FILE *fw = fopen("Readers.txt","w");
	if(fw == NULL){
		printf("�ļ��򿪴���\n"); 
		fclose(fw);
		exit(EXIT_FAILURE); //�˳�����
	}
	int i = 0, j = 0, k = 0, l = 0;
	char t[100];
	for(i=0; i<ReaderAmount; i++){
		k=0;
		for(j=0; reader[i].name[j] != '\0'; j++){
			t[k] = reader[i].name[j];
			k++;
		}
		t[k++] = '-';
		for(j=0; reader[i].key[j] != '\0'; j++){
			t[k] = reader[i].key[j];
			k++;
		}
		t[k++] = '-';
		for(j=0; reader[i].borrow_book_code[j]!=0; j++){
			char c[10] = {'\0'};
			itoa(reader[i].borrow_book_code[j], c, 10);
			if(c[strlen(c)] == NULL) c[strlen(c)] = '\0';
			for(l=0; l<strlen(c); l++){
				t[k] = c[l];
				k++;
			}
			t[k] = '.';
			k++;
		}
		t[k] = '0';
		k++;
		t[k] = '\0';
		fputs(t,fw);
		fputc('\n',fw); 
	}
	fputs("end",fw);
	fclose(fw);
}

void UpdateManagerInfo(){
	FILE *fw = fopen("Managers.txt","w");
	if(fw == NULL){
		printf("�ļ��򿪴���\n"); 
		fclose(fw);
		exit(EXIT_FAILURE); //�˳�����
	}
	int i = 0, j = 0, k = 0;
	char t[100];
	for(i=0; i<ManagerAmount; i++){
		k=0;
		for(j=0; manager[i].name[j] != '\0'; j++){
			t[k] = manager[i].name[j];
			k++;
		}
		t[k] = '-';
		k++;
		for(j=0; manager[i].key[j] != '\0'; j++){
			t[k] = manager[i].key[j];
			k++;
		}
		t[k] = '\0';
		fputs(t,fw);
		fputc('\n',fw);
	}
	fputs("end",fw);
	fclose(fw);
}

void UpdateBorrowerList(){
	FILE *fw = fopen("BorrowerList.txt","w");
	if(fw == NULL){
		printf("�ļ��򿪴���\n"); 
		fclose(fw);
		exit(EXIT_FAILURE); //�˳�����
	}
	int i = 0, j = 0, k = 0;
	char t[100];
	for(i=0; i<BookAmount; i++){
		strcpy(t, BorrowerList[i]);
		fputs(t,fw);
		fputc('\n',fw);
	}
	fputs("end",fw);
	fclose(fw);
}

void bookQuery(){
	int i = 0;
	int choice = -1;
	while(choice != 0){
		fflush(stdin);
		printf("��ѡ���ѯ��ʽ������ѡ����뼴�ɣ���\n1.��Ų�ѯ\n2.������ѯ\n0.�˳�\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:{
				int code = 0;
				printf("���������ѯ�鼮�ı�ţ�");
				scanf("%d",&code);
				getchar();
				if(code>BookAmount){
					printf("���鼮������\n");
					break; 
				}
				for(i=0; i<BookAmount; i++){
					if(book[i].code == code){
						showBook(i);
						break;
					}
				}
				break;
			}
			case 2:{
				char name[50];
				int flag = 0; 
				printf("���������ѯ�鼮�����֣�");
				getchar();
				gets(name);
				for(i=0; i<BookAmount; i++){
					if( !strcmp(book[i].name, name) ){
						showBook(i);
						flag = 1;
						break;
					}
				}
				if(flag == 0){
					printf("δ��ѯ�����鼮\n");
				}
				break;
			}
			case 0: printf("���˳�ͼ���ѯ����\n"); break; 
			default : printf("�������\n");
		} 
	} 
}

void showBook(int i){
	printf("������%s\n",book[i].name);
	printf("�鼮��ţ�%d\n",book[i].code);
	printf("��棺%d\n",book[i].inventory);
	printf("�����ߣ�%s\n",BorrowerList[i]);
}

void showReader(int i){
	printf("���߱�ţ�%d\n",reader[i].id);
	printf("����������%s\n",reader[i].name);
	printf("�������룺%s\n",reader[i].key);
	printf("�����鼮����%d\n",reader[i].borrowAmount);
	printf("�ѽ��ĵ��鼮��ţ�");
	int j;
	for(j=0; j<reader[i].borrowAmount; j++){
		printf("%d ",reader[i].borrow_book_code[j]); 
	}
	printf("\n");
}

void bookRegister(){
	char name[50];
	int num;
	int i = 0, flag = 0;
	fflush(stdin);
	printf("����������鼮��������");
	gets(name);
	fflush(stdin);
	printf("����������������");
	scanf ("%d",&num);
	for(i=0; i<BookAmount; i++){
		//�����鱾���ʹ��ڣ������ӿ�� 
		if( !strcmp(book[i].name, name) ){
			flag = 1;
			book[i].inventory += num;
			break;
		}
	}
	//����ͼ��Ϊ���飬������������� 
	if(flag == 0){
		strcpy(book[BookAmount].name, name);
		book[BookAmount].inventory = num;
		book[BookAmount].code = BookAmount+1;
		BookAmount++;
		UpdateBookID();
	}
	UpdateBookInfo();
	printf("�ѳɹ����\n");
}

void bookRemove(){
	int code;
	printf("��������Ҫ�Ƴ���ͼ��ı�ţ�");
	fflush(stdin);
	scanf("%d",&code);
	int i = 0;
	for(i=code-1; i<BookAmount-1; i++){
		book[i] = book[i+1];
		strcpy(BorrowerList[i],BorrowerList[i+1]);
	}
	memset(&book[BookAmount-1], 0, sizeof(BOOK));
	strcpy(BorrowerList[BookAmount-1],"");
	BookAmount--;
	UpdateBookID();
	UpdateBookInfo();
	UpdateBorrowerList();
	printf("�ѳɹ��Ƴ�����Ŀ\n");
}

void userManagement(){
	int choice = -1;
	while(choice != 0){
		printf("��ѡ����Ҫ���еĹ��ܣ�\n1.������Ϣ����\n2.���Ӷ���\n3.ɾ������\n0.�˳�\n");
		fflush(stdin);
		scanf("%d",&choice);
		switch(choice){
			case 1:{
				editUsr();
				break;
			}
			case 2:{
				addUsr();
				break;
			}
			case 3:{
				delUsr();
				break;
			}
			case 0:{
				printf("���˳��û�������\n");
				break;
			}
			default: printf("�������\n");
		}
	} 
}

void readerQuery(){
	int id;
	fflush(stdin);
	printf("��������Ҫ��ѯ�û��ı�ţ�"); 
	scanf("%d",&id);
	if(id>ReaderAmount){
		printf("���û�������\n");
	}
	else{
		showReader(id-1);
	}
}

void bookBorrow(char* usrName){
	int code = 0, flag = 0, bookcnt = 0, id = 0;
	int i = 0;
	//ȷ����� 
	for(i=0; i<ReaderAmount; i++){
		if( !strcmp(reader[i].name, usrName) ){
			bookcnt = reader[i].borrowAmount;
			id = reader[i].id;
		}
	}
	BORROW:
	fflush(stdin);
	printf("��������Ҫ�����ͼ��ı�ţ�");
	scanf("%d",&code);
	if(code>BookAmount) {
		printf("���鲻����\n");
		goto BORROW;
	}
	//�ж��ܷ���飬��ʵʩ 
	if(book[code-1].inventory == 0){
		printf("�����ѱ����\n");
	}
	else if(bookcnt>10){
		printf("���������ѳ�������\n");
	}
	//���Խ��� 
	else{
		book[code-1].inventory--;
		if( !strcmp(BorrowerList[code-1], "null") ){
			strcpy(BorrowerList[code-1], usrName); 
		}
		else{
			strcat(BorrowerList[code-1], " ");
			strcat(BorrowerList[code-1], usrName);
		}
		reader[id-1].borrow_book_code[bookcnt++] = code;
		reader[id-1].borrow_book_code[bookcnt] = 0;
		reader[i].borrowAmount++; 
		flag = 1;
	}
	if(flag == 1){
		printf("�ѳɹ��������Ŀ\n");
	}
	else{
		printf("����ʧ��\n");
	}
	UpdateBookInfo();
	UpdateReaderInfo();
	UpdateBorrowerList(); 
}

void bookReturn(char* usrName){
	int code = 0, flag = 0, bookcnt = 0, id = 0;
	int i = 0;
	//ȷ����� 
	for(i=0; i<ReaderAmount; i++){
		if( !strcmp(reader[i].name, usrName) ){
			bookcnt = reader[i].borrowAmount;
			id = reader[i].id;
		}
	}
	RETURN:
	fflush(stdin);
	printf("��������Ҫ���ص�ͼ��ı�ţ�"); 
	scanf("%d",&code);
	if(code>BookAmount) {
		printf("���鲻����\n");
		goto RETURN;
	}
	else{
		book[code-1].inventory++;
		for(i=0; i<reader[id-1].borrowAmount; i++){
			if( reader[id-1].borrow_book_code[i] == code ){
				for(; i<reader[id-1].borrowAmount; i++){
					reader[id-1].borrow_book_code[i] = reader[id-1].borrow_book_code[i+1];
				}
			}
		}
		reader[id-1].borrowAmount--;
		char *des = strstr(BorrowerList[code-1], usrName);
		char p[MAX];
		for(i=0; BorrowerList[code-1]+i<des; i++){
			p[i] = BorrowerList[code-1][i];
		}
		p[i] = '\0';
		des += strlen(usrName);
		if(des != NULL){
			des++;
			strcat(p, des);
		}
		else{
			p[i-1] = '\0';
		}
		strcpy(BorrowerList[code-1], p);
		flag = 1;
	}
	if(flag == 1){
		printf("�ѳɹ��黹����Ŀ\n");
	}
	else{
		printf("����ʧ��\n");
	}
	UpdateBookInfo();
	UpdateReaderInfo(); 
	UpdateBorrowerList();
}

void editUsr(){
	int id, judge = -1;
	char name[20], password[20];
	fflush(stdin);
	printf("��������Ҫ������Ϣ���û��ı�ţ�");
	scanf("%d",&id);
	printf("��ѡ���Ƿ���Ҫ�����û����������ļ���0�������ļ���1����");
	scanf("%d",&judge);
	switch(judge){
		case 0:{
			fflush(stdin);
			printf("�������µ�������");
			gets(name);
			strcpy(reader[id-1].name, name);
			printf("�ѳɹ������û�����\n");
			break;
		}
		case 1:{
			break;
		}
		default : printf("�������\n");
	}
	printf("��ѡ���Ƿ���Ҫ�����û����루���ļ���0�������ļ���1����");
	scanf("%d",&judge);
	switch(judge){
		case 0:{
			fflush(stdin);
			printf("�������µ����룺");
			gets(password);
			strcpy(reader[id-1].key, password);
			printf("�ѳɹ������û�����\n");
			break;
		}
		case 1:{
			break;
		}
		default : printf("�������\n");
	}
	UpdateReaderInfo();
}

void addUsr(){
	char name[20], password[20];
	fflush(stdin);
	printf("��������Ҫ���ӵ��û���������");
	gets(name);
	fflush(stdin);
	printf("�����ø��û������룺");
	scanf("%s",password);
	strcpy(reader[ReaderAmount].name, name);
	strcpy(reader[ReaderAmount].key, password);
	memset(reader[ReaderAmount].borrow_book_code, 0, sizeof(reader[ReaderAmount].borrow_book_code));
	reader[ReaderAmount].borrowAmount = 0;
	ReaderAmount++;
	UpdateUsrID(Reader);
	UpdateReaderInfo();
	printf("�ѳɹ����Ӷ�����Ϣ\n");
}

void delUsr(){
	int id;
	fflush(stdin);
	printf("��������Ҫɾ�����û��ı�ţ�");
	scanf("%d",&id);
	int i = 0;
	for(i=id-1; i<ReaderAmount-1; i++){
		reader[i] = reader[i+1];
	}
	memset(&reader[ReaderAmount-1], 0, sizeof(READER));
	ReaderAmount--;
	UpdateUsrID(Reader);
	UpdateReaderInfo();
	printf("�ѳɹ�ɾ��������Ϣ\n");
}

void UpdateUsrID(ROLE role){
	int i = 0;
	if(role == Reader){
		for(i=0; i<ReaderAmount; i++){
			reader[i].id = i+1;
		}
	}
	else if(role == Manager){
		for(i=0; i<ManagerAmount; i++){
			manager[i].id = i+1; 
		}
	}
}

void UpdateBookID(){
	int i = 0;
	for(i=0; i<BookAmount; i++){
		book[i].code = i+1;
	}
}