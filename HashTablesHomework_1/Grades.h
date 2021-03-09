#ifndef Grades_h
#define Grades_h
#include "Header.h"
#include "Points.h"

using namespace std;

class Grades
{
private:
	string _name;
	vector<Points> ranking;
	int _PossibleGrade;
	int _EarnedGrade;

public:
	Grades()
	{//Defualt Constructor
		_name = "This Class";
		_PossibleGrade = 100;
		_EarnedGrade = 75;
	}

	Grades(string name, int possible, int earned)
	{//Actual Constructor
		_name = name;
		_PossibleGrade = possible;
		_EarnedGrade = earned;
	}

	Grades(const Grades &other)
	{//Copy Constructor
		_name = other._name;
		_PossibleGrade = other._PossibleGrade;
		_EarnedGrade = other._EarnedGrade;
		ranking = other.ranking;
	}

	Grades &operator=(const Grades &other)
	{//Copy Operator
		_name = other._name;
		_PossibleGrade = other._PossibleGrade;
		_EarnedGrade = other._EarnedGrade;
		ranking = other.ranking;
		return *this;
	}

	Grades(Grades &&other)
	{//Move Constructor
		_name = other._name;
		_PossibleGrade = other._PossibleGrade;
		_EarnedGrade = other._EarnedGrade;
		swap(other.ranking, ranking);
	}

	Grades &operator=(Grades &&other)
	{//Move Operator
		_name = other._name;
		_PossibleGrade = other._PossibleGrade;
		_EarnedGrade = other._EarnedGrade;
		swap(other.ranking, ranking);
		return *this;
	}

	~Grades()/*This is the Deconstructor*/
	{vector<Points>temp;
	ranking.swap(temp);}
	
	void addGraded(int possible, int earned, int index)
	{
		string student = _name;
		student += index;
		Points Graded(student, possible, earned);
		ranking.push_back(Graded);
	}
};

#endif