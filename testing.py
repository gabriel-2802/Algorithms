# import os 
# from tarjan_alg import scc_tarjan

# def read_graph_from_file(file_path):
#     with open(file_path, 'r') as file:
#         lines = file.readlines()
#         if not lines:
#             raise ValueError("File is empty")

#         n, m = map(int, lines[0].strip().split())  # Read number of nodes and edges
#         graph = [[] for _ in range(n)]  # Create an adjacency list, 0-indexed

#         for line in lines[1:m + 1]:  # Process only m lines containing the edges
#             parts = line.strip().split()
#             if len(parts) != 2:
#                 raise ValueError("Edge line does not consist of two integers")
#             u, v = map(int, parts)
#             if not (1 <= u <= n) or not (1 <= v <= n):
#                 raise ValueError("Node index out of valid range")

#             # Subtract 1 to convert from 1-indexed to 0-indexed
#             graph[u-1].append(v-1)

#     print(graph)

# # def process_graphs_in_folder(folder_path):
# #     graphs = []
# #     for filename in os.listdir(folder_path):
# #         if filename.endswith(".in"):
# #             full_path = os.path.join(folder_path, filename)
# #             graph = read_graph_from_file(full_path)
# #             graphs.append(graph)
# #             print(f"Graph from {filename}: {graph}")

# #     return graphs

# # Example usage
# # folder_path = 'pa-lab/skel/lab08/tests/task-1'
# # graphs = process_graphs_in_folder(folder_path)
# (read_graph_from_file('pa-lab/skel/lab08/tests/task-1/1.in'))


# # scc = scc_tarjan(graph)
# # print(len(scc))
# # print(scc)
