
#include <iostream>
#include "CArc/Arc.h"
#include "CVertex/CVertex.h"
#include "PrintGraph/CPrintGraph.h"
#include "Parser/Parser.h"
#include "CGraph/CGraphNOrient.h"
#include "CGraph/CGraphOrient.h"
#include "Parser/CGraphParser.h"
#include "CException/CException.h"

#include "CArc/ArcPondere.h"
#include "Parser/CGraphPondereParser.h"

int main()
{
    CGraphPondereParser<CVertex, CArcPondere> parserPondere;
    parserPondere.GPRMain("graph.txt", "1");
   
    return 0;
}