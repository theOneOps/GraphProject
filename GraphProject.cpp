// GraphProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "CArc/Arc.h"
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
        CGRAgraph1->GROAddArc(CVersommet1, CVersommet4);

        CPrintGraph::GROPrintGraph(CGRAgraph1);

         
        CGRAgraph1->GRORemoveVertex("2");

        cout << "affichage du remove vertex 2" << endl;

        CGRAgraph1->GROAddArc(CVersommet4, CVersommet4);
        CGRAgraph1->GROAddArc(CVersommet3, CVersommet4);

        cout << "ajout des arcs (4 4) et (3 4)" << endl;

        CPrintGraph::GROPrintGraph(CGRAgraph1);

        cout << "Inversion d'arcs" << endl;

        CGRAgraph1->GROInverseAllArcs();

        CGRAgraph1->GRORemoveArc("4", "3");
        CGRAgraph1->GRORemoveArc("4", "4");
        CGRAgraph1->GRORemoveArc("1", "3");

        CPrintGraph::GROPrintGraph(CGRAgraph1);

        CGRAgraph1->GROModifyVertex("4", "5");

        cout << "modification de la valeur du vertex 4 par 5" << endl;

        CPrintGraph::GROPrintGraph(CGRAgraph1);

        CGRAgraph1->GROAddArc(CVersommet3, CVersommet4);

        CGRAgraph1->GRORemoveVertex("5");

        CPrintGraph::GROPrintGraph(CGRAgraph1);

        delete CGRAgraph1;
        
    }
    catch (CException e)
    {
        e.CEXReadMessage();
    }
    return 0;
}