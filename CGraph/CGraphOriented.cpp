#include "CGraphOriented.h"
#include "../CException/CException.h"
#include <algorithm>

CGraphOriented::~CGraphOriented()
{
	for (auto& pair : mGROArcs)
	{
		for (auto& arc : pair.second)
		{
			delete arc;
		}
	}

	for (auto& pair : mGROVertex)
	{
		delete pair.second;
	}
}

// problème avec cette fonction GROModifyVertex...

void CGraphOriented::GROModifyVertex(const string& sVertexName, const string& sValue)
{
	if (mGROVertex.find(sValue) != mGROVertex.end())
	{
		string sErrorMessage = "a vertex with the value " + sValue + " already exists";
		throw CException(vertex_already_existed, sErrorMessage, "CGraphOriented.cpp", 23);
	}
	else
	{
		if (mGROVertex.find(sVertexName) == mGROVertex.end())
		{
			string sErrorMessage = "a vertex with the value " + sVertexName + " doesn't exist";
			throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 23);
		}
		else
		{
			set<string> allAdjacentsVertex = mGROVertex[sVertexName]->getAllAdjacenceVertexToAVertex();

			for (string v : allAdjacentsVertex)
			{
				if (mGROVertex[v]->VERGetArcIn()[sVertexName] == true)
					mGROVertex[v]->changeKeysVerArcIn(sVertexName, sValue);

				if (mGROVertex[v]->VERGetArcOut()[sVertexName] == true)
					mGROVertex[v]->changeKeysVerArcOut(sVertexName, sValue);

				vector<CArc*>& allArcs = mGROArcs[v];
				for (auto it = allArcs.begin(); it != allArcs.end(); it++)
				{
					if ((*it)->ARCGetVertexArr() == sVertexName)
					{
						(*it)->ModifyVertexArr(sValue);
					}

					if ((*it)->ARCGetVertexDep() == sVertexName)
					{
						(*it)->ModifyVertexDep(sValue);
					}
				}
			}

			// problème: on devrait modifier tous les arcs dont la clé d'ajout est sVertexName
			// et la clé par la nouvelle valeur sValue
			// faudrait tester si ça marche...

			if (mGROArcs.find(sVertexName) != mGROArcs.end())
			{
				vector<CArc*>& ARClocalArc = mGROArcs[sVertexName];
				mGROArcs.erase(sVertexName);
				mGROArcs[sValue] = ARClocalArc;
			}

			if (mGROVertex.find(sVertexName) != mGROVertex.end())
			{
				CVertex* VERlocalVertex = mGROVertex[sVertexName];
				VERlocalVertex->VERModifyName(sValue);
				mGROVertex.erase(sVertexName);
				mGROVertex[sValue] = VERlocalVertex;
			}

		}
	}
}

void CGraphOriented::GROAddVertex(CVertex* VerVertex)
{
	if (mGROVertex.count(VerVertex->VERGetName()) == 0)
	{
		mGROVertex[VerVertex->VERGetName()] = VerVertex;
	}
	else
	{
		string sErrorMessage = "a vertex with the value " + VerVertex->VERGetName() + " already exists";
		throw CException(vertex_already_existed, sErrorMessage,  "CGraphOriented.cpp", 87);
	}
}

void CGraphOriented::GROAddArc(CVertex* sVertexDep, CVertex* sVertexArr)
{
	if (GROCheckExistenceOfArc(*sVertexDep, *sVertexArr) == false)
	{
		if (GROCheckExistenceOfArc(*sVertexArr, *sVertexDep) == false)
		{
			sVertexArr->VERAddInTheMapIn(sVertexDep->VERGetName());
			sVertexDep->VERAddInTheMapOut(sVertexArr->VERGetName());

			CArc* arc = new CArc(sVertexDep->VERGetName(), sVertexArr->VERGetName());

			GROAddArcInTheMap(sVertexDep->VERGetName(), arc);

			cout << "arc added successfully ! " << endl;
		}

		else
		{
			string sErrorMessage = "an arc with a vertexDep " + sVertexArr->VERGetName() + " and vertexArr " + sVertexDep->VERGetName() + " already existed in the graph";
			throw CException(arc_already_existed, sErrorMessage, "CGraphOriented.cpp", 79);
		}
		
	}
	else
	{
		string sErrorMessage = "an arc with that vertexDep " + sVertexDep->VERGetName() +" and vertexArr " + sVertexArr->VERGetName() +" already existed in the graph";
		throw CException(arc_already_existed, sErrorMessage, "CGraphOriented.cpp", 79);
	}
}

void CGraphOriented::GROAddArcInTheMap(const string& key, CArc* arc)
{
	mGROArcs[key].push_back(arc);
}

void CGraphOriented::GRORemoveVertex(const string& sNum)
{
	if (mGROVertex.find(sNum) != mGROVertex.end())
	{
		set<string> allAdjacentsVertex = mGROVertex[sNum]->getAllAdjacenceVertexToAVertex();
		if (!allAdjacentsVertex.empty())
		{
			for (string num : allAdjacentsVertex)
			{
				try
				{
					GRORemoveArc(sNum, num);
				}
				catch (CException e)
				{
					GRORemoveArc(num, sNum);
				}
			}
		}
		delete mGROVertex[sNum];
		mGROVertex.erase(sNum);
	}
	else
	{
		string sErrorMessage = "a vertex with the value " + sNum + " doesn't exist";
		throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 143);
	}
}

