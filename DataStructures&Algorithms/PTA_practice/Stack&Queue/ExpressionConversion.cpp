/*
 * [编程题]
 * 算术表达式有前缀表示法、中缀表示法和后缀表示法等形式。日常使用的算术表达式是采用中缀表示法，即二元运算符位于两个运算数中间。请设计程序将中缀表达式转换为后缀表达式。
 * 输入格式:
 *  输入在一行中给出不含空格的中缀表达式，可包含+、-、*、\以及左右括号()，表达式不超过20个字符。
 * 输出格式:
 *  在一行中输出转换后的后缀表达式，要求不同对象（运算数、运算符号）之间以空格分隔，但结尾不得有多余空格。
 * 输入样例:
 *  2+3*(7-4)+8/4
 * 输出样例:
 *  2 3 7 4 - * + 8 4 / +
 */

#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main (){
    stack<char> exp;
    bool flag = false; //标记数字前面是否有运算符
    string s;
    cin>>s;
    for(int i=0; i<s.size(); i++){
        //运算数直接输出
        if(s[i] >= '0' && s[i] <= '9' || s[i] == '.'){
            if (i==0 || !flag) cout << s[i];
            else if (i>0) {
                if(s[i-1] >= '0' && s[i-1] <= '9' || s[i-1] == '.' || s[i] == '.') {
                    cout << s[i];
                } else {
                    cout << " " << s[i];
                }
            }
            flag = false;
        } else if (s[i] == '(') {
            //控制括号嵌套的输出格式
            if (i==0) flag = false;
            else if (s[i-1] == '(') {
                flag = false;
            }
            else flag = true;
            exp.push('('); //左括号直接压入栈
        } else if (s[i] == ')') {
            //将栈顶的运算符弹出, 直到遇见做左括号
            while (exp.top() != '(') {
                cout << " " << exp.top();
                exp.pop();
            }
            exp.pop(); //将左括号弹出栈, 但不输出
        } else if (s[i] == '+' || s[i] == '-') {
            /*
             * 关于运算符:
             * 若优先级大于栈顶运算符, 直接把他压入栈
             * 若优先级小于等于栈顶运算符, 把栈顶运算符弹出并输出; 再比较新的栈顶运算符, 直到该运算符优先级大于栈顶运算符优先级为止. 最后将该运算符压栈
             */
            if (i==0){
                flag = false;
                cout << (s[i]=='-'?"-":""); //若加减号在开头, 开头不空格, 并作为正负号格式化输出
                continue;
            } else if (i<s.size()-1 && s[i+1]>='0' && s[i+1]<='9' && (s[i-1]<'0' || s[i-1]>'9') && s[i-1]!=')') {
                flag = false;
                cout << " " << (s[i]=='-'?"-":""); //若正加减号在式子中, 要输出空格, 作为正负号直接输出
                continue;
            } else {
                flag = true; //作为运算符的加减号进行后续优先级判断
            }
            if (exp.empty()) {
                exp.push(s[i]);
            } else if ( exp.top() == '+' || exp.top() == '-' || exp.top() == '(') {
                exp.push(s[i]);
            } else {
                while (!exp.empty()) {
                    if(exp.top() == '(') break;
                    cout << " " << exp.top();
                    exp.pop();
                }
                exp.push(s[i]);
            }
        } else if (s[i] == '*' || s[i] == '/') {
            flag = true;
            if (exp.empty()) exp.push(s[i]);
            else if (exp.top() == '+' || exp.top() == '-' || exp.top() == '(') exp.push(s[i]);
            else {
                while (!exp.empty()) {
                    if(exp.top() == '+' || exp.top() == '-' || exp.top() == '(') break;
                    else {
                        cout << " " << exp.top();
                        exp.pop();
                    }
                }
                exp.push(s[i]);
            }
        }
    }
    //若处理结束后仍有符号在栈中, 则依次输出
    while (!exp.empty()) {
        cout << " " << exp.top();
        exp.pop();
    }
    return 0;
}