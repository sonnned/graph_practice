#include <iostream>
#include "graph.h"
#define PATH "C:/Users/dev/Documents/Udea/p4/red_prueba.txt"

int main() {
    graph g;
    bool ban = true;

    while (ban) {
        std::cout << "1. Crear grafo aleatorio" << std::endl;
        std::cout << "2. Cargar grafo desde archivo" << std::endl;
        std::cout << "3. Salir" << std::endl;
        int option;
        std::cout << "Ingrese una opcion: ";
        std::cin >> option;
        std::cout << std::endl;

        switch (option) {
            case 1: {
                int nodes;
                int probability;
                std::cout << "Ingrese el numero de nodos: ";
                std::cin >> nodes;
                std::cout << std::endl;
                if (nodes < 2) {
                    std::cout << "El numero de nodos debe ser mayor a 1" << std::endl;
                    break;
                }
                std::cout << "Ingrese la probabilidad: ";
                std::cin >> probability;
                std::cout << std::endl;
                if (probability < 0 || probability > 100) {
                    std::cout << "La probabilidad debe estar entre 0 y 100" << std::endl;
                    break;
                }
                g.generate_aleatory_graph(nodes, probability);
                ban = false;
                break;
            }
            case 2: {
                g.create_graph(PATH);
                ban = false;
                break;
            }
            case 3: {
                ban = false;
                break;
            }
            default: {
                std::cout << "Opcion invalida" << std::endl;
                break;
            }
        }
    }

    bool ban2 = true;
    
    while (ban2) {
        std::cout << "1. Imprimir matriz de adyacencia" << std::endl;
        std::cout << "2. Imprimir lista de adyacencia" << std::endl;
        std::cout << "3. Agregar nodo" << std::endl;
        std::cout << "4. Eliminar nodo" << std::endl;
        std::cout << "5. Agregar conexion" << std::endl;
        std::cout << "6. Eliminar conexion" << std::endl;
        std::cout << "7. Modificar conexion" << std::endl;
        std::cout << "8. Calcular ruta mas corta" << std::endl;
        std::cout << "9. Salir" << std::endl;
        int option;
        std::cout << "Ingrese una opcion: ";
        std::cin >> option;
        std::cout << std::endl;

        switch (option) {
            case 1: {
                g.print_adjacency_matrix();
                break;
            }
            case 2: {
                std::string node_name;
                std::cout << "Ingrese el nombre del nodo: ";
                std::cin >> node_name;
                std::cout << std::endl;
                g.print_adjacency_list(node_name);
                break;
            }
            case 3: {
                std::string node_name;
                std::cout << "Ingrese el nombre del nodo: ";
                std::cin >> node_name;
                std::cout << std::endl;
                g.add_node(node_name);
                break;
            }
            case 4: {
                std::string node_name;
                std::cout << "Ingrese el nombre del nodo: ";
                std::cin >> node_name;
                std::cout << std::endl;
                g.remove_node(node_name);
                break;
            }
            case 5: {
                std::string node1;
                std::string node2;
                std::string weight;
                std::cout << "Ingrese el nombre del nodo 1: ";
                std::cin >> node1;
                std::cout << std::endl;
                std::cout << "Ingrese el nombre del nodo 2: ";
                std::cin >> node2;
                std::cout << std::endl;
                std::cout << "Ingrese el peso de la conexion: ";
                std::cin >> weight;
                std::cout << std::endl;
                g.add_connection(node1, node2, weight);
                break;
            }
            case 6: {
                std::string node1;
                std::string node2;
                std::cout << "Ingrese el nombre del nodo 1: ";
                std::cin >> node1;
                std::cout << std::endl;
                std::cout << "Ingrese el nombre del nodo 2: ";
                std::cin >> node2;
                std::cout << std::endl;
                g.remove_connection(node1, node2);
                break;
            }
            case 7: {
                std::string node1;
                std::string node2;
                std::string new_weight;
                std::cout << "Ingrese el nombre del nodo 1: ";
                std::cin >> node1;
                std::cout << std::endl;
                std::cout << "Ingrese el nombre del nodo 2: ";
                std::cin >> node2;
                std::cout << std::endl;
                std::cout << "Ingrese el nuevo peso de la conexion: ";
                std::cin >> new_weight;
                std::cout << std::endl;
                g.modify_connection(node1, node2, new_weight);
                break;
            }
            case 8: {
                std::string node1;
                std::string node2;
                std::cout << "Ingrese el nombre del nodo 1: ";
                std::cin >> node1;
                std::cout << std::endl;
                std::cout << "Ingrese el nombre del nodo 2: ";
                std::cin >> node2;
                std::cout << std::endl;
                std::pair<int, std::vector<std::string>> dijkstra = g.dijkstra(node1, node2);

                std::cout << "Shortest path: " << dijkstra.first << std::endl;
                std::cout << "Path: ";
                for (int i = 0; i < dijkstra.second.size(); i++) {
                    std::cout << dijkstra.second[i] << " ";
                }
                std::cout << std::endl << std::endl;
                break;
            }
            case 9: {
                ban2 = false;
                break;
            }
            default: {
                std::cout << "Opcion invalida" << std::endl;
                break;
            }
        }
    }
    return 0;
}
