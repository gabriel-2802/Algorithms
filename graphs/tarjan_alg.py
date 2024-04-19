from typing import List
from typing import Set
from typing import Tuple
from graphs.graphs_alg import scc_kosaraju


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
        discover_t[node] = low[node] = timestamp # convention for low

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

# tested
def critical_vertexes_tarjan(graph: List[List[int]]) -> Set[int]:
    n = len(graph)  # Number of vertices in the graph including the placeholder at index 0
    timestamp = 0
    visited = [False] * n
    discover_t = [-1] * n
    low = [0] * n
    parent = [-1] * n
    critical_vertices = set()

    def dfs(node):
        nonlocal timestamp
        visited[node] = True
        discover_t[node] = low[node] = timestamp + 1
        timestamp += 1

        children = 0  # Children counter for the current node

        for neighbor in graph[node]:
            if not visited[neighbor]:
                parent[neighbor] = node
                children += 1
                dfs(neighbor)

                # Check if the subtree rooted at neighbor has connection back to one of the ancestors of node
                low[node] = min(low[node], low[neighbor])

                # (1) node is root of DFS tree and has two or more children
                if parent[node] == -1 and children > 1:
                    critical_vertices.add(node)
                
                # (2) node is not root and low value of one of its child is more than discovery value of node
                if parent[node] != -1 and low[neighbor] >= discover_t[node]:
                    critical_vertices.add(node)

            elif neighbor != parent[node]:  # Update low value of node for parent function calls.
                low[node] = min(low[node], discover_t[neighbor])

    # Start from 1 as the first index, since 0 is a placeholder
    for i in range(1, n):
        if not visited[i]:
            dfs(i)

    return critical_vertices

#tested 
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


#tested
def biconnected_tarjan(graph: List[List[int]]) -> List[Set[int]]:
    n = len(graph) 

    # Initialize variables
    visited = [False] * n
    discover_t = [-1] * n
    parent = [-1] * n
    low = [0] * n

    timestamp = 0
    # linked list actually of pairs
    stack_edges = []
    biconnected_components = []

    def dfs(node):
        nonlocal timestamp
        visited[node] = True
        discover_t[node] = low[node] = timestamp
        timestamp += 1

        for neighbor in graph[node]:
            if not visited[neighbor]:
                parent[neighbor] = node
                stack_edges.append((node, neighbor))  # Push edge onto stack on first visit

                dfs(neighbor)

                # Update low-link values
                low[node] = min(low[node], low[neighbor])

                # Check if the current vertex-edge pair is a critical connection
                if (parent[node] == -1 and discover_t[node] <= low[neighbor]) or (parent[node] != -1 and discover_t[node] <= low[neighbor]):
                    comp = set()
        
                    while stack_edges and stack_edges[-1] != (node, neighbor):
                        edge = stack_edges.pop()
                        comp.add(edge[0])
                        comp.add(edge[1])
    
                    edge = stack_edges.pop()  # Pop the last edge that completes the component
                    comp.add(edge[0])
                    comp.add(edge[1])

                    if comp:
                        biconnected_components.append(comp)

            elif neighbor != parent[node] and discover_t[neighbor] < discover_t[node]:
                low[node] = min(low[node], discover_t[neighbor])
                stack_edges.append((node, neighbor))

    for i in range(1, n):
        if not visited[i]:
            dfs(i)
            # Empty any remaining edges in the stack
            comp = set()
            while stack_edges:
                edge = stack_edges.pop()
                comp.add(edge[0])
                comp.add(edge[1])
            if comp:
                biconnected_components.append(comp)

    return biconnected_components
    