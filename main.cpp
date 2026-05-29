#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <vector>
#include "dynamic_array.hpp"
#include "linked_list.hpp"
#include "array_sequence.hpp"
#include "list_sequence.hpp"
#include "map_reduce_tasks.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "deque.hpp"

template <class T>
std::ostream& operator<<(std::ostream& os, const Sequence<T>& seq) {
    os << "[";
    for (int i = 0; i < seq.GetLength(); i++) {
        if (i > 0) os << ", ";
        os << seq.Get(i);
    }
    os << "]";
    return os;
}
//Stack
template <class T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& stack) {
    os << "[";
    for (int i = 0; i < stack.GetSize(); i++) {
        if (i > 0) os << ", ";
        Stack<T> temp = stack;
        Stack<T> reversed;
        while (!temp.IsEmpty()) {
            reversed.Push(temp.Pop());
        }
        bool first = true;
        while (!reversed.IsEmpty()) {
            if (!first) os << ", ";
            os << reversed.Pop();
            first = false;
        }
        return os;
    }
    os << "]";
    return os;
}
// Queue
template <class T>
std::ostream& operator<<(std::ostream& os, const Queue<T>& queue) {
    os << "[";
    for (int i = 0; i < queue.GetSize(); i++) {
        if (i > 0) os << ", ";
        Queue<T> temp = queue;
        for (int j = 0; j < i; j++) {
            T val = temp.Dequeue();
            temp.Enqueue(val);
        }
        os << temp.Peek();
    }
    os << "]";
    return os;
}

//Deque
template <class T>
std::ostream& operator<<(std::ostream& os, const Deque<T>& deque) {
    os << "[";
    for (int i = 0; i < deque.GetSize(); i++) {
        if (i > 0) os << ", ";
        os << deque.Peek(i);
    }
    os << "]";
    return os;
}

void runAllTests();

using namespace std;

Sequence<int>* currentIntSeq = nullptr;
Stack<int>* currentStack = nullptr;
Queue<int>* currentQueue = nullptr;
Deque<int>* currentDeque = nullptr;

enum SeqType {
    ARRAY_MUTABLE,
    ARRAY_IMMUTABLE,
    LIST_MUTABLE,
    LIST_IMMUTABLE,
    STACK,
    QUEUE,
    DEQUE
};

SeqType currentSeqType = ARRAY_MUTABLE;
bool isStackMode = false;
bool isQueueMode = false;
bool isDequeMode = false;

void selectInitialType() {
    cout << "\n========================================\n";
    cout << "   ВЫБОР ТИПА ПОСЛЕДОВАТЕЛЬНОСТИ\n";
    cout << "========================================\n";
    cout << "1. MutableArraySequence   (изменяемый массив)\n";
    cout << "2. ImmutableArraySequence (неизменяемый массив)\n";
    cout << "3. MutableListSequence    (изменяемый список)\n";
    cout << "4. ImmutableListSequence  (неизменяемый список)\n";
    cout << "5. Stack                  (стек)\n";
    cout << "6. Queue                  (очередь)\n";
    cout << "7. Deque                  (дек)\n";
    cout << "==========================\n";
    cout << "Ваш выбор: ";

    int choice;
    cin >> choice;

    if (currentIntSeq != nullptr) {
        delete currentIntSeq;
        currentIntSeq = nullptr;
    }
    if (currentStack != nullptr) {
        delete currentStack;
        currentStack = nullptr;
    }
    if (currentQueue != nullptr) {
        delete currentQueue;
        currentQueue = nullptr;
    }
    if (currentDeque != nullptr) {
        delete currentDeque;
        currentDeque = nullptr;
    }

    switch (choice) {
        case 1:
            currentSeqType = ARRAY_MUTABLE;
            isStackMode = false;
            isQueueMode = false;
            isDequeMode = false;
            currentIntSeq = new MutableArraySequence<int>();
            cout << "\nСоздана пустая MutableArraySequence<int>\n";
            break;
        case 2:
            currentSeqType = ARRAY_IMMUTABLE;
            isStackMode = false;
            isQueueMode = false;
            isDequeMode = false;
            currentIntSeq = new ImmutableArraySequence<int>();
            cout << "\nСоздана пустая ImmutableArraySequence<int>\n";
            break;
        case 3:
            currentSeqType = LIST_MUTABLE;
            isStackMode = false;
            isQueueMode = false;
            isDequeMode = false;
            currentIntSeq = new MutableListSequence<int>();
            cout << "\nСоздана пустая MutableListSequence<int>\n";
            break;
        case 4:
            currentSeqType = LIST_IMMUTABLE;
            isStackMode = false;
            isQueueMode = false;
            isDequeMode = false;
            currentIntSeq = new ImmutableListSequence<int>();
            cout << "\nСоздана пустая ImmutableListSequence<int>\n";
            break;
        case 5:
            currentSeqType = STACK;
            isStackMode = true;
            isQueueMode = false;
            isDequeMode = false;
            currentStack = new Stack<int>();
            cout << "\nСоздан пустой Stack<int>\n";
            break;
        case 6:
            currentSeqType = QUEUE;
            isStackMode = false;
            isQueueMode = true;
            isDequeMode = false;
            currentQueue = new Queue<int>();
            cout << "\nСоздана пустая Queue<int>\n";
            break;
        case 7:
            currentSeqType = DEQUE;
            isStackMode = false;
            isQueueMode = false;
            isDequeMode = true;
            currentDeque = new Deque<int>();
            cout << "\nСоздан пустой Deque<int>\n";
            break;
        default:
            cout << "\nНеверный выбор! Создана последовательность по умолчанию.\n";
            currentSeqType = ARRAY_MUTABLE;
            isStackMode = false;
            isQueueMode = false;
            isDequeMode = false;
            currentIntSeq = new MutableArraySequence<int>();
    }
}

