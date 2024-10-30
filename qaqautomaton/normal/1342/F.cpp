/*
Author: QAQAutomaton
Lang: C++
Code: F.cpp
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
int f[1<<15|5][16][16];
pii op[1<<15][16][16];
int s[1<<15|5];
int a[15],at[15];
int t,n;
void del(int x,int y){
	write(at[x],' ',at[y],'\n');
	for(int i=x+1;i<n;++i)--at[i];
}
void out(int s,int x,int y){
	pii xop=op[s][x][y];
	for(int i=0;i<n;++i)if(i!=xop.y && (xop.x&(1<<i)))del(i,xop.y);
	if(s^xop.x)out(s^xop.x,xop.y,y-1);
}
void dp(){
	int S=(1<<n)-1;
	for(int i=0;i<1<<n;++i)for(int k=0;k<=n;++k)f[i][0][k]=inf;
	f[0][0][0]=0;
	for(int j=0;j<n;++j){
		for(int i=0;i<1<<n;++i)for(int k=0;k<=n;++k){
			op[i][j+1][k]=op[i][j][k];
			f[i][j+1][k]=f[i][j][k];
		}
		for(int i=0;i<1<<n;++i)if((i&(1<<j))){
			for(int k=S^i;;k=(k-1)&(S^i)){
				for(int l=0;l<=j;++l){
					if(f[k][j][l]<s[i] && chkmin(f[i|k][j+1][l+1],s[i]))op[i|k][j+1][l+1]=make_pair(i,j);
					//if(f[k][j-1][l]<s[i]k|i
				}
				if(!k)break;
			}
		}
	}
}
signed main(){
#ifdef QAQAutoMaton 
	freopen("F.in","r",stdin);
	freopen("F.out","w",stdout);
#endif
	read(t);
	for(;t;--t){
		read(n);
		for(int i=0;i<n;++i){
			read(a[i]);
			s[1<<i]=a[i];
		}
		for(int i=1;i<1<<n;++i)if(i&(i-1)){s[i]=s[i&(-i)]+s[i&(i-1)];}
		int s=(1<<n)-1;
		dp();
//		DP
		for(int i=0;i<n;++i)at[i]=i+1;
		for(int i=n;i;--i)if(f[s][n][i]!=inf){
			write(n-i,'\n');
			out(s,n,i);
			break;	
		}
	}

	return 0;
}