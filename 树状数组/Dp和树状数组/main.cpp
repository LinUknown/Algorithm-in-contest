/**
���������� ����һ�����У� �󳤶ȵ���k+1 �����������еĸ���

˼·��  ���Թ���DP[len][j] ��ʾ��j��β��������j+1֮ǰ���ĳ���Ϊlen �����������и���
״̬ת�ƹ�ʽ��dp[len][j] = dp[len-1][1] + dp[len-1][2] + ...+ dp[len-1][j-1]
���ص��㷨�Ǳ���j->(1,n), len ->(1,k+1),��ÿ��dp[len][j]��Ҫ��͡�ʱ�临�Ӷ�o(k*n*n)
����ע�⵽dp[len][j]ֻ�Ƕ�֮ǰ����ͼ��㣬������״������ص㣬��˼��롣 ʱ�临�Ӷ�o(k*n*logn)

*/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
const int maxn = 100005;
typedef long long ll;

ll c[12][maxn];
int n,k;

int Lowbit(int pos)
{
    return pos &(-pos);
}

ll Sum(int len,int pos)
{
    ll sum = 0;
    while(pos >= 1)
    {
        sum += c[len][pos];
        pos = pos - Lowbit(pos);
    }
    return sum;
}

//���ȣ�����ֵ������
void Update(int len,int pos,ll delta)
{
    while(pos <= n)
    {
        c[len][pos]+= delta;
        pos += Lowbit(pos);
    }
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        Update(1,x,1);
        //����һ������������Ҳ���Ǹ��Ӵ�������Ϊ1������Ϊ1
        for(int len = 2;len<=k+1;len++)
        {
            int temp = Sum(len-1, x-1);
            //��x֮ǰ�ģ�����Ϊlen-1 �ĸ�����dp[len][x] �������ǵĻ���������temp��
            Update(len, x, temp);
        }
    }
    cout<<Sum(k+1,n)<<endl;
    return 0;
}
