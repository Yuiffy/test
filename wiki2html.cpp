#pragma comment(linker, "/STACK:102400000,102400000")
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define REP(i,n) for(i=0;i<n;i++)
#define FOR(i,x,y) for(i=x;i<=y;i++)
#define mz(x) memset(x,0,sizeof(x))
#define mf1(x) memset(x,-1,sizeof(x))
#define re freopen("input.txt","r",stdin)
#define we freopen("output.txt","w",stdout)
#define pb push_back
#define ll long long
#define mod 1000000009
#define eps 1e-9

const int maxn=11111;
const int maxm=11111;

struct Edge {
    int next,v;
} e[maxm];
int head[maxn],en;

inline void add(int x,int y) {
    e[en].v=y;
    e[en].next=head[x];
    head[x]=en++;
}

struct node {
    int l,r,x,fx;
    node() {}
    node(int _l,int _r,int _x,int _fx) {
        l=_l,r=_r,x=_x,fx=_fx;
    }
} o[maxn];
int on;

char s[1111][2222];
int c[1111];
int n;

inline int cnt(const int &x) {
    int i=0;
    while(s[x][i]=='#' || s[x][i]=='*') i++;
    return i;
}

inline int cmp(const int &x , const int &y,const int &z) {
    int i=z;
    while(s[x][i]==s[y][i] && (s[x][i]=='#'||s[x][i]=='*')) i++;
    return i;
}

void gank(const int &non) {
    int l=o[non].l;
    int r=o[non].r;
    int x=o[non].x;
    //printf("(%d %d,%d,%d)  ",non,l,r,x);
    int i,j,k;
    j=l;
    k=11111;
    FOR(i,l,r) {
        if(j<i) {
            int t=cmp(i,j,x);
            //printf("(t=%d)",t);
            if(t==0) {
                if(k!=11111) {
                    o[on].l=j;
                    o[on].r=i-1;
                    o[on].x=k;
                    o[on].fx=x;
                    on++;
                    //printf("%d,%d ",on-1,o[on-1].r);
                    add(non,on-1);
                    //printf("%d,%d\n",non,on-1);
                    gank(on-1);
                    k=11111;
                    j=i+1;
                }else j=i;
            } else k=min(t,k);
        }
    }
    ///TODO ...
}

void out(const int &non) {
    int l=o[non].l;
    int r=o[non].r;
    int x=o[non].x;
    int fx=o[non].fx;
    int i,j,k;
    j=l;
    //printf("%d %d,%d,%d,%d\n",non,l,r,x,fx);
    FOR(i,fx,x-1) {
        if(s[l][i]=='*')puts("<ul>");
        else puts("<ol>");
    }
    for(i=head[non]; i!=-1; i=e[i].next) {
        while(j<o[e[i].v].l) {
            int len=strlen(s[j]);
            puts("<li>");
            FOR(k,x,len)putchar(s[j][k]);
            puts("");
            puts("</li>");
            j++;
        }
        //printf("%d->%d %d,%d\n",non,e[i].v,i,e[i].next);
        out(e[i].v);
        j=o[e[i].v].r+1;
    }
    while(j<r) {
        int len=strlen(s[j]);
        puts("<li>");
        FOR(k,x,len)putchar(s[j][k]);
        puts("");
        puts("</li>");
        j++;
    }
    for(i=x-1; i>=fx; i--) {
        if(s[l][i]=='*')puts("</ul>");
        else puts("</ol>");
    }
}

void farm() {
    on=1;
    en=0;
    mf1(head);
    o[0].l=0;
    o[0].r=n-1;
    o[0].x=0;
    o[0].fx=0;
    gank(0);
    out(0);
}

int main() {
    int i;
    re;
    //we;
    n=0;
    while(scanf(" %s",s[n++])!=EOF);
    farm();
    return 0;
}
