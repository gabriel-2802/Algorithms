import java.util.*;
import java.io.*;


// https://www.hackerrank.com/contests/pa2016-test-1-varianta-2-goku/challenges/cryptography-1/problem
class Solution {
    char[] a;
    char[] b;
    char[] c;
    Map<Character, Integer> map = new HashMap<>(); // char -> coded value
    Set<Character> alphabet = new HashSet<>(); // all characters in a, b, c

    char[] alphabetArr;
    int[] alphabetValue;

    // a + b = c in coded form
    void read() {
        MyScanner sc = new MyScanner(new InputStreamReader(System.in));
        a = sc.nextLine().toCharArray();
        b = sc.nextLine().toCharArray();
        c = sc.nextLine().toCharArray();

        for (char ch : a) {
            alphabet.add(ch);

        }

        for (char ch : b) {
            alphabet.add(ch);
        }

        for (char ch : c) {
            alphabet.add(ch);
        }

    }

    void solve() {
        alphabetArr = new char[alphabet.size()];
        alphabetValue = new int[alphabet.size()];
        int idx = 0;
        for (char ch : alphabet) {
            alphabetArr[idx++] = ch;
        }
    
        if (backtrack(0, new boolean[10])) {
            System.out.println(convertToNumber(a));
            System.out.println(convertToNumber(b));
            System.out.println(convertToNumber(c));
        }
    }
    
    boolean backtrack(int index, boolean[] used) {
        if (index == alphabetArr.length) {
            if (testValid()) {
                return true;
            }
            return false;
        }
    
        for (int digit = 0; digit < 10; digit++) {
            if (!used[digit]) {
                used[digit] = true;
                alphabetValue[index] = digit;
                if (backtrack(index + 1, used)) {
                    return true;
                }
                used[digit] = false;
            }
        }
        return false;
    }

    boolean testValid() {
        long numA = convertToNumber(a);
        long numB = convertToNumber(b);
        long numC = convertToNumber(c);
        return numA + numB == numC;
    }

    long convertToNumber(char[] array) {
        long result = 0;
        for (char ch : array) {
            result = result * 10 + alphabetValue[indexOf(ch)];
        }
        return result;
    }
    int indexOf(char ch) {
        for (int i = 0; i < alphabetArr.length; i++) {
            if (alphabetArr[i] == ch) {
                return i;
            }
        }
        return -1;
    }
    
}

public class Crypto {
    public static void main(String[] args) {
        Solution solution = new Solution();
        solution.read();
        solution.solve();
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