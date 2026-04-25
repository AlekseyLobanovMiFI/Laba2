template<class T> class Queue {
private:
    DynamicArray<T> buffer;
    int head = 0;
    int tail = 0;
    int size = 0;
    int capacity;

    void Resize() {
        int newCapacity = capacity * 2;
        DynamicArray<T> newBuffer(newCapacity);

        for (int i = 0; i < size; i++) {
            newBuffer[i] = buffer[(head + i) % capacity];
        }

        buffer = newBuffer;
        head = 0;
        tail = size;
        capacity = newCapacity;
    }

public:
    Queue(int cap = 4) : buffer(cap), capacity(cap) {}

    void Enqueue(const T& item) {
        if (size == capacity){
            Resize();
        }
        buffer[tail] = item;
        tail = (tail + 1) % capacity;
        size++;
    }

    T Dequeue() {
        if (size == 0){
            throw std::out_of_range("Empty queue");
        }

        T val = buffer[head];
        head = (head + 1) % capacity;
        size--;
        return val;
    }

    bool IsEmpty() const {
        return size == 0;
    }

    T Front() const {
        if (size == 0)
            throw std::out_of_range("Empty queue");
        return buffer[head];
    }

    T Back() const {
        if (size == 0)
            throw std::out_of_range("Empty queue");
        return buffer[(tail - 1 + capacity) % capacity];
    }

    int GetSize() const {
        return size;
    }
};