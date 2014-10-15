//#pragma comment(linker, "/STACK:102400000,102400000")
#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<map>
#include<set>
#include<stack>
#include<queue>
using namespace std;
#define ll long long
#define usll unsigned ll
#define mz(array) memset(array, 0, sizeof(array))
#define mf1(array) memset(array, -1, sizeof(array))
#define minf(array) memset(array, 0x3f, sizeof(array))
#define REP(i,n) for(i=0;i<(n);i++)
#define FOR(i,x,n) for(i=(x);i<=(n);i++)
#define RD(x) scanf("%d",&x)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define WN(x) printf("%d\n",x);
#define RE  freopen("D.in","r",stdin)
#define WE  freopen("huzhi.txt","w",stdout)
#define mp make_pair
#define pb push_back
#define pf push_front
#define ppf pop_front
#define ppb pop_back
const double pi=acos(-1.0);
const double eps=1e-10;

int k,n;
int a[11];

//int cntt[133];
int cnt(int st) {
    //if(cntt[st]!=-1)return cntt[st];
    int t=0,tt=st;
    while(tt) {
        if(tt&1)t++;
        tt>>=1;
    }
    //cntt[st]=t;
    return t;
}

//int okk[133][133];
int ok(int j,int k) {
    //if(okk[j][k]!=-1)return okk[j][k];
    if(cnt(j)<cnt(k)) {
        //okk[j][k]=0;
        return 0;
    }
    int tk=k,tj=j,ck=0,cj=0;
    while(tk) {
        if(tk&1==1) {
            while(tj) {
                if(tj&1==1) {
                    if(cj>ck) {
                        //okk[j][k]=0;
                        return 0;
                    }
                    cj++;
                    tj>>=1;
                    break;
                }
                cj++;
                tj>>=1;
                if(!tj)while(1);
            }
        }
        ck++;
        tk>>=1;
    }
    //okk[j][k]=1;
    return 1;
}

ll d[11][133];
int c[11],mj;

ll farm() {
    int i,j;
    int maxst=1<<n;
    //printf("maxst = %d\n",maxst);
    mz(d);
    FOR(k,0,maxst-1)
    if(cnt(k)==c[1])d[1][k]=1;

    FOR(i,2,mj) {
        FOR(j,0,maxst-1) {
            FOR(k,0,maxst-1) {
                if(d[i-1][j]!=0 && cnt(k)==c[i] && cnt(j)==c[i-1] && ok(j,k)) {
                    d[i][k]+=d[i-1][j];
                    //printf("d[%d][%x]=%I64d , d[%d][%x]=%I64d\n",i-1,j,d[i-1][j] ,i,k,d[i][k]);
                }
            }
        }
    }
    ll re=0;
    FOR(i,0,maxst-1)re+=d[mj][i];
    return re;
}

int main() {
    int i,j;
    //mf1(cntt);
    //mf1(okk);
    while(RD(k)!=EOF) {
        mz(c);
        FOR(i,1,k) {
            RD(a[i]);
            FOR(j,1,a[i])c[j]++;
        }
        mj=a[1];
        RD(n);
        printf("%I64d\n",farm());
    }
    return 0;
}
