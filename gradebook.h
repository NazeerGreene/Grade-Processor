//gradebook header file
#ifndef GRADEBOOK_H
#define GRADEBOOK_H

#include <string>

template <typename T>
class GradeBook {
public:
    //default
    GradeBook();

    //valid constructor
    GradeBook(const std::string, const std::string);

    //deconstructor -- delete all the nodes in the list -- frees allocated memory
    ~GradeBook();

	//to add or change the clientInputFile
	void newClientOutFile(const std::string);

	//to add or change the clientOutputFile
	void newClientInFile(const std::string);

    //reads csv file; allocates memory for linked list;
	//returns true if read is successful;
	//returns false if input file is not provided
    bool readFileAndCreateLinkedList(void);

    //prints out assessment statistics
    void displayMaxMinAvg(void);

    //writes student name and grade to file;
    //max length of name should be 19 characters;
	//returns true if write is successful;
	//returns false if output file is not provided
    bool storeStudentNameAndLetterGrade(void) const;

    //setter for head pointer of linked list
    void setHeadPtr(T* newHeadPtr);

    //getter for head pointer of linked list
    T* getHeadPtr(void) const;

private:
    //helper function - sets min and max array, average, and totalStudents
    void processGrades(void);

private:
    std::string clientInputFile;
    std::string clientOutputFile;
    T* headptr{ nullptr };

    //arrays for all seven assessments
    int minimum[7]{ 100,100,100,100,100,100,100 }; //reference point, assume the best
    int maximum[7]{};                              //reference point, assume the worst
    float average[7]{};
    int totalStudents = 0;
};

#endif