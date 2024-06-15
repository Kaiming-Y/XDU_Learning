/*
 * 实现priority queue
 */

#include <iostream>
#include <vector>
#include <stdexcept>

class MaxPriorityQueue {
public:
    // 插入元素到优先队列
    void push(int val) {
        heap.push_back(val);
        siftUp((int)heap.size() - 1);
    }

    // 移除并返回最大元素
    int pop() {
        if (heap.empty()) {
            throw std::runtime_error("Cannot pop from an empty priority queue.");
        }
        int maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            siftDown(0);
        }
        return maxVal;
    }

    // 返回最大元素
    int top() {
        if (heap.empty()) {
            throw std::runtime_error("Cannot access top element of an empty priority queue.");
        }
        return heap[0];
    }

    // 检查优先队列是否为空
    bool empty() const {
        return heap.empty();
    }

private:
    std::vector<int> heap;

    // 上浮调整
    void siftUp(int idx) {
        while (idx > 0 && heap[parent(idx)] < heap[idx]) {
            std::swap(heap[parent(idx)], heap[idx]);
            idx = parent(idx);
        }
    }

    // 下沉调整
    void siftDown(int idx) {
        while (leftChild(idx) < heap.size()) {
            int largest = leftChild(idx);
            if (rightChild(idx) < heap.size() && heap[rightChild(idx)] > heap[leftChild(idx)]) {
                largest = rightChild(idx);
            }
            if (heap[idx] >= heap[largest]) break;
            std::swap(heap[idx], heap[largest]);
            idx = largest;
        }
    }

    // 返回父节点的索引
    static int parent(int idx) { return (idx - 1) / 2; }
    // 返回左子节点的索引
    static int leftChild(int idx) { return 2 * idx + 1; }
    // 返回右子节点的索引
    static int rightChild(int idx) { return 2 * idx + 2; }
};

int main() {
    MaxPriorityQueue pq;
    pq.push(3);
    pq.push(1);
    pq.push(4);
    pq.push(1);
    pq.push(5);
    pq.push(9);
    pq.push(2);
    pq.push(6);

    while (!pq.empty()) {
        std::cout << pq.pop() << " ";
    }
    std::cout << std::endl;

    return 0;
}
