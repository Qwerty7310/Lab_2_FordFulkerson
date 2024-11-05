#include "FordFulkerson.h"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>

#include "Graph.h"

using namespace std;

int16_t bfs(vector<Node *> &list, int16_t s, int16_t t, vector<int16_t> &parent) {
    // Инициализируем вектор parent (хранит родительские вершины для восстановления пути)
    fill(parent.begin(), parent.end(), -1);  // -1 - еще не посещенные вершины
    parent[s] = -2;                          // Для исходной вершины

    // Инициализируем очередь для хранения вершин, которые нужно посетить
    queue<pair<int16_t, int16_t>> q;
    q.emplace(s, INT16_MAX);

    while (!q.empty()) {
        auto [cur, flow] = q.front();
        q.pop();

        for (Node *edge = list[cur]; edge; edge = edge->next) {
            if (parent[edge->vertex] == -1 && edge->weight > 0) {
                parent[edge->vertex] = cur;
                int16_t new_flow = min(flow, edge->weight);

                if (edge->vertex == t) return new_flow;

                q.emplace(edge->vertex, new_flow);
            }
        }
    }

    return 0;
}

int FordFulkerson(vector<Node *> &list, int16_t n, int16_t s, int16_t t) {
    int max_flow = 0;           // Максимальный поток от s к t
    vector<int16_t> parent(n);  // Вектор родительский вершин

    int16_t new_flow;  // Поток в текущем пути
    while ((new_flow = bfs(list, s, t, parent))) {
        max_flow += new_flow;

        // Обновление остаточной сети
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];

            // Обновление веса прямого ребра (prev, cur)
            for (Node *edge = list[prev]; edge; edge = edge->next) {
                if (edge->vertex == cur) {
                    edge->weight -= new_flow;
                    break;
                }
            }

            // Обновление веса обратного ребра (cur, prev)
            bool flag_found = false;
            for (Node *edge = list[cur]; edge; edge = edge->next) {
                if (edge->vertex == prev) {
                    edge->weight += new_flow;
                    flag_found = true;
                    break;
                }
            }

            // Если не нашли обратного ребра
            if (!flag_found) addEdge(list, cur, prev, new_flow);

            cur = prev;  // Переход к следующей вершине
        }
    }

    return max_flow;
}
