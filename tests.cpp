#include <iostream>
#include <cassert>
#include <string>
#include "dynamic_array.hpp"
#include "linked_list.hpp"
#include "array_sequence.hpp"
#include "list_sequence.hpp"
#include "map_reduce_tasks.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "deque.hpp"

int passed = 0;
int failed = 0;

void runTest(void (*test)(), const std::string& name) {
    try {
        test();
        passed++;
        std::cout << "  [OK] " << name << std::endl;
    } catch (const std::exception& e) {
        failed++;
        std::cout << "  [НЕУДАЧА] " << name << ": " << e.what() << std::endl;
    }
}

// DynamicArray
void test_da() {
    int items[] = {1, 2, 3};
    DynamicArray<int> a(items, 3);
    assert(a.GetSize() == 3);
    assert(a.Get(0) == 1);
    assert(a.Get(2) == 3);

    a.Set(1, 99);
    assert(a.Get(1) == 99);

    a.Resize(5);
    assert(a.GetSize() == 5);
}

// LinkedList
void test_ll() {
    int items[] = {1, 2, 3};
    LinkedList<int> list(items, 3);
    assert(list.GetLength() == 3);
    assert(list.GetFirst() == 1);
    assert(list.GetLast() == 3);

    list.Append(4);
    assert(list.GetLength() == 4);
    assert(list.GetLast() == 4);

    list.Prepend(0);
    assert(list.GetFirst() == 0);

    list.InsertAt(99, 2);
    assert(list.Get(2) == 99);
}

// MutableArraySequence
void test_mas() {
    int items[] = {1, 2, 3};
    MutableArraySequence<int> seq(items, 3);
    assert(seq.GetLength() == 3);
    assert(seq.GetFirst() == 1);
    assert(seq.GetLast() == 3);

    seq.Append(4);
    assert(seq.GetLength() == 4);
    assert(seq.GetLast() == 4);

    seq.Prepend(0);
    assert(seq.GetFirst() == 0);

    seq.InsertAt(99, 2);
    assert(seq.Get(2) == 99);
}

// ImmutableArraySequence
void test_ias() {
    int items[] = {1, 2, 3};
    ImmutableArraySequence<int> seq(items, 3);
    assert(seq.GetLength() == 3);

    Sequence<int>* newSeq = seq.Append(4);
    assert(seq.GetLength() == 3);
    assert(newSeq->GetLength() == 4);
    assert(newSeq != &seq);

    delete newSeq;
}

// MutableListSequence
void test_mls() {
    int items[] = {1, 2, 3};
    MutableListSequence<int> seq(items, 3);
    assert(seq.GetLength() == 3);
    assert(seq.GetFirst() == 1);
    assert(seq.GetLast() == 3);

    seq.Append(4);
    assert(seq.GetLast() == 4);

    seq.Prepend(0);
    assert(seq.GetFirst() == 0);
}

// ImmutableListSequence
void test_ils() {
    int items[] = {1, 2, 3};
    ImmutableListSequence<int> seq(items, 3);
    assert(seq.GetLength() == 3);

    Sequence<int>* newSeq = seq.Append(4);
    assert(seq.GetLength() == 3);
    assert(newSeq->GetLength() == 4);

    delete newSeq;
}

// Map/Reduce для Sequence
void test_map_reduce_sequence() {
    int items[] = {1, 2, 3, 4, 5};
    MutableArraySequence<int> seq(items, 5);

    Sequence<int>* mapped = seq.Map([](int x) { return x * 2; });
    assert(mapped->Get(0) == 2);
    assert(mapped->Get(2) == 6);
    delete mapped;

    Sequence<int>* filtered = seq.Where([](int x) { return x > 3; });
    assert(filtered->GetLength() == 2);
    assert(filtered->Get(0) == 4);
    delete filtered;

    int sum = seq.Reduce([](int a, int b) { return a + b; }, 0);
    assert(sum == 15);
}

