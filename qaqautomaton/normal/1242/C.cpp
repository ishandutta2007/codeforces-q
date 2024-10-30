/*
Author: QAQAutomaton
LANG: C++
PROG: C.cpp
Mail: lk@qaq-am.com
Blog: https://www.qaq-am.com/
*/
#include<bits/stdc++.h>
#define int long long
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
	// input a signed integer
	inline bool read (signed &x) {
		for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;else if(c==EOF)return 0;
		for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
		return 1;
	}

	inline bool read (long long &x) {
		for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;else if(c==EOF)return 0;
		for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
		return 1;
	}
	inline bool read (char &x) {
		x=gc();
		return x!=EOF;
	}
	inline bool read(char *x){
		while((*x=gc())=='\n' || *x==' '||*x=='\r')if(*x==EOF)return 0;
		while(!(*x=='\n'||*x==' '||*x=='\r'))*(++x)=gc();
		*x=0;
		return 1;
	}
	template<typename A,typename ...B>
	inline bool read(A &x,B &...y){
		return read(x)&&read(y...);
	}
	// print a signed integer
	inline bool write (signed x) {
		if (!x) putc ('0'); if (x < 0) putc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
		while (qr) putc (qu[qr --]);
		return 0;
	}

	inline bool write (long long x) {
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
int m[16];
int a[80005],id[80005];
int to[80005],vis[80005],s[17];
int ok[65536],c,f[65536],las[65536];
int pre[80005];
map<int,int> mp;
void dfs(int x){
	if(!x)return;
	if(vis[x]==c){
		int w=1<<(id[x]-1);
		for(int y=pre[x];y!=x;y=pre[y]){
			if(w&(1<<(id[y]-1)))return;	
			w|=(1<<(id[y]-1));
		}
		ok[w]=x;
		return;
	}
	if(vis[x])return;
	vis[x]=c;
	pre[to[x]]=x;
	dfs(to[x]);
}
int fa[17],fb[17];
signed main(){
#ifdef QAQAutoMaton 
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
#endif
	int n;
	read(n);
	int sum=0;
	for(int i=1;i<=n;++i){
		read(m[i]);
		m[i]+=m[i-1];
		for(int j=m[i-1]+1;j<=m[i];++j){
			read(a[j]);	
			id[j]=i;
			mp[a[j]]=j;
			s[i]+=a[j];
			sum+=a[j];
		}
	}
	if(sum%n)return write("No\n");
	sum/=n;
	for(int i=1;i<=m[n];++i){
		to[i]=mp[a[i]+sum-s[id[i]]];
	}
	for(int i=1;i<=m[n];++i)if(!vis[i]){++c;dfs(i);}
	f[0]=1;
	for(int i=1;i<1<<n;++i)for(int j=i;j;j=(j-1)&i)if(f[i-j] && ok[j]){
		f[i]=1;las[i]=j;
		break;
	}
	if(!f[(1<<n)-1])return write("No\n");
	int s=(1<<n)-1;
	while(s){
		int x=ok[las[s]],y=x;
		while(1){
			fb[id[to[y]]]=id[y];
			fa[id[to[y]]]=a[to[y]];
			y=to[y];
			if(x==y)break;
		}
		s^=las[s];
	}
	write("Yes\n");
	for(int i=1;i<=n;++i)write(fa[i],' ',fb[i],'\n');
	return 0;
}