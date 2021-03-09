#ifndef Student_h
#define Student_h

#include "Grades.h"
#include "Header.h"
using namespace std;

class Student
{
private:
	string _id;
	string _name;
	unordered_map<string, Grades> book;

public:
	Student()
	{
		_id = "00000";
		_name = "Adam";
		book = unordered_map<string, Grades>();
	}

	Student(string id, string name)
	{
		_id = id;
		_name = name;
		book = unordered_map<string, Grades>();
	}

	Student(const Student &other)
	{//Copy
		_id = other._id;
		_name = other._name;
		book = other.book;
	}

	Student(Student &&other)
	{//Move
		swap(other.book, book);
	}

	string getName() const
	{
		return _name;
	}

	string getId() const
	{
		return _id;
	}

	Student &operator=(const Student &other)
	{//Copy Op
		_id = other._id;
		_name = other._name;
		book = other.book;
		return *this;
	}

	Student &operator=(Student &&other)
	{//Move Op
		_id = other._id;
		_name = other._name;
		swap(other.book, book);
		return *this;
	}
	//Deconstructorssss
	~Student(){book.erase(book.begin());}

	void addBook(string bookName, int Possible, int Earned)
	{
		Grades newBook (bookName, Possible, Earned);
		book.insert(make_pair(bookName, newBook));
	}

	void addGraded(string grades, int possible, int earned, int index)
	{
		Grades currentBook = book.at(grades);
		currentBook.addGraded(possible, earned, index);
		book.at(grades) = currentBook;
	}


};

#endif
