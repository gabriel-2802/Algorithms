# This file contains dp implementation for problems related to backpack or SSM category

from typing import *
from numbers import Number
import heapq
import collections

"""
Steps to solve a dp problem:
	1. Determine the dimensions of the dp array
	2. Establish the dynamic significance
	3. Initialize the dp array
	4. Determine the recurrence relation
	5. Find solution
	6. Reconstitute the solution (OPTIONAL)
"""

"""
Some notes:
	substring = contiguous subsequence. Ex: [1, 2, 3] is a substring of [1, 2, 3, 4]
	subsequence = not necessarily contiguous. Ex: [1, 3] is a subsequence of [1, 2, 3, 4]
"""


# Tested
# Ex for arr = [-10, 2, 3, -1, 2, -3], ans = 6 (elements 2, 3, -1, 2)
def max_substring_sum(arr: List[int]) -> int:
	# The dimension of the dp array is the same as the input array
	dp = [0] * len(arr)
	# Base case
	dp[0] = arr[0]
	for i in range(1, len(arr)):
		# If the previous sum is positive, then add the current element to it
		if dp[i - 1] >= 0:
			dp[i] = dp[i - 1] + arr[i]
		# Else, start a new sum
		else:
			dp[i] = arr[i]
	return max(dp)


# Tested
# arr = [100, 12, 13, -1, 15, -30], ans = 3 (elements 12, 13, 15)
def max_ascending_subsequence(arr: List[int]) -> int:
	dp = [0] * (len(arr) + 1)
	# Base case
	dp[0] = 1
	for i in range(1, len(arr)):
		# The subsequence v[i] is the maximum subsequence ending at i
		dp[i] = 1
		# Test if I can extend the subsequence ending at i
		for j in range(i):
			if arr[j] < arr[i]:
				dp[i] = max(dp[i], dp[j] + 1)
	return max(dp)


# Tested
def rebuild_max_ascending_subsequence(arr: List[int]) -> List[int]:
	dp = [0] * (len(arr) + 1)
	# Base case
	dp[0] = 1
	for i in range(1, len(arr)):
		# The subsequence v[i] is the maximum subsequence ending at i
		dp[i] = 1
		# Test if I can extend the subsequence ending at i
		for j in range(i):
			if arr[j] < arr[i]:
				dp[i] = max(dp[i], dp[j] + 1)
	# Find the maximum subsequence
	max_len = max(dp)
	# The index of the biggest element in the subsequence
	max_index = dp.index(max_len)
	# Append the biggest element to the subsequence
	subsequence = [arr[max_index]]

	# Rebuild the subsequence
	for i in range(max_index - 1, -1, -1):
		# If the current element is part of the subsequence
		if dp[i] == dp[max_index] - 1 and arr[i] < arr[max_index]:
			subsequence.append(arr[i])
			max_index = i
	return subsequence[::-1]


# Tested
# Discrete case of the backpack problem
def backpack(capacity: int, weights: List[int], prices: List[int]) -> int:
	# rows = items, cols = capacity
	dp = [[0] * (capacity + 1) for _ in range(len(weights) + 1)]
	# dp[i][cap] = maximum price I can get with items 0 to i and capacity cap

	# Base case: First row and first column are 0, because I can't take any items
	for i in range(1, 1 + len(weights)):
		for cap in range(0, capacity + 1):
			# Start with the previous solution. Or check if I can skip the current item
			dp[i][cap] = dp[i - 1][cap]
			# I check only items that have a weight less than the current capacity
			if cap - weights[i - 1] >= 0:
				# check if current item is maximizing the solution
				potentional_sol = dp[i - 1][cap - weights[i - 1]] + prices[i - 1]
				dp[i][cap] = max(dp[i][cap], potentional_sol)

	return dp[len(weights)][capacity]


# Tested
# From backpack category
def coins_target(target: int, coins: List[int]) -> int:
	dp = [float('inf') for _ in range(target + 1)]
	# Base case
	dp[0] = 0

	for i in range(1, target + 1):
		for coin in coins:
			if i - coin >= 0:
				dp[i] = min(dp[i], 1 + dp[i - coin])

	return int(dp[target]) if dp[target] != float('inf') else -1


# Tested
def longest_common_subsequence(arr1: List[int], arr2: List[int]) -> List[int]:
	# rows = arr1_len, cols = arr2_len
	dp = [[0] * (len(arr2) + 1) for _ in range(len(arr1) + 1)]
	# dp[i][j] = length of the longest common subsequence between arr1[0:i] and arr2[0:j]

	for i in range(1, len(arr1) + 1):
		for j in range(1, len(arr2) + 1):
			if arr1[i - 1] == arr2[j - 1]:
				dp[i][j] = dp[i - 1][j - 1] + 1
			else:
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

	subseq = []
	i, j = len(arr1), len(arr2)
	while i > 0 and j > 0:
		if arr1[i - 1] == arr2[j - 1]:
			subseq.append(arr1[i - 1])
			i -= 1
			j -= 1
		elif dp[i - 1][j] > dp[i][j - 1]:
			i -= 1
		else:
			j -= 1
	return subseq[::-1]

def test():
	pass


def main():
	test()

if __name__ == "__main__":
	main()