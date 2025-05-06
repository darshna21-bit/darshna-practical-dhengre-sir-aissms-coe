#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Employee {
    int empID;
    string name, designation;
    float salary;
};

// Function to add employee
void addEmployee() {
    ofstream dataFile("employee_data.txt", ios::app);
    ofstream indexFile("employee_index.txt", ios::app);
    Employee emp;

    cout << "Enter Employee ID: ";
    cin >> emp.empID;
    cin.ignore(); // Ignore the newline after empID
    cout << "Enter Name: ";
    getline(cin, emp.name);
    cout << "Enter Designation: ";
    getline(cin, emp.designation);
    cout << "Enter Salary: ";
    cin >> emp.salary;

    // Write employee data to data file
    long position = dataFile.tellp();  // Get the current position of the file pointer
    dataFile << emp.empID << " " << emp.name << " " << emp.designation << " " << emp.salary << "\n";
    
    // Write employee ID and its position to the index file
    indexFile << emp.empID << " " << position << "\n";

    cout << "Employee added.\n";
}

// Function to display employee by ID
void displayEmployee() {
    ifstream indexFile("employee_index.txt");
    ifstream dataFile("employee_data.txt");
    int empID;
    bool found = false;

    cout << "Enter Employee ID to search: ";
    cin >> empID;

    int indexEmpID;
    long dataPosition;
    while (indexFile >> indexEmpID >> dataPosition) {
        if (indexEmpID == empID) {
            found = true;
            dataFile.seekg(dataPosition, ios::beg);

            Employee emp;
            dataFile >> emp.empID >> emp.name >> emp.designation >> emp.salary;
            cout << "ID: " << emp.empID << "\nName: " << emp.name
                 << "\nDesignation: " << emp.designation
                 << "\nSalary: " << emp.salary << endl;
            break;
        }
    }
    if (!found) cout << "Employee not found.\n";
}

// Function to delete employee by ID
void deleteEmployee() {
    ifstream indexFile("employee_index.txt");
    ifstream dataFile("employee_data.txt");
    ofstream tempDataFile("temp_employee_data.txt");
    ofstream tempIndexFile("temp_employee_index.txt");
    
    int empID;
    bool found = false;

    cout << "Enter Employee ID to delete: ";
    cin >> empID;

    int indexEmpID;
    long dataPosition;
    while (indexFile >> indexEmpID >> dataPosition) {
        if (indexEmpID != empID) {
            tempIndexFile << indexEmpID << " " << dataPosition << "\n";
            dataFile.seekg(dataPosition, ios::beg);
            
            Employee emp;
            dataFile >> emp.empID >> emp.name >> emp.designation >> emp.salary;
            tempDataFile << emp.empID << " " << emp.name << " " << emp.designation << " " << emp.salary << "\n";
        } else {
            found = true;
        }
    }

    if (found) cout << "Employee deleted.\n";
    else cout << "Employee not found.\n";

    indexFile.close();
    dataFile.close();
    tempDataFile.close();
    tempIndexFile.close();
    
    remove("employee_data.txt");
    remove("employee_index.txt");

    rename("temp_employee_data.txt", "employee_data.txt");
    rename("temp_employee_index.txt", "employee_index.txt");
}

int main() {
    int choice;
    do {
        cout << "\n--- Employee System ---\n";
        cout << "1. Add Employee\n2. Display Employee\n3. Delete Employee\n4. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployee(); break;
            case 3: deleteEmployee(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 4);
    return 0;
}
