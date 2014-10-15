#include<stdio.h>
#include<cstring>
#define INF 2147483647

const int maxn=111;
const int maxm=11111;
struct edge {
    int w,v,next;
} e[maxm];
int head[maxn],en;

void add(int x,int y,int z) {
    e[en].w=z;
    e[en].v=y;
    e[en].next=head[x];
    head[x]=en++;
}

int n;

bool f[101];///入队标志
int b[101],d[101];///b为循环队列，d为起点到各点的最短路长度
void spfa() { ///0~n-1，共n个点，起点为st
    int i,k;
    int st=0, l=0, r=1;
    memset(f,0,sizeof(f));
    memset(b,0,sizeof(b));
    for(i=0; i<n; i++)
        d[i]=INF;
    b[0]=st;
    f[st]=1;
    d[st]=0;
    while(l!=r) {
        k=b[l++];
        l%=n;
        for(i=head[k]; i!=-1; i=e[i].next)
            if (d[k]+e[i].w < d[e[i].v]) {
                d[e[i].v]=d[k] + e[i].w;
                if (!f[e[i].v]) {
                    if(d[e[i].v]>d[b[l]]) {///SLF优化
                        b[r++]=e[i].v;
                        r%=n;
                    } else {
                        l--;
                        if(l==-1)l=n-1;
                        b[l]=e[i].v;
                    }
                    f[e[i].v]=1;
                }
            }
        f[k]=0;
    }
}

void init(){
    memset(head,-1,sizeof(head));
    en=0;
}

int main() {
    int i,j;
    char c;
    int x,ans;
    scanf("%d",&n);
    init();
    for (i=1; i<n; i++)
        for(j=0; j<i; j++)
            if (scanf("%d",&x)==1) {
                add(j,i,x);
                add(i,j,x);
            } else {
                do {
                    scanf("%c",&c);
                } while(c!='x');
            }

    spfa();
    ans=0;
    for(i=0; i<n; i++)
        if (d[i]>ans) ans=d[i];
    printf("%ld\n",ans);
    return 0;
}
