#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

//图书信息 
typedef struct {
	int code;         		//书的编号 
	char name[50];    		//书名 
	int inventory;    		//在库数量 
}BOOK;

//读者信息 
typedef struct {
	int id;           		 //用户编码 
	char name[20];    		 //姓名
	char key[20];			 //密码 
	int borrow_book_code[11];//所借图书编号 （每种书仅允许借1本，最多借10本书）
	int borrowAmount;		 //所借图书数量 
}READER;

//管理员信息 
typedef struct {
	int id;           		//用户编码 
	char name[20];    		//姓名
	char key[20];			//密码 
}MANAGER;

//创建书本、读者、管理员、借还记录对象 
BOOK book[MAX];	 						//MAX种书 
READER reader[MAX];  					//MAX个读者 
MANAGER manager[10]; 					//10个管理员
char BorrowerList[MAX][MAX] = {{'\0'}}; //每本书的借阅者
	
//枚举用户种类（管理员、读者、其他） 
enum ROLE{ Manager = 1, Reader = 2, Other };

//登录 
ROLE login(char* cmd, char* name);

//展示菜单 
void dispMenu(const char* pmt[], int n);

//加载书本信息及借阅者信息 
void loadBookInfo();
//加载读者信息 
void loadReaderInfo();
//加载管理员信息 
void loadManagerInfo();

//更新图书信息 
void UpdateBookInfo();
//更新读者信息 
void UpdateReaderInfo();
//更新管理员信息 
void UpdateManagerInfo();
//更新借阅者信息 
void UpdateBorrowerList();

//图书查询 
void bookQuery();
//展示图书 
void showBook(int i);
//展示读者信息
void showReader(int i); 
//图书入库 
void bookRegister();
//图书移除
void bookRemove();
//用户管理 
void userManagement();
//用户信息查询 
void readerQuery();
//借书 
void bookBorrow(char* usrName);
//还书 
void bookReturn(char* usrName);
//编辑用户信息 
void editUsr();
//增加用户 
void addUsr();
//删除用户 
void delUsr();
//更改用户编号
void UpdateUsrID(ROLE role);
//更改书本编号
void UpdateBookID(); 

//菜单 
const char* ManagerMenu[] = {"1.图书查询", "2.图书入库", "3.图书移除", "4.用户管理", "5.用户信息查询", "0.退出"};
const char* ReaderMenu[] = {"1.图书查询", "2.借书", "3.还书", "0.退出"};

//图书、读者、管理员数量 
int BookAmount;
int ReaderAmount;
int ManagerAmount;

//Libsim -a(-u) xxxx
//第一个参数为可执行程序名称；第二个参数为用户身份，-a表示管理员，-u表示读者；第三个参数为用户名

//主程序 
int main(int argc, char* argv[])
{
	int i,k;
	//初始化，清空结构体 
	for(k=0; k<MAX; k++){
		memset(&book[k], 0, sizeof(BOOK));
		memset(&reader[k], 0, sizeof(READER));
	}
	for(k=0; k<10; k++){
		memset(&manager[k], 0, sizeof(MANAGER));
	}
	//初始化系统，读入书本、读者、管理员信息 
	loadBookInfo();
	loadReaderInfo();
	loadManagerInfo(); 
	//进入系统（用户交互） 
	int cmdNo = 0;
	printf("欢迎使用图书馆管理系统！\n") ;
	ROLE role = login(argv[1], argv[2]); 
	//管理员菜单 
	if( role == Manager ){
		while(1){
			//展示管理员菜单 
			dispMenu( ManagerMenu, sizeof(ManagerMenu) / sizeof(char*) );
			scanf("%d",&cmdNo);
			if( cmdNo == 0 ){
				printf("管理员退出！\n");
				break;
			}
			else{
				switch(cmdNo){
					case 1: bookQuery(); break;
					case 2: bookRegister(); break;
					case 3: bookRemove(); break;
					case 4: userManagement(); break;
					case 5: readerQuery(); break;
					default : printf("输入错误！\n"); 
				}
			}
		} 
	}
	//读者菜单 
	else if ( role == Reader ){
		while(1){
			//展示读者菜单 
			dispMenu( ReaderMenu, sizeof(ReaderMenu) / sizeof(char*) );
			scanf("%d",&cmdNo);
			if( cmdNo == 0 ){
				printf("读者用户退出！\n");
				break;
			}
			else{
				switch(cmdNo){
					case 1: bookQuery(); break;
					case 2: bookBorrow(argv[2]); break;
					case 3: bookReturn(argv[2]); break;
					default : printf("输入错误！\n"); 
				}
			} 
		} 
	}
	//other 
	else{
		printf("\n需要退出系统吗？（输入y退出）\n");
		char ch = getchar();
		if( ch == 'y' || ch == 'Y'){
			printf("再见!\n");
			return 0;
		}
	}
	return 0; 
}

