#include <bits/stdc++.h>

int a[105];

inline char nc()
{
	static char buf[1000000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}

inline int read()
{
	int res = 0;
	char ch;
	do ch = nc(); while (ch < 48 || ch > 57);
	do res = res * 10 + ch - 48, ch = nc(); while (ch >= 48 && ch <= 57);
	return res;
}

int main()
{
	int n = read();
	for (int i = 1; i <= n; ++i) ++a[read()];
	printf("%d", (a[1] > a[2]) ? (a[1] - a[2]) / 3 + a[2] : a[1]);
	return 0;
}