#include <fstream>
#include <iostream>

#include "FordFulkerson.h"
#include "Graph.h"
#include "cxxopts.hpp"

using namespace std;

void run(ifstream &input_file, ofstream &output_file);

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

        run(input, output);

    } catch (const std::exception &e) {
        cerr << "Ошибка при разборе аргументов: " << e.what() << endl;
        return 1;
    }

    return 0;
}

void run(ifstream &input, ofstream &output) {
    //    auto [n, list] = readGraph(input);

    vector<Node *> adjacencyList;
    addEdge(adjacencyList, 1, 2, 20);
    addEdge(adjacencyList, 1, 3, 30);
    addEdge(adjacencyList, 1, 4, 10);

    addEdge(adjacencyList, 2, 3, 40);
    addEdge(adjacencyList, 2, 5, 30);

    addEdge(adjacencyList, 3, 4, 10);
    addEdge(adjacencyList, 3, 5, 20);

    addEdge(adjacencyList, 4, 5, 20);


    FordFulkerson(adjacencyList, adjacencyList.size(), 0, adjacencyList.size() - 1);
}
