from typing import List
from collections import deque
MAX = 10**9

# complexity: O(V+E)
# tested
def convert_directed_to_undirected(graph: List[List[int]]) -> List[List[int]]:
    n = len(graph) 
    undirected_graph = [[] for _ in range(n)]

    for node in range(1,n):
        for neighbor in graph[node]:
             # add the edge (u,v) and (v,u) to the undirected graph
            if neighbor not in undirected_graph[node]:
                undirected_graph[node].append(neighbor)
            if node not in undirected_graph[neighbor]:
                undirected_graph[neighbor].append(node)

    return undirected_graph

# complexity: O(V+E)
# tested
# returns the complement of a graph
def invert_graph(graph: List[List[int]]) -> List[List[int]]:
    # create the empty complement graph
    n = len(graph)
    complement = [[] for _ in range(n)]

    for node in range(1, n):
        for neighbor in graph[node]:
            # for the edge (u,v) in the original graph, add the edge (v,u) to the complement graph
            complement[neighbor].append(node)
    return complement


# complexity: O(V+E)
# tested
# finds all strongly connected components
# used for directed graphs
def scc_kosaraju(graph: List[List[int]]) -> List[List[int]]:
    n = len(graph)
    visited = [False] * (n)

    # visiting order stack
    stack = []
    # list of lists to store the strongly connected components
    scc = []

    def dfs(node):
        visited[node] = True    
        for neighbor in graph[node]: 
            if not visited[neighbor]:
                dfs(neighbor)

        # add the node to the stack after visiting all its neighbors
        stack.append(node)


    # dfs on the graph with a stack to store the order of visiting
    for i in range(1, n):
        if not visited[i]:
            dfs(i)

    # Get the inverse of the graph
    inverse_graph = invert_graph(graph)
    visited = [False] * (n)  # Reset visited for the second pass

    def dfs2(node, cur_scc):
        visited[node] = True
        # add the node to the current scc
        cur_scc.append(node)

        # proceed the dfs
        for neighbor in inverse_graph[node]:
            if not visited[neighbor]:
                dfs2(neighbor, cur_scc)

    # Second pass: form SCCs based on the order in the stack
    # each non visited node in the stack is the start of a new SCC
    while stack:
        node = stack.pop()

        if not visited[node]:
            cur_scc = []
            dfs2(node, cur_scc)
            scc.append(cur_scc)

    return scc

# complexity: O(V)
# tested
# returns the shortest path from source to destination
# use a linked list to store the path to avoid reversing the path
# parent[i] = parent of node i, distance[i] = distance from source to node i
def rebuild_path(parent: List[int], distance: List[int], source: int, destination: int) -> List[int]:
    # if distance[destination] is MAX, then there is no path
    if distance[destination] == MAX:
        return []

    path = []

    node = destination
    while node != source:
        path.insert(0, node) # insert at the beginning of the list
        # go to the parent of the node
        node = parent[node]

    path.insert(0, source)
    return path

# complexity: O(V+E)
# tested
def internal_degree(graph: List[List[int]]) -> List[int]:
    n = len(graph)
    degree = [0] * n

    for node in range(1, n):
        for neighbor in graph[node]:
            degree[neighbor] += 1

    return degree

# complexity: O(V+E)
# tested
def topological_sort(graph: List[List[int]]) -> List[int]:
    n = len(graph)
    visited = [False] * n
    # queue to store the nodes with 0 internal degree
    queue = deque()

    # get the internal degree of each node
    degrees = internal_degree(graph)

    # add the nodes with 0 internal degree to the queue
    for node in range(1, n):
        if degrees[node] == 0:
            queue.append(node)

    topological_order = []
    while queue:
        # get the node with 0 internal degree
        node = queue.popleft()
        # add it to the topological order
        topological_order.append(node)

        for neighbor in graph[node]:
            degrees[neighbor] -= 1
            if degrees[neighbor] == 0:
                queue.append(neighbor)

    return topological_order

# complexity: O(V+E)
# tested
# tested
def topological_sort_dfs(graph: List[List[int]]) -> List[int]:
    n = len(graph)
    visited = [False] * n
    # list to store the topological order (use linked list to avoid reversing the order)
    topo = []

    def dfs(node):
        visited[node] = True
        for neighbor in graph[node]:
            if not visited[neighbor]:
                dfs(neighbor)
        topo.append(node)

    for node in range(1, n):
        if not visited[node]:
            dfs(node)

    return topo[::-1]  # reverse the order to get the topological order

    