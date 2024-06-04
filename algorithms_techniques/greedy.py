from typing import *
from numbers import Number
import heapq
import collections


# Tested
def max_sum_substring(arr: List[int]) -> int:
	sum = 0
	for elem in arr:
		if elem > 0:
			sum += elem

	if sum == 0:
		return max(arr)
	return sum


# Tested
def shows(intervals: List[Tuple[int, int]]) -> List[Tuple[int, int]]:
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
def florist(num_persons: int, costs: List[int]) -> int:
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
def plank_nails(planks: List[Tuple[int, int]]) -> List[int]:
	nails = []
	planks.sort(key = lambda x: x[0])
	last =  - 10**9

	def point_in_interval(point: int, interval: Tuple[int, int]) -> bool:
		return interval[0] <= point <= interval[1]

	for plank in planks:
		if not point_in_interval(last, plank):
			nails.append(plank[1])
			last = plank[1]
	return nails


# Tested
def backpack(capacity: int, items: List[Tuple[int, int]]) -> float:
	# An item is a pair (value, weight)
	# Sort the items by the value per weight
	items.sort(key = lambda x: x[0] / x[1], reverse = True)

	total = 0
	for item in items:
		if capacity >= item[1]:
			total += item[0]
			capacity -= item[1]
		else:
			total += item[0] * (capacity / item[1])
			break
	return total


# Tested
def distances_between_cities(car_capacity: int, num_gas_stations: int, distances: List[int]) -> int:
	# Return the minimum number of stops to reach the destination
	# from the source
	stops = 0
	curr_capacity = car_capacity
	for i in range(num_gas_stations):
		if distances[i] > curr_capacity:
			if i == 0 or distances[i] - distances[i - 1] > car_capacity:
				return -1

			curr_capacity = distances[i - 1] + car_capacity
			stops += 1
	return stops


# Tested
def homeworks_ACS(homeworks: List[Tuple[int, int]]) -> int:
    # A homework is a pair (deadline, score)
    # Sort the homeworks by the deadline in decreasing order
    sorted_homeworks = sorted(homeworks, key=lambda x: x[0], reverse=True)
    heap = []
    total = 0
    i = 0
    max_ddl = sorted_homeworks[0][0]

    for ddl in range(max_ddl, 0, -1):
        # Add the homeworks with the same deadline
        while i < len(sorted_homeworks) and sorted_homeworks[i][0] == ddl:
            heapq.heappush(heap, -sorted_homeworks[i][1])
            i += 1

        # Choose the homework with the maximum score
        if heap:
            total -= heapq.heappop(heap)  # Subtracting because we pushed negative scores

    return total
