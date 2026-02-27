#include <iostream>
#include <vector>

using namespace std;

void heapify(vector<int> &v, int n, int i) {
    int largest = i;       // root
    int left = 2 * i + 1;  // left child
    int right = 2 * i + 2; // right child

    if (left < n && v[left] > v[largest])
        largest = left;

    if (right < n && v[right] > v[largest])
        largest = right;

    if (largest != i) {
        swap(v[i], v[largest]);
        heapify(v, n, largest); // recursive down
    }
}

void heap_sort(vector<int> &v) {
    int n = v.size();

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(v, n, i);
    }

    // Extract elements
    for (int i = n - 1; i > 0; i--) {
        swap(v[0], v[i]); // move max to end
        heapify(v, i, 0); // heapify reduced heap
    }
}

int main() {
    vector<int> v = {1, 4, 2, 4, 9, 7, 3};

    heap_sort(v);

    for (int x : v)
        cout << x << " ";
}