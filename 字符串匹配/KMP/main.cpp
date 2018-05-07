/*kmp�㷨 N�ִ�ϣ����H�ִ����ҵ�ƥ���λ��

H aabaab
N aabaac

��ƥ�䵽���һ���ַ�ʱ��ƥ��ʧ�ܣ����ص��㷨��

H aabaab
N  aabaac

kmp�㷨��

H aab*aab

N     aab#aac

N��h ����һ��ƥ��ɹ���λ�� �����ǰ׺ ���ں�׺�ĵط� ��ʼƥ��
H��ָ���˻ص�*��λ�ã� N��ָ���˻ص�#��λ�ã�Ȼ��Ƚ�H[begin + matched] == ? N[matched]

*/



#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/*��pi���� ,�ռ�˼����ǣ��Ǳ����N����ģʽ������N ƥ�䡣
��ģʽ����ĸ���ҵ���ƥ���λ��i��ģʽ����һ����ȫƥ�䣩��
��ôp[i] = len(��ƥ��ĳ���) �� ���仰˵p[...i] ������ǰ׺���ں�׺�� �Ӵ�����=len

 mu: aabbcaa
 ģʽ:aabbcaa
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


//N��ģʽ����H��ĸ��
vector<int> kmpSearch(const string& H, const string& N)
{
    int n = H.size(), m = N.size();
    vector<int> ret;
    //p[i] = N[:i] ����ǰ׺���Ǻ�׺���ַ�����󳤶�
    vector <int> pi = getPartialMath(N);
    int begin = 0, matched = 0;//H,N��index

    while(begin <= n-m)
    {
        //cout<<H[begin + matched]<<"  matched  "<< N[matched]<<"   "<<begin<<"  be and matc "<<matched<<endl;
        if(matched <m && H[begin + matched] == N[matched])
        {
            ++matched;
            if(matched == m)
                ret.push_back(begin); // ƥ��ɹ�
        }
        else
        {
            if(matched == 0)
                ++begin;
            else
            {
                begin += matched - pi[matched-1];
                /*begin ���ص��㷨�Ǽ��� 1 ,��������֪����pi[matched-1] ��ô��������Ѿ�ƥ��ɹ���
                ��ôbegin�����￪ʼ(���ƥ�����һ��)
                matched û���⣬�˻ص�p[matched -1]
                matched-1 ����һ��ƥ��δʧ�ܵ�λ��*/
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