//Stack

void test_stack_basic() {
    Stack<int> s;
    assert(s.IsEmpty());
    assert(s.GetSize() == 0);

    s.Push(1);
    s.Push(2);
    s.Push(3);

    assert(!s.IsEmpty());
    assert(s.GetSize() == 3);
    assert(s.Top() == 3);

    int val = s.Pop();
    assert(val == 3);
    assert(s.GetSize() == 2);
    assert(s.Top() == 2);

    val = s.Pop();
    assert(val == 2);
    val = s.Pop();
    assert(val == 1);
    assert(s.IsEmpty());
}

void test_stack_copy() {
    Stack<int> s1;
    s1.Push(1);
    s1.Push(2);
    s1.Push(3);

    Stack<int> s2;
    Stack<int> temp;
    Stack<int> s1Copy;
    while (!s1.IsEmpty()) {
        int val = s1.Pop();
        temp.Push(val);
    }
    while (!temp.IsEmpty()) {
        int val = temp.Pop();
        s2.Push(val);
        s1Copy.Push(val);
    }
    Stack<int> restore;
    while (!s1Copy.IsEmpty()) {
        restore.Push(s1Copy.Pop());
    }
    while (!restore.IsEmpty()) {
        s1.Push(restore.Pop());
    }

    assert(s2.GetSize() == 3);
    assert(s2.Top() == 3);
    assert(s1.GetSize() == 3);

    assert(s2.Pop() == 3);
    assert(s2.Pop() == 2);
    assert(s2.Pop() == 1);
    assert(s2.IsEmpty());

    assert(s1.GetSize() == 3);
    assert(s1.Top() == 3);
}

void test_stack_map() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Push(3);

    Stack<int>* mapped = s.Map([](int x) { return x * 2; });
    assert(mapped->GetSize() == 3);

    assert(mapped->Pop() == 6);
    assert(mapped->Pop() == 4);
    assert(mapped->Pop() == 2);
    assert(mapped->IsEmpty());

    delete mapped;
}

void test_stack_map_index() {
    Stack<int> s;
    s.Push(10);
    s.Push(20);
    s.Push(30);

    Stack<int>* mapped = s.Map([](int x, int i) { return x + i; });

    assert(mapped->GetSize() == 3);
    assert(mapped->Pop() == 32);
    assert(mapped->Pop() == 21);
    assert(mapped->Pop() == 10);

    delete mapped;
}

void test_stack_where() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Push(3);
    s.Push(4);
    s.Push(5);

    Stack<int>* filtered = s.Where([](int x) { return x > 3; });
    assert(filtered->GetSize() == 2);

    assert(filtered->Pop() == 5);
    assert(filtered->Pop() == 4);
    assert(filtered->IsEmpty());

    delete filtered;
}

void test_stack_reduce() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Push(3);
    s.Push(4);

    int sum = s.Reduce([](int a, int b) { return a + b; }, 0);
    assert(sum == 10);

    int product = s.Reduce([](int a, int b) { return a * b; }, 1);
    assert(product == 24);
}

void test_stack_indexof() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Push(3);
    s.Push(1);
    s.Push(2);
    s.Push(3);

    Stack<int> sub;
    sub.Push(1);
    sub.Push(2);

    int idx = s.IndexOf(sub);
    assert(idx == 0);

    Stack<int> sub2;
    sub2.Push(2);
    sub2.Push(3);

    idx = s.IndexOf(sub2);
    assert(idx == 1);

    Stack<int> sub3;
    sub3.Push(9);
    sub3.Push(9);
    idx = s.IndexOf(sub3);
    assert(idx == -1);
}

void test_stack_indexof_empty() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);

    Stack<int> empty;
    int idx = s.IndexOf(empty);
    assert(idx == 0);
}

