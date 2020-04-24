//Processing grade data through a csv file, 04/19
//Developer: Na'zeer Greene
//GitHub: @NazeerGreene, URL: 
//LinkedIn: Nazeer Greene

#include <fstream> // file stream        
#include <iomanip>
#include <string>
#include <cstdlib> 
#include <sstream>
#include <iostream>
using namespace std;

template <class T>
void insertInAlphaOrder(T** root, std::string& info) {
    T* temp = new T(info);
    T* currentptr = *root;

    if (*root == nullptr) { //linked list is empty
        *root = temp;       //initialize the head
    } // end of if
    else if (*temp < *currentptr) { //new object comes before head
        *root = temp;                                   //new object is the head
        temp->setNextPtr(currentptr);                   //new object points to previous head
    } //end of if
    else {                                      //object is placed somewhere after the head
        T* previous = currentptr;
           
        while ( (currentptr != nullptr) and (*temp > *currentptr) ) { //advance until correct placement is found
            previous = currentptr;
            currentptr = currentptr->getNextPtr();
        } //end of while
        currentptr = previous->getNextPtr();
        previous->setNextPtr(temp);
        temp->setNextPtr(currentptr);
        } //end of else
}; //done with insertInAlphaOrder

class student {
public:
    student() : name("N/A") {}; //done with default constructor

    explicit student(const std::string& studentRec, student* nextPtr = nullptr)
    {
        processInfo(studentRec);
        setNextPtr(nextPtr);
    }; //done with valid constructor

    std::string getName(void) const { return name; }; //done with getName
    void setName(std::string& newName) { 
        name = (newName == "" ? "N/A" : newName);
    }; //done with setName

    void printGrades(void) const {
        for (unsigned int i = 0; i < 7; i++)
            cout << grades[i] << " ";
        cout << endl;
    }; //done with printGrades

    float numGrade(void) const {
        float numericGrade = 0;
        for (unsigned int i = 0; i < 4; i++) {                       //for the first four quizzes
            numericGrade += static_cast<float>( grades[i] * 0.1 );   //calculate and add grade
        }
        numericGrade += static_cast<float>( grades[4] * .2 ); //midterm I
        numericGrade += static_cast<float>( grades[5] * .15 ); //midterm II
        numericGrade += static_cast<float>( grades[6] * .25 ); //final test
        return numericGrade;
    }; //done with numGrade

    char letterGrade(void) const {
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
        }
    };

    int getScore(int index) const {
        if ( (0 <= index) and (index < 7) ) //within valid subscript range
            return grades[index];           //return grade
        return -1;                          //default return
    };

    student* getNextPtr(void) const { return nextptr; }; //done with getNextPtr
    void setNextPtr(student* ptr) { nextptr = ptr; };    //done with setNextPtr

    void insertAfter(student* newptr) {
        student* originalNextPtr = getNextPtr(); //get the original next ptr (this->nextptr)
        setNextPtr(newptr);                      //set the current pointer's next to the new ptr
        newptr->setNextPtr(originalNextPtr);     //set the new ptr's next to the current ptr's next in case 
    };

//-----------------------------OVERLOADED OPERATORS---------------------------------

    bool operator>(const student& other) const {
	return (name > other.getName()); //name-based comparison
    }; //done with overloaded operator >

    bool operator<(const student& other) const {
	return (name < other.getName()); //name-based comparison
    }; //done with overloaded operator <

    bool operator==(const student& other) const {
	return (name == other.getName()); //name-based comparison
    }; //done with overloaded operator ==

private:
    void processInfo(const std::string& info) {
        std::string studentName;
        stringstream studentRecord(info);            //string into buffer for convenience
        getline(studentRecord, studentName, ',');    //get name from buffer
        setName(studentName);                        //check for name validation

        for (unsigned int sub = 0; sub < 7; sub++) { //get all seven comma-delimited grades
            string grade;                            //temporary string
            getline(studentRecord, grade, ',');      //space + number stored in string
            grades[sub] = stoi(grade);               //convert and store in int array
        }
    };

private:
    std::string name{};
    int grades[7]{};
    student* nextptr{ nullptr };
};

//-------------------end of students----------------------------------

