#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

typedef struct {
    int n, m, cIndex;
    vector<int> c;
} board;

board create_board() {
    int n, m;
    cin >> n >> m;
    board b = {n, m, n-1, vector<int>(n, 0)};
    for (int i = 0; i < n; i++) {
        cin >> b.c[i];
    }
    return b;
}

bool isEmpty(board b) {
    for (int i = 0; i < b.n; i++) {
        if (b.c[i] > 0) {
            return false;
        }
    }
    return true;
}

int getcIndex(board b) {
    int maxC = b.c[0];
    for (int i = 0; i < b.n; i++) {
        if (maxC <= b.c[i]) {
            maxC = b.c[i];
            b.cIndex = i;
        }
    }
    return b.cIndex;
}

int getMaxSquareSide(board b) {
    int maxSide = 1, cIndex = getcIndex(b);
    for (int i = cIndex; i >= 0; i--) {
        if (maxSide == b.c[cIndex]) {
            break;
        }
        if (b.c[i] == 0) {
            maxSide = 0;    
            break;
        }
        if (i == 0) {
            break;
        }
        if (b.c[i] - b.c[i-1] == 0) {
            maxSide++;
        } else {
            break;
        }
    }
    return maxSide;
}

board deleteSquare(board b, int max) {
    for (int i = b.cIndex; i >= b.cIndex - max + 1; i--) {
        b.c[i] -= max;
    }
    b.cIndex = getcIndex(b);
    return b;
}

board createCopy(board b) {
    board copy = {b.n, b.m, b.cIndex, vector<int>(b.n, 0)};
    for (int i = 0; i < b.n; i++) {
        copy.c[i] = b.c[i];
    }
    return copy;
}

namespace std {
  template <>
  struct hash<vector<int>> {
    size_t operator()(const vector<int>& v) const {
        size_t hash= v.size();
        for(int i : v) {
            hash ^= i + (hash<<2);  
        }
        return hash;
    }
  };
}

bool operator==(const vector<int>& v1, const vector<int>& v2) {
    if (v1.size() != v2.size()) {
        return false;
    }
    for (long unsigned int i = 0; i < v1.size(); i++) {
        if (v1[i] != v2[i]) {
            return false;
        }
    }
    return true;
}
 
unsigned long int getCombinations(board b, unordered_map<vector<int>, unsigned long int> &memo) {
    int max;
    long int result = 0;
    if (isEmpty(b)) {
        return 1;
    }
    if (memo.find(b.c) != memo.end()) {
        return memo[b.c];
    }
    max = getMaxSquareSide(b);
    for (int i = 1; i <= max; i++) {
        board copy = createCopy(b);
        copy.cIndex = getcIndex(copy);
        copy = deleteSquare(copy, i);   
        result += getCombinations(copy, memo);
    }
    memo[b.c] = result;
    return result;
}

int main() {
    board b = create_board();
    if (isEmpty(b)) {
        cout << 0 << endl;
        return 0;
    }
    unordered_map<vector<int>, unsigned long int> memo;
    cout << getCombinations(b, memo) << endl;
    return 0;
}
