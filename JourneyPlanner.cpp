#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

// Use a resizable vector for the adjacency list instead of a fixed-size array.
vector<vector<pair<int, int>>> adj;
#define pb push_back

map<string, int> station_to_id;
map<int, string> id_to_station;
int station_count;
vector<string> station_keys;

void addEdge(string a, string b, int dis) {
    int x = station_to_id[a];
    int y = station_to_id[b];
    adj[x].pb({y, dis});
    adj[y].pb({x, dis});
}

void create_metro_map() {
    station_keys.pb("Noida Sector 62~B");
    station_keys.pb("Botanical Garden~B");
    station_keys.pb("Yamuna Bank~B");
    station_keys.pb("Rajiv Chowk~BY");
    station_keys.pb("Vaishali~B");
    station_keys.pb("Moti Nagar~B");
    station_keys.pb("Janak Puri West~BO");
    station_keys.pb("Dwarka Sector 21~B");
    station_keys.pb("Huda City Center~Y");
    station_keys.pb("Saket~Y");
    station_keys.pb("Vishwavidyalaya~Y");
    station_keys.pb("Chandni Chowk~Y");
    station_keys.pb("New Delhi~YO");
    station_keys.pb("AIIMS~Y");
    station_keys.pb("Shivaji Stadium~O");
    station_keys.pb("DDS Campus~O");
    station_keys.pb("IGI Airport~O");
    station_keys.pb("Rajouri Garden~BP");
    station_keys.pb("Netaji Subhash Place~PR");
    station_keys.pb("Punjabi Bagh West~P");

    station_count = station_keys.size();
    adj.resize(station_count); // Resize the adjacency list to the number of stations

    for (int i = 0; i < station_count; i++) {
        station_to_id[station_keys[i]] = i;
        id_to_station[i] = station_keys[i];
    }

    addEdge("Noida Sector 62~B", "Botanical Garden~B", 8);
    addEdge("Botanical Garden~B", "Yamuna Bank~B", 10);
    addEdge("Yamuna Bank~B", "Vaishali~B", 8);
    addEdge("Yamuna Bank~B", "Rajiv Chowk~BY", 6);
    addEdge("Rajiv Chowk~BY", "Moti Nagar~B", 9);
    addEdge("Moti Nagar~B", "Janak Puri West~BO", 7);
    addEdge("Janak Puri West~BO", "Dwarka Sector 21~B", 6);
    addEdge("Huda City Center~Y", "Saket~Y", 15);
    addEdge("Saket~Y", "AIIMS~Y", 6);
    addEdge("AIIMS~Y", "Rajiv Chowk~BY", 7);
    addEdge("Rajiv Chowk~BY", "New Delhi~YO", 1);
    addEdge("New Delhi~YO", "Chandni Chowk~Y", 2);
    addEdge("Chandni Chowk~Y", "Vishwavidyalaya~Y", 5);
    addEdge("New Delhi~YO", "Shivaji Stadium~O", 2);
    addEdge("Shivaji Stadium~O", "DDS Campus~O", 7);
    addEdge("DDS Campus~O", "IGI Airport~O", 8);
    addEdge("Moti Nagar~B", "Rajouri Garden~BP", 2);
    addEdge("Punjabi Bagh West~P", "Rajouri Garden~BP", 2);
    addEdge("Punjabi Bagh West~P", "Netaji Subhash Place~PR", 3);
}

void display_stations() {
    cout << "\n--- Stations List ---\n";
    for (int i = 0; i < station_count; i++) {
        cout << i + 1 << ". " << station_keys[i] << endl;
    }
    cout << "---------------------\n";
}

void display_map() {
    cout << "\n--- Metro Map Connections ---\n";
    for (int i = 0; i < station_count; ++i) {
        cout << id_to_station[i] << " is connected to:\n";
        for (auto const& [neighbor, dist] : adj[i]) {
            cout << "\t- " << id_to_station[neighbor] << " (" << dist << " km)\n";
        }
    }
    cout << "---------------------------\n";
}