void test_stack_concat() {
    Stack<int> s1;
    s1.Push(1);
    s1.Push(2);

    Stack<int> s2;
    s2.Push(3);
    s2.Push(4);

    Stack<int>* result = s1.Concat(&s2);
    assert(result->GetSize() == 4);

    assert(result->Pop() == 4);
    assert(result->Pop() == 3);
    assert(result->Pop() == 2);
    assert(result->Pop() == 1);
    assert(result->IsEmpty());

    delete result;
}

void test_stack_find_all_occurrences() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Push(3);
    s.Push(1);
    s.Push(2);
    s.Push(3);
    s.Push(1);
    s.Push(2);

    Stack<int> sub;
    sub.Push(1);
    sub.Push(2);

    Stack<int>* result = s.FindAllOccurrences(sub);
    assert(result->GetSize() == 3);

    assert(result->Pop() == 6);
    assert(result->Pop() == 3);
    assert(result->Pop() == 0);
    assert(result->IsEmpty());

    delete result;
}

void test_stack_find_all_occurrences_none() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);

    Stack<int> sub;
    sub.Push(9);

    Stack<int>* result = s.FindAllOccurrences(sub);
    assert(result->GetSize() == 0);
    assert(result->IsEmpty());

    delete result;
}

void test_stack_zip() {
    Stack<int> s1;
    s1.Push(1);
    s1.Push(2);
    s1.Push(3);

    Stack<int> s2;
    s2.Push(10);
    s2.Push(20);
    s2.Push(30);
    s2.Push(40);

    Stack<int>* zipped = s1.Zip(&s2, [](int a, int b) { return a + b; });
    assert(zipped->GetSize() == 3);

    assert(zipped->Pop() == 33);
    assert(zipped->Pop() == 22);
    assert(zipped->Pop() == 11);
    assert(zipped->IsEmpty());

    delete zipped;
}

void test_stack_exceptions() {
    Stack<int> s;

    try {
        s.Pop();
        assert(false);
    } catch (const EmptyContainerException&) {
    } catch (...) {
        assert(false);
    }

    try {
        s.Top();
        assert(false);
    } catch (const EmptyContainerException&) {
    }
}

void test_stack_large_data() {
    Stack<int> s;
    const int N = 1000;

    for (int i = 0; i < N; i++) {
        s.Push(i);
    }

    assert(s.GetSize() == N);
    assert(s.Top() == N - 1);

    int sum = s.Reduce([](int a, int b) { return a + b; }, 0);
    assert(sum == N * (N - 1) / 2);

    Stack<int>* doubled = s.Map([](int x) { return x * 2; });
    assert(doubled->GetSize() == N);

    Stack<int> tempCopy;
    Stack<int> temp;
    Stack<int> doubledCopy;
    while (!doubled->IsEmpty()) {
        int val = doubled->Pop();
        temp.Push(val);
    }
    while (!temp.IsEmpty()) {
        int val = temp.Pop();
        tempCopy.Push(val);
        doubledCopy.Push(val);
    }
    while (!doubledCopy.IsEmpty()) {
        doubled->Push(doubledCopy.Pop());
    }
    while (!tempCopy.IsEmpty()) {
        int val = tempCopy.Pop();
        assert(val % 2 == 0);
        assert(val >= 0 && val <= 2 * (N - 1));
    }
    delete doubled;

    for (int i = N - 1; i >= 0; i--) {
        assert(s.Pop() == i);
    }
    assert(s.IsEmpty());
}

void test_stack_string() {
    Stack<std::string> s;
    s.Push("hello");
    s.Push("world");

    assert(s.GetSize() == 2);
    assert(s.Top() == "world");

    assert(s.Pop() == "world");
    assert(s.Pop() == "hello");
    assert(s.IsEmpty());
}

// Queue

