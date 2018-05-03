/**HDOJ1556 color the boll
问题描述：给定序列a 有两种操作1）处理[l,r]区间,本题是区间内的东西+1  2）求a[t]

思路：建立一个C数组，C[0]+C[1]+...C[t] 代表a[t]的值
操作1时例如 l,r,delta 则C[l] += delta ,C[r+1] -= delta
因为使用到了求和操作，所以很适合用树状数组



这里补上树状数组的理解和代码分析
待求和的数组是a[maxn], 树状数组C[maxn]

C[pos]表示的是 从pos向前数k个数 a[]数组的和（包含pos），
k的意思是 pos的二进制表示 末尾0个数为t 那么k=pow(2,t),举个例子 6 = 110 那么k=2
抛出三个问题，理解代码部分

问题1：怎么求得pos对应的k的值？
答：return pos & -pos;

反码的表示告诉我们，一个数的反码就是从后面数，令第一次出现1的时为i， 那么i之前取反，i和i之后不变
例如 6 = 110 取反为010 进行按位与 就能得到10


问题2：得到C[]数组，如何求得a[i]数组的前缀和呢？
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

这里还得结合PDF的图片理解，再看代码，比如求a[7]的前缀和 我们知道7->111 则Lowbit(7) = 1 ，所以C[7]表示一个数组即a[7]
那么pos继续向前推进，加上C[6]的值，Lowbit(6) = 2 , 继续执行完

问题3:既然c[i]数组的值 影响到 c[j] j>i 数组的值，那么修改时要注意什么呢？
int Update(int pos,int delta)
{
    while(pos <= n)
    {
        c[pos]+= delta;
        pos += Lowbit(pos);
    }
}
依旧是看图和看代码说话，如果修改4 Lowbit(4)= 4 则要修改 4 + 4 这位


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
             Update(b+1,-1);//注意，是b+1
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
