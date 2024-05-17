from typing import *
from numbers import Number
import heapq
import collections
from dijkstra_and_bellman_ford import bellman_ford, dijkstra, MAX


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
				if dist[i][j] > dist[i][k] + dist[k][j]:
					dist[i][j] = dist[i][k] + dist[k][j]
					parent[i][j] = parent[k][j]

	# Set 0 to INF distances
	for i in range(n):
		for j in range(n):
			if dist[i][j] == INF:
				dist[i][j] = 0

	return dist, parent


"""
	*Tested*

	--> Calculates the shortest path between all pairs of nodes in a graph
	--> It is recommended to use this algorithm when the graph has few edges
	--> Can detect negative cycles by using bellman_ford algorithm

	@Complexity: O(V^2 log V + VE)
	@params:
		adj: adj[i] will contain an array of pairs (node, weight) representing
			the fact that there is an edge from i to node with cost weight
	@return:
		a tuple (bool, dist, parent) where:
			- bool is True if there is no negative cycle, False otherwise
			- dist contains the shortest distances between nodes
			- parent contains the parent of each node in the shortest path
"""
def johnson(adj: List[List[Tuple[int, int]]]) -> Tuple[bool, List[List[int]], List[List[int]]]:
	n = len(adj) # 1 based indexing (node 0 is not used)
	new_graph = adj + [[]]  # Adding a new node as the last node

	# Add a new dummy node and connect it to all other nodes with weight 0
	for i in range(1, n + 1):
		new_graph[-1].append((i, 0))

	try:
		# Bellman-Ford from the dummy node
		[d_bellman_ford, _] = bellman_ford(new_graph, n)
		
		# Reweight the edges
		reweighted_graph = [[] for _ in range(n + 1)]
		for u in range(n + 1):
			for v, weight in new_graph[u]:
				new_weight = weight + d_bellman_ford[u] - d_bellman_ford[v]
				reweighted_graph[u].append((v, new_weight))
		
		# Initialize distance and parent matrices
		d = [[0 if i == j else MAX for j in range(n + 1)] for i in range(n + 1)]
		p = [[-1 for _ in range(n + 1)] for _ in range(n + 1)]
		
		# Run Dijkstra for each node
		for i in range(1, n + 1):
			dijkstra_dist, dijkstra_parent = dijkstra(reweighted_graph, i)
			for j in range(1, n + 1):
				if dijkstra_dist[j] < MAX:
					d[i][j] = dijkstra_dist[j] - d_bellman_ford[i] + d_bellman_ford[j]
					p[i][j] = dijkstra_parent[j]
		
		# Remove the dummy node from the results (node n)
		d.pop()
		for i in range(n):
			d[i].pop()
		p.pop()
		for i in range(n):
			p[i].pop()
		
		return False, d, p
	
	except ValueError:
		# Negative cycle detected
		return True, [], []

