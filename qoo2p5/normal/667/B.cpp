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

const ll INF = 1e9;
const ll LINF = 1e18;
const ld EPS = 1e-9;
const ld PI = 3.141592653589;
const ll MOD = 1e9 + 7;

#define TASKNAME ""

const int N = 1e5 + 123;

int n;
ll a[N];

int main() {
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
	cin.tie(nullptr);
	float tbegin = clock();
	srand(time(nullptr));

#ifdef DEBUG
	freopen("input.txt", "r", stdin);
#else
	if (TASKNAME != "") {
		freopen(TASKNAME ".in", "r", stdin);
		freopen(TASKNAME ".out", "w", stdout);
	}
#endif

  cin >> n;
  ll sum = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    sum += a[i];
  }
  
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    ans = max(ans, 2 * a[i] - sum + 1);
  }
  
  cout << ans << "\n";

#ifdef DEBUG
	cerr << "TIME ELAPSED: " << (clock() - tbegin) / CLOCKS_PER_SEC << "\n";
#endif

	return 0;
}