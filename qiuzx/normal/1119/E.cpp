#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define INF 1000000000
#define LINF 1000000000000000000
#define MOD 1000000007
#define mod 998244353
#define INF63 1061109567
#define INF127 9187201950435737471
#define UINF 18446744073709551615
#define F first
#define S second
#define ll long long
#define N 300010
using namespace std;
ll n,a[N],ans;
int main(){
	ll i,sum,x;
	scanf("%lld",&n);
	for(i=0;i<n;i++)
	{
		scanf("%lld",&a[i]);
	}
	sum=0;
	for(i=0;i<n;i++)
	{
		sum+=a[i];
		x=ans*3;
		ans+=min(a[i]/2,(sum-x)/3);
	}
	cout<<ans<<endl;
	return 0;
}