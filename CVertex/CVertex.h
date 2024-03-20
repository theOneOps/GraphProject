#ifndef CVERTEX_H
#define CVERTEX_H
#include<string>
#include <map>
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
	map<string, bool> sVERArcIn;
	map<string, bool> sVERArcOut;
public:

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
	string VERGetName() const;

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
	map<string, bool> VERGetArcIn() const;

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
	map<string, bool> VERGetArcOut() const;


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

<<<<<<< HEAD
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

=======
>>>>>>> 87a65594fccc6cfc4813e980539e19a2e155f283
};
#endif
