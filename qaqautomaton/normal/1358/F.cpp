/*
Author: QAQAutomaton
Lang: C++
Code: F.cpp
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
int a[200005],b[200005];
bitset<500005> ans;
int sP,s;
void addP(){
	if(s<500000)ans[++s]=1;
	++sP;
}
void addR(){
	if(s<500000)ans[++s]=0;
}
void put_ans(){
	if(sP<=200000){
		write("SMALL\n",s,'\n');for(int i=s;i;--i)putc(ans[i]?'P':'R');putc('\n');
	}
	else write("BIG\n",sP,'\n');
	exit(0);
}
void addPs(int x){
	sP+=x;
	while(x&&s<500000){ans[++s]=1;--x;}
}
signed main(){
#ifdef QAQAutoMaton 
	freopen("F.in","r",stdin);
	freopen("F.out","w",stdout);
#endif
	int n;
	read(n);
	for(int i=1;i<=n;++i)read(a[i]);
	for(int i=1;i<=n;++i)read(b[i]);
	if(n==1){
		if(a[1]==b[1])return write("SMALL\n0\n");
		else return write("IMPOSSIBLE\n");
	}
	else if(n==2){
		int r=a[1]>a[2];
		if(r)swap(a[1],a[2]);
		while(b[1]&&b[2]){
			if(b[1]>b[2]){
				addR();
				swap(b[1],b[2]);
			}
			if(b[1]==a[1]){
				if(b[2]<a[2])return write("IMPOSSIBLE\n");
				if((b[2]-a[2])%b[1])return write("IMPOSSIBLE\n");
				else{
					addPs((b[2]-a[2])/b[1]);
					if(r)addR();
					put_ans();
				}
			}
			addPs(b[2]/b[1]);
			b[2]%=b[1];
		}
		return write("IMPOSSIBLE\n");
//		if(r)addR();
	}
	else{
		while(1){
			int s=1;
			for(int i=1;i<=n;++i)if(a[i]!=b[i]){s=0;break;}
			if(s){put_ans();return 0;}
			s=1;
			for(int i=1;i<=n;++i)if(a[i]!=b[n+1-i]){s=0;break;}
			if(s){
				addR();
				put_ans();
				return 0;
			}
			for(int i=1;i<n;++i)if(b[i]==b[i+1])return write("IMPOSSIBLE\n");
			s=0;
			for(int i=1;i<n;++i)if(b[i]>b[i+1]){s=1;break;}
			if(s){addR();reverse(b+1,b+n+1);}
			for(int i=1;i<n;++i)if(b[i]>b[i+1])return write("IMPOSSIBLE\n");
			addP();
			for(int i=n;i;--i)b[i]-=b[i-1];
		}	
		return write("IMPOSSIBLE\n");
	}

	return 0;
}