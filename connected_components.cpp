/*  Identifier = 15C1680EE94C640EC35E1694295A3625C3254CBA

    EECS 281 Lab 4: Connected Components

    For this lab, you will write a program that calculates the
    number of connected components in an undirected graph.

    Your program will receive an input file in the following format:
    1) The first line of input contains the number of vertices V and number
       of edges E in the graph.
    2) The next E lines list out the connections between vertices in the
       graph in the format of "u v", which indicates the existence of an edge
       between u and v.

    For example, the following input file would be read as follows:
    4 2  (the graph has 4 vertices numbered from 0-3, and two edges exist in
          the graph)
    0 1  (the first of these edges connects vertex 0 with vertex 1)
    0 2  (the second of these edges connects vertex 0 with vertex 2)

    In this case, vertices {0, 1, 2} form a connected component, and vertex
    {3} forms a connected component (since 3 is not connected to anything).
    Thus, your program should print out 2.

    You will be using union-find to complete this lab. The following starter
    code has been provided. Feel free to modify this code in your
    implementation. Good luck!
*/

#include "xcode_redirect.hpp"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <vector>
using std::vector;


class Graph {
    uint32_t V;
    uint32_t E;
    // TODO: add any additional member variables, as needed
    vector<uint32_t> reps;
    vector<vector<uint32_t>> lst;
//    struct edge {
//        uint32_t source;
//        uint32_t dest;
//    };
//    edge* e;

public:
    // Graph constructor that initializes the graph and its member variables
    Graph(uint32_t v, uint32_t e) : V{v}, E{e} {
        // TODO: initialize member variables that you added above
        this->V = v;
        this->E = e;
        reps.resize(v);
        reps[v] = v;
        lst.resize(v);
//        lst[v].resize(v);
        vector<uint32_t> push;
        push.resize(v);
        push[1] = v;
//        lst[v] = vector<uint32_t>(1, v);
        lst[v] = push;
//        reps[v] = e;
       
    }  // Graph()


    uint32_t find_set(uint32_t v) {
        // TODO: implement the find_set function
        
        size_t parent = v;
        
        while (reps[v] != v) {
          v = reps[v];
        }

        while (reps[parent] != v) {
          size_t tmp = reps[parent];
          reps[parent] = v;
          parent = tmp;
        }
        return v;
    }  // find_set()


    void union_set(uint32_t a, uint32_t b) {
        // TODO: implement the union_set function
        a = find_set(a);
            b = find_set(b);
            if (a != b) {
                if (lst[a].size() < lst[b].size())
                    std::swap(a, b);
                while (!lst[b].empty()) {
                    uint32_t v = lst[b].back();
                    lst[b].pop_back();
                    reps[v] = a;
                    lst[a].push_back(v);
                }
            }
    }  // union_set()


    uint32_t count_components() {
        // TODO: implement the count_components function
        bool* visited = new bool[V];
        uint32_t count = 0;
            for (uint32_t v = 0; v < V; v++)
                visited[v] = false;

            for (uint32_t v = 0; v < V; v++) {
                if (visited[v] == false) {
                    union_set(v, find_set(v));
                    count += 1;
                }
            }

        return count;
    }  // count_components()
};  // Graph{}


int main(int argc, char *argv[]) {
    xcode_redirect(argc, argv);
    // You do not need to modify main.
    std::ios_base::sync_with_stdio(false);
    uint32_t vertex_count, edge_count = 0;

    cin >> vertex_count;
    cin >> edge_count;

    Graph g(vertex_count, edge_count);

    cout << g.count_components() << endl;
    return 0;
}  // main()
