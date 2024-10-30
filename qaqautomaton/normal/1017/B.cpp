/*
Author: CNYALI_LK
LANG: C++
PROG: 1017B.cpp
Mail: cnyalilk@vip.qq.com
*/
#include<bits/stdc++.h>
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define DEBUG printf("Passing [%s] in LINE %lld\n",__FUNCTION__,__LINE__)
#define Debug debug("Passing [%s] in LINE %lld\n",__FUNCTION__,__LINE__)
#define all(x) x.begin(),x.end()
using namespace std;
const double eps=1e-8;
const double pi=acos(-1.0);
typedef long long ll;
typedef pair<ll,ll> pii;
template<class T>ll chkmin(T &a,T b){return a>b?a=b,1:0;}
template<class T>ll chkmax(T &a,T b){return a<b?a=b,1:0;}
template<class T>T sqr(T a){return a*a;}
template<class T>T mmin(T a,T b){return a<b?a:b;}
template<class T>T mmax(T a,T b){return a>b?a:b;}
template<class T>T aabs(T a){return a<0?-a:a;}
#define min mmin
#define max mmax
#define abs aabs
ll read(){
	ll s=0,base=1;
	char c;
	while(!isdigit(c=getchar()))if(c=='-')base=-base;
	while(isdigit(c)){s=s*10+(c^48);c=getchar();}
	return s*base;
}
char WritellBuffer[1024];
template<class T>void write(T a,char end){
	ll cnt=0,fu=1;
	if(a<0){putchar('-');fu=-1;}
	do{WritellBuffer[++cnt]=fu*(a%10)+'0';a/=10;}while(a);
	while(cnt){putchar(WritellBuffer[cnt]);--cnt;}
	putchar(end);
}
ll a[102423],b[102423],s[4];
ll readbit(){
	char c;
	while(!isdigit(c=getchar()));
	return c-'0';
}
int main(){
#ifdef cnyali_lk
	freopen("1017B.in","r",stdin);
	freopen("1017B.out","w",stdout);
#endif
	ll n;
	n=read();
	for(ll i=1;i<=n;++i)a[i]=readbit();
	for(ll i=1;i<=n;++i){
		b[i]=readbit();
		++s[a[i]*2+b[i]];
	}
	printf("%lld\n",s[3]*s[0]+s[2]*s[1]+s[2]*s[0]);
	return 0;
}