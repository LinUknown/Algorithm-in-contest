/**
问题描述： 给定一个序列， 求长度等于k+1 的上升子序列的个数

思路：  可以构建DP[len][j] 表示以j结尾（序列在j+1之前）的长度为len 的上升子序列个数
状态转移公式：dp[len][j] = dp[len-1][1] + dp[len-1][2] + ...+ dp[len-1][j-1]
朴素的算法是遍历j->(1,n), len ->(1,k+1),而每个dp[len][j]都要求和。时间复杂度o(k*n*n)
我们注意到dp[len][j]只是对之前做求和计算，符合树状数组的特点，因此加入。 时间复杂度o(k*n*logn)

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

//长度，数的值，个数
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
        //加入一个数，则自身也算是个子串，长度为1，个数为1
        for(int len = 2;len<=k+1;len++)
        {
            int temp = Sum(len-1, x-1);
            //在x之前的，长度为len-1 的个数，dp[len][x] 会在他们的基础上增加temp个
            Update(len, x, temp);
        }
    }
    cout<<Sum(k+1,n)<<endl;
    return 0;
}
