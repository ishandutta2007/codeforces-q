/*
Author: QAQAutomaton
Lang: C++
Code: A.cpp 
Mail: lk@qaq-am.com
Blog: https://www.qaq-am.com/
*/
#include<bits/stdc++.h>
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define DEBUG printf("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define Debug debug("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define all(x) x.begin(),x.end()
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
int inf;
const double eps=1e-8;
const double pi=acos(-1.0);
template<class T>int chkmin(T &a,T b){return a>b?a=b,1:0;}
template<class T>int chkmax(T &a,T b){return a<b?a=b,1:0;}
template<class T>T sqr(T a){return a*a;}
template<class T>T mmin(T a,T b){return a<b?a:b;}
template<class T>T mmax(T a,T b){return a>b?a:b;}
template<class T>T aabs(T a){return a<0?-a:a;}
template<class T>int dcmp(T a,T b){return a>b;}
template<int *a>int cmp_a(int x,int y){return a[x]<a[y];}
#define min mmin
#define max mmax
#define abs aabs
struct __INIT__{
	__INIT__(){
		memset(&inf,0x3f,sizeof(inf));
	}
}__INIT___;
namespace io {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
	// getchar
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	// print the remaining part
	inline void flush () {
		fwrite (obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	// putchar
	inline void putc (char x) {
		*oS ++ = x;
		if (oS == oT) flush ();
	}
	template<typename A>
	inline bool read (A &x) {
		for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;else if(c==EOF)return 0;
		for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
		return 1;
	}
	inline bool read (char &x) {
		while((x=gc())==' '||x=='\n' || x=='\r');
		return x!=EOF;
	}
	inline bool read(char *x){
		while((*x=gc())=='\n' || *x==' '||*x=='\r');
		if(*x==EOF)return 0;
		while(!(*x=='\n'||*x=='\r'))*(++x)=gc();
		*x=0;
		return 1;
	}
	template<typename A,typename ...B>
	inline bool read(A &x,B &...y){
		return read(x)&&read(y...);
	}
	template<typename A>
	inline bool write (A x) {
		if (!x) putc ('0'); if (x < 0) putc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
		while (qr) putc (qu[qr --]);
		return 0;
	}
	inline bool write (char x) {
		putc(x);
		return 0;
	}
	inline bool write(const char *x){
		while(*x){putc(*x);++x;}
		return 0;
	}
	inline bool write(char *x){
		while(*x){putc(*x);++x;}
		return 0;
	}
	template<typename A,typename ...B>
	inline bool write(A x,B ...y){
		return write(x)||write(y...);
	}
	//no need to call flush at the end manually!
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using io :: read;
using io :: putc;
using io :: write;
int a[105];
int c[2],cc[2];
vector<int> vt[2];
signed main(){
#ifdef QAQAutoMaton 
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
#endif
	int n,ans=0;
	read(n);
	c[0]=n>>1,c[1]=n-(n>>1);
	for(int i=1;i<=n;++i){
		read(a[i]);
		if(a[i])--c[a[i]&1];
		if(a[i] && a[i-1])ans+=(a[i]^a[i-1])&1;
	}
	int mn=n+1;
	a[0]=1;
	a[n+1]=1;
	pii w1=make_pair(0,0),w2=make_pair(0,0);
	for(int i=1;i<=n;++i){
		if(!a[i]){
			int j=i;
			while(!a[j+1])++j;
			if(i==1 && j==n){return write(n>1,'\n');}
			if(i==1)w1=make_pair(a[j+1]&1,j);
			else if(j==n)w2=make_pair(a[i-1]&1,n-i+1);
			else{
				if((a[i-1]&1)==(a[j+1]&1)){
					vt[a[j+1]&1].push_back(j-i+1);
				}
				else ++ans;
			}
			i=j;
		}	
	}
	cc[0]=c[0];cc[1]=c[1];
	sort(all(vt[0]));
	sort(all(vt[1]));
	for(int k=0;k<4;++k){
		c[0]=cc[0];c[1]=cc[1];
		int x=0;
		if((k&1)){if((c[w1.x]-=w1.y)<0)continue;}else ++x;
		if((k&2)){if((c[w2.x]-=w2.y)<0)continue;}else ++x;
		x+=(vt[0].size()+vt[1].size())*2;
		for(auto i:vt[0]){
			if(c[0]>=i){c[0]-=i;x-=2;}
			else break;
		}

		for(auto i:vt[1]){
			if(c[1]>=i){c[1]-=i;x-=2;}
			else break;
		}
		chkmin(mn,x);
	}
	write(ans+mn,'\n');
	return 0;
}