void printMenu() {
    if (isDequeMode) {
        cout << "\n========== МЕНЮ (ДЕК) ==========\n";
        cout << "1. Создать новый дек\n";
        cout << "2. Показать дек\n";
        cout << "3. PushFront (добавить в начало)\n";
        cout << "4. PushBack (добавить в конец)\n";
        cout << "5. PopFront (взять из начала)\n";
        cout << "6. PopBack (взять из конца)\n";
        cout << "7. PeekFront (посмотреть начало)\n";
        cout << "8. PeekBack (посмотреть конец)\n";
        cout << "9. Peek (посмотреть по индексу)\n";
        cout << "10. IsEmpty (проверить пустоту)\n";
        cout << "11. GetSize (размер)\n";
        cout << "12. IndexOf (поиск подпоследовательности)\n";
        cout << "13. GetSubsequence (подпоследовательность)\n";
        cout << "14. Concat (объединить с другим деком)\n";
        cout << "15. Map (применить функцию)\n";
        cout << "16. Where (фильтрация)\n";
        cout << "17. Reduce (свёртка)\n";
        cout << "18. Sort (сортировка)\n";
        cout << "19. Map-Reduce задачи\n";
        cout << "20. A-1.1: Число инверсий\n";
        cout << "21. A-3: Range [l, h]\n";
        cout << "22. Запустить все тесты\n";
        cout << "0. Выход\n";
        cout << "================================\n";
        cout << "Текущий тип: Deque\n";
        cout << "Выберите действие: ";
        return;
    }

    if (isStackMode) {
        cout << "\n========== МЕНЮ (СТЕК) ==========\n";
        cout << "1. Создать новый стек\n";
        cout << "2. Показать стек\n";
        cout << "3. Push (добавить на вершину)\n";
        cout << "4. Pop (удалить с вершины)\n";
        cout << "5. Top (посмотреть вершину)\n";
        cout << "6. IsEmpty (проверить пустоту)\n";
        cout << "7. GetSize (размер)\n";
        cout << "8. IndexOf (поиск подпоследовательности)\n";
        cout << "9. FindAllOccurrences (все вхождения)\n";
        cout << "10. Concat (объединить с другим стеком)\n";
        cout << "11. Map (применить функцию)\n";
        cout << "12. Where (фильтрация)\n";
        cout << "13. Reduce (свёртка)\n";
        cout << "14. Zip (поэлементная операция)\n";
        cout << "15. Map-Reduce задачи\n";
        cout << "16. A-1.1: Число инверсий\n";
        cout << "17. A-3: Range [l, h]\n";
        cout << "18. Запустить все тесты\n";
        cout << "0. Выход\n";
        cout << "================================\n";
        cout << "Текущий тип: Stack\n";
        cout << "Выберите действие: ";
        return;
    }

    if (isQueueMode) {
        cout << "\n========== МЕНЮ (ОЧЕРЕДЬ) ==========\n";
        cout << "1. Создать новую очередь\n";
        cout << "2. Показать очередь\n";
        cout << "3. Enqueue (добавить в конец)\n";
        cout << "4. Dequeue (взять из начала)\n";
        cout << "5. Peek (посмотреть первый)\n";
        cout << "6. IsEmpty (проверить пустоту)\n";
        cout << "7. GetSize (размер)\n";
        cout << "8. IndexOf (поиск подпоследовательности)\n";
        cout << "9. Concat (объединить с другой очередью)\n";
        cout << "10. GetSubsequence (подпоследовательность)\n";
        cout << "11. Map (применить функцию)\n";
        cout << "12. Where (фильтрация)\n";
        cout << "13. Reduce (свёртка)\n";
        cout << "14. Map-Reduce задачи\n";
        cout << "15. A-1.1: Число инверсий\n";
        cout << "16. A-3: Range [l, h]\n";
        cout << "17. Запустить все тесты\n";
        cout << "0. Выход\n";
        cout << "================================\n";
        cout << "Текущий тип: Queue\n";
        cout << "Выберите действие: ";
        return;
    }

    cout << "\n========== МЕНЮ (SEQUENCE) ==========\n";
    cout << "1. Создать новую последовательность\n";
    cout << "2. Показать последовательность\n";
    cout << "3. Append (добавить в конец)\n";
    cout << "4. Prepend (добавить в начало)\n";
    cout << "5. InsertAt (вставить по индексу)\n";
    cout << "6. Get (получить элемент)\n";
    cout << "7. GetSubsequence (подпоследовательность)\n";
    cout << "8. Concat (объединить)\n";
    cout << "9. Map\n";
    cout << "10. Where\n";
    cout << "11. Reduce\n";
    cout << "12. Zip\n";
    cout << "13. Skip\n";
    cout << "14. Take\n";
    cout << "15. Переключиться на Stack\n";
    cout << "16. Переключиться на Queue\n";
    cout << "17. Переключиться на Deque\n";
    cout << "18. Map-Reduce задачи\n";
    cout << "19. A-1.1: Число инверсий\n";
    cout << "20. A-3: Range [l, h]\n";
    cout << "21. Запустить все тесты\n";
    cout << "0. Выход\n";
    cout << "=====================================\n";
    cout << "Текущий тип: ";
    switch (currentSeqType) {
        case ARRAY_MUTABLE:   cout << "MutableArraySequence"; break;
        case ARRAY_IMMUTABLE: cout << "ImmutableArraySequence"; break;
        case LIST_MUTABLE:    cout << "MutableListSequence"; break;
        case LIST_IMMUTABLE:  cout << "ImmutableListSequence"; break;
        default:              cout << "Sequence"; break;
    }
    cout << "\nВыберите действие: ";
}

//стек через ввод с клавиатуры
void createStackInteractive() {
    cout << "\n--- Создание Stack ---\n";
    cout << "Введите элементы стека через пробел (Enter для завершения):\n";
    cout << "(первый элемент = дно, последний = вершина): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);

    if (currentStack != nullptr) {
        delete currentStack;
    }

    currentStack = new Stack<int>();

    int val;
    while (ss >> val) {
        currentStack->Push(val);
    }

    cout << "Создан стек: " << *currentStack << endl;
    cout << "Размер: " << currentStack->GetSize() << endl;
}

//очередь через ввод
void createQueueInteractive() {
    cout << "\n--- Создание Queue ---\n";
    cout << "Введите элементы очереди через пробел (Enter для завершения):\n";
    cout << "(первый элемент = начало, последний = конец): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);

    if (currentQueue != nullptr) {
        delete currentQueue;
    }

    currentQueue = new Queue<int>();

    int val;
    while (ss >> val) {
        currentQueue->Enqueue(val);
    }

    cout << "Создана очередь: " << *currentQueue << endl;
    cout << "Размер: " << currentQueue->GetSize() << endl;
}

//дек через ввод
void createDequeInteractive() {
    cout << "\n--- Создание Deque ---\n";
    cout << "Введите элементы дека через пробел (Enter для завершения):\n";
    cout << "(первый элемент = начало, последний = конец): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);

    if (currentDeque != nullptr) {
        delete currentDeque;
    }

    currentDeque = new Deque<int>();

    int val;
    while (ss >> val) {
        currentDeque->PushBack(val);
    }

    cout << "Создан дек: " << *currentDeque << endl;
    cout << "Размер: " << currentDeque->GetSize() << endl;
}

void createSequence() {
    if (isDequeMode) {
        createDequeInteractive();
        return;
    }

    if (isStackMode) {
        createStackInteractive();
        return;
    }

    if (isQueueMode) {
        createQueueInteractive();
        return;
    }

    cout << "\n--- Создание последовательности (int) ---\n";
    cout << "Выберите тип:\n";
    cout << "1. MutableArraySequence\n";
    cout << "2. ImmutableArraySequence\n";
    cout << "3. MutableListSequence\n";
    cout << "4. ImmutableListSequence\n";
    cout << "Ваш выбор: ";

    int typeChoice;
    cin >> typeChoice;

    cout << "Введите элементы через пробел (Enter для завершения): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);

    if (currentIntSeq != nullptr) {
        delete currentIntSeq;
        currentIntSeq = nullptr;
    }

    int val;
    vector<int> items;
    while (ss >> val) {
        items.push_back(val);
    }

    switch (typeChoice) {
        case 1:
            if (items.empty()) {
                currentIntSeq = new MutableArraySequence<int>();
            } else {
                currentIntSeq = new MutableArraySequence<int>(items.data(), items.size());
            }
            currentSeqType = ARRAY_MUTABLE;
            cout << "Создана MutableArraySequence\n";
            break;
        case 2:
            if (items.empty()) {
                currentIntSeq = new ImmutableArraySequence<int>();
            } else {
                currentIntSeq = new ImmutableArraySequence<int>(items.data(), items.size());
            }
            currentSeqType = ARRAY_IMMUTABLE;
            cout << "Создана ImmutableArraySequence\n";
            break;
        case 3:
            if (items.empty()) {
                currentIntSeq = new MutableListSequence<int>();
            } else {
                currentIntSeq = new MutableListSequence<int>(items.data(), items.size());
            }
            currentSeqType = LIST_MUTABLE;
            cout << "Создана MutableListSequence\n";
            break;
        case 4:
            if (items.empty()) {
                currentIntSeq = new ImmutableListSequence<int>();
            } else {
                currentIntSeq = new ImmutableListSequence<int>(items.data(), items.size());
            }
            currentSeqType = LIST_IMMUTABLE;
            cout << "Создана ImmutableListSequence\n";
            break;
        default:
            cout << "Неверный выбор!\n";
    }

    if (currentIntSeq != nullptr) {
        cout << "Текущая последовательность: " << *currentIntSeq << endl;
    }
}

