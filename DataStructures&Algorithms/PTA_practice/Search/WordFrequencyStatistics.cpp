/*
 * [编程题] 词频统计
 * 请编写程序，对一段英文文本，统计其中所有不同单词的个数，以及词频最大的前10%的单词。
 * 所谓“单词”，是指由不超过80个单词字符组成的连续字符串，但长度超过15的单词将只截取保留前15个单词字符。而合法的“单词字符”为大小写字母、数字和下划线，其它字符均认为是单词分隔符。
 * 输入格式:
 *  输入给出一段非空文本，最后以符号#结尾。输入保证存在至少10个不同的单词。
 * 输出格式:
 *  在第一行中输出文本中所有不同单词的个数。注意“单词”不区分英文大小写，例如“PAT”和“pat”被认为是同一个单词。
 *  随后按照词频递减的顺序，按照词频:单词的格式输出词频最大的前10%的单词。若有并列，则按递增字典序输出。
 * 输入样例：
 *  This is a test.
 *  The word "this" is the word with the highest frequency.
 *  Longlonglonglongword should be cut off, so is considered as the same as longlonglonglonee.  But this_8 is different than this, and this, and this...#
 *  this line should be ignored.
 * 输出样例：（注意：虽然单词the也出现了4次，但因为我们只要输出前10%（即23个单词中的前2个）单词，而按照字母序，the排第3位，所以不输出。）
 *  23
 *  5:this
 *  4:is
 */

#include <iostream>
#include <string>
#include <map>
#include <cstring>
#include <algorithm>

using namespace std;

typedef struct WORD{
    int frequency{};
    string word;
}Word;

bool cmp(Word a, Word b);

int main() {
    Word list[10001];
    memset(list, 0, sizeof (struct WORD) * 10001);
    int txt_length, amount = 0, flag = 0;
    char ch;
    string text, tempWord;
    map<string, int> hash_map;
    while (scanf("%c", &ch) && ch != '#') text += ch; //读取文本
    txt_length = (int)text.size();
    for (int i = 0; i < txt_length; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') text[i] += 32; //将大写统一转化为小写
    }
    for (int i = 0; i < txt_length; i++) {
        if (text[i] >= 'a' && text[i] <= 'z' || text[i] >= '0' && text[i] <= '9' || text[i] == '_') {
            if (tempWord.size() < 15){
                tempWord += text[i]; //若为字母则加入临时单词
                flag = 1;
            }
        } else {
            if (flag) { //一个单词结束
                flag = 0;
                if (hash_map[tempWord] == 0) { //若该词没出现过
                    list[++amount].frequency++;
                    list[amount].word = tempWord; //将该词加入词表
                    hash_map[tempWord] = amount;
                } else {
                    list[hash_map[tempWord]].frequency++; //若出现过直接计数
                }
                tempWord.clear(); //清除临时单词
            }
        }
    }
    sort(list+1, list+amount+1, cmp); //按规则排序
    cout << amount << endl;
    for (int i = 1; i <= amount/10; i++) {
        cout << list[i].frequency << ":" << list[i].word << endl;
    }
}

bool cmp(Word a, Word b) {
    if (a.frequency != b.frequency) return a.frequency > b.frequency; //若频率不等, 按频率排序
    return a.word < b.word; //若频率相等, 按递增字典排序
}