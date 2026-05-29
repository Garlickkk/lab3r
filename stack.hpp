#ifndef STACK_HPP
#define STACK_HPP

#include "array_sequence.hpp"
#include "exceptions.hpp"
#include <functional>

template<class T>
class Stack {
private:
    MutableArraySequence<T> data;

public:
    Stack() {}

    void Push(T item);
    T Pop();
    T Top() const;
    bool IsEmpty() const;
    int GetSize() const;

    int IndexOf(const Stack<T> &subseq) const; // инд первого вхождения
    Stack<int> *FindAllOccurrences(const Stack<T> &subseq) const; // все вхождения

    Stack<T> *Map(std::function<T(T)> f) const; // поэлементное преобразование
    Stack<T> *Map(std::function<T(T, int)> f) const; // Map с индексом
    Stack<T> *Where(std::function<bool(T)> f) const;
    T Reduce(std::function<T(T, T)> f, T init) const;
    Stack<T> *Zip(const Stack<T> *other, std::function<T(T, T)> f) const; // поэлементная операция
    Stack<T> *Concat(const Stack<T> *other) const; // объединение 2 ст
};


template<class T>
void Stack<T>::Push(T item) {
    data.Append(item); // добавляем элемент в конец
}

template<class T>
T Stack<T>::Pop() {
    if (data.GetLength() == 0) {
        throw EmptyContainerException("Стек пуст");
    }
    T item = data.GetLast();
    data.RemoveLast();
    return item;
}

template<class T>
T Stack<T>::Top() const {
    if (data.GetLength() == 0) {
        throw EmptyContainerException("Стек пуст");
    }
    return data.GetLast();
}

template<class T>
bool Stack<T>::IsEmpty() const {
    return data.GetLength() == 0;
}

template<class T>
int Stack<T>::GetSize() const {
    return data.GetLength();
}


template<class T>
int Stack<T>::IndexOf(const Stack<T> &subseq) const {
    if (subseq.GetSize() == 0) { // пустая подп-ть
        return 0; // считается найденной в начале
    }
    if (subseq.GetSize() > GetSize()) { // подп-ть длиннее стека
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
            return i; // индекс начала
        }
    }
    return -1;
}

template<class T>
Stack<int> *Stack<T>::FindAllOccurrences(const Stack<T> &subseq) const {
    Stack<int> *result = new Stack<int>(); // стек для хранения индексов

    if (subseq.GetSize() == 0 || subseq.GetSize() > GetSize()) {
        return result; // пустой стек
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
            result->Push(i); // индекс вхождения
        }
    }
    return result;
}

template<class T>
Stack<T> *Stack<T>::Concat(const Stack<T> *other) const {
    Stack<T> *result = new Stack<T>();

    for (int i = 0; i < GetSize(); i++) { // копируем элементы текущего стека
        result->Push(data.Get(i));
    }

    for (int i = 0; i < other->GetSize(); i++) { // копируем элементы второго стека
        result->Push(other->data.Get(i));
    }

    return result;
}


template<class T>
Stack<T> *Stack<T>::Map(std::function<T(T)> f) const {
    Stack<T> *result = new Stack<T>();
    for (int i = 0; i < GetSize(); i++) {
        result->Push(f(data.Get(i))); // применяем функцию и добавляем в новый стек
    }
    return result;
}

template<class T>
Stack<T> *Stack<T>::Map(std::function<T(T, int)> f) const {
    Stack<T> *result = new Stack<T>();
    for (int i = 0; i < GetSize(); i++) {
        result->Push(f(data.Get(i), i)); // передаём элемент и его индекс
    }
    return result;
}

template<class T>
Stack<T> *Stack<T>::Where(std::function<bool(T)> f) const {
    Stack<T> *result = new Stack<T>();
    for (int i = 0; i < GetSize(); i++) {
        T val = data.Get(i);
        if (f(val)) {
            result->Push(val);
        }
    }
    return result;
}

template<class T>
T Stack<T>::Reduce(std::function<T(T, T)> f, T init) const {
    T acc = init;
    for (int i = 0; i < GetSize(); i++) {
        acc = f(acc, data.Get(i));
    }
    return acc;
}

template<class T>
Stack<T> *Stack<T>::Zip(const Stack<T> *other, std::function<T(T, T)> f) const {
    Stack<T> *result = new Stack<T>();
    int minSize;
    if (GetSize() < other->GetSize()) {
        minSize = GetSize();
    } else {
        minSize = other->GetSize();
    }
    for (int i = 0; i < minSize; i++) {
        result->Push(f(data.Get(i), other->data.Get(i)));
    }
    return result;
}
#endif // STACK_HPP