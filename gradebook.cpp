//gradebook source file
#include "gradebook.h"
#include <fstream>      
#include <iomanip>
#include <cstdlib> 
#include <sstream>
#include <iostream>

template <class NODETYPE>
void insertInAlphaOrder(NODETYPE** root, std::string& info)
{
    NODETYPE* temp = new NODETYPE(info);
    NODETYPE* currentptr = *root;

    if (*root == nullptr) { //linked list is empty
        *root = temp;       //initialize the head
    } // end of if
    else if (*temp < *currentptr) { //new object comes before head
        *root = temp;                                   //new object is the head
        temp->setNextPtr(currentptr);                   //new object points to previous head
    } //end of if
    else {                                      //object is placed somewhere after the head
        NODETYPE* previous = currentptr;
           
        while ( (currentptr != nullptr) and (*temp > *currentptr) ) { //advance until correct placement is found
            previous = currentptr;
            currentptr = currentptr->getNextPtr();
        } //end of while
        currentptr = previous->getNextPtr();
        previous->setNextPtr(temp);
        temp->setNextPtr(currentptr);
        } //end of else
}; //done with insertInAlphaOrder

template<typename T>
GradeBook<T>::GradeBook()
    : clientInputFile(""), clientOutputFile(""), headptr(nullptr) {}; //done with default constructor

template<typename T>
GradeBook<T>::GradeBook(const std::string inputFile, const std::string outputFile)
    : clientInputFile(inputFile), clientOutputFile(outputFile), headptr(nullptr) {}; //done with constructor

template<typename T>
GradeBook<T>::~GradeBook() 
{ 
	T* nextptr = nullptr;
	while (headptr != nullptr) {            //while nodes still present
	    nextptr = headptr->getNextPtr();    //store so remaining nodes aren't lost
	    //std::cout << "Deleting " << headptr->getName() << std::endl;
	    delete headptr;                     //delete current node
	    headptr = nextptr;                  //next node to be deleted
	} //end of while
}; //done with deconstructor

template<typename T>
void GradeBook<T>::newClientInFile(const std::string newfile)
{
	clientInputFile = newfile;
}; //done with newClientInFile

template<typename T>
void GradeBook<T>::newClientOutFile(const std::string newfile){
	clientOutputFile = newfile;
}; //done with newClientOutFile

template<typename T>
bool GradeBook<T>::readFileAndCreateLinkedList(void) 
{
	if (clientInputFile == "")
	    return 0;

	// ifstream constructor opens the file          
	std::ifstream inClientFile(clientInputFile, std::ios::in);

	// exit program if ifstream could not open file
	if (!inClientFile) {
	    std::cerr << clientInputFile << " could not be opened." << std::endl;
	    exit(EXIT_FAILURE);
	}

	// temporary hold for each record in file
	std::string studentInfo;

	//root for linked list
	T* root = nullptr;

	while (getline(inClientFile, studentInfo, '\n')) { //while not EOF, get student record
	    insertInAlphaOrder<T>(&root, studentInfo);     //create and insert new student into linked list
	    totalStudents++;                               //add to total students
	} //end of while

	headptr = root;
	inClientFile.close();

	return true;
}; //done with initiate

template<typename T>
void GradeBook<T>::displayMaxMinAvg(void) 
{
	processGrades();

	const char* assess[7]{ "Q1","Q2","Q3","Q4","MIDI","MIDII","FINAL"};
	//--------------------formatting the assessments-----------------
	std::cout << std::setw(8) << " ";
	for (unsigned int i = 0; i < 7; i++)
	    std::cout << std::setfill(' ') << std::setw(8) << assess[i]; //end of for-loop
	std::cout << std::endl;

	//-----------------printing the avg, min, max--------------------
	std::cout << "Average: ";
	for (unsigned int i = 0; i < 7; i++)
	    std::cout << std::right << std::setw(7) << std::setprecision(4) << average[i] << " "; //end of for-loop
	std::cout << std::endl;

	std::cout << "Minimum: ";
	for (unsigned int i = 0; i < 7; i++)
	    std::cout << std::right << std::setw(7) << minimum[i] << " "; //end of for-loop
	std::cout << std::endl;

	std::cout << "Maximum: ";
	for (unsigned int i = 0; i < 7; i++)
	    std::cout << std::right << std::setw(7) << maximum[i] << " "; //end of for-loop
	std::cout << std::endl;
}; //end of displayBook

template<typename T>
bool GradeBook<T>::storeStudentNameAndLetterGrade(void) const 
{
	if (clientOutputFile == "")
	    return false;

	// ifstream constructor opens the file          
	std::ofstream outClientFile(clientOutputFile, std::ios::out);

	// exit program if ifstream could not open file
	if (!outClientFile) {
	    std::cerr << clientOutputFile << " could not be opened." << std::endl;
	    delete this; //free allocated memory
	    exit(EXIT_FAILURE);
	}

	T* temp = headptr;

	while (temp != nullptr) {
	    outClientFile << std::left << std::setw(20) << temp->getName() //writing student name -- output field for formatting
	        << temp->letterGrade() << std::endl;                  //writing letter grade

	    temp = temp->getNextPtr();
	} //end of while

	outClientFile.close();

	return true;
}; //done with storing grades

template<typename T>
void GradeBook<T>::setHeadPtr(T* newHeadPtr) { headptr = newHeadPtr; }; //done with setHeadPtr

template<typename T>
T* GradeBook<T>::getHeadPtr(void) const { return headptr; }; //done with getHeadPtr

template<typename T>
void GradeBook<T>::processGrades() 
{
	T* temp = headptr;

	while (temp != nullptr) {                   //for each student in gradebook
	    for (unsigned int i = 0; i < 7; i++) {
	        int score = temp->getScore(i);      //get their score for that assessment

	        if (score > maximum[i])             //check for a new maximum per assessment
	            maximum[i] = score;
	        if (score < minimum[i])             //check for a new minimum per assessment
	            minimum[i] = score;
	        average[i] += score;                //add score to average

	    } //done iterating over grades for one student; end of for-loop
	    temp = temp->getNextPtr();              //go to next student
	} //done iterating over students; end of while-loop

	for (unsigned int i = 0; i < 7; i++)        //for each total score in average array
	    average[i] /= totalStudents;            //divide the total score by total students; end of for-loop
}; //done with processGrades