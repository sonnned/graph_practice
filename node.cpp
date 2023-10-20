//
// Created by dev on 10/19/2023.
//

#include "node.h"

std::string node::get_name() const {
    return name;
}

node::node() {
}

node::node(std::string name) {
    this->name = name;
    edges.push_back(std::make_tuple(name, 0));
}

void node::print_adjacency_list() {
    std::cout << "Node: " << name << std::endl;
    for (auto & edge : edges) {
        std::cout << "Edge: " << std::get<0>(edge) << " Weight: " << std::get<1>(edge) << std::endl;
    }
}

int node::get_node_position(std::string node_name) {
    int current_position = -1;

    for (int i = 0; i < edges.size(); i++) {
        if (std::get<0>(edges[i]) == node_name) {
            current_position = i;
            break;
        }
    }

    return current_position;
}

void node::change_node_weight(std::string node_name, int new_weight) {
    int current_position = get_node_position(node_name);

    if (current_position != -1) {
        std::get<1>(edges[current_position]) = new_weight;
    }
}

void node::add_edge(std::string node_name, int weight) {
    edges.push_back(std::make_tuple(node_name, weight));
}

void node::remove_edge(std::string node_name) {
    int current_position = get_node_position(node_name);

    if (current_position != -1) {
        edges.erase(edges.begin() + current_position);
    }
}

std::vector<std::tuple<std::string, int>> node::get_edges() const {
    return edges;
}

void node::modify_edge(std::string node_name, int new_weight) {
    int current_position = get_node_position(node_name);

    if (current_position != -1) {
        std::get<1>(edges[current_position]) = new_weight;
    }
}