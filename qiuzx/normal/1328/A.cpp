#include <bits/stdc++.h>
#define INF 1000000000
#define LINF 1000000000000000000
#define MOD 1000000007
#define mod 1000007
#define INF63 1061109567
#define INF127 9187201950435737471
#define UINF 18446744073709551615
#define F first
#define S second
#define ll long long
using namespace std;
ll a,b,t;
int main(){
	cin>>t;
	while(t--)
	{
		cin>>a>>b;
		if(a%b!=0)
		{
			cout<<b-a%b<<endl;
		}
		else
		{
			cout<<0<<endl;
		}
	}
	return 0;
}