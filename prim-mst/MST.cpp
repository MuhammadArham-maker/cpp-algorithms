/*
Definition: MST and Prim’s AlgorithmWhat is a Minimum Spanning Tree (MST)?A Minimum Spanning Tree is the set of edges that connects all
 vertices in an undirected, weighted graph such that the total weight of the edges is minimized and no cycles (loops) are formed. While 
 Dijkstra’s algorithm focuses on the shortest distance from a single source to every other node, an MST focuses on the most efficient way 
 to link the entire group together.How Prim’s Algorithm WorksPrim’s algorithm is a "greedy" strategy that "grows" the MST one node at a
  time. It is structurally very similar to Dijkstra’s algorithm, utilizing three main components:in_tree (Boolean List): This acts as a 
  checklist to ensure we don't pick the same node twice, preventing loops.min_edge (Value List): Unlike Dijkstra, which stores the 
  cumulative distance from the start, this list stores the cheapest single edge currently available to connect a node to the existing tree.
  Priority Queue (Min-Heap): This acts as the "Bargain Bin." It stores potential neighbor edges and always hands us the absolute cheapest
   "bridge" to an unvisited node.The Core LogicAt each step, we pop the cheapest edge from the priority queue. If the node isn't already
    in_tree, we "buy" that edge, add its weight to our total, and look at its neighbors. If a neighbor $v$ can be connected to our current
     tree more cheaply than our previous best guess in min_edge[v], we update the list and push the new "better deal" into the priority
      queue.
*/

#include <iostream>             // for I/O
#include <queue>                // for priority_queue
#include <vector>               // for vector
#include <utility>              // for pair
#include <functional>           // for greater<>

// 1st Lets make the blue print of the GRAPH
class Graph {
private:
    int num_vertices;
    int num_edges;
    std::vector<std::vector<double>> matrix;
public:
    // Constructor 
    Graph(int size): num_vertices(size), num_edges(0),
                     // Make a matrix of size rows and each row has size number of array elements and value
                     matrix(size, std::vector<double>(size, 1.0e9)) {
                        
            // For diagonals intialize the value to 0 
            for (int i = 0; i < num_vertices; i++) {
                matrix[i][i] = 0.0;
            }
        }

        // Method to insert edge(road) with a value weight
        void addEdge (int u, int v, double weight) {
            if(u >= 0 && u < num_vertices && v >= 0 && v < num_vertices) {
                // Add the road in both directions
                matrix[u][v] = matrix[v][u] = weight;
                // Keep track of total roads
                num_edges++;
            }
        }

        // A Get Weight Method for Dijkstra's algorithm
        double getWeight (int u, int v) const {
            if (u >= 0 && u < num_vertices && v >= 0 && v < num_vertices) {
                return matrix[u][v];
            }
            // If nodes are invalid return infinity
            return 1.0e9;
        }

        // Getter method for Dijkstra's algorithm
        int V () const {
            return num_vertices;
        }
};

// Prim Function
double primMST(const Graph& g, int start_node) {
    // Containers we want 
    int n = g.V();
    if(n == 0) { return 0.0; }

    // Notebook for cheapest edge to each city
    std::vector<double> min_edge (n, 1.0e9);
    // In the Grid checklist
    std::vector<bool> in_tree (n, false);
    // stores total weight
    double total_weight = 0.0;

    // priority queque
    std::priority_queue<std::pair<double, int>,
                        std::vector<std::pair<double, int>>,
                        std::greater<std::pair<double, int>>> pq;

    // Start at Node 0
    min_edge[start_node] = 0.0;
    // Push the 1st node in the pq
    pq.push(std::make_pair(0.0, start_node));

    while (!pq.empty()) {
        // Get the weight & node before popping
        double w = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (in_tree[u]) { continue; }

        in_tree [u] = true;
        total_weight += w;
        

        // Find all u neighbours and add in the pq
        for (int v = 0; v < n; v++) {
            double weight = g.getWeight(u, v);
            // Check if its shortest road to that city 
            if (!in_tree[v] && weight < min_edge[v]) {
                min_edge[v] = weight;
                pq.push(std::make_pair(weight, v));
            }
        }  
    }
    return total_weight;
}

// Main Function 
int main() {
    int V, E;
    // Read the Vertices (nodes) & Edges (Connections) 
    if(! (std::cin >> V >> E)) {
        return 0;
    }

    // Initialize the graph object with size V
    Graph g(V);

    // Loop through the number of Edges (Connections)
    for (int i = 0; i < E; i++) {
        int u, v;
        double w;

        // Read the 2 nodes and the weight
        std::cin >> u >> v >> w;

        // Putting the read values in the matrix
        g.addEdge(u, v, w);

        // g is fully populated and ready for MST!
    }
    // Compute and output the result
    double mst_cost = primMST(g, 0);
    std::cout << "MST Cost: " << mst_cost << std::endl;

    return 0;
}
