#include <iostream>
#include "input_data_readers.h"
#include <string>
#include <list>
using namespace std;

int main() {
    cout << ReadReferentGenome("./ecoli.fasta") << endl;
    list<string> sequences = ReadMutatedGenomeSequences("./ecoli_simulated_reads.fasta");
    list<string>::iterator it;
    int i=1;
    for(it=sequences.begin();it!=sequences.end();it++){
        cout << i <<". "<< *it << endl;
        i++;
    }

    return 0;
}