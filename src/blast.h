#include <string>
#include <map>
#include <list>
#include <iostream>
#include <vector>
using namespace std;

#ifndef MUTATIONDETECTION_BLAST_H
#define MUTATIONDETECTION_BLAST_H

//
// Created by Marko Meštrović.
//

/**
 * Generates a list of k-mers that appear in both reference_kmers and seq_kmers (hits)
 * @param reference_kmers: k-mers generated from the reference genome
 * @param seq_kmers: k-mers generated from the mutated genome read
 * @param k: size of k-mer
 * @return returns list of hits
 */
vector<string> Blast(vector<string>* reference_kmers, map<string, list<int>>* seq_kmers,int k);

#endif //MUTATIONDETECTION_BLAST_H
