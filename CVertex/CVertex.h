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
	void VERModify(string svalue);


	// put the accessors of the attributs...
};
#endif
