//ANMHLIJKTJIY!
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
#pragma GCC diagnostic error "-fwhole-program"
#pragma GCC diagnostic error "-fcse-skip-blocks"
#pragma GCC diagnostic error "-funsafe-loop-optimizations"
#include <bits/stdc++.h>
#define INF 1000000000
#define LINF 1000000000000000000
#define MOD 1000000007
#define mod 998244353
#define F first
#define S second
#define ll long long
#define N 100010
using namespace std;
string s;
ll cnt[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	ll T,i;
	cin>>T;
	while(T--)
	{
		cin>>s;
		for(i=0;i<26;i++)
		{
			cnt[i]=0;
		}
		for(i=s.size()-1;i>=0;i--)
		{
			cnt[s[i]-'a']++;
		}
		for(i=0;i<s.size();i++)
		{
			if(cnt[s[i]-'a']<=1)
			{
				break;
			}
			cnt[s[i]-'a']--;
		}
		for(;i<s.size();i++)
		{
			cout<<s[i];
		}
		cout<<endl;
	}
	return 0;
}