void test_queue_basic() {
    Queue<int> q;
    assert(q.IsEmpty());
    assert(q.GetSize() == 0);

    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);

    assert(!q.IsEmpty());
    assert(q.GetSize() == 3);
    assert(q.Peek() == 1);

    int val = q.Dequeue();
    assert(val == 1);
    assert(q.GetSize() == 2);
    assert(q.Peek() == 2);

    val = q.Dequeue();
    assert(val == 2);
    val = q.Dequeue();
    assert(val == 3);
    assert(q.IsEmpty());
}

void test_queue_copy() {
    Queue<int> q1;
    q1.Enqueue(1);
    q1.Enqueue(2);
    q1.Enqueue(3);

    Queue<int> q2;
    Queue<int> temp;
    Queue<int> q1Copy;
    while (!q1.IsEmpty()) {
        int val = q1.Dequeue();
        temp.Enqueue(val);
    }
    while (!temp.IsEmpty()) {
        int val = temp.Dequeue();
        q2.Enqueue(val);
        q1Copy.Enqueue(val);
    }
    while (!q1Copy.IsEmpty()) {
        q1.Enqueue(q1Copy.Dequeue());
    }

    assert(q2.GetSize() == 3);
    assert(q2.Peek() == 1);
    assert(q1.GetSize() == 3);

    assert(q2.Dequeue() == 1);
    assert(q2.Dequeue() == 2);
    assert(q2.Dequeue() == 3);
    assert(q2.IsEmpty());

    assert(q1.GetSize() == 3);
    assert(q1.Peek() == 1);
}

void test_queue_map() {
    Queue<int> q;
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);

    Queue<int>* mapped = q.Map([](int x) { return x * 2; });
    assert(mapped->GetSize() == 3);

    assert(mapped->Dequeue() == 2);
    assert(mapped->Dequeue() == 4);
    assert(mapped->Dequeue() == 6);
    assert(mapped->IsEmpty());

    delete mapped;
}

void test_queue_where() {
    Queue<int> q;
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    q.Enqueue(4);
    q.Enqueue(5);

    Queue<int>* filtered = q.Where([](int x) { return x > 3; });
    assert(filtered->GetSize() == 2);

    assert(filtered->Dequeue() == 4);
    assert(filtered->Dequeue() == 5);
    assert(filtered->IsEmpty());

    delete filtered;
}

void test_queue_reduce() {
    Queue<int> q;
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    q.Enqueue(4);

    int sum = q.Reduce([](int a, int b) { return a + b; }, 0);
    assert(sum == 10);

    int product = q.Reduce([](int a, int b) { return a * b; }, 1);
    assert(product == 24);
}

void test_queue_indexof() {
    Queue<int> q;
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    q.Enqueue(1);
    q.Enqueue(2);

    Queue<int> sub;
    sub.Enqueue(1);
    sub.Enqueue(2);

    int idx = q.IndexOf(sub);
    assert(idx == 0);

    Queue<int> sub2;
    sub2.Enqueue(2);
    sub2.Enqueue(3);

    idx = q.IndexOf(sub2);
    assert(idx == 1);

    Queue<int> sub3;
    sub3.Enqueue(9);
    idx = q.IndexOf(sub3);
    assert(idx == -1);
}

void test_queue_concat() {
    Queue<int> q1;
    q1.Enqueue(1);
    q1.Enqueue(2);

    Queue<int> q2;
    q2.Enqueue(3);
    q2.Enqueue(4);

    Queue<int>* result = q1.Concat(&q2);
    assert(result->GetSize() == 4);

    assert(result->Dequeue() == 1);
    assert(result->Dequeue() == 2);
    assert(result->Dequeue() == 3);
    assert(result->Dequeue() == 4);
    assert(result->IsEmpty());

    delete result;
}

void test_queue_getsubsequence() {
    Queue<int> q;
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    q.Enqueue(4);
    q.Enqueue(5);

    Queue<int>* sub = q.GetSubsequence(1, 3);
    assert(sub->GetSize() == 3);

    assert(sub->Dequeue() == 2);
    assert(sub->Dequeue() == 3);
    assert(sub->Dequeue() == 4);
    assert(sub->IsEmpty());

    delete sub;
}

