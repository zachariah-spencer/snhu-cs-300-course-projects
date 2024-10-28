#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Structure for course details
struct Course {
    string courseNumber;  // Course code
    string courseTitle;   // Course name
    vector<string> prerequisites;  // List of prerequisites
};

vector<Course> courses;  // Store list of courses

// Load course data from a file
void loadCourses(const string& fileName) {
    ifstream inputFile(fileName);  // Open file for reading
    if (!inputFile.is_open()) {    // Error handling for file opening failure
        cout << "Error: Could not open file: " << fileName << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        Course course;
        size_t pos = line.find(",");
        course.courseNumber = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(",");
        course.courseTitle = line.substr(0, pos);
        line.erase(0, pos + 1);

        while (!line.empty()) {
            pos = line.find(",");
            string prereq = line.substr(0, pos);
            course.prerequisites.push_back(prereq);
            if (pos == string::npos) break;
            line.erase(0, pos + 1);
        }

        courses.push_back(course);
    }

    inputFile.close();  // Close the file after reading
}

// Display the course list sorted by course number
void displayCourses() {
    sort(courses.begin(), courses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
        });

    cout << "Course List:" << endl;
    for (const auto& course : courses) {
        cout << course.courseNumber << ": " << course.courseTitle << endl;
    }
}

// Display detailed information about a specific course
void displayCourseDetails(const string& courseNumber) {
    auto it = find_if(courses.begin(), courses.end(), [&](const Course& c) {
        return c.courseNumber == courseNumber;
        });

    if (it != courses.end()) {
        cout << it->courseNumber << ": " << it->courseTitle << endl;
        cout << "Prerequisites: ";
        if (it->prerequisites.empty()) {
            cout << "None" << endl;
        }
        else {
            for (const auto& prereq : it->prerequisites) {
                cout << prereq << ", ";
            }
            cout << endl;
        }
    }
    else {
        cout << "Course not found." << endl;
    }
}

int main() {
    string fileName, courseNumber;
    int option;

    cout << "Welcome to the Course Planner" << endl;

    do {
        cout << endl << endl << endl;
        cout << "Menu Options:" << endl;
        cout << "1. Load Course Data" << endl;
        cout << "2. Show Course List" << endl;
        cout << "3. Show Course Details" << endl;
        cout << "9. Exit" << endl;
        cout << "Choose an option: ";
        cin >> option;

        switch (option) {
        case 1:
            cout << "Enter the file name: ";
            cin >> fileName;
            loadCourses(fileName);
            break;
        case 2:
            displayCourses();
            break;
        case 3:
            cout << "Enter the course number: ";
            cin >> courseNumber;
            displayCourseDetails(courseNumber);
            break;
        case 9:
            cout << "Exiting the program. Thank you!" << endl;
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    } while (option != 9);

    return 0;
}
