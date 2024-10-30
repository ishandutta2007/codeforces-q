#include <bits/stdc++.h>

const int N = 2e5 + 50;
const int mod = 1e9 + 7;

inline int inc(int x, int y) { x += y - mod; return x + (x >> 31 & mod); }
inline int dec(int x, int y) { x -= y; return x + (x >> 31 & mod); }

int n, b[N], f[N][2];
long long S[N];

template<int T>
struct fast_io
{
	char p[T], q[T], *p1, *p2, *q1, *q2;

	fast_io()
	{
		p1 = p2 = p;
		q1 = q, q2 = q + T;
	}

	inline char gc()
	{
		return p1 == p2 && (p2 = (p1 = p) + fread(p, 1, T, stdin), p1 == p2) ? EOF : *p1++;
	}

	inline void pc(char c)
	{
		if (q1 == q2)
		{
			fwrite(q, 1, T, stdout);
			q1 = q;
		}
		*q1++ = c;
	}

	~fast_io()
	{
		fwrite(q, 1, q1 - q, stdout);
	}
};

fast_io<2000000> io;

inline int64_t read()
{
	int64_t r = 0, neg = 1;
	char ch;
	do
	{
		ch = io.gc();
		if (ch == '-') neg = -1;
	}
	while (ch < 48 || ch > 57);
	do r = r * 10 + ch - 48, ch = io.gc(); while (ch >= 48 && ch <= 57);
	return r * neg;
}

inline void putint(int x)
{
	if (x < 0)
	{
		io.pc('-');
		putint(-x);
		return;
	}
	if (x / 10) putint(x / 10);
	io.pc(48 + x % 10);
}

inline void output(int x, char ch = ' ')
{
	putint(x);
	io.pc(ch);
}

std::unordered_map<long long, int> map;
int main()
{
	int t = read();
	while (t--)
	{
		int n = read();
		for (int i = 1; i <= n; ++i) b[i] = read(), f[i][0] = f[i][1] = 0, S[i] = S[i - 1] + b[i];
		f[0][1] = 1;
		int sum = 1;
		
		map.clear();
		map[0] = 1;
		for (int i = 1; i <= n; ++i)
		{
			f[i][0] = inc(f[i - 1][0], f[i - 1][1]);
			f[i][1] = dec(sum, map[S[i] - b[i]]);
			sum = inc(sum, f[i][1]);
			if (!map.count(S[i - 1])) map[S[i - 1]] = 0;
			int x = map[S[i - 1]];
			x = inc(x, f[i][1]);
			map[S[i - 1]] = x;
		}
		output(inc(f[n][0], f[n][1]), '\n');
	}
	return 0;
}