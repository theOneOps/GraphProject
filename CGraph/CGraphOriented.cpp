#include "CGraphOriented.h"
#include <set>


CGraphOriented::CGraphOriented()
{
}

CGraphOriented::~CGraphOriented()
{

	for (pair<string, CVertex*> pair : mGROVertex)
	{
		delete pair.second;
	}

	for (pair<pair<string, string>, CArc*> pair : mGROArcs)
	{
		delete pair.second;
	}
}

unordered_map<string, CVertex*>& CGraphOriented::GROGetMVertex()
{
	return mGROVertex;
}

unordered_map<pair<string, string>, CArc*, CGraphOriented::hash_pair>& CGraphOriented::GROGetMArcs()
{
	return mGROArcs;
}

void CGraphOriented::addKeyVertexInMap(const string& key)
{
	CVertex* newVertex = new CVertex(key);
	mGROVertex[key] = newVertex;
}

bool CGraphOriented::ExistenceOfVertex(const string& key)
{
	bool res = false;

	if (GROGetMVertex().count(key) > 0)
		res = true;

	return res;

}

void CGraphOriented::GROAddVertex(const string& key)
{
	if (!ExistenceOfVertex(key))
	{
		addKeyVertexInMap(key);
		cout << "vertex added successfully" << endl;
	}
	else
	{
		string sErrorMessage = "a vertex with the value " + key + " already exists";
		throw CException(vertex_already_existed, sErrorMessage, "CGraphOriented.cpp", 87);
	}
}

void CGraphOriented::GRORemoveVertex(const string& key)
{
	if (ExistenceOfVertex(key))
	{
		CVertex* Vertex = GROGetVertexFromKey(key);

		set<string> adjacentVertecies = Vertex->getAllAdjacenceVertexToAVertex();

		for (string v : adjacentVertecies)
		{
			try
			{
				GRORemoveArc(key, v);
			}
			catch (CException e)
			{
				GRORemoveArc(v, key);
			}
		}
		
		delete Vertex;
		mGROVertex.erase(key);

	}
	else
	{
		string sErrorMessage = "a vertex with the value " + key + " doesn't exist";
		throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 48);
	}
}

void CGraphOriented::GROPrintAllVertecies()
{
	unordered_map<string, CVertex*>::iterator it = mGROVertex.begin();

	for (; it != mGROVertex.end(); it++)
	{
		cout << it->first << endl;
	}
}

void CGraphOriented::PrintAllArcs()
{
	for (pair<pair<string, string>, CArc*> pair : mGROArcs)
	{
		cout << pair.first.first + " " << pair.first.second << endl;
	}
}

void CGraphOriented::GROPrintGraph()
{
	unordered_map<string, CVertex*> VerteciesMap = GROGetVertexMap();
	unordered_map<string, CVertex*>::iterator it = VerteciesMap.begin();

	for (; it != VerteciesMap.end(); it++)
	{
		cout << it->first << " : " << it->second->getAllListInVertecies() << endl;
	}
}

bool CGraphOriented::ExistenceOfArcNOriented(const string& sVertexDep, const string& sVertexArr)
{
	bool res = false;

	if (GROGetMArcs().count(make_pair(sVertexDep, sVertexArr)) > 0)
		res = true;
	return res;
}

void CGraphOriented::addPairKeysMArcs(const string& sVertexDep, const string& sVertexArr)
{
	pair<string, string> pairkeyDepArr{ sVertexDep, sVertexArr };

	CArc* newArc = new CArc(sVertexDep, sVertexArr);

	mGROArcs[pairkeyDepArr] = newArc;

}

void CGraphOriented::GROAddArc(const string& sVertexDep, const string& sVertexArr)
{
	if (ExistenceOfVertex(sVertexDep))
	{
		CVertex* VertexDep = GROGetVertexFromKey(sVertexDep);
		if (ExistenceOfVertex(sVertexArr))
		{
			CVertex* VertexArr = GROGetVertexFromKey(sVertexArr);
			if (!ExistenceOfArcNOriented(sVertexDep, sVertexArr))
			{
				if (!ExistenceOfArcNOriented(sVertexArr, sVertexDep))
				{
					VertexArr->VERAddInTheMapIn(sVertexDep);
					VertexDep->VERAddInTheMapOut(sVertexArr);


					addPairKeysMArcs(sVertexDep, sVertexArr);

					string res = "arc (" + sVertexDep + " " + sVertexArr + ") created successfully";
					cout << res << endl;
				}
				else
				{
					string sErrorMessage = "an arc with a vertexDep " + sVertexDep + " and vertexArr " + sVertexArr + " is already in the graph";
					throw CException(arc_already_existed, sErrorMessage, "CGraphOriented.cpp", 68);
				}
			}
			else
			{
				string sErrorMessage = "an arc with a vertexDep " + sVertexDep + " and vertexArr " + sVertexArr + " is already in the graph";
				throw CException(arc_already_existed, sErrorMessage, "CGraphOriented.cpp", 66);

			}
		}
		else
		{
			string sErrorMessage = "a vertex with the value " + sVertexArr + " doesn't exist";
			throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 70);

		}
	}
	else
	{
		string sErrorMessage = "a vertex with the value " + sVertexDep + " doesn't exist";
		throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 68);
	}
}

