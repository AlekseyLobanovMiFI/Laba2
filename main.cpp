#include <iostream>
#include <stdexcept>

#include "sequence.h"
#include "arraySequence.h"
#include "listSequence.h"
#include "bitSequence.h"
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

// ============================================================================
// 1) Тесты для ImmutableArraySequence
// ============================================================================

int Square(int x) { return x * x; }
bool IsEven(int x) { return x % 2 == 0; }
int Add(int x, int y) { return x + y; }

void test_ImmutableArraySequence() {
    cout << "=== IMMUTABLE ARRAYSEQUENCE ===\n";

    int arr[] = {1, 2, 3, 4, 5};
    ImmutableArraySequence<int> immutableSeq(arr, 5);

    cout << "ImmutableArraySequence: ";
    PrintSequence(&immutableSeq);

    // ============================= Map =========================
    Sequence<int>* mapped = immutableSeq.Map(Square);
    cout << "Map(x*x):               ";
    PrintSequence(mapped);

    // ============================= Where =======================
    Sequence<int>* filtered = immutableSeq.Where(IsEven);
    cout << "Where(even):            ";
    PrintSequence(filtered);

    // ============================= Map + Where chain ===========
    Sequence<int>* chained = immutableSeq.Map(Square)->Where(IsEven);
    cout << "Map(x*x)->Where(even):  ";
    PrintSequence(chained);

    // ============================= Reduce ======================
    int sum = immutableSeq.Reduce(0, Add);
    cout << "Reduce(sum = 0 + x): " << sum << "\n";

    // ============================= SubSequence =================
    Sequence<int>* sub = immutableSeq.GetSubsequence(1, 3);
    cout << "GetSubsequence(1..3):   ";
    PrintSequence(sub);

    // ============================= First/Last ==================
    cout << "GetFirst(): " << immutableSeq.GetFirst() << "\n";
    cout << "GetLast():  " << immutableSeq.GetLast()  << "\n\n";

    delete mapped;
    delete filtered;
    delete chained;
    delete sub;
}

// ============================================================================
// 2) Тесты для MutableArraySequence
// ============================================================================

void test_MutableArraySequence() {
    cout << "=== MUTABLEARRAYSEQUENCE ===\n";

    int arr[] = {1, 2, 3, 4, 5};
    MutableArraySequence<int> mutableSeq(arr, 5);

    cout << "MutableArraySequence: ";
    PrintSequence(&mutableSeq);

      // ============================= Map =========================
    Sequence<int>* mapped = mutableSeq.Map(Square);
    cout << "Map(x*x):               ";
    PrintSequence(mapped);

    // ============================= Where =======================
    Sequence<int>* filtered = mutableSeq.Where(IsEven);
    cout << "Where(even):            ";
    PrintSequence(filtered);

    // ============================= Map + Where chain ===========
    Sequence<int>* chained = mutableSeq.Map(Square)->Where(IsEven);
    cout << "Map(x*x)->Where(even):  ";
    PrintSequence(chained);

    cout << "GetFirst(): " << mutableSeq.GetFirst() << "\n";
    cout << "GetLast():  " << mutableSeq.GetLast()  << "\n";

    Sequence<int>* sub = mutableSeq.GetSubsequence(1, 3);
    cout << "GetSubsequence(1..3): ";
    PrintSequence(sub);

    int sum = mutableSeq.Reduce(0, Add);
    cout << "Reduce(sum): " << sum << "\n";

    delete sub;
}

// ============================================================================
// 3) Тесты для ListSequence
// ============================================================================

void test_ListSequence() {
    cout << "\n=== LIST SEQUENCE (immutable) ===\n";

    int arr[] = {1, 3, 5, 7, 9};
    ListSequence<int> listSeq(arr, 5);

    cout << "ListSequence: ";
    PrintSequence(&listSeq);

    // Map
    auto Twice = [](int x) { return x * 2; };
    Sequence<int>* doubled = listSeq.Map(Twice);
    cout << "Map(x*2):              ";
    PrintSequence(doubled);

    // Where
    auto IsBig = [](int x) { return x >= 5; };
    Sequence<int>* big = listSeq.Where(IsBig);
    cout << "Where(x >= 5):        ";
    PrintSequence(big);

    // Reduce
    int sum = listSeq.Reduce(0, Add);
    cout << "Reduce(sum): " << sum << "\n";

    Sequence<int>* sub = listSeq.GetSubsequence(1, 3);
    cout << "GetSubsequence(1..3): ";
    PrintSequence(sub);

    delete doubled;
    delete big;
    delete sub;
}

// ============================================================================
// 4) Тесты для BitSequence (без Map!)
// ============================================================================
void PrintBitSeq(const BitSequence& bits) {
    int n = bits.GetLength();
    if (n == 0) {
        cout << "[]\n";
        return;
    }
    cout << "[";
    for (int i = 0; i < n; ++i) {
        cout << bits[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]\n";
}

void test_BitSequence() {
    cout << "\n=== BIT SEQUENCE===\n";

    Bit bits[] = {Bit(true),  Bit(false), Bit(true),  Bit(true),
                  Bit(false), Bit(true),  Bit(false), Bit(true)};
    BitSequence bitSeq(bits, 8);

    cout << "Original bitSeq:        ";
    PrintBitSeq(bitSeq);

    // Not
    BitSequence not_res = ~bitSeq;
    cout << "Not (bitSeq):           ";
    PrintBitSeq(not_res);

    // And
    Bit ones[] = {Bit(true), Bit(true), Bit(true), Bit(true)};
    BitSequence mask(ones, 4);
    BitSequence and_res = bitSeq & mask;
    cout << "And (bitSeq & mask):    ";
    PrintBitSeq(and_res);

    // Or
    BitSequence or_res = bitSeq | mask;
    cout << "Or  (bitSeq | mask):    ";
    PrintBitSeq(or_res);

    // Xor
    BitSequence xor_res = bitSeq ^ mask;
    cout << "Xor (bitSeq ^ mask):    ";
    PrintBitSeq(xor_res);

}

// ============================================================================
// main
// ============================================================================

int main() {
    try {
        test_ImmutableArraySequence();

        test_MutableArraySequence();

        test_ListSequence();

        test_BitSequence();
    }
    catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}