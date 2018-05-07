/*#include <iostream>
#include <bits/stdc++.h>
using namespace std;
const int maxn = 55555;
int sum[maxn << 2];
int add[maxn << 2];
int n;
void Pushup(int pos)
{
    sum[pos] = sum[pos * 2] + sum[pos*2+1];

}
void PushDown(int rt , int m)
{
    if(add[rt])
    {
        add[rt << 1] += add[rt];
        add[rt << 1 | 1] += add[rt];
        sum[rt << 1] += add[rt] * (m - (m >> 1));
        sum[rt << 1 | 1] += add[rt] * (m >> 1);
        add[rt] = 0;
    }
}


void build(int l,int r,int rt)
{
    add[rt] = 0;
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
void update(int L,int R, int c, int l, int r, int rt)
{
    if(L <= l && r <= R)
    {   add[rt] += c;
        sum[rt] += c * (r-l+1);
        return;
    }
    PushDown(rt, r-l+1);

    int m = (l + r) /2;
    if(L <= m)
        update(L,R,c,l,m,rt*2);
    if(m < R)
        update(L,R,c,m+1,r,rt*2+1);

    Pushup(rt);

}


int query(int L,int R,int l,int r,int rt)
{

    if(L <= l && R >= r)
    {
        return sum[rt];

    }
    PushDown(rt, r-l+1);

    int m = (l + r)/2;
    int temp = 0;
    if(L <= m)
        temp += query(L,R,l,m,rt*2);
    if(R > m)
        temp += query(L,R,m+1,r,rt*2+1);
    return temp;
}
int main()
{   int a = 1, b = 4, c = 3,n = 5;
    build(1,n,1);
    printf("%d\n",query(a,b,1,n,1));
    update(a,b-1,c,1,n,1);
    printf("%d\n",query(a,b,1,n,1));

    return 0;
}
*/
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 100005;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1

__int64 sum[N<<2],add[N<<2];
struct Node
{
    int l,r;
    int mid()
    {
        return (l+r)>>1;
    }
} tree[N<<2];

void PushUp(int rt)
{
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}

void PushDown(int rt,int m)
{
    if(add[rt])
    {
        add[rt<<1] += add[rt];
        add[rt<<1|1] += add[rt];
        sum[rt<<1] += add[rt] * (m - (m>>1));
        sum[rt<<1|1] += add[rt] * (m>>1);
        add[rt] = 0;
    }
}

void build(int l,int r,int rt)
{
    tree[rt].l = l;
    tree[rt].r = r;
    add[rt] = 0;
    if(l == r)
    {
        scanf("%I64d",&sum[rt]);
        return ;
    }
    int m = tree[rt].mid();
    build(lson);
    build(rson);
    PushUp(rt);
}

void update(int c,int l,int r,int rt)
{
    if(tree[rt].l == l && r == tree[rt].r)
    {
        add[rt] += c;
        sum[rt] += (__int64)c * (r-l+1);
        return;
    }
    if(tree[rt].l == tree[rt].r) return;
    PushDown(rt,tree[rt].r - tree[rt].l + 1);
    int m = tree[rt].mid();
    if(r <= m) update(c,l,r,rt<<1);
    else if(l > m) update(c,l,r,rt<<1|1);
    else
    {
        update(c,l,m,rt<<1);
        update(c,m+1,r,rt<<1|1);
    }
    PushUp(rt);
}

__int64 query(int l,int r,int rt)
{
    if(l == tree[rt].l && r == tree[rt].r)
    {
        return sum[rt];
    }
    PushDown(rt,tree[rt].r - tree[rt].l + 1);
    int m = tree[rt].mid();
    __int64 res = 0;
    if(r <= m) res += query(l,r,rt<<1);
    else if(l > m) res += query(l,r,rt<<1|1);
    else
    {
       res += query(l,m,rt<<1);
       res += query(m+1,r,rt<<1|1);
    }
    return res;
}

int main()
{
    int n,m;
    while(~scanf("%d %d",&n,&m))
    {
        build(1,n,1);
        while(m--)
        {
            char ch[2];
            scanf("%s",ch);
            int a,b,c;
            if(ch[0] == 'Q')
            {
                scanf("%d %d", &a,&b);
                printf("%I64d\n",query(a,b,1));
            }

            else
            {
                scanf("%d %d %d",&a,&b,&c);
                update(c,a,b,1);
            }
        }
    }
    return 0;
}
