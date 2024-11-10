#include <iostream>
#include <vector>
#include <set>
#include <mutex>
#include <thread>


std::vector<std::vector<int> > graph;   // Adjacency list representation of the graph
std::set<std::set<int> > cliques;       // A set to store unique K-Cliques
std::mutex cliques_mutex;              // Mutex for thread-safe access to cliques
int K;                                 // Size of the clique to find

// Function to check if all vertices in a set are connected (form a K-Clique)
bool isClique(const std::vector<int>& subgraph) {
    for (size_t i = 0; i < subgraph.size(); ++i) {
        for (size_t j = i + 1; j < subgraph.size(); ++j) {
            if (std::find(graph[subgraph[i]].begin(), graph[subgraph[i]].end(), subgraph[j]) == graph[subgraph[i]].end()) {
                return false;
            }
        }
    }
    return true;
}

// Recursive DFS to find all K-Cliques starting from a given vertex
void findKCliques(int vertex, std::vector<int> current_clique) {
    current_clique.push_back(vertex);

    // If current clique size is K, check if it’s a clique and add to results
    if (current_clique.size() == K) {
        if (isClique(current_clique)) {
            std::set<int> clique_set(current_clique.begin(), current_clique.end());
            std::lock_guard<std::mutex> lock(cliques_mutex);
            cliques.insert(clique_set);  // Add K-Clique to result set
        }
        return;
    }

    // Explore neighbors to expand the clique
    for (int neighbor : graph[vertex]) {
        if (std::find(current_clique.begin(), current_clique.end(), neighbor) == current_clique.end()) {
            findKCliques(neighbor, current_clique);
        }
    }
}

// Thread worker function to process a range of vertices
void worker(int start, int end) {
    for (int i = start; i < end; ++i) {
        findKCliques(i, {});
    }
}

int main() {
    // Example graph (adjacency list)
    graph = {
        {1, 2},        // Node 0 is connected to nodes 1 and 2
        {0, 2, 3},     // Node 1 is connected to nodes 0, 2, and 3
        {0, 1, 3},     // Node 2 is connected to nodes 0, 1, and 3
        {1, 2}         // Node 3 is connected to nodes 1 and 2
    };

    K = 3;  // Set the desired clique size

    // Start threads to divide the work of finding K-Cliques
    int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    int vertices_per_thread = graph.size() / num_threads;

    for (int i = 0; i < num_threads; ++i) {
        int start = i * vertices_per_thread;
        int end = (i == num_threads - 1) ? graph.size() : (i + 1) * vertices_per_thread;
        threads.emplace_back(worker, start, end);
    }

    // Join threads after they complete
    for (auto& t : threads) {
        t.join();
    }

    // Print found K-Cliques
    std::cout << "Found " << K << "-Cliques:\n";
    for (const auto& clique : cliques) {
        for (int node : clique) {
            std::cout << node << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
