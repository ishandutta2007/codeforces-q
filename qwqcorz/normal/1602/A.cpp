#include<bits/stdc++.h>
using namespace std;
const int N=105;

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

signed main(signed bangumi,char *ss1672[])
{
	(void)bangumi,(void)ss1672;
	int T=read();
	while (T--)
	{
		scanf("%s",a+1);
		int n=strlen(a+1),mn=1;
		for (int i=2;i<=n;i++) if (a[i]<a[mn]) mn=i;
		putchar(a[mn]);
		putchar(' ');
		for (int i=1;i<=n;i++) if (i!=mn) putchar(a[i]);
		putchar('\n');
	}
	
	return 0;
}