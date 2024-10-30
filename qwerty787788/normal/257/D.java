import java.io.*;
import java.util.*;

public class CF159DIV2 {
	FastScanner in;
	PrintWriter out;

	void solve() {
		int n = in.nextInt();
		int[] a = new int[n];
		for (int i =0; i < n; i++)
			a[i] = in.nextInt();
		solve2(a);
//		Random rnd = new Random(124);
//		while (true) {
//			int n = 30;
//			int[] a = new int[n];
//			a[0] = 1 + rnd.nextInt(10);
//			for (int i = 1; i < n; i++) {
//				int l = a[i - 1];
//				int r = a[i - 1] * 2;
//				int val = l + rnd.nextInt(r - l + 1);
//				a[i] = val;
//			}
//			solve2(a);
//		}
	}
	
	void solve2(int[] x) {
		int n = x.length;
		int[] a = new int[n];
		for (int i = 0; i < n; i++)
			a[i] = x[i];
		int[] ans = new int[n];
		ans[n - 1] = 1;
		int sum = a[n - 1];
		for (int i = n - 2; i >= 0; i--) {
			if (sum >= 0) {
				sum -= a[i];
			} else {
				sum += a[i];
				ans[i] = 1;
			}
		}
		if (sum > a[0] || sum < 0) {
			ans = new int[n];
			ans[n - 1] = 0;
			sum = -a[n - 1];
			for (int i = n - 2; i >= 0; i--) {
				if (sum > 0) {
					sum -= a[i];
				} else {
					sum += a[i];
					ans[i] = 1;
				}
			}
			if (sum > a[0] || sum < 0) {
				System.err.println("F*CK");
				for (int i = 0; i < n; i++) 
					System.err.print(a[i] + " ");
				throw new AssertionError();
			}
		}
		for (int i = 0; i < n; i++) {
			if (ans[i] == 0) 
				out.print("-"); else
					out.print("+");
		}
	}

	void run() {
		try {
			in = new FastScanner(new File("object.in"));
			out = new PrintWriter(new File("object.out"));

			solve();

			out.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}

	void runIO() {

		in = new FastScanner(System.in);
		out = new PrintWriter(System.out);

		solve();

		out.close();
	}

	class FastScanner {
		BufferedReader br;
		StringTokenizer st;

		public FastScanner(File f) {
			try {
				br = new BufferedReader(new FileReader(f));
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			}
		}

		public FastScanner(InputStream f) {
			br = new BufferedReader(new InputStreamReader(f));
		}

		String next() {
			while (st == null || !st.hasMoreTokens()) {
				String s = null;
				try {
					s = br.readLine();
				} catch (IOException e) {
					e.printStackTrace();
				}
				if (s == null)
					return null;
				st = new StringTokenizer(s);
			}
			return st.nextToken();
		}

		boolean hasMoreTokens() {
			while (st == null || !st.hasMoreTokens()) {
				String s = null;
				try {
					s = br.readLine();
				} catch (IOException e) {
					e.printStackTrace();
				}
				if (s == null)
					return false;
				st = new StringTokenizer(s);
			}
			return true;
		}

		int nextInt() {
			return Integer.parseInt(next());
		}

		long nextLong() {
			return Long.parseLong(next());
		}

		double nextDouble() {
			return Double.parseDouble(next());
		}
	}

	public static void main(String[] args) {
		new CF159DIV2().runIO();
	}
}