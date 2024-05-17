from typing import List
from typing import List, Deque
from collections import deque

MAX=10**9
'''
    TESTED
    Complexity: O(V^2 * E)
    Finds the maximum flow in a graph
    @params: capacity_graph - Capacity Matrix of the graph(0 indexed), source - source vertex, target - target vertex
    @return: int - Maximum flow from source to target
'''

def pre_flow_alg(capacity_graph: List[List[int]], source: int, target: int) -> int:
    # push flow from u to v
    def init():
        height[source] = n
        excess[source] = MAX
        for i in range(n):
            if i != source:
                push(source, i)

    # push flow from u to v
    def push(u: int, v: int):
        d = min(excess[u], capacity_graph[u][v] - flow[u][v])
        flow[u][v] += d
        flow[v][u] -= d
        excess[u] -= d
        excess[v] += d
        if d > 0 and excess[v] == d:
            excess_vertices.append(v)

    # relabel node u to a higher height so that it can push flow
    def relabel(u: int):
        min_height = MAX

        # find the minimum height of the neighbors of u that have available capacity to push flow
        for i in range(n):
            if capacity_graph[u][i] - flow[u][i] > 0:
                min_height = min(min_height, height[i])

        if min_height < MAX:
            height[u] = min_height + 1


    def discharge(u: int):
        # while there is excess flow at u
        while excess[u] > 0:
            # there can be maximum n pushes from u
            if seen[u] < n:
                v = seen[u]
                if capacity_graph[u][v] - flow[u][v] > 0 and height[u] > height[v]:
                    push(u, v)
                seen[u] += 1
            else:
                relabel(u)
                seen[u] = 0

    n = len(capacity_graph)
    height = [0] * n                       # height[u] = height of node u
    flow = [[0] * n for _ in range(n)]     # flow[u][v] = flow from u to v
    excess = [0] * n                       # excess[u] = excess flow at node u
    seen = [0] * n                         # seen[u] = number of neighbors of u that have been examined
    excess_vertices = deque()             # excess_vertices = queue of vertices with excess flow

    # Initialize preflow
    init()

    # while there are vertices with excess flow i.e. there are possible pushes and relabels
    while excess_vertices:
        u = excess_vertices.popleft()

        # Discharge u i.e. push flow from u to its neighbors
        if u != source and u != target:
            discharge(u)

    # Calculate maximum flow as all the flows that enter the target
    max_flow = sum(flow[u][target] for u in range(n))
    return max_flow

