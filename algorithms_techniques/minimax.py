from typing import Any, List

INFINITY = 10**9

# Given a configuration of the game, returns the evaluation of the state
def evaluate(state_node: Any) -> int:
    # Implementation of evaluation function goes here
    return 0

# Given a configuration of the game, returns the list of possible moves
def possible_moves(state_node: Any) -> List[Any]:
    # Implementation to generate possible moves goes here
    return []

# Check if the state is a terminal state
def is_terminal(state_node: Any) -> bool:
    # Implementation to check if the state is terminal goes here
    return False

def minimax(depth: int, state_node: Any, maximizing: bool) -> int:
    if depth == 0 or is_terminal(state_node):
        return evaluate(state_node)
    
    if maximizing:
        max_eval = -INFINITY
        for move in possible_moves(state_node):
            eval = minimax(depth - 1, move, False)
            max_eval = max(max_eval, eval)
        return max_eval
    else:
        min_eval = INFINITY
        for move in possible_moves(state_node):
            eval = minimax(depth - 1, move, True)
            min_eval = min(min_eval, eval)
        return min_eval


def alpha_beta_pruning(depth: int, state_node: Any, alpha: int, beta: int, maximizing: bool) -> int:
    if depth == 0 or is_terminal(state_node):
        return evaluate(state_node)
    
    if maximizing:
        max_eval = -INFINITY
        for move in possible_moves(state_node):
            eval = alpha_beta_pruning(depth - 1, move, alpha, beta, False)
            max_eval = max(max_eval, eval)
            alpha = max(alpha, eval)

            # Alpha-Beta Pruning: Cut off the remaining branches, becase the maximum value of the subtree is already found
            if beta <= alpha:
                break
        return max_eval
    else:
        min_eval = INFINITY
        for move in possible_moves(state_node):
            eval = alpha_beta_pruning(depth - 1, move, alpha, beta, True)
            min_eval = min(min_eval, eval)
            beta = min(beta, eval)
            
            # Alpha-Beta Pruning: Cut off the remaining branches because the minimum value of the subtree is already found
            if beta <= alpha:
                break
        return min_eval