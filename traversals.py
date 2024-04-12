from collections import deque

def dfs(graph, visited):
    for node in range(len(graph)):
        if node not in visited:
            dfs_from_source(node, graph, visited)

# visited = set()
def dfs_from_source(node, graph, visited):
    visited.add(node)
    # start[node] = time++
    for neighbor in graph[node]:
        if neighbor not in visited:
            # parent[neighbor] = node
            dfs_from_source(neighbor, graph, visited)

    #end[node] = time++
    # stack.append(node) for topological sort


# returns the shortest distances from source to all nodes
def bfs(source, graph):
    dist = [float('inf')] * len(graph)  # Initialize distances to infinity
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

                
    

