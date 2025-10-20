//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Jeremy White
// Version     : 3.14
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <sstream>
#include <list>

using namespace std;

struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

class HashTable {
private:
    static const int HASH_TABLE_SIZE = 1009; // Prime number for better distribution
    list<Course>* table;

public:
    HashTable() {
        table = new list<Course>[HASH_TABLE_SIZE];
    }

    int hashFunction(string courseNumber) {
        int hash = 0;
        for (char c : courseNumber) {
            hash = (hash * 31 + c) % HASH_TABLE_SIZE;
        }
        return hash;
    }

    void insert(Course course) {
        int index = hashFunction(course.courseNumber);
        table[index].push_back(course);
    }

    Course* search(string courseNumber) {
        transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);
        int index = hashFunction(courseNumber);

        for (auto& course : table[index]) {
            string storedCourseNumber = course.courseNumber;
            transform(storedCourseNumber.begin(), storedCourseNumber.end(),
                     storedCourseNumber.begin(), ::toupper);

            if (storedCourseNumber == courseNumber) {
                return &course;
            }
        }
        return nullptr;
    }

    vector<Course> getAllCourses() {
        vector<Course> courses;
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            for (const Course& course : table[i]) {
                courses.push_back(course);
            }
        }
        return courses;
    }

    bool isEmpty() {
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            if (!table[i].empty()) {
                return false;
            }
        }
        return true;
    }

    ~HashTable() {
        delete[] table;
    }
};

HashTable courseTable;

bool validatePrerequisites(const Course& course, const set<string>& validCourses) {
    for (const string& prereq : course.prerequisites) {

        if (validCourses.find(prereq) == validCourses.end()) {
            cout << "Warning: Invalid prerequisite " << prereq
                 << " for course " << course.courseNumber << endl;
            return false;
        }
    }
    return true;
}

void loadDataStructure(string filename) {
    string filepath = "src/" + filename;
    cout << "Attempting to open file: " << filepath << endl;

    ifstream file(filepath);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filepath << endl;
        cout << "Current working directory contents:" << endl;
        system("dir");
        return;
    }

    cout << "File opened successfully. Reading contents..." << endl;

    string line;
    set<string> validCourseNumbers;

    // First pass to collect valid course numbers
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber;
        getline(ss, courseNumber, ',');
        validCourseNumbers.insert(courseNumber);
    }

    // Reset file to beginning
    file.clear();
    file.seekg(0);

    // Second pass to create courses
    while (getline(file, line)) {
        cout << "Read line: " << line << endl;

        stringstream ss(line);
        Course course;
        string token;

        // Get course number
        if (getline(ss, token, ',')) {
            course.courseNumber = token;
        }

        // Get course name
        if (getline(ss, token, ',')) {
            course.courseName = token;
        }

        // Get prerequisites
        while (getline(ss, token, ',')) {
            if (!token.empty()) {
                course.prerequisites.push_back(token);
            }
        }

        if (!course.courseNumber.empty()) {
            courseTable.insert(course);
            cout << "Added course: " << course.courseNumber << " - " << course.courseName << endl;
        }
    }

    file.close();
    cout << "File loading completed." << endl;
}



void printCourse(Course* course) {
    cout << course->courseNumber << ", " << course->courseName << endl;
    if (course->prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    }
    else {
        cout << "Prerequisites: ";
        for (const string& prereq : course->prerequisites) {
            Course* prereqCourse = courseTable.search(prereq);
            if (prereqCourse != nullptr) {
                cout << prereq << " - " << prereqCourse->courseName << "; ";
            }
        }
        cout << endl;
    }
}

void printSortedCourseList() {
    vector<Course> courses = courseTable.getAllCourses();
    sort(courses.begin(), courses.end(),
         [](const Course& a, const Course& b) { return a.courseNumber < b.courseNumber; });

    cout << "Here is a sample schedule:" << endl;
    cout << "------------------------------------" << endl;
    for (const Course& course : courses) {
        cout << course.courseNumber << " | " << course.courseName << endl;
    }
    cout << "------------------------------------" << endl;
}

void displayMenu() {
    bool running = true;

    while (running) {
        cout << "\nWelcome to the Course Planner" << endl;
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course Information" << endl;
        cout << "9. Exit" << endl;
        cout << "\nWhat would you like to do? ";

        string input;
        getline(cin, input);
        int choice;

        try {
            choice = stoi(input);
        } catch (...) {
            choice = 0;
        }

        switch(choice) {
            case 1: {
                cout << "Enter the file name: ";
                string filename;
                getline(cin, filename);
                loadDataStructure(filename);
                break;
            }
            case 2:
                if (courseTable.isEmpty()) {
                    cout << "Please load data first (Option 1)" << endl;
                }
                else {
                    printSortedCourseList();
                }
                break;
            case 3:
                if (courseTable.isEmpty()) {
                    cout << "Please load data first (Option 1)" << endl;
                }
                else {
                     string courseNumber;
                     cout << "Enter course number: ";
                     getline(cin, courseNumber);

                     // Convert input to uppercase for consistency and prevent errors
                     transform(courseNumber.begin(), courseNumber.end(),
                             courseNumber.begin(), ::toupper);

                     Course* course = courseTable.search(courseNumber);
                     if (course != nullptr) {
                         printCourse(course);
                     }
                     else {
                         cout << "Course not found." << endl;
                     }
                }
                break;
            case 9:
                cout << "Thank you for using the course planner!" << endl;
                running = false;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }
}

int main() {
    displayMenu();
    return 0;
}
