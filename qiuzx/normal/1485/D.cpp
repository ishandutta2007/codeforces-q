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
#define N 510
using namespace std;
ll n,m,a[N][N],num[20];
int main(){
	ll i,j;
	scanf("%lld%lld",&n,&m);
	for(i=0;i<20;i++)
	{
		num[i]=16*9*5*7*11*13-i*i*i*i;
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			scanf("%lld",&a[i][j]);
			if(i%2!=j%2)
			{
				a[i][j]=0;
			}
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			printf("%lld ",num[a[i][j]]);
		}
		puts("");
	}
	return 0;
}