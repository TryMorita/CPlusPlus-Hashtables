#include "Header.h"
#include "CsvWriter_Reader.h"
#include "HashTable.h"
#include "Calculate.h"
#include "Student.h"
#include "Grades.h"
#include "Points.h"
#include "AdamsStringSplitter.h"

using namespace std;

int main (void)
{
	vector<string> grade{};
	vector<string> finishedGrade{};
	vector<string> gradeBook{}; 
	string redLine = "";
	string person = " ";

	unordered_map<string, Student>ThisBook;

	Csv_Reader read(ThisBook);

	 cout << "Input full File Name Please" << endl;
		getline(cin, redLine);
	
		try {
			string ss = "../Homework 2/inputs/" + redLine;
			read.setFileName(ss);
			gradeBook = AdamsStringSplitter::split(redLine, "_");
			read.Read();
			grade.push_back(redLine);
		}
		catch(const char* e)
		{

		}
		
	return 0;
}