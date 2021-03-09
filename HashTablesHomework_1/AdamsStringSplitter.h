#ifndef AdamsStringSplitter_h
#define AdamsStringSplitter_h
#include <string>
#include <vector>

using namespace std;

class AdamsStringSplitter
{
private:

public:

	//Breaks apart the supplied text based on the given delimiter
	//static function do not affect the internal state
	//(e.g. variables) of a given class instance
	static vector<string> split(string text, string delimiter)
	{
		//vectors are dynamically expanding arrays
		vector<string> pieces;

		//find the first delimiter
		int location = text.find(delimiter);

		//we are starting at the beginning of our string
		int start = 0;

		//go until we have no more delimiters
		while (location != string::npos)
		{
			//add the current piece to our list of pieces
			string piece = text.substr(start, location - start);
			pieces.push_back(piece);

			//update our index markers for the next round
			start = location + 1;
			location = text.find(delimiter, start);
		}

		//at the end of our loop, we're going to have one trailing piece to take care of.
		//handle that now.
		string piece = text.substr(start, location - start);
		pieces.push_back(piece);

		//now, return the completed vector
		return pieces;
	}

	//This is where the edditing begins!

	static vector<string> ThisSplit(string line)
	{

		vector<string> temp;
		int comma_index = 0;
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] == ',')
			{
				comma_index++;
			}
			if (comma_index == 2)
			{
				line[i] = ',';
				break;
			}
		}
		temp = split(line, ",");
		if (temp.size() != 1)
		{
			for (int i = 0; i < temp[i].size(); i++)
			{
				if (temp[1][i] == ' ')
				{
					temp[1][i] = ',';
					break;
				}
			}
		}
		return temp;
	}//End of While Loop
};


#endif