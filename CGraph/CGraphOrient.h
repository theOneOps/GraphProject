#ifndef CGRAPH_ORIENT_H
#define CGRAPH_ORIENT_H

#include "../CArc/Arc.h"
#include "../CVertex/CVertex.h"
#include <unordered_map>
#include <string>
#include <utility>
#include <set>
#include "../CException/CException.h"

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

    // we just check if the type put in the class's type are what we are expected to have
    static_assert(is_base_of<CVertex, SommetType>::value, "SommetType needs to be a CVertex class or a derivate of CVertex's class");
    static_assert(is_base_of<CArc, ArcType>::value, "ArcType needs to be a CArc class or a derivate of CArc's class");

    //Attributs

    // for one record, the key represents the value of the vertex we want to store
    // and the value of the record would be the involved arc
    unordered_map<string, SommetType*> mGROVertex;

    // here is a definition of the hashcode to represents a pair of value for 
    // an arc in the mGROArcs unordered_mpa 
    struct hash_pair {
        size_t operator()(const pair<string, string>& p) const {
            size_t hash1 = hash<string>{}(p.first);
            size_t hash2 = hash<string>{}(p.second);
            return hash1 ^ hash2;
        }
    };

    // for one record, the key represents a pair of the start value of the arc, 
    // and the end value of the arc we want to store and the value of the record
    // would be the involved arc
    unordered_map<pair<string, string>, ArcType*, hash_pair> mGROArcs;

