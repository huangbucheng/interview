#include <vector>
#include <iostream>

/*
 * 最小堆
 * 例：海量数据中查找Top N的数
 */

class MinHeap {
    public:
        MinHeap(int capacity):_m_capacity(capacity) {}
        void insert(int value);
        void print();

    private:
        void shift_up();
        void shift_down();

    private:
        std::vector<int> _m_heap;
        int _m_capacity;
};

void MinHeap::insert(int value) {
    if (_m_heap.size() < _m_capacity) {
        _m_heap.push_back(value);
        shift_up();
    } else if (_m_heap[0] < value) {
        _m_heap[0] = value;
        shift_down();
    }
}

void MinHeap::shift_up() {
    int idx = _m_heap.size();
    if (idx == 1) {
        return;
    }
    while (idx/2 >= 1) {
        int parent = idx/2;
        if (_m_heap[parent-1] > _m_heap[idx-1]) {
            std::swap(_m_heap[parent-1], _m_heap[idx-1]);
            idx = parent;
        } else {
            break;
        }
    }
}

void MinHeap::shift_down() {
    int idx = 1;
    int size = _m_heap.size();
    while (idx*2 <= size) {
        int left = idx*2;
        int right = idx*2+1;
        int min_idx = left;
        if ((right <= size) && (_m_heap[left-1] > _m_heap[right-1])) {
            min_idx = right;
        }
        if (_m_heap[min_idx-1] < _m_heap[idx-1]) {
            std::swap(_m_heap[min_idx-1], _m_heap[idx-1]);
            idx = min_idx;
        } else {
            break;
        }
    }
}

void MinHeap::print() {
    for (int i=0; i<_m_heap.size(); i++) {
        std::cout << _m_heap[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int s_list[20] = {28, 23, 13, 64, 23, 12, 0, 232, 323, 21,
                      93, 98, 32, 11, 45, 0, 1, 98, 123, 121};
    MinHeap my_heap(10);
    for (int i = 0; i < 20; i++) {
        my_heap.insert(s_list[i]);
    }
    my_heap.print();
}
