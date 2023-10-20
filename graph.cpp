//
// Created by dev on 10/19/2023.
//

#include "graph.h"

graph::graph() {
}

void graph::create_graph(std::string file_name) {
    std::vector<std::string> info;
    std::vector<std::tuple<std::string, std::string, std::string>> file_nodes;
    database db(file_name);

    db.set_database_separator(' ');
    try {
        info = db.get_database_columns();
        for (int i = 0; i < info[0].size(); i++) {
            if (info[0][i] != '\n') {
                std::string node1 = "";
                node1 += info[0][i];
                std::string node2 = "";
                node2 += info[1][i];
                std::tuple<std::string, std::string, std::string> node_connection(node1, node2, "-1");
                file_nodes.push_back(node_connection);
            }
        }

        db.set_database_separator('\n');
        info = db.split(info[2]);

        for (int i = 0; i < info.size(); i++) {
            std::get<2>(file_nodes[i]) = info[i];
        }

        //creamos los nodos y los agregamos a la matriz de adyacencia
        for (int i = 0; i < file_nodes.size(); i++) {
            std::string node1 = std::get<0>(file_nodes[i]);
            std::string node2 = std::get<1>(file_nodes[i]);
            std::string weight = std::get<2>(file_nodes[i]);
            int node1_position = get_node_position(node1);
            int node2_position = get_node_position(node2);
            bool node1_exists = node1_position != -1;
            bool node2_exists = node2_position != -1;

            /*
            for (int j = 0; j < adjacency_matrix.size(); j++) {
                if (adjacency_matrix[j].get_name() == node1) {
                    node1_position = j;
                    node1_exists = true;
                }
                if (adjacency_matrix[j].get_name() == node2) {
                    node2_position = j;
                    node2_exists = true;
                }
            }
            */

            if (!node1_exists) {
                node new_node(node1);
                adjacency_matrix.push_back(new_node);
                node1_position = adjacency_matrix.size() - 1;
            }
            if (!node2_exists) {
                node new_node(node2);
                adjacency_matrix.push_back(new_node);
                node2_position = adjacency_matrix.size() - 1;
            }

            adjacency_matrix[node1_position].add_edge(node2, std::stoi(weight));
            adjacency_matrix[node2_position].add_edge(node1, std::stoi(weight));
        }
    } catch (int e) {
        std::cout << "Error: " << e << std::endl;
    }
}

