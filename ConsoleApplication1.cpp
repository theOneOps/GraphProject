
#include <iostream>
#include "CArc/Arc.h"
#include "CVertex/CVertex.h"
#include "CPrintGraph.h"
#include "Parser.h"
#include "CGraphOrient.h"
#include "CGraphNOrient.h"

using namespace std;

/*
void testGraphNOriented()
{
	cout << "test graph Non Oriented" << endl;

	try
	{
		CGraphNOriented graphB;

		graphB.GROAddVertex("1");
		graphB.GROAddVertex("2");
		graphB.GROAddVertex("3");
		graphB.GROAddVertex("4");

		graphB.GROAddArc("1", "2");
		graphB.GROAddArc("2", "3");
		graphB.GROAddArc("1", "3");

		CPrintGraph::GROPrintGraph(graphB);

		graphB.GRORemoveArc("3", "1");

		CPrintGraph::GROPrintGraph(graphB);

		graphB.GROInverserAllArcs();

		cout << "replace the vertex value of 1 by 6" << endl;
		graphB.GROModifyVertex("1", "6");

		CPrintGraph::GROPrintGraph(graphB);

		graphB.GRORemoveVertex("6");

		CPrintGraph::GROPrintGraph(graphB);

		//graphB.PrintAllArcs();

	}
	catch (CException e)
	{
		e.CEXReadMessage();
	}

}

void testGraphOriented()
{
	cout << "test graph Oriented" << endl;

	try
	{
		CGraphOriented graphA;
		graphA.GROAddVertex("1");
		graphA.GROAddVertex("2");
		graphA.GROAddVertex("3");
		graphA.GROAddVertex("4");

		graphA.GROPrintAllVertecies();

		graphA.GROAddArc("1", "2");
		graphA.GROAddArc("2", "3");
		graphA.GROAddArc("1", "3");
		graphA.GROAddArc("1", "1");
		graphA.GROAddArc("3", "4");
		graphA.GROAddArc("4", "4");

		CPrintGraph::GROPrintGraph(graphA);

		graphA.GRORemoveArc("1", "1");

		graphA.GROModifyVertex("3", "5");
		graphA.GROModifyVertex("2", "");
		graphA.GROModifyVertex("", "deux");
		graphA.GROModifyVertex("deux", "2");
		graphA.GROModifyVertex("5", "3");

		CPrintGraph::GROPrintGraph(graphA);

		graphA.GRORemoveVertex("1");
		graphA.GROAddVertex("1");
		graphA.GROAddVertex("5");


		graphA.GROAddArc("1", "1");
		graphA.GROAddArc("1", "5");

		CPrintGraph::GROPrintGraph(graphA);

		graphA.GROInverserAllArcs();

		CPrintGraph::GROPrintGraph(graphA);
	}
	catch (CException e)
	{
		e.CEXReadMessage();
	}
}


void testGraphOrient()
{
	cout << "test graph Oriented" << endl;

	try
	{
		CGraphOriented* graphA = new CGraphOriented();

		graphA->GROAddVertex("1");
		graphA->GROAddVertex("2");
		graphA->GROAddVertex("3");
		graphA->GROAddVertex("4");

		graphA->GROPrintAllVertecies();

		graphA->GROAddArc("1", "2");
		graphA->GROAddArc("2", "3");
		graphA->GROAddArc("1", "3");
		graphA->GROAddArc("1", "1");
		graphA->GROAddArc("3", "4");
		graphA->GROAddArc("4", "4");

		graphA->GRORemoveArc("1", "1");
		//graphA->PrintAllArcs();

		graphA->GROModifyVertex("3", "5");
		graphA->GROModifyVertex("2", "");
		graphA->GROModifyVertex("", "deux");
		graphA->GROModifyVertex("deux", "2");
		graphA->GROModifyVertex("5", "3");

		CPrintGraph::GROPrintGraph(*graphA);

		graphA->GROInverserAllArcs();

		CPrintGraph::GROPrintGraph(*graphA);

		delete graphA;
	}
	catch (CException e)
	{
		e.CEXReadMessage();
	}
}

*/

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

		graphC.GROAddArc("1", "2");
		graphC.GROAddArc("2", "3");
		graphC.GROAddArc("3", "1");

		CPrintGraph::PrintGraph(graphC);

		cout << "remove of the arc (1, 2)" << endl;

		graphC.GRORemoveArc("1", "2");

		CPrintGraph::PrintGraph(graphC);

		cout << "inversion of the arc (2, 3)" << endl;

		graphC.GROInverserArc("2", "3");

		CPrintGraph::PrintGraph(graphC);

		cout << "inversion of all arcs" << endl;

		graphC.GROInverserAllArcs();

		CPrintGraph::PrintGraph(graphC);

	}
	catch (CException e)
	{
		e.CEXReadMessage();
	}
	*/

	try
	{
		Parser::PARMainFunc("graph.txt");
	}
	catch (CException e)
	{
		e.CEXReadMessage();
	}
	

}

