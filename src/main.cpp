#include <iostream>
#include "input_data_readers.h"
#include <string>
#include <list>
#include "smith_waterman.h"
#include "k_mer_generator.h"
#include "blast.h"
#include "hit_mapper.h"

using namespace std;

int main() {
    int w = 1;
    int k = 3;
    string reference = ReadReferentGenome("../train-data/nas");
    //cout << "done with read" << endl;
    map<string, list<int>> kmers = GenerateKmers(&reference, w, k);

    //cout << "done with gen kmers" << endl;
    list<string> sequences = ReadMutatedGenomeSequences("../train-data/nas_mutated");

    //auto it = sequences.begin();
    //advance(it,1);
    //string sequence = *it;
    string sequence = sequences.front();
    map<string, list<int>> seq_kmers = GenerateKmers(&sequence, w, k);
    /*
    for (auto el2 : seq_kmers) {
        cout << el2.first << endl;
        for (auto el3 : el2.second) {
            cout << el3 << "-" << endl;
        }
    }
    */

    list<string> hit_list = Blast(&kmers, &seq_kmers, k);
    //cout << "done with blast" << endl;
    seq_kmers.erase(seq_kmers.begin(), seq_kmers.end());
    pair<int,int> region = MapHits(&hit_list, &kmers, reference.size(), sequence.size(), k);
    //cout << "done with map hit" << endl;

    hit_list.clear();
    string hit_region = reference.substr(region.first, region.second);
    cout << hit_region << endl;
    pair<string, string> result = SmithWaterman(hit_region, sequence, region.first);
    //cout << "done with smith" << endl;
    cout << result.first << endl;
    cout << result.second << endl;

    /*
    for(auto elem : words) {
        cout << elem.first << endl;
        for (auto el2 : elem.second) {
            cout << el2 + 1 << " ";
        }
        cout << endl;
    }

    pair<string, string> sequences = SmithWaterman("GGTTGACTA", "TGTTACGG");
    cout << sequences.first << endl;
    cout << sequences.second << endl;

    char sequence[12] = "GGTTGGTACTA";

    map<string,list<int>> words = GenerateKmers(sequence, 0, 3);
    for(auto elem : words) {
        cout << elem.first << endl;
        for (auto el2 : elem.second) {
            cout << el2 << " ";
        }
        cout << endl;
    }
    cout << ReadReferentGenome("../train-data/ecoli.fasta") << endl;
    list<string> sequences = ReadMutatedGenomeSequences("../train-data/ecoli_simulated_reads.fasta");
    list<string>::iterator it;
    int i=1;
    for(it=sequences.begin();it!=sequences.end();it++){
        cout << i <<". "<< *it << endl;
        i++;
    }

    return 0;
     */
}