from typing import *
from numbers import Number

# tested
def permutations(n: int) -> List[List[int]]:
    solutions = []

    def backtracking(current_permutation: List[int]):
        if len(current_permutation) == n:
            solutions.append(current_permutation.copy())  # Append a copy of the list
            return

        for i in range(1, n+1):
            if i not in current_permutation:
                current_permutation.append(i)
                backtracking(current_permutation)
                current_permutation.pop()

    backtracking([])
    return solutions
	

# tested
def combinations(n : int, k : int) -> List[List[int]]:
	solutions = []
      
	def backtracking(current_combination: List[int], start: int):
		if len(current_combination) == k:
			solutions.append(current_combination.copy())
			return

		for i in range(start, n+1):
			current_combination.append(i)
			backtracking(current_combination, i + 1)
			current_combination.pop()

	backtracking([], 1)
	return solutions
    
from typing import List


# tested
def arrangements(n: int, k: int) -> List[List[int]]:
    solutions = []
    used = [False] * (n + 1)  # Tracking usage of elements
    
    def backtracking(current_arrangement: List[int]):
        if len(current_arrangement) == k:
            solutions.append(current_arrangement.copy())
            return
        
        for i in range(1, n+1):
            if not used[i]:
                current_arrangement.append(i)
                # Mark the element as used
                used[i] = True
                backtracking(current_arrangement)
                used[i] = False
                current_arrangement.pop()

    backtracking([])
    return solutions

def subsets(nums: List[int]) -> List[List[int]]:
	solutions = []
	
	def backtracking(start: int, current_subset: List[int]):
		solutions.append(current_subset.copy())
		
		for i in range(start, len(nums)):
			current_subset.append(nums[i])
			backtracking(i + 1, current_subset)
			current_subset.pop()
	
	backtracking(0, [])
	return solutions


# to be tested
def n_queens(n : int) -> List[Dict[int, int]]:
	solutions = []
    
	# row -> the row we are currently placing a queen in
	# columns -> the columns that are already occupied
	# diagonal1 -> the diagonals that are already occupied
	# diagonal2 -> the anti-diagonals that are already occupied
	# current_solution -> a dict as a mapping from row to column
	def backtracking(row : int, columns : Set[int], diagonal1 : Set[int], diagonal2 : Set[int], current_solution : Dict[int, int]):
		if row == n:
			solutions.append(current_solution.copy())
			return
            
		for col in range(n):
			diag = row - col
			diag2 = row + col

			if col not in columns and diag not in diagonal1 and diag2 not in diagonal2:
				current_solution[row] = col
				columns.add(col)
				diagonal1.add(diag)
				diagonal2.add(diag2)
				backtracking(row + 1, columns, diagonal1, diagonal2, current_solution)
				columns.remove(col)
				diagonal1.remove(diag)
				diagonal2.remove(diag2)
				del current_solution[row] # Remove the queen from the current row
		
		backtracking(0, set(), set(), set(), {})
		return solutions

      



"""
	# general algorithm for backtracking
    def backtrack(domain, partial_solution):
		if partial_solution is complete:
			solutions.append(partial_solution)
			return
		
		for candidate in domain:
			if candidate is valid:
				partial_solution.append(candidate)
				backtrack(domain, partial_solution)
				partial_solution.pop()

"""
