#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    string rollNo;
    string name;
    string division;
    string address;
};

void addStudent() {
    Student s;
    ofstream fout("students.txt", ios::app);

    cout << "Enter Roll Number: ";
    cin >> s.rollNo;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, s.name);
    cout << "Enter Division: ";
    cin >> s.division;
    cout << "Enter Address: ";
    cin.ignore();
    getline(cin, s.address);

    fout << s.rollNo << "," << s.name << "," << s.division << "," << s.address << "\n";
    fout.close();

    cout << "Student record added.\n";
}

void displayStudent() {
    string roll;
    cout << "Enter Roll Number to search: ";
    cin >> roll;

    ifstream fin("students.txt");
    string line;
    bool found = false;

    while (getline(fin, line)) {
        size_t pos = line.find(",");
        string r = line.substr(0, pos);
        if (r == roll) {
            found = true;
            cout << "Student Details:\n";
            cout << "Roll No: " << r << endl;

            line = line.substr(pos + 1);
            pos = line.find(",");
            cout << "Name: " << line.substr(0, pos) << endl;

            line = line.substr(pos + 1);
            pos = line.find(",");
            cout << "Division: " << line.substr(0, pos) << endl;

            cout << "Address: " << line.substr(pos + 1) << endl;
            break;
        }
    }

    if (!found)
        cout << "Student with Roll No " << roll << " not found.\n";

    fin.close();
}

void deleteStudent() {
    string roll;
    cout << "Enter Roll Number to delete: ";
    cin >> roll;

    ifstream fin("students.txt");
    ofstream temp("temp.txt");
    string line;
    bool deleted = false;

    while (getline(fin, line)) {
        size_t pos = line.find(",");
        string r = line.substr(0, pos);
        if (r == roll) {
            deleted = true;
            continue; // skip writing this line
        }
        temp << line << "\n";
    }

    fin.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (deleted)
        cout << "Student record deleted.\n";
    else
        cout << "Student with Roll No " << roll << " not found.\n";
}

int main() {
    int choice;
    do {
        cout << "\n--- Student Record System ---\n";
        cout << "1. Add Student\n2. Display Student\n3. Delete Student\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudent(); break;
            case 3: deleteStudent(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}

