#include <stdio.h>
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define pll pair<ll,ll>
#define puu pair<ull,ull>
#define fi first
#define se second
#define inf 0x3f3f3f3f
#define infll 0x3f3f3f3f3f3f3f3f
#define mset(a, b) memset(a, b, sizeof a)
#define lep(i, j, k) for (int i = (j); i <= (k); i++)
#define rep(i, j, k) for (int i = (j); i >= (k); i--)
#define Lep(i, j, k) for (int i = (j); i < (k); i++)
#define Rep(i, j, k) for (int i = (j); i > (k); i--)

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

template <typename T>
void ckmin(T &A, T B) {A = A < B ? A : B;}
template <typename T>
void ckmax(T &A, T B) {A = A > B ? A : B;}

inline void read(int &x) {scanf("%d", &x);}
inline void print(int x) {printf("%d", x);}
inline void print(int x, char c) {printf("%d%c", x, c);}
inline void read(long long &x) {scanf("%lld", &x);}
inline void print(long long x) {printf("%lld", x);}
inline void print(long long x, char c) {printf("%lld%c", x, c);}

namespace MOD {
	const int P = 1e9 + 7;
	inline int add(int x, int y) {return x + y >= P ? x + y - P : x + y;}
	inline int sub(int x, int y) {return x < y ? x - y + P : x - y;}
	inline int mul(int x, int y) {return (long long)x * y % P;}
	inline void inc(int &x, int y) {x = add(x, y);}
	inline void dec(int &x, int y) {x = sub(x, y);}
	inline void upd(int &x, int y) {x = mul(x, y);}
};
using namespace MOD;

const int N = 2e5 + 10;

int n, a[N], c[100], pw[N];

int main() {
	read(n);
	pw[0] = 1;
	for (int i = 1; i <= n; i++) pw[i] = mul(pw[i - 1], 2);
	for (int i = 1; i <= n; i++) read(a[i]);
	for (int i = 1; i <= n; i++) {
		int b = 1, t = 1;
		while (a[i] % (b << 1) == 0) b <<= 1, t++;
		c[t]++;
	}
	int nw = n - c[1];
	int ans = mul(pw[nw], sub(pw[c[1]], 1));
	for (int i = 2; i <= 30; i++) {
		nw -= c[i];
		if (c[i] > 0) ans = add(ans, mul(sub(pw[c[i] - 1], 1), pw[nw]));
	}
	print(ans, '\n');
	return 0;
}