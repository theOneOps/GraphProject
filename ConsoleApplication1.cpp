
#include <iostream>
#include "CArc/Arc.h"
#include "CVertex/CVertex.h"
#include "PrintGraph/CPrintGraph.h"
#include "Parser/Parser.h"
#include "CGraph/CGraphNOrient.h"
#include "CGraph/CGraphOrient.h"
#include "Parser/CGraphParser.h"
#include "CException/CException.h"

#include <algorithm>

using namespace std;

//#define wrong_number_of_args 404

/*
	* const string PARTrimString(const string& sValue)
	{
		if (!sValue.empty())
		{
			// we take the max of those fst values
			size_t fst_char_not_space = sValue.find_first_not_of(" ");
			size_t fst_char_not_tab = sValue.find_first_not_of(" \t");

			// we take the min of those last values
			size_t lst_char_not_space = sValue.find_last_not_of(" ");
			size_t lst_char_not_tab = sValue.find_last_not_of("\t ");


			size_t start_pos_char = max(fst_char_not_space, fst_char_not_tab);


			return sValue.substr(start_pos_char, min(lst_char_not_space, lst_char_not_tab) - start_pos_char + 1);
		}
		else
			throw CException(delimiter_not_found, "the string to trim is empty", "Parser.h", 234);
	}

	const string PARUppercaseOf(const string& str)
	{
		string res = str;
		transform(res.begin(), res.end(), res.begin(), [](unsigned char c) { return toupper(c); });
		return res;
	}

	void printStringFromVector(vector<string>& vec)
	{
		for (string word : vec)
			cout << word << endl;
	}

	const string PARAnalyzeSectionElement(const string& sLine, const string& nameElement, const string& sDelimiter = "=")
	{
		size_t pos = string::npos;

		string currentLineStr = PARTrimString(PARUppercaseOf(sLine));

		pos = currentLineStr.find(PARTrimString(PARUppercaseOf(nameElement)));

		if (pos != string::npos)
		{
			pos = currentLineStr.find(sDelimiter);

			cout << "pos delimiter " << pos + 1 << endl;


			if (pos != string::npos)
			{
				if (PARTrimString(sLine).size() == pos)
				{
					throw CException(delimiter_not_found, "No value found to parse the line of the file", "Parser.h", 139);
				}
				else
					return PARTrimString(PARTrimString(sLine).substr(pos + 1, PARTrimString(sLine).size()));
			}
		}
		else // unless we throw an exception
			throw CException(delimiter_not_found, "Error on finding the delimiter to parse the line of the file", "Parser.h", 139);
	}
*/

/*
* 
* int main(int argc, char* argv[])
{	
	if (argc == 2)
	{
		CGraphParser<CVertex, CArc> parser;
		parser.GPRMain(argv[1]);
	}
	else
		cout << "you have to call the executable like this : ConsoleApplication1.exe  path_to_your_file";

	/*
		string res = "Hello	world ==  ";
		cout << "|" << PARUppercaseOf(PARSplitString(res)) << "|" << endl;


	//Parser parser;

	//parser.PARReadFile("graph.txt");
	//parser.PARPrintAllLines();


return 0;
}
*/

int main()
{
	cout << "hello world" << endl;
	return 0;
}

