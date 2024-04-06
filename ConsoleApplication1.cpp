
#include <iostream>
#include "CArc/Arc.h"
#include "CVertex/CVertex.h"
#include "CPrintGraph.h"
#include "Parser/Parser.h"
#include "CGraphOrient.h"
#include "CGraphNOrient.h"
#include "Parser/CGraphParser.h"

using namespace std;


int main()
{
	// testGraphNOriented();
	// testGraphOriented();
	// testGraphOrient();

	/*
	
	try
	{
		CGraphNOrient<CVertex, CArc> graphC;

		graphC.GROAddVertex("1");
		graphC.GROAddVertex("2");
		graphC.GROAddVertex("3");
		graphC.GROAddVertex("4");


		graphC.GROAddArc("1", "2");
		graphC.GROAddArc("2", "3");
		graphC.GROAddArc("3", "1");
		graphC.GROAddArc("1", "1");
		graphC.GROAddArc("4", "4");

		//cout << "inversion des arcs " << endl;

		//CPrintGraph::PrintGraph(graphC);

		graphC.GROInverserAllArcs();

		CPrintGraph::PrintGraph(graphC);

		graphC.GROAddArc("1", "4");

		graphC.GROModifyVertex("1", "5");

		graphC.GROModifyVertex("4", "7");


		CPrintGraph::PrintGraph(graphC);

		//cout << "remove of the arc (1, 2)" << endl;

		cout << "inversion of the arc (3, 2)" << endl;

		graphC.GROInverserArc("3", "2");

		CPrintGraph::PrintGraph(graphC);

		cout << "inversion of all arcs" << endl;

		graphC.GROInverserAllArcs();

		CPrintGraph::PrintGraph(graphC);

		cout << "suppression du vertex 5" << endl;

		graphC.GRORemoveVertex("5");

		CPrintGraph::PrintGraph(graphC);

		graphC.GROModifyVertex("7", "4");

		graphC.GROModifyVertex("2", "1");

		cout << "modification du 7 en 4 et celui de 2 en 1" << endl;

		CPrintGraph::PrintGraph(graphC);

		graphC.GROAddArc("1", "1");

		graphC.GROModifyVertex("1", "2");

		CPrintGraph::PrintGraph(graphC);

	}
	catch (CException e)
	{
		e.CEXReadMessage();
	}

	*/

	try
	{
		CGraphParser<CVertex, CArc> parser;

		parser.PARGRAMain("graph.txt");

	}
	catch (CException e)
	{
		e.CEXReadMessage();
	}

}

