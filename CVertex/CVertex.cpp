#include "CVertex.h"
#include <iostream>


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
