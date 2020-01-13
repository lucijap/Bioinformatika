#include <string>
#include <map>
#include <list>
#include <iostream>
#include <vector>
using namespace std;
#ifndef MUTATIONDETECTION_HIT_MAPPER_H
#define MUTATIONDETECTION_HIT_MAPPER_H




pair<int,int> MapHits(vector<string>* hit_list,map<string,list<int>>* reference_kmers,int reference_size,int sequence_size,int k);
#endif //MUTATIONDETECTION_HIT_MAPPER_H