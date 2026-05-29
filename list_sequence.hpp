#ifndef LIST_SEQUENCE_HPP
#define LIST_SEQUENCE_HPP

#include "sequence.hpp"
#include "linked_list.hpp"

template <class T> class MutableListSequence;
template <class T> class ImmutableListSequence;

template <class T>
class ListSequence : public Sequence<T> {
protected:
    LinkedList<T>* items;
    virtual ListSequence<T>* Instance() = 0;

    void AppendInternal(T item);
    void PrependInternal(T item);
    void InsertAtInternal(T item, int index);

public:
    ListSequence();
    ListSequence(T* data, int count);
    ListSequence(const LinkedList<T>& list);
    ListSequence(const ListSequence<T>& other);
    ~ListSequence() override;

    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
    int GetLength() const override;

    Sequence<T>* Append(T item) override;
    Sequence<T>* Prepend(T item) override;
    Sequence<T>* InsertAt(T item, int index) override;
    Sequence<T>* Concat(Sequence<T>* other) override;
    Sequence<T>* Empty() const override;
};

template <class T>
ListSequence<T>::ListSequence() : items(new LinkedList<T>()) {}

template <class T>
ListSequence<T>::ListSequence(T* data, int count) : items(new LinkedList<T>(data, count)) {}

template <class T>
ListSequence<T>::ListSequence(const LinkedList<T>& list) : items(new LinkedList<T>(list)) {}

template <class T>
ListSequence<T>::ListSequence(const ListSequence<T>& other)
    : items(new LinkedList<T>(*other.items)) {}

template <class T>
ListSequence<T>::~ListSequence() {
    delete items;
}

template <class T>
void ListSequence<T>::AppendInternal(T item) {
    items->Append(item);
}

template <class T>
void ListSequence<T>::PrependInternal(T item) {
    items->Prepend(item);
}

template <class T>
void ListSequence<T>::InsertAtInternal(T item, int index) {
    items->InsertAt(item, index);
}

template <class T>
T ListSequence<T>::GetFirst() const {
    return items->GetFirst();
}

template <class T>
T ListSequence<T>::GetLast() const {
    return items->GetLast();
}

template <class T>
T ListSequence<T>::Get(int index) const {
    return items->Get(index);
}

template <class T>
Sequence<T>* ListSequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    if (startIndex < 0 || startIndex >= items->GetLength())
        throw IndexOutOfRangeException("startIndex вне диапазона");
    if (endIndex < 0 || endIndex >= items->GetLength())
        throw IndexOutOfRangeException("endIndex вне диапазона");
    if (endIndex < startIndex)
        throw IndexOutOfRangeException("startIndex > endIndex");

    LinkedList<T>* sub = items->GetSubList(startIndex, endIndex);
    MutableListSequence<T>* result = new MutableListSequence<T>(*sub);
    delete sub;
    return result;
}

template <class T>
int ListSequence<T>::GetLength() const {
    return items->GetLength();
}

template <class T>
Sequence<T>* ListSequence<T>::Append(T item) {
    ListSequence<T>* inst = Instance();
    inst->AppendInternal(item);
    return inst;
}

template <class T>
Sequence<T>* ListSequence<T>::Prepend(T item) {
    ListSequence<T>* inst = Instance();
    inst->PrependInternal(item);
    return inst;
}

template <class T>
Sequence<T>* ListSequence<T>::InsertAt(T item, int index) {
    ListSequence<T>* inst = Instance();
    inst->InsertAtInternal(item, index);
    return inst;
}

template <class T>
Sequence<T>* ListSequence<T>::Concat(Sequence<T>* other) {
    ListSequence<T>* inst = Instance();
    for (int i = 0; i < other->GetLength(); i++) {
        inst->AppendInternal(other->Get(i));
    }
    return inst;
}

template <class T>
Sequence<T>* ListSequence<T>::Empty() const {
    return new MutableListSequence<T>();
}

//Mutable

template <class T>
class MutableListSequence : public ListSequence<T> {
protected:
    ListSequence<T>* Instance() override {
        return this;
    }
public:
    using ListSequence<T>::ListSequence;
    MutableListSequence(const ListSequence<T>& other) : ListSequence<T>(other) {}
    void RemoveFirst() {
        int len = this->items->GetLength();
        if (len == 0) {
            throw EmptyContainerException("Последовательность пуста");
        }
        if (len == 1) {
            delete this->items;
            this->items = new LinkedList<T>();
            return;
        }
        LinkedList<T>* newList = this->items->GetSubList(1, len - 1);
        delete this->items;
        this->items = newList;
    }

    void RemoveLast() {
        int len = this->items->GetLength();
        if (len == 0) {
            throw EmptyContainerException("Последовательность пуста");
        }
        if (len == 1) {
            delete this->items;
            this->items = new LinkedList<T>();
            return;
        }
        LinkedList<T>* newList = this->items->GetSubList(0, len - 2);
        delete this->items;
        this->items = newList;
    }
};

//Immutable

template <class T>
class ImmutableListSequence : public ListSequence<T> {
protected:
    ListSequence<T>* Instance() override {
        return new MutableListSequence<T>(static_cast<const ListSequence<T>&>(*this));
    }
public:
    using ListSequence<T>::ListSequence;
    ImmutableListSequence(const ListSequence<T>& other) : ListSequence<T>(other) {}
};

#endif