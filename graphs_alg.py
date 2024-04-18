from typing import List

# tested
def complement_graph(graph: List[List[int]]) -> List[List[int]]:
    # create the empty complement graph
    n = len(graph) + 1
    complement = [[] for _ in range(n + 1)]


    for node in range(1, n):
        for neighbor in graph[node - 1]:
            complement[neighbor].append(node)
    return complement


# tested
def scc_kosaraju(graph: List[List[int]]) -> List[List[int]]:
    n = len(graph)
    visited = [False] * (n + 1)  # Visited list with extra space for 1-based indexing

    stack = []
    scc = []

    def dfs(node):
        visited[node] = True
        for neighbor in graph[node - 1]:  # Translate to 0-index to access neighbors
            if not visited[neighbor]:
                dfs(neighbor)

        stack.append(node) 

    for i in range(1, n + 1):
        if not visited[i]:
            dfs(i)

    # Get the transpose of the graph
    transposed_graph = complement_graph(graph)
    visited = [False] * (n + 1)  # Reset visited for the second pass

    def dfs2(node, cur_scc):
        visited[node] = True
        cur_scc.append(node)
        for neighbor in transposed_graph[node]:
            if not visited[neighbor]:
                dfs2(neighbor, cur_scc)

    # Second pass: form SCCs based on the order in the stack
    while stack:
        node = stack.pop()
        if not visited[node]:
            cur_scc = []
            dfs2(node, cur_scc)
            scc.append(cur_scc)

    return scc



            




    
