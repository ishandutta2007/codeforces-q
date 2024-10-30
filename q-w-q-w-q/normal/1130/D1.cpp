#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<cmath>
#include<map>
#include<set>
#include<queue>
#include<iomanip>
#include<cstdlib>
#define _t putchar(32)
#define _e putchar(10)
#define inf 2147483647
#define ine -2147483647
#define lb(x) (x)&(-x)
using namespace std;
typedef long long ll;
bool o;
char chh,ss[1<<17],*A=ss,*B=ss;
inline char gc(){
    return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?EOF:*A++;
}
template <typename _Tp> inline void rd(_Tp &x);
template <typename _Tp> inline void wr(_Tp x);
template <typename _Tp> inline _Tp mx(_Tp x,_Tp y);
template <typename _Tp> inline _Tp mn(_Tp x,_Tp y);
ll n,m,l[5001],r[5001],q[5001],k;
struct p{
	ll b,e;
	friend bool operator<(p i,p j){
		return i.b^j.b?i.b<j.b:i.e<j.e;
	}
}a[20001];
ll ans;
int main(){
	rd(n);
	rd(m);
	for(int i=1;i<=m;i++)
	rd(a[i].b),rd(a[i].e);
	sort(a+1,a+1+m);
	for(int i=1;i<=n;i++){
		int j;
		for(j=r[i-1]+1;j<=m&&a[j].b==i;j++);
		j--;
		l[i]=r[i-1]+1;
		r[i]=j;
	}
	for(int i=1;i<=n;i++){
		if(l[i]>r[i]){
			q[i]=-1;
			continue;
		}
		q[i]=inf,k=r[i]-l[i];
		for(int j=l[i];j<=r[i];j++)
		q[i]=mn(q[i],k*n+(a[j].e+n-i)%n);
	}
	for(int i=1;i<=n;i++){
		ans=0;
		for(int j=1;j<=n;j++){
			if(q[j]!=-1)ans=mx(ans,q[j]+(j+n-i)%n);
		}
		wr(ans),_t;
	}
}
template <typename _Tp>
    inline void rd(_Tp &x){
    	o=0;
        x=0;
      	while (chh^45&&(chh<48||chh>57)) chh=gc();
      	if(chh==45)o=1,chh=gc();
        while(chh>47&&chh<58){
            x=(x<<1)+(x<<3)+(chh^48);
            chh=gc();
        }
      	if(o) x=-x;
 	}
template <typename _Tp>
    inline void wr(_Tp x){
        if(x<0) x=-x,putchar(45);
        if(x<10){
            putchar(x+48);
            return;
        }
        wr(x/10);
        putchar(x%10+48);
    }
template <typename _Tp>
    inline _Tp mx(_Tp x,_Tp y){
        return x>y?x:y;
    }
template <typename _Tp>
    inline _Tp mn(_Tp x,_Tp y){
        return x<y?x:y;
    }