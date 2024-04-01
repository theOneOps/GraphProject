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
	* Entries : tree : BSTree* = the tree we want to compare with
	* Needs : None
	* Returns : void
	* Leads :
	*******************************************************************************
	*/
	const string printAdjacentNeightboors();

	/**
	*******************************************************************************
	* removeArcFromArcIn
	* *****************************************************************************
	* Entries : tree : BSTree* = the tree we want to compare with
	* Needs : None
	* Returns : void
	* Leads : Return description
	*******************************************************************************
	*/
	void removeArcFromArcIn(const string& s);


	/**
	*******************************************************************************
	* removeArcFromArcOut
	* *****************************************************************************
	* Entries : tree : BSTree* = the tree we want to compare with
	* Needs : None
	* Returns : void
	* Leads : Return description
	*******************************************************************************
	*/
	void removeArcFromArcOut(const string& s);

	/**
	*******************************************************************************
	* getAllAdjacenceVertexToAVertex
	* *****************************************************************************
	* Entries : tree : BSTree* = the tree we want to compare with
	* Needs : None
	* Returns : void
	* Leads : Return description
	*******************************************************************************
	*/
	const set<string> getAllAdjacenceVertexToAVertex();

	/**
	*******************************************************************************
	* changeKeysVerArcIn
	* *****************************************************************************
	* Entries : tree : BSTree* = the tree we want to compare with
	* Needs : None
	* Returns : void
	* Leads : Return description
	*******************************************************************************
	*/
	void changeKeysVerArcIn(const string& oldVal, const string& newVal);

	/**
	*******************************************************************************
	* changeKeysVerArcOut
	* *****************************************************************************
	* Entries : tree : BSTree* = the tree we want to compare with
	* Needs : None
	* Returns : void
	* Leads : Return description
	*******************************************************************************
	*/
	void changeKeysVerArcOut(const string& oldVal, const string& newVal);

	/**
	*******************************************************************************
	* getAllListInVertecies
	* *****************************************************************************
	* Entries : tree : BSTree* = the tree we want to compare with
	* Needs : None
	* Returns : void
	* Leads : Return description
	*******************************************************************************
	*/
	const string getAllListInVertecies();

};
#endif
