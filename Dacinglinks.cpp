#include<iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include<vector>
#include<algorithm>
#include<cstring>
#define RE freopen("in.txt","r",stdin);
const int MAXN=44;
const int MAXC=MAXN;
const int MAXR=MAXN;
const int MAXM=MAXC*MAXR;
const int inf = MAXN;

using namespace std;

struct Point
{
    int x,y;
};

int L[MAXM],R[MAXM],U[MAXM],D[MAXM],C[MAXM],RO[MAXM];//LRUD十字链表，C列号，H行号
int S[MAXC],H[MAXR];//S列容量
int O[MAXN],O2[MAXN];//答案
Point a[MAXN];//坐标
int head,ans;
int n,r,size;

long long dis2(int x,int y)
{
    long long dx=a[x].x-a[y].x;
    long long dy=a[x].y-a[y].y;
    return dx*dx+dy*dy;
}

void remove(int c){//把c在的那一列的节点全删了
    for (int i=D[c]; i!=c; i=D[i])
        L[R[i]]=L[i], R[L[i]]=R[i], S[C[i]]--;
}
void resume(int c){//把c在的那一列的节点全恢复了
    for (int i=U[c]; i!=c; i=U[i])
        L[R[i]]=R[L[i]]=i, S[C[i]]++;
}

int h(){//A*的估价函数，超碉
    bool vis[MAXM];
    int ret=0,i,j,k;
    memset (vis, false, sizeof(vis));
    for (i=R[0]; i; i=R[i])
    {
        if(vis[i])continue;
        ret++;
        vis[i]=true;
        for (j=D[i]; j!=i; j=D[j])
            for (k=R[j]; k!=j; k=R[k])
                vis[C[k]]=true;
    }
    return ret;
}

bool dfs(int k)
{
    if(k+h()>=ans) return false;
    if (R[0]==0)
    {
        if(k<ans)
        {
            ans=k;
            for(int i=0; i<ans; i++)
                O2[i]=O[i];
        }
        return true;
    }
    int c=R[0];
    for (int i=R[0]; i; i=R[i])
        if(S[i]<S[c])c=i;
    //找到c为元素最少的一列
    for (int i=D[c]; i!=c; i=D[i])
    {
        remove(i);
        O[k]=RO[i];
        for (int j=R[i]; j!=i; j=R[j])
        {
            remove(j);
            S[C[j]]--;
        }
        //删了与i行有交点的所有列，即在第i个城市扔炸弹，把这些列表示的城市都炸了
        dfs(k+1);
        for (int j=L[i]; j!=i; j=L[j])
        {
            resume(j);
            S[C[j]]++;
        }
        resume(i);
        //恢复
    }
    return false;
}

void init()
{
    int i,j,k;
    for(i=0;i<=n;i++)// 建立每一列的头指针
    {
        L[i] = i-1;
        R[i] = i+1;
        U[i]=D[i]=C[i]=i;// 初始化，相当于m个列链表的头指针
        S[i] = 0;
    }
    head=0;//head初始化
    L[0]=n;R[n]=0;
    size=n+1;
    memset(H,-1,sizeof(H));
}

void Link(int r,int c)
{
    RO[size]=r;
    C[size]=c;
    S[c]++;

    U[size]=U[c];
    D[U[c]]=size;
    D[size]=c;
    U[c]=size;

    if(H[r]==-1) H[r]=L[size]=R[size]=size;
    else
    {
        L[size]=L[H[r]];
        R[L[size]]=size;
        R[size]=H[r];
        L[R[size]]=size;
    }
    size++;
}

int farm()
{
    int i,j,k;
    long long rr=r*r;
    init();
    for(i=1; i<=n; i++)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
        for(j=1; j<i; j++)
            if(dis2(i,j)<=rr)
            {
                Link(i,j);
                Link(j,i);
            }
        Link(i,i);
    }
    ans=inf;
    dfs(0);
    //sort(O2,O2+ans);
    printf("%d\n",ans);
    for(i=0; i<ans-1; i++)
    {
        printf("%d ",O2[i]);
    }
    printf("%d\n",O2[i]);
    return 0;
}


int main()
{
    //RE
    while(scanf("%d%d",&n,&r)!=EOF)
    {
        farm();
    }
    return 0;
}