void graph::print_adjacency_matrix() {
    std::cout << "\t";
    for (int i = 0; i < adjacency_matrix.size(); i++) {
        std::cout << adjacency_matrix[i].get_name() << "\t";
    }
    std::cout << std::endl;

    for (int i = 0; i < adjacency_matrix.size(); i++) {
        std::cout << adjacency_matrix[i].get_name() << "\t";
        for (int j = 0; j < adjacency_matrix.size(); j++) {
            std::string weight = "-1";
            for (int k = 0; k < adjacency_matrix[i].get_edges().size(); k++) {
                if (std::get<0>(adjacency_matrix[i].get_edges()[k]) == adjacency_matrix[j].get_name()) {
                    weight = std::to_string(std::get<1>(adjacency_matrix[i].get_edges()[k]));
                }
            }
            std::cout << weight << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void graph::print_adjacency_list(std::string node_name) {
    int current_node_position = get_node_position(node_name);

    adjacency_matrix[current_node_position].print_adjacency_list();
    std::cout << std::endl;
}

int graph::get_node_position(std::string node_name) {
    int current_node_position = -1;

    for (int i = 0; i < adjacency_matrix.size(); i++) {
        if (adjacency_matrix[i].get_name() == node_name) {
            current_node_position = i;
        }
    }

    return current_node_position;
}

void graph::add_node(std::string node_name) {
    node new_node(node_name);
    adjacency_matrix.push_back(new_node);
}

void graph::add_connection(std::string node1, std::string node2, std::string weight) {
    int node1_position = get_node_position(node1);
    int node2_position = get_node_position(node2);
    bool node1_exists = node1_position != -1;
    bool node2_exists = node2_position != -1;

    if (!node1_exists) {
        add_node(node1);
        node1_position = adjacency_matrix.size() - 1;
    }
    if (!node2_exists) {
        add_node(node2);
        node2_position = adjacency_matrix.size() - 1;
    }

    adjacency_matrix[node1_position].add_edge(node2, std::stoi(weight));
    adjacency_matrix[node2_position].add_edge(node1, std::stoi(weight));
}

void graph::remove_node(std::string node_name) {
    int node_position = get_node_position(node_name);

    adjacency_matrix.erase(adjacency_matrix.begin() + node_position);

    for (int i = 0; i < adjacency_matrix.size(); i++) {
        adjacency_matrix[i].remove_edge(node_name);
    }
}

void graph::remove_connection(std::string node1, std::string node2) {
    int node1_position = get_node_position(node1);
    int node2_position = get_node_position(node2);

    adjacency_matrix[node1_position].remove_edge(node2);
    adjacency_matrix[node2_position].remove_edge(node1);
}

void graph::modify_connection(std::string node1, std::string node2, std::string new_weight) {
    int node1_position = get_node_position(node1);
    int node2_position = get_node_position(node2);

    adjacency_matrix[node1_position].modify_edge(node2, std::stoi(new_weight));
    adjacency_matrix[node2_position].modify_edge(node1, std::stoi(new_weight));
}

void graph::generate_aleatory_graph(int nodes, int probability) {
    int max_weight = 100;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, max_weight);

    for (int i = 0; i < nodes; i++) {
        std::string node_name = "N" + std::to_string(i);
        add_node(node_name);
    }

    for (int i = 0; i < nodes; i++) {
        for (int j = i + 1; j < nodes; j++) {
            int random_number = dis(gen);
            if (random_number <= probability) {
                std::string node1 = "N" + std::to_string(i);
                std::string node2 = "N" + std::to_string(j);
                add_connection(node1, node2, std::to_string(random_number));
            }
        }
    }

    print_adjacency_matrix();
}

std::pair<int, std::vector<std::string>> graph::dijkstra(std::string node1, std::string node2) {
    int node1_position = get_node_position(node1);
    int node2_position = get_node_position(node2);
    std::vector<std::string> path;
    std::vector<int> distances;
    std::vector<bool> visited;
    std::vector<int> previous;
    std::priority_queue<std::pair<int, int>> pq;

    for (int i = 0; i < adjacency_matrix.size(); i++) {
        distances.push_back(INT_MAX);
        visited.push_back(false);
        previous.push_back(-1);
    }

    distances[node1_position] = 0;
    pq.push(std::make_pair(0, node1_position));

    while (!pq.empty()) {
        int current_node = pq.top().second;
        pq.pop();

        if (!visited[current_node]) {
            visited[current_node] = true;

            for (int i = 0; i < adjacency_matrix[current_node].get_edges().size(); i++) {
                std::string adjacent_node = std::get<0>(adjacency_matrix[current_node].get_edges()[i]);
                int adjacent_node_position = get_node_position(adjacent_node);
                int weight = std::get<1>(adjacency_matrix[current_node].get_edges()[i]);

                if (distances[adjacent_node_position] > distances[current_node] + weight) {
                    distances[adjacent_node_position] = distances[current_node] + weight;
                    previous[adjacent_node_position] = current_node;
                    pq.push(std::make_pair(-distances[adjacent_node_position], adjacent_node_position));
                }
            }
        }
    }

    int current_node = node2_position;
    while (current_node != -1) {
        path.push_back(adjacency_matrix[current_node].get_name());
        current_node = previous[current_node];
    }

    std::reverse(path.begin(), path.end());

    return std::make_pair(distances[node2_position], path);
}