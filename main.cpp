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


// reading the graph from the file
vector<Node> readGraphFromFile(const string& filename) {
    vector<Node> graph;
    ifstream file(filename);

    // check if the file can be open safely
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        // return empty graph
        return graph;
    }

    // reading the file 
    int numNodes, numEdges;
    file >> numNodes >> numEdges;

    // resize the graph vector to work much faster with memory
    graph.resize(numNodes);

    // initialize the graph
    // this is used when a node doesn't have any neighbors
    // if this doesn't run, the nodes with no edge would be printed 0
    for(int i = 0; i < numNodes; i++)
        graph[i].id = i; 
    

    // loading the graph
    int node1, node2;
    while (file >> node1 >> node2) {
        graph[node1].id = node1;
        graph[node1].neighbors.push_back(node2);
    }

    file.close();
    return graph;
}

// show the graph
void printGraph(const vector<Node>& graph) 
{
    for (const Node& node : graph) 
    {
        cout << "Node " << node.id << ": ";
        for (int neighbor : node.neighbors) 
        {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}


///////////////////////////////
////////// DFS ////////////////

/// recursive
void recursiveDFS(const vector<Node>& graph, int node, vector<bool>& visited) {
    visited[node] = true;
    cout << node << " ";

    for (int neighbor : graph[node].neighbors) {
        if (!visited[neighbor]) {
            recursiveDFS(graph, neighbor, visited);
        }
    }
}

void recursiveDFS(const vector<Node>& graph, int startNode) {
    vector<bool> visited(graph.size(), false);
    recursiveDFS(graph, startNode, visited);
    cout << endl;
}

