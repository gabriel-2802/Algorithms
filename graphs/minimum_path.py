import heapq
from typing import List
from typing import Tuple

MAX = 10**9


"""
	For particular graphs, a more efficient algorithm can be used to find the shortest path between nodes.
	ex: topological sort for DAGs
	For general graphs, we can use Dijkstra's algorithm or Bellman-Ford algorithm.
	Dijkstra's algorithm is more efficient than Bellman-Ford algorithm for graphs with non-negative weights.
	Bellman-Ford algorithm can be used for graphs with negative weights.
	Bellman-Ford algorithm (original and optimised1) can detect negative cycles in the graph.
	Bellman-Ford algorithm (optimised2) does not detect negative cycles, however, it is more efficient than the original algorithm (and optimised1).
"""

# tested
# returns the distance vector and the parent vector
# graph[i] = [(neighbor, weight)]
# ONLY WORKS FOR NON-NEGATIVE WEIGHTS
def dijkstra(graph: List[List[Tuple]], source: int) -> List[List[int]]:
	n = len(graph)

	# initialize
	parent = [-1] * n
	distance = [MAX] * n
	visited = [False] * n
	
	# distance to source is 0 and parent is -1 by convention
	distance[source] = 0
	parent[source] = -1

	# Min-heap of pairs (distance, node) : key is distance
	min_heap = []
	heapq.heappush(min_heap, (0, source))

	while min_heap:
		dist_to_node, node = heapq.heappop(min_heap)
		
		# only proceed if we pop the smallest distance for `node` seen so far
		# this ensures that we don't relax the edges of a node more than once
		if visited[node]:
			continue
		visited[node] = True

		# Relax the edges
		for neighbor, weight in graph[node]:
			if dist_to_node + weight < distance[neighbor]:

				distance[neighbor] = dist_to_node + weight
				parent[neighbor] = node

				# since we relaxed the edge, we need to update the min_heap
				heapq.heappush(min_heap, (distance[neighbor], neighbor))

	# ignore node 0 since its 1 indexed
	return [distance, parent]


# tested
# returns the distance vector and the parent vector for all nodes from source
# throws an error if the graph contains a negative cycle
def bellman_ford(graph: List[List[Tuple]], source: int) -> Tuple[bool, List[List[int]]]:
	n = len(graph)

	# initialize
	parent = [-1] * n
	distance = [MAX] * n

	# distance to source is 0 and parent is -1 by convention
	distance[source] = 0
	parent[source] = -1

	# Relax the edges n-1 times
	for _ in range(n - 1):
		# for all edges (u, v) with weight w we relax the edge
		for node in range(1, n):
			for neighbor, weight in graph[node]:
				# check is relaxing the edge will give a shorter path
				if distance[node] + weight < distance[neighbor]:
					distance[neighbor] = distance[node] + weight
					parent[neighbor] = node

	# check for negative cycles by attempting to relax the edges one more time
	for node in range(1, n):
		for neighbor, weight in graph[node]:
			if distance[node] + weight < distance[neighbor]:
				return [True, [distance, parent]]
	
	for i in range(1, n):
		if distance[i] == MAX:
			distance[i] = -1

	return [False, [distance, parent]]

# tested
# returns the distance vector and the parent vector for all nodes from source
# throws an error if the graph contains a negative cycle
def bellman_ford_optimised(graph: List[List[Tuple]], source: int) -> List[List[int]]:
	n = len(graph)

	# initialize
	parent = [-1] * n
	distance = [MAX] * n

	# distance to source is 0 and parent is -1 by convention
	distance[source] = 0
	parent[source] = -1

	# keep track of the nodes that have been updated in the last iteration
	updated_nodes = set([source])

	# Relax the edges n-1 times
	for _ in range(n - 1):
		new_updated_nodes = set()

		# for edges(u,v) with u in updated_nodes we relax the edge
		# if the node was not updated in the last iteration, then its children cannot be updated
		for node in updated_nodes:
			for neighbor, weight in graph[node]:
				# check is relaxing the edge will give a shorter path
				if distance[node] + weight < distance[neighbor]:
					distance[neighbor] = distance[node] + weight
					parent[neighbor] = node
					new_updated_nodes.add(neighbor)
		
		# if no nodes were updated in the last iteration, then we can break
		if not new_updated_nodes:
			break
		# update the updated_nodes set
		updated_nodes = new_updated_nodes

	# check for negative cycles by attempting to relax the edges one more time
	for node in range(1, n):
		for neighbor, weight in graph[node]:
			if distance[node] + weight < distance[neighbor]:
				ValueError("Graph contains a negative cycle")

	return [distance, parent]

# tested
# no longer detects negative cycles
# works for graphs with negative weights
# similar to Dijkstra's algorithm
def bellman_ford_optimised2(graph: List[List[Tuple]], source: int) -> List[List[int]]:
	n = len(graph)

	# initialize
	distance = [MAX] * n
	parent = [-1] * n

	# mark all nodes which were relaxed
	marked = [False] * n
	# heap of pairs (distance, node) : key is distance
	min_heap = []

	# distance to source is 0 and parent is -1 by convention
	distance[source] = 0
	parent[source] = -1
	marked[source] = True
	heapq.heappush(min_heap, (0, source))

	while min_heap:
		dist_to_node, node = heapq.heappop(min_heap)
		marked[node] = False

		# try to relax the edges for all neighbors of node
		for neighbor, weight in graph[node]:
			if  dist_to_node + weight < distance[neighbor]:
				distance[neighbor] = dist_to_node + weight
				parent[neighbor] = node

				# key for optimisation: only push to heap if the node was not relaxed in the last iteration
				if not marked[neighbor]:
					marked[neighbor] = True
					heapq.heappush(min_heap, (distance[neighbor], neighbor))

	
	return [distance, parent]
