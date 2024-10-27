#ifndef LAB_2_FORDFULKERSON_GRAPH_H
#define LAB_2_FORDFULKERSON_GRAPH_H

#include <cstdint>
#include <iostream>
#include <vector>

struct Node {
    int16_t vertex;
    int16_t weight;
    Node *next;

    Node(int16_t v, int16_t w, Node *n = nullptr) : vertex(v), weight(w), next(n) {}
};

/// Считывание графа из файла
/// \param file входной файл
/// \return возвращает пару [количество вершин; вектор указателей на списки смежности]
std::pair<int16_t, std::vector<Node *>> readGraph(std::ifstream &file);

/// Добавление ребра в список смежности
/// \param list вектор указателей на списки смежности
/// \param src начало ребра
/// \param dest конец ребра
/// \param weight вес ребра
void addEdge(std::vector<Node *> &list, int16_t src, int16_t dest, int16_t weight);

#endif  // LAB_2_FORDFULKERSON_GRAPH_H
