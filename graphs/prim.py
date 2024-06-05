from typing import List, Tuple
import heapq

MAX = 10**9


# tested
def prim_alg(src: int, weights: List[List[Tuple[int, int]]]) -> List[int]:
    n = len(weights)

    # initialize
    distance = [MAX] * n
    inside_tree = [False] * n
    parent = [-1] * n

    # distance to source is 0 and parent is -1 by convention
    distance[src] = 0
    parent[src] = -1

    # heap of pairs (distance, node): key is distance
    min_heap = []
    heapq.heappush(min_heap, (0, src))

    while min_heap:
        _, node = heapq.heappop(min_heap)
        if inside_tree[node]:
            continue
        inside_tree[node] = True

        # try to relax the edges for all neighbors of node
        for neighbor, weight in weights[node]:
            if weight < distance[neighbor] and not inside_tree[neighbor]:
                distance[neighbor] = weight
                parent[neighbor] = node
                heapq.heappush(min_heap, (distance[neighbor], neighbor))

    return parent
