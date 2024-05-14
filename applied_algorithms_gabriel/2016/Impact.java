import java.util.*;
import java.io.*;


// https://www.hackerrank.com/contests/pa2016-test-1-varianta-1-sasuke/challenges/acs-impact-problema-usoara/problem
class Solution {
    int curPoints, endPoints, levels;
    Pair<Integer, Integer> levelScores[];

    int maxLevel = 0;

    @SuppressWarnings("unchecked")
    void read() {
        MyScanner sc = new MyScanner(new InputStreamReader(System.in));
        curPoints = sc.nextInt();
        endPoints = sc.nextInt();
        levels = sc.nextInt();
        levelScores = new Pair[levels];

        for (int i = 0; i < levels; i++) {
            int start = sc.nextInt();
            int end = sc.nextInt();
            levelScores[i] = new Pair<>(start, end);
        }
    }

    void solve() {
        // sort by entry points
        Arrays.sort(levelScores, (a, b) -> Integer.compare(a.first, b.first));
        
        // max heap to store most profitable levels
        PriorityQueue<Pair<Integer, Integer>> pq = new PriorityQueue<>((a, b) -> Integer.compare(b.second, a.second));

        int index = 0;

        while (curPoints < endPoints) {
            while (true) {
                if (index >= levels) {
                    break;
                }

                Pair<Integer, Integer> level = levelScores[index];
                if (level.first <= curPoints) {
                    pq.add(level);
                    index++;
                } else {
                    break;
                }
            }

            if (pq.isEmpty()) {
                break;
            }

            Pair<Integer, Integer> level = pq.poll();
            curPoints  = level.second;
            maxLevel++;
        }
    }

    void print() {
        System.out.println(maxLevel);
    }
}



public class Impact {
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