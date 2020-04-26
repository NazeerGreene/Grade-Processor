//student header file
#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class student {
public:

	//default constructor
    student(); 

	//valid constructor
    explicit student(const std::string&, student* = nullptr);

	//setter for student's name
    void setName(std::string&);

	//getter for student's name
    std::string getName(void) const;

	//print student's assessment grades (quizzes, midterms, final)
    void printGrades(void) const;

	//getter for student's numerical grade (0-100)
    float numGrade(void) const;

	//getter for student's letter grade (A-F)
    char letterGrade(void) const;

	//getter for assessment score stored in float array
    int getScore(int index) const;

	//setter for next pointer
    void setNextPtr(student*);

	//getter for next pointer
    student* getNextPtr(void) const;

	//shortcut for inserting student object into linked list (after this object)
    void insertAfter(student*);

//-----------------------------OVERLOADED OPERATORS---------------------------------

	//returns true if this object comes before other student object alphabetically
    bool operator>(const student& other) const;

	//returns true if this object comes after other student object alphabetically
    bool operator<(const student& other) const; 

	//returns true if student's name equals other's name
    bool operator==(const student& other) const; 

private:

	//helper function - sets student name and grades array
    void processInfo(const std::string& info);

private:
    std::string name{};
    int grades[7]{};
    student* nextptr{ nullptr };
};

#endif