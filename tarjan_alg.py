from typing import List
from typing import Set
from typing import Tuple
from graphs_alg import scc_kosaraju


# tested
# used for directed graphs
def scc_tarjan(graph: List[List[int]]) -> List[List[int]]:
    n = len(graph)

    # Initialize variables
    timestamp = 0
    visited = [False] * (n)  # Visited nodes (not using index 0)
    low = [0] * (n)  # Low link value of each node (not using index 0)
    discover_t = [-1] * (n)  # Discovery time of each node (not using index 0)

    # stack and set to keep track of nodes in the current 
    stackNodes = []
    onStack = set()
    all_scc = []

    def dfs(node):
        nonlocal timestamp
        timestamp += 1
        discover_t[node] = low[node] = timestamp

        stackNodes.append(node)
        onStack.add(node)

        visited[node] = True

        for neighbor in graph[node]:
            if not visited[neighbor]:
                dfs(neighbor)
                low[node] = min(low[node], low[neighbor])
            elif neighbor in onStack:
                low[node] = min(low[node], discover_t[neighbor])

        # Tarjan's check to find SCC
        if low[node] == discover_t[node]:
            scc = []
            while True:
                top = stackNodes.pop()
                onStack.remove(top)
                scc.append(top)
                if top == node:
                    break
            all_scc.append(scc)

    for node in range(1, n):
        if not visited[node]:
            dfs(node)

    return all_scc

def critical_vertexes_tarjan(graph: List[List[int]]) -> Set[int]:
    n = len(graph)

    # Initialize variables
    timestamp = 0
    visited = [False] * (n)
    discover_t = [-1] * (n)
    low = [0] * (n)
    parent = [-1] * (n) # addition to Tarjan's algorithm
    critical_vertexes = set()

    def dfs(node):
        children = 0 # children of the current node
        visited[node] = True

        nonlocal timestamp
        timestamp += 1
        discover_t[node] = low[node] = timestamp

        for neighbor in graph[node]:
            if not visited[neighbor]:
                children += 1
                parent[neighbor] = node
                dfs(neighbor)

                # check if the subtree rooted at neighbor has a back edge to an ancestor of node
                low[neighbor] = min(low[neighbor], low[node])

                # node is CV if it s root and has more than one child
                if parent[node] == -1 and children > 1:
                    critical_vertexes.add(node)

                # node is CV if it is not root and has a child that has a back edge to an ancestor of node
                if parent[node] != -1 and low[neighbor] >= discover_t[node]:
                    critical_vertexes.add(node)

            elif neighbor != parent[node]:
                low[node] = min(low[node], discover_t[neighbor])


    for i in range(1, n):
        if not visited[i]:
            dfs(i)

    return critical_vertexes
    
def critical_edges_tarjan(graph: List[List[int]]) -> Set[Tuple[int, int]]:
    n = len(graph)

    # Initialize variables
    visited = [False] * (n)
    discover_t = [-1] * (n)
    parent = [-1] * (n)
    low = [0] * (n)
    timestamp = 0

    critical_edges = set()

    def dfs(node):
        nonlocal timestamp
        timestamp += 1
        visited[node] = True
        discover_t[node] = low[node] = timestamp


        for neighbor in graph[node]:
            if not visited[neighbor]:
                parent[neighbor] = node
                dfs(neighbor)
                low[node] = min(low[node], low[neighbor])

                if low[neighbor] > discover_t[node]:
                    critical_edges.add((node, neighbor))
            elif neighbor != parent[node]:
                low[node] = min(low[node], discover_t[neighbor])

    
    for i in range(1, n):
        if not visited[i]:
            dfs(i)
    
    return critical_edges
    

# one component
graph = [
    [],
   [2],
   [3],
   [1]
]

# one component
graph2 = [
    [],
    [2],
    [3],
    [1, 4],
    [5],
    [6],
    [4, 1]
]

# 3 components
graph3 = [
    [],
    [2],
    [1, 3],
    [4],
    [4,3],
    [4,5]
]

# print(scc_tarjan(graph))
# print(scc_kosaraju(graph))


# print(scc_tarjan(graph2))
# print(scc_kosaraju(graph2))

# print(scc_tarjan(graph3))
# print(scc_kosaraju(graph3))

    