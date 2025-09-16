#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include "gtest/gtest.h"

//2. y=x^3 cos(x) - e^(2x)

using namespace std;

struct Group {
    string name;
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
    {"ИТ-101", "Информационные технологии"},
    {"ИТ-102", "Информационные технологии"},
    {"ФИ-201", "Физика"},
    {"МАТ-301", "Математика"}
};

void displayGroups() {
    cout << "Доступные группы:\n";
    for (size_t i = 0; i < availableGroups.size(); ++i) {
        cout << i + 1 << ". " << availableGroups[i].name 
             << " (" << availableGroups[i].faculty << ")\n";
    }
}

Student addStudent() {
    Student newStudent;
    cout << "Введите имя студента: ";
    cin >> newStudent.name;
    
    displayGroups();
    cout << "Выберите группу (1-" << availableGroups.size() << "): ";
    int choice;
    cin >> choice;
    
    if (choice > 0 && choice <= availableGroups.size()) {
        newStudent.group = availableGroups[choice - 1];
    } else {
        cout << "Неверный выбор, назначена группа по умолчанию\n";
        newStudent.group = availableGroups[0];
    }
    
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

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
