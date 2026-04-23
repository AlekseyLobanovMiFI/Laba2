#include <iostream>
#include "ui.h"

using namespace std;

int main() {
    cout << "=== Sequence Project ===\n";

    try {
        RunUI();
    }
    catch (const exception& e) {
        cerr << "Unhandled exception: " << e.what() << "\n";
    }
    catch (...) {
        cerr << "Unknown error occurred\n";
    }

    cout << "Program finished.\n";
    return 0;
}