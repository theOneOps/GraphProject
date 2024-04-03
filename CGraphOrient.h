#ifndef CGRAPH_ORIENT_H
#define CGRAPH_ORIENT_H

#include "CArc/Arc.h"
#include "CVertex/CVertex.h"
#include <unordered_map>
#include <string>
#include <utility>
#include <set>
#include "CException/CException.h"

using namespace std;

#define vertex_already_existed 11
#define arc_already_existed 10
#define vertex_not_existed 9
#define arc_not_existed 8

template<typename SommetType, typename ArcType>
class CGraphOrient
{
private:
    static_assert(is_base_of<CVertex, SommetType>::value, "SommetType needs to be a CVeertex class or a derivate of CVertex's class");
    static_assert(is_base_of<CArc, ArcType>::value, "ArcType needs to be a Carc class or a derivate of CArc's class");

    //Attributs

    unordered_map<string, SommetType*> mGROVertex;

    struct hash_pair {
        size_t operator()(const pair<string, string>& p) const {
            size_t hash1 = hash<string>{}(p.first);
            size_t hash2 = hash<string>{}(p.second);
            return hash1 ^ hash2;
        }
    };

    unordered_map<pair<string, string>, ArcType*, hash_pair> mGROArcs;

public:

    //Constructors

    //CGraphOrient();
    ~CGraphOrient()
    {
        for (pair<string, SommetType*> pair : mGROVertex)
        {
            delete pair.second;
        }

        for (pair<pair<string, string>, ArcType*> pair : mGROArcs)
        {
            delete pair.second;
        }
    }
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
    void GROAddVertex(const string& key)
    {
        if (!ExistenceOfVertex(key))
        {
            addKeyVertexInMap(key);
            cout << "vertex added successfully" << endl;
        }
        else
        {
            string sErrorMessage = "a vertex with the value " + key + " already exists";
            throw CException(vertex_already_existed, sErrorMessage, "CGraphOriented.cpp", 87);
        }
    }

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
    virtual void GRORemoveVertex(const string& key)
    {
        if (ExistenceOfVertex(key))
        {
            SommetType* Vertex = GROGetVertexFromKey(key);

            set<string> adjacentVertecies = Vertex->getAllAdjacenceVertexToAVertex();

            for (string v : adjacentVertecies)
            {
                try
                {
                    GRORemoveArc(key, v);
                }
                catch (CException e)
                {
                    GRORemoveArc(v, key);
                }
            }

            delete Vertex;
            mGROVertex.erase(key);

        }
        else
        {
            string sErrorMessage = "a vertex with the value " + key + " doesn't exist";
            throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 48);
        }
    }

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
    virtual void GROAddArc(const string& sVertexDep, const string& sVertexArr)
    {
        if (ExistenceOfVertex(sVertexDep))
        {
            SommetType* VertexDep = GROGetVertexFromKey(sVertexDep);
            if (ExistenceOfVertex(sVertexArr))
            {
                SommetType* VertexArr = GROGetVertexFromKey(sVertexArr);
                if (!ExistenceOfArcNOriented(sVertexDep, sVertexArr))
                {
                    if (!ExistenceOfArcNOriented(sVertexArr, sVertexDep))
                    {
                        VertexArr->VERAddInTheMapIn(sVertexDep);
                        VertexDep->VERAddInTheMapOut(sVertexArr);


                        addPairKeysMArcs(sVertexDep, sVertexArr);

                        string res = "arc (" + sVertexDep + " " + sVertexArr + ") created successfully";
                        cout << res << endl;
                    }
                    else
                    {
                        string sErrorMessage = "an arc with a vertexDep " + sVertexDep + " and vertexArr " + sVertexArr + " is already in the graph";
                        throw CException(arc_already_existed, sErrorMessage, "CGraphOriented.cpp", 68);
                    }
                }
                else
                {
                    string sErrorMessage = "an arc with a vertexDep " + sVertexDep + " and vertexArr " + sVertexArr + " is already in the graph";
                    throw CException(arc_already_existed, sErrorMessage, "CGraphOriented.cpp", 66);

                }
            }
            else
            {
                string sErrorMessage = "a vertex with the value " + sVertexArr + " doesn't exist";
                throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 70);

            }
        }
        else
        {
            string sErrorMessage = "a vertex with the value " + sVertexDep + " doesn't exist";
            throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 68);
        }
    }

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
    virtual void GRORemoveArc(const string& sVertexDep, const string& sVertexArr)
    {
        if (ExistenceOfVertex(sVertexDep))
        {
            SommetType* VDep = GROGetVertexFromKey(sVertexDep);
            if (ExistenceOfVertex(sVertexArr))
            {
                SommetType* VArr = GROGetVertexFromKey(sVertexArr);

                if (ExistenceOfArcNOriented(sVertexDep, sVertexArr))
                {
                    pair<string, string> key{ sVertexDep, sVertexArr };

                    ArcType* arc = GROGetArcFromKeys(sVertexDep, sVertexArr);

                    mGROArcs.erase(key);

                    delete arc;

                    VDep->removeArcFromArcIn(sVertexArr);
                    VDep->removeArcFromArcOut(sVertexArr);
                    VArr->removeArcFromArcIn(sVertexDep);
                    VArr->removeArcFromArcOut(sVertexDep);

                    string res = "arc (" + sVertexDep + " " + sVertexArr + ") removed successfully";

                    cout << res << endl;
                }
                else
                {
                    string sErrorMessage = "an arc with a vertexDep " + sVertexDep + " and vertexArr " + sVertexArr + " is not in the graph";
                    throw CException(arc_already_existed, sErrorMessage, "CGraphOriented.cpp", 178);
                }
            }
            else
            {
                string sErrorMessage = "a vertex with the value " + sVertexArr + " doesn't exist";
                throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 117);
            }
        }
        else
        {
            string sErrorMessage = "a vertex with the value " + sVertexDep + " doesn't exist";
            throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 115);

        }
    }

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
    virtual void GROModifyVertex(const string& sVertexOldValue, const string& sVertexNewValue)
    {
        if (ExistenceOfVertex(sVertexOldValue))
        {
            if (!ExistenceOfVertex(sVertexNewValue))
            {
                SommetType* VertexOldValue = GROGetVertexFromKey(sVertexOldValue);
                set<string> adjacentVertecies = VertexOldValue->getAllAdjacenceVertexToAVertex();

                for (string sAdjVertex : adjacentVertecies)
                {
                    SommetType* VAdjVertex = GROGetVertexFromKey(sAdjVertex);
                    if (ExistenceOfArcNOriented(sVertexOldValue, sAdjVertex))
                    {
                        VAdjVertex->changeKeysVerArcIn(sVertexOldValue, sVertexNewValue);
                        ArcType* arc = GROGetArcFromKeys(sVertexOldValue, sAdjVertex);
                        arc->ModifyVertexDep(sVertexNewValue);

                        pair<string, string> oldKey{ sVertexOldValue, sAdjVertex };
                        pair<string, string> newKey{ sVertexNewValue, sAdjVertex };

                        mGROArcs[newKey] = arc;

                        mGROArcs.erase(oldKey);
                    }
                    else
                    {
                        VAdjVertex->changeKeysVerArcOut(sVertexOldValue, sVertexNewValue);
                        ArcType* arc = GROGetArcFromKeys(sAdjVertex, sVertexOldValue);
                        arc->ModifyVertexArr(sVertexNewValue);

                        pair<string, string> oldKey{ sAdjVertex, sVertexOldValue };

                        pair<string, string> newKey{ sAdjVertex, sVertexNewValue };

                        mGROArcs[newKey] = arc;

                        mGROArcs.erase(oldKey);
                    }
                }

                VertexOldValue->VERModifyName(sVertexNewValue);
                mGROVertex.erase(sVertexOldValue);
                mGROVertex[sVertexNewValue] = VertexOldValue;
            }
            else
            {
                string sErrorMessage = "a vertex with the value " + sVertexNewValue + " already exists in the graph";
                throw CException(vertex_already_existed, sErrorMessage, "CGraphOriented.cpp", 161);
            }
        }
        else
        {
            string sErrorMessage = "a vertex with the value " + sVertexOldValue + " doesn't exist";
            throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 159);
        }
    }

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
    virtual void GROInverserArc(const string& sVertexDep, const string& sVertexArr)
    {
        if (ExistenceOfVertex(sVertexDep))
        {
            if (ExistenceOfVertex(sVertexArr))
            {
                if (ExistenceOfArcNOriented(sVertexDep, sVertexArr))
                {
                    if (sVertexDep != sVertexArr)
                    {
                        SommetType* vertexDep = GROGetVertexFromKey(sVertexDep);
                        SommetType* vertexArr = GROGetVertexFromKey(sVertexArr);

                        vertexDep->VERModifyArcOut(sVertexArr, false);
                        vertexDep->VERAddInTheMapIn(sVertexArr);

                        vertexArr->VERModifyArcIn(sVertexDep, false);
                        vertexArr->VERAddInTheMapOut(sVertexDep);

                        ArcType* arc = GROGetArcFromKeys(sVertexDep, sVertexArr);

                        arc->ModifyVertexDep(sVertexArr);
                        arc->ModifyVertexArr(sVertexDep);

                        pair<string, string> pairOldKey{ sVertexDep, sVertexArr };

                        mGROArcs.erase(pairOldKey);

                        pair<string, string> pairNewKey{ sVertexArr, sVertexDep };

                        mGROArcs[pairNewKey] = arc;

                        cout << "arc (" + sVertexDep + ", " + sVertexArr + ") inversed successfully " << endl;
                    }

                }
                else
                {
                    string sErrorMessage = "an arc with a vertex Dep " + sVertexDep + " an vertex Arr " + sVertexArr + " doesn't exist";
                    throw CException(arc_not_existed, sErrorMessage, "CGraphOriented.cpp", 141);

                }
            }
            else
            {
                string sErrorMessage = "a vertex with the value " + sVertexArr + " doesn't exist";
                throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 287);
            }
        }
        else
        {
            string sErrorMessage = "a vertex with the value " + sVertexDep + " doesn't exist";
            throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.cpp", 285);

        }
    }

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
    virtual void GROInverserAllArcs()
    {
        vector<pair<string, string>> res;
        vector<pair<string, string>> arcsToInvert;

        for (const auto& arcEntry : mGROArcs) {
            arcsToInvert.push_back({ arcEntry.first.first, arcEntry.first.second });
        }

        vector<pair<string, string>>::iterator it = arcsToInvert.begin();

        for (; it != arcsToInvert.end(); it++)
        {
            vector<pair<string, string>>::iterator foundDepArr = find(res.begin(), res.end(), make_pair(it->first, it->second));
            vector<pair<string, string>>::iterator foundArrDep = find(res.begin(), res.end(), make_pair(it->second, it->first));

            if (foundDepArr == res.end() && foundArrDep == res.end())
            {
                GROInverserArc(it->first, it->second);
                res.push_back(make_pair(it->first, it->second));
            }
        }

        cout << "all arcs have been inversed successfully " << endl;
    }

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
    const unordered_map<string, SommetType*>& GROGetVertexMap() const
    {
        return mGROVertex;
    }



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
    void GROPrintAllVertecies()
    {
        typename unordered_map<string, SommetType*>::iterator it = mGROVertex.begin();

        for (; it != mGROVertex.end(); it++)
        {
            cout << it->first << endl;
        }
    }

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
    void PrintAllArcs()
    {
        for (pair<pair<string, string>, ArcType*> pair : mGROArcs)
        {
            cout << pair.first.first + " " << pair.first.second << endl;
        }
    }

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
    virtual void GROPrintGraph()
    {
        unordered_map<string, SommetType*> VerteciesMap = GROGetVertexMap();
        typename unordered_map<string, SommetType*>::iterator it = VerteciesMap.begin();

        for (; it != VerteciesMap.end(); it++)
        {
            cout << it->first << " : " << it->second->getAllListInVertecies() << endl;
        }
    }


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
    bool ExistenceOfVertex(const string& key)
    {
        bool res = false;

        if (GROGetMVertex().count(key) > 0)
            res = true;

        return res;
    }

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
    bool ExistenceOfArcNOriented(const string& sVertexDep, const string& sVertexArr)
    {
        bool res = false;

        if (GROGetMArcs().count(make_pair(sVertexDep, sVertexArr)) > 0)
            res = true;
        return res;
    }

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
    void addKeyVertexInMap(const string& key)
    {
        SommetType* newVertex = new SommetType(key);
        mGROVertex[key] = newVertex;
    }

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
    unordered_map<string, SommetType*>& GROGetMVertex()
    {
        return mGROVertex;
    }


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
    unordered_map<pair<string, string>, ArcType*, hash_pair>& GROGetMArcs()
    {
        return mGROArcs;
    }

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
    void addPairKeysMArcs(const string& sVertexDep, const string& sVertexArr)
    {
        pair<string, string> pairkeyDepArr{ sVertexDep, sVertexArr };

        ArcType* newArc = new ArcType(sVertexDep, sVertexArr);

        mGROArcs[pairkeyDepArr] = newArc;
    }

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
    SommetType* GROGetVertexFromKey(const string& key)
    {
        return mGROVertex[key];
    }

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
    ArcType* GROGetArcFromKeys(const string& sVertexDep, const string& sVertexArr)
    {
        pair<string, string> pairKey{ sVertexDep, sVertexArr };
        return mGROArcs[pairKey];
    }

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
    void GRORemoveArcFromMap(const string& sVertexDep, const string& sVertexArr)
    {
        pair<string, string> pairKey{ sVertexDep, sVertexArr };

        mGROArcs.erase(pairKey);
    }

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
    void ModifyArc(const string& sVertexDep, const string& sVertexArr, CArc*& arc)
    {
        pair<string, string> pairKey{ sVertexDep, sVertexArr };
        mGROArcs[pairKey] = arc;
    }


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
    void ModifyVertex(const string& sVertexOldValue, const string& sVertexNewValue, SommetType*& vertex)
    {
        EraseVertexKey(sVertexOldValue);
        mGROVertex[sVertexNewValue] = vertex;
    }

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
    void EraseVertexKey(const string& key)
    {
        mGROVertex.erase(key);
    }
};
#endif 