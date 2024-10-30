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
const long long INF = 100000000;
const int Y = 2000100;
//const long long m = 1000000007;
long long ar[100];
long long n, m;
long long get() {
    long long d = 1, r = 0;
    for (int i = m - 1; i >= 0; --i) {
        char t;
        cin >> t;
        if (t == '1') r |= d << i;
    }
    return r;
}
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    vector < string> dd;
    while (t--) {
        cin >> n >> m;
        for (int i = 0; i < n; ++i) {
            ar[i] = get();
        }
        sort(ar, ar + n);
        long long ct = ((long long)1 << m) - n;
        long long in = (ct - 1) / 2;
        long long nw = 0;
        long long res = -1;
        for (int i = 0; i < n; ++i) {
            if (in + nw < ar[i]) {
                res = in + nw;
                break;
            }
            else {
                ct = ar[i] - nw + 1;
                in -= ct - 1;
                nw = ar[i] + 1;
            }
        }
        if (res == -1)res = nw + in;
        string ans = "";
        long long d = 1;
        for (int i = m - 1; i >= 0; --i) {
            if ((res & (d << i)) != 0) {
                ans.push_back('1');
            }
            else ans.push_back('0');
        }
        dd.push_back(ans);
    }
    for (auto x : dd)cout << x << endl;
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