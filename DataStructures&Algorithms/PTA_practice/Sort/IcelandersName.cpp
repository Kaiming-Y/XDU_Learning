/*
 * [编程题] 冰岛人
 *  2018年世界杯，冰岛队因1:1平了强大的阿根廷队而一战成名。好事者发现冰岛人的名字后面似乎都有个“松”（son），于是有网友科普如下：
 *  冰岛人沿用的是维京人古老的父系姓制，孩子的姓等于父亲的名加后缀，如果是儿子就加 sson，女儿则加 sdottir。因为冰岛人口较少，为避免近亲繁衍，
 *  本地人交往前先用个 App 查一下两人祖宗若干代有无联系。本题就请你实现这个 App 的功能。
 * #输入格式
 *  输入首先在第一行给出一个正整数 N（1<N≤10^5 ），为当地人口数。随后 N 行，每行给出一个人名，格式为：名 姓（带性别后缀），两个字符串均由
 *  不超过 20 个小写的英文字母组成。维京人后裔是可以通过姓的后缀判断其性别的，其他人则是在姓的后面加 m 表示男性、f 表示女性。题目保证给出的每个维京家族的起源人都是男性。
 *  随后一行给出正整数 M，为查询数量。随后 M 行，每行给出一对人名，格式为：名1 姓1 名2 姓2。注意：这里的姓是不带后缀的。四个字符串均由不超过 20 个小写的英文字母组成。
 *  题目保证不存在两个人是同名的。
 * #输出格式
 *  对每一个查询，根据结果在一行内显示以下信息：
 *  若两人为异性，且五代以内无公共祖先，则输出 Yes；
 *  若两人为异性，但五代以内（不包括第五代）有公共祖先，则输出 No；
 *  若两人为同性，则输出 Whatever；
 *  若有一人不在名单内，则输出 NA。
 *  所谓“五代以内无公共祖先”是指两人的公共祖先（如果存在的话）必须比任何一方的曾祖父辈分高。
 * #输入样例
 *  15
 *  chris smithm
 *  adam smithm
 *  bob adamsson
 *  jack chrissson
 *  bill chrissson
 *  mike jacksson
 *  steve billsson
 *  tim mikesson
 *  april mikesdottir
 *  eric stevesson
 *  tracy timsdottir
 *  james ericsson
 *  patrick jacksson
 *  robin patricksson
 *  will robinsson
 *  6
 *  tracy tim james eric
 *  will robin tracy tim
 *  april mike steve bill
 *  bob adam eric steve
 *  tracy tim tracy tim
 *  x man april mikes
 * #输出格式
 *  Yes
 *  No
 *  No
 *  Whatever
 *  Whatever
 *  NA
 */

#include <iostream>
#include <map>
#define MAXSIZE 100000
using namespace std;

struct Icelander {
    char gender;
    string father;
    explicit Icelander(char gender = '\0', string father = ""):gender(gender), father(move(father)){}
};

int N, M;
map<string, Icelander> maps;

bool judge(const string& p1, const string& p2);

int main(){
    string firstname1, lastname1;
    string firstname2, lastname2;
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> firstname1 >> lastname1;
        //直接由姓氏确定父亲, 用名做映射
        if (lastname1.back() == 'n') maps[firstname1] = Icelander('m', lastname1.substr(0, lastname1.size() - 4));
        else if (lastname1.back() == 'r') maps[firstname1] = Icelander('f', lastname1.substr(0, lastname1.size() - 7));
        else maps[firstname1].gender = lastname1.back();
    }
    cin >> M;
    for (int i = 0; i < M; i++){
        cin >> firstname1 >> lastname1 >> firstname2 >> lastname2;
        if (maps.find(firstname1) == maps.end() || maps.find(firstname2) == maps.end()) cout << "NA" << endl; //改人不存在表中
        else if (maps[firstname1].gender == maps[firstname2].gender) cout << "Whatever" << endl; //两人性别相同
        else cout << (judge(firstname1, firstname2) ? "Yes" : "No") << endl; //既不同性, 也都在表中, 进行祖辈判断
    }
    return 0;
}

bool judge(const string& p1, const string& p2){
    int cnt1 = 1, cnt2; //记录两个人回溯祖辈的次数
    for (string p1_father = p1; !p1_father.empty(); p1_father = maps[p1_father].father, cnt1++) {
        cnt2 = 1;
        for (string p2_father = p2; !p2_father.empty(); p2_father = maps[p2_father].father, cnt2++) {
            if (cnt1 >= 5 && cnt2 >= 5) return true; //5代以内无公共祖先
            else if (p2_father == p1_father) return false; //5代以内有公共祖先
        }
    }
    return true; //两人在祖辈5代内就已经溯源了, 仍然没有公共祖先
}
