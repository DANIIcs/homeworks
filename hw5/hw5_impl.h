#ifndef HW5_IMPL_H
#define HW5_IMPL_H

#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

#include "hw5.h"

// Añadir una arista al grafo dirigido
void add_edge(std::vector<std::vector<int>>& graph, int from, int to) {
    if (from >= graph.size() || to >= graph.size()) {
        graph.resize(std::max(from, to) + 1);
    }
    graph[from].push_back(to);
}

// Retornar el número de vértices en el grafo
int n_vertices(std::vector<std::vector<int>> const& graph) {
    return graph.size();
}

// Retornar el número de aristas en el grafo
int n_edges(std::vector<std::vector<int>> const& graph) {
    int edges = 0;
    for (const auto& adj_list : graph) {
        edges += adj_list.size();
    }
    return edges;
}

// Algoritmo de búsqueda en anchura (BFS)
std::vector<int> BFS(std::vector<std::vector<int>> const& graph, int from) {
    std::vector<int> visited(graph.size(), 0);
    std::queue<int> q;
    std::vector<int> ret;

    q.push(from);
    visited[from] = 1;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        ret.push_back(curr);

        for (int neighbor : graph[curr]) {
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = 1;
            }
        }
    }
    return ret;
}

// Algoritmo de búsqueda en profundidad (DFS)
std::vector<int> DFS(std::vector<std::vector<int>> const& graph, int from) {
    std::vector<int> visited(graph.size(), 0);
    std::stack<int> s;
    std::vector<int> ret;

    s.push(from);

    while (!s.empty()) {
        int curr = s.top();
        s.pop();

        if (!visited[curr]) {
            visited[curr] = 1;
            ret.push_back(curr);

            for (int neighbor : graph[curr]) {
                if (!visited[neighbor]) {
                    s.push(neighbor);
                }
            }
        }
    }
    return ret;
}

// Encontrar componentes conexas en el grafo
std::vector<std::vector<int>> connected_components(
    std::vector<std::vector<int>> const& graph) {
    std::vector<int> visited(graph.size(), 0);
    std::vector<std::vector<int>> ret;

    for (int i = 0; i < graph.size(); ++i) {
        if (!visited[i]) {
            std::vector<int> component;
            std::stack<int> s;
            s.push(i);

            while (!s.empty()) {
                int curr = s.top();
                s.pop();

                if (!visited[curr]) {
                    visited[curr] = 1;
                    component.push_back(curr);

                    for (int neighbor : graph[curr]) {
                        if (!visited[neighbor]) {
                            s.push(neighbor);
                        }
                    }
                }
            }
            ret.push_back(component);
        }
    }
    return ret;
}

// Contar el número de componentes conexas
int n_connected_components(std::vector<std::vector<int>> const& graph) {
    return connected_components(graph).size();
}

#endif
