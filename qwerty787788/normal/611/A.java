import java.io.*;
import java.util.*;

public class CF {
	FastScanner in;
	PrintWriter out;

	void solve() {
		int x = in.nextInt();
		in.next();
		String s = in.next();
		if (s.equals("week")) {
			x--;
			int cur = 4;
			int res = 0;
			for (int i = 0; i < 366; i++) {
				if (cur == x) {
					res++;
				}
				cur = (cur + 1) % 7;
			}
			out.println(res);
		} else {
			int[] a = new int[] { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30,
					31 };
			int res = 0;
			for (int y : a) {
				if (y >= x) {
					res++;
				}
			}
			out.println(res);
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
		new CF().runIO();
	}
}