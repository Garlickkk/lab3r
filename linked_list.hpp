#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
#include <stdexcept>
#include "exceptions.hpp"

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node *next;
    };

    Node *head;
    Node *tail;
    int size;

public:
    LinkedList(); // Создать пустой список
    LinkedList(T *items, int count); //Копировать элементы из переданного массива
    LinkedList(const LinkedList<T> &list); // Копирующий конструктор
    LinkedList<T>& operator=(const LinkedList<T> &other); // Оператор присваивания
    ~LinkedList();

    T GetFirst() const; // сделать константы

    T GetLast() const;

    T Get(int index) const;

    LinkedList<T> *GetSubList(int startIndex, int endIndex) const;

    int GetLength() const;

    void Append(T item);

    void Prepend(T item);

    void InsertAt(T item, int index);

    LinkedList<T>* Concat(LinkedList<T> *list);
};

template<typename T>
LinkedList<T>::LinkedList() {
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

template<typename T>
LinkedList<T>::LinkedList(T *items, int count) {
    if (count < 0) {
        throw InvalidArgumentException("размер не может быть отрицательным");
    }
    if (items == nullptr) {
        throw InvalidArgumentException("Указатель не должен 0");
    }
    if (count == 0) {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
        return;
    }
    this->head = new Node{items[0], nullptr};
    Node *current = this->head;
    for (int i = 1; i < count; i++) {
        // 1-й эл создан
        current->next = new Node{items[i], nullptr};
        current = current->next;
    }
    this->size = count;
    this->tail = current;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) {
    if (list.head == nullptr) {  // не на что не указывает -> список пустой
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
        return;
    }
    this->head = new Node{list.head->data, nullptr};
    Node *current = this->head;
    Node *source = list.head->next;

    while (source != nullptr) {
        current->next = new Node{source->data, nullptr};
        current = current->next;
        source = source->next;
    }

    this->size = list.size;
    this->tail = current;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> &other) {
    if (this != &other) {
        Node* current = this->head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        if (other.head == nullptr) {
            this->head = nullptr;
            this->tail = nullptr;
            this->size = 0;
        } else {
            this->head = new Node{other.head->data, nullptr};
            Node* dest = this->head;
            Node* src = other.head->next;
            while (src != nullptr) {
                dest->next = new Node{src->data, nullptr};
                dest = dest->next;
                src = src->next;
            }
            this->tail = dest;
            this->size = other.size;
        }
    }
    return *this;
}

template<typename T>
T LinkedList<T>::GetFirst() const {
    if (this->head == nullptr) {
        throw IndexOutOfRangeException("Список пуст");
    }
    return this->head->data;
}

template<typename T>
T LinkedList<T>::GetLast() const {
    if (this->tail == nullptr) {
        throw IndexOutOfRangeException("Список пуст");
    }
    return this->tail->data;
}

template<typename T>
T LinkedList<T>::Get(int index) const {
    if (this->head == nullptr) {
        throw IndexOutOfRangeException("Список пуст");
    }
    if (index < 0 || index >= this->size) {
        throw IndexOutOfRangeException("Индекс отрицательный или больше/равен числу элементов");
    }
    Node *current = this->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template<typename T>
LinkedList<T> *LinkedList<T>::GetSubList(int startIndex, int endIndex) const {
    if (this->head == nullptr) {
        throw IndexOutOfRangeException("Список пуст");
    }
    if (startIndex < 0 || startIndex >= this->size) {
        throw IndexOutOfRangeException("");
    }
    if (endIndex < 0 || endIndex >= this->size) {
        throw IndexOutOfRangeException("");
    }
    if (endIndex < startIndex) {
        throw IndexOutOfRangeException("начальный индекс должен быть меньше конечного");
    }
    Node *current = this->head;
    for (int i = 0; i < startIndex; i++) {
        current = current->next;
    }
    LinkedList<T> *subList = new LinkedList<T>();
    for (int i = startIndex; i <= endIndex; i++) {
        subList->Append(current->data);
        current = current->next;
    }

    return subList;
}

template<typename T>
int LinkedList<T>::GetLength() const {
    return this->size;
}

template<typename T>
void LinkedList<T>::Append(T item) {
    if (this->head == nullptr) {
        this->head = new Node{item, nullptr};
        this->tail = this->head;
    } else {
        this->tail->next = new Node{item, nullptr};
        this->tail = this->tail->next;
    }
    this->size++;
}

template<typename T>
void LinkedList<T>::Prepend(T item) {
    if (this->head == nullptr) {
        this->head = new Node{item, nullptr};
        this->tail = this->head;
    } else {
        Node *current = new Node{item, this->head};
        this->head = current;
    }
    this->size++;
}

template<typename T>
void LinkedList<T>::InsertAt(T item, int index) {
    if (index < 0 || index > this->size) {
        throw IndexOutOfRangeException("индекс отрицательный или больше/равен числу элементов");
    }
    if (index == 0) {
        this->head = new Node{item, this->head};
        if (this->tail == nullptr) {
            this->tail = this->head;
        }
    } else {
        Node *current = this->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        current->next = new Node{item, current->next};
        if (current == this->tail) {
            this->tail = this->tail->next;
        }
    }
    this->size++;
}

template<typename T>
LinkedList<T> * LinkedList<T>::Concat(LinkedList<T> *list) {
    LinkedList<T> *result = new LinkedList<T>();
    Node *current = this->head;
    for (int i = 0; i < this->size; i++) {
        result->Append(current->data);
        current = current->next;
    }
    current = list->head;
    for (int i = 0; i < list->size; i++) {
        result->Append(current->data);
        current = current->next;
    }
    return result;
}
template <class T>
LinkedList<T>::~LinkedList() {
    Node* current = this->head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

#endif