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
	# The dimensions of the dp array is the same as the input array
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


def test():
	pass


def main():
	test()

if __name__ == "__main__":
	main()