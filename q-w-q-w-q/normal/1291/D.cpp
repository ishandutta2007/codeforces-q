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
#define _t putchar(32)
#define _e putchar(10)
#define inf 2147483647
#define ine -2147483647
#define lb(x) ((x)&(-x))
#define sp(x,y) x^=y^=x^=y
using namespace std;
typedef long long ll;
bool o;
char ch,ss[1<<17],*A=ss,*B=ss;
inline char gc(){
	return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?EOF:*A++;
}
template <typename _Tp> inline void rd(_Tp &x);
template <typename _Tq> inline void wr(_Tq x);
template <typename _Tp> inline _Tp mx(_Tp x,_Tp y);
template <typename _Tp> inline _Tp mn(_Tp x,_Tp y);
char a[200001];
int n,q,l,r,k;
int s[200001][26],qwq[200001];
int main(){
	scanf("%s",a+1);
	n=strlen(a+1);
	for(int i=1,j;i<=n;i=j+1){
		for(j=i+1;j<=n&&a[i]==a[j];j++);
		j--;
		for(int k=i;k<=j;k++) qwq[k]=j;
	}
	for(int i=1;i<=n;i++){
		memcpy(s[i],s[i-1],sizeof(s[i-1]));
		s[i][a[i]-'a']++;
	}
	rd(q);
	while(q--){
		rd(l),rd(r);
		if(l==r){
			puts("Yes");
			continue;
		}
		k=0;
		for(int i=0;i<26;i++) if(s[r][i]-s[l-1][i]) k++;
		if(k>2){
			puts("Yes");
			continue;
		}
		if(qwq[l]>=r){
			puts("No");
			continue;
		}
		puts(a[l]!=a[r]?"Yes":"No");
	}
}
template <typename _Tp>
    inline void rd(_Tp &x){
    	o=0;
        x=0;
      	while (ch^45&&(ch<48||ch>57)) ch=gc();
      	if(ch==45)o=1,ch=gc();
        while(ch>47&&ch<58){
			x=(x<<1)+(x<<3)+(ch^48);
			ch=gc();
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