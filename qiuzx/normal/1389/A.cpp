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
using namespace std;
ll a,b,x,y;
int main(){
	ll T;
	cin>>T;
	while(T--)
	{
		cin>>a>>b;
		x=a;
		y=a*2;
		if(y>b)
		{
			puts("-1 -1");
		}
		else
		{
			cout<<x<<" "<<y<<endl;
		}
	}
	return 0;
}