//
// Created by dev on 10/19/2023.
//

#ifndef P4_NODE_H
#define P4_NODE_H

#include <iostream>
#include <vector>
#include <string>
#include <tuple>

class node {
private:
    std::vector<std::tuple<std::string, int>> edges;
    std::string name;
    int get_node_position(std::string node_name);
public:
    node();
    node(std::string name);
    void print_adjacency_list();
    void change_node_weight(std::string node_name, int new_weight);
    void add_edge(std::string node_name, int weight);
    void remove_edge(std::string node_name);
    std::string get_name() const;
    std::vector<std::tuple<std::string, int>> get_edges() const;
    void modify_edge(std::string node_name, int new_weight);
};


#endif //P4_NODE_H
