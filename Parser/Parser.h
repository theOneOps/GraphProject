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
#define delimiter_not_found 22
#define the_number_of_vertex_not_found 23

using namespace std;

/**********************************************************
*  Class : Parser management
* *********************************************************
* ROLE : parse a file, given into parameter
* *********************************************************
* VERSION: 1.0
* AUTHOR: Selly Bill-Gate MEDEWOU
		  Jeremie YANG
* DATE: 28/03/2024
* *********************************************************
*
*/
class Parser
{
private:
	// container of all lines of the read file
	vector<string> PARAllLines;
public:

	/**
	*******************************************************************************
	* PARReadFile
	* *****************************************************************************
	* Entries : filename : string representing the file to read/to parse
	* Needs : None
	* Returns : void
	* Leads : throw an exception if it can't open the file unless it fills
	* the PARAllLines's container with each line of the file
	*******************************************************************************
	*/
	void PARReadFile(const string& filename)
	{
		// we first open the file
		ifstream flux(filename);

		// we verify if the file is successfully opened
		if (flux)
		{
			// we declared a stirng variable tostore each read line
			string line;
			while (getline(flux, line))
			{
				// we add each line into the container's PARAllLines
				PARAllLines.push_back(line);
			}
		}
		else // unless we throw an exception
			throw CException(file_not_open, "Error on opening the file to read", "Parser.h", 44);
	}

	/**
	*******************************************************************************
	* PARAnalyzeSection
	* *****************************************************************************
	* Entries : sSectionName : string representing the name of the section to read plus the first delimiter of the section (eg:"Sommets=[" for "Sommets=[2, 3]")
	*			sDelimiterEnd : string representing the last delimiter of the section (eg: "]" for "Sommets=[2, 3]")
	* Needs : a file needed to be read first by the PARReadFile's method
	* Returns : const vector<string>
	* Leads : Returns a vector containing each line of the section (each line between the sSectionName and the sDelimiterEnd)
	*******************************************************************************
	*/
	const vector<string> PARAnalyzeSection(const string& sSectionName,  const string& sDelimiterEnd)
	{
		vector<string> elements;
		size_t pos = string::npos;
		int idx = 0;

		// with a for loop, we iterate over the PARAllLines's container to find the position of the sSectionName's value
		for (vector<string>::iterator it = PARAllLines.begin(); it != PARAllLines.end(); it++)
		{
			pos = it->find(sSectionName);
			if (pos != string::npos)
			{
				//cout << "pos different de zero " << "pos trouve en position " << idx << " " << *it << endl;
				break;
			}
			idx++;
		}

		// if we did find something the sSectionName
		if (idx != PARAllLines.size())
		{
			// we create an iterator initalized on the first line of the section to read
			vector<string>::iterator itSectionName = PARAllLines.begin() + idx + 1;

			// we have finally get all the lines of the section
			for (; *itSectionName != sDelimiterEnd; itSectionName++)
			{
				// we populate the variable elements's container with each line of the section
				elements.push_back(*itSectionName);
			}
		}
		else // if there is no sSectionName in any line read before, then we throw an exception
		{
			string errorMessage = "Error on finding the sectionName '" + sSectionName + "'";
			throw CException(section_name_not_found, errorMessage, "Parser.h", 75);
		}
		
		return elements;
}
	
	/**
	*******************************************************************************
	* AnalyzeSectionElement
	* *****************************************************************************
	* Entries : sLine : string representing the line we want to analyze
				sElement  : string representing the name of the element we want to analyze (eg: here it's "numero" for "numero=2")
				sDelimiter : string representing the delimiter between the name of the element and its value (eg: here it's "2" for "numero=2")
	* Needs : a file needed to be read first by the PARReadFile's method
	* Returns : const string
	* Leads : returns the value of the element read
	*******************************************************************************
	*/
	const string AnalyzeSectionElement(const string& sLine,  const string& sDelimiter="=")
	{
		// first we get the value of the delimiter
		size_t pos = sLine.find(sDelimiter);
		// if we found it, then we retuns the string between the character after 
		// the position of the delimiter until the end of the line
		if (pos)
			return sLine.substr(pos + 1, sLine.size());
		else // unless we throw an exception
			throw CException(delimiter_not_found, "Error on finding the delimiter to parse the line of the file", "Parser.h", 139);

	}

	/**
	*******************************************************************************
	* getLineContains
	* *****************************************************************************
	* Entries : sName : string representing the value to search for
	* Needs : a file needed to be read first by the PARReadFile's method
	* Returns : const string
	* Leads : returns a string that contains the line containing the value of sName
	*******************************************************************************
	*/
	const string getLineContains(const string& name)
	{
		size_t pos;
		// to find the line that contained "name", we need to verify if :
		for (vector<string>::iterator it = PARAllLines.begin(); it != PARAllLines.end(); it++)
		{
			// there is a line that conatains "name"
			pos = it->find(name);
			// if yes, then we return that line
			if (pos != string::npos)
			{
				return *it;
				break;
			}
		}
		// unless, we return an empty string
		return "";
	}

	/**
	*******************************************************************************
	* PARPrintAllLines
	* *****************************************************************************
	* Entries : None
	* Needs : a file needed to be read first by the PARReadFile's method
	* Returns : void
	* Leads : print each line read in the read file
	*******************************************************************************
	*/
	void PARPrintAllLines() const
	{
		for (string line : PARAllLines)
		{
			cout << line << endl;
		}
	} 
};

#endif // PARSER_H
