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
#define no_value_to_read 23

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
	void PARReadFile(const string& sfilename)
	{
		// we first open the file
		ifstream flux(sfilename);

		// we verify if the file is successfully opened
		if (flux)
		{
			// we declared a stirng variable to store each read line
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

		// this value will correspond to the line of the starting point of the sSectionName
		int idx = 0;

		for (vector<string>::iterator it = PARAllLines.begin(); it != PARAllLines.end(); it++)
		{
			// we put the current line into uppercase after removing tabs and spaces at the beginning and the end
			currentLineStr = PARTrimString(PARUppercaseOf(*it));
			// we first try to get the position of the sectionName
			pos = currentLineStr.find(PARTrimString(PARUppercaseOf(sSectionName)));
			// we indeed find a corresponded value
			if (pos != string::npos)
			{
				// then we do the same with the sDelimiterAffectation and the same for the sDelimiterBegin
				if ((currentLineStr.find(sDelimiterAffectation) != string::npos) && (currentLineStr.find(sDelimiterBegin) != string::npos))
				{
					break;
				}
			}
			idx++;
		}

		// if we did find the sSectionName
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
				sNameElement  : string representing the name of the element we want to analyze (eg: here it's "numero" for "numero=2")
				sDelimiter : string representing the delimiter between the name of the element and its value (eg: here it's "2" for "numero=2")
	* Needs : a file needed to be read first by the PARReadFile's method
	* Returns : const string
	* Leads : returns the value of the element read
	*******************************************************************************
	*/
	const string PARAnalyzeSectionElement(const string& sLine, const string& sNameElement, const string& sDelimiter="=")
	{
		// we declare the varaible that will conrrespond to the position of the "nameElement"
		size_t pos = string::npos;

		// we 
		string currentLineStr = PARTrimString(PARUppercaseOf(sLine));

		// we try to find the "nameElement" over the case sensitive thing by putting 
		// the nameElemnt to uppercase, and by triming it
		pos = currentLineStr.find(PARTrimString(PARUppercaseOf(sNameElement)));


		// if we indeed find the nameElement
		if (pos != string::npos)
		{
			// then we do the same for the sDelimiter
			pos = currentLineStr.find(sDelimiter);

			// if we indeed find a correspond value
			if (pos != string::npos)
			{
				// then we check if there is some  
				if (PARTrimString(sLine).size() == pos)
				{
					// if yes, then we throw an exception meaning there is no value to read for the nameElement
					throw CException(delimiter_not_found, "No value found to parse the line of the file", "Parser.h", 169);
				}
				else
				{
					// if not, we return the value after the sDelimiter until the end of the value's size
					return PARTrimString(PARTrimString(sLine).substr(pos + 1, PARTrimString(sLine).size()));
				}
			}
		}
		else // if we didn't find some delimiter, that's meaned the user has made some errors and need to correct that, so we throw an exception
			throw CException(delimiter_not_found, "Error on finding the delimiter to parse the line of the file", "Parser.h", 161);
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
	const string PARGetLineContains(const string& sName)
	{
		size_t pos;
		string currentLineStr;
		// to find the line that contained "name", we need to verify by a loop :
		// if there is a line in the PARAllLines's that contained the "name"
		for (vector<string>::iterator it = PARAllLines.begin(); it != PARAllLines.end(); it++)
		{
			// and again, we trim the current line and put it to uppercase to get reid od the sensitive thing
			currentLineStr = PARTrimString(PARUppercaseOf(*it));

			// now we try to fing a valid line that contains the "name" we are looking for
			pos = currentLineStr.find(PARTrimString(PARUppercaseOf(sName)));
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
	* Leads : the string trimed unless we return an empty string if the sValue is empty at the beginning
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

			// we get the position of the last tabulation or the last space at the beginning of the "sValue"
			size_t start_pos_char = max(fst_char_not_space, fst_char_not_tab);

			// to return a trim value of the sValue : 
			// we just need to find the min pos of the character at the end that is not a space or a tabulation
			// =>  min(lst_char_not_space, lst_char_not_tab)
			// then the slice between that value and the start_pos_char 
			// the "1" value we add is because the start_pos_char is one step behind the true start position of the sValue's content
			return sValue.substr(start_pos_char, min(lst_char_not_space, lst_char_not_tab) - start_pos_char + 1);
		}

		// we return an empty string as the "sValue" we try to trim is of course empty
		return "";
	}

	/**
	*******************************************************************************
	* PARUppercaseOf
	* *****************************************************************************
	* Entries : sValue: const string : the string to put into uppercase
	* Needs : None
	* Returns : void
	* Leads : Return the uppercase of the parameter
	*******************************************************************************
	*/
	const string PARUppercaseOf(const string& sStr)
	{
		// we declare another string because we can't make changes directly on a constant value
		string res = sStr;
		// this method transform, takes 4 parameters : 
		// the first : an iterator at the begining of the string
		// the second : an iteraotr to the end of the string
		// the third one : an iterator to where to start putting to uppercase
		// the fourth one : a fonction that puts a character took in parameter into uppercase

		// so basically, this transform's method acts like a for loop and loop into
		// the character of the string starting by the position defined by the third parameter  
		transform(res.begin(), res.end(), res.begin(), [](unsigned char c) { return toupper(c); });

		return res;
	}

	/**
	*******************************************************************************
	* PARContainsSpaceOrTab
	* *****************************************************************************
	* Entries : sValue: const string : the string to verify if it contains space or tabulation 
	* Needs : None
	* Returns : void
	* Leads : returns true if there is indeed a tabulation or sapce in the parameter's value unless false
	*******************************************************************************
	*/
	bool PARContainsSpaceOrTab(const string& sValue)
	{
		// we just try to find a position of a tabulation or a space, 
		// if yes thne we return true unless we return false
		return (sValue.find(" ") != string::npos) || (sValue.find("\t") != string::npos);
	}
};

#endif // PARSER_H
