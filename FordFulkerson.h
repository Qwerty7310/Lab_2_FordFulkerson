#ifndef LAB_2_FORDFULKERSON_FORDFULKERSON_H
#define LAB_2_FORDFULKERSON_FORDFULKERSON_H

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>

#include "Graph.h"

/// Поиск в ширину (BFS)
/// \param list вектор указателей на списки соседних вершин
/// \param s исток
/// \param t сток
/// \param parent вектор родительских вершин (для восстановления пути)
/// \return возвращает поток в текущем пути (0, если такого пути нет)
int16_t bfs(std::vector<Node *> &list, int16_t s, int16_t t, std::vector<int16_t> &parent);

/// Алгоритм Форда-Фалкерсона
/// \param list вектор указателей на списки соседних вершин
/// \param n количество вершин
/// \param s исток
/// \param t сток
/// \return максимальный поток
int FordFulkerson(std::vector<Node *> &list, int16_t n, int16_t s, int16_t t);

int verticesFlow(std::vector<Node *> &original_list, std::vector<Node *> &list, std::ofstream &output);

#endif  // LAB_2_FORDFULKERSON_FORDFULKERSON_H
