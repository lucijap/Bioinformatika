#include "smith_waterman.h"
#include <string>
#include <iostream>
#include <map>
#include <list>
#include <algorithm>
#include <vector>

using namespace std;

short SimilarityScore(char a, char b) {
    if (a == b) {
        return (short) 3;
    } else {
        return (short) -5;
    }
}

list<tuple<char,int,char>> SmithWaterman(string sequence_A, string sequence_B, int region_start) {
    const int dim_A = sequence_A.length();
    const int dim_B = sequence_B.length();
    vector<vector<short>> similarity_matrix(dim_A + 1);
    for (int i = 0; i < dim_A + 1; i++) {
        similarity_matrix[i].resize(dim_B + 1);
    }
    const short penalty = 4;

    vector<vector<short>> traceback(dim_A + 1);
    for (int i = 0; i < dim_A + 1; i++) {
        traceback[i].resize(dim_B + 1);
    }

    int match = 0, insertion = 0, deletion = 0, maximum_value = 0;
    int max_so_far = 0;
    pair<int, int> max_pair;

    // fill out similarity matrix
    for (int i = 1; i < dim_A + 1; i++) {
        for (int j = 1; j < dim_B + 1; j++) {
            match = similarity_matrix[i - 1][j - 1] + SimilarityScore(sequence_A[i - 1], sequence_B[j - 1]);
            insertion = similarity_matrix[i][j - 1] - penalty;
            deletion = similarity_matrix[i - 1][j] - penalty;
            maximum_value = max({0, match, insertion, deletion});
            similarity_matrix[i][j] = (short) maximum_value;
            if (maximum_value != 0) {
                if (maximum_value == match) {
                    traceback[i][j] = 3;
                } else if (maximum_value == insertion) {
                    traceback[i][j] = 2;
                } else if (maximum_value == deletion) {
                    traceback[i][j] = 1;
                }
                // save maximum value in matrix for tra
                if (maximum_value > max_so_far) {
                    max_so_far = maximum_value;
                    max_pair = pair<int, int> (i, j);
                }
            }
        }
    }


    string first;
    string second;
    list<tuple<char,int,char>> list_of_mutations;
    tuple<char,int,char> mutation_tuple;
    int sum;
    char mutation_char;
    char char_of_second;
    pair<int, int> next_pair = {};

    // detect mutations
    while (traceback[max_pair.first][max_pair.second] != 0) {
        // match
        if (traceback[max_pair.first][max_pair.second] == 3) {
            next_pair = {max_pair.first - 1, max_pair.second - 1};
            if (sequence_A[max_pair.first - 1] != sequence_B[max_pair.second - 1]) {
                mutation_char = 'X';
                sum = max_pair.first + region_start-1;
                char_of_second = sequence_B[max_pair.second - 1];
                mutation_tuple = make_tuple(mutation_char, sum, char_of_second);
                list_of_mutations.push_back(mutation_tuple);
            }
            // deletion
        } else if (traceback[max_pair.first][max_pair.second] == 1) {
            next_pair = {max_pair.first - 1, max_pair.second};
            mutation_char ='D';
            sum=max_pair.first+region_start-1;
            char_of_second='-';
            mutation_tuple = make_tuple(mutation_char,sum, char_of_second);
            list_of_mutations.push_back(mutation_tuple);
            // insertion
        } else if (traceback[max_pair.first][max_pair.second] == 2) {
            next_pair = {max_pair.first, max_pair.second - 1};
            mutation_char ='I';
            sum=max_pair.first+region_start-1;
            char_of_second=sequence_B[max_pair.second - 1];
            mutation_tuple = make_tuple(mutation_char,sum, char_of_second);
            list_of_mutations.push_back(mutation_tuple);
        }
        max_pair = {next_pair.first, next_pair.second};
    }


    return list_of_mutations;
}
