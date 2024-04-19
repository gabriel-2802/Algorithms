from typing import List
MAX = 10**9

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

# tested
# returns the complement of a graph
def complement_graph(graph: List[List[int]]) -> List[List[int]]:
    # create the empty complement graph
    n = len(graph)
    complement = [[] for _ in range(n)]

    for node in range(1, n):
        for neighbor in graph[node]:
            # for the edge (u,v) in the original graph, add the edge (u,v) to the complement graph
            complement[neighbor].append(node)
    return complement


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

    # Get the transpose of the graph
    transposed_graph = complement_graph(graph)
    visited = [False] * (n)  # Reset visited for the second pass

    def dfs2(node, cur_scc):
        visited[node] = True
        # add the node to the current scc
        cur_scc.append(node)

        # proceed the dfs
        for neighbor in transposed_graph[node]:
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
