#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>
using namespace std;

typedef pair<string, int> Edge;
unordered_map<string, vector<Edge>> graph;

// Adds a flight (edge) between cities
void addFlight(string src, string dest, int cost) {
    graph[src].push_back({dest, cost});
    graph[dest].push_back({src, cost}); // Assuming undirected graph
}

// Displays the adjacency list of the graph
void displayGraph() {
    cout << "\nFlight connections (Adjacency List):\n";
    for (auto city : graph) {
        cout << city.first << " -> ";
        for (auto edge : city.second) {
            cout << "(" << edge.first << ", " << edge.second << ") ";
        }
        cout << endl;
    }
}

// Checks if the graph is connected using BFS
bool isConnected(string startCity) {
    if (graph.empty()) return false;

    set<string> visited;
    queue<string> q;

    q.push(startCity);
    visited.insert(startCity);

    while (!q.empty()) {
        string city = q.front();
        q.pop();

        for (auto neighbor : graph[city]) {
            if (visited.find(neighbor.first) == visited.end()) {
                visited.insert(neighbor.first);
                q.push(neighbor.first);
            }
        }
    }

    return visited.size() == graph.size();
}

int main() {
    int choice;
    string src, dest;
    int cost;

    while (true) {
        cout << "\n------ Flight Route System ------\n";
        cout << "1. Add flight\n";
        cout << "2. Display graph\n";
        cout << "3. Check if graph is connected\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter source city: ";
            cin >> src;
            cout << "Enter destination city: ";
            cin >> dest;
            cout << "Enter cost (time/fuel): ";
            cin >> cost;
            addFlight(src, dest, cost);
            cout << "Flight added successfully.\n";
            break;

        case 2:
            displayGraph();
            break;

        case 3:
            if (graph.empty()) {
                cout << "Graph is empty.\n";
                break;
            }
            cout << "Enter a starting city to check connectivity: ";
            cin >> src;
            if (isConnected(src))
                cout << "The graph is CONNECTED.\n";
            else
                cout << "The graph is NOT connected.\n";
            break;

        case 4:
            cout << "Exiting program.\n";
            return 0;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

