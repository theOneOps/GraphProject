#ifndef CVERTEX_H
#define CVERTEX_H
#include<string>
#include <utility>
#include <set>
#include <unordered_map>

using namespace std;

/**********************************************************
*  Class : CVertex
* *********************************************************
* ROLE : management of Vertex
* *********************************************************
* VERSION: 1.0
* AUTHOR: Selly Bill-Gate MEDEWOU
*				  Jeremie YANG
* DATE: 19/03/2024
* *********************************************************
*/
class CVertex
{
private:
	//ATRIBUTS
	// value of the vertex
	string sVERName;
	// map containing the values of Vertices whose arrival's vertex is the current vertex
	unordered_map<string, bool> sVERArcIn;
	//  map containing the values of Vertices whose departure's vertex is the current vertex
	unordered_map<string, bool> sVERArcOut;
public:

	//Constructors 

	CVertex() = default;

	// Constructor taking the value of the vertex
	CVertex(string value);

	//METHODS
	/**
	*******************************************************************************
	* VERModifyName
	* *****************************************************************************
	* Entries : string sValue
	* Needs : None
	* Returns : void
	* Leads : modify the value of the vertex by sValue
	********************************************************************************
	*/
	void VERModifyName(const string& sValue);

	/**
	*******************************************************************************
	* VERGetName
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : string
	* Leads : get the value of the vertex
	*******************************************************************************
	*/
	const string VERGetName() const;

	/**
	*******************************************************************************
	* VERGetArcIn
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : map<string, bool>
	* Leads :  get the sVERArcIn's map of the vertex
	*******************************************************************************
	*/
	const unordered_map<string, bool>& VERGetArcIn() const;

	/**
	*******************************************************************************
	* VERGetArcOut
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : map<string, bool>
	* Leads :  get the sVERArcOut's map of the vertex
	*******************************************************************************
	*/
	const unordered_map<string, bool>& VERGetArcOut() const;


	/**
	*******************************************************************************
	* VERGROModifyArcIn
	* *****************************************************************************
	* Entries : the string sKey to change, and the bool new value to put at the sKey's "value"
	* Needs : None
	* Returns : void
	* Leads : change the value of the map sVERArcIn at the 'key' to the new 'value' bool given into the parameter
	*******************************************************************************
	*/
	void VERGROModifyArcIn(const string& sKey, bool value);


	/**
	*******************************************************************************
	* VERGROModifyArcOut
	* *****************************************************************************
	* Entries : the string sKey to change, and the bool new value to put at the sKey's "bValue"
	* Needs : None
	* Returns : void
	* Leads : change the value of the map sVERArcOut at the sKey to the new 'bValue' given into the parameter
	*******************************************************************************
	*/
	void VERGROModifyArcOut(const string& sKey, bool bValue);

	/**
	*******************************************************************************
	* VERAddInTheMapIn
	* *****************************************************************************
	* Entries : the value of the sKey to add in the sVERArcIn
	* Needs : None
	* Returns : None
	* Leads : a new value with another sKey equals to sKey will be added to the map sVERArcIn
	*******************************************************************************
	*/
	void VERAddInTheMapIn(const string& sKey);

	/**
	*******************************************************************************
	* VERAddInTheMapOut
	* *****************************************************************************
	* Entries : the value of the sKey to add in the sVERArcOut
	* Needs : None
	* Returns : None
	* Leads : a new value with another sKey equals to sKey will be added to the map sVERArcOut
	*******************************************************************************
	*/
	void VERAddInTheMapOut(const string& sKey);


	/**
	*******************************************************************************
	* VERPrintAdjacentNeightboors
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : const string 
	* Leads :   print None if the vertex got no ajdacents neighboors, unless it returns a string
		that will contain all the adjacents Vertices's values of the vertex
	*******************************************************************************
	*/
	const string VERPrintAdjacentNeightboors();

	/**
	*******************************************************************************
	* VERRemoveArcFromArcIn
	* *****************************************************************************
	* Entries : sKey : string represents the value of the arc in IN direction we want to remove
		from the vertex sVERArcIn's unordered_map
	* Needs : None
	* Returns : void
	* Leads : the IN arc of the vertex which vertex arr's value is 'sKey' will 
		be remove from the sVERArcIn's unordered_map
	*******************************************************************************
	*/
	void VERRemoveArcFromArcIn(const string& sKey);


	/**
	*******************************************************************************
	* VERRemoveArcFromArcOut
	* *****************************************************************************
	* Entries : sKey :  string represents the value of the arc in OUT direction we want to remove
		from the vertex sVERArcOut's unordered_map
	* Needs : None
	* Returns : void
	* Leads : the OUT arc of the vertex which vertex arr's value is sKey will 
		be remove from the sVERArcOut's unordered_map
	*******************************************************************************
	*/
	void VERRemoveArcFromArcOut(const string& sKey);

	/**
	*******************************************************************************
	* VERGetAllAdjacencesVerticesValues
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : const set<string>
	* Leads : the set returned will be empty if the vertex has no adjacents Vertices unless it returns
		a set that contains all the values of those adjacents Vertices
	*******************************************************************************
	*/
	const set<string> VERGetAllAdjacencesVerticesValues();

	/**
	*******************************************************************************
	* VERChangeKeysVerArcIn
	* *****************************************************************************
	* Entries : sOldVal : string represents the old value on the arr value of the arc in 
		the IN direction that we need to change
	*	sNewVal : string represents the new value to set on the arr value of the arc's IN 
	* Needs : None
	* Returns : void
	* Leads : the arr value of the arc which was sOldVal will be change to sNewVal
	*******************************************************************************
	*/
	void VERChangeKeysVerArcIn(const string& sOldVal, const string& sNewVal);

	/**
	*******************************************************************************
	* VERChangeKeysVerArcOut
	* *****************************************************************************
	* Entries : sOldVal : string represents the old value on the dep value of the arc in 
		the OUT direction that we need to change
	*	sNewVal : string represents the new value to set on the dep value of the arc's OUT
	* Needs : None
	* Returns : void
	* Leads : the dep value of the arc which was sOldVal will be change to sNewVal
	*******************************************************************************
	*/
	void VERChangeKeysVerArcOut(const string& sOldVal, const string& sNewVal);

	/**
	*******************************************************************************
	* VERGetAllListOutVertices
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : const string
	* Leads :returns a string that contains all Vertices which we can reach from the vertex in the OUT direction
	*******************************************************************************
	*/
	const string VERGetAllListOutVertices();

};
#endif
