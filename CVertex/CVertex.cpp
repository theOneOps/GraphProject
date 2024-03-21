#include "CVertex.h"
#include <iostream>
#include <algorithm>
#include <set>


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
	set<string> see;

	for (auto it = sVERArcIn.begin(); it != sVERArcIn.end(); it++)
	{
		if (it->second)
		{
			if (see.insert(it->first).second)
				res += it->first + " ";
		}
	}

	for (auto it = sVERArcOut.begin(); it != sVERArcOut.end(); it++)
	{
		if (it->second)
		{
			if (see.insert(it->first).second)
				res += it->first + " ";
		}
	}

	if (res.empty())
		res = "None";

	return res;
}

void CVertex::removeArcFromArcIn(const string& s)
{
	if (sVERArcIn.find(s) != sVERArcIn.end())
		sVERArcIn[s] = false;
}

void CVertex::removeArcFromArcOut(const string& s)
{
	if (sVERArcOut.find(s) != sVERArcOut.end())
		sVERArcOut[s] = false;
}



set<string> CVertex::getAllAdjacenceVertexToAVertex()
{
	set<string> see;

	for (auto it = sVERArcIn.begin(); it != sVERArcIn.end(); it++)
	{
		if (it->second)
		{
			see.insert(it->first);
		}
	}

	for (auto it = sVERArcOut.begin(); it != sVERArcOut.end(); it++)
	{
		if (it->second)
		{
			see.insert(it->first);
		}
	}

	return see;
}
