from typing import *
from numbers import Number


# Tested
def max_sum_substring(arr: List[Number]) -> Number:
	sum = 0
	for elem in arr:
		if elem > 0:
			sum += elem

	if sum == 0:
		return max(arr)
	return sum


# Tested
def shows(intervals: List[Tuple[Number, Number]]) -> List[Tuple[Number, Number]]:
	# Sort the intervals by the end time
	intervals.sort(key = lambda x: x[1])

	# A list of tuples
	plan = []
	last = float('-inf')
	for interval in intervals:
		if interval[0] >= last:
			plan.append(interval)
			last = interval[1]
	return plan


# Tested
def florist(num_persons: int, costs: List[Number]) -> Number:
	# Sorted in decreasing order of cost
	sorted_costs = sorted(costs, reverse = True)
	total = 0

	# The ith flower bought by a person
	nr_flowers_at_time = 1

	for i in range(len(sorted_costs)):
		person_idx = i % num_persons
		total += sorted_costs[i] * nr_flowers_at_time
		if person_idx == num_persons - 1:
			nr_flowers_at_time += 1
	return total


# Tested
def plank_nails(planks: List[Tuple[Number, Number]]) -> List[Number]:
	nails = []
	planks.sort(key = lambda x: x[1])
	last = float('-inf')

	def point_in_interval(point: Number, interval: Tuple[Number, Number]) -> bool:
		return interval[0] <= point <= interval[1]

	for plank in planks:
		if not point_in_interval(last, plank):
			nails.append(plank[1])
			last = plank[1]
	return nails


def backpack(capacity: Number, items: List[Tuple[Number, Number]]) -> Number:
	pass	


if __name__ == "__main__":
	main()
