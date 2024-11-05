#include <chrono>
#include <fstream>
#include <iostream>

#include "FordFulkerson.h"
#include "Graph.h"
#include "cxxopts.hpp"

using namespace std;

void run(ifstream &input_file, ofstream &output_file, int test_number);

int main(int argc, char *argv[]) {
    try {
        cxxopts::Options options("Lab_2_FordFulkerson", "Lab2");

        // Определение возможных опций
        options.add_options()("o,output", "Имя выходного файла",
                              cxxopts::value<std::string>()->default_value("../default_output.txt"))(
            "input", "Имя входного файла", cxxopts::value<std::string>())("h,help", "Вывод справки");

        // Указываем, что "input" — позиционный аргумент
        options.parse_positional({"input"});

        // Парсим аргументы
        auto result = options.parse(argc, argv);

        // Проверяем, запрошена ли справка
        if (result.count("help")) {
            cout << options.help() << endl;
            return 0;
        }

        // Проверяем наличие обязательного аргумента "input"
        if (!result.count("input")) {
            cerr << "Ошибка: необходим входной файл." << endl;
            return 1;
        }

        // Получаем значения аргументов
        string input_file = result["input"].as<string>();
        string output_file = result["output"].as<string>();

        // Ваш основной код с использованием входного и выходного файлов
        ifstream input(input_file, ios::binary);
        if (!input.is_open()) {
            cerr << "Ошибка: не удается открыть входной файл " << input_file << endl;
            return 1;
        }

        ofstream output(output_file);
        if (!output.is_open()) {
            cerr << "Ошибка: не удается открыть выходной файл " << output_file << endl;
            return 1;
        }

        run(input, output, (int)input_file[input_file.size() - 4] - '0');

    } catch (const std::exception &e) {
        cerr << "Ошибка при разборе аргументов: " << e.what() << endl;
        return 1;
    }

    return 0;
}

void run(ifstream &input, ofstream &output, int test_number) {
    cout << "test: " << test_number << endl;
    auto [n, list] = readGraph(input);

    /* ------ Пример графа с 5 вершинами ------ */
    /*
        int n = 5;
        vector<Node *> adjacencyList(n, nullptr);
        addEdge(adjacencyList, 0, 1, 20);
        addEdge(adjacencyList, 0, 2, 30);
        addEdge(adjacencyList, 0, 3, 10);

        addEdge(adjacencyList, 1, 2, 40);
        addEdge(adjacencyList, 1, 4, 30);

        addEdge(adjacencyList, 2, 3, 10);
        addEdge(adjacencyList, 2, 4, 20);

        addEdge(adjacencyList, 3, 4, 20);
     */

    // clang-format off
    int16_t vertices[6][2] = {
        {376, 309},
        {168, 267},
        {340, 995},
        {477, 231},
        {637, 471},
        {93, 604}
    };
    // clang-format on

    // Начало замера времени
    auto start_time = chrono::high_resolution_clock::now();

    /* ------ Поиск потока через вершины из ответов ------ */
    //    int max_flow = FordFulkerson(list, n, vertices[test_number - 1][0], vertices[test_number - 1][1]);
    //    cout << "Max flow: " << max_flow << endl;
    /* --------------------------------------------------- */

    int max_flow = FordFulkerson(list, n, 0, 1);
    cout << "Max flow: " << max_flow << endl;

    // Конец замера времени
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end_time - start_time;
    cout << "Time: " << elapsed.count() << " seconds\n";
}