ROLE login(char* cmd, char* name){
	//判断身份 
	ROLE identity;
	char usrName[20], usrKey[20];
	int i, flag = 0;
	strcpy(usrName, name);
	if(!strcmp(cmd, "-a")){
		identity = Manager;
		//核对身份
		CONFIRM_MANAGER_IDENTITY:
		printf("请输入密码：");
		scanf("%s",usrKey); 
		getchar();
		for(i=0; i<ManagerAmount; i++){
			if(!strcmp(usrName, manager[i].name) && !strcmp(usrKey, manager[i].key)){
				printf("登陆成功\n");
				flag = 1;
				break;
			} 
		}
		if(flag == 0){
			printf("用户名不存在或密码错误\n");
			goto CONFIRM_MANAGER_IDENTITY;
		} 
	}
	else if(!strcmp(cmd, "-u")){
		identity = Reader;
		//核对身份
		CONFIRM_READER_IDENTITY:
		printf("请输入密码：");
		scanf("%s",usrKey); 
		getchar();
		for(i=0; i<ReaderAmount; i++){
			if(!strcmp(usrName, reader[i].name) && !strcmp(usrKey, reader[i].key)){
				printf("登陆成功\n");
				flag = 1;
				break;
			} 
		}
		if(flag == 0){
			printf("用户名不存在或密码错误\n");
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
	printf("\n请输入操作选项编号：");
}

void loadBookInfo(){
	FILE *fp = fopen("Books.txt","r");
	FILE *fp1 = fopen("BorrowerList.txt","r"); 
	if(fp == NULL || fp1 == NULL){
		printf("文件打开错误\n"); 
		fclose(fp);
		exit(EXIT_FAILURE); //退出程序
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
		printf("文件打开错误\n"); 
		fclose(fp);
		exit(EXIT_FAILURE); //退出程序
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
		printf("文件打开错误\n"); 
		fclose(fp);
		exit(EXIT_FAILURE); //退出程序
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
		printf("文件打开错误\n"); 
		fclose(fw);
		exit(EXIT_FAILURE); //退出程序
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
		printf("文件打开错误\n"); 
		fclose(fw);
		exit(EXIT_FAILURE); //退出程序
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
		printf("文件打开错误\n"); 
		fclose(fw);
		exit(EXIT_FAILURE); //退出程序
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
		printf("文件打开错误\n"); 
		fclose(fw);
		exit(EXIT_FAILURE); //退出程序
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
		printf("请选择查询方式（输入选项号码即可）；\n1.编号查询\n2.书名查询\n0.退出\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:{
				int code = 0;
				printf("请输入需查询书籍的编号：");
				scanf("%d",&code);
				getchar();
				if(code>BookAmount){
					printf("该书籍不存在\n");
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
				printf("请输入需查询书籍的名字：");
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
					printf("未查询到该书籍\n");
				}
				break;
			}
			case 0: printf("已退出图书查询功能\n"); break; 
			default : printf("输入错误\n");
		} 
	} 
}

void showBook(int i){
	printf("书名：%s\n",book[i].name);
	printf("书籍编号：%d\n",book[i].code);
	printf("库存：%d\n",book[i].inventory);
	printf("借阅者：%s\n",BorrowerList[i]);
}

void showReader(int i){
	printf("读者编号：%d\n",reader[i].id);
	printf("读者姓名：%s\n",reader[i].name);
	printf("读者密码：%s\n",reader[i].key);
	printf("借阅书籍数：%d\n",reader[i].borrowAmount);
	printf("已借阅的书籍编号：");
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
	printf("请输入入库书籍的书名：");
	gets(name);
	fflush(stdin);
	printf("请输入入库的数量：");
	scanf ("%d",&num);
	for(i=0; i<BookAmount; i++){
		//若该书本来就存在，则增加库存 
		if( !strcmp(book[i].name, name) ){
			flag = 1;
			book[i].inventory += num;
			break;
		}
	}
	//若该图书为新书，则增加书的种类 
	if(flag == 0){
		strcpy(book[BookAmount].name, name);
		book[BookAmount].inventory = num;
		book[BookAmount].code = BookAmount+1;
		BookAmount++;
		UpdateBookID();
	}
	UpdateBookInfo();
	printf("已成功入库\n");
}

void bookRemove(){
	int code;
	printf("请输入需要移除的图书的编号：");
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
	printf("已成功移除该书目\n");
}

void userManagement(){
	int choice = -1;
	while(choice != 0){
		printf("请选择需要进行的功能：\n1.读者信息更改\n2.增加读者\n3.删除读者\n0.退出\n");
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
				printf("已退出用户管理功能\n");
				break;
			}
			default: printf("输入错误\n");
		}
	} 
}

