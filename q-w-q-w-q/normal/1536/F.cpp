#include <cstdio>
#include <iostream>
using namespace std;
const int mod = 1e9 + 7, N = 1000005;
int n, fac[N], ifac[N], ans;
inline int power(int a, int n) {
  int tp = 1;
  while (n) {
    if (n & 1) tp = 1ll * tp * a % mod;
    a = 1ll * a * a % mod, n >>= 1;
  }
  return tp;
}
inline int c(int n, int m) { return n < m || m < 0 ? 0 : 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod; }
int main() {
  cin >> n;
  fac[0] = 1;
  for (int i = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
  ifac[n] = power(fac[n], mod - 2);
  for (int i = n - 1; ~i; i--) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
  for (int i = n & 1; i <= n; i += 2) ans = (ans + 1ll * c(n - i, i) * fac[n - i - 1]) % mod;
  cout << 2ll * ans * n % mod;
}