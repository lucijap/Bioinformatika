#include "blast.h"
#include <string>
#include <map>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;



vector<string> Blast(vector<string>* reference_kmers, map<string, list<int>>* seq_kmers,int k){

    //generate list of keys in sequence

    vector<string> seq_keys;
    for(auto const&k_mer:*seq_kmers){
        seq_keys.push_back(k_mer.first);
    }

    //generate hit_list

    vector<string> hit_list;
    set_intersection(reference_kmers->begin(), reference_kmers->end(), seq_keys.begin(), seq_keys.end(), inserter(hit_list,  hit_list.begin()));
    return hit_list;
}

