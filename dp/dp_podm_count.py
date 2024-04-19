# This file contains dp implementation for problems related to Optimal Matrix Parenthesis or counting category

from typing import *
from numbers import Number
import heapq
import collections

INF = 10 ** 20

"""
PODM category
-------------
Characteristics:
	--> We can formulate this type of problem as a subinterval problem [i,j].
	--> To find the optimum for this interval, we need to consider all
			combinations of 2 subproblems that could generate a solution for the problems [i,j].
	--> Each division into 2 subproblems, given by the intermediary k, is considered.
	--> If [i,k] and [k+1,j] are the 2 subproblems for which we know the solutions, then
	  		a solution for [i,j] can be obtained by combining the two.
	--> To find the best solution, we will iterate through all possible k values and choose
	  		the one that maximizes the solution to the problem [i,j].
	--> The calculation is done from small intervals (easy problems - [i,i] or [i,i+1]) towards
	 		general problems (general size - [i,j]). In the end, we also reach the initial dimensions ([1,n]).
	--> Looking at the big picture, i.e., how the dp matrix is filled, we notice that it is filled diagonally.
"""


"""
Description: Given a list of matrix dimensions, find the optimal way to multiply them.
ex for list : [2, 3, 4, 5], we have 3 matrices with dimensions A(2x3), B(3x4), C(4x5).

--- dp[i][j] = minimum number of multiplications needed to multiply matrices from i to j
--- answer is found in dp[1][n]

--- This solution is tested and 100% correct
"""
def matrix_mult_order(arr: List[int]) -> int:
	n = len(arr) - 1
	# create the dp matrix
	dp = [[INF for _ in range(n + 1)] for _ in range(n + 1)]

	# Base case 1: if we have only 1 matrix, we don't need any multiplication
	for i in range(1, n + 1):
		dp[i][i] = 0

	# Base case 2: if we have 2 matrices, we need to multiply them
	for i in range(1, n):
		dp[i][i + 1] = arr[i - 1] * arr[i] * arr[i + 1]

	# Iterate over the lengths of subintervals
	for length in range(2, n + 1):
		# Iterate over the starting indices of subintervals
		for i in range(1, n - length + 2):
			# Calculate the ending index of the subinterval
			j = i + length - 1
			# Iterate over the possible division points within the subinterval
			for k in range(i, j):
				# General case: dp[i][j] = min(dp[i][k] + dp[k + 1][j] + d[i - 1] * d[k] * d[j]), k = i : j - 1
				new_sol = dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j]
				# Update the minimum number of multiplications needed for the subinterval
				dp[i][j] = min(dp[i][j], new_sol)

	return dp[1][n]






def main():
	arr = [13, 5, 89, 3, 34]
	print(matrix_mult_order(arr))


if __name__ == "__main__":
	main()