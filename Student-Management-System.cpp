#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class Student {
public:
    int rollNo;
    char name[50];
    float cgpa;

    void input() {
        cout << "Enter Roll Number: "; cin >> rollNo;
        cout << "Enter Name: "; cin.ignore(); cin.getline(name, 50);
        cout << "Enter CGPA: "; cin >> cgpa;
    }

    void show() {
        cout << left << setw(10) << rollNo << setw(20) << name << setw(5) << cgpa << endl;
    }
};

// Validates if a roll number already exists before adding
bool isDuplicate(int r) {
    Student s;
    ifstream file("records.dat", ios::binary);
    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.rollNo == r) return true;
    }
    return false;
}

void addRecord() {
    Student s;
    s.input();
    if (isDuplicate(s.rollNo)) {
        cout << "Error: Roll Number already exists!\n";
        return;
    }
    ofstream file("records.dat", ios::binary | ios::app);
    file.write(reinterpret_cast<char*>(&s), sizeof(s));
    cout << "Record Saved Successfully.\n";
}

void displayRecords() {
    Student s;
    ifstream file("records.dat", ios::binary);
    if (!file) { cout << "File Error/No Records.\n"; return; }
    
    cout << "\n" << setfill('-') << setw(40) << "-" << setfill(' ') << endl;
    cout << left << setw(10) << "Roll" << setw(20) << "Name" << setw(5) << "CGPA" << endl;
    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) s.show();
}

void deleteRecord(int r) {
    Student s;
    ifstream file("records.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.rollNo != r) temp.write(reinterpret_cast<char*>(&s), sizeof(s));
        else found = true;
    }
    file.close(); temp.close();
    remove("records.dat"); rename("temp.dat", "records.dat");
    if (found) cout << "Record Deleted.\n";
    else cout << "Record Not Found.\n";
}

int main() {
    int choice, roll;
    while (true) {
        cout << "\n1. Add 2. View 3. Delete 4. Exit: "; cin >> choice;
        if (choice == 4) break;
        switch (choice) {
            case 1: addRecord(); break;
            case 2: displayRecords(); break;
            case 3: cout << "Roll to delete: "; cin >> roll; deleteRecord(roll); break;
        }
    }
    return 0;
}
