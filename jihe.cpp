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
#include<vector>
using namespace std;
#define ll long long
#define usll unsigned ll
#define mz(array) memset(array, 0, sizeof(array))
#define minf(array) memset(array, 0x3f, sizeof(array))
#define REP(i,n) for(i=0;i<(n);i++)
#define FOR(i,x,n) for(i=(x);i<=(n);i++)
#define RD(x) scanf("%d",&x)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define WN(x) printf("%d\n",x);
#define RE  freopen("D.in","r",stdin)
#define WE  freopen("1biao.out","w",stdout)
#define mp make_pair
#define pb push_back
const double eps=1e-10;
const double pi=acos(-1.0);

const int maxn=5005;

inline int dcmp(double x)
{
    if(fabs(x)<eps)
        return 0;
    return x>0?1:-1;
}
struct pt
{
    double x,y;
    pt() {}
    pt(double _x,double _y):x(_x),y(_y) {}
    friend pt operator + (pt a,pt b)
    {
        return pt(a.x+b.x,a.y+b.y);
    }
    friend pt operator - (pt a,pt b)
    {
        return pt(a.x-b.x , a.y-b.y);
    }
    friend pt operator * (pt a,double d)
    {
        return pt(a.x*d , a.y*d);
    }
    friend pt operator / (pt a,double d)
    {
        return pt(a.x/d , a.y/d);
    }
    friend bool operator == (pt a,pt b)
    {
        return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;
    }
    friend bool operator != (pt a,pt b)
    {
        return dcmp(a.x-b.x)!=0 || dcmp(a.y-b.y)!=0;
    }
};
pt p[maxn];
inline bool isint(double x)
{
    return fabs(x-(int)(x+0.5))<eps;
}
inline double dis(pt a,pt b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
inline double earth_dis(pt a,pt b)
{
    double x1=pi*a.x/180.0;
    double y1=pi*a.y/180.0;
    double x2=pi*b.x/180.0;
    double y2=pi*b.y/180.0;
    return acos(cos(x1-x2)*cos(y1)*cos(y2)+sin(y1)*sin(y2));
}
inline double cross(pt a,pt b)
{
    return a.x*b.y-a.y*b.x;
}
inline double cross(pt a,pt b,pt o)
{
    return cross(a-o,b-o);
}
inline double cross(pt a,pt b,pt c,pt d)
{
    return cross(b-a,d-c);
}
inline double fabscross(pt a,pt b,pt o)
{
    return fabs(cross(a-o,b-o));
}
inline double dot(pt a,pt b)
{
    return a.x*b.x + a.y*b.y;
}
inline double dot(pt a,pt b,pt o)
{
    return dot(a-o,b-o);
}
inline double angle(pt a,pt b,pt o)
{
    double ao=atan2(a.y-o.y,a.x-o.x);
    double bo=atan2(b.y-o.y,b.x-o.x);
    return fabs(ao-bo)>=pi?(pi*2-fabs(ao-bo)):fabs(ao-bo);
}
inline double dis_pt_to_line(pt o,pt a,pt b)
{
    pt v1 = b-a;
    pt v2 = o-a;
    return fabs(cross(v1,v2))/dis(a,b);
}
inline double dis_pt_to_seg(pt o,pt a,pt b)
{
    if(a==b)
        return dis(o,a);
    pt v1 = b-a;
    pt v2 = o-a;
    pt v3 = o-b;
    if(dcmp(dot(v1,v2))<0)
        return dis(o,a);
    else if(dcmp(dot(v1,v3))>0)
        return dis(o,b);
    else
        return fabs(cross(v1,v2))/dis(a,b);
}
inline bool intersect_seg(pt a,pt b,pt c,pt d)
{
    int d1 = dcmp( cross(a,b,c) );
    int d2 = dcmp( cross(a,b,d) );
    int d3 = dcmp( cross(c,d,a) );
    int d4 = dcmp( cross(c,d,b) );
    if((d1*d2<0&&d3*d4<0))
        return true;
    else if(d1==0&&dot(a,b,c)<=0)
        return true;
    else if(d2==0&&dot(a,b,d)<=0)
        return true;
    else if(d3==0&&dot(c,d,a)<=0)
        return true;
    else if(d4==0&&dot(c,d,b)<=0)
        return true;
    else
        return false;
}
inline pair<pt,int> intersect_line(pt a,pt b,pt c,pt d)
{
    pt ret=a;
    if(dcmp(cross(a-b,c-d))==0)
    {
        if(dcmp(cross(c-a,d-a))==0)
            return make_pair(ret,0);///共线
        else
            return make_pair(ret,1);///平行
    }
    double t=cross(a-c,c-d)/cross(a-b,c-d);
    ret.x+=(b.x-a.x)*t;
    ret.y+=(b.y-a.y)*t;
    return make_pair(ret,2);///相交
}
inline double get_area(int n)
{
    double area=0;
    for(int i=1; i<n-1; i++)
        area+=cross(p[i],p[i+1],p[0]);
    area/=2;
    return fabs(area);
}
inline pt getreflect(pt o,pt a,pt b)
{
    pt tmp=o;
    tmp.x+=a.y-b.y;
    tmp.y+=b.x-a.x;
    tmp=intersect_line(a,b,o,tmp).first;
    pt ret=pt(o.x+(tmp.x-o.x)+(tmp.x-o.x),o.y+(tmp.y-o.y)+(tmp.y-o.y));
    return ret;
}

inline pt chuizhi(pt o,pt a,pt b){
    pt tmp=a-b;
    pt re=o;
    re.x-=tmp.y;
    re.y+=tmp.x;
    return re;
}

int main(){
    pt a[3],o01,c1,o12,c2;
    while(scanf("%lf%lf%lf%lf%lf%lf",&a[0].x,&a[0].y,&a[1].x,&a[1].y,&a[2].x,&a[2].y)!=EOF){
        o01=(a[0]+a[1])/2;
        o12=(a[1]+a[2])/2;
        c1=chuizhi(o01,a[0],a[1]);
        c2=chuizhi(o12,a[1],a[2]);
        pair<pt,int> mid=intersect_line(o01,c1,o12,c2);
        double ans=dis(mid.first,a[0])*2.0*pi;
        //printf("(%f,%f)->(%f,%f) (%f,%f)->(%f,%f) %f,%f\n",o01.x,o01.y,c1.x,c1.y,o12.x,o12.y,c2.x,c2.y,mid.first.x,mid.first.y);
        printf("%.2f\n",ans);
    }
    return 0;
}
