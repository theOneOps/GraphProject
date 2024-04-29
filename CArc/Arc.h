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
* EXTERNES INCLUSIONS
*
*/
class CArc
{
private:
	//ATTRIBUTS
	// the departure's value of the arc
	string sARCDep;
	// the arrival's value of the arc
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
	CArc()=default;

	/**
	*******************************************************************************
	* CArc
	* *****************************************************************************
	* Entries : string sDep : the departure's value of the arc,
	*  string sArr : the arrival's value of the arc
	* Needs : None
	* Returns : None
	* Leads : Create an CArc with sARCdep equals to sDep and sARCarr equals to sArr of the arc
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
	* Leads : Get the departure's value of the arc
	 *******************************************************************************
	*/
	const string ARCGetVertexDep() const;

	/**
	*******************************************************************************
	* ARCGetVertexArr
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : string
	* Leads :  Get the arrival's value of the arc
	 *******************************************************************************
	*/
	const string ARCGetVertexArr() const;

	/**
	*******************************************************************************
	* ARCGROModifyVertexDep
	* *****************************************************************************
	* Entries : string snewValue
	* Needs : None
	* Returns : void
	* Leads : change the Dep value of the arc with the snewValue
	 *******************************************************************************
	*/
	void ARCGROModifyVertexDep(const string& sNewValue);

	/**
	*******************************************************************************
	* ARCGROModifyVertexArr
	* *****************************************************************************
	* Entries : string sNewValue
	* Needs : None
	* Returns : void
	* Leads : change the Arr value of the arc with the snewValue
	 *******************************************************************************
	*/
	void ARCGROModifyVertexArr(const string& sNewValue);
};

#endif;