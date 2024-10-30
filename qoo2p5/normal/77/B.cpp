#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ull unsigned ll
#define ld long double
#define sz(x) (ll) x.size()
#define mp(a, b) make_pair(a, b)
#define pb(a) push_back(a)
#define eq(a, b) abs(a - b) < EPS

#ifdef DEBUG
  #define debug(x) cerr << "\033[31m" << x << "\033[39m" << endl;
#else
  #define debug(x)
#endif

const int INF = 1e9;
const ll LINF = 1e18;
const ld EPS = 1e-10;
const ld PI = 3.141592653589;
const ll MOD = 1e9 + 7;

#define TASKNAME ""

int main() {
  ios::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  float tbegin = clock();
  srand(42);

#ifdef DEBUG
  freopen("input.txt", "r", stdin);
#else
  if (TASKNAME != "") {
    freopen(TASKNAME ".in", "r", stdin);
    freopen(TASKNAME ".out", "w", stdout);
  }
#endif

  cout << fixed << setprecision(16);

  int t;
  cin >> t;

  for (int i = 0; i < t; i++) {
    ld a, b;
    cin >> a >> b;
    a /= 4;

    ld ans;

    if (abs(a) > EPS) {
      if (a <= b) {
        ans = ((a * b + a * a / 2) / (2 * b)) / a;
      } else {
        ans = (a - b) / a + (1 - (a - b) / a) * 0.75;
      }
    } else {
      ans = abs(b) < EPS ? 1 : 0.5;
    }

    cout << ans << "\n";
  }

#ifdef DEBUG
	cerr << "TIME ELAPSED: " << (clock() - tbegin) / CLOCKS_PER_SEC << "\n";
#endif

	return 0;
}