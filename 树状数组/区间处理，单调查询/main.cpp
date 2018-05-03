/**HDOJ1556 color the boll
������������������a �����ֲ���1������[l,r]����,�����������ڵĶ���+1  2����a[t]

˼·������һ��C���飬C[0]+C[1]+...C[t] ����a[t]��ֵ
����1ʱ���� l,r,delta ��C[l] += delta ,C[r+1] -= delta
��Ϊʹ�õ�����Ͳ��������Ժ��ʺ�����״����



���ﲹ����״��������ʹ������
����͵�������a[maxn], ��״����C[maxn]

C[pos]��ʾ���� ��pos��ǰ��k���� a[]����ĺͣ�����pos����
k����˼�� pos�Ķ����Ʊ�ʾ ĩβ0����Ϊt ��ôk=pow(2,t),�ٸ����� 6 = 110 ��ôk=2
�׳��������⣬�����벿��

����1����ô���pos��Ӧ��k��ֵ��
��return pos & -pos;

����ı�ʾ�������ǣ�һ�����ķ�����ǴӺ����������һ�γ���1��ʱΪi�� ��ôi֮ǰȡ����i��i֮�󲻱�
���� 6 = 110 ȡ��Ϊ010 ���а�λ�� ���ܵõ�10


����2���õ�C[]���飬������a[i]�����ǰ׺���أ�
int Sum(int pos)
{
    int sum = 0;
    while(pos >= 1)
    {
        sum += c[pos];
        pos = pos - Lowbit(pos);
    }
    return sum;
}

���ﻹ�ý��PDF��ͼƬ��⣬�ٿ����룬������a[7]��ǰ׺�� ����֪��7->111 ��Lowbit(7) = 1 ������C[7]��ʾһ�����鼴a[7]
��ôpos������ǰ�ƽ�������C[6]��ֵ��Lowbit(6) = 2 , ����ִ����

����3:��Ȼc[i]�����ֵ Ӱ�쵽 c[j] j>i �����ֵ����ô�޸�ʱҪע��ʲô�أ�
int Update(int pos,int delta)
{
    while(pos <= n)
    {
        c[pos]+= delta;
        pos += Lowbit(pos);
    }
}
�����ǿ�ͼ�Ϳ�����˵��������޸�4 Lowbit(4)= 4 ��Ҫ�޸� 4 + 4 ��λ


*/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
const int maxn = 100050;
typedef long long ll;

ll c[maxn];
int n,k;

int Lowbit(int pos)
{
    return pos &(-pos);
}

int Sum(int pos)
{
    int sum = 0;
    while(pos >= 1)
    {
        sum += c[pos];
        pos = pos - Lowbit(pos);
    }
    return sum;
}

int Update(int pos,int delta)
{
    while(pos <= n)
    {
        c[pos]+= delta;
        pos += Lowbit(pos);
    }
}

int main()
{
     while(scanf("%d",&n) !=EOF)
     {
         if(n==0) break;
         memset(c,0,sizeof(c));
         int a,b;
         for(int i=1;i<=n;i++)
         {
             scanf("%d%d",&a,&b);
             Update(a,1);
             Update(b+1,-1);//ע�⣬��b+1
         }
         for(int i=1;i<=n;i++)
         {
             if(i != 1) printf(" ");
             printf("%d",Sum(i));
         }
         printf("\n");
     }
    return 0;
}
