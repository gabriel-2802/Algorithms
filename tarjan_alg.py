from typing import List
from graphs_alg import scc_kosaraju


# tested
def scc_tarjan(graph: List[List[int]]) -> List[List[int]]:
    n = len(graph) + 1

    # Initialize variables
    timestamp = 0
    visited = [False] * n  # Visited nodes (not using index 0)
    low = [0] * n  # Low link value of each node (not using index 0)
    discover_t = [-1] * n  # Discovery time of each node (not using index 0)

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

        for neighbor in graph[node - 1]:
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









# one component
graph = [
   [2],
   [3],
   [1]
]

# one component
graph2 = [
    [2],
    [3],
    [1, 4],
    [5],
    [6],
    [4, 1]
]

# 3 components
graph3 = [
    [2],
    [1, 3],
    [4],
    [4,3],
    [4,5]
]

print(scc_tarjan(graph))
#print(scc_kosaraju(graph))


print(scc_tarjan(graph2))
#print(scc_kosaraju(graph2))

print(scc_tarjan(graph3))
#print(scc_kosaraju(graph3))

    
