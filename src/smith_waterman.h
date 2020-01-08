#include <string>
using namespace std;
#ifndef SRC_SMITH_WATERMAN_H
#define SRC_SMITH_WATERMAN_H


pair<string, string> SmithWaterman(string sequence_A, string sequence_B);
int SimilarityScore(char a, char b);

#endif //SRC_SMITH_WATERMAN_H
