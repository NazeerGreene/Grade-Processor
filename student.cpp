//student source file
#include "student.h"
#include <sstream>
#include <iostream>

student::student() : name("N/A") {}; //done with default constructor

student::student(const std::string& studentRec, student* nextPtr) 
{
	processInfo(studentRec);
	setNextPtr(nextPtr);
}; //done with valid constructor

std::string student::getName(void) const { return name; }; //done with getName

void student::setName(std::string& newName) 
{ 
	name = (newName == "" ? "N/A" : newName);
}; //done with setName

void student::printGrades(void) const 
{
	for (unsigned int i = 0; i < 7; i++)
		std::cout << grades[i] << " "; //end of for-loop
	std::cout << std::endl;
}; //done with printGrades

float student::numGrade(void) const 
{
	float numericGrade = 0;
	for (unsigned int i = 0; i < 4; i++) {                       //for the first four quizzes
		numericGrade += static_cast<float>( grades[i] * 0.1 );   //calculate and add grade
	} //end of for-loop
	numericGrade += static_cast<float>( grades[4] * .2 ); //midterm I
	numericGrade += static_cast<float>( grades[5] * .15 ); //midterm II
	numericGrade += static_cast<float>( grades[6] * .25 ); //final test
	return numericGrade;
}; //done with numGrade

char student::letterGrade(void) const 
{
	int numericGrade = static_cast<int>(numGrade());
	switch (numericGrade / 10) {
	case 10:
	case 9:
		return 'A';
	case 8:
		return 'B';
	case 7:
		return 'C';
	case 6:
		return 'D';
	default:
		return 'F';
	} //end of switch
}; //done with letterGrade

int student::getScore(int index) const 
{
	if ( (0 <= index) and (index < 7) ) //within valid subscript range
		return grades[index];           //return grade
	return -1;                          //default return
};

student* student::getNextPtr(void) const { return nextptr; }; //done with getNextPtr

void student::setNextPtr(student* ptr) { nextptr = ptr; };    //done with setNextPtr

void student::insertAfter(student* newptr) 
{
	student* originalNextPtr = getNextPtr(); //get the original next ptr (this->nextptr)
	setNextPtr(newptr);                      //set this next-pointer to the new ptr
	newptr->setNextPtr(originalNextPtr);     //set the new ptr's next to the this's original next
}; //done with insertAfter

//-----------------------------OVERLOADED OPERATORS---------------------------------

bool student::operator>(const student& other) const 
{
	return (name > other.getName()); //name-based comparison
}; //done with overloaded operator >

bool student::operator<(const student& other) const 
{
	return (name < other.getName()); //name-based comparison
}; //done with overloaded operator <

bool student::operator==(const student& other) const 
{
	return (name == other.getName()); //name-based comparison
}; //done with overloaded operator ==

void student::processInfo(const std::string& info) 
{
	std::string studentName;
	std::stringstream studentRecord(info);       //string into buffer for convenience
	getline(studentRecord, studentName, ',');    //get name from buffer
	setName(studentName);                        //check for name validation

	for (unsigned int sub = 0; sub < 7; sub++) { //get all seven comma-delimited grades
		std::string grade;                       //temporary string
		getline(studentRecord, grade, ',');      //space + number stored in string
		grades[sub] = stoi(grade);               //convert and store in int array
	} //end of for-loop
}; //done with processInfo