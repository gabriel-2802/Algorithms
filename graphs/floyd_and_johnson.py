from typing import *
from numbers import Number
import heapq
import collections
from graphs.minimum_paths_one_to_many import bellman_ford, dijkstra, MAX


INF = 10 ** 20
NULL_PARENT = 0

"""
	*Tested*

	--> Calculates the shortest path between all pairs of nodes in a graph
	--> Recommended for dense (many edges) graphs
	--> Cannot be used for graphs with negative cycles
	@Complexity: O(V^3)

	@params:
		n: number of nodes
		w: w[i][j] will contain the weight of the edge from i to j
	@return:
		a tuple (dist, parent) where:
			- dist contains the shortest distances between nodes
			- parent contains the parent of each node in the shortest path
"""
def roy_floyd(n: int, w: List[List[int]]) -> Tuple[List[List[int]], List[List[int]]]:
	# Initializations
	dist = [[INF for _ in range(n)] for _ in range(n)]
	parent = [[NULL_PARENT for _ in range(n)] for _ in range(n)]

	for i in range(n):
		for j in range(n):
			if i == j:
				dist[i][j] = 0
			elif w[i][j] == 0:
				dist[i][j] = INF
			elif w[i][j] != 0:
				dist[i][j] = w[i][j]
				parent[i][j] = i

	# Roy-Floyd algorithm
	for k in range(n):
		for i in range(n):
			for j in range(n):
				if dist[i][k] == INF or dist[k][j] == INF:
					continue
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

	# Set 0 to INF distances
	for i in range(n):
		for j in range(n):
			if dist[i][j] == INF:
				dist[i][j] = 0

	return dist, parent


"""
	*NOT Tested*

	--> Calculates the shortest path between all pairs of nodes in a graph
	--> It is recommended to use this algorithm when the graph has few edges
	--> Can detect negative cycles by using bellman_ford algorithm

	@Complexity: O(V^2 log V + VE)
	@params:
		n: number of nodes
		m: number of edges
		adj: adj[i] will contain an array of pairs (node, weight) representing
			the fact that there is an edge from i to node with cost weight
	@return:
		a tuple (bool, dist, parent) where:
			- bool is True if there is no negative cycle, False otherwise
			- dist contains the shortest distances between nodes
			- parent contains the parent of each node in the shortest path
"""
def johnson(n: int, m: int, adj: List[List[Tuple[int, int]]]) -> Tuple[bool, List[List[int]], List[List[int]]]:
	d = [[0] * (n + 1) for _ in range(n + 1)]
	p = [[0] * (n + 1) for _ in range(n + 1)]
	edges = []
	source_node = 0

	for i in range(n):
		edges.append((source_node, i, 0))

	for i in range(n):
		for neigh in adj[i]:
			edges.append((i, neigh[0], neigh[1]))

	# Bellman-Ford
	(neg_cycle, [d_bellman_ford, p_bellman_ford]) = bellman_ford(edges, source_node)
	if neg_cycle:
		return True, [], []

	for i in range(n):
		for neigh in adj[i]:
			neigh_weight = neigh[1] - d_bellman_ford[i] + d_bellman_ford[neigh[0]]
			edges.append((i, neigh[0], neigh_weight))

	# Dijkstra
	for i in range(n):
		[d_dijkstra, p_dijkstra] = dijkstra(adj, i)
		for j in range(n):
			if d_dijkstra[j] == MAX:
				d[i][j] = 0
				continue
			d[i][j] = d_dijkstra[j]
			p[i][j] = p_dijkstra[j]

	for i in range(n):
		for j in range(n):
			d[i][j] += d_bellman_ford[j] - d_bellman_ford[i]

	return False, d, p
