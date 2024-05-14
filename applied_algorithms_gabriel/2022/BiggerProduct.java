import java.io.*;
import java.math.BigInteger;
import java.util.*;

// https://www.hackerrank.com/contests/test-practic-2022-06318/challenges/1-2-bigger-product-usoara/problem
// 30/50 score
class Solver {
    int n;
    Integer[] a;
    private int minCardinal;
    private BigInteger totalProduct;

    void read() {
        MyScanner sc = new MyScanner(new InputStreamReader(System.in));
        n = sc.nextInt();
        a = new Integer[n];
        totalProduct = BigInteger.ONE;
        for (int i = 0; i < n; i++) {
            a[i] = sc.nextInt();
            totalProduct = totalProduct.multiply(BigInteger.valueOf(a[i]));
        }
    }

    void solve() {
        Arrays.sort(a, Collections.reverseOrder());

        int index = 0;
        int cardinal = 0;
        BigInteger product = BigInteger.ONE;

        while (product.compareTo(totalProduct) < 0) {
            product = product.multiply(BigInteger.valueOf(a[index]));
            index++;
            cardinal++;
            totalProduct = totalProduct.divide(BigInteger.valueOf(a[index]));
        }

        minCardinal = cardinal;
    }
    void print() {
        System.out.println(minCardinal);

    }
}

public class BiggerProduct {

    public static void main(String[] args) {
        Solver solver = new Solver();
        solver.read();
        solver.solve();
        solver.print();
    }
}

class MyScanner {
    private BufferedReader br;
    private StringTokenizer st;

    public MyScanner(Reader reader) {
        br = new BufferedReader(reader);
    }

    public String next() {
        while (st == null || !st.hasMoreElements()) {
            try {
                st = new StringTokenizer(br.readLine());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return st.nextToken();
    }

    public int nextInt() {
        return Integer.parseInt(next());
    }

    public long nextLong() {
        return Long.parseLong(next());
    }

    public double nextDouble() {
        return Double.parseDouble(next());
    }

    public String nextLine() {
        String str = "";
        try {
            str = br.readLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return str;
    }
}