void showSequence() {
    if (isDequeMode) {
        if (currentDeque == nullptr) {
            cout << "Deque не создан.\n";
            return;
        }
        cout << "Текущий Deque: " << *currentDeque << endl;
        cout << "Размер: " << currentDeque->GetSize() << endl;
        if (!currentDeque->IsEmpty()) {
            cout << "Начало (PeekFront): " << currentDeque->PeekFront() << endl;
            cout << "Конец (PeekBack): " << currentDeque->PeekBack() << endl;
        }
        return;
    }

    if (isStackMode) {
        if (currentStack == nullptr) {
            cout << "Stack не создан.\n";
            return;
        }
        cout << "Текущий Stack: " << *currentStack << endl;
        cout << "Размер: " << currentStack->GetSize() << endl;
        if (!currentStack->IsEmpty()) {
            cout << "Вершина (Top): " << currentStack->Top() << endl;
        }
        return;
    }

    if (isQueueMode) {
        if (currentQueue == nullptr) {
            cout << "Queue не создана.\n";
            return;
        }
        cout << "Текущая Queue: " << *currentQueue << endl;
        cout << "Размер: " << currentQueue->GetSize() << endl;
        if (!currentQueue->IsEmpty()) {
            cout << "Первый (Peek): " << currentQueue->Peek() << endl;
        }
        return;
    }

    if (currentIntSeq == nullptr) {
        cout << "Последовательность не создана.\n";
        return;
    }
    cout << "Текущая последовательность: " << *currentIntSeq << endl;
    cout << "Длина: " << currentIntSeq->GetLength() << endl;
    if (currentIntSeq->GetLength() > 0) {
        cout << "Первый элемент: " << currentIntSeq->GetFirst() << endl;
        cout << "Последний элемент: " << currentIntSeq->GetLast() << endl;
    }
}

// дек
void dequePushFront() {
    if (currentDeque == nullptr) {
        cout << "Deque не создан.\n";
        return;
    }
    int val;
    cout << "Введите значение для PushFront: ";
    cin >> val;
    currentDeque->PushFront(val);
    cout << "Результат: " << *currentDeque << endl;
}

void dequePushBack() {
    if (currentDeque == nullptr) {
        cout << "Deque не создан.\n";
        return;
    }
    int val;
    cout << "Введите значение для PushBack: ";
    cin >> val;
    currentDeque->PushBack(val);
    cout << "Результат: " << *currentDeque << endl;
}

