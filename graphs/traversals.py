from collections import deque
from typing import List

MAX = 10**9
# graphs are represented as adjacency lists , node 0 is a valid node

# complexity: O(V+E)
# visits all nodes in the graph
# tested
def dfs_traversal(graph: List[List[int]]):
    visited = set()
    def dfs(node):
        visited.add(node)
        # start[node] = time++

        for neighbor in graph[node]:
            if neighbor not in visited:
                # parent[neighbor] = node
                dfs(neighbor)
        #end[node] = time++

    for node in range(len(graph)):
        if node not in visited:
            dfs(node)

# complexity: O(V+E)
# returns the shortest distances from source to all nodes
# tested
def bfs(source: int, graph: List[List[int]]) -> List[int]: 
    dist = [MAX] * len(graph)
    q = deque()

    dist[source] = 0  # Distance to the source itself is 0
    q.append(source)

    while q:
        node = q.popleft()

        for neighbor in graph[node]:
            # If the neighbor's current distance is infinity, it hasn't been visited
           if dist[node] + 1 < dist[neighbor]:
                dist[neighbor] = dist[node] + 1
                q.append(neighbor)

    return dist

                
    