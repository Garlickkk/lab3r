#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list_sequence.hpp"
#include "exceptions.hpp"
#include <functional>


template<class T>
class Queue {
private:
    MutableListSequence<T> data;

public:
    Queue() {}

    void Enqueue(T item); // добавить в конец
    T Dequeue(); // взять из начала
    T Peek() const; // 1-й элемент
    bool IsEmpty() const;
    int GetSize() const;

    Queue<T> *Map(std::function<T(T)> f) const;
    Queue<T> *Map(std::function<T(T, int)> f) const;
    Queue<T> *Where(std::function<bool(T)> f) const;
    T Reduce(std::function<T(T, T)> f, T init) const;
    Queue<T> *Concat(const Queue<T> *other) const;
    Queue<T> *GetSubsequence(int startIndex, int endIndex) const;

    int IndexOf(const Queue<T> &subseq) const;
};


template<class T>
void Queue<T>::Enqueue(T item) {
    data.Append(item);
}

template<class T>
T Queue<T>::Dequeue() {
    if (data.GetLength() == 0) {
        throw EmptyContainerException("Очередь пуста");
    }
    T firstItem = data.GetFirst();
    data.RemoveFirst();
    return firstItem;
}

template<class T>
T Queue<T>::Peek() const {
    if (data.GetLength() == 0) {
        throw EmptyContainerException("Очередь пуста");
    }
    return data.GetFirst();
}

template<class T>
bool Queue<T>::IsEmpty() const {
    return data.GetLength() == 0;
}

template<class T>
int Queue<T>::GetSize() const {
    return data.GetLength();
}

template<class T>
Queue<T> *Queue<T>::Map(std::function<T(T)> f) const {
    Queue<T> *result = new Queue<T>();
    for (int i = 0; i < GetSize(); i++) {
        result->Enqueue(f(data.Get(i)));
    }
    return result;
}

template<class T>
Queue<T> *Queue<T>::Map(std::function<T(T, int)> f) const {
    Queue<T> *result = new Queue<T>();
    for (int i = 0; i < GetSize(); i++) {
        result->Enqueue(f(data.Get(i), i));
    }
    return result;
}

template<class T>
Queue<T> *Queue<T>::Where(std::function<bool(T)> f) const {
    Queue<T> *result = new Queue<T>();
    for (int i = 0; i < GetSize(); i++) {
        T val = data.Get(i);
        if (f(val)) {
            result->Enqueue(val);
        }
    }
    return result;
}

template<class T>
T Queue<T>::Reduce(std::function<T(T, T)> f, T init) const {
    T acc = init;
    for (int i = 0; i < GetSize(); i++) {
        acc = f(acc, data.Get(i));
    }
    return acc;
}

template<class T>
Queue<T> *Queue<T>::Concat(const Queue<T> *other) const {
    Queue<T> *result = new Queue<T>();

    for (int i = 0; i < GetSize(); i++) {
        result->Enqueue(data.Get(i));
    }

    for (int i = 0; i < other->GetSize(); i++) {
        result->Enqueue(other->data.Get(i));
    }

    return result;
}

template<class T>
Queue<T> *Queue<T>::GetSubsequence(int startIndex, int endIndex) const {
    if (startIndex < 0 || startIndex >= GetSize())
        throw IndexOutOfRangeException(startIndex, GetSize());
    if (endIndex < 0 || endIndex >= GetSize())
        throw IndexOutOfRangeException(endIndex, GetSize());
    if (endIndex < startIndex)
        throw IndexOutOfRangeException("startIndex > endIndex");

    Queue<T> *result = new Queue<T>();
    for (int i = startIndex; i <= endIndex; i++) {
        result->Enqueue(data.Get(i));
    }
    return result;
}

template<class T>
int Queue<T>::IndexOf(const Queue<T> &subseq) const {
    if (subseq.GetSize() == 0) {
        return 0;
    }
    if (subseq.GetSize() > GetSize()) {
        return -1;
    }

    for (int i = 0; i <= GetSize() - subseq.GetSize(); i++) {
        bool found = true;
        for (int j = 0; j < subseq.GetSize(); j++) {
            if (data.Get(i + j) != subseq.data.Get(j)) {
                found = false;
                break;
            }
        }
        if (found) {
            return i;
        }
    }
    return -1; // не нашли
}
#endif // QUEUE_HPP