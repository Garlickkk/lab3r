#ifndef DEQUE_HPP
#define DEQUE_HPP

#include "list_sequence.hpp"
#include "exceptions.hpp"
#include <functional>

template<class T>
class Deque {
private:
    MutableListSequence<T> data;

public:
    Deque() {}

    void PushFront(T item);
    void PushBack(T item);
    T PopFront();
    T PopBack();
    T PeekFront() const;
    T PeekBack() const;
    T Peek(int index) const;
    bool IsEmpty() const;
    int GetSize() const;

    Deque<T> *Map(std::function<T(T)> f) const;
    Deque<T> *Where(std::function<bool(T)> f) const;
    T Reduce(std::function<T(T, T)> f, T init) const;

    Deque<T> *Concat(const Deque<T> *other) const;

    Deque<T> *GetSubsequence(int startIndex, int endIndex) const;

    int IndexOf(const Deque<T> &subseq) const;

    void Sort();
};

template<class T>
void Deque<T>::PushFront(T item) {
    data.Prepend(item);
}

template<class T>
void Deque<T>::PushBack(T item) {
    data.Append(item);
}

template<class T>
T Deque<T>::PopFront() {
    if (data.GetLength() == 0) {
        throw EmptyContainerException("Дек пуст");
    }
    T item = data.GetFirst();
    data.RemoveFirst();
    return item;
}

template<class T>
T Deque<T>::PopBack() {
    if (data.GetLength() == 0) {
        throw EmptyContainerException("Дек пуст");
    }
    T item = data.GetLast();
    data.RemoveLast();
    return item;
}

template<class T>
T Deque<T>::PeekFront() const {
    if (data.GetLength() == 0) {
        throw EmptyContainerException("Дек пуст");
    }
    return data.GetFirst();
}

template<class T>
T Deque<T>::PeekBack() const {
    if (data.GetLength() == 0) {
        throw EmptyContainerException("Дек пуст");
    }
    return data.GetLast();
}

template<class T>
T Deque<T>::Peek(int index) const {
    if (index < 0 || index >= data.GetLength()) {
        throw IndexOutOfRangeException(index, data.GetLength());
    }
    return data.Get(index);
}

template<class T>
bool Deque<T>::IsEmpty() const {
    return data.GetLength() == 0;
}

template<class T>
int Deque<T>::GetSize() const {
    return data.GetLength();
}

template<class T>
Deque<T> *Deque<T>::Map(std::function<T(T)> f) const {
    Deque<T> *result = new Deque<T>();
    for (int i = 0; i < data.GetLength(); i++) {
        result->PushBack(f(data.Get(i)));
    }
    return result;
}

template<class T>
Deque<T> *Deque<T>::Where(std::function<bool(T)> f) const {
    Deque<T> *result = new Deque<T>();
    for (int i = 0; i < data.GetLength(); i++) {
        T val = data.Get(i);
        if (f(val)) {
            result->PushBack(val);
        }
    }
    return result;
}

template<class T>
T Deque<T>::Reduce(std::function<T(T, T)> f, T init) const {
    T acc = init;
    for (int i = 0; i < data.GetLength(); i++) {
        acc = f(acc, data.Get(i));
    }
    return acc;
}

template<class T>
Deque<T> *Deque<T>::Concat(const Deque<T> *other) const {
    Deque<T> *result = new Deque<T>();

    for (int i = 0; i < data.GetLength(); i++) {
        result->PushBack(data.Get(i));
    }

    for (int i = 0; i < other->data.GetLength(); i++) {
        result->PushBack(other->data.Get(i));
    }

    return result;
}

template<class T>
Deque<T> *Deque<T>::GetSubsequence(int startIndex, int endIndex) const {
    if (startIndex < 0 || startIndex >= data.GetLength()) {
        throw IndexOutOfRangeException(startIndex, data.GetLength());
    }
    if (endIndex < 0 || endIndex >= data.GetLength()) {
        throw IndexOutOfRangeException(endIndex, data.GetLength());
    }
    if (endIndex < startIndex) {
        throw IndexOutOfRangeException("startIndex > endIndex");
    }

    Deque<T> *result = new Deque<T>();
    for (int i = startIndex; i <= endIndex; i++) {
        result->PushBack(data.Get(i));
    }
    return result;
}

template<class T>
int Deque<T>::IndexOf(const Deque<T> &subseq) const {
    if (subseq.data.GetLength() == 0) {
        return 0;
    }
    if (subseq.data.GetLength() > data.GetLength()) {
        return -1;
    }

    for (int i = 0; i <= data.GetLength() - subseq.data.GetLength(); i++) {
        bool found = true;
        for (int j = 0; j < subseq.data.GetLength(); j++) {
            if (data.Get(i + j) != subseq.data.Get(j)) {
                found = false;
                break;
            }
        }
        if (found) {
            return i;
        }
    }
    return -1;
}

template<class T>
void Deque<T>::Sort() { // пузырьковая
    int size = data.GetLength();
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            T a = data.Get(j);
            T b = data.Get(j + 1);
            if (a > b) { // л > п.
                MutableListSequence<T> temp;
                for (int k = 0; k < size; k++) {
                    if (k == j) { // сейчас левый
                        temp.Append(b); // доб правый
                    }
                    else if (k == j + 1) { // сейчас правый
                        temp.Append(a); // доб левый
                    }
                    else {
                        temp.Append(data.Get(k));// копия без изм
                    }
                }
                data = temp;
            }
        }
    }
}
#endif // DEQUE_HPP