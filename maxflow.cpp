//ISAP+当前弧+GAP，邻接表，起点为st终点为ed，先输入m再输入n
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
typedef int lll;
const int maxn=222;//点数
const int maxm=444444;//边数
const lll inf=0x7fffffff;//MAXINT
struct vnode
{
    int v,next;
    lll cap;
}e[maxm];
 int head[maxn],cnt;
int h[maxn],g[maxn],d[maxn];//g[i]为标号为i的结点个数，h[i]为i结点的标号，d[]当前弧优化，记录当前弧
bool found;
int n,m,st,ed;//n个点m条边
lll augc,flow;//augc为增广路容量，flow为最大流
void add(int x,int y,lll z)
{
    e[cnt].v=y;e[cnt].cap=z;
    e[cnt].next=head[x];
    head[x]=cnt++;
    e[cnt].v=x;e[cnt].cap=0;
    e[cnt].next=head[y];
    head[y]=cnt++;
}

void aug(const int m)
{
    int i,mini,minh=n-1;
    lll augco=augc;
    if (m==ed)//如果当前结点为汇点
    {
        found=true;
        flow+=augc;	//增加流量
        return;
    }
    for (i=d[m]; i!=-1; i=e[i].next)//寻找容许边
        if (e[i].cap && h[e[i].v]+1==h[m])//如果残留容量大于0，如果是容许边
        {
            if (e[i].cap < augc)  augc=e[i].cap;//如果容许边流量小于当前增广路流量 则更新增广路流量
            d[m]=i;	//把i定为当前弧
            aug(e[i].v);	//递归
            if (h[st]>=n) return; //GAP 如果源点距离标号大于n 则停止算法
            if (found) break;	//如果找到汇点 则退出寻找
            augc=augco;//没找到就还原当前的流
        }
    if (!found)        //重标号
    {
        for (i=head[m]; i!=-1; i=e[i].next) //找那个标号，这里不能用d[m]开始，不然会蛋疼
            if (e[i].cap && h[e[i].v]<minh)
            {
                minh=h[e[i].v];
                mini=i;
            }
        g[h[m]]--; 								//GAP 距离为
        if (!g[h[m]]) h[st]=n; 				//GAP
        h[m]=minh+1;
        d[m]=mini;
        g[h[m]]++; 								//GAP
    }
    else
    {//修改残量
        e[i].cap-=augc;
        e[i^1].cap+=augc;
    }
}

void farm()
{
    int i,j,x,y,z;
    memset(head,-1,sizeof(head));
    cnt=0;
    for(i=0; i<m; i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z);
    }
    st=1;ed=n;
    memset(h,0,sizeof(h));
    memset(g,0,sizeof(g));
    g[0]=n;
    flow=0;
    for(i=1; i<=n; i++)
        d[i]=head[i];//当前弧初始化
    while(h[st]<n)
    {
        augc=inf;//初始化增广路容量为正无穷大
        found=false;
        aug(st);//从源点开始找
    }
    printf("%d\n",flow);
}

int main()
{
    while(scanf("%d%d",&m,&n)!=EOF) farm();
    return 0;
}
