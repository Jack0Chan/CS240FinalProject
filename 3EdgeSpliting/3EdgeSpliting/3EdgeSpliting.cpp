#include <iostream>
#include <vector>
#include <map>

using namespace std;

class EdgeSplitter
{
public:
    long numVertices;
    // use set to map the vertices
    map<long, long> vertexMap;
    vector<vector<long>> inputEdges = {};
    // simple for bi-color checking
    vector<vector<long>> originGraph;
    // graph in matrix format
    // simple for floyd
    // there are at most 200 vertices XXXXXX :(
    // we do not know whether the name of the nodes 
    // are continuous
    vector<vector<long>> matrixGraph;
    vector<vector<long>> floydGraph;
    long diameter = 0;
    vector<long> vertexColor;

    void ReadInput();
    void OutputOriginGraph();
    void OutputFloyd();
    bool BiColorVertex(long vertex, int colorID);
    bool IsBipartite();
    long GetDiameter();
    void Floyd();
    void SplitEdges();
};

void EdgeSplitter::ReadInput()
{
    // 看错题了第一行输入搞错了，我吐了de了好久的bug
    int n1, n2;
    cin >> n1 >> n2;
    // 我tm以为第一行也是一个边
    long node1, node2;
    while (cin >> node1 >> node2)
    {
        inputEdges.push_back({ node1, node2 });
        if (vertexMap.count(node1) == 0) vertexMap[node1] = vertexMap.size();
        if (vertexMap.count(node2) == 0) vertexMap[node2] = vertexMap.size();
    }

    numVertices = (long)vertexMap.size();
    originGraph = vector<vector<long>>(numVertices);
    matrixGraph = vector<vector<long>>(numVertices, vector<long>(numVertices));
    vertexColor = vector<long>(numVertices);

    for (long e = 0; e < (long)inputEdges.size(); e++)
    {
        node1 = vertexMap[inputEdges[e][0]];
        node2 = vertexMap[inputEdges[e][1]];
        matrixGraph[node1][node2] = 1;
        matrixGraph[node2][node1] = 1;
    }

    for (long i = 0; i < numVertices; i++)
    {
        for (long j = 0; j < numVertices; j++)
        {
            if (matrixGraph[i][j] == 1) originGraph[i].push_back(j);
        }
    }
}

void EdgeSplitter::OutputOriginGraph()
{
    for (long i = 0; i < numVertices; i++)
    {
        for (long j = 0; j < numVertices; j++)
        {
            cout << matrixGraph[i][j];
        }
        cout << endl;
    }
}

void EdgeSplitter::OutputFloyd()
{
    for (long i = 0; i < numVertices; i++)
    {
        for (long j = 0; j < numVertices; j++)
        {
            cout << floydGraph[i][j] << " ";
        }
        cout << endl;
    }
}

// color the graph with two colors
// two colors 1 and -1, because origin are set 0
bool EdgeSplitter::BiColorVertex(long vertexID, int colorID)
{
    // first color current vertex
    vertexColor[vertexID] = colorID;
    // check all neibor nodes
    // cout << "size: " << originGraph[vertex].size() << endl;
    long v;
    for (long i = 0; i < (long)originGraph[vertexID].size(); i++)
    {
        v = originGraph[vertexID][i];
        // cout << "i: " << i << " v: " << v << endl;
        // if have the same color, not bipartite
        if (vertexColor[v] == colorID) return false;
        // if not colored, try to give it an inverse color
        if ((vertexColor[v] == 0) && !BiColorVertex(v, -colorID)) return false;
        // if all the checkings above are finished
    }
    return true;
}

// the graph satisfies edge splliting iff it is bipartite
bool EdgeSplitter::IsBipartite()
{
    return BiColorVertex(0, 1);
}

// reference: baidubaike
void EdgeSplitter::Floyd()
{
    floydGraph = vector<vector<long>>(numVertices, vector<long>(numVertices, numVertices+1));
    // deep copy
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            if (matrixGraph[i][j] == 1) floydGraph[i][j] = 1;
        }
        floydGraph[i][i] = 0;
    }

    for (long k = 0; k < numVertices; k++)
    {
        for (long i = 0; i < numVertices; i++)
        {
            for (long j = 0; j < numVertices; j++)
            {
                if (floydGraph[i][j] > floydGraph[i][k] + floydGraph[k][j])
                {
                    floydGraph[i][j] = floydGraph[i][k] + floydGraph[k][j];
                }
            }
        }
    }

    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            diameter = max(diameter, floydGraph[i][j]);
        }
    }
}

long EdgeSplitter::GetDiameter()
{
    return diameter;
}

void EdgeSplitter::SplitEdges()
{
    if (!IsBipartite())
    {
        // floydGraph[numVertices + 10][numVertices + 10] = 9999;
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
    edgeSplitter.Floyd();
    // edgeSplitter.OutputOriginGraph();
    // edgeSplitter.OutputFloyd();
    // cout << "isBipartite: " << edgeSplitter.IsBipartite() << endl;
    edgeSplitter.SplitEdges();
    return 0;
}
