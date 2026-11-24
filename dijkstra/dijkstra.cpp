/* Dijkstra’s Algorithm LogicDijkstra’s algorithm is a greedy search method designed to find the shortest path from a source node to all 
other nodes in a weighted graph. My implementation utilizes three primary data structures: a distance vector to store the current "best" total path cost, a 
visited vector to track completed nodes, and a Min-Priority Queue (Min-Heap) to manage the "To-Do List." Initially, all distances are set
 to infinity (1.0e9), except for the starting node, which is set to zero. As the algorithm explores the graph, it "relaxes" edges by
checking if passing through a current node u offers a shorter path to a neighbor v than previously recorded. If a better path is 
found, the distance vector is updated, and the new pair is pushed into the priority queue. This process repeats until the queue is empty,
ensuring that every reachable node has its absolute shortest distance calculated with an efficiency of  O(E \log V).Monte Carlo Simulation 
The Monte Carlo simulation estimates the average shortest path length by generating 1,000 unique random graphs for specific edge densities (20% and 40%). 
For each iteration, the program constructs a new graph and populates it with edges based on a "coin-flip" probability. By running Dijkstra’s algorithm across these 1,000 scenarios, 
we collect a statistically significant sample of data. The final average is calculated by summing all reachable path distances and dividing by the total count of valid paths.
 Unreachable nodes (islands) are explicitly ignored to prevent "Infinity" values from skewing the results. This simulation demonstrates the inverse relationship between edge density and path length: 
 as the graph becomes more connected, the average travel distance between nodes significantly decreases. */

#include <iostream>             // for I/O
#include <queue>                // for priority_queue
#include <vector>               // for vector
#include <utility>              // for pair
#include <functional>           // for greater<>
#include <random>


// 1st Lets make the blue print of the GRAPH
class Graph {
private:
    int num_vertices;
    int num_edges;
    std::vector<std::vector<double>> matrix;
    // Making engine(generates random numbers) accessible to all (like every graph having a dice in pocket)
    std::default_random_engine engine;
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

        // Helper Function 
        double prob() {
            // Probability distributed equally from 0.0 to 1.0
            static std::uniform_real_distribution<double> dist(0.0, 1.0);
            // Returns the filtered result between 0.0 & 1.0
            return dist(engine);
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

        // Method to generate random weight for elements inside the matrix
        void generateRandomEdges (double density){
            // Generate a random weight between 1.0 to 10.0
            static std::uniform_real_distribution<double> weight_dist(1.0, 10.0);
            
            for (int i = 0; i < num_vertices; i++) {
                for (int j = i+1; j < num_vertices; j++) {
                    // Coin flip density check
                    if (prob() < density) {
                        double weight = weight_dist(engine);
                        // Call the edge adder
                        addEdge (i, j, weight);
                    }
                }
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


// Dijkstra's algorithm
std::vector<double> dijkstra (const Graph& g, int start_node) {
    // Get the size of the graph
    int n = g.V();
    // Create the distance list
    std::vector<double> dist(n, 1.0e9);
    // Set the start node distance to 0
    dist[start_node] = 0.0;
    // Create the visited List
    std::vector<bool> visited(n, false);

    // Creates a To-do List that keeps the smallest distance at the top
    std::priority_queue<std::pair<double, int>,
                        std::vector<std::pair<double, int>>,
                        std::greater<std::pair<double, int>>> pq;

    // Put the starting city in the To-do list
    pq.push(std::make_pair(0.0, start_node));

    // dijkstra loop
    while(!pq.empty()) {
        // Pick the closes city from To-do list 
        int u = pq.top().second;
        pq.pop();
        // Check if its visited
        if (visited[u]) {
            continue;
        }
        // Mark visited
        visited[u] = true;

        // Look for its neighbours
        for (int v = 0; v < n; v++) {
            // Get the neighbour weight
            double weight = g.getWeight(u, v);
            // Check if road exist or not 
            if (weight < 1.0e9) {
                // Check if its better way to v then value in dist
                if (dist[u] + weight < dist[v]) {
                    // Update the dist for better way
                    dist[v] = dist[u] + weight;
                    // Push the new better path in the To-do List / priority queue
                    pq.push(std::make_pair(dist[v], v));
                }
            }
        }
    }
    // Hand back the finished notebook
    return dist;
}

// Function to run the Monte-Carlo Simulation
void runSimulation (double density) {
    int num_nodes = 50;
    double sum = 0.0;
    int count = 0;

    // Monte Carlo Loop
    for (int i = 0; i < 1000; i++){
        Graph g(num_nodes);
        g.generateRandomEdges(density);

        // Find all the paths from Node 0
        std::vector<double> result = dijkstra(g, 0);

        // Sum up all distances except non roads (infinity)
        for (int j = 1; j < num_nodes; j++) {
            if (result[j] < 1.0e9) {
                sum += result[j];
                count++;
            }
        }
    }
    if (count > 0) {
        std::cout << "Density " << density << " - Average Shortest Path: " << (sum/count) << std::endl;
    }
}

// Main Function 
int main() {
    std::cout << "-- Graph Simulation --" << std::endl;
    runSimulation(0.2);
    runSimulation(0.4);
    return 0;
}
