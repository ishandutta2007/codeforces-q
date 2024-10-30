#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
const int inf=1ll<<60;

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
	int n=read(),m=read(),k=read(),ans=0;
	for (int i=1;i<=n;i++) a[i]=a[i-1]+read();
	for (int l=0;l<m;l++)
	for (int r=0;r<m;r++)
	{
		int Min=inf,add=((r-l)%m>0)*k;
		for (int i=1;i<=n;i++)
		{
			if ((i-1)%m==l)
			{
				Min=min(Min,a[i-1]-(i-1)/m*k);
			}
			if (i%m==r)
			{
				if (Min==inf) continue;
				ans=max(ans,a[i]-(i/m)*k-Min-add);
			}
		}
	}
	print(ans);

	return 0;
}