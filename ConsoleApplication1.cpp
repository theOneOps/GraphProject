
#include <iostream>
#include "CArc/Arc.h"
#include "CVertex/CVertex.h"
#include "PrintGraph/CPrintGraph.h"
#include "Parser/Parser.h"
#include "CGraph/CGraphNOrient.h"
#include "CGraph/CGraphOrient.h"
#include "Parser/CGraphParser.h"
#include "CException/CException.h"

#include "Utils/ShortestPathDjistra.h"


using namespace std;


int main()
{
    CGraphOrient<CVertex, CArc> graph;

    graph.GROAddVertex("1");
    graph.GROAddVertex("2");
    graph.GROAddVertex("3");
    graph.GROAddVertex("4");
    graph.GROAddVertex("5");
    graph.GROAddVertex("6");
    graph.GROAddVertex("7");
    graph.GROAddVertex("8");
    graph.GROAddVertex("10");


    graph.GROAddArc("1", "10");

    graph.GROAddArc("1", "2", 2);
    graph.GROAddArc("1", "4", 3);
    graph.GROAddArc("1", "3", 2);
    graph.GROAddArc("2", "5", 4);
    graph.GROAddArc("3", "6", 2);
    graph.GROAddArc("3", "7", 1);
    graph.GROAddArc("5", "6", 1);
    graph.GROAddArc("5", "8", 2);
    graph.GROAddArc("6", "8", 1);
    graph.GROAddArc("4", "7", 1);
    graph.GROAddArc("7", "8", 3);

    //CPrintGraph::PRIPrintGraph(graph);

    CShortestPathDjistra::SPDGetShortestPathDjistra(graph, "1", "8");

   
    return 0;
}