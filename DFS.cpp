#include <iostream>
#include <vector>
#include <stack>
#include <limits>
#include <list>

const auto INF = std::numeric_limits<int>::max();

struct Branch
{
    int index;
    int weight;
};

struct Node
{
    std::vector<Branch> branches;
    bool visited;
    int prevInd;
    int id;
    int weight;
    void start_value(int id)
    {
        this->id = id;
        prevInd = -1;
        weight = INF;
        visited = false;
    }
};

class Graph
{
private:
    std::vector<Node> nodes;
    std::stack<Node> Stack;
    size_t size;
    std::vector<int> result;
    std::vector<int> shortest_path(int);
public:
    Graph();
    Graph(std::vector<std::vector<int>>);
    std::vector<int> dfs(int, int);
};

std::vector<int> Graph::shortest_path(int end_index)
{
    std::vector<int> temp;
    while (end_index != -1)
    {
        temp.push_back(end_index);
        end_index = nodes[end_index].prevInd;
    }
    std::reverse(temp.begin(), temp.end());
    return temp;
}

Graph::Graph()
{
    std::vector<int> temp = { 0, 1, 2, 1, 0, 4, 2, 4, 0 };
    this->size = 3;
    nodes.resize(size);
    for (size_t i = 0; i < size; i++)
        nodes[i].branches.resize(size);
    size_t i = 0, j = 0;
    for (auto t : temp)
    {
        nodes[i].branches[j].index = j;
        nodes[i].branches[j].weight = t;
        j = (++j) % 3;
        if (j == 0)
            i++;
    }
}

Graph::Graph(std::vector<std::vector<int>> matrix)
{
    this->size = matrix.size();
    nodes.resize(size);
    for (ptrdiff_t i = 0; i < size; i++)
        nodes[i].branches.resize(size);
    for (ptrdiff_t i = 0; i < size; i++)
    {
        nodes[i].start_value(i);
        for (ptrdiff_t j = 0; j < size; j++)
        {
            nodes[i].branches[j].index = j;
            nodes[i].branches[j].weight = matrix[i][j];
        }
    }
}

std::vector<int> Graph::dfs(int start_index, int end_index)
{
    std::vector<Node> visited;
    result.resize(size);
    nodes[start_index].visited = true;
    Stack.push(nodes[start_index]);
    do
    {
        visited.push_back(Stack.top());
        Node temp = Stack.top();
        Stack.pop();
        for (auto& branch : temp.branches)
        {
            if (branch.weight != 0 && !nodes[branch.index].visited)
            {
                nodes[branch.index].prevInd = temp.id;
                nodes[branch.index].visited = true;
                Stack.push(nodes[branch.index]);
            }
        }
        result[visited.back().id] = nodes[visited.back().id].prevInd;
    } while (!Stack.empty());
    for (auto& node : nodes)
    {
        if (!node.visited)
        {
            dfs(node.id, end_index);
        }
    }
    return shortest_path(end_index);
}

std::vector<std::vector<int>> adjacency_matrix(size_t size)
{
    std::vector<std::vector<int>> matrix;
    matrix.resize(size);
    for (ptrdiff_t i = 0; i < size; i++)
    {
        matrix[i].resize(size);
    }
    for (ptrdiff_t i = 0; i < size; i++)
    {
        for (ptrdiff_t j = i + 1; j < size; j++)
        {
            std::cout << "Input " << i << '-' << j << ": ";
            std::cin >> matrix[i][j];
            matrix[j][i] = matrix[i][j];
        }
    }
    return matrix;
}

int main()
{
    setlocale(LC_ALL, "rus");
    int size, start_ind, end_ind;
    std::cout << "Введите количество вершин: ";
    std::cin >> size;
    Graph graph(adjacency_matrix(size));
    std::cout << "Введите начальный индекс: ";
    std::cin >> start_ind;
    std::cout << "Введите конечный индекс: ";
    std::cin >> end_ind;
    for (auto DFS : graph.dfs(start_ind, end_ind))
    {
        std::cout << DFS << ' ';
    }
}