#include "minimap.h"
#include <cmath>
#include <set>

using namespace std;

unsigned int InvertibleHash(unsigned int x, int p) {
    unsigned int m = (unsigned int) pow(2, p) - 1;
    x = (~x + (x << 21u)) & m;
    x = x ^ x >> 14u;
    x = (x + (x << 2u) + (x << 4u)) & m;
    x = x ^ x >> 28u;
    x = (x + (x << 31u)) & m;
    return x;
}

int NucleotideHash(char c) {
    switch (c) {
        case 'A':
            return 0;
        case 'C':
            return 1;
        case 'G':
            return 2;
        case 'T':
            return 3;
        default:
            throw invalid_argument("Non nucleotide letter encountered");
    }
}

unsigned int KmerHash(string s, int k) {
    int hash_sum = 0;
    for (int i = k - 1; i >= 0; i++) {
        hash_sum += NucleotideHash(s.at(i)) * (int) pow(4, i);
    }
    return InvertibleHash(hash_sum, 2*k);
}

string SequenceComplement(string* s) {
    string complement;
    for (char& c : *s) {
        switch (c) {
            case 'A':
                complement += "T";
                break;
            case 'C':
                complement += "G";
                break;
            case 'G':
                complement += "C";
                break;
            case 'T':
                complement += "A";
                break;
            default:
                throw invalid_argument("Non nucleotide letter encountered");
        }
    }
    return complement;
}

set<tuple<int, int, int>> MinimizerSketch(string* s, int w, int k) {
    set<tuple<int, int, int>> Mu;
    unsigned int u, v, m;
    string sc = SequenceComplement(s);
    for (int i = 1; i <= s->length() - w - k + 1; i++) {
        m = 2147483647;
        for (int j = 0; j <= w - 1; j++) {
            u = KmerHash(s->substr(i + j, k), k);
            v = KmerHash(sc.substr(i + j, k), k);
            if (u != v) {
                m =  min(m, min(u, v));
            }
        }
        for (int j = 0; j <= w - 1; j++) {
            u = KmerHash(s->substr(i + j, k), k);
            v = KmerHash(sc.substr(i + j, k), k);
            if (u < v && u == m) {
                Mu.insert(tuple<int, int, int> (m, i + j, 0));
            } else if (v < u && v == m) {
                Mu.insert(tuple<int, int, int> (m, i + j, 1));
            }
        }
    }
    return Mu;
}