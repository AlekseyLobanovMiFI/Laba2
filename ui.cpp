#include <iostream>
#include "ui.h"
#include "menu.h"

using namespace std;

void RunUI() {
    int choice = -1;

    while (true) {
        ShowMenu();

        if (!(cin >> choice)) {
            cout << "Invalid input. Try again.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 0) {
            cout << "Exiting...\n";
            break;
        }

        HandleMenu(choice);
    }
}