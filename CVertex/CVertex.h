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

	string sVERName;
	unordered_map<string, bool> sVERArcIn;
	unordered_map<string, bool> sVERArcOut;
public:

	//Constructors 

	CVertex();


	CVertex(string value);

	//METHODS
	/**
	*******************************************************************************
	* VERModify
	* *****************************************************************************
	* Entries : string svalue
	* Needs : None
	* Returns : void
	* Leads : modify sVERName by svalue
	********************************************************************************
	*/
	void VERModifyName(const string& svalue);

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
	* VERModifyArcIn
	* *****************************************************************************
	* Entries : the string key to change, and the string new value to put at the key's "value"
	* Needs : None
	* Returns : void
	* Leads : change the value of the map sVERArcIn at the key to the new Value given into the parameter
	*******************************************************************************
	*/
	void VERModifyArcIn(const string& key, bool value);


	/**
	*******************************************************************************
	* VERModifyArcOut
	* *****************************************************************************
	* Entries : the string key to change, and the string new value to put at the key's "value"
	* Needs : None
	* Returns : void
	* Leads : change the value of the map sVERArcOut at the key to the new Value given into the parameter
	*******************************************************************************
	*/
	void VERModifyArcOut(const string& key, bool value);

	/**
	*******************************************************************************
	* VERAddInTheMapIn
	* *****************************************************************************
	* Entries : the value of the key to add in the sVERArcIn
	* Needs : None
	* Returns : None
	* Leads : a new value with another key equals to s will be added to the map sVERArcIn
	*******************************************************************************
	*/
	void VERAddInTheMapIn(const string& s);

	/**
	*******************************************************************************
	* VERAddInTheMapOut
	* *****************************************************************************
	* Entries : the value of the key to add in the sVERArcOut
	* Needs : None
	* Returns : None
	* Leads : a new value with another key equals to s will be added to the map sVERArcOut
	*******************************************************************************
	*/
	void VERAddInTheMapOut(const string& s);


	/**
	*******************************************************************************
	* printAdjacentNeightboors
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : const string 
	* Leads :   print None if the vertex got no ajdacents neighboors, unless it returns a string
		that will contain all the adjacents vertecies's values of the vertex
	*******************************************************************************
	*/
	const string printAdjacentNeightboors();

	/**
	*******************************************************************************
	* removeArcFromArcIn
	* *****************************************************************************
	* Entries : s : string represents the value of the arc in IN direction we want to remove
		from the vertex sVERArcIn's unordered_map
	* Needs : None
	* Returns : void
	* Leads : the IN arc of the vertex which vertex arr's value is s will 
		be remove from the sVERArcIn's unordered_map
	*******************************************************************************
	*/
	void removeArcFromArcIn(const string& s);


	/**
	*******************************************************************************
	* removeArcFromArcOut
	* *****************************************************************************
	* Entries : s :  string represents the value of the arc in OUT direction we want to remove
		from the vertex sVERArcOut's unordered_map
	* Needs : None
	* Returns : void
	* Leads : the OUT arc of the vertex which vertex arr's value is s will 
		be remove from the sVERArcOut's unordered_map
	*******************************************************************************
	*/
	void removeArcFromArcOut(const string& s);

	/**
	*******************************************************************************
	* getAllAdjacencesVerteciesValues
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : const set<string>
	* Leads : the set returned will be empty if the vertex has no adjacents vertecies unless it returns
		a set that contains all the values of those adjacents vertecies
	*******************************************************************************
	*/
	const set<string> getAllAdjacencesVerteciesValues();

	/**
	*******************************************************************************
	* changeKeysVerArcIn
	* *****************************************************************************
	* Entries : oldVal : string represents the old value on the arr value of the arc in 
		the IN direction that we need to change
	*	newVal : string represents the new value to set on the arr value of the arc's IN 
	* Needs : None
	* Returns : void
	* Leads : the arr value of the arc which was oldVal will be change to newVal
	*******************************************************************************
	*/
	void changeKeysVerArcIn(const string& oldVal, const string& newVal);

	/**
	*******************************************************************************
	* changeKeysVerArcOut
	* *****************************************************************************
	* Entries : oldVal : string represents the old value on the dep value of the arc in 
		the OUT direction that we need to change
	*	newVal : string represents the new value to set on the dep value of the arc's OUT 
	* Needs : None
	* Returns : void
	* Leads : the dep value of the arc which was oldVal will be change to newVal
	*******************************************************************************
	*/
	void changeKeysVerArcOut(const string& oldVal, const string& newVal);

	/**
	*******************************************************************************
	* getAllListOutVertecies
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : const string
	* Leads :returns a string thatcontains all vertecies which we can reach from the vertex in the OUT direction
	*******************************************************************************
	*/
	const string getAllListOutVertecies();

};
#endif
