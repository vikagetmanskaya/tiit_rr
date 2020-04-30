// ConsoleApplication27.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

const unsigned int kTestCasesNumber = 5;

enum class GraphType
{
    Common,
    Functional,
    CounterFunctional
};

GraphType getType(const vector<vector<int>>& graph);

int main()
{
    ifstream fin;
    ofstream fout;

    for (unsigned test = 1; test <= kTestCasesNumber; ++test)
    {
        fin.open("test-in-" + std::to_string(test) + ".txt");
        fout.open("test-out-" + std::to_string(test) + ".txt");

        if (!fin.is_open() || !fout.is_open())
        {
            std::cout << "Can't open files for test #" << test << std::endl;
            continue;
        }

        int nodesCnt, edgesCnt;
        fin >> nodesCnt >> edgesCnt;

        if (nodesCnt < 1)
        {
            std::cout << "Test #" << test << " ";
            std::cout << "Number of nodes can't be less than 1, but given " << nodesCnt << std::endl;
            fin.close();
            fout.close();
            continue;
        }

        vector<vector<int>> graph(nodesCnt);

        bool broken = false;

        for (int i = 0; i < edgesCnt; ++i)
        {
            int a, b;
            fin >> a >> b;

            if (a < 1 || a > nodesCnt || b < 1 || b > nodesCnt)
            {
                std::cout << "Test #" << test << " ";
                std::cout << "Node number should be in range from " << 1 << " to " << nodesCnt << std::endl;
                broken = true;
                break;
            }

            --a, --b;
            graph[a].push_back(b);
        }

        if (broken)
        {
            fin.close();
            fout.close();
            continue;
        }

        std::string output;

        switch (getType(graph)) {
        case GraphType::Common: output = "common"; break;
        case GraphType::Functional: output = "functional"; break;
        case GraphType::CounterFunctional: output = "counter-functional"; break;
        default: output = "undefined";
        }

        fout << output << endl;

        fout.close();
        fin.close();
    }
    return 0;
}

GraphType getType(const vector<vector<int>>& graph)
{
    unsigned functionalNodes = 0;

    for (size_t i = 0; i < graph.size(); ++i)
        functionalNodes += graph[i].size() == 1;

    if (functionalNodes == graph.size())
        return GraphType::Functional;
    if (functionalNodes == 0)
        return GraphType::CounterFunctional;
    return GraphType::Common;
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