void CGraphOriented::GRORemoveArc(const string& sVertexDep, const string& sVertexArr)
{
	if (ExistenceOfVertex(sVertexDep))
	{
		CVertex* VDep = GROGetVertexFromKey(sVertexDep);
		if (ExistenceOfVertex(sVertexArr))
		{
			CVertex* VArr = GROGetVertexFromKey(sVertexArr);

			if (ExistenceOfArcNOriented(sVertexDep, sVertexArr))
			{
				pair<string, string> key{ sVertexDep, sVertexArr };

				CArc* arc = GROGetArcFromKeys(sVertexDep, sVertexArr);

				mGROArcs.erase(key);

				delete arc;

				VDep->removeArcFromArcIn(sVertexArr);
				VDep->removeArcFromArcOut(sVertexArr);
				VArr->removeArcFromArcIn(sVertexDep);
				VArr->removeArcFromArcOut(sVertexDep);

				string res = "arc (" + sVertexDep + " " + sVertexArr + ") removed successfully";

				cout << res << endl;
			}
			else
			{
				string sErrorMessage = "an arc with a vertexDep " + sVertexDep + " and vertexArr " + sVertexArr + " is not in the graph";
				throw CException(arc_already_existed, sErrorMessage, "CGraphOriented.cpp", 178);
			}
		}
		else
		{
			string sErrorMessage = "a vertex with the value " + sVertexArr + " doesn't exist";
			throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 117);
		}
	}
	else
	{
		string sErrorMessage = "a vertex with the value " + sVertexDep + " doesn't exist";
		throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 115);

	}
}

void CGraphOriented::GROModifyVertex(const string& sVertexOldValue, const string& sVertexNewValue)
{
	if (ExistenceOfVertex(sVertexOldValue))
	{
		if (!ExistenceOfVertex(sVertexNewValue))
		{
			CVertex* VertexOldValue = GROGetVertexFromKey(sVertexOldValue);
			set<string> adjacentVertecies = VertexOldValue->getAllAdjacenceVertexToAVertex();

			for (string sAdjVertex : adjacentVertecies)
			{
				CVertex* VAdjVertex = GROGetVertexFromKey(sAdjVertex);
				if (ExistenceOfArcNOriented(sVertexOldValue, sAdjVertex))
				{
					VAdjVertex->changeKeysVerArcIn(sVertexOldValue, sVertexNewValue);
					CArc* arc = GROGetArcFromKeys(sVertexOldValue, sAdjVertex);
					arc->ModifyVertexDep(sVertexNewValue);

					pair<string, string> oldKey{ sVertexOldValue, sAdjVertex };
					pair<string, string> newKey{ sVertexNewValue, sAdjVertex };

					mGROArcs[newKey] = arc;

					mGROArcs.erase(oldKey);
				}
				else
				{
					VAdjVertex->changeKeysVerArcOut(sVertexOldValue, sVertexNewValue);
					CArc* arc = GROGetArcFromKeys(sAdjVertex, sVertexOldValue);
					arc->ModifyVertexArr(sVertexNewValue);

					pair<string, string> oldKey{ sAdjVertex, sVertexOldValue };

					pair<string, string> newKey{ sAdjVertex, sVertexNewValue };

					mGROArcs[newKey] = arc;

					mGROArcs.erase(oldKey);
				}
			}

			VertexOldValue->VERModifyName(sVertexNewValue);
			mGROVertex.erase(sVertexOldValue);
			mGROVertex[sVertexNewValue] = VertexOldValue;
		}
		else
		{
			string sErrorMessage = "a vertex with the value " + sVertexNewValue + " already exists in the graph";
			throw CException(vertex_already_existed, sErrorMessage, "CGraphOriented.cpp", 161);
		}
	}
	else
	{
		string sErrorMessage = "a vertex with the value " + sVertexOldValue + " doesn't exist";
		throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 159);
	}
}

