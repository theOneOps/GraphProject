#ifndef PARSER_H
#define PARSER_H


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#define file_not_open 20
#define section_name_not_found 21
#define delimiter_not_found 22
#define the_number_of_vertex_not_found 23
#define no_value_to_read 24

#include "../CException/CException.h"

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
* VARIABLES
* file_not_open 20
  section_name_not_found 21
  delimiter_not_found 22
  the_number_of_vertex_not_found 23
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
	const vector<string> PARAnalyzeSection(const string& sSectionName, const string& sDelimiterAffectation, const string& sDelimiterBegin, const string& sDelimiterEnd)
	{
		vector<string> elements;

		size_t pos = string::npos;
		string currentLineStr = "";

		int idx = 0;

		for (vector<string>::iterator it = PARAllLines.begin(); it != PARAllLines.end(); it++)
		{
			currentLineStr = PARTrimString(PARUppercaseOf(*it));
			//cout << "the current line is " << currentLineStr << endl;
			pos = currentLineStr.find(PARTrimString(PARUppercaseOf(sSectionName)));
			if (pos != string::npos)
			{
				if ((currentLineStr.find(sDelimiterAffectation) != string::npos) && (currentLineStr.find(sDelimiterBegin) != string::npos))
				{
					break;
				}
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
			throw CException(section_name_not_found, errorMessage, "Parser.h", 106);
		}


		return elements;
	}
	
	/**
	*******************************************************************************
	* PARAnalyzeSectionElement
	* *****************************************************************************
	* Entries : sLine : string representing the line we want to analyze
				sElement  : string representing the name of the element we want to analyze (eg: here it's "numero" for "numero=2")
				sDelimiter : string representing the delimiter between the name of the element and its value (eg: here it's "2" for "numero=2")
	* Needs : a file needed to be read first by the PARReadFile's method
	* Returns : const string
	* Leads : returns the value of the element read
	*******************************************************************************
	*/
	const string PARAnalyzeSectionElement(const string& sLine, const string& nameElement, const string& sDelimiter = "=")
	{
		size_t pos = string::npos;

		string currentLineStr = PARTrimString(PARUppercaseOf(sLine));

		pos = currentLineStr.find(PARTrimString(PARUppercaseOf(nameElement)));

		//cout << pos << endl;


		if (pos != string::npos)
		{
			pos = currentLineStr.find(sDelimiter);

			//cout << "pos delimiter " << pos + 1 << endl;

			if (pos != string::npos)
			{
				if (PARTrimString(sLine).size() == pos)
				{
					throw CException(delimiter_not_found, "No value found to parse the line of the file", "Parser.h", 162);
				}
				else
				{
					//cout << sLine << endl;
					return PARTrimString(PARTrimString(sLine).substr(pos + 1, PARTrimString(sLine).size()));

				}
			}
		}
		else // unless we throw an exception
			throw CException(delimiter_not_found, "Error on finding the delimiter to parse the line of the file", "Parser.h", 156);
	}

	/**
	*******************************************************************************
	* PARGetLineContains
	* *****************************************************************************
	* Entries : sName : string representing the value to search for
	* Needs : a file needed to be read first by the PARReadFile's method
	* Returns : const string
	* Leads : returns a string that contains the line containing the value of sName
	*******************************************************************************
	*/
	const string PARGetLineContains(const string& name)
	{
		size_t pos;
		string currentLineStr;
		// to find the line that contained "name", we need to verify if :
		for (vector<string>::iterator it = PARAllLines.begin(); it != PARAllLines.end(); it++)
		{
			// there is a line that conatains "name"

			currentLineStr = PARTrimString(PARUppercaseOf(*it));

			pos = currentLineStr.find(PARTrimString(PARUppercaseOf(name)));
			// if yes, then we return that line
			if (pos != string::npos)
			{
				return *it;
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



	/**
	*******************************************************************************
	* PARTrimString
	* *****************************************************************************
	* Entries : sValue: const string : the string to trim in order to not have space at the beginning and the end
	* Needs : None
	* Returns : const string
	* Leads : the string trimed
	*******************************************************************************
	*/
	const string PARTrimString(const string& sValue)
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

		return "";
	}

	/**
	*******************************************************************************
	* PARUppercaseOf
	* *****************************************************************************
	* Entries : tree : BSTree* = the tree we want to compare with
	* Needs : None
	* Returns : void
	* Leads : Return description
	*******************************************************************************
	*/
	const string PARUppercaseOf(const string& str)
	{
		string res = str;
		transform(res.begin(), res.end(), res.begin(), [](unsigned char c) { return toupper(c); });
		return res;
	}

	/**
	*******************************************************************************
	* FunctionName
	* *****************************************************************************
	* Entries : tree : BSTree* = the tree we want to compare with
	* Needs : None
	* Returns : void
	* Leads : Return description
	*******************************************************************************
	*/
	bool PARContainsSpaceOrTab(const string& sValue)
	{
		return (sValue.find(" ") != string::npos) || (sValue.find("\t") != string::npos);
	}
};

#endif // PARSER_H
