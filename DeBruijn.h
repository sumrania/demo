//
//  DeBruijn.h
//  demo
//
//  Created by Shefali Umrania on 1/5/13.
//  Copyright (c) 2013 Shefali Umrania. All rights reserved.
//

#ifndef __demo__DeBruijn__
#define __demo__DeBruijn__

#include <stdio.h>
#include "utils.h"
#include <map>
using std::map;
#include <string>
using namespace std;

struct Node
{
    vector<int> nodeprev;
    vector<int> prev_cnt;
    vector<int> nodenext;
    vector<int> next_cnt;
    string node_kmer;
    
    Node() : nodeprev(0), prev_cnt(0), nodenext(0), next_cnt(0), node_kmer() {}
    Node(vector<int> nodeprev2, vector<int> prev_cnt2, vector<int> nodenext2, vector<int> next_cnt2, string node_kmer2)
    : nodeprev(nodeprev2), prev_cnt(prev_cnt2), nodenext(nodenext2), next_cnt(next_cnt2), node_kmer(node_kmer2) {}
    
};


struct Cnode
{
    typedef map<char, vector<int> > next_t;
    next_t nextmap;
    typedef map<char, vector<int> > prev_t;
    prev_t prevmap;
    
    Cnode() : nextmap(), prevmap() {}
    Cnode(const map<char, vector<int> > & nextmap2, const map<char, vector<int> >& prevmap2) : nextmap(nextmap2), prevmap(prevmap2) {}
    
};

class DeBruijn
{
  
public:
    
    int k;
    typedef map<int, Node*> myGraph;
    typedef map<string, Cnode*> myDBgraph;
    typedef map<char, vector<int> > next_t;
    typedef map<char, vector<int> > prev_t;
    DeBruijn::myGraph graph;
    DeBruijn::myDBgraph dbgraph;
    DeBruijn::next_t nextmap;
    DeBruijn::prev_t prevmap;
    
    DeBruijn(int k){this->k = k;};	
    
    myDBgraph* parsefile(string filename2);
    myDBgraph * combinegraphs(myDBgraph * dbgraph1, myDBgraph * dbgraph2, unsigned int num_samples);

private:

};
#endif