template <typename T>
class GradeBook {
public:
    //default
    GradeBook()
        : clientInputFile(""), clientOutputFile(""), headptr(nullptr) {}; //done with default constructor
    //valid constructor
    GradeBook(const std::string inputFile, const std::string outputFile)
        : clientInputFile(inputFile), clientOutputFile(outputFile), headptr(nullptr) {}; //done with constructor

    //deconstructor -- delete all the nodes in the list -- frees allocated memory
    ~GradeBook() { 
        T* nextptr = nullptr;
        while (headptr != nullptr) {            //while nodes still present
            nextptr = headptr->getNextPtr();    //store so remaining nodes aren't lost
            //std::cout << "Deleting " << headptr->getName() << endl;
            delete headptr;                     //delete current node
            headptr = nextptr;                  //next node to be deleted
        } //end of while
    }; //done with deconstructor

    bool readFileAndCreateLinkedList(void) {
        if (clientInputFile == "")
            return 0;

        // ifstream constructor opens the file          
        ifstream inClientFile(clientInputFile, ios::in);

        // exit program if ifstream could not open file
        if (!inClientFile) {
            cerr << clientInputFile << " could not be opened." << endl;
            exit(EXIT_FAILURE);
        }

        // temporary hold for each record in file
        std::string studentInfo;

        //root for linked list
        T* root = nullptr;

        while (getline(inClientFile, studentInfo, '\n')) { //while not EOF, get student record
            insertInAlphaOrder<T>(&root, studentInfo);     //create and insert new student into linked list
            totalStudents++;                               //add to total students
        };
        headptr = root;
        inClientFile.close();
        return true;
    }; //done with initiate

    void displayMaxMinAvg(void) {
        processGrades();

        const char* assess[7]{ "Q1","Q2","Q3","Q4","MIDI","MIDII","FINAL"};
        //--------------------formatting the assessments-----------------
        cout << setw(8) << " ";
        for (unsigned int i = 0; i < 7; i++)
            cout << setfill(' ') << setw(8) << assess[i];
        cout << endl;
        //-----------------printing the avg, min, max--------------------
        cout << "Average: ";
        for (unsigned int i = 0; i < 7; i++)
            cout << right << setw(7) << setprecision(4) << average[i] << " ";
        cout << endl;

        cout << "Minimum: ";
        for (unsigned int i = 0; i < 7; i++)
            cout << right << setw(7) << minimum[i] << " ";
        cout << endl;

        cout << "Maximum: ";
        for (unsigned int i = 0; i < 7; i++)
            cout << right << setw(7) << maximum[i] << " ";
        cout << endl;
    }; //end of displayBook

    void storeStudentNameAndLetterGrade(void) const {
        if (clientOutputFile == "")
            return;

        // ifstream constructor opens the file          
        ofstream outClientFile(clientOutputFile, ios::out);

        // exit program if ifstream could not open file
        if (!outClientFile) {
            cerr << clientOutputFile << " could not be opened." << endl;
	    delete this; //free allocated memory
            exit(EXIT_FAILURE);
        }

        T* temp = headptr;

        while (temp != nullptr) {
            outClientFile << left << setw(20) << temp->getName() //writing student name -- output field for formatting
                << temp->letterGrade() << endl;                  //writing letter grade

            temp = temp->getNextPtr();
        }
        outClientFile.close();
    }; //done with storing grades


    void setHeadPtr(T* newHeadPtr) { headptr = newHeadPtr; }; //done with setHeadPtr
    T* getHeadPtr(void) const { return headptr; }; //done with getHeadPtr

private:
    void processGrades() { //helper function
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
            average[i] /= totalStudents;            //divide the total score by total students
    }; //done with processGrades

private:
    std::string clientInputFile;
    std::string clientOutputFile;
    T* headptr{ nullptr };

    int minimum[7]{ 100,100,100,100,100,100,100 }; //reference point, assume the best
    int maximum[7]{};                              //reference point, assume the worst
    float average[7]{};
    int totalStudents = 0;
};

int main(int argc, char* args[]) {
/*
    if (argc != 3) {
        cout << args[0] << " expected arguments: inputFile.txt outFile.txt" << endl;
        exit(EXIT_FAILURE);
    }
    GradeBook<student> book{ args[1], args[2] };*/
    GradeBook<student> book{ "sampleIn.txt", "sampleOut.txt" };
    book.readFileAndCreateLinkedList();
    book.displayMaxMinAvg();
    book.storeStudentNameAndLetterGrade();

}// end of main