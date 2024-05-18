def solve():
    import sys
    input = sys.stdin.read
    data = input().split()
    
    n = int(data[0])
    k1 = int(data[1])
    k2 = int(data[2])
    a = list(map(int, data[3:3+n]))
    b = list(map(int, data[3+n:3+2*n]))
    
    from collections import defaultdict, deque
    
    # Create graph connections based on index difference k1 and k2
    graph = defaultdict(list)
    for i in range(n):
        if i + k1 < n:
            graph[i].append(i + k1)
            graph[i + k1].append(i)
        if i + k2 < n:
            graph[i].append(i + k2)
            graph[i + k2].append(i)
    
    # Find connected components using BFS or DFS
    visited = [False] * n
    components = []
    
    def bfs(start):
        queue = deque([start])
        component = []
        visited[start] = True
        while queue:
            node = queue.popleft()
            component.append(node)
            for neighbor in graph[node]:
                if not visited[neighbor]:
                    visited[neighbor] = True
                    queue.append(neighbor)
        return component
    
    for i in range(n):
        if not visited[i]:
            components.append(bfs(i))
    
    # Calculate the minimal number of superspecial operations
    superspecial_operations = 0
    
    for comp in components:
        # Gather elements in the component from both arrays
        current_a = [a[i] for i in comp]
        current_b = [b[i] for i in comp]
        
        # Sort to compare
        current_a.sort()
        current_b.sort()
        
        # Count mismatches
        for x, y in zip(current_a, current_b):
            if x != y:
                superspecial_operations += 1
    
    # Output the result
    print(superspecial_operations)

if __name__ == "__main__":
    solve()
