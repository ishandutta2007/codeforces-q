/*
Author: QAQAutoMaton
Lang: C++
Code: E1.cpp
Mail: lk@qaq-am.com
Blog: https://www.qaq-am.com/
*/
#include<bits/stdc++.h>
#define debug(qaq...) fprintf(stderr,qaq)
#define DEBUG printf("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define Debug debug("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define all(x) x.begin(),x.end()
#define x first
#define y second
#define unq(a) sort(all(a)),a.erase(unique(all(a)),a.end())
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
template<class T,class ...T2>T mmin(T a,T2 ...b){return mmin(a,mmin(b...));}
template<class T,class ...T2>T mmax(T a,T2 ...b){return mmax(a,mmax(b...));}
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
vector<int> operator +(const vector<int> &a,const vector<int> &b){
	vector<int> c(a.size()+b.size());
	for(int i=0;i<a.size();++i)c[i]=a[i];
	for(int i=0;i<b.size();++i)c[a.size()+i]=b[i];
	return c;
}
int ask(vector<int> a){
	cout<<"? "<<a.size();
	for(auto i:a)cout<<' '<<i;
	cout<<endl;
	string v;
	cin>>v;
	return v=="YES";
}
void answer(int a){
	cout<<"! "<<a<<endl;
	string v;
	cin>>v;
	if(v==":)")exit(0);
}
vector<int> st,nst[4];
vector<int> big[2],small[3];
int s[4];
int f[105][105],vx[105][105],vy[105][105];
signed main(){
	for(int ij=3;ij<=100;++ij){
		for(int i=0;i<=ij;++i)f[i][ij-i]=inf;
		for(int i=0;i<=ij;++i){
			int j=ij-i;
			if(i+j<=2){f[i][j]=0;continue;}
			f[i][j]=inf;
			for(int x=0;x<=i;++x)for(int y=0;y<=j;++y)if(x+y && (i-x+j-y)){
				if(chkmin(f[i][j],max(f[x+y][i-x],f[i-x+j-y][x])+1)){
					vx[i][j]=x;vy[i][j]=y;
				};
			}
		}
	}
	int n;
	cin>>n;
	st.resize(n);
	for(int i=1;i<=n;++i)st[i-1]=i;
	if(st.size()>=4){
		for(int i=0;i<4;++i){s[i]=(st.size()+3-i)/4;nst[i].clear();}
		for(int i=0;i<4;++i){for(;s[i];--s[i]){nst[i].emplace_back(st.back());st.pop_back();}}
		int v1=ask(nst[0]+nst[1]),v2=ask(nst[0]+nst[2]);
		int vv=v1<<1|v2;
		st.clear();
		big[0]=nst[!v2]+nst[!v2+2];
		small[0]=nst[!(v1)<<1|v2];
		while(big[0].size()+small[0].size()>3){
			int v1=big[0].size()>>1,v2=small[0].size()>>1;
			if(big[0].size()&small[0].size()&1){
				++v1;
			}
			if(big[0].size()+small[0].size()<=100){
				v1=vx[big[0].size()][small[0].size()];
				v2=vy[big[0].size()][small[0].size()];
			}
			for(;v1;--v1){big[1].push_back(big[0].back());big[0].pop_back();}
			for(;v2;--v2){small[1].push_back(small[0].back());small[0].pop_back();}
			io::flush();
			int val=ask(big[1]+small[1]);
			small[!val].clear();
			while(!small[val].empty()){big[val].emplace_back(small[val].back());small[val].pop_back();}
			swap(small[0],big[!val]);
			if(val)swap(big[0],big[val]);
		}	
		if(big[0].size()+small[0].size()==3){
			if(big[0].size()==2){
				if(!ask({small[0][0]})){
					st=big[0];
					goto END;
				}
				else swap(big[0],small[0]);
			}
			if(ask({small[0][0]}))st={big[0][0],small[0][0]};
			else st={big[0][0],small[0][1]};
		}
		else st=big[0]+small[0];
		END:;
	}
	else if(st.size()==3){
		if(!ask({st[2]})){
			if(!ask({st[2]})){
				st.pop_back();
				
			}
		}
		if(st.size()==3){
			int v=ask({st[1]});
			if(v)swap(st[0],st[2]);
			else swap(st[1],st[2]);
			st.pop_back();
		}
	}
	for(auto i:st)answer(i);
	return 0;
}