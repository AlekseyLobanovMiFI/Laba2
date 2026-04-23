#include <iostream>
#include "autotests.h"

#include "arraySequence.h"
#include "listSequence.h"
#include "MutableArraySequence.h"
#include "immutableArraySequence.h"

using namespace std;

// ================= CONFIG =================

bool verbose = false;

// ================= COLORS =================

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

// ================= STATS =================

int totalChecks = 0;
int failedChecks = 0;

int totalTests = 0;
int failedTests = 0;

bool currentTestFailed = false;

// ================= HELPERS =================

int Square(const int& x) { return x * x; }
bool IsEven(const int& x) { return x % 2 == 0; }
bool IsBig(const int& x) { return x >= 5; }
int Add(const int& a, const int& b) { return a + b; }

// печать последовательности
void PrintSeq(Sequence<int>* seq) {
    cout << "[";
    for (int i = 0; i < seq->GetLength(); i++) {
        cout << seq->Get(i);
        if (i < seq->GetLength() - 1) cout << ", ";
    }
    cout << "]";
}

// ================= ASSERT =================

#define ASSERT_EQ(a,b) \
    totalChecks++; \
    if ((a)!=(b)) { \
        cout << RED << "  FAIL: " << #a << " != " << #b \
             << " (" << (a) << " vs " << (b) << ")" \
             << RESET << "\n"; \
        failedChecks++; \
        currentTestFailed = true; \
    }

#define ASSERT_TRUE(x) \
    totalChecks++; \
    if (!(x)) { \
        cout << RED << "  FAIL: " << #x << RESET << "\n"; \
        failedChecks++; \
        currentTestFailed = true; \
    }

// ================= RUNNER =================

void RunTest(void (*testFunc)(), const string& name) {
    totalTests++;
    currentTestFailed = false;

    cout << YELLOW << "[ RUN      ] " << name << RESET << "\n";

    testFunc();

    if (currentTestFailed) {
        cout << RED << "[  FAILED  ] " << name << RESET << "\n\n";
        failedTests++;
    } else {
        cout << GREEN << "[  PASSED  ] " << name << RESET << "\n\n";
    }
}

// ================= TESTS =================

void Test_ArraySequence() {
    int arr[] = {1,2,3,4,5};
    MutableArraySequence<int> seq(arr, 5);

    auto mapped = seq.Map(Square);

    if (verbose) {
        cout << "  input: "; PrintSeq(&seq); cout << "\n";
        cout << "  mapped: "; PrintSeq(mapped); cout << "\n";
    }

    ASSERT_EQ(mapped->Get(2), 9);

    delete mapped;
}

void Test_ListSequence() {
    int arr[] = {1,3,5,7,9};
    ListSequence<int> seq(arr, 5);

    auto filtered = seq.Where(IsBig);

    if (verbose) {
        cout << "  input: "; PrintSeq(&seq); cout << "\n";
        cout << "  filtered: "; PrintSeq(filtered); cout << "\n";
    }

    ASSERT_EQ(filtered->GetLength(), 3);

    delete filtered;
}

void Test_Mutable() {
    MutableArraySequence<int> seq;

    seq.Append(1);
    seq.Append(2);
    seq.Append(3);

    if (verbose) {
        cout << "  after append: "; PrintSeq(&seq); cout << "\n";
    }

    ASSERT_EQ(seq.GetLength(), 3);
}

void Test_Immutable() {
    int arr[] = {1,2,3,4};
    ImmutableArraySequence<int> seq(arr, 4);

    auto mapped = seq.Map(Square);

    if (verbose) {
        cout << "  original: "; PrintSeq(&seq); cout << "\n";
        cout << "  mapped: "; PrintSeq(mapped); cout << "\n";
    }

    ASSERT_EQ(seq.Get(0), 1);

    delete mapped;
}

void Test_Empty() {
    ListSequence<int> list;

    ASSERT_EQ(list.GetLength(), 0);
}

void Test_Comparison() {
    int arr[] = {1,2,3};

    ImmutableArraySequence<int> imm(arr,3);
    MutableArraySequence<int> mut(arr,3);

    if (verbose) {
        cout << "  immutable: "; PrintSeq(&imm); cout << "\n";
        cout << "  mutable:   "; PrintSeq(&mut); cout << "\n";
    }

    ASSERT_EQ(imm.Get(1), 2);
    ASSERT_EQ(mut.Get(1), 2);
}

void Test_Stress() {
    MutableArraySequence<int> seq;

    for (int i = 0; i < 10000; i++) {
        seq.Append(i);
    }

    ASSERT_EQ(seq.GetLength(), 10000);
}

// ================= RUN ALL =================

void RunAllTests() {
    totalChecks = 0;
    failedChecks = 0;
    totalTests = 0;
    failedTests = 0;

    RunTest(Test_ArraySequence, "ArraySequence");
    RunTest(Test_ListSequence, "ListSequence");
    RunTest(Test_Mutable, "Mutable");
    RunTest(Test_Immutable, "Immutable");
    RunTest(Test_Empty, "Empty");
    RunTest(Test_Comparison, "Comparison");
    RunTest(Test_Stress, "Stress");

    cout << "============================\n";
    cout << "Tests:   " << totalTests << "\n";
    cout << "Failed:  " << failedTests << "\n";
    cout << "Checks:  " << totalChecks << "\n";

    double percent = 100.0 * (totalTests - failedTests) / totalTests;

    cout << "Success: " << percent << "%\n";
    cout << "============================\n";
}