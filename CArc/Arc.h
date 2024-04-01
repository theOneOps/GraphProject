#ifndef _ARC_H
#define _ARC_H


#include <iostream>
#include <string>
using namespace std;

/**********************************************************
*  Class : CARC
* *********************************************************
* ROLE : management of ARC
* *********************************************************
* VERSION: 1.0
* AUTHOR: Selly Bill-Gate MEDEWOU
		  Jeremie YANG
* DATE: 19/03/2024
* *********************************************************
* EXTERNES InCLUSIONS
*
*/
class CArc
{
private:
	//ATTRIBUTS
	string sARCDep;
	string sARCArr;
public:
	// CONSTRUCTORS

	/**
	*******************************************************************************
	* CArc
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : None
	* Leads : Create an arc by default (done by the compiler)
	 *******************************************************************************
	*/
	CArc();

	/**
	*******************************************************************************
	* CArc
	* *****************************************************************************
	* Entries : string sDep : the value of the arc's departure,
	*  string sArr : the value of the arc's arrival
	* Needs : None
	* Returns : None
	* Leads : Create an CArc with sARCdep equals to sDep and sARCarr equals to sArr
	 *******************************************************************************
	*/
	CArc(string sDep, string sArr);

	/**
	*******************************************************************************
	* ARCGetVertexDep
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : string
	* Leads : Get the departure's value of the vertex
	 *******************************************************************************
	*/
	string ARCGetVertexDep() const;

	/**
	*******************************************************************************
	* ARCGetVertexArr
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : string
	* Leads :  Get the arrival's value of the vertex
	 *******************************************************************************
	*/
	string ARCGetVertexArr() const;

	/**
	*******************************************************************************
	* ModifyVertexDep
	* *****************************************************************************
	* Entries : string snewValue
	* Needs : None
	* Returns : void
	* Leads : change the Dep value of the vertex
	 *******************************************************************************
	*/
	void ModifyVertexDep(const string& sNewValue);

	/**
	*******************************************************************************
	* ModifyVertexArr
	* *****************************************************************************
	* Entries : string sNewValue
	* Needs : None
	* Returns : void
	* Leads : change the Arr value of the vertex
	 *******************************************************************************
	*/
	void ModifyVertexArr(const string& sNewValue);
};

#endif;