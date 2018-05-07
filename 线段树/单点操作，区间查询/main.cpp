#include <iostream>
#include <bits/stdc++.h>
using namespace std;
const int maxn = 55555;
int sum[maxn << 2];
int n;
void Pushup(int pos)
{
    sum[pos] = sum[pos * 2] + sum[pos*2+1];
    /* 父节点的值由左右子节点的值决定
      sum[1] = sum[2] + sum[2 + 1];*/
}

//线段树通过l，r 定位到该点对应的rt，
void build(int l,int r,int rt)
{
    if(l == r)
    {
        scanf("%d",&sum[rt]);
        return;
    }
    int m = (l + r) / 2;
    build(l,m,rt*2);
    build(m+1,r,rt*2 +1);
    Pushup(rt);

}
void update(int p,int add, int l,int r,int rt)
{
    if(l == r)
    {
        sum[rt] += add;
        return;
    }
    int m = (l + r) /2;
    if(p <= m) // 这里进行定位点的判断，二分查找思想
        update(p,add,l,m,rt*2);
    else
        update(p,add,m+1,r,rt*2+1);

    Pushup(rt);
    //从根节点 1 出发， 那么根节点的值 就由 左右子树的值确定
}
//查询，目标内容的L，R ， 和一开始为(1,n)的 lr ，以及根节点1

int query(int L,int R,int l,int r,int rt)
{
    /* 查询过程中，目标区间（L，R）是不变的 ，变化的是1 r
    当查询的l r在目标之内时，那么这个值就是我们需要的，
    L l r R*/
    if(L <= l && R >= r)
    {
        return sum[rt];

    }
    int m = (l + r)/2;
    int temp = 0;
    if(L <= m)
        temp += query(L,R,l,m,rt*2);
    if(R > m)
        temp += query(L,R,m+1,r,rt*2+1);
    return temp;
}
int main()
{
    int t;
    int cas = 1;
    scanf("%d",&t);
    while(t--)
    {
        printf("Case %d:\n",cas++);
        scanf("%d",&n);
        build(1,n,1);
        string st;
        while(cin>>st)
        {
            if(st[0] =='E')
                break;
            int a,b;
            scanf("%d%d",&a,&b);
            if(st[0] == 'Q')
            {
                printf("%d\n",query(a,b,1,n,1));
            }
            else if(st[0] == 'S')
            {
                update(a,-b,1,n,1);
            }
            else
            {
                update(a,b,1,n,1);
            }
        }
    }

    return 0;
}
