#include <iostream>
#include <stdexcept>
#include <vector>

#include "sequence.h"
#include "arraySequence.h"
#include "listSequence.h"
#include "MutableArraySequence.h"
#include "immutableArraySequence.h"

using namespace std;

void PrintSequence(Sequence<int>* seq) {
    if (!seq) {
        cout << "nullptr\n";
        return;
    }
    int n = seq->GetLength();
    if (n == 0) {
        cout << "[]\n";
        return;
    }
    cout << "[";
    for (int i = 0; i < n; ++i) {
        cout << seq->Get(i);
        if (i < n - 1) cout << ", ";
    }
    cout << "]\n";
}

int Square(const int& x) { return x * x; }
bool IsEven(const int& x) { return x % 2 == 0; }
bool IsOdd(const int& x)  { return x % 2 == 1; }
bool IsBig(const int& x)   { return x >= 5; }
int Add(const int& x, const int& y) { return x + y; }
int Mult(const int& x, const int& y) { return x * y; }

void test_ImmutableArraySequence() {
    cout << "=== IMMUTABLE ARRAYSEQUENCE FULL TEST ===\n\n";

    ImmutableArraySequence<int> empty;
    cout << "Length: " << empty.GetLength() << "\n";
    try {
        empty.GetFirst();
    } catch (const out_of_range&) {
        cout << "GetFirst() on empty throws → OK\n";
    }
    try {
        empty.GetLast();
    } catch (const out_of_range&) {
        cout << "GetLast() on empty throws → OK\n";
    }

    Sequence<int>* emptyMapped = empty.Map(Square);
    cout << "Map on empty → Length: " << emptyMapped->GetLength() << "\n";

    Sequence<int>* emptyFiltered = empty.Where(IsEven);
    cout << "Where on empty → Length: " << emptyFiltered->GetLength() << "\n";

    int emptySum = empty.Reduce(42, Add);
    cout << "Reduce on empty (init=42) → " << emptySum << "\n\n";

    delete emptyMapped;
    delete emptyFiltered;

    int arr1[] = {1, 2, 3, 4, 5};
    ImmutableArraySequence<int> seq1(arr1, 5);

    cout << "Original: ";
    PrintSequence(&seq1);

    cout << "GetFirst(): " << seq1.GetFirst() << "\n";
    cout << "GetLast():  " << seq1.GetLast()  << "\n";
    cout << "Get(3):     " << seq1.Get(3)     << "\n\n";

    Sequence<int>* mapped = seq1.Map(Square);
    cout << "Map(x*x): ";
    PrintSequence(mapped);

    Sequence<int>* filtered = seq1.Where(IsEven);
    cout << "Where(even): ";
    PrintSequence(filtered);

    Sequence<int>* chain = seq1.Map(Square)->Where(IsEven);
    cout << "Map(x*x)->Where(even): ";
    PrintSequence(chain);

    int sum = seq1.Reduce(0, Add);
    int prod = seq1.Reduce(1, Mult);
    cout << "Reduce(sum=0): " << sum << "\n";
    cout << "Reduce(prod=1): " << prod << "\n\n";

    Sequence<int>* sub = seq1.GetSubsequence(1, 3);
    cout << "GetSubsequence(1..3): ";
    PrintSequence(sub);

    Sequence<int>* full = seq1.GetSubsequence(0, 4);
    cout << "GetSubsequence(0..4): ";
    PrintSequence(full);

    Sequence<int>* single = seq1.GetSubsequence(2, 2);
    cout << "GetSubsequence(2..2): ";
    PrintSequence(single);

    cout << "\n";

    delete mapped;
    delete filtered;
    delete chain;
    delete sub;
    delete full;
    delete single;

    int arr2[] = {2, 2, 4, 4, 6};
    ImmutableArraySequence<int> seq2(arr2, 5);
    Sequence<int>* doubled = seq2.Map([](const int& x) { return x * 2; });
    cout << "Original: ";
    PrintSequence(&seq2);
    cout << "Map(x*2): ";
    PrintSequence(doubled);

    Sequence<int>* gt3 = seq2.Where([](const int& x) { return x > 3; });
    cout << "Where(x>3): ";
    PrintSequence(gt3);

    int sum2 = seq2.Reduce(0, Add);
    cout << "Reduce(sum=0): " << sum2 << "\n\n";

    delete doubled;
    delete gt3;
}

