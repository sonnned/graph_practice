//
// Created by dev on 10/19/2023.
//

#ifndef P4_GRAPH_H
#define P4_GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <random>
#include <algorithm>
#include <queue>
#include "node.h"
#include "database.h"

class graph {
private:
    std::vector<node> adjacency_matrix;
public:
    graph();
    void create_graph(std::string file_name);
    void print_adjacency_matrix();
    void print_adjacency_list(std::string node_name);
    int get_node_position(std::string node_name);
    void add_node(std::string node_name);
    void add_connection(std::string node1, std::string node2, std::string weight);
    void remove_node(std::string node_name);
    void remove_connection(std::string node1, std::string node2);
    void modify_connection(std::string node1, std::string node2, std::string new_weight);
    void generate_aleatory_graph(int nodes, int probability);
    std::pair<int, std::vector<std::string>> dijkstra(std::string node1, std::string node2);
};


#endif //P4_GRAPH_H
