#include "CGraphNOriented.h"

CGraphNOriented::CGraphNOriented()
{

}

void CGraphNOriented::GROAddArc(const string& sVertexDep, const string& sVertexArr)
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

					VertexDep->VERAddInTheMapIn(sVertexArr); 
					VertexArr->VERAddInTheMapOut(sVertexDep);

					addPairKeysMArcs(sVertexDep, sVertexArr);
					addPairKeysMArcs(sVertexArr, sVertexDep);

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

void CGraphNOriented::GRORemoveArc(const string& sVertexDep, const string& sVertexArr)
{
	if (sVertexArr == sVertexDep)
	{
		CGraphOriented::GRORemoveArc(sVertexDep, sVertexArr);
	}
	else
	{
		if (ExistenceOfVertex(sVertexDep))
		{
			CVertex* VDep = GROGetVertexFromKey(sVertexDep);
			if (ExistenceOfVertex(sVertexArr))
			{
				CVertex* VArr = GROGetVertexFromKey(sVertexArr);

				if (ExistenceOfArcNOriented(sVertexDep, sVertexArr))
				{
					CArc* arcFst = GROGetArcFromKeys(sVertexDep, sVertexArr);

					CArc* arcScd = GROGetArcFromKeys(sVertexArr, sVertexDep);

					GRORemoveArcFromMap(sVertexDep, sVertexArr);

					GRORemoveArcFromMap(sVertexArr, sVertexDep);

					delete arcFst;
					delete arcScd;

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
	
}

void CGraphNOriented::GROModifyVertex(const string& sVertexOldValue, const string& sVertexNewValue)
{
	if (ExistenceOfVertex(sVertexOldValue))
	{
		if (!ExistenceOfVertex(sVertexNewValue))
		{
			CVertex* VertexOldValue = GROGetVertexFromKey(sVertexOldValue);
			set<string> adjacentVertecies = VertexOldValue->getAllAdjacencesVerteciesValues();

			for (string sAdjVertex : adjacentVertecies)
			{
				CVertex* VAdjVertex = GROGetVertexFromKey(sAdjVertex);

				VAdjVertex->changeKeysVerArcIn(sVertexOldValue, sVertexNewValue);
				VAdjVertex->changeKeysVerArcOut(sVertexOldValue, sVertexNewValue);


				CArc* arcOne = GROGetArcFromKeys(sVertexOldValue, sAdjVertex);
				CArc* arcTwo = GROGetArcFromKeys(sAdjVertex, sVertexOldValue);

				arcOne->ModifyVertexDep(sVertexNewValue);

				arcTwo->ModifyVertexArr(sVertexNewValue);

				GRORemoveArcFromMap(sVertexOldValue, sAdjVertex);

				GRORemoveArcFromMap(sAdjVertex, sVertexOldValue);

				ModifyArc(sVertexNewValue, sAdjVertex, arcOne);

				ModifyArc(sAdjVertex, sVertexNewValue, arcTwo);
			}

			VertexOldValue->VERModifyName(sVertexNewValue);

			ModifyVertex(sVertexOldValue, sVertexNewValue, VertexOldValue);
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

void CGraphNOriented::GRORemoveVertex(const string& key)
{
	if (ExistenceOfVertex(key))
	{
		CVertex* Vertex = GROGetVertexFromKey(key);

		set<string> adjacentVertecies = Vertex->getAllAdjacencesVerteciesValues();

		for (string v : adjacentVertecies)
		{
			GRORemoveArc(key, v);
		}

		delete Vertex;
		EraseVertexKey(key);
	}
	else
	{
		string sErrorMessage = "a vertex with the value " + key + " doesn't exist";
		throw CException(vertex_not_existed, sErrorMessage, "CGraphNOriented.cpp", 161);
	}
}

void CGraphNOriented::GROPrintGraph()
{
	unordered_map<string, CVertex*> VerteciesMap = GROGetVertexMap();
	unordered_map<string, CVertex*>::iterator it = VerteciesMap.begin();

	for (; it != VerteciesMap.end(); it++)
	{
		cout << it->first << " : " << it->second->printAdjacentNeightboors() << endl;
	}
}