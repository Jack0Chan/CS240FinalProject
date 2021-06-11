#include <iostream>
#include <map>
#include <vector>

using namespace std;

class EdgeSplitter
{
public:
    // graph in dict format
    // simple for bi-color checking
    map<int, vector<int>> originGraph;
    // graph in matrix format
    // simple for floyd
    // there are at most 200 vertices
    // we do not know whether the name of the nodes 
    // are continuous
    vector<vector<int>> matrixGraph(200, vector<int>(200));
    vector<vector<int>> floydGraph;
    int diameter = 0;
    vector<int> vertexColor(200);

    void ReadInput();
    void OutputOriginGraph();
    bool BiColorVertex(int vertex, int colorID);
    bool IsBipartite();
    int GetDiameter();
    void Floyd();
    void SplitEdges();
};

void EdgeSplitter::ReadInput()
{
    int node1, node2;
    while (cin >> node1 >> node2)
    {
        if (originGraph.count(node1) == 0) originGraph.insert({ node1, {} });
        if (originGraph.count(node2) == 0) originGraph.insert({ node2, {} });
        originGraph[node1].push_back(ndoe2);
        originGraph[node2].push_back(ndoe1);
    }
}

void EdgeSplitter::OutputOriginGraph()
{
    map<int, vector<int>>::const_iterator it;
    for (it = originGraph.begin(); it != originGraph.end(); ++it) {
        cout << "node: " << it->first << " neibor: " << it->second << endl;
    }
}

// color the graph with two colors
// two colors 1 and -1, because origin are set 0
bool EdgeSplitter::BiColorVertex(int vertex, int colorID)
{
    // first color current vertex
    vertexColor[vertex] = colorID;
    // check all neibor nodes
    for (v in originGraph[vertex])
    {
        // if have the same color, not bipartite
        if (color[v] == colorID) return false;
        // if not colored, try to give it an inverse color
        if (color[v] == 0 && !ColorVertex(v, -colorID)) return false;
        // if all the checkings above are finished
        return true;
    }
}

// the graph satisfies edge splliting iff it is bipartite
bool EdgeSplitter::IsBipartite()
{
    return BiColorVertex(0, 1);
}

// reference: https://baike.baidu.com/item/Floyd%E7%AE%97%E6%B3%95
void EdgeSplitter::Floyd()
{
    // deep copy
    floydGraph.assign(matrixGraph.begin(), matrixGraph.end());
    for (int k = 0; k < 200; k++) 
    {
        for (int i = 0; i < 200; i++)
        {
            for (int j = 0; j < 200; j++)
            {
                if (floydGraph[i][j] > floydGraph[i][k] + floydGraph[k][j])
                {
                    floydGraph[i][j] = floydGraph[i][k] + floydGraph[k][j];
                    // update diameter
                    diameter = max(diameter, floydGraph[i][j]);
                }
            }
        }
    }
}

int EdgeSplitter::GetDiameter()
{
    return diameter;
}

void EdgeSplitter::SplitEdges()
{
    if !IsBipartite()
    {
        cout << -1 << endl;
    }
    else
    {
        cout << GetDiameter() + 1 << endl;
    }
}

int main()
{
    EdgeSplitter edgeSplitter;
    edgeSplitter.ReadInput();
    edgeSplitter.SplitEdges();
    return 0;
}
