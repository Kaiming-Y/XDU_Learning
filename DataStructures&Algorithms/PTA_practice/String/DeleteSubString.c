/*
 * [函数题]
 * [题目名称] 删除子串
 * [题目描述]
 *  请编写函数，删除子串。
 * [函数原型]
 *      char* StrRemove(char *str, int idx, int len);
 *  说明：str 为指示字符串起始地址的指针，idx 为子串的起始位置(下标)，len 为子串的长度。函数删除字符串 str 中从下标 idx 处开始、长度为 len 的子串，
 *       函数值为 str。若 len 值不正确，则自动修正。若 idx 值不正确，则不删除子串。
 *  要求：直接在原数组上完成操作，不要借助其它数组。
 * [输入样例]
 *  abcd
 *  1 2
 * [输出样例]
 *  ad
 */

#include <stdio.h>
#include <string.h>

char* StrRemove(char *str, int idx, int len);

int main()
{
    char a[1024];
    int i, n;
    gets(a);
    scanf("%d%d", &i, &n);
    StrRemove(a, i, n);
    puts(a);
    return 0;
}

char* StrRemove(char *str, int idx, int len) {
    int i, flag = 0;
    int left = (int)strlen(str);
    if (idx >= left || idx < 0) return str; //若idx值不正确, 则不删除子串
    if(len < 0) len = 0;
    else if (idx + len > left) len = left - idx; //修正len
    for( i = idx, left -= idx; left > 0; left--, i++){
        if (flag == 0 && str[i+len] != '\0') str[i] = str[i+len];
        else {
           flag = -1;
           str[i] = '\0';
        }
    }
    return str;
}