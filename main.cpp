#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

// defining each node for graph
struct Node {
    int id;
    vector<int> neighbors;
};
