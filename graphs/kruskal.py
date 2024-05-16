from typing import *
from collections import defaultdict

"""
"""
class DisjointSet:
	def __init__(self, n: int):
		self.parent = list(range(n + 1))
		self.size = [1] * (n + 1)
	
	def setOf(self, u: int) -> int:
		if self.parent[u] == u:
			return u
		
		self.parent[u] = self.setOf(self.parent[u])
		return self.parent[u]
	
	def union(self, u: int, v: int):
		rx = self.setOf(u)
		ry = self.setOf(v)

		if self.size[rx] <= self.size[ry]:
			self.size[ry] += self.size[rx]
			self.parent[rx] = ry
		else:
			self.size[rx] += self.size[ry]
			self.parent[ry] = rx


"""
"""
class Edge:
	def __init__(self, node: int, neigh: int, w: int):
		self.node = node
		self.neigh = neigh
		self.w = w


"""
"""
def kruskal(n: int, edges: List[Edge]) -> Tuple[int, List[Tuple[int, int]]]:
	edges.sort(key=lambda e: e.w)
	cost = 0
	mst = []

	ds = DisjointSet(n)

	for edge in edges:
		if ds.setOf(edge.node) != ds.setOf(edge.neigh):
			cost += edge.w
			mst.append((edge.node, edge.neigh))
			ds.union(edge.node, edge.neigh)
	
	return cost, mst


# Tested
def main():
	n = 5
	edges = [
		Edge(1, 3, -3),
		Edge(1, 5, 7),
		Edge(3, 2, -2),
		Edge(3, 4, 7),
		Edge(5, 1, 4),
		Edge(5, 2, 3),
		Edge(5, 3, 4),
		Edge(4, 5, 3)
	]

	cost, mst = kruskal(n, edges)
	print(cost, mst)
	# assert cost == 1


if __name__ == "__main__":
	main()
	