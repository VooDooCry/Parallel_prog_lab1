#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include "gtest/gtest.h"

using namespace std;

struct Group {
    string name;
    string faculty;
};

struct Student {
    string name;
    Group group;
};

double addend1(double x) {
    return x*x*x * cos(x);
}

double addend2(double x) {
    return exp(2*x);
}

double y(double x) {
    return addend1(x) - addend2(x);
}

vector<Group> availableGroups = {
    {"IT-101", "Information technology"},
    {"IT-102", "Information technology"},
    {"PH-201", "Physics"},
    {"MAT-301", "Mathematics"}
};

void displayGroups() {
    cout << "Available groups:\n";
    for (size_t i = 0; i < availableGroups.size(); ++i) {
        cout << i + 1 << ". " << availableGroups[i].name 
             << " (" << availableGroups[i].faculty << ")\n";
    }
}

Group selectGroup(int choice) {
    if (choice > 0 && choice <= availableGroups.size()) {
        return availableGroups[choice - 1];
    } else {
        cout << "Incorrect selection, default group assigned\n";
        return availableGroups[0];
    }
}

Student addStudent(const string& name, int groupChoice) {
    Student newStudent;
    newStudent.name = name;
    newStudent.group = selectGroup(groupChoice);
    return newStudent;
}

Student addStudentInteractive() {
    Student newStudent;
    cout << "Enter the student's name: ";
    getline(cin, newStudent.name);
    
    displayGroups();
    cout << "Select a group (1-" << availableGroups.size() << "): ";
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    newStudent.group = selectGroup(choice);
    return newStudent;
}

TEST(FunctionTesting, test_addend1) {
    EXPECT_NEAR(addend1(0), 0.0, 1e-6);
    EXPECT_NEAR(addend1(1), 0.54030230586, 1e-6);
    EXPECT_NEAR(addend1(-1), -0.54030230586, 1e-6);
    EXPECT_NEAR(addend1(M_PI), -M_PI*M_PI*M_PI, 1e-6);
}

TEST(FunctionTesting, test_addend2) {
    EXPECT_NEAR(addend2(0), 1.0, 1e-6);
    EXPECT_NEAR(addend2(1), 7.38905609893, 1e-6);
    EXPECT_NEAR(addend2(-1), 0.13533528323, 1e-6);
    EXPECT_NEAR(addend2(-100), 0.0, 1e-6);
}

TEST(FunctionTesting, test_y) {
    EXPECT_NEAR(y(0), -1.0, 1e-6);
    EXPECT_NEAR(y(1), 0.54030230586-7.38905609893, 1e-6);
    EXPECT_NEAR(y(-1), -0.54030230586-0.13533528323, 1e-6);
}

TEST(GroupTest, GroupCreation) {
    Group g{"IT-101", "Information technology"};
    EXPECT_EQ(g.name, "IT-101");
    EXPECT_EQ(g.faculty, "Information technology");
}

TEST(StudentTest, StudentCreation) {
    Group defaultGroup = availableGroups[0];
    Student s;
    s.name = "Test Student";
    s.group = defaultGroup;
    
    EXPECT_EQ(s.name, "Test Student");
    EXPECT_EQ(s.group.name, "IT-101");
    EXPECT_EQ(s.group.faculty, "Information technology");
}

TEST(GroupTest, AvailableGroupsSize) {
    EXPECT_EQ(availableGroups.size(), 4);
}

TEST(GroupTest, SelectGroupValid) {
    Group g = selectGroup(2);
    EXPECT_EQ(g.name, "IT-102");
    EXPECT_EQ(g.faculty, "Information technology");
}

TEST(GroupTest, SelectGroupInvalid) {
    Group g = selectGroup(0);
    EXPECT_EQ(g.name, "IT-101");
    
    g = selectGroup(999);
    EXPECT_EQ(g.name, "IT-101");
}

TEST(StudentTest, AddStudent) {
    Student s = addStudent("Test Student", 3);
    EXPECT_EQ(s.name, "Test Student");
    EXPECT_EQ(s.group.name, "PH-201");
    EXPECT_EQ(s.group.faculty, "Physics");
}

