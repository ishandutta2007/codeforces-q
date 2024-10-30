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
const double eps = 1e-11, pi = acos(-1);
const ll maxN = 100010, maxT = 4096, A = 179, K = 170;
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
	cout << "No\n";
	exit(0);
}
void solve() {
	int n, m, k;
	cin >> n >> m >> k;
	vector<vector<int>>a(n, vector<int>(m)), b(n, vector<int>(m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			char t;
			cin >> t;
			a[i][j] = t == '*';
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (j + k >= m || j - k < 0 || i - k < 0)
				continue;
			bool f = 1;
			for (int k1 = 0; k1 <= k; ++k1) {
				f &= a[i - k1][j + k1] == a[i - k1][j - k1] && a[i - k1][j - k1] == 1;
			}
			if (!f)
				continue;
			for (int k1 = 0; j + k1 < m && j - k1 >= 0 && i - k1 >= 0; ++k1) {
				if (a[i - k1][j - k1] == 0)
					break;
				if (a[i - k1][j + k1] == 0)
					break;
				b[i - k1][j + k1] = b[i - k1][j - k1] = 1;
			}
		}
	}
	if (a == b)cout << "YES\n";
	else cout << "NO\n";
}
int32_t main()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout.precision(20);
	srand(time(0));
#ifdef _DEBUG
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
#else
	//freopen("graph.in", "r", stdin); freopen("graph.out", "w", stdout);
#endif
	int t = 1;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}