void test_queue_exceptions() {
    Queue<int> q;

    try {
        q.Dequeue();
        assert(false);
    } catch (const EmptyContainerException&) {
    } catch (...) {
        assert(false);
    }

    try {
        q.Peek();
        assert(false);
    } catch (const EmptyContainerException&) {
    }
}

void test_queue_string() {
    Queue<std::string> q;
    q.Enqueue("hello");
    q.Enqueue("world");

    assert(q.GetSize() == 2);
    assert(q.Peek() == "hello");

    assert(q.Dequeue() == "hello");
    assert(q.Dequeue() == "world");
    assert(q.IsEmpty());
}

// Deque

void test_deque_basic() {
    Deque<int> d;
    assert(d.IsEmpty());
    assert(d.GetSize() == 0);

    d.PushBack(1);
    d.PushBack(2);
    d.PushBack(3);

    assert(!d.IsEmpty());
    assert(d.GetSize() == 3);
    assert(d.PeekFront() == 1);
    assert(d.PeekBack() == 3);

    int val = d.PopFront();
    assert(val == 1);
    assert(d.GetSize() == 2);
    assert(d.PeekFront() == 2);

    val = d.PopBack();
    assert(val == 3);
    assert(d.PeekBack() == 2);

    d.PushFront(10);
    assert(d.PeekFront() == 10);
    assert(d.GetSize() == 2);
}

void test_deque_copy() {
    Deque<int> d1;
    d1.PushBack(1);
    d1.PushBack(2);
    d1.PushBack(3);

    Deque<int> d2;
    for (int i = 0; i < d1.GetSize(); i++) {
        d2.PushBack(d1.Peek(i));
    }

    assert(d2.GetSize() == 3);
    assert(d2.PeekFront() == 1);
    assert(d2.PeekBack() == 3);
    assert(d1.GetSize() == 3);

    assert(d2.PopFront() == 1);
    assert(d2.PopFront() == 2);
    assert(d2.PopFront() == 3);
    assert(d2.IsEmpty());

    assert(d1.GetSize() == 3);
    assert(d1.PeekFront() == 1);
}

void test_deque_map() {
    Deque<int> d;
    d.PushBack(1);
    d.PushBack(2);
    d.PushBack(3);

    Deque<int>* mapped = d.Map([](int x) { return x * 2; });
    assert(mapped->GetSize() == 3);

    assert(mapped->PopFront() == 2);
    assert(mapped->PopFront() == 4);
    assert(mapped->PopFront() == 6);
    assert(mapped->IsEmpty());

    delete mapped;
}

void test_deque_where() {
    Deque<int> d;
    d.PushBack(1);
    d.PushBack(2);
    d.PushBack(3);
    d.PushBack(4);
    d.PushBack(5);

    Deque<int>* filtered = d.Where([](int x) { return x > 3; });
    assert(filtered->GetSize() == 2);

    assert(filtered->PopFront() == 4);
    assert(filtered->PopFront() == 5);
    assert(filtered->IsEmpty());

    delete filtered;
}

void test_deque_reduce() {
    Deque<int> d;
    d.PushBack(1);
    d.PushBack(2);
    d.PushBack(3);
    d.PushBack(4);

    int sum = d.Reduce([](int a, int b) { return a + b; }, 0);
    assert(sum == 10);

    int product = d.Reduce([](int a, int b) { return a * b; }, 1);
    assert(product == 24);
}

void test_deque_indexof() {
    Deque<int> d;
    d.PushBack(1);
    d.PushBack(2);
    d.PushBack(3);
    d.PushBack(1);
    d.PushBack(2);

    Deque<int> sub;
    sub.PushBack(1);
    sub.PushBack(2);

    int idx = d.IndexOf(sub);
    assert(idx == 0);

    Deque<int> sub2;
    sub2.PushBack(2);
    sub2.PushBack(3);

    idx = d.IndexOf(sub2);
    assert(idx == 1);

    Deque<int> sub3;
    sub3.PushBack(9);
    idx = d.IndexOf(sub3);
    assert(idx == -1);
}