void readerQuery(){
	int id;
	fflush(stdin);
	printf("请输入需要查询用户的编号："); 
	scanf("%d",&id);
	if(id>ReaderAmount){
		printf("该用户不存在\n");
	}
	else{
		showReader(id-1);
	}
}

void bookBorrow(char* usrName){
	int code = 0, flag = 0, bookcnt = 0, id = 0;
	int i = 0;
	//确认身份 
	for(i=0; i<ReaderAmount; i++){
		if( !strcmp(reader[i].name, usrName) ){
			bookcnt = reader[i].borrowAmount;
			id = reader[i].id;
		}
	}
	BORROW:
	fflush(stdin);
	printf("请输入需要借出的图书的编号：");
	scanf("%d",&code);
	if(code>BookAmount) {
		printf("该书不存在\n");
		goto BORROW;
	}
	//判定能否借书，并实施 
	if(book[code-1].inventory == 0){
		printf("该书已被借空\n");
	}
	else if(bookcnt>10){
		printf("借书数量已超出限制\n");
	}
	//可以借书 
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
		printf("已成功借出该书目\n");
	}
	else{
		printf("借书失败\n");
	}
	UpdateBookInfo();
	UpdateReaderInfo();
	UpdateBorrowerList(); 
}

void bookReturn(char* usrName){
	int code = 0, flag = 0, bookcnt = 0, id = 0;
	int i = 0;
	//确认身份 
	for(i=0; i<ReaderAmount; i++){
		if( !strcmp(reader[i].name, usrName) ){
			bookcnt = reader[i].borrowAmount;
			id = reader[i].id;
		}
	}
	RETURN:
	fflush(stdin);
	printf("请输入需要还回的图书的编号："); 
	scanf("%d",&code);
	if(code>BookAmount) {
		printf("该书不存在\n");
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
		printf("已成功归还该书目\n");
	}
	else{
		printf("还书失败\n");
	}
	UpdateBookInfo();
	UpdateReaderInfo(); 
	UpdateBorrowerList();
}

void editUsr(){
	int id, judge = -1;
	char name[20], password[20];
	fflush(stdin);
	printf("请输入需要更改信息的用户的编号：");
	scanf("%d",&id);
	printf("请选择是否需要更改用户姓名（更改键入0，不更改键入1）：");
	scanf("%d",&judge);
	switch(judge){
		case 0:{
			fflush(stdin);
			printf("请输入新的姓名：");
			gets(name);
			strcpy(reader[id-1].name, name);
			printf("已成功更改用户姓名\n");
			break;
		}
		case 1:{
			break;
		}
		default : printf("输入错误\n");
	}
	printf("请选择是否需要更改用户密码（更改键入0，不更改键入1）：");
	scanf("%d",&judge);
	switch(judge){
		case 0:{
			fflush(stdin);
			printf("请输入新的密码：");
			gets(password);
			strcpy(reader[id-1].key, password);
			printf("已成功更改用户密码\n");
			break;
		}
		case 1:{
			break;
		}
		default : printf("输入错误\n");
	}
	UpdateReaderInfo();
}

void addUsr(){
	char name[20], password[20];
	fflush(stdin);
	printf("请输入需要增加的用户的姓名：");
	gets(name);
	fflush(stdin);
	printf("请设置该用户的密码：");
	scanf("%s",password);
	strcpy(reader[ReaderAmount].name, name);
	strcpy(reader[ReaderAmount].key, password);
	memset(reader[ReaderAmount].borrow_book_code, 0, sizeof(reader[ReaderAmount].borrow_book_code));
	reader[ReaderAmount].borrowAmount = 0;
	ReaderAmount++;
	UpdateUsrID(Reader);
	UpdateReaderInfo();
	printf("已成功增加读者信息\n");
}

void delUsr(){
	int id;
	fflush(stdin);
	printf("请输入需要删除的用户的编号：");
	scanf("%d",&id);
	int i = 0;
	for(i=id-1; i<ReaderAmount-1; i++){
		reader[i] = reader[i+1];
	}
	memset(&reader[ReaderAmount-1], 0, sizeof(READER));
	ReaderAmount--;
	UpdateUsrID(Reader);
	UpdateReaderInfo();
	printf("已成功删除读者信息\n");
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