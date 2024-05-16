from typing import *
from collections import deque
INF = 10**9

'''
    Complexity: O(V + E)
    @params: graph - Capacity Matrtix of the graph(1 indexed), source - source vertex, target - target vertex, parent - parent array to store the path
    @return: bool - True if there is a path from source to target, False otherwise

'''
def ff_bfs(graph: List[List[int]], source: int, target: int, parent: List[int]) -> bool:
    n = len(graph)
    visited = [False] * n
    queue = deque()

    queue.append(source)
    visited[source] = True

    while queue:
        current = queue.popleft()

        for neighbor in range(1,n):
            # Check if the neighbor has not been visited and there's available capacity
            if not visited[neighbor] and graph[current][neighbor] > 0:
                queue.append(neighbor)
                visited[neighbor] = True
                parent[neighbor] = current

                # If we reach the target node, we have found a path
                if neighbor == target:
                    return True

    return False

'''
    Complexity: O(V * E * E)
    IT ALTERS THE GRAPH!!!
    Also known as Edmonds-Karp Algorithm
    @params: graph - Capacity Matrtix of the graph(1 indexed), source - source vertex, target - target vertex
    @return: int - Maximum flow from source to target
'''
def ford_fulkerson(graph:List[List[int]], source:int, target:int) -> int:
    n = len(graph)
    # initialize parent array
    parent = [-1] * n
    max_flow = 0

    # while there is a path from source to target
    while ff_bfs(graph, source, target, parent):
        path_flow = INF

        # find the minimum capacity in the path
        node = target
        while node != source:
            node_parent =  parent[node]
            path_flow = min(path_flow, graph[node_parent][node])
            node = node_parent

        # add path flow to overall flow
        max_flow += path_flow

        # update the residual capacities of the edges and reverse edges along the path
        node = target
        while node != source:
            node_parent = parent[node]
            graph[node_parent][node] -= path_flow
            graph[node][node_parent] += path_flow
            node = node_parent

    return max_flow
