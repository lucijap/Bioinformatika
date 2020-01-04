#include <string>
#include <list>
#include <map>
#ifndef MUTATIONDETECTION_K_MER_INDEX_ALIGNMENT_H
#define MUTATIONDETECTION_K_MER_INDEX_ALIGNMENT_H

#endif //MUTATIONDETECTION_K_MER_INDEX_ALIGNMENT_H
using namespace std;

/**
 * Generates a map of k-mers and their indices for a given sequence.
 * To reduce storage space, k-mers that are stored are minimizers of a certain window.
 * @param sequence: sequence from which k-mers are generated
 * @param w: window size
 * @param k: k-mer size
 * @return: map where each pair contains a k-mer string and the index of the k-mer in the original sequence
 */
map<string,list<int>>generate_k_mers(string* sequence,int w,int k);