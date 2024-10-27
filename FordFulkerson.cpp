#include "FordFulkerson.h"

#include <queue>
#include <vector>

#include "Graph.h"

using namespace std;

int FordFulkerson(std::vector<Node *> &list, int16_t n, int16_t s, int16_t t) {
    vector<pair<int16_t, int16_t>> vertices(n, {-1, -1});
    vertices[s] = {INT16_MAX, -1};

    vector<Node *> edges = list;  // Копия вектора для изменения текущих потоков

    priority_queue<pair<int, int>>
        pq;  // Очередь приоритетов для выбора ребра с самым большим текущим потоком

    int i = s;
    bool rollback = false;  // Флаг отката назад в случае невозможности продолжить путь
    int max_flow = 0;
    while (true) {
        Node *temp = list[i];
        if (!rollback) {
            pq = priority_queue<pair<int, int>>();
            while (temp) {
                if (temp->weight > 0 && vertices[temp->vertex].first == -1)
                    pq.emplace(temp->weight, temp->vertex);
                temp = temp->next;
            }
        }

        if (pq.empty()) {
            // Шаг 4
            if (i == s) {
                break;  // Переход к Шаг 6
            } else {
                i = vertices[i].second;
                pq.pop();
                rollback = true;
                continue;
            }
        } else {
            auto [weight, next_vertex] = pq.top();
            vertices[next_vertex] = {weight, i};
            //            flow.emplace_back(weight, i);
            if (next_vertex == t) {
                // Находим минимальный поток
                int16_t min = INT16_MAX;
                auto p = vertices[t];
                while (p.second != s) {
                    if (p.first < min) {
                        min = p.first;
                    }
                    p = vertices[p.second];
                }

                // Пересчитываем поток
                p = vertices[t];
                while (p.second != s) {
                    // Ребро (u, v)
                    int16_t u = vertices[p.second].second;
                    int16_t v = p.second;

                    // Для ребра (u, v)
                    Node *ptr = edges[u];
                    while (ptr) {
                        if (ptr->vertex == v) ptr->weight -= min;
                        ptr = ptr->next;
                    }

                    // Для ребра (v, u)
                    ptr = edges[v];
                    bool flag_found = false;  // Такого ребра может не быть
                    while (ptr) {
                        if (ptr->vertex == u) {
                            ptr->weight += min;
                            flag_found = true;
                        }
                        ptr = ptr->next;
                    }
                    // Если такого ребра нет
                    if (!flag_found) addEdge(edges, v, u, min);
                }
                // Очищаем метки
                vertices = vector<pair<int16_t, int16_t>>(n, {-1, -1});
                vertices[s] = {INT16_MAX, -1};
                max_flow += min;
                i = s;  // Переходим на новую итерацию
                continue;
            } else
                i = next_vertex;
        }
    }
    cout << max_flow;

    return 0;
}