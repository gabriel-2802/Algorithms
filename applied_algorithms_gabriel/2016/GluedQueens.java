import java.util.*;
import java.io.*;

// https://www.hackerrank.com/contests/pa2016-test-1-varianta-1-sasuke/challenges/super-glue-chess-problema-medie
class Solution {
    int n;
    int xTower, yTower; // a tower at (xTower, yTower)
    
    Set<Integer> blockedCols = new HashSet<>();
    int solutionCount = 0;

    void read() {
        MyScanner sc = new MyScanner(new InputStreamReader(System.in));
        n = sc.nextInt();
        xTower = sc.nextInt();
        yTower = sc.nextInt();
    }

    void solve() {
        int[][] board = new int[n][n]; // Not strictly necessary for solution count
        board[xTower][yTower] = 2; // Mark the tower
        blockedCols.add(yTower);
        backtracking(0, board);
    }

    // String buildSolution(int[][] board) {
    //     StringBuilder sb = new StringBuilder();
    //     for (int i = 0; i < n; i++) {
    //         for (int j = 0; j < n; j++) {
    //             if (board[i][j] == 1) {
    //                 sb.append("Q");
    //             } else if (board[i][j] == 2) {
    //                 sb.append("T");
    //             } else {
    //                 sb.append("_");
    //             }
    //         }
    //         sb.append("\n");
    //     }

    //     return sb.toString();
    // }


    void backtracking(int row, int[][] board) {
        if (row == n) {
            solutionCount++;
            return;
        }

        if (row == xTower) {
            backtracking(row + 1, board);
            return;
        }

        for (int col = 0; col < n; col++) {
            if (blockedCols.contains(col) || checkDiagonal(row, col, board) || checkDiagonal2(row, col, board)) {
                continue;
            }

            board[row][col] = 1;
            blockedCols.add(col);

            backtracking(row + 1, board);

            board[row][col] = 0;
            blockedCols.remove(col);
        }
    }

    boolean checkDiagonal(int startRow, int startCol, int[][] board) {
        // upper left main diagonal
        for (int i = startRow, j = startCol; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 2) {
                break;
            }

            if (board[i][j] == 1) {
                return true;
            }
        }

        // lower right main diagonal
        for (int i = startRow, j = startCol; i < n && j < n; i++, j++) {
            if (board[i][j] == 2) {
                break;
            }

            if (board[i][j] == 1) {
                return true;
            }
        }

        return false;
    }

    boolean checkDiagonal2(int startRow, int startCol, int[][] board) {
        // upper right main diagonal
        for (int i = startRow, j = startCol; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 2) {
                break;
            }

            if (board[i][j] == 1) {
                return true;
            }
        }

        // lower left main diagonal
        for (int i = startRow, j = startCol; i < n && j >= 0; i++, j--) {
            if (board[i][j] == 2) {
                break;
            }

            if (board[i][j] == 1) {
                return true;
            }
        }

        return false;
    }




    void print() {
        System.out.println(solutionCount);
    }
}

public class GluedQueens {
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