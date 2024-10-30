#pragma comment(linker, "/STACK:9759095000")
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
#include <unordered_map>
#include<random>
#include<ctime>
#define double long double
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
long long gcd(long long i, long long j) {
    if (j == 0)return i;
    else return gcd(j, i % j);
}
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
const long long INF = 1e9;
const int mod = 998244353;
const double eps = 1e-9, pi = acos(-1);
const int maxN = 100100, maxT = 2001;
void file_inc() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
   // file_inc();
    int t;
    cin >> t;
    vector<int>p;
    vector<int>simp(maxN);
    for (int i = 2; i < maxN; ++i) {
        if (simp[i] == 0) {
            p.push_back(i);
            for (int j = i + i; j < maxN; j += i)simp[j] = 1;
        }
    }
    while (t--) {
        ll n;
        cin >> n;
        map<ll, int>mp;
        int mx = 1;
        for (auto x : p) {
            while (n % x == 0) {
                n /= x;
                mx = max(mx, ++mp[x]);
            }
        }
        if (n != 1)++mp[n];
        cout << mx << "\n";
        for (; mx > 0; --mx) {
            ll tt = 1;
            for (auto& x : mp) {
                if (x.second == mx) {
                    tt *= x.first;
                    --x.second;
                }
            }
            cout << tt << " ";
        }
        cout << "\n";
    }
    return 0;
}