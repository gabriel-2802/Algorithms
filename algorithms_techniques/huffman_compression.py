import heapq
import collections
from typing import  *


# tested
class Node: 
    def __init__(self, freq, symbol, left=None, right=None): 
        # frequency of symbol 
        self.freq = freq 
  
        # symbol name (character) 
        self.symbol = symbol 
  
        # node left of current node 
        self.left = left 
  
        # node right of current node 
        self.right = right 
  
        # tree direction (0/1) 
        self.huff = '' 
  
    def __lt__(self, nxt): 
        return self.freq < nxt.freq 
  

def build_huffman_tree(s: str) -> Node:
    # counts the frequency of each character in the string freq = [(char, freq), ...]
    freq = collections.Counter(s)
    
    nodes = [] # min heap of nodes (sorted by frequency)

    for character, frequency in freq.items():
        heapq.heappush(nodes, Node(frequency, character))


    while len(nodes) > 1:
        left = heapq.heappop(nodes)
        right = heapq.heappop(nodes)

        left.huff = '0'
        right.huff = '1'

        # combine the 2 nodes and push it back to the heap
        new_node = Node(left.freq + right.freq, left.symbol + right.symbol, left, right)
        heapq.heappush(nodes, new_node)


    return nodes[0]


def encodings(node: Node, huff_code = "", codes = {}) -> Dict[str, str]:
    new_code = huff_code + node.huff

    # if node is not an edge node (leaf) then traverse inside it
    if node.left:
        encodings(node.left, new_code, codes)
    if node.right:
        encodings(node.right, new_code, codes)

    # if node is an edge node then save its huff_code
    if not node.left and not node.right:
        codes[node.symbol] = new_code

    return codes





