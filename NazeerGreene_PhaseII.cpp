//Processing grade data through a csv file, 04/25
//Developer: Na'zeer Greene
//GitHub: @NazeerGreene
//LinkedIn: Nazeer Greene, URL: https://www.linkedin.com/in/na-zeer-greene-940430195

#include "required.cpp"

int main(int argc, char* args[]) {

    if (argc != 3) {
        cout << args[0] << " expected arguments: inputFile.txt outFile.txt" << endl;
        exit(EXIT_FAILURE);
    }

    GradeBook<student> book{ args[1], args[2] };
    book.readFileAndCreateLinkedList();
    book.displayMaxMinAvg();
    book.storeStudentNameAndLetterGrade();

}// end of main