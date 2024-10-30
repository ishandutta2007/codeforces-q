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
const ll maxN = 200010, maxT = 61, A = 179, mid = 150;
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
ll tree[maxN << 2], to_push[maxN << 2];
int sz = 1;
void push(int v) {
	tree[v] += to_push[v];
	if (v < sz) {
		to_push[2 * v] += to_push[v];
		to_push[2 * v + 1] += to_push[v];
	}
	to_push[v] = 0;
}
void add(int ql, int qr, ll val, int tl = 0, int tr = sz - 1, int v = 1) {
	if (ql <= tl && tr <= qr) {
		to_push[v] += val;
		push(v);
		return;
	}
	int m = (tr + tl) / 2;
	push(v);
	if (ql <= m) {
		add(ql, qr, val, tl, m, 2 * v);
	}
	if (qr > m) {
		add(ql, qr, val, m + 1, tr, 2 * v + 1);
	}
	push(2 * v);
	push(2 * v + 1);
	tree[v] = min(tree[2 * v], tree[2 * v + 1]);
}
void solve(){
	int n;
	cin >> n;
	vector<pair<ll, int>>a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i].first;
		a[i].second = i;
	}
	while (sz < n)sz <<= 1;
	sort(a.begin(), a.end());
	reverse(a.begin(), a.end());
	int ans = 0;
	for (auto x : a) {
		ll vl, i;
		tie(vl, i) = x;
		add(i, n - 1, vl);
		if (tree[1] >= 0)++ans;
		else {
			add(i, n - 1, -vl);
		}
	}
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
	//cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}