#ifndef ARC_PONDERE_H
#define ARC_PONDERE_H


#include "Arc.h"


/**********************************************************
*  Class : ArcPondere management
* *********************************************************
* ROLE : management of a class ARC with  weight
* *********************************************************
* VERSION: 1.0
* AUTHOR: Selly Bill-Gate MEDEWOU
		  Jeremie YANG
* DATE: 29/04/2024
* *********************************************************
* EXTERNES InCLUSIONS
*/

/*
* TYPES
*
*/

/*
* VARIABLES
*
*/
class CArcPondere : public CArc
{
private:
	// the weight of the arc
	unsigned int uiWeight;
public:

	CArcPondere() = default;

	CArcPondere(const string& sDep, const string& sArr) :CArc(sDep, sArr) { uiWeight = 0; }

	/**
	*******************************************************************************
	* ARCGetWeight
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : void
	* Leads : Return the weight of the arc
	*******************************************************************************
	*/
	const unsigned int ARCGetWeight() const
	{
		return CArcPondere::uiWeight;
	}

	/**
	*******************************************************************************
	* ARCSetWeight
	* *****************************************************************************
	* Entries : None
	* Needs : None
	* Returns : void
	* Leads : Return the weight of the arc
	*******************************************************************************
	*/
	void ARCSetWeight(const unsigned int weight)
	{
		CArcPondere::uiWeight = weight;
	}
};

#endif; // !ARC_PONDERE_H
