#include<iostream>
#include<vector>
#include<stack>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
#include<string>
#include<tuple>
#include<queue>
//#define int long long
using namespace std;
int gcd(int i, int j) {
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
const long long INF = 1e17;
const int Y = 200100;
vector<int>Ed[Y];
int dp[1000];
//const long long m = 1000000007;
int32_t main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        int n, x;
        cin >> n >> x;
        --x;
        for (int i = 0; i < n; ++i) {
            Ed[i].clear();
            dp[i] = 0;
        }
        vector<int>li(n);
        for (int i = 0; i < n - 1; ++i) {
            int a, b;
            cin >> a >> b;
            --a;
            --b;
            Ed[a].push_back(b);
            Ed[b].push_back(a);
            ++li[a];
            ++li[b];
        }
        if (li[x] <= 1) {
            cout << "Ayush\n";
            continue;
        }
        if (n % 2 == 1) {
            cout << "Ashish\n";
        }
        else cout << "Ayush\n";
    }
    return 0;
}
//freopen("painter.in", "r", stdin);
//freopen("painter.out", "w", stdout);
/*
3
ooo
o..
o..
*/
/* Fri May 15 2020 19:54:42 GMT+0300 (MSK) */

/* Wed May 20 2020 19:33:48 GMT+0300 (MSK) */