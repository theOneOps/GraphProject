#ifndef _CGRAPH_ORIENTE_H
#define _CGRAPH_ORIENTE_H
#include <string>
#include "../CArc/Arc.h"
#include "../CVertex/CVertex.h"
#include "../CException/CException.h"

using namespace std;

#define vertex_already_existed 11
#define arc_already_existed 10
#define vertex_not_existed 9
#define arc_not_existed 8


/**********************************************************
*  Class : CGrapheOriente
* *********************************************************
* ROLE : management of the oriented graph
* *********************************************************
* VERSION: 1.0
* AUTHOR: Selly Bill-Gate MEDEWOU
*                 Jeremie YANG
* DATE: 19/03/2024
* *********************************************************
*/
class CGraphOriented
{
private:

    //Attributs

    unordered_map<string, CVertex*> mGROVertex;

    struct hash_pair {
        size_t operator()(const pair<string, string>& p) const {
            size_t hash1 = hash<string>{}(p.first);
            size_t hash2 = hash<string>{}(p.second);
            return hash1 ^ hash2;
        }
    };

    unordered_map<pair<string, string>, CArc*, hash_pair> mGROArcs;

public:

    //Constructors

    CGraphOriented();
    ~CGraphOriented();
    /**
    *******************************************************************************
    * GROAddVertex
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    void GROAddVertex(const string& key);

    /**
    *******************************************************************************
    * GRORemoveVertex
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    virtual void GRORemoveVertex(const string& key);

    /**
    *******************************************************************************
    * GROAddArc
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    virtual void GROAddArc(const string& sVertexDep, const string& sVertexArr);

    /**
    *******************************************************************************
    * GRORemoveArc
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    virtual void GRORemoveArc(const string& sVertexDep, const string& sVertexArr);

    /**
    *******************************************************************************
    * GROModifyVertex
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    virtual void GROModifyVertex(const string& sVertexOldValue, const string& sVertexNewValue);

    /**
    *******************************************************************************
    * GROInverserArc
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    virtual void GROInverserArc(const string& sVertexDep, const string& sVertexArr);

    /**
    *******************************************************************************
    * GROInverserAllArcs
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    virtual void GROInverserAllArcs();

    /**
    *******************************************************************************
    * GROGetVertexMap
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    const unordered_map<string, CVertex*>& GROGetVertexMap() const;


    /**
    *******************************************************************************
    * GROPrintAllVertecies
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    void GROPrintAllVertecies();

    /**
    *******************************************************************************
    * PrintAllArcs
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    void PrintAllArcs();

    /**
    *******************************************************************************
    * GROPrintGraph
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    virtual void GROPrintGraph();


protected:

    /**
    *******************************************************************************
    * ExistenceOfVertex
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    bool ExistenceOfVertex(const string& key);

    /**
    *******************************************************************************
    * ExistenceOfArcNOriented
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    bool ExistenceOfArcNOriented(const string& sVertexDep, const string& sVertexArr);

    /**
    *******************************************************************************
    * addKeyVertexInMap
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    void addKeyVertexInMap(const string& key);

    /**
    *******************************************************************************
    * GROGetMVertex
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    unordered_map<string, CVertex*>& GROGetMVertex();


    /**
   *******************************************************************************
   * GROGetMArcs
   * *****************************************************************************
   * Entries : tree : BSTree* = the tree we want to compare with
   * Needs : None
   * Returns : void
   * Leads : Return description
   *******************************************************************************
   */
    unordered_map<pair<string, string>, CArc*, hash_pair>& GROGetMArcs();

    /**
    *******************************************************************************
    * addPairKeysMArcs
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    void addPairKeysMArcs(const string& sVertexDep, const string& sVertexArr);

    /**
    *******************************************************************************
    * getVertexFromKey
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    CVertex* GROGetVertexFromKey(const string& key);

    /**
    *******************************************************************************
    * GROGetArcFromKeys
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    CArc* GROGetArcFromKeys(const string& sVertexDep, const string& sVertexArr);

    /**
    *******************************************************************************
    * GRORemoveArcFromMap
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    void GRORemoveArcFromMap(const string& sVertexDep, const string& sVertexArr);

    /**
    *******************************************************************************
    * ModifyArc
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    void ModifyArc(const string& sVertexDep, const string& sVertexArr, CArc*& arc);


    /**
    *******************************************************************************
    * ModifyVertex
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    void ModifyVertex(const string& sVertexOldValue, const string& sVertexNewValue, CVertex*& vertex);

    /**
    *******************************************************************************
    * EraseVertexKey
    * *****************************************************************************
    * Entries : tree : BSTree* = the tree we want to compare with
    * Needs : None
    * Returns : void
    * Leads : Return description
    *******************************************************************************
    */
    void EraseVertexKey(const string& key);


};
#endif 