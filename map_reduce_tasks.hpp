#ifndef MAP_REDUCE_TASKS_HPP
#define MAP_REDUCE_TASKS_HPP

#include "sequence.hpp"
#include "array_sequence.hpp"
#include <cmath>
#include <algorithm>
#include <tuple>

// П-1
inline std::tuple<double, double, double> computeMinMaxAvg(Sequence<int> *seq) {
    if (seq->GetLength() == 0) {
        throw InvalidArgumentException("Последовательность пуста");
    }

    struct Acc {
        int minVal;
        int maxVal;
        long long sum;
        int count;
    };

    Acc acc{seq->Get(0), seq->Get(0), 0, 0};

    for (int i = 0; i < seq->GetLength(); i++) {
        int val = seq->Get(i);
        if (val < acc.minVal) acc.minVal = val;
        if (val > acc.maxVal) acc.maxVal = val;
        acc.sum += val;
        acc.count++;
    }

    double avg = static_cast<double>(acc.sum) / acc.count;
    return {
        static_cast<double>(acc.minVal),
        static_cast<double>(acc.maxVal),
        avg
    };
}

// П-2
inline double computeMedian(Sequence<int> *seq) {
    if (seq->GetLength() == 0) {
        throw InvalidArgumentException("Последовательность пуста");
    }

    int n = seq->GetLength();
    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = seq->Get(i);
    }

    std::sort(arr, arr + n);

    double median;
    if (n % 2 == 1) {
        median = arr[n / 2];
    } else {
        median = (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
    }

    delete[] arr;
    return median;
}

// П-5 префиксы
inline Sequence<Sequence<int> *> *computePrefixes(Sequence<int> *seq) {
    MutableArraySequence<Sequence<int> *> *result = new MutableArraySequence<Sequence<int> *>();

    MutableArraySequence<int> *current = new MutableArraySequence<int>();
    for (int i = 0; i < seq->GetLength(); i++) {
        current->Append(seq->Get(i));
        MutableArraySequence<int> *copy = new MutableArraySequence<int>();
        for (int j = 0; j < current->GetLength(); j++) {
            copy->Append(current->Get(j));
        }
        result->Append(copy);
    }
    delete current;

    return result;
}

// П-5 постфиксы
inline Sequence<Sequence<int> *> *computeSuffixes(Sequence<int> *seq) {
    MutableArraySequence<Sequence<int> *> *result = new MutableArraySequence<Sequence<int> *>();
    int n = seq->GetLength();

    for (int i = 0; i < n; i++) {
        result->Append(seq->GetSubsequence(i, n - 1));
    }

    return result;
}

// П-8
inline Sequence<int> *computeMirrorSum(Sequence<int> *seq) {
    int n = seq->GetLength();
    if (n == 0) {
        return new MutableArraySequence<int>();
    }

    MutableArraySequence<int> *reversed = new MutableArraySequence<int>();
    for (int i = n - 1; i >= 0; i--) {
        reversed->Append(seq->Get(i));
    }

    Sequence<int> *result = seq->Zip(reversed, [](int a, int b) { return a + b; });

    delete reversed;
    return result;
}

// ============================================================
// A-1.1: Число инверсий через Map-Reduce (с индексом)
// ============================================================
inline int countInversionsMapReduce(Sequence<int>* seq) {
    int n = seq->GetLength();
    if (n <= 1) return 0;

    // Map с индексом: для каждого элемента считаем,
    // сколько элементов СПРАВА от него строго меньше
    auto* mapped = seq->Map([seq, n](int x, int i) -> int {
        int count = 0;
        for (int j = i + 1; j < n; j++) {
            if (seq->Get(j) < x) {
                count++;
            }
        }
        return count;
    });

    // Reduce: суммируем все числа инверсий
    int inversions = mapped->Reduce([](int acc, int val) {
        return acc + val;
    }, 0);

    delete mapped;
    return inversions;
}

// ============================================================
// A-3: Range – генерация последовательности целых чисел [l, h]
// ============================================================
inline Sequence<int>* Range(int l, int h) {
    if (l > h) {
        throw InvalidArgumentException("Range: l должно быть <= h");
    }
    auto* result = new MutableArraySequence<int>();
    for (int i = l; i <= h; i++) {
        result->Append(i);
    }
    return result;
}

#endif // MAP_REDUCE_TASKS_HPP