void test_deque_indexof_empty() {
    Deque<int> d;
    d.PushBack(1);
    d.PushBack(2);

    Deque<int> empty;
    int idx = d.IndexOf(empty);
    assert(idx == 0);
}

void test_deque_concat() {
    Deque<int> d1;
    d1.PushBack(1);
    d1.PushBack(2);

    Deque<int> d2;
    d2.PushBack(3);
    d2.PushBack(4);

    Deque<int>* result = d1.Concat(&d2);
    assert(result->GetSize() == 4);

    assert(result->PopFront() == 1);
    assert(result->PopFront() == 2);
    assert(result->PopFront() == 3);
    assert(result->PopFront() == 4);
    assert(result->IsEmpty());

    delete result;
}

void test_deque_getsubsequence() {
    Deque<int> d;
    d.PushBack(1);
    d.PushBack(2);
    d.PushBack(3);
    d.PushBack(4);
    d.PushBack(5);

    Deque<int>* sub = d.GetSubsequence(1, 3);
    assert(sub->GetSize() == 3);

    assert(sub->PopFront() == 2);
    assert(sub->PopFront() == 3);
    assert(sub->PopFront() == 4);
    assert(sub->IsEmpty());

    delete sub;
}

void test_deque_sort() {
    Deque<int> d;
    d.PushBack(3);
    d.PushBack(1);
    d.PushBack(4);
    d.PushBack(2);

    d.Sort();
    assert(d.PopFront() == 1);
    assert(d.PopFront() == 2);
    assert(d.PopFront() == 3);
    assert(d.PopFront() == 4);
    assert(d.IsEmpty());
}

void test_deque_exceptions() {
    Deque<int> d;

    try {
        d.PopFront();
        assert(false);
    } catch (const EmptyContainerException&) {
    } catch (...) {
        assert(false);
    }

    try {
        d.PopBack();
        assert(false);
    } catch (const EmptyContainerException&) {
    }

    try {
        d.PeekFront();
        assert(false);
    } catch (const EmptyContainerException&) {
    }

    try {
        d.PeekBack();
        assert(false);
    } catch (const EmptyContainerException&) {
    }
}

void test_deque_large_data() {
    Deque<int> d;
    const int N = 1000;

    for (int i = 0; i < N; i++) {
        d.PushBack(i);
    }

    assert(d.GetSize() == N);
    assert(d.PeekFront() == 0);
    assert(d.PeekBack() == N - 1);

    int sum = d.Reduce([](int a, int b) { return a + b; }, 0);
    assert(sum == N * (N - 1) / 2);

    for (int i = 0; i < N; i++) {
        assert(d.PopFront() == i);
    }
    assert(d.IsEmpty());
}

void test_deque_string() {
    Deque<std::string> d;
    d.PushBack("hello");
    d.PushFront("world");

    assert(d.GetSize() == 2);
    assert(d.PeekFront() == "world");
    assert(d.PeekBack() == "hello");

    assert(d.PopFront() == "world");
    assert(d.PopBack() == "hello");
    assert(d.IsEmpty());
}

//П-задачи
void test_tasks() {
    int items[] = {3, 1, 4, 1, 5, 9};
    MutableArraySequence<int> seq(items, 6);

    auto result = computeMinMaxAvg(&seq);
    assert(std::get<0>(result) == 1.0);
    assert(std::get<1>(result) == 9.0);

    int items2[] = {3, 1, 4, 1, 5};
    MutableArraySequence<int> seq2(items2, 5);
    assert(computeMedian(&seq2) == 3.0);

    int items3[] = {1, 2, 3, 4, 5};
    MutableArraySequence<int> seq3(items3, 5);
    Sequence<int>* mirror = computeMirrorSum(&seq3);
    assert(mirror->Get(0) == 6);
    assert(mirror->Get(2) == 6);
    delete mirror;
}

