#ifndef Points_h
#define Points_h

#include "Header.h"
using namespace std;

class Points
{
private:
	string _student;
	int _PointsPossible;
	int _PointsEarned;

public:
	Points(){/* THIS CONSTRUCTOR SHOULD NOT BE USED */}

	Points(string student, int possible, int earned)
	{
		_student = student;
		_PointsPossible = possible;
		_PointsEarned = earned;
	}


};

#endif