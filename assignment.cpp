#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        // Build the graph as adjacency list
        vector<vector<int>> graph(n);
        for (auto& conn : connections) {
            graph[conn[0]].push_back(conn[1]);
            graph[conn[1]].push_back(conn[0]);
        }
        
        // Initialize the disc and low vectors to -1, indicate that no node is there
        vector<int> disc(n, -1);
        vector<int> low(n, -1);
        
        // Initialize an empty vector to store the critical connections
        vector<vector<int>> bridges;
        
        // Initialize the time variable to 0
        int time = 0;
        
        // Define the DFS function using a lambda expression
        function<void(int, int)> dfs = [&](int node, int parent) {
            // Assigning the discovery time and low value of the current node
            disc[node] = time;
            low[node] = time;
            time++;
            
            // Recursively visit all the neighbors of the current node, skipping the parent node
            for (int neighbor : graph[node]) {
                if (neighbor == parent) continue;
                
                if (disc[neighbor] == -1) {
                    // If the neighbor has not been discovered yet, visit it and update the low value of the current node
                    dfs(neighbor, node);
                    low[node] = min(low[node], low[neighbor]);
                    
                    // If the low value of the neighbor is greater than the discovery time of the current node,
                    // then the edge connecting the current node to the neighbor is a bridge, and it is added to the bridges vector
                    if (low[neighbor] > disc[node]) {
                        bridges.push_back({node, neighbor});
                    }
                } else {
                    // If the neighbor has already been discovered, update the low value of the current node
                    low[node] = min(low[node], disc[neighbor]);
                }
            }
        };
        
        // Call the DFS function on any node that has not been discovered yet
        for (int i = 0; i < n; i++) {
            if (disc[i] == -1) {
                dfs(i, -1);
            }
        }
        
        // Return the bridges vector, which contains all the critical connections in the graph
        return bridges;
    }
};

int main() {
    int n = 4;
    vector<vector<int>> connections =  {{0,1},{1,2},{2,0},{1,3}};
    Solution s;
    vector<vector<int>> bridges = s.criticalConnections(n, connections);
    cout<<"[";
    for (auto& bridge : bridges) {
        cout << "["<<bridge[0] << "," << bridge[1] <<"]";
    }
    cout<<"]";
    return 0;
}
