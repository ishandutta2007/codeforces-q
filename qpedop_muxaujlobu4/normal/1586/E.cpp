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
const ll INF = 1e18 + 100;
const int mod = 1000000007;
const ld eps = 1e-11, pi = acos(-1);
const ll maxN = 300010, maxT = 3010, A = 179, K = 420;
mt19937 mt_rand(time(0));
ll bp(ll et, ll b) {
	b %= mod - 1;
	et %= mod;
	ll res = 1;
	for (int i = 30; i >= 0; --i) {
		res = (res * res) % mod;
		if ((b & (1 << i)) != 0)res = (res * et) % mod;
	}
	return res;
}
void panic() {
	cout << "No solution\n";
	exit(0);
}
int f[maxN];
int find(int v) { return (f[v] == v ? v : f[v] = find(f[v])); }
bool uni(int a, int b) {
	a = find(a);
	b = find(b);
	if (a == b)return false;
	f[a] = b;
	return true;
}
vector<int>g[maxN];
int pr[maxN], cnt[maxN], deep[maxN];
void dfs(int v, int p = -1) {
	for (auto x : g[v]) {
		if (x == p)
			continue;
		pr[x] = v;
		deep[x] = deep[v] + 1;
		dfs(x, v);
	}
}
ll dp[maxN];
void dfs1(int v, int p = -1) {
	vector<int>tmp;
	for (auto x : g[v]) {
		if (x == p)
			continue;
		dfs1(x, v);
		if (cnt[x])tmp.push_back(x);
	}
	dp[0] += tmp.size() / 2;
	if (cnt[v] == 0)dp[0] += tmp.size() % 2;
}
void solve() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; ++i)f[i] = i;
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		if (uni(--a, --b)) {
			g[a].push_back(b);
			g[b].push_back(a);
		}
	}
	dfs(0);
	int q;
	cin >> q;
	vector<pair<int, int>>qw(q);
	for (auto& x : qw) {
		cin >> x.first >> x.second;
		--x.first;
		--x.second;
		int a = x.first, b = x.second;
		while (a != b) {
			if (deep[a] < deep[b]) {
				swap(a, b);
			}
			cnt[a] ^= 1;
			a = pr[a];
		}
	}
	int c = 0;
	for (int i = 0; i < n; ++i) {
		c += cnt[i];
	}
	if (c) {
		cout << "NO\n";
		dfs1(0);
		cout << dp[0] << "\n";
		return;
	}
	cout << "YES\n";
	for (auto x : qw) {
		int a, b;
		tie(a, b) = x;
		vector<int>va, vb;
		va.push_back(a);
		vb.push_back(b);
		while (a != b) {
			if (deep[a] > deep[b]) {
				a = pr[a];
				va.push_back(a);
			}
			else {
				b = pr[b];
				vb.push_back(b);
			}
		}
		vb.pop_back();
		reverse(vb.begin(), vb.end());
		cout << va.size() + vb.size() << "\n";
		for (auto x : va)cout << x + 1 << " ";
		for (auto x : vb)cout << x + 1 << " ";
		cout << "\n";
	}

}
int32_t main()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout.precision(20);
	srand(time(0));
#ifdef _DEBUG
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
#else
	//freopen("input.in", "r", stdin); freopen("input.out", "w", stdout);
#endif
	int t = 1;
	//cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
/*
7 7
1 2
2 3
3 4
4 5
2 5
5 6
6 7
5
4 3 2 5 6 7
1
*/