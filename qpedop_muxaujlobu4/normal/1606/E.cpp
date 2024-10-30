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
const int mod = 998244353;
const ld eps = 1e-11, pi = acos(-1);
const ll maxN = 501, maxT = 1010, A = 179, K = 200;
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
	cout << "impossible\n";
	exit(0);
}
int dp[maxN][maxN];
// sub[n][k]
int sub_dp[maxN][maxN];
ll f[maxN], g[maxN];
ll c(int n, int k) {
	return f[n] * g[k] % mod * g[n - k] % mod;
}
void solve() {
	f[0] = g[0] = 1;
	for (int i = 1; i < maxN; ++i) {
		f[i] = f[i - 1] * i % mod;
		g[i] = bp(f[i], mod - 2);
	}
	int n, x;
	cin >> n >> x;
	dp[n][0] = 1;
	int ans = 0;
	for (int i = 0; i <= n; ++i) {
		for (int k = 0; k <= x; ++k) {
			sub_dp[i][k] = 1;
			for (int j = 0; j < i; ++j) {
				sub_dp[i][k] = (ll)sub_dp[i][k] * k % mod;
			}
		}
	}
	for (int i = 0; i <= x; ++i) {
		ans = (ans + dp[0][i]) % mod;
		for (int j = 2; j <= n; ++j) {
			int add = j - 1;
			if (i + add > x) {
				int tmp = x - i;
				if (tmp) {
					ans = (ans + (ll)dp[j][i] * sub_dp[j][tmp]) % mod;
				}
				continue;
			}
			for (int d = 0; d <= j; ++d) {
				dp[j - d][i + add] = (dp[j - d][i + add] +
					(ll)dp[j][i] * sub_dp[d][add] % mod * c(j, d)) % mod;
			}
		}
	}
	cout << ans << endl;
}
int32_t main()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout.precision(20);
	srand(time(0));
#ifdef _DEBUG
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
#else
	//freopen("hear.in", "r", stdin); freopen("hear.out", "w", stdout);
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