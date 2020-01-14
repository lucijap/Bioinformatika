#include <string>
#include <map>
#include <list>
#include <iostream>
#include <vector>
using namespace std;
#ifndef MUTATIONDETECTION_HIT_MAPPER_H
#define MUTATIONDETECTION_HIT_MAPPER_H

/**
 *Counts the number of hits for every region, chooses the region with the most hits
 * @param hit_list: list of shared k-mers in sequence and reference
 * @param reference_kmers: reference k-mers
 * @param reference_size: size of the reference genome
 * @param sequence_size: size of the mutated genome read
 * @param k: size of k-mer
 * @return pair containing start and length of region with the most hits
 */


pair<int,int> MapHits(vector<string>* hit_list,map<string,list<int>>* reference_kmers,int reference_size,int sequence_size,int k);
#endif //MUTATIONDETECTION_HIT_MAPPER_H