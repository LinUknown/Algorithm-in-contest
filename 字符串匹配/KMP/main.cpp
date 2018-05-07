/*kmp算法 N字串希望在H字串中找到匹配的位置

H aabaab
N aabaac

当匹配到最后一个字符时，匹配失败，朴素的算法是

H aabaab
N  aabaac

kmp算法是

H aab*aab

N     aab#aac

N，h 从上一次匹配成功的位置 的最大前缀 等于后缀的地方 开始匹配
H的指针退回到*的位置， N的指针退回到#的位置，然后比较H[begin + matched] == ? N[matched]

*/



#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/*求pi数组 ,终极思想就是，那本身的N当成模式串，和N 匹配。
当模式串在母串找到相匹配的位置i（模式串不一定完全匹配），
那么p[i] = len(相匹配的长度) ， 换句话说p[...i] 内最大的前缀等于后缀的 子串长度=len

 mu: aabbcaa
 模式:aabbcaa
       aabbcaa
        aabbcaa

*/
vector<int> getPartialMath(const string& N)
{
    int m = N.size();
    vector <int>pi(m,0);
    int begin = 1, matched = 0;
    while(begin + matched < m)
    {
        if(N[begin + matched ] == N[matched])
        {
            ++matched;
            pi[begin+matched-1] = matched;
        }
        else
        {
            if(matched == 0)
                ++begin;
            else
            {
                begin += matched - pi[matched -1];
                matched = pi[matched -1];
            }
        }
    }
    return pi;
}


//N是模式串，H是母串
vector<int> kmpSearch(const string& H, const string& N)
{
    int n = H.size(), m = N.size();
    vector<int> ret;
    //p[i] = N[:i] 既是前缀又是后缀的字符串最大长度
    vector <int> pi = getPartialMath(N);
    int begin = 0, matched = 0;//H,N的index

    while(begin <= n-m)
    {
        //cout<<H[begin + matched]<<"  matched  "<< N[matched]<<"   "<<begin<<"  be and matc "<<matched<<endl;
        if(matched <m && H[begin + matched] == N[matched])
        {
            ++matched;
            if(matched == m)
                ret.push_back(begin); // 匹配成功
        }
        else
        {
            if(matched == 0)
                ++begin;
            else
            {
                begin += matched - pi[matched-1];
                /*begin 朴素的算法是加上 1 ,但是我们知道有pi[matched-1] 这么多个东西已经匹配成功，
                那么begin从这里开始(跨过匹配过的一段)
                matched 没问题，退回到p[matched -1]
                matched-1 是上一次匹配未失败的位置*/
                matched = pi[matched-1];
            }
        }
    }

    return ret;
}
int main()
{   string H = "aabaabaac*aabaac";
    string N = "aabaac";
    vector <int> kmp = kmpSearch(H,N);
    for(vector<int>::iterator it = kmp.begin();it != kmp.end(); it++)
        cout<<*it<<endl;
    return 0;
}
