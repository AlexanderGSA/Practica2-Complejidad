#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

// Ejemplo de algoritmo: Bubble Sort
void bubbleSort(std::vector<float>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Aquí agregas Mergesort, Heapsort, Tree Sort y Counting Sort...

int main() {
    // Tamaños: 100000, 1000000, 10000000, 100000000, 1000000000
    size_t n = 100000; 
    
    std::cout << "Asignando memoria para " << n << " elementos...\n";
    std::vector<float> arr(n);
    
    // Generación de números reales aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0, 1000.0);
    
    for(size_t i = 0; i < n; ++i) {
        arr[i] = dis(gen);
    }

    std::cout << "Iniciando ordenamiento...\n";
    auto start = std::chrono::high_resolution_clock::now();
    
    // Llama a tu algoritmo aquí
    bubbleSort(arr); 
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    
    std::cout << "Tiempo de ejecucion: " << diff.count() << " segundos\n";
    std::cout << "Memoria aprox. del arreglo: " << (n * sizeof(float)) / (1024.0 * 1024.0) << " MB\n";

    return 0;
}
// --- HEAPSORT ---
void heapify(std::vector<float>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<float>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}


// --- TREE SORT ---
struct Node {
    float key;
    Node *left, *right;
    Node(float item) : key(item), left(nullptr), right(nullptr) {}
};

Node* insert(Node* node, float key) {
    if (node == nullptr) return new Node(key);
    if (key < node->key) node->left = insert(node->left, key);
    else node->right = insert(node->right, key);
    return node;
}

void storeSorted(Node* root, std::vector<float>& arr, int& i) {
    if (root != nullptr) {
        storeSorted(root->left, arr, i);
        arr[i++] = root->key;
        storeSorted(root->right, arr, i);
    }
}

void treeSort(std::vector<float>& arr) {
    Node* root = nullptr;
    for (float val : arr) root = insert(root, val);
    int i = 0;
    storeSorted(root, arr, i);
}


// --- COUNTING SORT (Adaptado para Reales) ---
// Multiplica por 100 para tratar los dos primeros decimales como enteros
void countingSort(std::vector<float>& arr) {
    if(arr.empty()) return;
    float max_val = *std::max_element(arr.begin(), arr.end());
    float min_val = *std::min_element(arr.begin(), arr.end());
    
    int scale = 100; 
    int range = (max_val - min_val) * scale + 1;
    
    std::vector<int> count(range, 0);
    std::vector<float> output(arr.size());
    
    for(size_t i = 0; i < arr.size(); i++) {
        count[(int)((arr[i] - min_val) * scale)]++;
    }
    
    for(size_t i = 1; i < count.size(); i++) {
        count[i] += count[i-1];
    }
    
    for(int i = arr.size() - 1; i >= 0; i--) {
        int idx = (int)((arr[i] - min_val) * scale);
        output[count[idx] - 1] = arr[i];
        count[idx]--;
    }
    
    for(size_t i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
    }
}