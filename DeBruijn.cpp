//
//  DeBruijn.cpp
//  demo
//
//  Created by Shefali Umrania on 1/5/13.
//  Copyright (c) 2013 Shefali Umrania. All rights reserved.
//
#include <numeric>
using namespace std;
#include <iterator>
using namespace std;
#include <functional>
#include <iostream>
using namespace std;
#include "DeBruijn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "assert.h"
using std::string;
#include <map>
using std::map;
#include <vector>
using std::vector;
#include <algorithm>
using std::reverse;
#include <fstream>
#include <stdio.h>
#include <cstdlib>
using namespace std;


//creates a map with only the parsed data
DeBruijn::myDBgraph* DeBruijn::parsefile(string filename)
{
    DeBruijn::myGraph graph;
    DeBruijn::myDBgraph* dbgraph = new DeBruijn::myDBgraph;
    DeBruijn::next_t nextmap;
    DeBruijn::prev_t prevmap;
    
    string id, prev, wt, num, kmer;
    string word;
    std::ifstream infile(filename.c_str());
    
        if (infile.is_open())
        {
            infile >>word>>word;
    
            while ( infile >> word)
            {
                id = word;
                infile >> word;
                
                prev = word;
                infile >> word;
                
                wt = word;
                infile >> word;
                
                kmer = word;
            	
                //converts string to integer
                int cid = atoi(id.c_str());
                
                //creates a new node
                Node* n = graph[cid];
                if (!n)
                {
                    n = new Node;
                    graph[cid] = n;
                }
            
                if (atoi(prev.c_str())>=0)
                {
                    n->nodeprev.push_back(atoi(prev.c_str()));
                    n->prev_cnt.push_back(atoi(wt.c_str()));
                }
    
                n->node_kmer = kmer;
           
                infile >>word;
                num = word;
            }
        }
    
    //adding bidirectional connections on graph map
    myGraph::iterator it;
    for (it = graph.begin(); it != graph.end(); it++)
    {
        Node* n = (*it).second;
        for (int i=0; i< (int) n->nodeprev.size(); i++)
        {
            int prev_id = n->nodeprev[i];
            Node* pn = graph[prev_id];
            if (!pn)
            {
                printf("Error!!! Check your data for non existent prev id => id: %i, prev id:%i, %s\n", (*it).first, prev_id, n->node_kmer.c_str());
				exit(1);
                
            }       
            pn->nodenext.push_back((*it).first);
            pn->next_cnt.push_back(n->prev_cnt[i]);
        }
    }
    
    //populate dbgraph
    for (myGraph::const_iterator j = graph.begin(); j != graph.end(); ++j)
    {
        string kmer = (*j).second->node_kmer;
        
        //If node with kmer node_kmer does not exist
        Cnode* n = (*dbgraph)[kmer];
        if(! n)
        {
            n = new Cnode();
            (*dbgraph)[kmer] = n;
        }
        
        
        //populating prev map with char and weighted ints
        for (int m=0; m< (int) (*j).second->nodeprev.size(); m++)
        {
            vector<int> prevwt_vec;
            //creates new node np by using vector nodeprev
            Node* np = graph[(*j).second->nodeprev[m]];
            
            if (! np)
            {
                np = new Node();
                graph[(*j).second->nodeprev[m]] = np;
            }
            assert(np);
            //finds the first char of the kmer of nodeprev
            char cp = np->node_kmer[0];
 
            //put all weights in a vector
            int wt =  (*j).second->prev_cnt[m];
            prevwt_vec.insert(prevwt_vec.begin(), wt);
            
            //puts char as key and weighted int as value in prevmap
            n->prevmap[cp] = prevwt_vec;
        }
        
        
        //populating next map with char and weighted ints
        for (int p=0; p< (int) (*j).second->nodenext.size(); ++p)
        {
            vector<int> nextwt_vec;
            //creates new node nn by using vector nodenext
            Node* nn = graph[(*j).second->nodenext[p]];
            
            if (! nn)
            {
                nn = new Node();
                graph[(*j).second->nodenext[p]] = nn;
            }
            assert(nn);

            //finds the last char of the kmer of nodenext
            char cn = nn->node_kmer[nn->node_kmer.length() - 1];

            //add wt ints to the vector
            int wt = (*j).second->next_cnt[p];
            nextwt_vec.insert(nextwt_vec.begin(), wt);
                                                       
            //puts char as key and weighted int as value in nextmap
            n->nextmap[cn] = nextwt_vec;
        }
    
    }
    

    //printing the dbgraph
 /*   myDBgraph::iterator iter;
    for (iter = dbgraph->begin(); iter != dbgraph->end(); iter++)
    {
        map<char, vector<int> > next_map = (*iter).second->nextmap;
        map<char, vector<int> > prev_map = (*iter).second->prevmap;
        
        printf("%s\t", (*iter).first.c_str());
        
        for (map<char, vector<int> >::iterator ii = next_map.begin(); ii != next_map.end(); ++ii)
        {
            printf("n:%c ", ii->first);
            vector<int> next = ii->second;
            
            for (vector<int>::iterator i = next.begin(); i != next.end(); i++)
            {
                printf("vec:%i ", *i);
            }
        
	 }
        for (map<char, vector<int> >::iterator ii = prev_map.begin(); ii != prev_map.end(); ii++)
        {
            printf("p:%c ",ii->first);
            vector<int> prev = ii->second;
            
            for (vector<int>::iterator i = prev.begin(); i != prev.end(); i++)
            {
                printf("vec:%i ", *i);
            }
                
        }
    
	printf("\n");
    }*/
    return dbgraph;
}

//combine 2 graphs to create one graph

DeBruijn::myDBgraph * DeBruijn::combinegraphs(myDBgraph * dbgraph1, myDBgraph * dbgraph2, unsigned int num_samples)
{

}

