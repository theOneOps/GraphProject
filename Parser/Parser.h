#ifndef PARSER_H
#define PARSER_H


#include <iostream>
#include <fstream>
#include "../CArc/Arc.h"
#include "../CVertex/CVertex.h"
#include "../CGraphOrient.h"
#include "../CGraphNOrient.h"
#include "../CPrintGraph.h"

#include <vector>
#include <string>

#define file_not_open 20
#define section_name_not_found 21

using namespace std;

/**********************************************************
*  Class : Parser management
* *********************************************************
* 
* ROLE : parse a file, given into parameter
* 
* *********************************************************
* VERSION: 1.0
* AUTHOR: Selly Bill-Gate MEDEWOU
		  Jeremie YANG
* DATE: 28/03/2024
* *********************************************************
* EXTERNES InCLUSIONS
*/


class Parser
{
private:
	vector<string> PARAllLines;
public:

	void PARReadFile(const string& filename)
	{
		ifstream flux(filename);

		if (flux)
		{
			string line;
			while (getline(flux, line))
			{
				PARAllLines.push_back(line);
			}
		}
		else
			throw CException(file_not_open, "Error on opening the file to read", "Parser.h", 44);
	}

	vector<string> PARAnalyzeSection(const string& sSectionName,  const string& sDelimiterEnd)
	{
		vector<string> elements;
		size_t pos = string::npos;
		int idx = 0;
		for (vector<string>::iterator it = PARAllLines.begin(); it != PARAllLines.end(); it++)
		{
			pos = it->find(sSectionName);
			if (pos != string::npos)
			{
				cout << "pos different de zero " << "pos trouve en position " << idx << " " << *it << endl;
				break;
			}
			idx++;
		}
		if (idx != PARAllLines.size())
		{
			vector<string>::iterator itSectionName = PARAllLines.begin() + idx + 1;

			// we have finally get all the lines of the section
			for (; *itSectionName != sDelimiterEnd; itSectionName++)
			{
				elements.push_back(*itSectionName);
			}

			for (string line : elements)
			{
				cout << line << endl;
			}
		}
		else
		{
			string errorMessage = "Error on finding the sectionName '" + sSectionName + "'";
			throw CException(section_name_not_found, errorMessage, "Parser.h", 75);
		}
		
		return elements;
}
	
	string AnalyzeSectionElement(const string& line, const string& element, const string& sDelimiter="=")
	{
		return line.substr(line.find(sDelimiter)+1, line.size());
	}

	string getLineContains(const string& name)
	{
		size_t pos;
		for (vector<string>::iterator it = PARAllLines.begin(); it != PARAllLines.end(); it++)
		{
			pos = it->find(name);
			if (pos != string::npos)
			{
				return *it;
				break;
			}
		}
		return "";
	}

	void PARPrintAllLines()
	{
		for (string line : PARAllLines)
		{
			cout << line << endl;
		}
	}
};

#endif // PARSER_H
