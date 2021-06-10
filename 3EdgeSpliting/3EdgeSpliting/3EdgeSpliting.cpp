#include <iostream>
#include<vector>

using namespace std;

class EdgeSplitter
{
public:
    vector<vector<int>> originGraph;

    void ReadInput();
};

void EdgeSplitter::ReadInput()
{
    int node1, node2;
    while (cin >> node1 >> node2)
    {
        originGraph.push_back({ node1, node2 });
    }
}

int main()
{
    EdgeSplitter edgeSplitter;
    edgeSplitter.ReadInput();
    return 0;
}
