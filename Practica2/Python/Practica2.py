import time
import tracemalloc
import random
import sys

# Aumentar límite de recursión para Tree Sort y Merge Sort
sys.setrecursionlimit(2000000)

def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        L = arr[:mid]
        R = arr[mid:]

        merge_sort(L)
        merge_sort(R)

        i = j = k = 0
        while i < len(L) and j < len(R):
            if L[i] < R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1

        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1

        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1

# Aquí agregas las demás implementaciones...

def ejecutar_prueba(n):
    print(f"\n--- Prueba con N={n} ---")
    arr = [random.uniform(0.0, 1000.0) for _ in range(n)]
    
    tracemalloc.start()
    inicio_tiempo = time.time()
    
    # Llama a tu algoritmo aquí
    merge_sort(arr)
    
    fin_tiempo = time.time()
    memoria_actual, memoria_pico = tracemalloc.get_traced_memory()
    tracemalloc.stop()
    
    print(f"Tiempo de ejecución: {fin_tiempo - inicio_tiempo:.4f} segundos")
    print(f"Pico de memoria consumida: {memoria_pico / 10**6:.2f} MB")

# Prueba (Evita correr los tamaños muy grandes con algoritmos lentos)
ejecutar_prueba(100_000)

# --- HEAPSORT ---
def heapify(arr, n, i):
    largest = i
    l = 2 * i + 1
    r = 2 * i + 2
    
    if l < n and arr[l] > arr[largest]:
        largest = l
    if r < n and arr[r] > arr[largest]:
        largest = r
        
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)

def heap_sort(arr):
    n = len(arr)
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)
    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        heapify(arr, i, 0)


# --- TREE SORT ---
class Node:
    def __init__(self, key):
        self.left = None
        self.right = None
        self.val = key

def insert(root, key):
    if root is None:
        return Node(key)
    if key < root.val:
        root.left = insert(root.left, key)
    else:
        root.right = insert(root.right, key)
    return root

def store_sorted(root, arr, i):
    if root is not None:
        i = store_sorted(root.left, arr, i)
        arr[i] = root.val
        i += 1
        i = store_sorted(root.right, arr, i)
    return i

def tree_sort(arr):
    if not arr: return
    root = None
    for val in arr:
        root = insert(root, val)
    store_sorted(root, arr, 0)


# --- COUNTING SORT (Adaptado para Reales) ---
def counting_sort(arr):
    if not arr: return
    max_val, min_val = max(arr), min(arr)
    scale = 100
    
    ran = int((max_val - min_val) * scale) + 1
    count = [0] * ran
    output = [0.0] * len(arr)
    
    for num in arr:
        count[int((num - min_val) * scale)] += 1
        
    for i in range(1, len(count)):
        count[i] += count[i-1]
        
    for num in reversed(arr):
        idx = int((num - min_val) * scale)
        output[count[idx] - 1] = num
        count[idx] -= 1
        
    for i in range(len(arr)):
        arr[i] = output[i]