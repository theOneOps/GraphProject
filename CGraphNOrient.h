#ifndef CGRAPH_NORIENT_H
#define CGRAPH_NORIENT_H

#include "CGraphOrient.h"


template< typename SommetType,  typename ArcType>
class CGraphNOrient: public CGraphOrient< SommetType,  ArcType>
{
public :
	CGraphNOrient() = default;

	virtual void GROAddArc(const string& sVertexDep, const string& sVertexArr)
	{
		if (CGraphOrient< SommetType,  ArcType>::ExistenceOfVertex(sVertexDep))
		{
			SommetType* VertexDep = CGraphOrient< SommetType,  ArcType>::GROGetVertexFromKey(sVertexDep);
			if (CGraphOrient< SommetType,  ArcType>::ExistenceOfVertex(sVertexArr))
			{
				SommetType* VertexArr = CGraphOrient< SommetType,  ArcType>::GROGetVertexFromKey(sVertexArr);
				if (!CGraphOrient< SommetType,  ArcType>::ExistenceOfArcNOriented(sVertexDep, sVertexArr))
				{
					if (!CGraphOrient< SommetType,  ArcType>::ExistenceOfArcNOriented(sVertexArr, sVertexDep))
					{
						VertexArr->VERAddInTheMapIn(sVertexDep);
						VertexDep->VERAddInTheMapOut(sVertexArr);

						VertexDep->VERAddInTheMapIn(sVertexArr);
						VertexArr->VERAddInTheMapOut(sVertexDep);

						CGraphOrient< SommetType,  ArcType>::addPairKeysMArcs(sVertexDep, sVertexArr);
						CGraphOrient< SommetType,  ArcType>::addPairKeysMArcs(sVertexArr, sVertexDep);

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

	virtual void GRORemoveArc(const string& sVertexDep, const string& sVertexArr)
	{
		if (sVertexArr == sVertexDep)
		{
			CGraphOrient< SommetType,  ArcType>::GRORemoveArc(sVertexDep, sVertexArr);
		}
		else
		{
			if (CGraphOrient< SommetType,  ArcType>::ExistenceOfVertex(sVertexDep))
			{
				SommetType* VDep = CGraphOrient< SommetType,  ArcType>::GROGetVertexFromKey(sVertexDep);
				if (CGraphOrient< SommetType,  ArcType>::ExistenceOfVertex(sVertexArr))
				{
					SommetType* VArr = CGraphOrient< SommetType,  ArcType>::GROGetVertexFromKey(sVertexArr);

					if (CGraphOrient< SommetType,  ArcType>::ExistenceOfArcNOriented(sVertexDep, sVertexArr))
					{
						ArcType* arcFst = CGraphOrient< SommetType,  ArcType>::GROGetArcFromKeys(sVertexDep, sVertexArr);

						ArcType* arcScd = CGraphOrient< SommetType,  ArcType>::GROGetArcFromKeys(sVertexArr, sVertexDep);

						CGraphOrient< SommetType,  ArcType>::GRORemoveArcFromMap(sVertexDep, sVertexArr);

						CGraphOrient< SommetType,  ArcType>::GRORemoveArcFromMap(sVertexArr, sVertexDep);

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

	virtual void GROModifyVertex(const string& sVertexOldValue, const string& sVertexNewValue)
	{
		if (CGraphOrient< SommetType,  ArcType>::ExistenceOfVertex(sVertexOldValue))
		{
			if (!CGraphOrient< SommetType,  ArcType>::ExistenceOfVertex(sVertexNewValue))
			{
				SommetType* VertexOldValue = CGraphOrient< SommetType,  ArcType>::GROGetVertexFromKey(sVertexOldValue);
				set<string> adjacentVertecies = VertexOldValue->getAllAdjacenceVertexToAVertex();

				for (string sAdjVertex : adjacentVertecies)
				{
					SommetType* VAdjVertex = CGraphOrient< SommetType,  ArcType>::GROGetVertexFromKey(sAdjVertex);

					VAdjVertex->changeKeysVerArcIn(sVertexOldValue, sVertexNewValue);
					VAdjVertex->changeKeysVerArcOut(sVertexOldValue, sVertexNewValue);


					ArcType* arcOne = CGraphOrient< SommetType, ArcType>::GROGetArcFromKeys(sVertexOldValue, sAdjVertex);
					ArcType* arcTwo = CGraphOrient< SommetType, ArcType>::GROGetArcFromKeys(sAdjVertex, sVertexOldValue);

					arcOne->ModifyVertexDep(sVertexNewValue);

					arcTwo->ModifyVertexArr(sVertexNewValue);

					CGraphOrient< SommetType,  ArcType>::GRORemoveArcFromMap(sVertexOldValue, sAdjVertex);

					CGraphOrient< SommetType,  ArcType>::GRORemoveArcFromMap(sAdjVertex, sVertexOldValue);

					CGraphOrient< SommetType,  ArcType>::ModifyArc(sVertexNewValue, sAdjVertex, arcOne);

					CGraphOrient< SommetType,  ArcType>::ModifyArc(sAdjVertex, sVertexNewValue, arcTwo);
				}

				VertexOldValue->VERModifyName(sVertexNewValue);

				CGraphOrient< SommetType,  ArcType>::ModifyVertex(sVertexOldValue, sVertexNewValue, VertexOldValue);
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

	virtual void GROInverserArc(const string& sVertexDep, const string& sVertexArr) {};

	virtual void GROInverserAllArcs() {};

	virtual void GRORemoveVertex(const string& key)
	{
		if (CGraphOrient< SommetType,  ArcType>::ExistenceOfVertex(key))
		{
			SommetType* Vertex = CGraphOrient< SommetType,  ArcType>::GROGetVertexFromKey(key);

			set<string> adjacentVertecies = Vertex->getAllAdjacenceVertexToAVertex();

			for (string v : adjacentVertecies)
			{
				CGraphOrient< SommetType,  ArcType>::GRORemoveArc(key, v);
			}

			delete Vertex;
			CGraphOrient< SommetType,  ArcType>::EraseVertexKey(key);
		}
		else
		{
			string sErrorMessage = "a vertex with the value " + key + " doesn't exist";
			throw CException(vertex_not_existed, sErrorMessage, "CGraphNOriented.cpp", 161);
		}
	}

	virtual void GROPrintGraph()
	{
		unordered_map<string, SommetType*> VerteciesMap = CGraphOrient< SommetType,  ArcType>::GROGetVertexMap();
		typename unordered_map<string, SommetType*>::iterator it = VerteciesMap.begin();

		for (; it != VerteciesMap.end(); it++)
		{
			cout << it->first << " : " << it->second->printAdjacentNeightboors() << endl;
		}
	}
};
#endif // CGRAPH_NORIENT_H
