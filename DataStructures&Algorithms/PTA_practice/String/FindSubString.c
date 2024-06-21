/*
 * [函数题]
 * [题目名称]查找子串
 * [题目描述]
 *  C语言标准函数库中包括 strstr 函数，在主串中查找子串。作为练习，我们自己编写一个功能与之相同的函数
 * [函数原型]
 *      char* StrStr(const char *txt, const char *pat);
 *  说明: txt 和 pat 分别为主串和子串的起始地址。若查找成功，则函数值为子串在主串中首次出现的起始地址，否则函数值为NULL
 *  特别地，我们对C语言库函数strstr进行适当修改：若子串为空串，则没有意义，函数值规定为NULL
 * [输入样例]
 *  This is a pencil
 *  is
 * [输出样例]
 *  2
 */

#include <stdio.h>
#include <string.h>

char* StrStr(const char *txt, const char *pat);

int main()
{
    char m[1024], s[1024], *p;
    gets(m);
    gets(s);
    p = StrStr(m, s);
    if (p)
    {
        printf("%d\n", p - m);
    }
    else
    {
        puts("NULL");
    }
    return 0;
}

char* StrStr(const char *txt, const char *pat){
    char *p;
    int isFound = 0;
    for (p = (char*)txt; *p != '\0'; p++) {
        if (*p == pat[0]) {
            char *q;
            int i = 0;
            int flag = 0;
            for (q = p; *q != '\0' && pat[i] != '\0'; q++, i++) {
                if(*q != pat[i]){
                    flag = -1;
                    break;
                }
            }
            if (*q == '\0' && pat[i] != '\0') flag = -1;
            if (flag == 0) {
                isFound = 1;
                break;
            }
        }
    }
    if (isFound) return p;
    else return NULL;
}