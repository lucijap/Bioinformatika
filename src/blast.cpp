#include "blast.h"
#include <string>
#include <map>
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printAllKLengthRec(char set[], string prefix,list<string>*result ,int n, int k){

    if (k == 0)
    {
        result->push_back(prefix);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        string newPrefix;

        newPrefix = prefix + set[i];

        printAllKLengthRec(set, newPrefix,result, n, k - 1);
    }

}

list<string> getAllKLength(char set[], int k,int n){
    list<string> result;
    printAllKLengthRec(set, "", &result,n, k);
    return result;
}

list<string> Blast(map<string,list<int>>* reference_kmers, map<string, list<int>>* seq_kmers,int k){
    /*
    int thresh = 7;
    char bases [4]= {'A','C','G','T'};

    for(unsigned int i=0;i<sequence.size()-k;i++){
        string k_mer=sequence.substr(i,(unsigned int)k);

        for(auto const&k_mer1:all_kmers){
            int sum = 0;
            for(unsigned int j=0;j<k;j++){
                if (k_mer.at(j) == k_mer1.at(j)) {
                    sum += 1;
                }
            }
            if (sum>=thresh){
                kmers_to_compare.push_back(k_mer1);
            }
        }
    }
     */

    list<string> hit_list;

    // generate list of keys in reference_kmers
    vector<string> keys;
    keys.reserve(reference_kmers->size());
    for(auto const&it:*reference_kmers){
        keys.push_back(it.first);
    }

    // generate list of hits
    for(auto const&k_mer:*seq_kmers){
        if(count(keys.begin(),keys.end(),k_mer.first)>0){
            hit_list.push_back(k_mer.first);
        }
    }
    return hit_list;
}

