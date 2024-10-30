#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,abm,mmx,tune=native")
#include<vector>
#include<iostream>
#include<stack>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
#include<string>
#include<tuple>
#include<bitset>
#include<queue>
#include<unordered_map>
#include<random>
#include<ctime>
//#include<complex>
#include<numeric>
typedef long long ll;
typedef long double ld;
typedef unsigned short us;
typedef unsigned long long ull;
//typedef complex<double> base;
using namespace std;
ll gcd(ll i, ll j) {
	if (j == 0)return i;
	else return gcd(j, i % j);
}
#ifdef _DEBUG
int __builtin_popcount(int x) { return x ? (__builtin_popcount(x >> 1) + (x & 1)) : 0; }
#endif
template<typename T> inline T getint() {
	T val = 0;
	char c;

	bool neg = false;
	while ((c = getchar()) && !(c >= '0' && c <= '9')) {
		neg |= c == '-';
	}

	do {
		val = (val * 10) + c - '0';
	} while ((c = getchar()) && (c >= '0' && c <= '9'));

	return val * (neg ? -1 : 1);
}
//#define int long long
const ll INF = 1e9 + 100;
const int mod = 1000000007;
const ld eps = 1e-10, pi = acosl(-1);
const ll maxN = 200100, maxT = 61, A = 179, mid = 150;
mt19937 mt_rand(time(0));
ll bp(ll et, ll b) {
	b %= mod - 1;
	ll res = 1;
	for (int i = 30; i >= 0; --i) {
		res = (res * res) % mod;
		if ((b & (1 << i)) != 0)res = (res * et) % mod;
	}
	return res;
}
void panic() {
	cout << "-1\n";
	exit(0);
}
vector<vector<int>>g, g1;
vector<int>tin, tout;
int tmr, ans = 0;
set<pair<int, int>>s;
void dfs1(int v) {
	tin[v] = tmr++;
	for (auto x : g1[v]) {
		dfs1(x);
	}
	tout[v] = tmr++;
}
void dfs(int v) {
	vector < pair<int, int>>add, del;
	auto it = s.lower_bound({ tin[v],tout[v] });
	if (it != s.end() && tin[v] <= (*it).first && (*it).first <= tin[v]) {

	}
	else {
		del.push_back({ tin[v],tout[v] });
		if (it != s.begin()) {
			--it;
			if ((*it).first <= tin[v] && tin[v] <= (*it).second) {
				add.push_back(*it);
				s.erase(it);
			}
		}
		s.insert({ tin[v],tout[v] });
	}
	ans = max(ans, (int)s.size());
	for (auto x : g[v]) {
		dfs(x);
	}
	for (auto x : del) {
		s.erase(x);
	}
	for (auto x : add) {
		s.insert(x);
	}
}
void solve(){
	int n;
	cin >> n;
	tmr = 0;
	g.assign(n, vector<int>());
	g1.assign(n, vector<int>());
	tin.assign(n, 0);
	tout.assign(n, 0);
	tmr = ans = 0;
	for (int i = 1; i < n; ++i) {
		int v;
		cin >> v;
		g[--v].push_back(i);
	}
	for (int i = 1; i < n; ++i) {
		int v;
		cin >> v;
		g1[--v].push_back(i);
	}
	dfs1(0);
	dfs(0);
	cout << ans << "\n";
}
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout.precision(10);
	//srand(time(0));
#ifdef _DEBUG
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
#else
	//freopen("gymnasts.in", "r", stdin); freopen("gymnasts.out", "w", stdout);
#endif
	int t = 1;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}