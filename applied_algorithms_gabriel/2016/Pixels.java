import java.util.*;
import java.io.*;


// https://www.hackerrank.com/contests/pa2016-test-1-varianta-2-goku/challenges/pixeli-problema-usoara/problem
class Solution {
    int[][] img;
    int size;

    StringBuilder sb = new StringBuilder();
    void read() {
        MyScanner sc = new MyScanner(new InputStreamReader(System.in));
        size = sc.nextInt();
        img = new int[size][size];

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                img[i][j] = sc.nextInt();
            }
        }
    }

    void solve() {
        sb.append(divideConquer(0, 0, size));
    }

    String divideConquer(int start, int end, int size) {
        if (size == 1) {
            return img[start][end] == 1 ? "01" : "00";
        }

        int half = size / 2;
        String upperLeft = divideConquer(start, end, half);
        String upperRight = divideConquer(start, end + half, half);
        String lowerLeft = divideConquer(start + half, end, half);
        String lowerRight = divideConquer(start + half, end + half, half);

        if (upperLeft.equals("01") && upperRight.equals("01") && lowerLeft.equals("01") && lowerRight.equals("01")) {
            return "01";
        } else if (upperLeft.equals("00") && upperRight.equals("00") && lowerLeft.equals("00") && lowerRight.equals("00")) {
            return "00";
        } else {
            return "1" + upperLeft + upperRight + lowerLeft + lowerRight;
        }

    }

    void print() {
        System.out.println(sb.toString().length());
    }
}

public class Pixels {
    public static void main(String[] args) {
        Solution solution = new Solution();
        solution.read();
        solution.solve();
        solution.print();
    }
}

class Pair<T1, T2> {
    T1 first;
    T2 second;

    Pair(T1 first, T2 second) {
        this.first = first;
        this.second = second;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Pair) {
            Pair<?, ?> other = (Pair<?, ?>) obj;
            return first.equals(other.first) && second.equals(other.second);
        }
        return false;
    }
    

    @Override
    public int hashCode() {
        return first.hashCode() ^ second.hashCode();
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