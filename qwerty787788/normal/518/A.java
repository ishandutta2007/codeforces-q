import java.io.*;
import java.util.*;

public class CF {
	FastScanner in;
	PrintWriter out;

	void solve() {
		char[] a = in.next().toCharArray();
		char[] b = in.next().toCharArray();
		int n = a.length;
		boolean fail = true;
		for (int i = n - 1; i >= 0; i--) {
			if (a[i] != 'z') {
				a[i]++;
				for (int j = i + 1; j < n; j++) {
					a[j] = 'a';
				}
				break;
			}
		}
		for (int i = 0; i < n; i++) {
			if (a[i] != b[i]) {
				fail = false;
			}
		}
		if (fail) {
			out.println("No such string");
		} else {
			for (int i = 0; i < n; i++) {
				out.print(a[i]);
			}
			out.println();
		}
	}

	void runIO() {

		in = new FastScanner(System.in);
		out = new PrintWriter(System.out);

		solve();

		out.close();
	}

	void run() {
		try {
			in = new FastScanner(new File("test.in"));
			out = new PrintWriter(new File("test.out"));

			solve();

			out.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
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
		new CF().runIO();
	}
}