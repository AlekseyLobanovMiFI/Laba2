#ifndef AUTOTESTS_H
#define AUTOTESTS_H

#include <string>

extern bool verbose;

void RunAllTests();
void RunTest(void (*testFunc)(), const std::string& name);

void Test_ArraySequence();
void Test_ListSequence();
void Test_Mutable();
void Test_Immutable();
void Test_Empty();
void Test_Comparison();
void Test_Stress();

#endif