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
int a[300005],nx[300005],id[300005];
int pw[300005];
pii b[600005];
const int p=1000000007,i2=(p+1)>>1;
struct smt{
	int ls,rs,lans,rans,ans,cnt;
	smt *l,*r;
	smt(int la,int ra){
		ls=la;rs=ra;
		lans=rans=ans=cnt=0;
		if(ls==rs){
			l=r=0;return;
		}
		int mid=(ls+rs)>>1;
		l=new smt(ls,mid);
		r=new smt(mid+1,rs);
	}	
	void push_up(){
		ans=(l->ans+r->ans+l->rans*r->lans)%p;
		lans=(l->lans+r->lans*pw[l->cnt])%p;
		rans=(r->rans+l->rans*pw[r->cnt])%p;
		cnt=l->cnt+r->cnt;
	}
	void set(int x){
		if(ls==rs){
			ans=0;lans=rans=b[x].x*i2%p;
			cnt=1;
			return;
		}
		if(x<=l->rs)l->set(x);	
		else r->set(x);
		push_up();
	}
	void unset(int x){
		if(ls==rs){
			lans=rans=ans=cnt=0;
			return;
		}
		if(x<=l->rs)l->unset(x);	
		else r->unset(x);
		push_up();
	}
};
smt *rt;
signed main(){
#ifdef QAQAutoMaton 
	freopen("F.in","r",stdin);
	freopen("F.out","w",stdout);
#endif
	int n;
	read(n);
	for(int i=1;i<=n;++i){
		read(a[i]);
		b[i]=make_pair(a[i],i);
	}
	int q;
	read(q);
	for(int i=1;i<=q;++i){
		read(id[i],nx[i]);
		b[n+i]=make_pair(nx[i],n+i);
	}
	sort(b+1,b+n+q+1);
	rt=new smt(1,n+q);
	for(int i=1;i<=n+q;++i){
		if(b[i].y<=n)a[b[i].y]=i;
		else{
			nx[b[i].y-n]=i;
		}
	}
	pw[0]=1;
	for(int i=1;i<=n;++i)pw[i]=pw[i-1]*i2%p;
	for(int i=1;i<=n;++i){
		rt->set(a[i]);	
	}
	write(rt->ans,'\n');
	for(int i=1;i<=q;++i){
		rt->unset(a[id[i]]);
		rt->set(a[id[i]]=nx[i]);
		write(rt->ans,'\n');
	}
	return 0;
}