void test_MutableArraySequence() {
    cout << "=== MUTABLEARRAYSEQUENCE FULL TEST ===\n\n";

    int arr[] = {10, 20, 30, 40, 50};
    MutableArraySequence<int> seq(arr, 5);

    cout << "Original: ";
    PrintSequence(&seq);

    cout << "GetFirst(): " << seq.GetFirst() << "\n";
    cout << "GetLast():  " << seq.GetLast()  << "\n\n";

    int sum = seq.Reduce(0, Add);
    cout << "Reduce(sum=0): " << sum << "\n\n";

    Sequence<int>* mapped = seq.Map(Square);
    cout << "Map(x*x): ";
    PrintSequence(mapped);

    Sequence<int>* filtered = seq.Where(IsEven);
    cout << "Where(even): ";
    PrintSequence(filtered);

    Sequence<int>* chain = seq.Map(Square)->Where(IsEven);
    cout << "Map(x*x)->Where(even): ";
    PrintSequence(chain);

    cout << "\n";

    delete mapped;
    delete filtered;
    delete chain;

    MutableArraySequence<int> emptySeq;
    cout << "Length: " << emptySeq.GetLength() << "\n";
    try {
        emptySeq.GetFirst();
    } catch (const out_of_range&) {
        cout << "GetFirst() on empty → OK\n";
    }
    Sequence<int>* emptyMapped = emptySeq.Map(Square);
    cout << "Map on empty → Length: " << emptyMapped->GetLength() << "\n";
    Sequence<int>* emptyFiltered = emptySeq.Where(IsEven);
    cout << "Where on empty → Length: " << emptyFiltered->GetLength() << "\n\n";

    delete emptyMapped;
    delete emptyFiltered;
}

void test_ListSequence() {
    cout << "=== LISTSEQUENCE FULL TEST ===\n\n";

    int arr1[] = {1, 3, 5, 7, 9};
    ListSequence<int> listSeq1(arr1, 5);

    cout << "Original: ";
    PrintSequence(&listSeq1);

    auto Twice = [](const int& x) { return x * 2; };
    Sequence<int>* doubled = listSeq1.Map(Twice);
    cout << "Map(x*2): ";
    PrintSequence(doubled);

    auto IsBig = [](const int& x) { return x >= 5; };
    Sequence<int>* big = listSeq1.Where(IsBig);
    cout << "Where(x>=5): ";
    PrintSequence(big);

    int sum = listSeq1.Reduce(0, Add);
    cout << "Reduce(sum=0): " << sum << "\n";

    Sequence<int>* sub = listSeq1.GetSubsequence(1, 3);
    cout << "GetSubsequence(1..3): ";
    PrintSequence(sub);

    cout << "\n";

    delete doubled;
    delete big;
    delete sub;

    ListSequence<int> emptyList(arr1, 0);
    cout << "Length: " << emptyList.GetLength() << "\n";
    try {
        emptyList.GetFirst();
    } catch (const out_of_range&) {
        cout << "GetFirst() on empty → OK\n";
    }
    Sequence<int>* emptyMapped = emptyList.Map(Square);
    cout << "Map on empty → Length: " << emptyMapped->GetLength() << "\n";
    Sequence<int>* emptyFiltered = emptyList.Where(IsEven);
    cout << "Where on empty → Length: " << emptyFiltered->GetLength() << "\n\n";

    delete emptyMapped;
    delete emptyFiltered;

    int arr2[] = {100};
    ListSequence<int> singleList(arr2, 1);
    PrintSequence(&singleList);

    Sequence<int>* singleMapped = singleList.Map(Square);
    cout << "Map(x*x): ";
    PrintSequence(singleMapped);

    Sequence<int>* singleFiltered = singleList.Where(IsBig);
    cout << "Where(x>=5): ";
    PrintSequence(singleFiltered);

    int singleSum = singleList.Reduce(0, Add);
    cout << "Reduce(sum=0): " << singleSum << "\n";

    cout << "\n";

    delete singleMapped;
    delete singleFiltered;
}

int main() {
    try {
        test_ImmutableArraySequence();
        test_MutableArraySequence();
        test_ListSequence();
    }
    catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}