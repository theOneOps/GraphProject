#ifndef CGRAPH_NORIENT_H
#define CGRAPH_NORIENT_H

#include "CGraphOrient.h"

/**********************************************************
*  Class : CGrapheNOrient
* *********************************************************
* ROLE : management of the Non Oriented graph
* *********************************************************
* VERSION: 1.0
* AUTHOR: Selly Bill-Gate MEDEWOU
*                 Jeremie YANG
* DATE: 19/03/2024
* *********************************************************
*
* Variables
*
* vertex_already_existed 11
* arc_already_existed 10
* vertex_not_existed 9
* arc_not_existed 8
*
*/
template< typename SommetType,  typename ArcType>
class CGraphNOrient: public CGraphOrient< SommetType,  ArcType>
{
public :

	CGraphNOrient() = default;


	/**
	*******************************************************************************
	* GROAddArc
	* *****************************************************************************
	* Entries : sVertexDep: string represented the start value of the arc,
	* sVertexArr: string represented the end value of the arc
	* Needs : None
	* Returns : void
	* Leads : throw an exception if :
	* if one of the vertex is not in the graph, it throw an exception
	* if there is already an arc between those vertecies
	*
	* Unless it add a arc between those vertecies
	*******************************************************************************
	*/
	virtual void GROAddArc(const string& sVertexDep, const string& sVertexArr)
	{
		// to add an arc between from a start value  "sVertexDep" to and end value "sVertexDArr",
		// we should first check if the involved vertecies of values 
		// "sVertexDep and sVertexArr" really existed

		// check the existence of the start vertex

		if (CGraphOrient< SommetType,  ArcType>::GROExistenceOfVertex(sVertexDep))
		{
			SommetType* VertexDep = CGraphOrient< SommetType,  ArcType>::GROGetVertexFromKey(sVertexDep);
			// then we check if there is already an arc between those vertecies or not 
				
			// check the existence of the end vertex
			if (CGraphOrient< SommetType,  ArcType>::GROExistenceOfVertex(sVertexArr))
			{

				SommetType* VertexArr = CGraphOrient< SommetType,  ArcType>::GROGetVertexFromKey(sVertexArr);

				// check the existence of an arc IN
				if (!CGraphOrient< SommetType,  ArcType>::GROExistenceOfArcNOriented(sVertexDep, sVertexArr))
				{
					// check the existence of an arc OUT
					if (!CGraphOrient< SommetType,  ArcType>::GROExistenceOfArcNOriented(sVertexArr, sVertexDep))
					{
						
						if (sVertexDep == sVertexArr)
						{
							CGraphOrient< SommetType, ArcType>::GROAddArc(sVertexDep, sVertexArr);
						}
						else
						{
							VertexArr->VERAddInTheMapIn(sVertexDep);
							VertexDep->VERAddInTheMapOut(sVertexArr);

							VertexDep->VERAddInTheMapIn(sVertexArr);
							VertexArr->VERAddInTheMapOut(sVertexDep);

							// we create an arc with the correponding start value and end value of the arc
							// and then we add the arc created to the unorderd_map mGROArcs

							CGraphOrient< SommetType, ArcType>::GROAddPairKeysMArcs(sVertexDep, sVertexArr);

							// we create an arc with the correponding end value and start value of the arc
							// and then we add the arc created to the unorderd_map mGROArcs
							CGraphOrient< SommetType, ArcType>::GROAddPairKeysMArcs(sVertexArr, sVertexDep);

							string res = "arc (" + sVertexDep + " " + sVertexArr + ") created successfully";
							//cout << res << endl;
						}
					}
					else
					{
						// if there is already an arc OUT the in way, we throw an exception
						string sErrorMessage = "an arc with a vertexDep " + sVertexDep + " and vertexArr " + sVertexArr + " is already in the graph";
						throw CException(arc_already_existed, sErrorMessage, "CGraphOriented.cpp", 68);
					}
				}
				else
				{
					// if there is already an arc IN the in way, we throw an exception
					string sErrorMessage = "an arc with a vertexDep " + sVertexDep + " and vertexArr " + sVertexArr + " is already in the graph";
					throw CException(arc_already_existed, sErrorMessage, "CGraphOriented.cpp", 66);

				}
			}
			else
			{
				// if the end vertex doesn't exist, we throw an exception
				string sErrorMessage = "a vertex with the value " + sVertexArr + " doesn't exist";
				throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 70);

			}
		}
		else
		{
			// if the start vertex doesn't exist, we throw an exception
			string sErrorMessage = "a vertex with the value " + sVertexDep + " doesn't exist";
			throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 68);
		}
	}

	/**
	*******************************************************************************
	* GRORemoveArc
	* *****************************************************************************
	* Entries :  sVertexDep: string represented the start value of the arc,
	* sVertexArr: string represented the end value of the arc
	* Needs : None
	* Returns : void
	* Leads : throw an exception if :
	* if one of the vertex is not in the graph, it throw an exception
	* if there is no arc between those vertecies
	*
	* Unless it removes the arc between those vertecies
	*******************************************************************************
	*/
	virtual void GRORemoveArc(const string& sVertexDep, const string& sVertexArr)
	{
		// if the arc's vertecies have equal values, then by calling the GROREmoveArc of the CGraphOrient, 
		// we can delete easily the arc

		if (sVertexArr == sVertexDep)
		{
			CGraphOrient< SommetType,  ArcType>::GRORemoveArc(sVertexDep, sVertexArr);
		}
		else
		{
			// to remove an arc between from a start value  "sVertexDep" to and end value "sVertexDArr",
			// we should first check if the involved vertecies of values 
			// "sVertexDep and sVertexArr" really existed
			if (CGraphOrient< SommetType,  ArcType>::GROExistenceOfVertex(sVertexDep))
			{
				SommetType* VDep = CGraphOrient< SommetType,  ArcType>::GROGetVertexFromKey(sVertexDep);
				if (CGraphOrient< SommetType,  ArcType>::GROExistenceOfVertex(sVertexArr))
				{
					SommetType* VArr = CGraphOrient< SommetType,  ArcType>::GROGetVertexFromKey(sVertexArr);

					// then we check there is really an arc between those vertecies
					if (CGraphOrient< SommetType,  ArcType>::GROExistenceOfArcNOriented(sVertexDep, sVertexArr))
					{
						// if yes, we get the access the arc we want to remove in the IN direction
						ArcType* arcFst = CGraphOrient< SommetType,  ArcType>::GROGetArcFromKeys(sVertexDep, sVertexArr);

						// if yes, we get the access the arc we want to remove in the OUT direction

						ArcType* arcScd = CGraphOrient< SommetType,  ArcType>::GROGetArcFromKeys(sVertexArr, sVertexDep);

						// then we erase the arc in the IN direction from the mGROArcs (that contains all arcs of the graph)

						CGraphOrient< SommetType,  ArcType>::GRORemoveArcFromMap(sVertexDep, sVertexArr);

						// then we erase the arc in the OUT direction from the mGROArcs (that contains all arcs of the graph)

						CGraphOrient< SommetType,  ArcType>::GRORemoveArcFromMap(sVertexArr, sVertexDep);

						// then we deallocate the memory for the arc  in the IN direction
						delete arcFst;
						// then we deallocate the memory for the arc  in the OUT direction
						delete arcScd;

						// finally, we remove the arc from the start vertex and the end vertex involved in the arc's creation
						VDep->VERRemoveArcFromArcIn(sVertexArr);
						VDep->VERRemoveArcFromArcOut(sVertexArr);

						// finally, we remove the arc from the end vertex and the start vertex involved in the arc's creation
						VArr->VERRemoveArcFromArcIn(sVertexDep);
						VArr->VERRemoveArcFromArcOut(sVertexDep);

						string res = "arc (" + sVertexDep + " " + sVertexArr + ") removed successfully";

						cout << res << endl;
					}
					else
					{
						// if there is no arc between those vertecies, we throw an exception
						string sErrorMessage = "an arc with a vertexDep " + sVertexDep + " and vertexArr " + sVertexArr + " is not in the graph";
						throw CException(arc_already_existed, sErrorMessage, "CGraphOriented.cpp", 178);
					}
				}
				else
				{
					// if the end vertex doesn't exist in the graph, we remove the graph
					string sErrorMessage = "a vertex with the value " + sVertexArr + " doesn't exist";
					throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 117);
				}
			}
			else
			{
				// if the start vertex doesn't exist in the graph, we remove the graph
				string sErrorMessage = "a vertex with the value " + sVertexDep + " doesn't exist";
				throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 115);

			}
		}
	}

	/**
	*******************************************************************************
	* GROModifyVertex
	* *****************************************************************************
	* Entries : sVertexOldValue : string  represented the old value of the vertex,
	*           sVertexNewValue : string represented the new value to replace that old Value of the vertex
	* Needs : None
	* Returns : void
	* Leads : throw an exception:
	* if a vertex of value equals to oldValue doesn't exsit in the graph
	* if the new value to put in replace on the oldValue already exist
	*
	* Unless change the vertex by assigining newValue to his old value, and apply the change to the entire graph
	*******************************************************************************
	*/
	virtual void GROModifyVertex(const string& sVertexOldValue, const string& sVertexNewValue)
	{
		// to modify the involved vertex, we shoould first test if it exists
		if (CGraphOrient< SommetType,  ArcType>::GROExistenceOfVertex(sVertexOldValue))
		{
			// then we should check if a vertex with a new value, is in the graph or not
			if (!CGraphOrient< SommetType,  ArcType>::GROExistenceOfVertex(sVertexNewValue))
			{
				// if not then we first get the vertex we want to modify the value of
				SommetType* VertexOldValue = CGraphOrient< SommetType,  ArcType>::GROGetVertexFromKey(sVertexOldValue);
				// then we get the adjacents vertecies that are linked to our vertex
				set<string> adjacentVertecies = VertexOldValue->VERGetAllAdjacencesVerteciesValues();

				// next with a for loop, we go through all arcs that linked our vertex to each of its adjacents vertex 
				for (string sAdjVertex : adjacentVertecies)
				{
					// if the current arc is in IN direction 
					// we just change the value at start of the arc ith the new value of the arc
					SommetType* VAdjVertex = CGraphOrient< SommetType,  ArcType>::GROGetVertexFromKey(sAdjVertex);

					// we modify the map that represents the IN value of this adjacent current vertex 
					// by putting the correct value of the vertex "sVertexNewValue"
					VAdjVertex->VERChangeKeysVerArcIn(sVertexOldValue, sVertexNewValue);
					VAdjVertex->VERChangeKeysVerArcOut(sVertexOldValue, sVertexNewValue);


					ArcType* arcOne = CGraphOrient< SommetType, ArcType>::GROGetArcFromKeys(sVertexOldValue, sAdjVertex);
					ArcType* arcTwo = CGraphOrient< SommetType, ArcType>::GROGetArcFromKeys(sAdjVertex, sVertexOldValue);

					// we change the value at start of the arc with the new value of the vertex

					arcOne->ARCGROModifyVertexDep(sVertexNewValue);

					// we change the value at end of the arc with the new value of the vertex

					arcTwo->ARCGROModifyVertexArr(sVertexNewValue);

					// then we put the arc into the correct key constituted of the right start value 
					// "sVertexNewValue" and the right end value "sAdjVertex" (value of the current adjacent vertex)
					// finally we erase the old record of the arc from the unordored_map, mGROArcs

					if (sAdjVertex ==  sVertexOldValue)
					{

						CGraphOrient< SommetType, ArcType>::GRORemoveArcFromMap(sAdjVertex, sVertexOldValue);

						//cout << arcOne->ARCGetVertexDep() << " | " << arcOne->ARCGetVertexArr() << endl;

						CGraphOrient<SommetType, ArcType>::GROModifyArc(sVertexNewValue, sVertexNewValue, arcTwo);
					}
					else
					{
						CGraphOrient< SommetType, ArcType>::GRORemoveArcFromMap(sVertexOldValue, sAdjVertex);

						CGraphOrient< SommetType, ArcType>::GRORemoveArcFromMap(sAdjVertex, sVertexOldValue);

						CGraphOrient< SommetType, ArcType>::GROModifyArc(sVertexNewValue, sAdjVertex, arcOne);

						CGraphOrient< SommetType, ArcType>::GROModifyArc(sAdjVertex, sVertexNewValue, arcTwo);
					}

				}

				VertexOldValue->VERModifyName(sVertexNewValue);

				CGraphOrient< SommetType,  ArcType>::GROModifyVertex(sVertexOldValue, sVertexNewValue, VertexOldValue);
			}
			else
			{
				// if the new value is already in use by another vertex, we throw an exception
				string sErrorMessage = "a vertex with the value " + sVertexNewValue + " already exists in the graph";
				throw CException(vertex_already_existed, sErrorMessage, "CGraphOriented.cpp", 161);
			}
		}
		else
		{
			// if there is no vertex with the old value we want to change, we throw an exception
			string sErrorMessage = "a vertex with the value " + sVertexOldValue + " doesn't exist";
			throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 159);
		}
	}

	/**
	*******************************************************************************
	* GROInverserArc
	* *****************************************************************************
	* Entries : sVertexOldValue : string  represented the old value of the vertex,
	*           sVertexNewValue : string represented the new value to replace that old Value of the vertex
	*
	* Needs : None
	* Returns : void
	* Leads : This function does anything, because inversing an arc of a non oriented 
	* graph changes anything for the graph
	*******************************************************************************
	*/
	virtual void GROInverserArc(const string& sVertexDep, const string& sVertexArr) {};

	/**
   *******************************************************************************
   * GROInverserAllArcs
   * *****************************************************************************
   * Entries : None
   * Needs : the arcs to invert should exist as well as the vertecies that link the arc
   * Returns : void
   * Leads :  This function does anything, because inversing an arc of a non oriented 
	* graph changes anything for the graph
   *******************************************************************************
   */
	virtual void GROInverserAllArcs() {};

	/**
	*******************************************************************************
	* GRORemoveVertex
	* *****************************************************************************
	* Entries : string key: value of the vertex to remove from the graph
	* Needs : None
	* Returns : void
	* Leads : Remove a vertex into the Graph if the vertex is in
		the graph, but first, it removes all arcs that are related to the vertex,
		before unless throw an exception
	*******************************************************************************
	*/
	virtual void GRORemoveVertex(const string& key)
	{
		// to remove a vertex, we need to check if the vertex to remove ireally existed in the graph
		if (CGraphOrient< SommetType,  ArcType>::GROExistenceOfVertex(key))
		{
			// if that's so, we get the vertex by accessing it by its value from the unordered_map
		   // mGROArcs( that contains all the vertecies of the graph )
			SommetType* Vertex = CGraphOrient< SommetType,  ArcType>::GROGetVertexFromKey(key);

			// then we get all, the value of the veeertecies adjacents to the vertex we want to remove
			set<string> adjacentVertecies = Vertex->VERGetAllAdjacencesVerteciesValues();

			// then, by a loop we remove all the arcs that linked our vertex with its adjacents vertecies
			for (string v : adjacentVertecies)
			{
				CGraphNOrient< SommetType, ArcType>::GRORemoveArc(key, v);
			}

			// afterwards, we deallocate memory for the vertex
			delete Vertex;
			// and finally, we remove the record that represents the vertex from the unordered_map
			// mGROArcs
			CGraphOrient< SommetType,  ArcType>::GROEraseVertexKey(key);
		}
		else
		{
			string sErrorMessage = "a vertex with the value " + key + " doesn't exist";
			throw CException(vertex_not_existed, sErrorMessage, "CGraphNOriented.cpp", 161);
		}
	}
};
#endif // CGRAPH_NORIENT_H
