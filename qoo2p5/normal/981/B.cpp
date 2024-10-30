#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int INF = (int) 1e9 + 1e6 + 123;
const ll LINF = (ll) 1e18 + 1e9 + 123;

#define rep(i, s, t) for (auto i = (s); i < (t); ++(i))
#define per(i, s, t) for (auto i = (s); i >= (t); --(i))
#define sz(x) ((int)(x).size())
#define mp make_pair
#define pb push_back
#define all(x) (x).begin(), (x).end()

auto mini(auto &x, const auto &y) {
    if (y < x) {
        x = y;
        return 1;
    }
    return 0;
}

auto maxi(auto &x, const auto &y) {
    if (y > x) {
        x = y;
        return 1;
    }
    return 0;
}

void run();

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    run();
    return 0;
}

bool check(string s) {
    string rs = s;
    reverse(all(rs));
    return s == rs;
}

void run() {
    map<int, int> q;
    int n;
    cin >> n;
    rep(i, 0, n) {
        int a, x;
        cin >> a >> x;
        maxi(q[a], x);
    }
    int m;
    cin >> m;
    rep(i, 0, m) {
        int a, x;
        cin >> a >> x;
        maxi(q[a], x);
    }
    ll ans = 0;
    for (auto &it : q) {
        ans += it.second;
    }
    cout << ans << "\n";
}