void test_stack_tasks() {
    Stack<int> s;
    s.Push(3);
    s.Push(1);
    s.Push(4);
    s.Push(1);
    s.Push(5);
    s.Push(9);

    MutableArraySequence<int> seq;
    Stack<int> temp;
    Stack<int> reversed;
    Stack<int> sCopy;
    while (!s.IsEmpty()) {
        int val = s.Pop();
        temp.Push(val);
    }
    while (!temp.IsEmpty()) {
        int val = temp.Pop();
        sCopy.Push(val);
        reversed.Push(val);
    }
    while (!sCopy.IsEmpty()) {
        s.Push(sCopy.Pop());
    }
    while (!reversed.IsEmpty()) {
        seq.Append(reversed.Pop());
    }

    auto result = computeMinMaxAvg(&seq);
    assert(std::get<0>(result) == 1.0);
    assert(std::get<1>(result) == 9.0);
}

void test_queue_tasks() {
    Queue<int> q;
    q.Enqueue(3);
    q.Enqueue(1);
    q.Enqueue(4);
    q.Enqueue(1);
    q.Enqueue(5);
    q.Enqueue(9);

    MutableArraySequence<int> seq;
    Queue<int> temp;
    Queue<int> qCopy;
    while (!q.IsEmpty()) {
        int val = q.Dequeue();
        temp.Enqueue(val);
    }
    while (!temp.IsEmpty()) {
        int val = temp.Dequeue();
        qCopy.Enqueue(val);
        seq.Append(val);
    }
    while (!qCopy.IsEmpty()) {
        q.Enqueue(qCopy.Dequeue());
    }

    auto result = computeMinMaxAvg(&seq);
    assert(std::get<0>(result) == 1.0);
    assert(std::get<1>(result) == 9.0);
}

void test_deque_tasks() {
    Deque<int> d;
    d.PushBack(3);
    d.PushBack(1);
    d.PushBack(4);
    d.PushBack(1);
    d.PushBack(5);
    d.PushBack(9);

    MutableArraySequence<int> seq;
    for (int i = 0; i < d.GetSize(); i++) {
        seq.Append(d.Peek(i));
    }

    auto result = computeMinMaxAvg(&seq);
    assert(std::get<0>(result) == 1.0);
    assert(std::get<1>(result) == 9.0);
}

// A1.1
void test_inversions_mapreduce() {
    int arr1[] = {1, 3, 2};
    MutableArraySequence<int> seq1(arr1, 3);
    assert(countInversionsMapReduce(&seq1) == 1);

    int arr2[] = {5, 4, 3, 2, 1};
    MutableArraySequence<int> seq2(arr2, 5);
    assert(countInversionsMapReduce(&seq2) == 10);

    int arr3[] = {1, 2, 3};
    MutableArraySequence<int> seq3(arr3, 3);
    assert(countInversionsMapReduce(&seq3) == 0);

    MutableArraySequence<int> empty;
    assert(countInversionsMapReduce(&empty) == 0);
}

// A3
void test_range() {
    Sequence<int>* r1 = Range(1, 5);
    assert(r1->GetLength() == 5);
    assert(r1->Get(0) == 1);
    assert(r1->Get(4) == 5);
    delete r1;

    Sequence<int>* r2 = Range(0, 0);
    assert(r2->GetLength() == 1);
    assert(r2->Get(0) == 0);
    delete r2;

    Sequence<int>* r3 = Range(-3, 2);
    assert(r3->GetLength() == 6);
    assert(r3->Get(0) == -3);
    assert(r3->Get(5) == 2);
    delete r3;

    try {
        Range(5, 1);
        assert(false);
    } catch (const InvalidArgumentException&) {
        // OK
    }
}

