#include <iostream>
#include <bits/stdc++.h>
using namespace std;
const int maxn = 55555;
int sum[maxn << 2];
int n;
void Pushup(int pos)
{
    sum[pos] = sum[pos * 2] + sum[pos*2+1];
    /* ���ڵ��ֵ�������ӽڵ��ֵ����
      sum[1] = sum[2] + sum[2 + 1];*/
}

//�߶���ͨ��l��r ��λ���õ��Ӧ��rt��
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
    if(p <= m) // ������ж�λ����жϣ����ֲ���˼��
        update(p,add,l,m,rt*2);
    else
        update(p,add,m+1,r,rt*2+1);

    Pushup(rt);
    //�Ӹ��ڵ� 1 ������ ��ô���ڵ��ֵ ���� ����������ֵȷ��
}
//��ѯ��Ŀ�����ݵ�L��R �� ��һ��ʼΪ(1,n)�� lr ���Լ����ڵ�1

int query(int L,int R,int l,int r,int rt)
{
    /* ��ѯ�����У�Ŀ�����䣨L��R���ǲ���� ���仯����1 r
    ����ѯ��l r��Ŀ��֮��ʱ����ô���ֵ����������Ҫ�ģ�
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