TEST(GroupTest, DisplayGroupsTest) {
    stringstream buffer;
    streambuf* oldCout = cout.rdbuf(buffer.rdbuf());
    
    displayGroups();
    
    cout.rdbuf(oldCout);
    string output = buffer.str();
    
    EXPECT_NE(output.find("Available groups:"), string::npos);
    EXPECT_NE(output.find("IT-101"), string::npos);
    EXPECT_NE(output.find("Physics"), string::npos);
}

TEST(StudentTest, AddStudentInteractiveTest) {
    streambuf* origCin = cin.rdbuf();
    streambuf* origCout = cout.rdbuf();
    
    stringstream testInput;
    testInput << "John Doe\n2\n";
    cin.rdbuf(testInput.rdbuf());
    
    stringstream testOutput;
    cout.rdbuf(testOutput.rdbuf());
    
    Student s = addStudentInteractive();
    
    cin.rdbuf(origCin);
    cout.rdbuf(origCout);
    
    EXPECT_EQ(s.name, "John Doe");
    EXPECT_EQ(s.group.name, "IT-102");
}

int runTests() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

int runInteractive() {
    vector<Student> students;
    char choice;
    
    do {
        students.push_back(addStudentInteractive());
        cout << "Add another student? (y/n): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (choice == 'y' || choice == 'Y');
    
    cout << "\nAdded students:\n";
    for (const auto& student : students) {
        cout << student.name << " - " << student.group.name 
             << " (" << student.group.faculty << ")\n";
    }

    return 0;
}

TEST(InteractiveTest, RunInteractiveSingleStudent) {
    streambuf* origCin = cin.rdbuf();
    streambuf* origCout = cout.rdbuf();
    
    stringstream testInput;
    testInput << "Alice Smith\n1\nn\n";
    cin.rdbuf(testInput.rdbuf());
    
    stringstream testOutput;
    cout.rdbuf(testOutput.rdbuf());
    
    runInteractive();
    
    cin.rdbuf(origCin);
    cout.rdbuf(origCout);
    
    string output = testOutput.str();
    EXPECT_NE(output.find("Added students:"), string::npos);
    EXPECT_NE(output.find("Alice Smith"), string::npos);
    EXPECT_NE(output.find("IT-101"), string::npos);
}

TEST(InteractiveTest, RunInteractiveTwoStudents) {
    streambuf* origCin = cin.rdbuf();
    streambuf* origCout = cout.rdbuf();
    
    stringstream testInput;
    testInput << "Bob Johnson\n2\ny\nCharlie Brown\n3\nn\n";
    cin.rdbuf(testInput.rdbuf());
    
    stringstream testOutput;
    cout.rdbuf(testOutput.rdbuf());
    
    runInteractive();
    
    cin.rdbuf(origCin);
    cout.rdbuf(origCout);
    
    string output = testOutput.str();
    EXPECT_NE(output.find("Bob Johnson"), string::npos);
    EXPECT_NE(output.find("Charlie Brown"), string::npos);
    EXPECT_NE(output.find("IT-102"), string::npos);
    EXPECT_NE(output.find("PH-201"), string::npos);
}

TEST(InteractiveTest, RunInteractiveInvalidGroup) {
    streambuf* origCin = cin.rdbuf();
    streambuf* origCout = cout.rdbuf();
    
    stringstream testInput;
    testInput << "Test Student\n999\nn\n";
    cin.rdbuf(testInput.rdbuf());
    
    stringstream testOutput;
    cout.rdbuf(testOutput.rdbuf());
    
    runInteractive();
    
    cin.rdbuf(origCin);
    cout.rdbuf(origCout);
    
    string output = testOutput.str();
    EXPECT_NE(output.find("Incorrect selection"), string::npos);
    EXPECT_NE(output.find("IT-101"), string::npos); // Должна быть выбрана группа по умолчанию
}

int main(int argc, char **argv) {
    #ifdef COVERAGE
    cout << "Running with code coverage instrumentation" << endl;
    #endif
   
    if (argc > 1 && string(argv[1]) == "test") {
        return runTests();
    } else {
        return runInteractive();
    }
}