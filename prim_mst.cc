#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

#include "index_min_pq.h"

// Class of edge that stores source vertex, destination vertex, and
// the weight of the edge
class Edge {
 public:
  // Constructor
  Edge(unsigned int src, unsigned int dst, double weight)
                                        : src(src), dst(dst), weight(weight) {}
  unsigned int GetSrc() { return src; }
  unsigned int GetDst() { return dst; }
  double GetWeight() { return weight; }
 private:
  unsigned int src;
  unsigned int dst;
  double weight;
};

// Class that represents graph. Adjacent_list implementation is used, but
// instead of vector of vertex, we used vector of Edge for each vertex.
class Graph {
 public:
  // Constructor
  explicit Graph(std::ifstream &input_file);
  // number of vertices
  unsigned int GetNumV() { return num_vertex; }
  // Vector of Edges adjacent to vertex
  std::vector<std::vector<Edge>> GetAdjEdgeVec() { return adj_edge_vec; }
 private:
  unsigned int num_vertex;
  // Adjacency lists implementation
  std::vector<std::vector<Edge>> adj_edge_vec;
};

Graph::Graph(std::ifstream &input_file) {
  // Get number of vertices
  input_file >> num_vertex;

  // Allocate list of vertces
  adj_edge_vec.resize(num_vertex);

  unsigned int cur_src;
  unsigned int cur_dst;
  double cur_weight;

  // Go through all the edges
  while (input_file >> cur_src >> cur_dst >> cur_weight) {
    Edge cur_edge(cur_src, cur_dst, cur_weight);
    adj_edge_vec[cur_src].push_back(cur_edge);
    adj_edge_vec[cur_dst].push_back(cur_edge);
  }
}

// Check if the string is Positive Integer
bool IsPositiveInteger(std::string input) {
  return (input.find_first_not_of("0123456789") == std::string::npos);
}

// Check if the string is Positive Double
bool IsPositiveDouble(std::string input) {
  return (input.find_first_not_of(".0123456789") == std::string::npos);
}

// Check if the command line argument
bool IsValidArgument(int argc, char* argv[]) {
  // check if text file is given
  if (argc < 2) {
    std::cerr << "Usage: ./prim_mst <graph.dat>" << std::endl;
    return false;
  }

  // check if the file can be opened
  std::ifstream input_file(argv[1]);
  if (!static_cast<bool>(input_file)) {
    std::cerr << "Error: cannot open file " << argv[1] << std::endl;
    return false;
  }

  // Check if graph size is valid
  // 1) if the size exist
  // 2) if size is positive integer
  std::string temp;
  input_file >> temp;
  if (!IsPositiveInteger(temp) || input_file.eof()) {
    std::cerr << "Error: invalid graph size" << std::endl;
    return false;
  }

  // Check edges are valid
  // We use counter to distinguish src, dst, and weight one at a time
  int graph_size = std::stoi(temp);
  int counter = 0;
  while (input_file >> temp) {
    // check source
    if (counter % 3 == 0) {
      if (!IsPositiveInteger(temp) || (std::stoi(temp) > graph_size)) {
        std::cerr << "Invalid source vertex number " << temp << std::endl;
        return false;
      }
    }
    // check dest
    if (counter % 3 == 1) {
      if (!IsPositiveInteger(temp) || (std::stoi(temp) > graph_size)) {
        std::cerr << "Invalid dest vertex number " << temp << std::endl;
        return false;
      }
    }
    // check weight
    if (counter % 3 == 2) {
      if (!IsPositiveDouble(temp)) {
        std::cerr << "Invalid weight " << temp << std::endl;
        return false;
      }
    }
    counter++;
  }

  return true;
}

// Build prim mst from the graph
std::vector<Edge> BuildPrimMst(Graph graph) {
  // store graph's objects as local variables
  unsigned int num_v = graph.GetNumV();
  std::vector<std::vector<Edge>> adj_edge_vec = graph.GetAdjEdgeVec();

  // create min-priority queue Q
  IndexMinPQ<double> Q(num_v);
  // Unknown distance from src to v
  std::vector<double> dist_vec(num_v, INFINITY);
  // Vertex v has not been visited
  std::vector<bool> marked_vec(num_v, false);
  // Best edge to v
  // std::vector<int> best_edge_vec(num_v, -1);
  std::vector<Edge> best_edge_vec(num_v, Edge(0, 0, 0));

  // Go through each vertex in graph
  for (unsigned int v = 0; v < num_v; v++) {
    // Skip visited vertex
    if (marked_vec[v]) {
      continue;
    }

    // Distance from v to itself is 0
    dist_vec[v] = 0;

    // Add first vertex to queue
    Q.Push(dist_vec[v], v);

    // iterate until min Q becomes empty
    while (Q.Size()) {
      // Remove and return closest vertex
      unsigned int root = Q.Top();
      Q.Pop();

      // We have reached root
      marked_vec[root] = true;

      // Go through all the neighbors
      for (auto &adj_edge : adj_edge_vec[root]) {
        // vertex adjacent to root
        unsigned int adj;

        // find the adj vertex from the adj edge: (root - adj) or (adj - root)
        if (adj_edge.GetDst() == root)
          adj = adj_edge.GetSrc();
        else if (adj_edge.GetSrc() == root)
          adj = adj_edge.GetDst();

        // Skip visited vertex
        if (marked_vec[adj]) {
          continue;
        }

        // New path to reach vertex is better than existing one
        if (adj_edge.GetWeight() < dist_vec[adj]) {
          dist_vec[adj] = adj_edge.GetWeight();         // Update distance to v
          best_edge_vec[adj] = adj_edge;               // Update best edge to v

          // Update priority queue
          if (Q.Contains(adj))
            Q.ChangeKey(dist_vec[adj], adj);
          else
            Q.Push(dist_vec[adj], adj);
        }
      }
    }
  }

  // mst is complete in the form of vector of edges
  return best_edge_vec;
}

// Print out the mst we have built
void PrintMst(std::vector<Edge> mst) {
  // keep track of total weight of mst
  double total_weight = 0.0;
  // Go through mst (each Edge class)
  for (auto &itr : mst) {
    // skip unworthy path
    if (itr.GetWeight() == 0) continue;
    // print source, destination, and weight in a proper manner
    std::cout << std::right << std::setfill('0') << std::setw(4)
                                                 << itr.GetSrc() << "-";
    std::cout << std::right << std::setfill('0') << std::setw(4)
                                                 << itr.GetDst();
    std::cout << " (" << std::left << std::setfill('0')
                      << std::setw(7) << itr.GetWeight() << ")" << std::endl;
    // add on to the total weight
    total_weight += itr.GetWeight();
  }
  // print the total weight of minimum spanning tree
  std::cout << std::left << std::setfill('0') << std::setw(7)
            << std::fixed << std::setprecision(5) <<  total_weight << std::endl;
}


int main(int argc, char* argv[]) {
  // checks if command line arguments are valid
  if (!IsValidArgument(argc, argv)) exit(1);

  // open the input file
  std::ifstream input_file(argv[1]);

  // construct graph from the input file
  Graph graph(input_file);

  // Build and display the minimum spanning tree of graph
  std::vector<Edge> mst = BuildPrimMst(graph);
  PrintMst(mst);

  return 0;
}
