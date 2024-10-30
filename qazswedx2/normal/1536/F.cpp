#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int mod=1e9+7;
inline int addmod(int x)
{
	return x>=mod?x-mod:x;
}
inline int submod(int x)
{
	return x<0?x+mod:x;
}
int fpow(int x,int y)
{
	int ans=1;
	while(y)
	{
		if(y&1) ans=1ll*ans*x%mod;
		x=1ll*x*x%mod;
		y/=2;
	}
	return ans;
}
int n,fr[1000005],infr[1000005],pn=1e6;
int C(int x,int y)
{
	return 1ll*fr[x]*infr[y]%mod*infr[x-y]%mod; 
}
int main()
{
	fr[0]=infr[0]=1;
	for(int i=1;i<=pn;i++)
	{
		fr[i]=1ll*fr[i-1]*i%mod;
		infr[i]=fpow(fr[i],mod-2);
	}
	scanf("%d",&n);
	int ans=0;
	for(int i=0;2*i<=n;i++)
	{
		if(n%2!=i%2) continue;
		ans=addmod(ans+1ll*(C(n-i,i)+C(n-i-1,i-1))*fr[n-i]%mod);
	}
	ans=2*ans%mod;
	printf("%d\n",ans);
	return 0;
}