void dequePopFront() {
    if (currentDeque == nullptr) {
        cout << "Deque не создан.\n";
        return;
    }
    try {
        int val = currentDeque->PopFront();
        cout << "Извлечён элемент (из начала): " << val << endl;
        cout << "Результат: " << *currentDeque << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void dequePopBack() {
    if (currentDeque == nullptr) {
        cout << "Deque не создан.\n";
        return;
    }
    try {
        int val = currentDeque->PopBack();
        cout << "Извлечён элемент (из конца): " << val << endl;
        cout << "Результат: " << *currentDeque << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void dequePeekFront() {
    if (currentDeque == nullptr) {
        cout << "Deque не создан.\n";
        return;
    }
    try {
        cout << "Начало (PeekFront): " << currentDeque->PeekFront() << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void dequePeekBack() {
    if (currentDeque == nullptr) {
        cout << "Deque не создан.\n";
        return;
    }
    try {
        cout << "Конец (PeekBack): " << currentDeque->PeekBack() << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void dequePeek() {
    if (currentDeque == nullptr) {
        cout << "Deque не создан.\n";
        return;
    }
    int index;
    cout << "Введите индекс: ";
    cin >> index;
    try {
        cout << "Элемент[" << index << "] = " << currentDeque->Peek(index) << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void dequeIsEmpty() {
    if (currentDeque == nullptr) {
        cout << "Deque не создан.\n";
        return;
    }
    cout << "IsEmpty: " << (currentDeque->IsEmpty() ? "true" : "false") << endl;
}

void dequeGetSize() {
    if (currentDeque == nullptr) {
        cout << "Deque не создан.\n";
        return;
    }
    cout << "GetSize: " << currentDeque->GetSize() << endl;
}

void dequeIndexOf() {
    if (currentDeque == nullptr) {
        cout << "Deque не создан.\n";
        return;
    }
    cout << "Введите подпоследовательность для поиска (через пробел):\n";
    cout << "(первый элемент = начало, последний = конец): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);
    Deque<int> subseq;
    int val;
    while (ss >> val) {
        subseq.PushBack(val);
    }
    int idx = currentDeque->IndexOf(subseq);
    cout << "Индекс первого вхождения: " << idx << endl;
}

void dequeGetSubsequence() {
    if (currentDeque == nullptr) {
        cout << "Deque не создан.\n";
        return;
    }
    int start, end;
    cout << "Введите startIndex: ";
    cin >> start;
    cout << "Введите endIndex: ";
    cin >> end;

    try {
        Deque<int>* sub = currentDeque->GetSubsequence(start, end);
        cout << "Подпоследовательность: " << *sub << endl;
        delete sub;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void dequeConcat() {
    if (currentDeque == nullptr) {
        cout << "Deque не создан.\n";
        return;
    }
    cout << "Введите элементы второго дека (через пробел):\n";
    cout << "(первый элемент = начало, последний = конец): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);
    Deque<int> other;
    int val;
    while (ss >> val) {
        other.PushBack(val);
    }
    Deque<int>* result = currentDeque->Concat(&other);
    cout << "Результат Concat: " << *result << endl;
    delete result;
}

void dequeMap() {
    if (currentDeque == nullptr) {
        cout << "Deque не создан.\n";
        return;
    }
    cout << "Выберите функцию Map:\n";
    cout << "1. Умножить на число\n";
    cout << "2. Прибавить число\n";
    cout << "3. Возвести в квадрат\n";
    int choice;
    cin >> choice;

    int arg;
    function<int(int)> func;
    switch (choice) {
        case 1:
            cout << "Введите множитель: ";
            cin >> arg;
            func = [arg](int x) { return x * arg; };
            break;
        case 2:
            cout << "Введите слагаемое: ";
            cin >> arg;
            func = [arg](int x) { return x + arg; };
            break;
        case 3:
            func = [](int x) { return x * x; };
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }
    Deque<int>* result = currentDeque->Map(func);
    cout << "Результат Map: " << *result << endl;
    delete result;
}

void dequeWhere() {
    if (currentDeque == nullptr) {
        cout << "Deque не создан.\n";
        return;
    }
    cout << "Выберите фильтр:\n";
    cout << "1. > N\n";
    cout << "2. < N\n";
    cout << "3. Чётные\n";
    cout << "4. Нечётные\n";
    int choice;
    cin >> choice;

    function<bool(int)> pred;
    int threshold;
    switch (choice) {
        case 1:
            cout << "Введите N: ";
            cin >> threshold;
            pred = [threshold](int x) { return x > threshold; };
            break;
        case 2:
            cout << "Введите N: ";
            cin >> threshold;
            pred = [threshold](int x) { return x < threshold; };
            break;
        case 3:
            pred = [](int x) { return x % 2 == 0; };
            break;
        case 4:
            pred = [](int x) { return x % 2 != 0; };
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }
    Deque<int>* result = currentDeque->Where(pred);
    cout << "Результат Where: " << *result << endl;
    delete result;
}

void dequeReduce() {
    if (currentDeque == nullptr) {
        cout << "Deque не создан.\n";
        return;
    }
    cout << "Выберите операцию Reduce:\n";
    cout << "1. Сумма\n";
    cout << "2. Произведение\n";
    cout << "3. Максимум\n";
    cout << "4. Минимум\n";
    int choice;
    cin >> choice;

    function<int(int, int)> func;
    int init;
    switch (choice) {
        case 1:
            func = [](int a, int b) { return a + b; };
            init = 0;
            break;
        case 2:
            func = [](int a, int b) { return a * b; };
            init = 1;
            break;
        case 3:
            func = [](int a, int b) { return a > b ? a : b; };
            init = currentDeque->GetSize() > 0 ? currentDeque->PeekFront() : 0;
            break;
        case 4:
            func = [](int a, int b) { return a < b ? a : b; };
            init = currentDeque->GetSize() > 0 ? currentDeque->PeekFront() : 0;
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }
    int result = currentDeque->Reduce(func, init);
    cout << "Результат Reduce: " << result << endl;
}

void dequeSort() {
    if (currentDeque == nullptr) {
        cout << "Deque не создан.\n";
        return;
    }
    currentDeque->Sort();
    cout << "Результат Sort: " << *currentDeque << endl;
}

// Операции стека
void stackPush() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    int val;
    cout << "Введите значение для Push: ";
    cin >> val;
    currentStack->Push(val);
    cout << "Результат: " << *currentStack << endl;
}

void stackPop() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    try {
        int val = currentStack->Pop();
        cout << "Удалён элемент: " << val << endl;
        cout << "Результат: " << *currentStack << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void stackTop() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    try {
        cout << "Вершина (Top): " << currentStack->Top() << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void stackIsEmpty() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    cout << "IsEmpty: " << (currentStack->IsEmpty() ? "true" : "false") << endl;
}

void stackGetSize() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    cout << "GetSize: " << currentStack->GetSize() << endl;
}

void stackIndexOf() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    cout << "Введите подпоследовательность для поиска (через пробел):\n";
    cout << "(первый элемент = дно, последний = вершина): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);
    Stack<int> subseq;
    int val;
    while (ss >> val) {
        subseq.Push(val);
    }
    int idx = currentStack->IndexOf(subseq);
    cout << "Индекс первого вхождения: " << idx << endl;
}

void stackFindAllOccurrences() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    cout << "Введите подпоследовательность для поиска (через пробел):\n";
    cout << "(первый элемент = дно, последний = вершина): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);
    Stack<int> subseq;
    int val;
    while (ss >> val) {
        subseq.Push(val);
    }
    Stack<int>* occurrences = currentStack->FindAllOccurrences(subseq);
    cout << "Индексы вхождений: " << *occurrences << endl;
    delete occurrences;
}

void stackConcat() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    cout << "Введите элементы второго стека (через пробел):\n";
    cout << "(первый элемент = дно, последний = вершина): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);
    Stack<int> other;
    int val;
    while (ss >> val) {
        other.Push(val);
    }
    Stack<int>* result = currentStack->Concat(&other);
    cout << "Результат Concat: " << *result << endl;
    delete result;
}

void stackMap() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    cout << "Выберите функцию Map:\n";
    cout << "1. Умножить на число\n";
    cout << "2. Прибавить число\n";
    cout << "3. Возвести в квадрат\n";
    int choice;
    cin >> choice;

    int arg;
    function<int(int)> func;
    switch (choice) {
        case 1:
            cout << "Введите множитель: ";
            cin >> arg;
            func = [arg](int x) { return x * arg; };
            break;
        case 2:
            cout << "Введите слагаемое: ";
            cin >> arg;
            func = [arg](int x) { return x + arg; };
            break;
        case 3:
            func = [](int x) { return x * x; };
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }
    Stack<int>* result = currentStack->Map(func);
    cout << "Результат Map: " << *result << endl;
    delete result;
}

void stackWhere() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    cout << "Выберите фильтр:\n";
    cout << "1. > N\n";
    cout << "2. < N\n";
    cout << "3. Чётные\n";
    cout << "4. Нечётные\n";
    int choice;
    cin >> choice;

    function<bool(int)> pred;
    int threshold;
    switch (choice) {
        case 1:
            cout << "Введите N: ";
            cin >> threshold;
            pred = [threshold](int x) { return x > threshold; };
            break;
        case 2:
            cout << "Введите N: ";
            cin >> threshold;
            pred = [threshold](int x) { return x < threshold; };
            break;
        case 3:
            pred = [](int x) { return x % 2 == 0; };
            break;
        case 4:
            pred = [](int x) { return x % 2 != 0; };
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }
    Stack<int>* result = currentStack->Where(pred);
    cout << "Результат Where: " << *result << endl;
    delete result;
}

void stackReduce() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    cout << "Выберите операцию Reduce:\n";
    cout << "1. Сумма\n";
    cout << "2. Произведение\n";
    cout << "3. Максимум\n";
    cout << "4. Минимум\n";
    int choice;
    cin >> choice;

    function<int(int, int)> func;
    int init;
    switch (choice) {
        case 1:
            func = [](int a, int b) { return a + b; };
            init = 0;
            break;
        case 2:
            func = [](int a, int b) { return a * b; };
            init = 1;
            break;
        case 3:
            func = [](int a, int b) { return a > b ? a : b; };
            init = currentStack->GetSize() > 0 ? currentStack->Top() : 0;
            break;
        case 4:
            func = [](int a, int b) { return a < b ? a : b; };
            init = currentStack->GetSize() > 0 ? currentStack->Top() : 0;
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }
    int result = currentStack->Reduce(func, init);
    cout << "Результат Reduce: " << result << endl;
}

void stackZip() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    cout << "Введите элементы второго стека (через пробел):\n";
    cout << "(первый элемент = дно, последний = вершина): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);
    Stack<int> other;
    int val;
    while (ss >> val) {
        other.Push(val);
    }
    cout << "Выберите операцию Zip:\n";
    cout << "1. Сложение\n";
    cout << "2. Вычитание (first - second)\n";
    cout << "3. Умножение\n";
    int choice;
    cin >> choice;

    function<int(int, int)> func;
    switch (choice) {
        case 1:
            func = [](int a, int b) { return a + b; };
            break;
        case 2:
            func = [](int a, int b) { return a - b; };
            break;
        case 3:
            func = [](int a, int b) { return a * b; };
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }
    Stack<int>* result = currentStack->Zip(&other, func);
    cout << "Результат Zip: " << *result << endl;
    delete result;
}

// Операции очереди
void queueEnqueue() {
    if (currentQueue == nullptr) {
        cout << "Queue не создана.\n";
        return;
    }
    int val;
    cout << "Введите значение для Enqueue: ";
    cin >> val;
    currentQueue->Enqueue(val);
    cout << "Результат: " << *currentQueue << endl;
}

void queueDequeue() {
    if (currentQueue == nullptr) {
        cout << "Queue не создана.\n";
        return;
    }
    try {
        int val = currentQueue->Dequeue();
        cout << "Извлечён элемент: " << val << endl;
        cout << "Результат: " << *currentQueue << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void queuePeek() {
    if (currentQueue == nullptr) {
        cout << "Queue не создана.\n";
        return;
    }
    try {
        cout << "Первый (Peek): " << currentQueue->Peek() << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void queueIsEmpty() {
    if (currentQueue == nullptr) {
        cout << "Queue не создана.\n";
        return;
    }
    cout << "IsEmpty: " << (currentQueue->IsEmpty() ? "true" : "false") << endl;
}

void queueGetSize() {
    if (currentQueue == nullptr) {
        cout << "Queue не создана.\n";
        return;
    }
    cout << "GetSize: " << currentQueue->GetSize() << endl;
}

void queueIndexOf() {
    if (currentQueue == nullptr) {
        cout << "Queue не создана.\n";
        return;
    }
    cout << "Введите подпоследовательность для поиска (через пробел):\n";
    cout << "(первый элемент = начало, последний = конец): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);
    Queue<int> subseq;
    int val;
    while (ss >> val) {
        subseq.Enqueue(val);
    }
    int idx = currentQueue->IndexOf(subseq);
    cout << "Индекс первого вхождения: " << idx << endl;
}

void queueConcat() {
    if (currentQueue == nullptr) {
        cout << "Queue не создана.\n";
        return;
    }
    cout << "Введите элементы второй очереди (через пробел):\n";
    cout << "(первый элемент = начало, последний = конец): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);
    Queue<int> other;
    int val;
    while (ss >> val) {
        other.Enqueue(val);
    }
    Queue<int>* result = currentQueue->Concat(&other);
    cout << "Результат Concat: " << *result << endl;
    delete result;
}

void queueGetSubsequence() {
    if (currentQueue == nullptr) {
        cout << "Queue не создана.\n";
        return;
    }
    int start, end;
    cout << "Введите startIndex: ";
    cin >> start;
    cout << "Введите endIndex: ";
    cin >> end;

    try {
        Queue<int>* sub = currentQueue->GetSubsequence(start, end);
        cout << "Подпоследовательность: " << *sub << endl;
        delete sub;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void queueMap() {
    if (currentQueue == nullptr) {
        cout << "Queue не создана.\n";
        return;
    }
    cout << "Выберите функцию Map:\n";
    cout << "1. Умножить на число\n";
    cout << "2. Прибавить число\n";
    cout << "3. Возвести в квадрат\n";
    int choice;
    cin >> choice;

    int arg;
    function<int(int)> func;
    switch (choice) {
        case 1:
            cout << "Введите множитель: ";
            cin >> arg;
            func = [arg](int x) { return x * arg; };
            break;
        case 2:
            cout << "Введите слагаемое: ";
            cin >> arg;
            func = [arg](int x) { return x + arg; };
            break;
        case 3:
            func = [](int x) { return x * x; };
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }
    Queue<int>* result = currentQueue->Map(func);
    cout << "Результат Map: " << *result << endl;
    delete result;
}

void queueWhere() {
    if (currentQueue == nullptr) {
        cout << "Queue не создана.\n";
        return;
    }
    cout << "Выберите фильтр:\n";
    cout << "1. > N\n";
    cout << "2. < N\n";
    cout << "3. Чётные\n";
    cout << "4. Нечётные\n";
    int choice;
    cin >> choice;

    function<bool(int)> pred;
    int threshold;
    switch (choice) {
        case 1:
            cout << "Введите N: ";
            cin >> threshold;
            pred = [threshold](int x) { return x > threshold; };
            break;
        case 2:
            cout << "Введите N: ";
            cin >> threshold;
            pred = [threshold](int x) { return x < threshold; };
            break;
        case 3:
            pred = [](int x) { return x % 2 == 0; };
            break;
        case 4:
            pred = [](int x) { return x % 2 != 0; };
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }
    Queue<int>* result = currentQueue->Where(pred);
    cout << "Результат Where: " << *result << endl;
    delete result;
}

void queueReduce() {
    if (currentQueue == nullptr) {
        cout << "Queue не создана.\n";
        return;
    }
    cout << "Выберите операцию Reduce:\n";
    cout << "1. Сумма\n";
    cout << "2. Произведение\n";
    cout << "3. Максимум\n";
    cout << "4. Минимум\n";
    int choice;
    cin >> choice;

    function<int(int, int)> func;
    int init;
    switch (choice) {
        case 1:
            func = [](int a, int b) { return a + b; };
            init = 0;
            break;
        case 2:
            func = [](int a, int b) { return a * b; };
            init = 1;
            break;
        case 3:
            func = [](int a, int b) { return a > b ? a : b; };
            init = currentQueue->GetSize() > 0 ? currentQueue->Peek() : 0;
            break;
        case 4:
            func = [](int a, int b) { return a < b ? a : b; };
            init = currentQueue->GetSize() > 0 ? currentQueue->Peek() : 0;
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }
    int result = currentQueue->Reduce(func, init);
    cout << "Результат Reduce: " << result << endl;
}

// Операции Sequence
void appendElement() {
    if (currentIntSeq == nullptr) {
        cout << "Последовательность не создана.\n";
        return;
    }
    int val;
    cout << "Введите значение для добавления в конец: ";
    cin >> val;

    Sequence<int>* newSeq = currentIntSeq->Append(val);
    if (newSeq != currentIntSeq) {
        delete currentIntSeq;
        currentIntSeq = newSeq;
    }
    cout << "Результат: " << *currentIntSeq << endl;
}

void prependElement() {
    if (currentIntSeq == nullptr) {
        cout << "Последовательность не создана.\n";
        return;
    }
    int val;
    cout << "Введите значение для добавления в начало: ";
    cin >> val;

    Sequence<int>* newSeq = currentIntSeq->Prepend(val);
    if (newSeq != currentIntSeq) {
        delete currentIntSeq;
        currentIntSeq = newSeq;
    }
    cout << "Результат: " << *currentIntSeq << endl;
}

void insertAt() {
    if (currentIntSeq == nullptr) {
        cout << "Последовательность не создана.\n";
        return;
    }
    int val, index;
    cout << "Введите индекс: ";
    cin >> index;
    cout << "Введите значение: ";
    cin >> val;

    try {
        Sequence<int>* newSeq = currentIntSeq->InsertAt(val, index);
        if (newSeq != currentIntSeq) {
            delete currentIntSeq;
            currentIntSeq = newSeq;
        }
        cout << "Результат: " << *currentIntSeq << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void getElement() {
    if (currentIntSeq == nullptr) {
        cout << "Последовательность не создана.\n";
        return;
    }
    int index;
    cout << "Введите индекс: ";
    cin >> index;

    try {
        cout << "Элемент[" << index << "] = " << currentIntSeq->Get(index) << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void getSubsequence() {
    if (currentIntSeq == nullptr) {
        cout << "Последовательность не создана.\n";
        return;
    }
    int start, end;
    cout << "Введите startIndex: ";
    cin >> start;
    cout << "Введите endIndex: ";
    cin >> end;

    try {
        Sequence<int>* sub = currentIntSeq->GetSubsequence(start, end);
        cout << "Подпоследовательность: " << *sub << endl;
        delete sub;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void concatSequence() {
    if (currentIntSeq == nullptr) {
        cout << "Последовательность не создана.\n";
        return;
    }

    cout << "Создайте последовательность для объединения:\n";
    cout << "Введите элементы через пробел: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);

    vector<int> items;
    int val;
    while (ss >> val) {
        items.push_back(val);
    }

    Sequence<int>* other = nullptr;
    cout << "Выберите тип для второй последовательности:\n";
    cout << "1. MutableArraySequence\n2. ImmutableArraySequence\n3. MutableListSequence\n4. ImmutableListSequence\n";
    int typeChoice;
    cin >> typeChoice;

    switch (typeChoice) {
        case 1:
            other = new MutableArraySequence<int>(items.data(), items.size());
            break;
        case 2:
            other = new ImmutableArraySequence<int>(items.data(), items.size());
            break;
        case 3:
            other = new MutableListSequence<int>(items.data(), items.size());
            break;
        case 4:
            other = new ImmutableListSequence<int>(items.data(), items.size());
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }

    try {
        Sequence<int>* result = currentIntSeq->Concat(other);
        if (result != currentIntSeq) {
            delete currentIntSeq;
            currentIntSeq = result;
        }
        cout << "Результат объединения: " << *currentIntSeq << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    delete other;
}

void mapOperation() {
    if (currentIntSeq == nullptr) {
        cout << "Последовательность не создана.\n";
        return;
    }

    cout << "Выберите функцию Map:\n";
    cout << "1. Умножить на число\n";
    cout << "2. Прибавить число\n";
    cout << "3. Возвести в квадрат\n";
    cout << "4. Пользовательская функция (лямбда)\n";
    int choice;
    cin >> choice;

    function<int(int)> func;
    int arg;

    switch (choice) {
        case 1:
            cout << "Введите множитель: ";
            cin >> arg;
            func = [arg](int x) { return x * arg; };
            break;
        case 2:
            cout << "Введите слагаемое: ";
            cin >> arg;
            func = [arg](int x) { return x + arg; };
            break;
        case 3:
            func = [](int x) { return x * x; };
            break;
        case 4:
            cout << "Введите лямбда-выражение (будет использована x*2+1): ";
            func = [](int x) { return x * 2 + 1; };
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }

    Sequence<int>* result = currentIntSeq->Map(func);
    cout << "Результат Map: " << *result << endl;
    delete result;
}

void whereOperation() {
    if (currentIntSeq == nullptr) {
        cout << "Последовательность не создана.\n";
        return;
    }

    cout << "Выберите фильтр:\n";
    cout << "1. > N\n";
    cout << "2. < N\n";
    cout << "3. == N\n";
    cout << "4. Чётные\n";
    cout << "5. Нечётные\n";
    int choice;
    cin >> choice;

    function<bool(int)> pred;
    int arg;

    switch (choice) {
        case 1:
            cout << "Введите N: ";
            cin >> arg;
            pred = [arg](int x) { return x > arg; };
            break;
        case 2:
            cout << "Введите N: ";
            cin >> arg;
            pred = [arg](int x) { return x < arg; };
            break;
        case 3:
            cout << "Введите N: ";
            cin >> arg;
            pred = [arg](int x) { return x == arg; };
            break;
        case 4:
            pred = [](int x) { return x % 2 == 0; };
            break;
        case 5:
            pred = [](int x) { return x % 2 != 0; };
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }

    Sequence<int>* result = currentIntSeq->Where(pred);
    cout << "Результат Where: " << *result << endl;
    delete result;
}

void reduceOperation() {
    if (currentIntSeq == nullptr) {
        cout << "Последовательность не создана.\n";
        return;
    }

    cout << "Выберите операцию Reduce:\n";
    cout << "1. Сумма\n";
    cout << "2. Произведение\n";
    cout << "3. Максимум\n";
    cout << "4. Минимум\n";
    int choice;
    cin >> choice;

    function<int(int, int)> func;
    int init;

    switch (choice) {
        case 1:
            func = [](int a, int b) { return a + b; };
            init = 0;
            break;
        case 2:
            func = [](int a, int b) { return a * b; };
            init = 1;
            break;
        case 3:
            func = [](int a, int b) { return a > b ? a : b; };
            init = currentIntSeq->GetLength() > 0 ? currentIntSeq->Get(0) : 0;
            break;
        case 4:
            func = [](int a, int b) { return a < b ? a : b; };
            init = currentIntSeq->GetLength() > 0 ? currentIntSeq->Get(0) : 0;
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }

    int result = currentIntSeq->Reduce(func, init);
    cout << "Результат Reduce: " << result << endl;
}

void zipOperation() {
    if (currentIntSeq == nullptr) {
        cout << "Текущая последовательность не создана.\n";
        return;
    }

    cout << "Введите элементы второй последовательности через пробел: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);

    vector<int> items;
    int val;
    while (ss >> val) {
        items.push_back(val);
    }

    MutableArraySequence<int> other(items.data(), items.size());

    cout << "Выберите операцию Zip:\n";
    cout << "1. Сложение\n";
    cout << "2. Вычитание (first - second)\n";
    cout << "3. Умножение\n";
    int choice;
    cin >> choice;

    function<int(int, int)> func;
    switch (choice) {
        case 1:
            func = [](int a, int b) { return a + b; };
            break;
        case 2:
            func = [](int a, int b) { return a - b; };
            break;
        case 3:
            func = [](int a, int b) { return a * b; };
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }

    Sequence<int>* result = currentIntSeq->Zip(&other, func);
    cout << "Результат Zip: " << *result << endl;
    delete result;
}

void skipOperation() {
    if (currentIntSeq == nullptr) {
        cout << "Последовательность не создана.\n";
        return;
    }
    int n;
    cout << "Сколько элементов пропустить? ";
    cin >> n;
    Sequence<int>* result = currentIntSeq->Skip(n);
    cout << "Результат Skip(" << n << "): " << *result << endl;
    delete result;
}

void takeOperation() {
    if (currentIntSeq == nullptr) {
        cout << "Последовательность не создана.\n";
        return;
    }
    int n;
    cout << "Сколько элементов взять? ";
    cin >> n;
    Sequence<int>* result = currentIntSeq->Take(n);
    cout << "Результат Take(" << n << "): " << *result << endl;
    delete result;
}

void switchToStack() {
    isStackMode = true;
    isQueueMode = false;
    isDequeMode = false;
    currentSeqType = STACK;
    if (currentStack == nullptr) {
        currentStack = new Stack<int>();
    }
    cout << "\nПереключено на Stack\n";
}

void switchToQueue() {
    isStackMode = false;
    isQueueMode = true;
    isDequeMode = false;
    currentSeqType = QUEUE;
    if (currentQueue == nullptr) {
        currentQueue = new Queue<int>();
    }
    cout << "\nПереключено на Queue\n";
}

void switchToDeque() {
    isStackMode = false;
    isQueueMode = false;
    isDequeMode = true;
    currentSeqType = DEQUE;
    if (currentDeque == nullptr) {
        currentDeque = new Deque<int>();
    }
    cout << "\nПереключено на Deque\n";
}

// Вспомогательные функции для Map-Reduce
MutableArraySequence<int>* stackToSequence(const Stack<int>* stack) {
    MutableArraySequence<int>* seq = new MutableArraySequence<int>();
    Stack<int> tempCopy;
    Stack<int> reversed;
    Stack<int> sCopy;
    Stack<int> temp;
    for (int i = 0; i < stack->GetSize(); i++) {
        sCopy.Push(stack->Top());
    }
    while (!sCopy.IsEmpty()) {
        temp.Push(sCopy.Pop());
    }
    while (!temp.IsEmpty()) {
        int val = temp.Pop();
        tempCopy.Push(val);
    }
    while (!tempCopy.IsEmpty()) {
        reversed.Push(tempCopy.Pop());
    }
    while (!reversed.IsEmpty()) {
        int val = reversed.Pop();
        seq->Append(val);
    }
    return seq;
}

MutableArraySequence<int>* queueToSequence(const Queue<int>* queue) {
    MutableArraySequence<int>* seq = new MutableArraySequence<int>();
    Queue<int> tempCopy;
    Queue<int> temp;
    Queue<int> qCopy;
    for (int i = 0; i < queue->GetSize(); i++) {
        qCopy.Enqueue(queue->Peek());
    }
    while (!qCopy.IsEmpty()) {
        temp.Enqueue(qCopy.Dequeue());
    }
    while (!temp.IsEmpty()) {
        int val = temp.Dequeue();
        tempCopy.Enqueue(val);
    }
    while (!tempCopy.IsEmpty()) {
        seq->Append(tempCopy.Dequeue());
    }
    return seq;
}

MutableArraySequence<int>* dequeToSequence(const Deque<int>* deque) {
    MutableArraySequence<int>* seq = new MutableArraySequence<int>();
    for (int i = 0; i < deque->GetSize(); i++) {
        seq->Append(deque->Peek(i));
    }
    return seq;
}

void mapReduceTasks() {
    if (isDequeMode) {
        if (currentDeque == nullptr) {
            cout << "Deque не создан.\n";
            return;
        }

        cout << "\n--- Map-Reduce задачи для Deque ---\n";
        cout << "1. (min, max, avg) за 1 проход\n";
        cout << "2. Медиана\n";
        cout << "3. Список всех префиксов\n";
        cout << "4. Список всех постфиксов\n";
        cout << "5. Поэлементная сумма с отражением\n";
        cout << "Выберите задачу: ";

        int choice;
        cin >> choice;

        Sequence<int>* seq = dequeToSequence(currentDeque);

        try {
            switch (choice) {
                case 1: {
                    auto result = computeMinMaxAvg(seq);
                    cout << "min = " << get<0>(result)
                         << ", max = " << get<1>(result)
                         << ", avg = " << get<2>(result) << endl;
                    break;
                }
                case 2: {
                    double median = computeMedian(seq);
                    cout << "Медиана = " << median << endl;
                    break;
                }
                case 3: {
                    Sequence<Sequence<int>*>* prefixes = computePrefixes(seq);
                    cout << "Префиксы:\n";
                    for (int i = 0; i < prefixes->GetLength(); i++) {
                        cout << "  " << *(prefixes->Get(i)) << endl;
                    }
                    for (int i = 0; i < prefixes->GetLength(); i++) {
                        delete prefixes->Get(i);
                    }
                    delete prefixes;
                    break;
                }
                case 4: {
                    Sequence<Sequence<int>*>* suffixes = computeSuffixes(seq);
                    cout << "Постфиксы:\n";
                    for (int i = 0; i < suffixes->GetLength(); i++) {
                        cout << "  " << *(suffixes->Get(i)) << endl;
                    }
                    for (int i = 0; i < suffixes->GetLength(); i++) {
                        delete suffixes->Get(i);
                    }
                    delete suffixes;
                    break;
                }
                case 5: {
                    Sequence<int>* result = computeMirrorSum(seq);
                    cout << "Зеркальная сумма: " << *result << endl;
                    delete result;
                    break;
                }
                default:
                    cout << "Неверный выбор!\n";
            }
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }

        delete seq;
        return;
    }

    if (isStackMode) {
        if (currentStack == nullptr) {
            cout << "Stack не создан.\n";
            return;
        }

        cout << "\n--- Map-Reduce задачи для Stack ---\n";
        cout << "1. (min, max, avg) за 1 проход\n";
        cout << "2. Медиана\n";
        cout << "3. Список всех префиксов\n";
        cout << "4. Список всех постфиксов\n";
        cout << "5. Поэлементная сумма с отражением\n";
        cout << "Выберите задачу: ";

        int choice;
        cin >> choice;

        Sequence<int>* seq = stackToSequence(currentStack);

        try {
            switch (choice) {
                case 1: {
                    auto result = computeMinMaxAvg(seq);
                    cout << "min = " << get<0>(result)
                         << ", max = " << get<1>(result)
                         << ", avg = " << get<2>(result) << endl;
                    break;
                }
                case 2: {
                    double median = computeMedian(seq);
                    cout << "Медиана = " << median << endl;
                    break;
                }
                case 3: {
                    Sequence<Sequence<int>*>* prefixes = computePrefixes(seq);
                    cout << "Префиксы:\n";
                    for (int i = 0; i < prefixes->GetLength(); i++) {
                        cout << "  " << *(prefixes->Get(i)) << endl;
                    }
                    for (int i = 0; i < prefixes->GetLength(); i++) {
                        delete prefixes->Get(i);
                    }
                    delete prefixes;
                    break;
                }
                case 4: {
                    Sequence<Sequence<int>*>* suffixes = computeSuffixes(seq);
                    cout << "Постфиксы:\n";
                    for (int i = 0; i < suffixes->GetLength(); i++) {
                        cout << "  " << *(suffixes->Get(i)) << endl;
                    }
                    for (int i = 0; i < suffixes->GetLength(); i++) {
                        delete suffixes->Get(i);
                    }
                    delete suffixes;
                    break;
                }
                case 5: {
                    Sequence<int>* result = computeMirrorSum(seq);
                    cout << "Зеркальная сумма: " << *result << endl;
                    delete result;
                    break;
                }
                default:
                    cout << "Неверный выбор!\n";
            }
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }

        delete seq;
        return;
    }

    if (isQueueMode) {
        if (currentQueue == nullptr) {
            cout << "Queue не создана.\n";
            return;
        }

        cout << "\n--- Map-Reduce задачи для Queue ---\n";
        cout << "1. (min, max, avg) за 1 проход\n";
        cout << "2. Медиана\n";
        cout << "3. Список всех префиксов\n";
        cout << "4. Список всех постфиксов\n";
        cout << "5. Поэлементная сумма с отражением\n";
        cout << "Выберите задачу: ";

        int choice;
        cin >> choice;

        Sequence<int>* seq = queueToSequence(currentQueue);

        try {
            switch (choice) {
                case 1: {
                    auto result = computeMinMaxAvg(seq);
                    cout << "min = " << get<0>(result)
                         << ", max = " << get<1>(result)
                         << ", avg = " << get<2>(result) << endl;
                    break;
                }
                case 2: {
                    double median = computeMedian(seq);
                    cout << "Медиана = " << median << endl;
                    break;
                }
                case 3: {
                    Sequence<Sequence<int>*>* prefixes = computePrefixes(seq);
                    cout << "Префиксы:\n";
                    for (int i = 0; i < prefixes->GetLength(); i++) {
                        cout << "  " << *(prefixes->Get(i)) << endl;
                    }
                    for (int i = 0; i < prefixes->GetLength(); i++) {
                        delete prefixes->Get(i);
                    }
                    delete prefixes;
                    break;
                }
                case 4: {
                    Sequence<Sequence<int>*>* suffixes = computeSuffixes(seq);
                    cout << "Постфиксы:\n";
                    for (int i = 0; i < suffixes->GetLength(); i++) {
                        cout << "  " << *(suffixes->Get(i)) << endl;
                    }
                    for (int i = 0; i < suffixes->GetLength(); i++) {
                        delete suffixes->Get(i);
                    }
                    delete suffixes;
                    break;
                }
                case 5: {
                    Sequence<int>* result = computeMirrorSum(seq);
                    cout << "Зеркальная сумма: " << *result << endl;
                    delete result;
                    break;
                }
                default:
                    cout << "Неверный выбор!\n";
            }
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }

        delete seq;
        return;
    }

    if (currentIntSeq == nullptr) {
        cout << "Последовательность не создана. Сначала создайте последовательность.\n";
        return;
    }

    cout << "\n--- Map-Reduce задачи (П-задачи) ---\n";
    cout << "1. (min, max, avg) за 1 проход\n";
    cout << "2. Медиана\n";
    cout << "3. Список всех префиксов\n";
    cout << "4. Список всех постфиксов\n";
    cout << "5. Поэлементная сумма с отражением\n";
    cout << "Выберите задачу: ";

    int choice;
    cin >> choice;

    try {
        switch (choice) {
            case 1: {
                auto result = computeMinMaxAvg(currentIntSeq);
                cout << "min = " << get<0>(result)
                     << ", max = " << get<1>(result)
                     << ", avg = " << get<2>(result) << endl;
                break;
            }
            case 2: {
                double median = computeMedian(currentIntSeq);
                cout << "Медиана = " << median << endl;
                break;
            }
            case 3: {
                Sequence<Sequence<int>*>* prefixes = computePrefixes(currentIntSeq);
                cout << "Префиксы:\n";
                for (int i = 0; i < prefixes->GetLength(); i++) {
                    cout << "  " << *(prefixes->Get(i)) << endl;
                }
                for (int i = 0; i < prefixes->GetLength(); i++) {
                    delete prefixes->Get(i);
                }
                delete prefixes;
                break;
            }
            case 4: {
                Sequence<Sequence<int>*>* suffixes = computeSuffixes(currentIntSeq);
                cout << "Постфиксы:\n";
                for (int i = 0; i < suffixes->GetLength(); i++) {
                    cout << "  " << *(suffixes->Get(i)) << endl;
                }
                for (int i = 0; i < suffixes->GetLength(); i++) {
                    delete suffixes->Get(i);
                }
                delete suffixes;
                break;
            }
            case 5: {
                Sequence<int>* result = computeMirrorSum(currentIntSeq);
                cout << "Зеркальная сумма: " << *result << endl;
                delete result;
                break;
            }
            default:
                cout << "Неверный выбор!\n";
        }
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

// A-1.1
void inversionsTask() {
    if (currentIntSeq == nullptr) {
        cout << "Последовательность не создана.\n";
        return;
    }
    int inv = countInversionsMapReduce(currentIntSeq);
    cout << "Число инверсий: " << inv << endl;
}

// A-3: Range
void rangeTask() {
    int l, h;
    cout << "Введите l (нижняя граница): ";
    cin >> l;
    cout << "Введите h (верхняя граница): ";
    cin >> h;

    try {
        Sequence<int>* r = Range(l, h);
        cout << "Range[" << l << ", " << h << "]: " << *r << endl;
        delete r;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

// A-1.1 и A-3 Deque
void dequeInversionsTask() {
    if (currentDeque == nullptr) {
        cout << "Deque не создан.\n";
        return;
    }
    Sequence<int>* seq = dequeToSequence(currentDeque);
    int inv = countInversionsMapReduce(seq);
    cout << "Число инверсий: " << inv << endl;
    delete seq;
}

void dequeRangeTask() {
    int l, h;
    cout << "Введите l (нижняя граница): ";
    cin >> l;
    cout << "Введите h (верхняя граница): ";
    cin >> h;

    try {
        Sequence<int>* r = Range(l, h);
        cout << "Range[" << l << ", " << h << "]: " << *r << endl;
        delete r;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

// A-1.1 и A-3 Stack/Queue
void stackInversionsTask() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    Sequence<int>* seq = stackToSequence(currentStack);
    int inv = countInversionsMapReduce(seq);
    cout << "Число инверсий: " << inv << endl;
    delete seq;
}

void queueInversionsTask() {
    if (currentQueue == nullptr) {
        cout << "Queue не создана.\n";
        return;
    }
    Sequence<int>* seq = queueToSequence(currentQueue);
    int inv = countInversionsMapReduce(seq);
    cout << "Число инверсий: " << inv << endl;
    delete seq;
}

void stackRangeTask() {
    int l, h;
    cout << "Введите l (нижняя граница): ";
    cin >> l;
    cout << "Введите h (верхняя граница): ";
    cin >> h;

    try {
        Sequence<int>* r = Range(l, h);
        cout << "Range[" << l << ", " << h << "]: " << *r << endl;
        delete r;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void queueRangeTask() {
    int l, h;
    cout << "Введите l (нижняя граница): ";
    cin >> l;
    cout << "Введите h (верхняя граница): ";
    cin >> h;

    try {
        Sequence<int>* r = Range(l, h);
        cout << "Range[" << l << ", " << h << "]: " << *r << endl;
        delete r;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void runTests() {
    cout << "\n--- Запуск всех тестов ---\n";
    runAllTests();
}

int main() {
    cout << "========================================\n";
    cout << "   ЛР №3\n";
    cout << "========================================\n";

    selectInitialType();

    int choice;
    do {
        printMenu();
        cin >> choice;

        if (isDequeMode) {
            switch (choice) {
                case 1: createSequence(); break;
                case 2: showSequence(); break;
                case 3: dequePushFront(); break;
                case 4: dequePushBack(); break;
                case 5: dequePopFront(); break;
                case 6: dequePopBack(); break;
                case 7: dequePeekFront(); break;
                case 8: dequePeekBack(); break;
                case 9: dequePeek(); break;
                case 10: dequeIsEmpty(); break;
                case 11: dequeGetSize(); break;
                case 12: dequeIndexOf(); break;
                case 13: dequeGetSubsequence(); break;
                case 14: dequeConcat(); break;
                case 15: dequeMap(); break;
                case 16: dequeWhere(); break;
                case 17: dequeReduce(); break;
                case 18: dequeSort(); break;
                case 19: mapReduceTasks(); break;
                case 20: dequeInversionsTask(); break;
                case 21: dequeRangeTask(); break;
                case 22: runTests(); break;
                case 0:
                    cout << "ЗАВЕРШЕНИЕ РАБОТЫ\n";
                    break;
                default:
                    cout << "Неверный выбор\n";
            }
        }
        else if (isStackMode) {
            switch (choice) {
                case 1: createSequence(); break;
                case 2: showSequence(); break;
                case 3: stackPush(); break;
                case 4: stackPop(); break;
                case 5: stackTop(); break;
                case 6: stackIsEmpty(); break;
                case 7: stackGetSize(); break;
                case 8: stackIndexOf(); break;
                case 9: stackFindAllOccurrences(); break;
                case 10: stackConcat(); break;
                case 11: stackMap(); break;
                case 12: stackWhere(); break;
                case 13: stackReduce(); break;
                case 14: stackZip(); break;
                case 15: mapReduceTasks(); break;
                case 16: stackInversionsTask(); break;
                case 17: stackRangeTask(); break;
                case 18: runTests(); break;
                case 0:
                    cout << "ЗАВЕРШЕНИЕ РАБОТЫ\n";
                    break;
                default:
                    cout << "Неверный выбор\n";
            }
        }
        else if (isQueueMode) {
            switch (choice) {
                case 1: createSequence(); break;
                case 2: showSequence(); break;
                case 3: queueEnqueue(); break;
                case 4: queueDequeue(); break;
                case 5: queuePeek(); break;
                case 6: queueIsEmpty(); break;
                case 7: queueGetSize(); break;
                case 8: queueIndexOf(); break;
                case 9: queueConcat(); break;
                case 10: queueGetSubsequence(); break;
                case 11: queueMap(); break;
                case 12: queueWhere(); break;
                case 13: queueReduce(); break;
                case 14: mapReduceTasks(); break;
                case 15: queueInversionsTask(); break;
                case 16: queueRangeTask(); break;
                case 17: runTests(); break;
                case 0:
                    cout << "ЗАВЕРШЕНИЕ РАБОТЫ\n";
                    break;
                default:
                    cout << "Неверный выбор\n";
            }
        }
        else {
            switch (choice) {
                case 1: createSequence(); break;
                case 2: showSequence(); break;
                case 3: appendElement(); break;
                case 4: prependElement(); break;
                case 5: insertAt(); break;
                case 6: getElement(); break;
                case 7: getSubsequence(); break;
                case 8: concatSequence(); break;
                case 9: mapOperation(); break;
                case 10: whereOperation(); break;
                case 11: reduceOperation(); break;
                case 12: zipOperation(); break;
                case 13: skipOperation(); break;
                case 14: takeOperation(); break;
                case 15: switchToStack(); break;
                case 16: switchToQueue(); break;
                case 17: switchToDeque(); break;
                case 18: mapReduceTasks(); break;
                case 19: inversionsTask(); break;
                case 20: rangeTask(); break;
                case 21: runTests(); break;
                case 0:
                    cout << "ЗАВЕРШЕНИЕ РАБОТЫ\n";
                    break;
                default:
                    cout << "Неверный выбор\n";
            }
        }
    } while (choice != 0);

    if (currentIntSeq != nullptr) delete currentIntSeq;
    if (currentStack != nullptr) delete currentStack;
    if (currentQueue != nullptr) delete currentQueue;
    if (currentDeque != nullptr) delete currentDeque;

    return 0;

}
