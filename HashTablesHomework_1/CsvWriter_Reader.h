#ifndef CsvWriter_Reader
#define CsvWriter_Reader
#include <cstdio>
#include "Header.h"
#include "Student.h"
#include "cstdlib"
#include "AdamsStringSplitter.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class CsvWriter
{
private: 
	vector<string> _lines;
	int _currentLine;

public:
	//constructor
	CsvWriter()
	{
		_currentLine = 0;
		_lines.push_back("");
	}

	void addText(string text)
	{
		string &currentLine = _lines[_currentLine];
		if(currentLine.length() > 0)
		{
			currentLine += ",";
		}
		currentLine += "\"" + text + "\"";
	}

	void nextLine()
	{
		_lines.push_back("");
		_currentLine++;
	}

	string toCsvString() const
	{
		string output = "";
		for (vector<string>::const_iterator iter = _lines.begin(); iter != _lines.end(); iter++)
		{
			output += *iter + "\n";
		}
		return output;
	}
};

class Csv_Reader
{
private:
	string _filename;
	string _grades;

	unordered_map<string, Student>_excel;
public:
	const void setFileName(string name)
	{
	_filename = name;
	}

	Csv_Reader(){/*Defualt Constructor*/}

	Csv_Reader(unordered_map<string,Student> &excel)
	{
		_excel = excel;
		 setFileName("");
	}

	unordered_map<string,Student> &giveStudentGrade()
	{
		return _excel;
	}

	Csv_Reader(const Csv_Reader &other)
	{
		_excel = other._excel;
		setFileName(other._filename);
		_excel = other._excel;
	}

	Csv_Reader(Csv_Reader &&other)
	{
		_excel = other._excel;
		setFileName(other._filename);
		swap(other._excel, _excel);
	}

	Csv_Reader& operator=(const Csv_Reader &other)
	{
		_excel = other._excel;
		setFileName(other._filename);
		_excel = other._excel;
		return *this;
	}

	Csv_Reader& operator=(Csv_Reader &other)
	{
		_excel = other._excel;
		setFileName(other._filename);
		swap(other._excel, _excel);
		return *this;
	}

	~Csv_Reader(){unordered_map<string, Student>temp;
	_excel.swap(temp);}

	void Read()
	{
		ifstream infile;

		string line = " ";
		string id = "";

		
		vector<string> temp;
		vector<string> score;
		vector<int> fullScore{};
		
		int index = 0;
		infile.open(_filename);
		
		while (!infile.good())
		{
			cout << "Bad File Name" << endl;
			getline(cin, _filename);
		}
		
		while(!infile.eof())	
		{
			getline(infile, line, '\n');

			cout << line << endl;

//			score = AdamsStringSplitter::ThisSplit(line);
			
			
			
			
			int comma_index = 0;
			for(int i = 0; i < line.size(); i++)
			{
				if(line[i] == ',')
				{
					comma_index++;
				}
				if(comma_index == 2)
				{
					line[i] = ',';
					break;
				}
			}
			score = AdamsStringSplitter::split(line, ",");
			if(score.size() != 1)
			{
				for(int i = 0; i < score[i].size(); i++)
				{
					if(score[1][i] == ' ')
					{
						score[1][i] = ',';
						break;
					}
				}
			}
			score = score;
			
			
			
			//This isnt working ^^^
			if(index == 0)
			{
			}
			if(index == 1)
			{
				for (int i = 0; i < score.size(); i++)
				{
					if(i != 0 && i != 1)
					{
						fullScore.push_back(stoi(score[i]));
					}
				}
			}
			else // THIS LINE IS NOT A HEADER
			{
				id = score[0];

				if(_excel.find(id) != _excel.end())
				{
					Student current = _excel.at(id);
					current.addBook(_grades, fullScore[0], stoi(score[2]));
					for(int i = 3; i < score.size(); i++)
					{
						current.addGraded(_grades, fullScore[i-2], stoi(score[i]), (i-2));
					}
					_excel.at(id) = current;
				}	
					else
				{
					Student current(id, score[1]);
					current.addBook(_grades,fullScore[0], stoi(score[2]));

					for(int i = 3; i < score.size(); i++)
					{
						current.addGraded(_grades, fullScore[i-2], stoi(score[i]), (i - 2));
					}
					_excel.emplace(id, current);
				}
			}

		
			if(infile.eof())
			{
				break;
			}
			index++;
		}//End of !infile.eof
	}//End of Read
};

#endif