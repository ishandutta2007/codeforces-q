/*
Author: QAQAutomaton
Lang: C++
Code: I.cpp
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
typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef complex<double> cp;
typedef pair<int,int> pii;
int inf;
const double eps=1e-8;
const double pi=acos(-1.0);
template<class T,class T2>int chkmin(T &a,T2 b){return a>b?a=b,1:0;}
template<class T,class T2>int chkmax(T &a,T2 b){return a<b?a=b,1:0;}
template<class T>T sqr(T a){return a*a;}
template<class T,class T2>T mmin(T a,T2 b){return a<b?a:b;}
template<class T,class T2>T mmax(T a,T2 b){return a>b?a:b;}
template<class T>T aabs(T a){return a<0?-a:a;}
template<class T>int dcmp(T a,T b){return a>b;}
template<int *a>int cmp_a(int x,int y){return a[x]<a[y];}
template<class T>bool sort2(T &a,T &b){return a>b?swap(a,b),1:0;}
#define min mmin
#define max mmax
#define abs aabs
struct __INIT__{
	__INIT__(){
		fill((unsigned char*)&inf,(unsigned char*)&inf+sizeof(inf),0x3f);
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
		while(!(*x=='\n'||*x==' '||*x=='\r'||*x==EOF))*(++x)=gc();
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
typedef pair<unsigned short,int> xp;
xp operator +(const xp &a,const xp &b){return {a.x+b.x,a.y+b.y};}
xp operator -(const xp &a,const xp &b){return {a.x-b.x,a.y-b.y};}
xp &operator +=(xp &a,const xp &b){return a=a+b;}
xp &operator -=(xp &a,const xp &b){return a=a-b;}
int a[50005];
int fa[50005];
vector<int> to[50005];
int dfn[50005],low[50005],t;
int dep[50005];
void dfs(int x){
	dfn[x]=++t;
	for(auto i:to[x]){
		dep[i]=dep[x]+1;
		dfs(i);
	}
	low[x]=t;
}
xp v[50005];
int xa[50005],ned[50005];
signed main(){
#ifdef QAQAutoMaton 
	freopen("I.in","r",stdin);
	freopen("I.out","w",stdout);
#endif
	int n,q;	
	read(n,q);
	for(int i=1;i<=n;++i){
		read(xa[i]);
	}
	for(int i=2;i<=n;++i){
		read(fa[i]);
		to[fa[i]].emplace_back(i);
	}
	dfs(1);
	for(int i=1;i<=n;++i){v[dfn[i]]={1,dep[i]};a[dfn[i]]=xa[i];}
	for(int at=1;at<=q;++at){
		int x;
		xp ans(0,0);
		read(x);
		int l=dfn[x],r=low[x];
		int i=l;
		#define make(i) ned[i]<=at?ans+=v[i],ned[i]=at+a[i]:0
		for(;i+7<=r;i+=8){
		    make(i),make(i+1),make(i+2),make(i+3),
		    make(i+4),make(i+5),make(i+6),make(i+7);
		}
		for(;i<=r;++i)make(i);
		write(ans.y-ans.x*dep[x],' ',ans.x,'\n');
	}
	return 0;
}