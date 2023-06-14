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


////// non-recursive
void nonRecursiveDFS(const vector<Node>& graph, int startNode) {
    vector<bool> visited(graph.size(), false);
    stack<int> nodeStack;
    nodeStack.push(startNode);

    while (!nodeStack.empty()) {
        int node = nodeStack.top();
        nodeStack.pop();

        if (!visited[node]) {
            visited[node] = true;
            cout << node << " ";

            for (int neighbor : graph[node].neighbors) {
                if (!visited[neighbor]) {
                    nodeStack.push(neighbor);
                }
            }
        }
    }
    cout << endl;
}


////////////// BFS /////////////
////// recursive
void recursiveBFSUtil(const vector<Node>& graph, queue<int>& nodeQueue, vector<bool>& visited) {
    if (nodeQueue.empty())
        return;

    int node = nodeQueue.front();
    nodeQueue.pop();
    cout << node << " ";

    for (int neighbor : graph[node].neighbors) {
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            nodeQueue.push(neighbor);
        }
    }

    recursiveBFSUtil(graph, nodeQueue, visited);
}

void recursiveBFS(const vector<Node>& graph, int startNode) {
    vector<bool> visited(graph.size(), false);
    queue<int> nodeQueue;
    nodeQueue.push(startNode);
    visited[startNode] = true;

    recursiveBFSUtil(graph, nodeQueue, visited);

    cout << endl;
}


////// non recursive
void nonRecursiveBFS(const vector<Node>& graph, int startNode) {
    vector<bool> visited(graph.size(), false);
    queue<int> nodeQueue;
    nodeQueue.push(startNode);
    visited[startNode] = true;

    while (!nodeQueue.empty()) {
        int node = nodeQueue.front();
        nodeQueue.pop();
        cout << node << " ";

        for (int neighbor : graph[node].neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                nodeQueue.push(neighbor);
            }
        }
    }
    cout << endl;
}


/////////////////////////////////
//////// Topological order
void topologicalDFS(const vector<Node>& graph, int node, vector<bool>& visited, stack<int>& order) {
    visited[node] = true;

    for (int neighbor : graph[node].neighbors) {
        if (!visited[neighbor]) {
            topologicalDFS(graph, neighbor, visited, order);
        }
    }

    order.push(node);
}

vector<int> topologicalOrder(const vector<Node>& graph) {
    vector<bool> visited(graph.size(), false);
    stack<int> order;

    for (const Node& node : graph) {
        if (!visited[node.id]) {
            topologicalDFS(graph, node.id, visited, order);
        }
    }

    vector<int> topological;

    while (!order.empty()) {
        topological.push_back(order.top());
        order.pop();
    }

    return topological;
}
