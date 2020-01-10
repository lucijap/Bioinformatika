#include "smith_waterman.h"
#include <string>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

int SimilarityScore(char a, char b) {
  if (a == b) {
      return 3;
  } else {
      return -5;
  }
}

pair<string, string> SmithWaterman(string sequence_A, string sequence_B) {
    int dim_A = sequence_A.length();
    int dim_B = sequence_B.length();
    const int penalty = 4;

    map<pair<int, int>, pair<int, int>> traceback;

    int scoring_matrix[dim_A + 1][dim_B + 1];

    for (int i = 0; i < dim_A + 1; i++) {
        scoring_matrix[i][0] = 0;
    }

    for (int i = 0; i < dim_B + 1; i++) {
        scoring_matrix[0][i] = 0;
    }

    int match = 0, insertion = 0, deletion = 0, maximum_value;
    for (int i = 1; i < dim_A + 1; i++) {
        for (int j = 1; j < dim_B + 1; j++) {
            match = scoring_matrix[i - 1][j - 1] + SimilarityScore(sequence_A[i - 1], sequence_B[j - 1]);
            insertion = scoring_matrix[i][j - 1] - penalty;
            deletion = scoring_matrix[i - 1][j] - penalty;
            maximum_value = max({0, match, insertion, deletion});
            scoring_matrix[i][j] = maximum_value;
            if (maximum_value == match) {
                traceback.insert({pair<int, int> (i, j), pair<int, int> (i - 1, j - 1)});
            } else if (maximum_value == insertion) {
                traceback.insert({pair<int, int> (i, j), pair<int, int> (i, j - 1)});
            } else if (maximum_value == deletion) {
                traceback.insert({pair<int, int> (i, j), pair<int, int> (i - 1, j)});
            }
        }
    }

    pair<int, int> max_pair(0, 0);
    int max_value = 0;
    for (int i = 1; i < dim_A + 1; i++) {
        for (int j = 1; j < dim_B + 1; j++) {
            if (scoring_matrix[i][j] > max_value) {
                max_value = scoring_matrix[i][j];
                max_pair = pair<int, int> (i, j);
            }
        }
    }

    string first;
    string second;
    while (traceback.count(max_pair)) {
        pair<int, int> next_pair = traceback.at(max_pair);
        if (next_pair.first == max_pair.first - 1 and next_pair.second == max_pair.second - 1) {
            first += sequence_A[next_pair.first];
            second += sequence_B[next_pair.second];
        } else if (next_pair.first == max_pair.first - 1 and next_pair.second == max_pair.second) {
            first += sequence_A[next_pair.first];
            second += "-";
        } else if (next_pair.first == max_pair.first and next_pair.second == max_pair.second - 1) {
            first += "-";
            second += sequence_B[next_pair.second];
        }
        max_pair = next_pair;
    }

    reverse(first.begin(), first.end());
    reverse(second.begin(), second.end());

    /*
    cout << first << endl;
    cout << second << endl;

    cout << "\t\t";
    for (int i = 0; i < dim_B; i++) {
        cout << sequence_B[i] << "\t";
    }

    cout << endl;

    for (int i = 0; i < dim_A + 1; i++) {
        if (i > 0) {
            cout << sequence_A[i - 1] << "\t";
        } else {
            cout << "\t";
        }
        for (int j = 0; j < dim_B + 1; j++) {
            cout << scoring_matrix[i][j] << "\t";
        }
        cout << endl;
    }
    */
    return pair<string, string> (first, second);

}
