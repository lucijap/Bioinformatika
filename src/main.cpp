#include <iostream>
#include "input_data_readers.h"
#include <string>
#include <list>
#include "smith_waterman.h"
#include "k_mer_generator.h"
#include "blast.h"
#include "hit_mapper.h"
#include <algorithm>
#include <fstream>

using namespace std;

int main() {

    int w = 5;
    int k = 11;
    // reading input files
    string reference = ReadReferentGenome("../train-data/lambda.fasta");
    list<string> sequences = ReadMutatedGenomeSequences("../train-data/lambda_simulated_reads.fasta");

    //cout << "done with read" << endl;

    // generating k-mers for reference
    map<string, list<int>> kmers = GenerateKmers(&reference, w, k);

    //cout << "done with gen kmers" << endl;

    // get vector of k-mers without index lists
    vector<string> keys;
    keys.reserve(kmers.size());
    for(auto const&itt:kmers){
        keys.push_back(itt.first);
    }

    sort(keys.begin(), keys.end());

    // detecting mutations
    int i = 0;
    for (auto const& it :sequences) {
        string sequence = it;

        // generate k-mers of read sequence
        map<string, list<int>> seq_kmers = GenerateKmers(&sequence, w, k);

        // generates hit_list of k-mers
        vector<string> hit_list = Blast(&keys, &seq_kmers, k);

        //cout << "done with hit list" << endl;

        seq_kmers.erase(seq_kmers.begin(), seq_kmers.end());

        // finds mapping regions
        pair<int,int> region = MapHits(&hit_list, &kmers, reference.size(), sequence.size(), k);
        if (region.second==0){
            continue;
        }
        //cout << "done with map hit" << endl;

        hit_list.clear();
        string hit_region = reference.substr(region.first, region.second);

        // local alignment with Smith Waterman and writing mutations to csv file
        SmithWaterman(hit_region, sequence, region.first);

        //cout << "done with smith" << endl;
        i++;
        if (i%10==0){
            cout<<"--------------------------"<<i<<"---------------------"<<endl;
        }


    }



}