void runAllTests() {
    passed = 0;
    failed = 0;

    std::cout << "\nЗапуск тестов\n" << std::endl;

    runTest(test_da, "DynamicArray");
    runTest(test_ll, "LinkedList");
    runTest(test_mas, "MutableArraySequence");
    runTest(test_ias, "ImmutableArraySequence");
    runTest(test_mls, "MutableListSequence");
    runTest(test_ils, "ImmutableListSequence");
    runTest(test_map_reduce_sequence, "Map/Reduce/Where для Sequence");

    runTest(test_stack_basic, "Stack: Push/Pop/Top/IsEmpty");
    runTest(test_stack_copy, "Stack: копирующий конструктор");
    runTest(test_stack_map, "Stack: Map");
    runTest(test_stack_map_index, "Stack: Map с индексом");
    runTest(test_stack_where, "Stack: Where");
    runTest(test_stack_reduce, "Stack: Reduce");
    runTest(test_stack_indexof, "Stack: IndexOf");
    runTest(test_stack_indexof_empty, "Stack: IndexOf (пустая подпоследовательность)");
    runTest(test_stack_concat, "Stack: Concat");
    runTest(test_stack_find_all_occurrences, "Stack: FindAllOccurrences");
    runTest(test_stack_find_all_occurrences_none, "Stack: FindAllOccurrences (ничего не найдено)");
    runTest(test_stack_zip, "Stack: Zip");
    runTest(test_stack_exceptions, "Stack: обработка исключений");
    runTest(test_stack_large_data, "Stack: большой объем данных");
    runTest(test_stack_string, "Stack: строки (шаблонность)");

    runTest(test_queue_basic, "Queue: Enqueue/Dequeue/Peek/IsEmpty");
    runTest(test_queue_copy, "Queue: копирующий конструктор");
    runTest(test_queue_map, "Queue: Map");
    runTest(test_queue_where, "Queue: Where");
    runTest(test_queue_reduce, "Queue: Reduce");
    runTest(test_queue_indexof, "Queue: IndexOf");
    runTest(test_queue_concat, "Queue: Concat");
    runTest(test_queue_getsubsequence, "Queue: GetSubsequence");
    runTest(test_queue_exceptions, "Queue: обработка исключений");
    runTest(test_queue_string, "Queue: строки (шаблонность)");

    runTest(test_deque_basic, "Deque: PushFront/PushBack/PopFront/PopBack/Peek");
    runTest(test_deque_copy, "Deque: копирующий конструктор");
    runTest(test_deque_map, "Deque: Map");
    runTest(test_deque_where, "Deque: Where");
    runTest(test_deque_reduce, "Deque: Reduce");
    runTest(test_deque_indexof, "Deque: IndexOf");
    runTest(test_deque_indexof_empty, "Deque: IndexOf (пустая подпоследовательность)");
    runTest(test_deque_concat, "Deque: Concat");
    runTest(test_deque_getsubsequence, "Deque: GetSubsequence");
    runTest(test_deque_sort, "Deque: Sort");
    runTest(test_deque_exceptions, "Deque: обработка исключений");
    runTest(test_deque_large_data, "Deque: большой объем данных");
    runTest(test_deque_string, "Deque: строки (шаблонность)");

    runTest(test_tasks, "П-задачи на Sequence");
    runTest(test_stack_tasks, "П-задачи через Stack");
    runTest(test_queue_tasks, "П-задачи через Queue");
    runTest(test_deque_tasks, "П-задачи через Deque");

    runTest(test_inversions_mapreduce, "A-1.1: число инверсий (MapReduce)");
    runTest(test_range, "A-3: Range [l, h]");

    std::cout << "\n--------------------------------------" << std::endl;
    std::cout << "ИТОГО: Пройдено: " << passed << ", Не пройдено: " << failed << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}