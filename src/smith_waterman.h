#include <string>
#include <list>
using namespace std;
#ifndef SRC_SMITH_WATERMAN_H
#define SRC_SMITH_WATERMAN_H


list<tuple<char,int,char>> SmithWaterman(string sequence_A, string sequence_B, int region_start);

#endif //SRC_SMITH_WATERMAN_H
