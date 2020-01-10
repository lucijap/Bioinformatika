#include <string>
#include <map>
#include <list>
#include <iostream>
using namespace std;

#ifndef MUTATIONDETECTION_BLAST_H
#define MUTATIONDETECTION_BLAST_H

#endif //MUTATIONDETECTION_BLAST_H

list<string> Blast(map<string,list<int>>* reference_kmers, map<string, list<int>>* seq_kmers, int k);
