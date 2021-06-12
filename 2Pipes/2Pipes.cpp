#include <iostream>
#include <vector>

using namespace std;

class Pipes
{
public:
    vector<vector<int>> originGraph;
    int k;
    // number of nodes
    int n;
    // edge: 
    // 0: from, 
    // 1: to ,
    // 2: capacity, 
    // 3: flow, 
    // 4: cost
    vector<vector<int>> flowGraph;

    void ReadInput();
    void AddEdge();
    bool SPFA();
    void MinCostMaxFlow();
    void OutputoriginGraph();
};

void Pipes::ReadInput()
{
    int num_n, num_k;
    cin >> num_n >> num_k;
    // read and store n and k
    n = num_n;
    k = num_k;
    // read the graph
    int width;
    originGraph = vector<vector<int>>(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> width;
            originGraph[i][j] = width;
        }
    }
}

void AddEdge()
{

}
// shortest path faster algorithm
// reference: wiki
bool Pipes::SPFA()
{

}

void Pipes::MinCostMaxFlow()
{

}

void Pipes::OutputoriginGraph()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << originGraph[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    Pipes pipes;
    pipes.ReadInput();
    pipes.OutputoriginGraph();
    return 0;
}