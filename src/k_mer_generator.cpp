#include "k_mer_generator.h"
#include <string>
#include <list>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

map<string,list<int>> GenerateKmers(string* sequence,int w, int k){

    map<string,list<int>> k_mers;
    list<string> current_window;
    list<string>::iterator min_kmer_iter;
    string min_kmer;

    // fill first window
    for(int i=0;i<w;i++){
        current_window.push_back(sequence->substr(i,k));
    }

    // slide window along sequence
    for(int i=w;i<sequence->size()-k;i++){
        if(i!=w){
            current_window.pop_front();
        }
        current_window.push_back(sequence->substr(i,k));

        // find minimal k-mer in current window and add it to k_mers
        min_kmer_iter = min_element(current_window.begin(),current_window.end());
        if(min_kmer != *min_kmer_iter ){
            if(k_mers.count(*min_kmer_iter)==0){
                k_mers.insert(pair<string,list<int>>(*min_kmer_iter,{i-w+distance(current_window.begin(), min_kmer_iter)}));
            }else{
                auto iter = k_mers.find(*min_kmer_iter);
                (*iter).second.push_back(i-w+distance(current_window.begin(), min_kmer_iter));
            }
            min_kmer = *min_kmer_iter;
        }
    }
    return k_mers;
}

