import java.util.*;
import java.io.*;

// https://www.hackerrank.com/contests/pa2016-test-1-varianta-2-goku/challenges/salupa-problema-usoara/problem
class Solution {
    int maxWeight;

    int chests = 0;
    int totalWeight = 0;

    void readAndSolve() {
        MyScanner sc = new MyScanner(new InputStreamReader(System.in));
        maxWeight = sc.nextInt();
        int n = sc.nextInt();

        PriorityQueue<Integer> pq = new PriorityQueue<>(Collections.reverseOrder());
        for (int i = 0; i < n; ++i) {
            int chestWeight = sc.nextInt();

            chests++;
            totalWeight += chestWeight;
            pq.add(chestWeight);

            while (totalWeight > maxWeight) {
                totalWeight -= pq.poll();
                chests--;
            }

        }

        System.out.println(chests);
        System.out.println(totalWeight);
    }
}

public class Boat {
    public static void main(String[] args) {
        Solution solution = new Solution();
        solution.readAndSolve();
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