void CGraphOriented::GRORemoveArc(const string& sNumDep, const string& sNumArr)
{
	if (mGROVertex[sNumDep] && mGROVertex[sNumArr])
	{
		CVertex* vDep = mGROVertex[sNumDep];
		CVertex* vArr = mGROVertex[sNumArr];

		if (GROCheckExistenceOfArc(*vDep, *vArr))
		{
			vDep->removeArcFromArcIn(vArr->VERGetName());
			vDep->removeArcFromArcOut(vArr->VERGetName());
			vArr->removeArcFromArcIn(vDep->VERGetName());
			vArr->removeArcFromArcOut(vDep->VERGetName());

			auto& allArcs = mGROArcs[sNumDep];
			vector<CArc*>::iterator it = allArcs.begin();

			for (; it != allArcs.end(); it++)
			{
				if ((*it)->ARCGetVertexArr() == sNumArr)
				{
					break;
				}
			}

			if (it != allArcs.end())
			{
				allArcs.erase(it);
			}

			/*
			* else
			{
				if (mGROArcs[sNumArr]->ARCGetVertexArr() == sNumDep)
				{
					delete mGROArcs[sNumArr];
					mGROArcs.erase(sNumArr);
				}
			}
			*/
		}
		else
		{
			string sErrorMessage = "an arc with a vertex Dep " + sNumDep + " an vertex Arr " + sNumArr + " doesn't exist";
			throw CException(arc_not_existed, sErrorMessage, "CGraphOriented.cpp", 151);
		}
	}
	else
	{
		string sErrorMessage = "one of those vertex " + sNumDep + " and " + sNumArr + " doesn't exist";
		throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 146);
	}
}

void CGraphOriented::GROInverseArc(const string& valueDep, const string& valueArr)
{
	if (mGROVertex.find(valueDep) == mGROVertex.end())
	{
		string sErrorMessage = "a vertex with the value " + valueDep + " don't exist";
		throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 185);
	}
	else if (mGROVertex.find(valueArr) == mGROVertex.end())
	{
		string sErrorMessage = "a vertex with the value " + valueArr + " don't exist";
		throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 185);
	}
	else
	{
		if (valueDep == valueArr)
		{
			return;
		}
		else if (GROCheckExistenceOfArc(*mGROVertex[valueDep], *mGROVertex[valueArr]))
		{
			mGROVertex[valueDep]->VERModifyArcOut(valueArr, false);
			mGROVertex[valueDep]->VERAddInTheMapIn(valueArr);

			mGROVertex[valueArr]->VERModifyArcIn(valueDep, false);
			mGROVertex[valueArr]->VERAddInTheMapOut(valueDep);

			auto& allArcs = mGROArcs[valueDep];
			vector<CArc*>::iterator it = allArcs.begin();

			for (; it != allArcs.end();)
			{
				if ((*it)->ARCGetVertexArr() == valueArr)
				{
					(*it)->ModifyVertexDep(valueArr);
					(*it)->ModifyVertexArr(valueDep);
					GROAddArcInTheMap(valueArr, *it);
					it = allArcs.erase(it);
					break;
				}
				else
					it++;
			}

			/*
			* CArc* ARClocalArc = mGROArcs[valueDep];

			ARClocalArc->ModifyVertexArr(valueDep);
			ARClocalArc->ModifyVertexDep(valueArr);

			mGROArcs.erase(valueDep);
			mGROArcs[valueArr] = ARClocalArc;
			*/
		}
		else
		{
			string sErrorMessage = "an arc with a vertex Dep " + valueDep + " an vertex Arr " + valueArr + " doesn''t exist";
			throw CException(arc_not_existed, sErrorMessage, "CGraphOriented.cpp", 141);
		}
	}
}

void CGraphOriented::GROInverseAllArcs()
{
	vector<pair<string, string>> res;
	for (auto it = mGROArcs.begin(); it != mGROArcs.end(); it++)
	{
		for (auto& arc : it->second)
		{
			//cout << arc->ARCGetVertexDep() << " | " << arc->ARCGetVertexArr() << endl;
			auto foundDepArr = find(res.begin(), res.end(), make_pair(arc->ARCGetVertexDep(), arc->ARCGetVertexArr()));
			auto foundArrDep = find(res.begin(), res.end(), make_pair(arc->ARCGetVertexArr(), arc->ARCGetVertexDep()));
			if ((foundDepArr == res.end()) || (foundArrDep == res.end()))
			{
				GROInverseArc(arc->ARCGetVertexDep(), arc->ARCGetVertexArr());
				res.push_back(make_pair(arc->ARCGetVertexDep(), arc->ARCGetVertexArr()));
			}
		}
	}
}

bool CGraphOriented::GROCheckExistenceOfArc(CVertex& vertexDep, CVertex& vertexArr)
{
	bool bRes = false;
	if (vertexArr.VERGetArcIn()[vertexDep.VERGetName()] && vertexDep.VERGetArcOut()[vertexArr.VERGetName()])		
		bRes = true;

	return bRes;
}

map<string, CVertex*> CGraphOriented::getGROVertex() const
{
	return mGROVertex;
}
