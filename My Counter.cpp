/// My Counter Small Project
// author: Saeed Ahmed
// 18 / 12 / 2022

#include <iostream>
#include <utility>
#include <vector>
#include <fstream>

using namespace std;

struct Item {
    string name;
    double x = 0;
    string unit;

    Item(string name = "name", int x = 0, string unit = "unit") : name(std::move(name)), x(x), unit(std::move(unit)) {

    }
    void print() {
        cout << name << '\t' << x << '\t' << unit << '\n';
    }
};

/// global memory:
vector<Item> myList;
ifstream fin;
ofstream fout;

/// utility functions:
void save_to_file() {
    fout.open("My List.txt");
    for(int i = 1; i < myList.size(); ++i) {
        fout << myList[i].name << '\n' << myList[i].x << '\n' << myList[i].unit << '\n';
    }
    fout.close();
}
void init() {
    myList.push_back(Item("Name", 0, "Unit"));

    Item tmp;
    fin.open("My List.txt");
    while (fin) {
        getline(fin, tmp.name);
        fin >> tmp.x;

        fin.ignore();
        getline(fin, tmp.unit);

        if (!tmp.name.empty())
            myList.push_back(tmp);
    }
    fin.close();
}

/// printing functions:
char main_menu() {
    cout << "\n1: Display my list\n" //
        << "2: Add a new item to track\n" //
        << "3: Modify an item\n"
        << "4: Save Changes\n" //
        << "5: Exit\n"; //
    cout << "\nEnter your option:\n";
    char option; cin >> option;
    return option;
}

/// features functions:
void display_list() {
    int n = myList.size();
    cout << "\n\t**** My List ****\n"
        << "\t-----------------\n";
    for (int i = 1; i < n; ++i) {
        cout << " [" << i << "] "; myList[i].print();
    }
    cout << '\n';
}
void add_new_item() {
    Item tmp;

    cout << "Enter the item's name:\n";
    cin.ignore();
    getline(cin, tmp.name);

    cout << "Enter the initial amount (default = 0):\n"; cin >> tmp.x;

    cin.ignore();
    cout << "Enter the unit of measure:\n";
    getline(cin, tmp.unit);

    myList.push_back(tmp);
}
void modify_item() {
    if (myList.size() == 1) {
        cout << "Empty list !\n";
        return;
    }

    display_list();
    int idx;
    do {
        cout << "Enter the number of the item to modify:\n";
        cin >> idx;
    } while (idx < 1 or idx >= myList.size());

    cout << "Enter the amount to add:\n";
    double amount; cin >> amount; // can be positive (increase) or negative (decrease)

    myList[idx].x += amount;
}

int main() {
    cout << "\n\t\t/\\/\\/\\/\\ My Counter App /\\/\\/\\/\\ \n\n";
    init();

    char option;
    do {
        option = main_menu();
        switch (option) {
            case '1':
                display_list();
                break;
            case '2':
                add_new_item();
                cout << "ADDED~\n";
                break;
            case '3':
                modify_item();
                cout << "MODIFIED~\n";
                break;
            case '4':
                save_to_file();
                cout << "SAVED~\n";
                break;
            case '5':
                cout << "See You Soon :)\n";
                break;
            default: cout << "Wrong Input.. try again\n";
        }
        system("pause");
    } while (option != '5');

    return 0;
}
