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
int a[300005],b[300005];
pii merge(pii a,pii b){
	int x=min(a.x,b.x);
	return {x,(a.x==x?a.y:0)+(b.x==x?b.y:0)};
}
struct smt{
	int ls,rs;
	pii mn;
	int tag;
	smt *l,*r;
	smt(){}
	smt(int,int);
	void put_tag(int x){tag+=x;mn.x+=x;}
	void push_down(){
		if(tag){l->put_tag(tag);r->put_tag(tag);tag=0;}
	}
	void set(int x,int y){
		if(ls==rs){mn={y,1};return;}
		push_down();
		if(x<=l->rs)l->set(x,y);
		else r->set(x,y);
		mn=merge(l->mn,r->mn);
	}
	void add(int la,int ra,int x){
		if(la<=ls && rs<=ra){put_tag(x);return;}
		push_down();
		if(la<=l->rs)l->add(la,ra,x);
		if(r->ls<=ra)r->add(la,ra,x);
		mn=merge(l->mn,r->mn);
	}
};
smt *rt,node[600005],*at=node;
smt *newsmt(int la,int ra){
	smt *rt=at;++at;
	*rt=smt(la,ra);
	return rt;
}
smt::smt(int la,int ra){
	ls=la;rs=ra;
	mn={inf,rs-ls+1};
	tag=0;
	if(ls==rs){l=r=0;return;}
	int mid=(ls+rs)>>1;
	l=newsmt(ls,mid);
	r=newsmt(mid+1,rs);
}
signed main(){
#ifdef QAQAutoMaton 
	freopen("F.in","r",stdin);
	freopen("F.out","w",stdout);
#endif
	int n,x,y;
	read(n);
	for(int i=1;i<=n;++i){
		read(x,y);
		a[x]=y;b[y]=x;
	}
	rt=newsmt(1,n);
	b[0]=b[n+1]=inf;
	ll ans=0;
	for(int i=1;i<=n;++i){
		rt->set(i,0);
		rt->add(1,i,1);
		if(b[a[i]-1]<i)rt->add(1,b[a[i]-1],-1);
		if(b[a[i]+1]<i)rt->add(1,b[a[i]+1],-1);
		ans+=rt->mn.y;
	}
	write(ans,'\n');
	return 0;
}