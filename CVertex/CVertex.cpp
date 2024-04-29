#include "CVertex.h"
#include <iostream>
#include <algorithm>
#include <set>



CVertex::CVertex(string value) :sVERName(value) {}

void CVertex::VERModifyName(const string& svalue)
{
	// we change the value of the vertex to "svalue"'s content
	sVERName = svalue;
}

const string CVertex::VERGetName() const
{
	return sVERName;
}

const unordered_map<string, bool>& CVertex::VERGetArcIn() const
{
	return sVERArcIn;
}

const unordered_map<string, bool>& CVertex::VERGetArcOut() const
{
	return sVERArcOut;
}

void CVertex::VERGROModifyArcIn(const string& sKey, bool value)
{
	// this changes the value at the 'sKey' value of the sVERArcIn to the bool 'value' of the methods'parameters
	sVERArcIn[sKey] = value;
}

void CVertex::VERGROModifyArcOut(const string& sKey, bool value)
{
	// this changes the value at the 'sKey' value of the sVERArcOut to the bool 'value' of the methods'parameters
	sVERArcOut[sKey] = value;
}

void CVertex::VERAddInTheMapIn(const string& sKey)
{
	// by assigining true to the sVERArcIn at the key's value
	// means there is an arc in the IN direction from the vertex at value = "key" to this (CVertex)
	sVERArcIn[sKey] = true;
}

void CVertex::VERAddInTheMapOut(const string& sKey)
{
	// by assigining true to the sVERArcOut at the key's value
	// means there is an arc in the OUT direction from the vertex at value = "key" to this (CVertex)
	sVERArcOut[sKey] = true;
}

const string CVertex::VERPrintAdjacentNeightboors()
{
	string res = "";
	set<string> see;

	for (unordered_map<string, bool>::iterator it = sVERArcIn.begin(); it != sVERArcIn.end(); it++)
	{
		if (it->second)
		{
			if (see.insert(it->first).second)
				res += it->first + " ";
		}
	}

	for (unordered_map<string, bool>::iterator it = sVERArcOut.begin(); it != sVERArcOut.end(); it++)
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

const string CVertex::VERGetAllListOutVertices()
{
	string res = "";
	set<string> see;

	// to have accessed to all Vertices we can reach from this vertex which will represents the deb of the arcs...
	// we use the sVERArcOut unordered_map because its keys are the values of the Vertices we seek for
	// 
	// so with a for loop, we ieterate through the sVERArcOut unordered_map
	for (unordered_map<string, bool>::iterator it = sVERArcOut.begin(); it != sVERArcOut.end(); it++)
	{
		// we need to check if the value at the key's value is true or not, because if it 's not,
		// then that means their is no arc reachable anymore from this vertex
		if (it->second == true)
		{
			if (see.insert(it->first).second)
				res += VERGetName() + " -> " + it->first + " | ";
		}
	}

	if (res.empty())
		res = "None";

	return res;

}

void CVertex::VERRemoveArcFromArcIn(const string& sKey)
{
	// by assigining false to the sVERArcIn at the key's value
	// means we are removing an arc in the IN direction from the vertex at value = "key" to this (CVertex)
	if (sVERArcIn.find(sKey) != sVERArcIn.end())
		sVERArcIn[sKey] = false;
}

void CVertex::VERRemoveArcFromArcOut(const string& sKey)
{
	// by assigining false to the sVERArcOut at the key's value
	// means we are removing an arc in the OUT direction from the vertex at value = "key" to this (CVertex)
	if (sVERArcOut.find(sKey) != sVERArcOut.end())
		sVERArcOut[sKey] = false;
}

const set<string> CVertex::VERGetAllAdjacencesVerticesValues()
{
	// to get all adjacents Vertices of a vertex, we need to collect all 
	// values of the Vertices connected to the vertex in the IN and the OUT direction
	set<string> see;


	for (unordered_map<string, bool>::iterator it = sVERArcIn.begin(); it != sVERArcIn.end(); it++)
	{
		// of coursre, we should check if there is an arc between our vertex and the current vertex
		// by looking at the pair->second (if true, there is an arc unless there isn't)
		if (it->second)
		{
			see.insert(it->first);
		}
	}

	for (unordered_map<string, bool>::iterator it = sVERArcOut.begin(); it != sVERArcOut.end(); it++)
	{
		// of coursre, we should check if there is an arc between our vertex and the current vertex
		// by looking at the pair->second (if true, there is an arc unless there isn't)
		if (it->second)
		{
			see.insert(it->first);
		}
	}
	return see;
}

void CVertex::VERChangeKeysVerArcIn(const string& sOldVal, const string& sNewVal)
{
	// to change the value of the key that contains the involved arc (here in the IN direction of the vertex)
	//
	// 
	// we should first store the value of the old record...
	bool bOldValue = sVERArcIn[sOldVal];

	// then, we should remove the old record of the arc 
	sVERArcIn.erase(sOldVal);

	// then we store that stored value into the "newVal" of the key that contains the involved arc
	VERGROModifyArcIn(sNewVal, bOldValue);
}

void CVertex::VERChangeKeysVerArcOut(const string& sOldVal, const string& sNewVal)
{
	// to change the value of the key that contains the involved arc (here in the OUT direction of the vertex)
	//
	// 
	// we should first store the value of the old record...
	bool bOldValue = sVERArcOut[sOldVal];

	// then, we should remove the old record of the arc 
	sVERArcOut.erase(sOldVal);

	// then we store that stored value into the "newVal" of the key that contains the involved arc
	VERGROModifyArcOut(sNewVal, bOldValue);
}
