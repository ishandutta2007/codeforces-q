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
ll n,f[105][105],g[105][105],dp[105][105];
char s[5];
bool qry(vector<ll> v)
{
	ll i;
	vector<ll> q;
	for(i=0;i<v.size();i++)
	{
		if(v[i]<=n)
		{
			q.push_back(v[i]);
		}
	}
	if(q.empty())
	{
		return false;
	}
	printf("? %d ",q.size());
	for(i=0;i<q.size();i++)
	{
		printf("%lld ",q[i]);
	}
	puts("");
	fflush(stdout);
	scanf("%s",&s);
	return (s[0]=='Y');
}
bool chk(ll v)
{
	printf("! %lld\n",v);
	fflush(stdout);
	scanf("%s",&s);
	return (s[1]==')');
}
void solve(vector<ll> tr,vector<ll> fs)
{
	ll i;
	if(tr.size()+fs.size()<3||(tr.size()+fs.size()==3&&fs.size()==1))
	{
		ll i;
		vector<ll> v=tr;
		for(i=0;i<fs.size();i++)
		{
			v.push_back(fs[i]);
		}
		if(v.size()==1)
		{
			assert(chk(v[0]));
		}
		else if(v.size()==2)
		{
			if(!chk(v[0]))
			{
				assert(chk(v[1]));
			}
		}
		else
		{
			if(!qry({v[2]}))
			{
				if(!chk(v[0]))
				{
					assert(chk(v[1]));
				}
			}
			else
			{
				if(!chk(v[2]))
				{
					if(qry({v[0]}))
					{
						assert(chk(v[0]));
					}
					else
					{
						assert(chk(v[1]));
					}
				}
			}
		}
		return;
	}
	ll la,lb;
	la=tr.size()/2;
	lb=(fs.size()+1)/2;
	vector<ll> lt,lf,rt,rf;
	for(i=0;i<tr.size();i++)
	{
		if(i<la)
		{
			lt.push_back(tr[i]);
		}
		else
		{
			rt.push_back(tr[i]);
		}
	}
	for(i=0;i<fs.size();i++)
	{
		if(i<lb)
		{
			lf.push_back(fs[i]);
		}
		else
		{
			rf.push_back(fs[i]);
		}
	}
	vector<ll> v=lt;
	for(i=0;i<lf.size();i++)
	{
		v.push_back(lf[i]);
	}
	if(!qry(v))
	{
		swap(lt,rt);
		swap(lf,rf);
	}
	vector<ll> nl=lt,nr=rt;
	for(i=0;i<lf.size();i++)
	{
		nl.push_back(lf[i]);
	}
	solve(nl,nr);
	return;
}
int main(){
	ll i;
	scanf("%lld",&n);
	vector<ll> v;
	for(i=1;i<=((n>=99000)?100000:n);i++)
	{
		v.push_back(i);
	}
	solve(v,{});
	return 0;
}