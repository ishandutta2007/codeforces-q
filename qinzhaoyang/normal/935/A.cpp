#include <iostream>

using namespace std;

int main()
{	
	int n;
	int ans = 0;
	cin >> n;
	for(int i = 2; i <= n; i++)
		if(n % i == 0)
			ans++;
	cout << ans << endl;
	return 0;
}