#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;

int read()
{
	int s=0;
	char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(int x)
{
	if (x<0) putchar('-'),x=-x;
	if (x<10) putchar(x+'0');
	else write(x/10),putchar(x%10+'0');
}
void print(int x,char c='\n')
{
	write(x);
	putchar(c);
}
char a[N];
int is[N],ans=0,n,q;
void fix(int x)
{
	if (x<1||x+2>n) return;
	ans-=is[x];
	ans+=is[x]=a[x]=='a'&&a[x+1]=='b'&&a[x+2]=='c';
}
void GreenDay()
{
	n=read(),q=read();
	scanf("%s",a+1);
	for (int i=1;i<=n;i++) fix(i);
	for (int i=1;i<=q;i++)
	{
		int x=read();
		cin>>a[x];
		for (int j=x-2;j<=x;j++) fix(j);
		print(ans);
	}
}

signed main(signed Hello,char *CodeForces[])
{
	(void)Hello,(void)CodeForces;
	int T=1;
//	int T=read();
	while (T--) GreenDay();
	
	return 0;
}