#include<bits/stdc++.h>
using namespace std;

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

int main()
{
	int T=read();
	while (T--)
	{
		int a=read(),b=read(),c=read(),ans=0;
		if (a<b) swap(a,b);
		if (a<c) swap(a,c);
		if (b<c) swap(b,c);
		if (a) a--,ans++;
		if (b) b--,ans++;
		if (c) c--,ans++;
		if (a&&b) a--,b--,ans++;
		if (a&&c) a--,c--,ans++;
		if (b&&c) b--,c--,ans++;
		if (a&&b&&c) ans++;
		print(ans);
	}

	return 0;
}