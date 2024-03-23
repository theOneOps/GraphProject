// GraphProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "CArc/Arc.h"
#include "CGraph/CGraphOriented.h"
#include "CPrintGraph.h"
#include "CVertex/CVertex.h"
#include "CException/CException.h"

using namespace std;

int main()
{
    try
    {
        CVertex* CVersommet1 = new CVertex("1");
        CVertex* CVersommet2 = new CVertex("2");
        CVertex* CVersommet3 = new CVertex("3");
        CVertex* CVersommet4 = new CVertex("4");

        CGraphOriented* CGRAgraph1 = new CGraphOriented();

        CGRAgraph1->GROAddVertex(CVersommet1);
        CGRAgraph1->GROAddVertex(CVersommet2);
        CGRAgraph1->GROAddVertex(CVersommet3);
        CGRAgraph1->GROAddVertex(CVersommet4);
        CGRAgraph1->GROAddArc(CVersommet1, CVersommet2);
        CGRAgraph1->GROAddArc(CVersommet2, CVersommet3);
        CGRAgraph1->GROAddArc(CVersommet3, CVersommet1);
        CGRAgraph1->GROAddArc(CVersommet1, CVersommet1);

        CPrintGraph::GROPrintGraph(CGRAgraph1);

        cout << "affichage du graphe apres suppression de l'arc 1 vers 3" << endl;

        CGRAgraph1->GRORemoveArc("1", "3");

        CPrintGraph::GROPrintGraph(CGRAgraph1);

        cout << "afficahge du graphe apres modification du vertex 3 par 5" << endl;

        CGRAgraph1->GROModifyVertex("3", "5");

        CPrintGraph::GROPrintGraph(CGRAgraph1);

        cout << "afficahge du graphe apres suppression de l'arc 2 5" << endl;

        CGRAgraph1->GRORemoveVertex("1");

        CPrintGraph::GROPrintGraph(CGRAgraph1);

        delete CGRAgraph1;
    }
    catch (CException e)
    {
        e.CEXReadMessage();
    }
    return 0;
}