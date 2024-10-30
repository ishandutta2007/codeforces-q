#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;

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
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x<10) putchar(x+'0');
	else
	{
		write(x/10);
		putchar(x%10+'0');
	}
}
void print(int x,char c='\n')
{
	write(x);
	putchar(c);
}
int a[N];

signed main()
{
	int T=read();
	while (T--)
	{
		int n=read(),k=read(),ans=0;
		for (int i=1;i<=n*k;i++) a[i]=read();
		sort(a+1,a+1+n*k);
		for (int i=1;i<=k;i++) ans+=a[n*k-i*(n/2+1)+1];
		print(ans);
	}

	return 0;
}