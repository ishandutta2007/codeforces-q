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
#include<ctime>
#define _t putchar(32)
#define _e putchar(10)
#define inf 2147483647
#define ine -2147483647
#define lb(x) (x)&(-x)
#define ic(x) ((x>='0'&&x<='9')||(x>='A'&&x<='Z')||(x>='a'&&x<='z'))
using namespace std;
typedef long long ll;
bool o;
char chh,ss[1<<17],*A=ss,*B=ss;
inline char gc(){
    return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?EOF:*A++;
}
inline void getstr(char *a,int &n){
    a[n=1]=gc();
    while(!ic(a[1])) a[1]=gc();
    while(ic(a[n])) a[++n]=gc();
    n--;
}
template <typename _Tp> inline void rd(_Tp &x);
template <typename _Tp> inline void wr(_Tp x);
template <typename _Tp> inline _Tp mx(_Tp x,_Tp y);
template <typename _Tp> inline _Tp mn(_Tp x,_Tp y);
int n,m,a[501];
ll mod=998244353;
ll f[501][501];
inline ll dfs(int l,int r){
	if(l>=r) return 1;
	if(f[l][r]^-1) return f[l][r];
	int k=l;
	for(int i=l+1;i<=r;i++)
	if(a[i]<a[k]) k=i;
	ll lt=0,rt=0;
	for(int i=l+1;i<=k;i++)
	lt+=dfs(l,i-1)*dfs(i,k-1)%mod,lt%=mod;
	lt+=dfs(l,k-1),lt%=mod;
	for(int i=k+1;i<=r;i++)
	rt+=dfs(k+1,i-1)*dfs(i,r)%mod,rt%=mod;
	rt+=dfs(k+1,r),rt%=mod;
	f[l][r]=lt*rt%mod;
	return f[l][r];
}
int main(){
	//freopen("experiment.in","r",stdin);
	//freopen("experiment.out","w",stdout);
	rd(n);
	rd(m);
	for(int i=1;i<=m;i++)
	rd(a[i]);
	memset(f,-1,sizeof(f));
	wr(dfs(1,m));
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