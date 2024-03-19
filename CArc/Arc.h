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
*/

class CArc
{
private:
	//ATTRIBUTS
	string sARCdep;
	string sARCarr;
public:
	// CONSTRUCTORS
	/**
	 *******************************************************************************
	 * @todo CArc
	 * *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : string
	* Leads : Create an arc by default (done by the compiler)
	 *******************************************************************************
	*/
	CArc();
	/**
	 *******************************************************************************
	 * @todo ARCGetVertexDep
	 * *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : string
	* Leads : Create an CArc with sARCdep equals to sDep and sARCarr equals to sArr
	 *******************************************************************************
	*/
	CArc(string sDep, string sArr);

	/**
	 *******************************************************************************
	 * @todo ARCGetVertexDep
	 * *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : string
	* Leads : Get the value of the vertex
	 *******************************************************************************
	*/
	string ARCGetVertexDep() const;

	/**
	 *******************************************************************************
	 * @todo ARCGetVertexArr
	 * *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : void
	* Leads : Return 
	 *******************************************************************************
	*/
	string ARCGetVertexArr() const;

	/**
	 *******************************************************************************
	 * @todo ModifyVertexDep
	 * *****************************************************************************
	* Entries : string snewValue
	* Needs : None
	* Returns : void
	* Leads : change the Dep value of the vertex 
	 *******************************************************************************
	*/
	void ModifyVertexDep(string sNewValue);

	/**
	 *******************************************************************************
	 * @todo ModifyVertexArr
	 * *****************************************************************************
	* Entries : string sNewValue
	* Needs : None
	* Returns : void
	* Leads : change the Arr value of the vertex 
	 *******************************************************************************
	*/
	void ModifyVertexArr(string sNewValue);
};

#endif;