#include <iostream>
#include "menu.h"
#include "autotests.h"

using namespace std;

void ShowMenu() {
    cout << "\n===== MENU =====\n";
    cout << "1. Run ALL tests\n";
    cout << "2. Toggle VERBOSE\n";
    cout << "0. Exit\n";
    cout << "Choice: ";
}

void HandleMenu(int choice) {
    switch (choice) {
        case 1:
            RunAllTests();
            break;

        case 2:
            verbose = !verbose;
            cout << "Verbose: " << (verbose ? "ON\n" : "OFF\n");
            break;

        case 0:
            cout << "Exit\n";
            break;

        default:
            cout << "Invalid\n";
    }
}