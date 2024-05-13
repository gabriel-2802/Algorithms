from typing import List
from typing import Set
from typing import Tuple
from graphs.graphs_alg import scc_kosaraju

# complexity: O(V+E)
# tested
# DIRECTED GRAPHS
# returns a list of strongly connected components as lists of nodes
def scc_tarjan(graph: List[List[int]]) -> List[List[int]]:
    n = len(graph)

    # Initialize
    timestamp = 0 # Time of discovery, global variable
    visited = [False] * (n)  # Visited nodes (not using index 0)
    low = [0] * (n) # the minimum discovery time of a node reachable from the current node
    discover_t = [-1] * (n)  # Discovery time of each node (not using index 0)

    # stack and set to keep track of nodes in the current SCC
    stackNodes = []
    onStack = set()
    all_scc = []

    def dfs(node):
        nonlocal timestamp
        timestamp += 1
        discover_t[node] = low[node] = timestamp # convention for initial low
        visited[node] = True

        # add node to visiting stack
        stackNodes.append(node)
        onStack.add(node)

        for child in graph[node]:
            if not visited[child]:
                dfs(child)
                # update low value of the current node to its child low value
                low[node] = min(low[node], low[child])
            elif child in onStack:
                low[node] = min(low[node], discover_t[child])

        # if low value of the current node is equal to its discovery time, then it formed a cycle
        # a cycle is a strongly connected component and the nodes in the stack form the SCC
        if low[node] == discover_t[node]:
            scc = []
            # we pop nodes from the stack until we reach the current node
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

# complexity: O(V+E)
# tested
# UNDIRECTED GRAPHS
#returns a set of critical vertexes
def critical_vertices_tarjan(graph: List[List[int]]) -> Set[int]:
    n = len(graph)  # Number of vertices in the graph including the placeholder at index 0
    
    timestamp = 0
    visited = [False] * n
    discover_t = [-1] * n
    low = [0] * n

    # we need parents to ensure 2 way connections are detected
    parent = [-1] * n
    critical_vertices = set()

    def dfs(node):
        nonlocal timestamp
        visited[node] = True
        discover_t[node] = low[node] = timestamp + 1
        timestamp += 1

        children = 0  # Children counter for the current node

        for child in graph[node]:
            if not visited[child]:
                parent[child] = node
                children += 1
                dfs(child)

                # Check if the subtree rooted at child has connection back to one of the ancestors of node
                low[node] = min(low[node], low[child])

                # (1) node is root of DFS tree and has two or more children
                if parent[node] == -1 and children > 1:
                    critical_vertices.add(node)
                
                # (2) node is not root and low value of one of its child is more than discovery value of node
                if parent[node] != -1 and low[child] >= discover_t[node]:
                    critical_vertices.add(node)

            elif child != parent[node]:  # Update low value of node for parent function calls.
                low[node] = min(low[node], discover_t[child])

    # Start from 1 as the first index, since 0 is a placeholder
    for i in range(1, n):
        if not visited[i]:
            dfs(i)

    return critical_vertices

# complexity: O(V+E)
#tested 
# UNDIRECTED GRAPHS
#returns a set of critical edges represented as pairs (src, dest)
def critical_edges_tarjan(graph: List[List[int]]) -> Set[Tuple[int, int]]:
    n = len(graph)

    # Initialize variables
    visited = [False] * (n)
    discover_t = [-1] * (n)
    low = [0] * (n)
    timestamp = 0

    parent = [-1] * (n)
    critical_edges = set()

    def dfs(node):
        nonlocal timestamp
        timestamp += 1
        visited[node] = True
        discover_t[node] = low[node] = timestamp

        for child in graph[node]:
            if not visited[child]:
                parent[child] = node
                dfs(child)
                low[node] = min(low[node], low[child])

                # condition for critical edge
                if low[child] > discover_t[node]:
                    critical_edges.add((node, child))

            elif child != parent[node]:
                low[node] = min(low[node], discover_t[child])

    
    for i in range(1, n):
        if not visited[i]:
            dfs(i)
    
    return critical_edges


# complexity: O(V+E)
#tested
# UNDIRECTED GRAPHS
#returns a list of biconnected components represented as sets of nodes
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
    # list of sets to store the biconnected components
    biconnected_components = []

    def dfs(node):
        nonlocal timestamp
        visited[node] = True
        discover_t[node] = low[node] = timestamp
        timestamp += 1

        for child in graph[node]:
            if not visited[child]:
                parent[child] = node
                stack_edges.append((node, child))  # Push edge onto stack on first visit

                dfs(child)
                # Update low-link values
                low[node] = min(low[node], low[child])

                # Check if the current vertex-edge pair is a critical connection
                if (parent[node] == -1 and discover_t[node] <= low[child]) or (parent[node] != -1 and discover_t[node] <= low[child]):
                    comp = set()
        
                    while stack_edges and stack_edges[-1] != (node, child):
                        edge = stack_edges.pop()
                        comp.add(edge[0])
                        comp.add(edge[1])
    
                    edge = stack_edges.pop()  # Pop the last edge that completes the component
                    comp.add(edge[0])
                    comp.add(edge[1])

                    if comp:
                        biconnected_components.append(comp)

            elif child != parent[node] and discover_t[child] < discover_t[node]:
                low[node] = min(low[node], discover_t[child])
                stack_edges.append((node, child))

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