CVertex* CGraphOriented::GROGetVertexFromKey(const string& key)
{
	return mGROVertex[key];
}

CArc* CGraphOriented::GROGetArcFromKeys(const string& sVertexDep, const string& sVertexArr)
{
	pair<string, string> pairKey{ sVertexDep, sVertexArr };
	return mGROArcs[pairKey];
}

void CGraphOriented::GRORemoveArcFromMap(const string& sVertexDep, const string& sVertexArr)
{
	pair<string, string> pairKey{ sVertexDep, sVertexArr };

	mGROArcs.erase(pairKey);
}

const unordered_map<string, CVertex*>& CGraphOriented::GROGetVertexMap() const
{
	return mGROVertex;
}

void CGraphOriented::GROInverserArc(const string& sVertexDep, const string& sVertexArr)
{
	if (ExistenceOfVertex(sVertexDep))
	{
		if (ExistenceOfVertex(sVertexArr))
		{
			if (ExistenceOfArcNOriented(sVertexDep, sVertexArr))
			{
				if (sVertexDep != sVertexArr)
				{
					CVertex* vertexDep = GROGetVertexFromKey(sVertexDep);
					CVertex* vertexArr = GROGetVertexFromKey(sVertexArr);

					vertexDep->VERModifyArcOut(sVertexArr, false);
					vertexDep->VERAddInTheMapIn(sVertexArr);

					vertexArr->VERModifyArcIn(sVertexDep, false);
					vertexArr->VERAddInTheMapOut(sVertexDep);

					CArc* arc = GROGetArcFromKeys(sVertexDep, sVertexArr);

					arc->ModifyVertexDep(sVertexArr);
					arc->ModifyVertexArr(sVertexDep);

					pair<string, string> pairOldKey{ sVertexDep, sVertexArr };

					mGROArcs.erase(pairOldKey);

					pair<string, string> pairNewKey{ sVertexArr, sVertexDep };

					mGROArcs[pairNewKey] = arc;

					cout << "arc (" + sVertexDep + ", " + sVertexArr + ") inversed successfully " << endl;
				}

			}
			else
			{
				string sErrorMessage = "an arc with a vertex Dep " + sVertexDep + " an vertex Arr " + sVertexArr + " doesn't exist";
				throw CException(arc_not_existed, sErrorMessage, "CGraphOriented.cpp", 141);

			}
		}
		else
		{
			string sErrorMessage = "a vertex with the value " + sVertexArr + " doesn't exist";
			throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 287);
		}
	}
	else
	{
		string sErrorMessage = "a vertex with the value " + sVertexDep + " doesn't exist";
		throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 285);

	}
}

void CGraphOriented::GROInverserAllArcs()
{
	vector<pair<string, string>> res;
	vector<pair<string, string>> arcsToInvert;

	for (const auto& arcEntry : mGROArcs) {
		arcsToInvert.push_back({ arcEntry.first.first, arcEntry.first.second });
	}

	vector<pair<string, string>>::iterator it = arcsToInvert.begin();
	
	for (;it != arcsToInvert.end(); it++)
	{
		vector<pair<string, string>>::iterator foundDepArr = find(res.begin(), res.end(), make_pair(it->first, it->second));
		vector<pair<string, string>>::iterator foundArrDep = find(res.begin(), res.end(), make_pair(it->second, it->first));

		if (foundDepArr == res.end() && foundArrDep == res.end())
		{
			GROInverserArc(it->first, it->second);
			res.push_back(make_pair(it->first, it->second));
		}
	}

	cout << "all arcs have been inversed successfully " << endl;
}

void CGraphOriented::ModifyArc(const string& sVertexDep, const string& sVertexArr, CArc*& arc)
{
	pair<string, string> pairKey{ sVertexDep, sVertexArr };
	mGROArcs[pairKey] = arc;
}

void CGraphOriented::ModifyVertex(const string& sVertexOldValue, const string& sVertexNewValue, CVertex*& vertex)
{
	EraseVertexKey(sVertexOldValue);
	mGROVertex[sVertexNewValue] = vertex;
}

void CGraphOriented::EraseVertexKey(const string& key)
{
	mGROVertex.erase(key);
}


