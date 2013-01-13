//
//  create_debruijn.cpp
//  demo
//
//  Created by Shefali Umrania on 1/5/13.
//  Copyright (c) 2013 Shefali Umrania. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
using std::string;
#include <map>
using std::map;
//#include <tr1/unordered_map>
//using std::tr1::unordered_map;
#include <vector>
using std::vector;
#include <algorithm>
using std::reverse;
#include <iostream>
#include<list>
#include <fstream>
using namespace std;

#include "utils.h"
#include "DeBruijn.h"

int main(int nargs, char** argv)
{
    
	FILE* fn_out=NULL;
	if (nargs>1)
	{
		fn_out = fopen(argv[1], "w");
		if (!fn_out)
        {
			fprintf(stderr, "could not open %s for writing\n", argv[1]);
			return -1;
		}
	}
	else
		fn_out = stdout;
    
	int k = 25;
    
	DeBruijn* G = new DeBruijn(k);
   // DeBruijn* M = new DeBruijn(k);
    
    //create a graph for each data file
    DeBruijn::myDBgraph * dbgraph1 = G->parsefile("compare.txt");
    DeBruijn::myDBgraph * dbgraph2 = G->parsefile("parser.txt");
    DeBruijn::myDBgraph * dbgraph3 = G->parsefile("roadkill.txt");
    
    //create a graph for each data file
    DeBruijn::myDBgraph * dbgraphm1 = G->parsefile("compare2.txt");
    DeBruijn::myDBgraph * dbgraphm2 = G->parsefile("parser2.txt");
    DeBruijn::myDBgraph * dbgraphm3 = G->parsefile("roadkill2.txt");
    
    
    //create a combined dbgraph for sample 1
    DeBruijn::myDBgraph * dbmix = G->combinegraphs(dbgraph2, dbgraph1, 1);
    G->combinegraphs(dbmix, dbgraph3, 2);
    
    //create a combined dbgraph for sample 2
    DeBruijn::myDBgraph * dbmixm = G->combinegraphs(dbgraphm2, dbgraphm1, 1);
    G->combinegraphs(dbmixm, dbgraphm3, 2);
    
    //create a combined graph for the 2 samples
    G->combinegraphs(dbmixm, dbmix, 4);
    
}