public:

    //Constructors

    CGraphOrient() = default;


    /**
    *******************************************************************************
    * CGraphOrient(CGraphOrient<SommetType, ArcType>& graph)
    * *****************************************************************************
    * Entries : CGraphOrient<SommetType, ArcType>& graph
    * Needs : None
    * Returns : CGraphOrient<SommetType, ArcType>& graph
    * Leads : the return graph will have the same structure as the graph given as parameter,
    * But the return graph won't point to the same memory as the graph given as parameter
    *******************************************************************************
    */
    CGraphOrient(CGraphOrient<SommetType, ArcType>& graph)
    {
        // To create a new Oriented graph, we should first add all Vertices of the graph given as parameter 
        for (const pair<string, SommetType*>& pair : graph.GROGetMVertex())
        {
            GROAddVertex(pair.first);
        }

        // and we do the same for all of the arcs of the graph given as parameter
        for (const pair<pair<string, string>, ArcType*>& pair : graph.GROGetMArcs())
        {
            GROAddArc(pair.first.first, pair.first.second);
        }
    }

    /**
    *******************************************************************************
    *  ~CGraphOrient()
    * *****************************************************************************
    * Entries : None
    * Needs : None
    * Returns : void
    * Leads : Destroy the graph by desallocating the memory for all the Vertices and all the arcs between those Vertices
    *******************************************************************************
    */
    ~CGraphOrient()
    {
        /*
        * To delete a graph, we need to delete : 
        */
        // all the Vertices of the graph
        for (pair<string, SommetType*> pair : mGROVertex)
        {
            delete pair.second;
        }

        // all the arcs of the graph
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
        the graph before, unless throw an exception
    *******************************************************************************
    */
    void GROAddVertex(const string& key)
    {
        // to add a vertex, we need to check first, if the value of the vertex we want to add, is available
        //(not use by other vertex before)
        if (!GROExistenceOfVertex(key))
        {
            // so if it's available, we call GROAddKeyVertexInMap's method to create the vertex with the "key" value and 
            // added it to the unordered_map that contains all the Vertices of the graph
            GROAddKeyVertexInMap(key);
            cout << "vertex added successfully" << endl;
        }
        else
        {
            // if the key is not avalaible to use, an exception is thrown
            string sErrorMessage = "a vertex with the value " + key + " already exists";
            throw CException(vertex_already_existed, sErrorMessage, "CGraphOriented.h", 144);
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
    virtual void GRORemoveVertex(const string& skey)
    {
        // to remove a vertex, we need to check if the vertex to remove ireally existed in the graph
        if (GROExistenceOfVertex(skey))
        {
            // if that's so, we get the vertex by accessing it by its value from the unordered_map
            // mGROArcs( that contains all the Vertices of the graph )
            SommetType* Vertex = GROGetVertexFromKey(skey);

            // then we get all, the value of the veeertecies adjacents to the vertex we want to remove
            set<string> adjacentVertices = Vertex->VERGetAllAdjacencesVerticesValues();

            // then, by a loop we remove all the arcs that linked our vertex with its adjacents Vertices
            for (string v : adjacentVertices)
            {
                
                try
                {
                    // if their is an arc which value dep is key and the value of one of the Vertices
                    // then we remove it
                    GRORemoveArc(skey, v);
                }
                catch (CException e)
                {
                    //if not, then it's the invert arc one, that we should remove
                    GRORemoveArc(v, skey);
                }
            }

            // afterwards, we deallocate memory for the vertex
            delete Vertex;

            // and finally, we remove the record that represents the vertex from the unordered_map
            // mGROArcs
            mGROVertex.erase(skey);

        }
        else
        {
            // if the vertex we want to remove doesn't exist in the graph, then we throw an exception
            string sErrorMessage = "a vertex with the value " + skey + " doesn't exist";
            throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.h", 174);
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
    * if one of the vertex is not in the graph, it throws an exception
    * if there is already an arc between those Vertices
    *
    * Unless it adds an arc between those Vertices
    *******************************************************************************
    */
    virtual void GROAddArc(const string& sVertexDep, const string& sVertexArr)
    {
        // to add an arc from a start value  "sVertexDep" to and end value "sVertexDArr",
        // we should first check if the involved Vertices of values 
        // "sVertexDep and sVertexArr" really existed

        if (GROExistenceOfVertex(sVertexDep))
        {

            SommetType* VertexDep = GROGetVertexFromKey(sVertexDep);
            if (GROExistenceOfVertex(sVertexArr))
            {
                SommetType* VertexArr = GROGetVertexFromKey(sVertexArr);

                // then we check if there is already an arc between those Vertices or not 
                // the existence of an arc IN 
                if (!GROExistenceOfArcNOriented(sVertexDep, sVertexArr))
                {

                    // the existence of an arc OUT
                    if (!GROExistenceOfArcNOriented(sVertexArr, sVertexDep))
                    {
                        // if there is not arc, then we get accessed to the involved Vertices 
                        // (the one for sVertexArr, and the one for sVertexDep)

                        VertexArr->VERAddInTheMapIn(sVertexDep);
                        VertexDep->VERAddInTheMapOut(sVertexArr);

                        // we create an arc with the correponding start value and end value of the arc
                        // and then we add the arc created to the unorderd_map mGROArcs
                        GROAddPairKeysMArcs(sVertexDep, sVertexArr);

                        string res = "arc (" + sVertexDep + " " + sVertexArr + ") created successfully";
                        cout << res << endl;
                    }
                    else
                    {
                        // if there is already an arc 'IN' in the way, we throw an exception
                        string sErrorMessage = "an arc with a vertexDep " + sVertexDep + " and vertexArr " + sVertexArr + " is already in the graph";
                        throw CException(arc_already_existed, sErrorMessage, "CGraphOriented.h", 251);
                    }
                }
                else
                {   // if there is already an arc 'OUT' in the in way, we throw an exception
                    string sErrorMessage = "an arc with a vertexDep " + sVertexDep + " and vertexArr " + sVertexArr + " is already in the graph";
                    throw CException(arc_already_existed, sErrorMessage, "CGraphOriented.h", 247);

                }
            }
            else
            {   // if the end vertex doesn't exist, we throw an exception
                string sErrorMessage = "a vertex with the value " + sVertexArr + " doesn't exist";
                throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.h", 241);

            }
        }
        else
        {   // if the start vertex doesn't exist, we throw an exception

            string sErrorMessage = "a vertex with the value " + sVertexDep + " doesn't exist";
            throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.h", 237);
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
    * Leads : throw an exception :
    * if one of the vertex is not in the graph, it throws an exception
    * if there is no arc between those Vertices
    *
    * Unless it removes the arc between those Vertices
    *******************************************************************************
    */
    virtual void GRORemoveArc(const string& sVertexDep, const string& sVertexArr)
    {
        // to remove an arc from a start value  "sVertexDep" to and end value "sVertexDArr",
        // we should first check if the involved Vertices of values 
        // "sVertexDep and sVertexArr" really existed
        if (GROExistenceOfVertex(sVertexDep))
        {
            SommetType* VDep = GROGetVertexFromKey(sVertexDep);
            if (GROExistenceOfVertex(sVertexArr))
            {
                SommetType* VArr = GROGetVertexFromKey(sVertexArr);

                // then we check there is really an arc between those Vertices
                if (GROExistenceOfArcNOriented(sVertexDep, sVertexArr))
                {
                    pair<string, string> key{ sVertexDep, sVertexArr };

                    // if yes, we get the access the arc we want to remove
                    ArcType* arc = GROGetArcFromKeys(sVertexDep, sVertexArr);

                    // then we erase the arc from the mGROArcs (that contains all arcs of the graph)
                    mGROArcs.erase(key);

                    // then we deallocate the memory for the arc
                    delete arc;

                    // finally, we remove the arc from the start vertex and the end vertex involved in the arc's creation

                    VDep->VERRemoveArcFromArcIn(sVertexArr);
                    VDep->VERRemoveArcFromArcOut(sVertexArr);
                    VArr->VERRemoveArcFromArcIn(sVertexDep);
                    VArr->VERRemoveArcFromArcOut(sVertexDep);

                    string res = "arc (" + sVertexDep + " " + sVertexArr + ") removed successfully";

                    cout << res << endl;
                }
                else
                {
                    // if there is no arc between those Vertices, we throw an exception
                    string sErrorMessage = "an arc with a vertexDep " + sVertexDep + " and vertexArr " + sVertexArr + " is not in the graph";
                    throw CException(arc_already_existed, sErrorMessage, "CGraphOriented.h", 323);
                }
            }
            else
            {
                // if the end vertex doesn't exist in the graph, we remove the graph
                string sErrorMessage = "a vertex with the value " + sVertexArr + " doesn't exist";
                throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.h", 318);
            }
        }
        else
        {
            // if the start vertex doesn't exist in the graph, we remove the graph
            string sErrorMessage = "a vertex with the value " + sVertexDep + " doesn't exist";
            throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.h", 315);

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
    * if a vertex of value equals to sVertexOldValue doesn't exsit in the graph
    * if the new value to put in replace on the sVertexOldValue already exist
    *
    * Unless change the vertex by assigining sVertexNewValue to his old value, and apply the change to the entire graph
    *******************************************************************************
    */
    virtual void GROModifyVertex(const string& sVertexOldValue, const string& sVertexNewValue)
    {
        // to modify the involved vertex, we should first test if it exists
        if (GROExistenceOfVertex(sVertexOldValue))
        {
            // then we should check if a vertex with a new value, is in the graph or not
            if (!GROExistenceOfVertex(sVertexNewValue))
            {
                // if not then we first get the vertex we want to modify the value of
                SommetType* VertexOldValue = GROGetVertexFromKey(sVertexOldValue);

                // then we get the adjacents Vertices that are linked to our vertex
                set<string> adjacentVertices = VertexOldValue->VERGetAllAdjacencesVerticesValues();

                // next with a for loop, we go through all arcs that linked our vertex to each of its adjacents vertex 
                for (string sAdjVertex : adjacentVertices)
                {

                    //cout << "vertex -> " + sAdjVertex << endl;

                    // if the current arc is in IN direction 
                    // we just change the value at start of the arc ith the new value of the arc
                    SommetType* VAdjVertex = GROGetVertexFromKey(sAdjVertex);

                    if (GROExistenceOfArcNOriented(sVertexOldValue, sAdjVertex))
                    {
                        ArcType* arc = GROGetArcFromKeys(sVertexOldValue, sAdjVertex);

                        if (sAdjVertex == sVertexOldValue)
                        {
                            VAdjVertex->VERChangeKeysVerArcIn(sVertexOldValue, sVertexNewValue);
                            VAdjVertex->VERChangeKeysVerArcOut(sVertexOldValue, sVertexNewValue);

                            GRORemoveArcFromMap(sVertexOldValue, sVertexOldValue);

                            arc->ARCGROModifyVertexDep(sVertexNewValue);

                            arc->ARCGROModifyVertexArr(sVertexNewValue);

                            pair<string, string> oldKey{ sVertexOldValue, sAdjVertex };
                            pair<string, string> newKey{ sVertexNewValue, sVertexNewValue };

                            // then we put the arc into the correct key contituted of the right start value 
                            // "sVertexNewValue" and the right end value "sAdjVertex" (value of the current adjacent vertex)
                            mGROArcs[newKey] = arc;

                            // finally we erase the old record of the arc from the unordored_map, mGROArcs
                            mGROArcs.erase(oldKey);
                        }
                        else
                        {
                            arc->ARCGROModifyVertexDep(sVertexNewValue);

                            //arc->ARCGROModifyVertexArr(sAdjVertex);

                            VAdjVertex->VERRemoveArcFromArcIn(sVertexOldValue);

                            VAdjVertex->VERAddInTheMapIn(sVertexNewValue);

                            // valeur d'avant de l'enregistrment de l'arc dans le mGROArcs, il faut l'enlever et y mettre le nouveau key pair

                            pair<string, string> oldKey{ sVertexOldValue, sAdjVertex };
                            pair<string, string> newKey{ sVertexNewValue, sAdjVertex };

                            // then we put the arc into the correct key contituted of the right start value 
                            // "sVertexNewValue" and the right end value "sAdjVertex" (value of the current adjacent vertex)
                            mGROArcs[newKey] = arc;

                            // finally we erase the old record of the arc from the unordored_map, mGROArcs
                            mGROArcs.erase(oldKey);

                        }
                    }
                    else
                    {
                        ArcType* arc = GROGetArcFromKeys(sAdjVertex, sVertexOldValue);

                        arc->ARCGROModifyVertexArr(sVertexNewValue);

                        //arc->ARCGROModifyVertexArr(sAdjVertex);

                        VAdjVertex->VERRemoveArcFromArcOut(sVertexOldValue);

                        VAdjVertex->VERAddInTheMapOut(sVertexNewValue);

                        // valeur d'avant de l'enregistrement de l'arc dans le mGROArcs, il faut l'enlever et y mettre le nouveau key pair

                        pair<string, string> oldKey{sAdjVertex, sVertexOldValue };
                        pair<string, string> newKey{ sAdjVertex, sVertexNewValue };

                        // then we put the arc into the correct key contituted of the right start value 
                        // "sVertexNewValue" and the right end value "sAdjVertex" (value of the current adjacent vertex)
                        mGROArcs[newKey] = arc;

                        // finally we erase the old record of the arc from the unordored_map, mGROArcs
                        mGROArcs.erase(oldKey);

                    }
                }

                // finally, we change the value of the vertex 
                VertexOldValue->VERModifyName(sVertexNewValue);

                // we erase the old record of the vertex in the mGROVertex
                mGROVertex.erase(sVertexOldValue);

                // we put the vertex into a new record using its new value as key
                mGROVertex[sVertexNewValue] = VertexOldValue;
            }
            else
            {
                // if the new value is already in use by another vertex, we throw an exception
                string sErrorMessage = "a vertex with the value " + sVertexNewValue + " already exists in the graph";
                throw CException(vertex_already_existed, sErrorMessage, "CGraphOriented.h", 391);
            }
        }
        else
        {
            // if there is no vertex with the old value we want to change, we throw an exception
            string sErrorMessage = "a vertex with the value " + sVertexOldValue + " doesn't exist";
            throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.h", 388);
        }
    }

    /**
    *******************************************************************************
    * GROInverserArc
    * *****************************************************************************
    * Entries : sVertexOldValue : string represented the old value of the vertex,
    *           sVertexNewValue : string represented the new value to replace that old Value of the vertex
    *
    * Needs : None
    * Returns : void
    * Leads : throw an exception if :
    * the Vertices of the arc don't exist in the graph
    *
    * Unless we reverse the arc by changing the link between
    *    the Vertices of the arc and by reversing the arc as well
    *******************************************************************************
    */
    virtual void GROInverserArc(const string& sVertexDep, const string& sVertexArr)
    {
        // To invert an arc, we need to first check if the involved Vertices in the creation of the arc really exist
        if (GROExistenceOfVertex(sVertexDep))
        {
            if (GROExistenceOfVertex(sVertexArr))
            {
                // if that's so, check if there is an arc between them to invert
                if (GROExistenceOfArcNOriented(sVertexDep, sVertexArr))
                {
                    // it yes, then we check if our Vertices are equal or not, if they are equal then inverting the arc won't change anything
                    if (sVertexDep != sVertexArr)
                    {
                        // if they are not equals, we first get accessed to those Vertices
                        SommetType* vertexDep = GROGetVertexFromKey(sVertexDep);
                        SommetType* vertexArr = GROGetVertexFromKey(sVertexArr);

                        // we change the In and Out of the Vertices
                        vertexDep->VERGROModifyArcOut(sVertexArr, false);
                        vertexDep->VERAddInTheMapIn(sVertexArr);

                        vertexArr->VERGROModifyArcIn(sVertexDep, false);
                        vertexArr->VERAddInTheMapOut(sVertexDep);

                        // then we get accessed to the arc, and we invert its start value and end value
                        ArcType* arc = GROGetArcFromKeys(sVertexDep, sVertexArr);

                        arc->ARCGROModifyVertexDep(sVertexArr);
                        arc->ARCGROModifyVertexArr(sVertexDep);

                        pair<string, string> pairOldKey{ sVertexDep, sVertexArr };

                        // then we remove the old record of the arc since the key's register has changed
                        mGROArcs.erase(pairOldKey);

                        pair<string, string> pairNewKey{ sVertexArr, sVertexDep };

                        // then we put the arc to the right key
                        mGROArcs[pairNewKey] = arc;

                        cout << "arc (" + sVertexDep + ", " + sVertexArr + ") inversed successfully " << endl;
                    }

                }
                else
                {
                    // if there is no arc to invert, we throw an exception
                    string sErrorMessage = "an arc with a vertex Dep " + sVertexDep + " an vertex Arr " + sVertexArr + " doesn't exist";
                    throw CException(arc_not_existed, sErrorMessage, "CGraphOriented.h", 533);

                }
            }
            else
            {
                // if the end vertex doesn't exist, we throw an exception
                string sErrorMessage = "a vertex with the value " + sVertexArr + " doesn't exist";
                throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.h", 530);
            }
        }
        else
        {
            // if the start vertex doesn't exist, we throw an exception
            string sErrorMessage = "a vertex with the value " + sVertexDep + " doesn't exist";
            throw CException(vertex_not_existed, sErrorMessage, "CGraphOriented.h", 528);

        }
    }

    /**
    *******************************************************************************
    * GROInverserAllArcs
    * *****************************************************************************
    * Entries : None
    * Needs : the arcs to invert should exist as well as the Vertices that link the arc
    * Returns : void
    * Leads : This function uses the GROInverseArc to invert an arc between
    * two Vertices and it does that with all the arcs of the graph
    *******************************************************************************
    */
    virtual void GROInverserAllArcs()
    {
        
        vector<pair<string, string>> res;
        vector<pair<string, string>> arcsToInvert;

        // first, we get access to all the arcs of the graph and we put them in the arcInvert vector
        for (const pair<pair<string, string>, ArcType*>& arcEntry : mGROArcs) {
            arcsToInvert.push_back({ arcEntry.first.first, arcEntry.first.second });
        }

        // then we create an iterator to go through the arcs we gether in the arcInvert vector
        vector<pair<string, string>>::iterator it = arcsToInvert.begin();

        // next, with a for loop, hence to the iterator instancied before, we go through 
        // those arcs and call the GROInverserArc's method to invert them

        for (; it != arcsToInvert.end(); it++)
        {
            // here we just check if we haven't invert the current arc before
            // and we check by verifying if there is no arc added into the res vector 
            // which start value or end value is the start or end value of the current arc

            vector<pair<string, string>>::iterator foundDepArr = find(res.begin(), res.end(), make_pair(it->first, it->second));
            
            vector<pair<string, string>>::iterator foundArrDep = find(res.begin(), res.end(), make_pair(it->second, it->first));

            // and if after the check there is no intels (condition "if" is true)
            if (foundDepArr == res.end() && foundArrDep == res.end())
            {
                // we invert the arc
                GROInverserArc(it->first, it->second);
                // we add the startvalue and end value of the arc that just bing inverted into to res vector
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
    * Leads : Return the map that contains all the Vertices of the graph in readonly mode
    * hence the const at the end of the function
    *******************************************************************************
    */
    const unordered_map<string, SommetType*>& GROGetVertexMap() const
    {
        // just return a const reference to the unordered_map that contains all Vertices of the graph
        // to be used only in readonly way
        return mGROVertex;
    }

    /**
    *******************************************************************************
    * GROExistenceOfArcNOriented
    * *****************************************************************************
    * Entries :  sVertexDep: string represented the start value of the arc,
    * sVertexArr: string represented the end value of the arc
    * Needs : None
    * Returns : void
    * Leads : Verify if there is an arc with a start equals to sVertexDep and
    * the end value equals to sVertexArr
    *******************************************************************************
    */
    bool GROExistenceOfArcNOriented(const string& sVertexDep, const string& sVertexArr)
    {
        bool res = false;

        // to check if there is an arc with start value equals to sVertexDep and end value equals to sVertexArr,
        // we count the number of vertex with value equals to the key string
        if (GROGetMArcs().count(make_pair(sVertexDep, sVertexArr)) > 0)
            res = true;

        return res;
    }

    unsigned int GROGetWeightOFArc(string sVertexDep, string sVertexArr)
    {
        //pair<string, string> key { sDep, sArr };
        return mGROArcs[make_pair(sVertexDep, sVertexArr)]->ARCGetWeight();
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
    ArcType*& GROGetArcFromKeys(const string& sVertexDep, const string& sVertexArr)
    {
        // this method just returns the arc which start value is sVertexDep 
        // and end valus is sVertexArr
        pair<string, string> pairKey{ sVertexDep, sVertexArr };
        return mGROArcs[pairKey];
    }

protected:

    /**
    *******************************************************************************
    * GROExistenceOfVertex
    * *****************************************************************************
    * Entries : skey : string
    * Needs : None
    * Returns : bool
    * Leads : Check if the vertex with the value skey exist in the graph
    *******************************************************************************
    */
    bool GROExistenceOfVertex(const string& skey)
    {
        bool res = false;

        // to check if there is a vertex of value key in the graph, we count 
        //the number of vertex with value equals to the key string
       
        // if the answer is upper than 0 then there is effectively an vertex of value key
        if (GROGetMVertex().count(skey) > 0)
            res = true;

        return res;
    }

    /**
    *******************************************************************************
    * GROAddKeyVertexInMap
    * *****************************************************************************
    * Entries : skey: string represented the value of the vertex to create and to add to the graph
    * Needs : None
    * Returns : void
    * Leads : add a vertex with value equals to skey by at the same time, creating the due vertex
    * This function is used in the GROAddVertex of course...
    *******************************************************************************
    */
    void GROAddKeyVertexInMap(const string& skey)
    {
        // to add a vertex of value key to the mGROVertex unordered_map,
        // we first allocate memory for that vertex with the value key
        SommetType* newVertex = new SommetType(skey);

        // then we put the vertex we just create into the mGROVertex at the key value
        mGROVertex[skey] = newVertex;
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
        // this method returns a reference to the mGROVertex unordered_map
        // that could be used directly in classes that specialize this class
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
        // this method returns a reference to the mGROArcs unordered_map
       // that could be used directly in classes that specialize this class
        return mGROArcs;
    }

    /**
    *******************************************************************************
    * GROAddPairKeysMArcs
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
    void GROAddPairKeysMArcs(const string& sVertexDep, const string& sVertexArr)
    {
        // to add an arc of start value equals to sVertexDep, and end value equals to sVertexArr,
       // we first get the key
        pair<string, string> pairkeyDepArr{ sVertexDep, sVertexArr };

        // then we allocate memory for the arc
        ArcType* newArc = new ArcType(sVertexDep, sVertexArr);

        // finally we insert the arc into the mGROArcs unordered_map at key that repsents the pairkeyDepArr's variable

        mGROArcs[pairkeyDepArr] = newArc;
    }

    /**
    *******************************************************************************
    * getVertexFromKey
    * *****************************************************************************
    * Entries : skey : string represented
    * Needs : None
    * Returns :  CVertex*
    * Leads : return the vertex with the value equals to skey
    *******************************************************************************
    */
    SommetType* GROGetVertexFromKey(const string& skey)
    {
        // this method just returns the vertex at the key value from the mGROVertex unordered_map 
        return mGROVertex[skey];
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
        // we remove the record of the arc which start value is sVertexDep 
        // and end value is sVertexArr from the mGROArcs unordered_map
        pair<string, string> pairKey{ sVertexDep, sVertexArr };


        mGROArcs.erase(pairKey);
    }

    /**
    *******************************************************************************
    * GROModifyArc
    * *****************************************************************************
    * Entries : sVertexDep: string represented the start value of the arc,
    * sVertexArr: string represented the end value of the arc
    *  arc: CArc*& represented the arc to store
    * Needs : None
    * Returns : void
    * Leads : store the arc with
    * It's used in the GROInverseArc's function to change the key in which we have stored the previous arc we have just inverted
    *******************************************************************************
    */
    void GROModifyArc(const string& sVertexDep, const string& sVertexArr, CArc*& arc)
    {
        // we modify the record of the arc which start value is sVertexDep 
        // and end value is sVertexArr from the mGROArcs unordered_map by putting the new "arc" 
        pair<string, string> pairKey{ sVertexDep, sVertexArr };

        //if (sVertexDep == sVertexArr)
          //  cout << "passage reussi " << endl;

        mGROArcs[pairKey] = arc;
    }


    /**
    *******************************************************************************
    * GROModifyVertex
    * *****************************************************************************
    * Entries : sVertexDep: string represented the start value of the arc,
    * sVertexArr: string represented the end value of the arc
    * Needs : None
    * Returns : void
    * Leads :
    * this function is used in the GROModifyVertex's function
    *******************************************************************************
    */
    void GROModifyVertex(const string& sVertexOldValue, const string& sVertexNewValue, SommetType*& vertex)
    {
        // to modify a vertex, we need to remove the old record with the old value "sVertexOldValue" of the vertex
        GROEraseVertexKey(sVertexOldValue);

        // and then we insert our new vertex to the new key "sVertexNewValue"
        mGROVertex[sVertexNewValue] = vertex;
    }

    /**
    *******************************************************************************
    * GROEraseVertexKey
    * *****************************************************************************
    * Entries : key : string represented the value of the vertex to erase from the graph
    * Needs : None
    * Returns : void
    * Leads : erase the vertex with the value from the map that contains all the Vertices of the graph
    *
    * this function is used in the GROModifyVertex's function
    *******************************************************************************
    */
    void GROEraseVertexKey(const string& skey)
    {
        // we remove the record of the vertex at the value "key" from the mGROVertex unordered_map
        mGROVertex.erase(skey);
    }
};
#endif 