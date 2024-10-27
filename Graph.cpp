#include "Graph.h"

#include <cstdint>
#include <fstream>
#include <vector>

using namespace std;

pair<int16_t, vector<Node *>> readGraph(ifstream &file) {
    int16_t n = 0;                           // Количество вершин в графе
    file.read((char *)&n, sizeof(int16_t));  // Считываем количество вершин
    vector<Node *> list(n, nullptr);  // Вектор указателей на списки смежности

    // Считывание ребер и добавление в списки смежности
    int16_t temp[3];
    while (file.read((char *)&temp, sizeof(temp))) addEdge(list, temp[0], temp[1], temp[2]);

    return {n, list};
}

void addEdge(vector<Node *> &list, int16_t src, int16_t dest, int16_t weight) {
    list[src] = new Node(dest, weight, list[src]);
}