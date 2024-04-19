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


"""
Counting category
-----------------
Characteristics:
	--> Recurrences have a common similarity: they all count things.
	--> Cases where the number sought is very large are interesting. In this case,
	  		the remainder of the division of the number sought by a number MOD is required.
	--> When looking for a recurrence for a counting problem, 
			you need to be careful about two aspects:
				1. Do not count the same object twice.
				2. Count all objects in question.
	--> A counting problem often involves partitioning all possible solutions according
	  		to a certain criterion. Finding the criterion is the essential part for finding the recurrence.
	--> There are rules for working with residue classes and mathematical properties that you
	 		should keep in mind when implementing to correctly obtain the remainders of certain expressions.
"""


"""
--- A piece dimension is 4 x 1. It can be placed horizontally or vertically.
	Every fence built has to be of height 4.
--- How many fences of length n and height 4 exist?

--- Ex: n <= 3 -> 0, n == 4 -> 2.

--- Tested and 100% correct
"""
def gigel_fence(n: int) -> int:
	MOD = 1009

	if n <= 3:
		return 1
	if n == 4:
		return 2

	dp = [0] * (n + 1)
	# dp[i] -> number of fences of length i and height 4
	dp[1] = dp[2] = dp[3] = 1
	dp[4] = 2

	# Iterate over the lengths of fences
	for i in range(5, n + 1):
		# Calculate the number of fences of length i and height 4
		dp[i] = (dp[i - 1] + dp[i - 4]) % MOD

	return dp[n]


"""
--- Tested and 100% correct
"""
def number_of_subsequences_of_even_sum(arr: List[int]) -> int:
	MOD = 1000000007
	n = len(arr)

	# Number of subsequences with even sum using the first i elements and ending with the i-th element
	dp_even = [0] * (n + 1)
	# Same as above, but for odd sum
	dp_odd = [0] * (n + 1)

	# Partial sums
	sum_even = 0 # dp_even[1] + dp_even[2] + ... + dp_even[i]
	sum_odd = 0 # dp_odd[1] + dp_odd[2] + ... + dp_odd[i]

	# Iterate over the elements of the array
	for i in range(1, n + 1):
		# If the i-th element is even
		if arr[i - 1] % 2 == 0:
			# arr[i] alone
			dp_even[i] = 1
			# arr[i] alone is an odd number so we don't have any subsequences with odd sum
			dp_odd[i] = 0

			# If we add arr[i] to a subsequence with even sum, the sum remains even
			# If we add arr[i] to a subsequence with odd sum, the sum remains odd
			dp_even[i] = (dp_even[i] + sum_even) % MOD
			dp_odd[i] = (dp_odd[i] + sum_odd) % MOD
		else:
			dp_even[i] = 0 # arr[i] cannot be alone
			dp_odd[i] = 1 # arr[i] alone

			# If we add arr[i] to a subsequence with even sum, the sum becomes odd
			# If we add arr[i] to a subsequence with odd sum, the sum becomes even
			dp_even[i] = (dp_even[i] + sum_odd) % MOD
			dp_odd[i] = (dp_odd[i] + sum_even) % MOD

		# Recalculate the partial sums
		sum_even = (sum_even + dp_even[i]) % MOD
		sum_odd = (sum_odd + dp_odd[i]) % MOD

	# Return the number of subsequences with even sum
	return sum_even
