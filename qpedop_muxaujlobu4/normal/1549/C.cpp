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
int mod = 1000000007;
const ld eps = 1e-9, pi = acosl(-1);
const ll maxN = 200100, maxT = 10010, A = 179, mid = 150;
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
int ans = 0;
int bd[maxN];
void add(int f, int s) {
	if (++bd[min(f, s)] == 1)--ans;
}
void del(int f, int s) {
	if (--bd[min(f, s)] == 0)++ans;
}
void solve() {
	int n, m;
	cin >> n >> m;
	ans = n;
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		add(--a, --b);
	}
	int q;
	cin >> q;
	while (q--) {
		int t;
		cin >> t;
		if (t == 3) {
			cout << ans << "\n";
			continue;
		}
		int a, b;
		cin >> a >> b;
		if (t == 1)
			add(--a, --b);
		else del(--a, --b);
	}
}
int32_t main()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout.precision(20);
	//srand(time(0));
#ifdef _DEBUG
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
#else
	//freopen("commuting.in", "r", stdin); freopen("commuting.out", "w", stdout);
#endif
	int t = 1;
	//cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}

/*
5
2 1 3 5 4
simple solve: 1 2 3 1 2
1 2 3 3 3
*/