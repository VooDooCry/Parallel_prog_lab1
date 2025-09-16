#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include "gtest/gtest.h"
//2. y=x^3 cos(x) - e^(2x)
using namespace std;

struct Group {
    string name;
    string faculty;
};


struct Student {
    string name;
    Group group;
};

double addend1(double x)
{
	return x*x*x * cos(x);
}

double addend2(double x)
{
	return exp(2*x);
}
double y(double x)
{
	return  addend1(x)-addend2(x);
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

Student addStudent() {
    Student newStudent;
    cout << "Enter the student's name:";
    cin >> newStudent.name;
    
    displayGroups();
    cout << "Select a group (1-" << availableGroups.size() << "): ";
    int choice;
    cin >> choice;
    
    newStudent.group = selectGroup(choice);
    return newStudent;
}

TEST(FunctionTesting, test_addend1) {
  EXPECT_NEAR(addend1(0),0.0,1e-6);
  EXPECT_NEAR(addend1(1),0.54030230586,1e-6);
  EXPECT_NEAR(addend1(-1),-0.54030230586,1e-6);
}

TEST(FunctionTesting, test_addend2) {
  EXPECT_NEAR(addend2(0),1.0,1e-6);
  EXPECT_NEAR(addend2(1),7.38905609893,1e-6);
  EXPECT_NEAR(addend2(-1),0.13533528323,1e-6);
}

TEST(FunctionTesting, test_y){
  EXPECT_NEAR(y(0),-1.0,1e-6);
  EXPECT_NEAR(y(1),0.54030230586-7.38905609893,1e-6);
  EXPECT_NEAR(y(-1),-0.54030230586-0.13533528323,1e-6);
}


TEST(GroupTest, GroupCreation) {
    Group g{"IT-101", "Information technology"};
    EXPECT_EQ(g.name, "IT-101");
    EXPECT_EQ(g.faculty, "Information technology");
}

TEST(StudentTest, StudentWithDefaultGroup) {
    Group defaultGroup = availableGroups[0];
    Student s;
    s.name = "Test Student";
    s.group = defaultGroup;
    
    EXPECT_FALSE(s.name.empty());
    EXPECT_FALSE(s.group.name.empty());
    EXPECT_FALSE(s.group.faculty.empty());
}

TEST(GroupTest, AvailableGroupsSize) {
    EXPECT_GE(availableGroups.size(), 4); 
}

TEST(StudentTest, GroupSelectionTest) {
    
    Group group1 = selectGroup(1);
    EXPECT_EQ(group1.name, "IT-101");
    
    Group defaultGroup = selectGroup(999);
    EXPECT_EQ(defaultGroup.name, "IT-101");
}

int main(int argc, char **argv)
{
    #ifdef COVERAGE
    std::cout << "Running with code coverage instrumentation" << std::endl;
    #endif
   
    if (argc > 1 && string(argv[1]) == "test") {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }


    vector<Student> students;
    char choice;
    
    do {
        students.push_back(addStudent());
        cout << "Add another student? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
    
    cout << "\nAdded students:\n";
    for (const auto& student : students) {
        cout << student.name << " - " << student.group.name 
             << " (" << student.group.faculty << ")\n";
    }

    return 0;
}
