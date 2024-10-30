#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=2e5+5;

ll read()
{
	ll s=0;
	char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(ll x)
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
void print(ll x,char c='\n')
{
	write(x);
	putchar(c);
}
ll a[N],w[N];

int main()
{
	ll T=read();
	while (T--)
	{
		ll n=read(),k=read(),ans=0;
		for (ll i=1;i<=n;i++) a[i]=read();
		for (ll i=1;i<=k;i++) w[i]=read();
		sort(a+1,a+1+n,greater<ll>());
		sort(w+1,w+1+k);
		for (ll i=1;i<=k;i++) ans+=a[i];
		ll now=k;
		for (ll i=1;i<=k;i++)
		if (w[i]==1) ans+=a[i];
		else
		{
			now+=w[i]-1;
			ans+=a[now];
		}
		print(ans);
	}

	return 0;
}