#include "CVertex.h"
#include <iostream>


CVertex::CVertex(string value):sVERName(value)
{
}

void CVertex::VERModifyName(const string& svalue)
{
	sVERName = svalue;
}

string CVertex::VERGetName() const
{
	return sVERName;
}

map<string, bool> CVertex::VERGetArcIn() const
{
	return sVERArcIn;
}

map<string, bool> CVertex::VERGetArcOut() const
{
	return sVERArcOut;
}

void CVertex::VERModifyArcIn(const string& key, bool value)
{
	sVERArcIn[key] = value;
}

void CVertex::VERModifyArcOut(const string& key, bool value)
{
	sVERArcOut[key] = value;
}

void CVertex::VERAddInTheMapIn(const string& s)
{
	sVERArcIn[s] = true;
}

void CVertex::VERAddInTheMapOut(const string& s)
{
	sVERArcOut[s] = true;
}

string CVertex::printAdjacentNeightboors()
{
	string res = "";

	for (auto it = sVERArcIn.begin(); it != sVERArcIn.end(); it++)
	{
		if (it->second)
			res += it->first + " ";
	}

	for (auto it = sVERArcOut.begin(); it != sVERArcOut.end(); it++)
	{
		if (it->second)
			res += it->first + " ";
	}

	if (res.empty())
		res = "None";

	return res;
}


