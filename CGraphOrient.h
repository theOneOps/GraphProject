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


/**********************************************************
*  Class : CGrapheOrient
* *********************************************************
* ROLE : management of the Oriented graph
* *********************************************************
* VERSION: 1.0
* AUTHOR: Selly Bill-Gate MEDEWOU
*                 Jeremie YANG
* DATE: 19/03/2024
* *********************************************************
* 
* Variables
* 
* vertex_already_existed 11
* arc_already_existed 10
* vertex_not_existed 9
* arc_not_existed 8
* 
*/
template<typename SommetType, typename ArcType>
class CGraphOrient
{
private:
    static_assert(is_base_of<CVertex, SommetType>::value, "SommetType needs to be a CVertex class or a derivate of CVertex's class");
    static_assert(is_base_of<CArc, ArcType>::value, "ArcType needs to be a CArc class or a derivate of CArc's class");

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

    CGraphOrient() = default;

    /**
    *******************************************************************************
    *  ~CGraphOrient()
    * *****************************************************************************
    * Entries : None
    * Needs : None
    * Returns : void
    * Leads : Destroy the graph by desallocating the memory for all the vertecies and all the arcs between those vertecies
    *******************************************************************************
    */
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
    * Entries : string key: value of the vertex to create
    * Needs : None
    * Returns : void
    * Leads : Add a vertex into the Graph if the vertex isn't in
        the graph before unless throw an exception
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
    * Entries : string key: value of the vertex to remove from the graph
    * Needs : None
    * Returns : void
    * Leads : Remove a vertex into the Graph if the vertex is in
        the graph, but first, it removes all arcs that are related to the vertex,
        before unless throw an exception
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
    * Entries : sVertexDep: string represented the start value of the arc,
    * sVertexArr: string represented the end value of the arc
    * Needs : None
    * Returns : void
    * Leads : throw an exception if :
    * if one of the vertex is not in the graph, it throw an exception
    * if there is already an arc between those vertecies
    *
    * Unless it add a arc between those vertecies
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
    * Entries :  sVertexDep: string represented the start value of the arc,
    * sVertexArr: string represented the end value of the arc
    * Needs : None
    * Returns : void
    * Leads : throw an exception if :
    * if one of the vertex is not in the graph, it throw an exception
    * if there is no arc between those vertecies
    *
    * Unless it removes the arc between those vertecies
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
    * Entries : sVertexOldValue : string  represented the old value of the vertex,
    *           sVertexNewValue : string represented the new value to replace that old Value of the vertex
    * Needs : None
    * Returns : void
    * Leads : throw an exception:
    * if a vertex of value equals to oldValue doesn't exsit in the graph
    * if the new value to put in replace on the oldValue already exist
    *
    * Unless change the vertex by assigining newValue to his old value, and apply the change to the entire graph
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
    * Entries : sVertexOldValue : string  represented the old value of the vertex,
    *           sVertexNewValue : string represented the new value to replace that old Value of the vertex
    *
    * Needs : None
    * Returns : void
    * Leads : throw an exception if :
    * the vertecies of the arc don't exist in the graph
    *
    * Unless we reverse the arc by changing the link between
    *    the vertecies of the arcs and by reversing the arc as well
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
    * Entries : None
    * Needs : the arcs to invert should exist as well as the vertecies that link the arc
    * Returns : void
    * Leads : This function uses the GROInverseArc to invert an arc between
    * two vertecies and it does that with all the arcs of the graph
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
    * Entries : None
    * Needs : None
    * Returns : const unordered_map<string, CVertex*>&
    * Leads : Return the map that contains all the vertecies of the graph in readonly mode
    * hence the const at the end of the function
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
    * Entries : None
    * Needs : None
    * Returns : void
    * Leads : Print all the vertecies of the graph into the console
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
    * Entries : None
    * Needs : None
    * Returns : void
    * Leads : Print all the arcs of the graph into the console
    * in fact, it print the related vertecies between
    * an arc and the direction in between them
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
    * Entries : None
    * Needs : None
    * Returns : void
    * Leads : Print the graph into the console
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
    * Entries : key : string
    * Needs : None
    * Returns : bool
    * Leads : Check if the vertex with the value key exist in the graph
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
    * Entries :  sVertexDep: string represented the start value of the arc,
    * sVertexArr: string represented the end value of the arc
    * Needs : None
    * Returns : void
    * Leads : Verify if there is an arc with a start equals to  sVertexDep and
    * the end value equals to sVertexArr
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
    * Entries : key: string represented the value of the vertex to create and to add to the graph
    * Needs : None
    * Returns : void
    * Leads : add a vertex with value equals to key by at the same time, creating the due vertex
    * This function is used in the GROAddVertex of course...
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
    * Entries : None
    * Needs : None
    * Returns : unordered_map<string, CVertex*>&
    * Leads : Return the map that contains all the veertecies of the graph
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
    * Entries : None
    * Needs : None
    * Returns : unordered_map<pair<string, string>, CArc*, hash_pair>&
    * Leads : Return the map that contains all the arcs of the graph
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
    * Entries : sVertexDep: string represented the start value of the arc,
    * sVertexArr: string represented the end value of the arc
    * Needs : None
    * Returns : void
    * Leads : add an arc with the start value equals to sVertexDep, the end value equals to sVertexArr,
    * by at the same time, creating the due vertex
    * This function is used to add a new arc in the GROAddArc's function
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
    * Entries : key : string represented
    * Needs : None
    * Returns :  CVertex*
    * Leads : return the vertex with the value equals to key
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
    * Entries : sVertexDep: string represented the start value of the arc,
    * sVertexArr: string represented the end value of the arc
    * Needs : None
    * Returns : CArc*
    * Leads :  Return the arc with start value is sVertexDep and end value is sVertexArr
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
    * Entries :sVertexDep: string represented the start value of the arc,
    * sVertexArr: string represented the end value of the arc
    * Needs : None
    * Returns : void
    * Leads : remove the arc from the arcs' map and from the graph
    * It is used in the GRORemoveArc's function
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
    * Entries : sVertexDep: string represented the start value of the arc,
    * sVertexArr: string represented the end value of the arc
    *  arc: CArc*& represented the arc to store
    * Needs : None
    * Returns : void
    * Leads : store the arc with
    * It's used in the GROInverseArc's function to change the key to store the previous arc we have invert
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
    * Entries : sVertexDep: string represented the start value of the arc,
    * sVertexArr: string represented the end value of the arc
    * Needs : None
    * Returns : void
    * Leads :
    * this function is used in the GROModifyVertex's function
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
    * Entries : key : string represented the value of the vertex to erase from the graph
    * Needs : None
    * Returns : void
    * Leads : erase the vertex with the value from the map that contains all the vertecies of the graph
    *
    * this function is used in the ModifyVertex's function
    *******************************************************************************
    */
    void EraseVertexKey(const string& key)
    {
        mGROVertex.erase(key);
    }
};
#endif 