// Corrected Dijkstra's algorithm
int get_shortest_distance(int src, int dest) {
    vector<int> dist(station_count, INT_MAX);
    dist[src] = 0;
    // Priority queue must store {distance, node} to sort by distance.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int u_dist = pq.top().first;
        int u_node = pq.top().second;
        pq.pop();
        
        // Optimization: if we've found a shorter path already, skip.
        if (u_dist > dist[u_node]) {
            continue;
        }

        for (auto& edge : adj[u_node]) {
            int v_node = edge.first;
            int weight = edge.second;
            if (dist[v_node] > dist[u_node] + weight) {
                dist[v_node] = dist[u_node] + weight;
                pq.push({dist[v_node], v_node});
            }
        }
    }
    return dist[dest];
}

// Correct function to print the shortest path using Dijkstra's
void print_shortest_path(int src, int dest) {
    vector<int> dist(station_count, INT_MAX);
    vector<int> parent(station_count, -1);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int u_dist = pq.top().first;
        int u_node = pq.top().second;
        pq.pop();

        if (u_node == dest) break; // Optimization: stop when destination is reached

        if (u_dist > dist[u_node]) {
            continue;
        }

        for (auto& edge : adj[u_node]) {
            int v_node = edge.first;
            int weight = edge.second;
            if (dist[v_node] > dist[u_node] + weight) {
                dist[v_node] = dist[u_node] + weight;
                parent[v_node] = u_node; // Store the parent
                pq.push({dist[v_node], v_node});
            }
        }
    }

    if (dist[dest] == INT_MAX) {
        cout << "No path found between " << id_to_station[src] << " and " << id_to_station[dest] << ".\n";
        return;
    }

    vector<int> path;
    for (int at = dest; at != -1; at = parent[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    cout << "Shortest Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << id_to_station[path[i]];
        if (i != path.size() - 1) {
            cout << " => ";
        }
    }
    cout << "\n";
}

int main() {
    create_metro_map();

    cout << "\n\t\t\t****WELCOME TO THE METRO APP*****\n";
    while (true) {
        cout << "\n\t\t\t\t~~LIST OF ACTIONS~~\n\n";
        cout << "1. LIST ALL THE STATIONS IN THE MAP\n";
        cout << "2. SHOW THE METRO MAP\n";
        cout << "3. GET SHORTEST DISTANCE FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n";
        cout << "4. GET SHORTEST TIME TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n";
        cout << "5. GET SHORTEST PATH TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n";
        cout << "6. EXIT THE MENU\n\n";
        cout << "ENTER YOUR CHOICE FROM THE ABOVE LIST (1 to 6): ";
        
        int choice;
        cin >> choice;

        if (choice == 1) {
            display_stations();
        } else if (choice == 2) {
            display_map();
        } else if (choice == 3 || choice == 4) {
            display_stations();
            cout << "Enter the serial no. of Source and Destination: ";
            int x, y;
            cin >> x >> y;
            x--; y--;

            if (x >= 0 && x < station_count && y >= 0 && y < station_count) {
                int p = get_shortest_distance(x, y);
                if (choice == 3) {
                     cout << "Shortest distance between stations is " << p << " KM\n";
                } else {
                     cout << "Shortest time between stations is approximately " << p * 2 << " minutes\n"; // Assuming 2 min/km
                }
            } else {
                cout << "Invalid station number.\n";
            }
        } else if (choice == 5) {
            display_stations();
            cout << "Enter the serial no. of Source and Destination: ";
            int x, y;
            cin >> x >> y;
            x--; y--;
            
            if (x >= 0 && x < station_count && y >= 0 && y < station_count) {
                print_shortest_path(x, y);
            } else {
                cout << "Invalid station number.\n";
            }
        } else {
            cout << "Exiting... Thank you for using the Metro App!\n";
            break;
        }
    }
    return 0;
}
