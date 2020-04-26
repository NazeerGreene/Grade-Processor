C++ Final Project: Grade Processor Using Objected Oriented Programming and Linked List

The GradeBook class is templatized because it should work if you create a child class of the 
student class or another class containing a student object, provided that the new class 
has the following functions:

- getNextPtr()
- setNextPtr()
- letterGrade()
- getName()
- getScore()

...which needs to do little more than call its parent's function, or the student object function, 
of the same name. And so while it may not be polymorphic, it does allow for expansion under inheritance 
and composition.
