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
int a[N];

signed main(signed Goodbye,char *Wangang[])
{
	(void)Goodbye,(void)Wangang;
	int n=read(),ans=0;
	for (int i=1;i<=n;i++) a[i]=read();
	for (int j=1;j<=30;j++)
	{
		int mx=0,sum=0;
		for (int i=1;i<=n;i++)
		if (a[i]<=j) mx=max(mx,sum=max(sum+a[i],0));
				else sum=0;
		ans=max(ans,mx-j);
	}
	print(ans);
	
	return 0;
}