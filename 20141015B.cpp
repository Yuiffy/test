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
#define WE  freopen("Bbiao.txt","w",stdout)
#define mp make_pair
#define pb push_back
#define pf push_front
#define ppf pop_front
#define ppb pop_back
const double pi=acos(-1.0);
const double eps=1e-10;

int gcd(int x,int y){
    return !y?x:gcd(y,x%y);
}

int n,K;

int b[11111],bn;
int ans[11111][4];

bool ok(int i,int j,int t){
    int k;
    REP(k,j){
        if(gcd(ans[i][k],t)!=1)return 0;
    }
    return 1;
}

void farm(){
    int i,j,k;
    bn=1;
    b[0]=1;
    i=2;
    while(bn<=n*4){
        bool ok=1;
        FOR(j,2,sqrt(i)){
            if(i%j==0){ok=0;break;}
        }
        if(ok){
            b[bn++]=i;
        }
        i++;
    }
    ans[0][0]=1;
    ans[0][1]=2;
    ans[0][2]=3;
    ans[0][3]=5;

    int q[4]={7,6,5,0};
    int w[4]={2,3,5,7};
    FOR(i,1,n-1){
        REP(j,4){
            ans[i][j]=w[j]*b[q[j]];
            q[j]++;
        }
    }
}

int main() {
    //WE;
    int i,j;
    RD2(n,K);
    farm();
    int ma=0;
    REP(i,n)REP(j,4)ma=max(ma,ans[i][j]);
    WN(ma*K);
    REP(i,n){
        printf("%d",ans[i][0]*K);
        FOR(j,1,3){
            printf(" %d",ans[i][j]*K);
        }
        puts("");
    }
    return 0;
}
