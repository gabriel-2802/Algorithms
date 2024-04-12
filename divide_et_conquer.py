import random
from typing import *

# verified -> merge_sort(v, 0, len(v) - 1)
def merge_sort(v, start, end):
    if start >= end:
        return

    mid = (end - start) // 2 + start
    merge_sort(v, start, mid)
    merge_sort(v, mid + 1, end)
    merge(v, start, end)

def merge(v, start, end):
    mid = (end - start) // 2 + start
    
    aux = [0] * (end - start + 1)
    i = start
    j = mid + 1
    k = 0

    while i <= mid and j <= end:
        if v[i] < v[j]:
            aux[k] = v[i]
            i += 1
        else:
            aux[k] = v[j]
            j += 1
        k += 1
    
    while i <= mid:
        aux[k] = v[i]
        i += 1
        k += 1
    
    while j <= end:
        aux[k] = v[j]
        j += 1
        k += 1
    
    for i in range(start, end + 1):
        v[i] = aux[i - start]


# verified -> quick_sort(v, 0, len(v) - 1)
def quick_sort(v, start, end):
    if start >= end:
        return

    pivot = partition(v, start, end)
    quick_sort(v, start, pivot - 1)
    quick_sort(v, pivot + 1, end)

def partition(v, start, end):
    pivot = random.randint(start, end)
    v[pivot], v[end] = v[end], v[pivot]
    pivot = end

    i = start
    for j in range(start, end):
        if v[j] < v[pivot]:
            v[i], v[j] = v[j], v[i]
            i += 1

    v[i], v[pivot] = v[pivot], v[i]
    return i

# verified -> binary_search(v, target, 0, len(v))
def binary_search(v, target, start, end):
    if start > end:
        return -1  

    mid = (end - start) // 2 + start
    if v[mid] == target:
        return mid  # Target found
    elif v[mid] < target:
        return binary_search(v, target, mid + 1, end) 
    else:
        return binary_search(v, target, start, mid - 1)


def binary_search_first_occurrence(v, target, start, end):
    if start > end:
        return -1

    mid = (end - start) // 2 + start
    if v[mid] == target and (mid == 0 or v[mid - 1] != target):
        return mid
    elif v[mid] < target:
        return binary_search_first_occurrence(v, target, mid + 1, end)
    else:
        return binary_search_first_occurrence(v, target, start, mid - 1)
    
def binary_search_last_occurrence(v, target, start, end):
    if start > end:
        return -1

    mid = (end - start) // 2 + start
    if v[mid] == target and (mid == len(v) - 1 or v[mid + 1] != target):
        return mid
    elif v[mid] <= target:
        return binary_search_last_occurrence(v, target, mid + 1, end)
    else:
        return binary_search_last_occurrence(v, target, start, mid - 1)



def logaritmic_exponentiation(base, exp, modulo):
    result = 1
    
    while (exp > 0):
        if exp % 2 == 1:
            result = ((result % modulo) * (base % modulo)) % modulo
        
        base = ((base % modulo) * (base % modulo)) % modulo
        exp //= 2
    
    return result % modulo