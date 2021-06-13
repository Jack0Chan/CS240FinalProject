import sys

class Pipes:
    # origing matrix graph
    originGraph = []
    # number of nodes
    n = 0
    # max costs
    k = 0
    # flow graph
    # each element is an edge 
    # [0from, 1to ,2capacity, 3flow, 4cost]
    flowEdges = []
    # flow graph
    # edge relations
    flowGraph = []
    # [0d, 1inq, 2p, 3a]
    spfaList = []
    # flow & cost
    flow = 0
    cost = 0
    num_of_deges = 0

    # matrix graph is a list [[]]
    def __init__(self, adjMatrix, num_n, num_k):
        self.originGraph = adjMatrix
        self.n = num_n
        self.k = num_k
        self.flowGraph = [-1 for _ in range(n)]
        self.flowEdges = [[-1, 0, 0, 0, 0] for _ in range(10000)]

    # add an edge
    # we need to add edges in two directions
    # with opposite costs without flow
    # [0from, 1to ,2capacity, 3flow, 4cost]
    def AddEdge(self, s, t, capacity, flow, cost):
        # positive direction
        self.flowEdges[self.num_of_deges] = [self.flowGraph[s], t, capacity, flow, cost]
        # opposite direction
        self.flowEdges[self.num_of_deges + 1] = ([self.flowGraph[t], s, 0, 0, -cost])
        self.flowGraph[s] = self.num_of_deges
        self.flowGraph[t] = self.num_of_deges + 1
        # we add two edges
        self.num_of_deges += 2

    # build FlowGraph
    def BuildFlowGraph(self):
        # print("start build flow graph")
        for i in range(self.n):
            for j in range(self.n):
                # if has pipe
                if self.originGraph[i][j] > 0:
                    self.AddEdge(i, j, self.originGraph[i][j], self.originGraph[i][j], 0)
                    self.AddEdge(i, j, self.k, self.k, 1)
        # print("finish build flow graph")


    # Shortest Path Faster Algorithm
    # search from node 0
    def SPFA(self):
        # print("===============start SPFA==================")
        # [0d, 1inq, 2p, 3a]
        self.spfaList = [[float('inf'), 0, -1, 0] for _ in range(self.n + 1)]
        self.spfaList[0][0] = 0
        for i in range(100): self.spfaList.append([0, 0, 0, 0])

        queue = [0]
        while (len(queue) != 0):
            # find from initial node 0
            edgeID = queue.pop(0)
            flag = self.flowGraph[edgeID]
            # print("u:", u)
            while (flag > -1):
                # print("flag: ", flag)
                # [0from, 1to ,2capacity, 3flow, 4cost]
                e = self.flowEdges[flag]
                # print("edge from {} to {}".format(e[0], e[1]))
                # [0d, 1inq, 2p, 3a]
                # print("eiflow: {} dei: {} du: {}  eicost {}".format(e[3], self.spfaList[e[1]][0], self.spfaList[u][0], e[4]))
                # print("ei_from: {} ei_to: {}".format(e[0], e[1]) )
                if (e[3] > 0) and (self.spfaList[e[1]][0] > self.spfaList[edgeID][0] + e[4]):
                     self.spfaList[e[1]][0] = self.spfaList[edgeID][0] + e[4]
                     # print("du: {} cost: {}".format(self.spfaList[u][0], e[4]))
                     self.spfaList[e[1]][2] = flag
                     queue.append(e[1])
                # print("spfaList")
                # for i in range(6):
                #     print(self.spfaList[i])
                flag = e[0]
        # print(len(self.spfaList[2]))
        if self.spfaList[self.n - 1][2] != -1:
            # print("=================finish SPFA=================")
            return True
        else:
            return False

    def Piper(self):
        while(self.SPFA()):
            tmp = float('inf')
            x = self.spfaList[self.n - 1][2]
            # print("x: ", x)
            while(x > -1):
                # [0from, 1to ,2capacity, 3flow, 4cost]
                tmp = min(tmp, self.flowEdges[x][3])
                # [0d, 1inq, 2p, 3a]
                # print("theMin1", tmp)
                # print("edge: {} ".format(self.flowEdges[x]))
                x = self.spfaList[self.flowEdges[x^1][1]][2]
                # print("x: ", x)
            # print("first while finished")
            # if run out of k
            # we just take the upper bound of k
            if (self.cost + self.spfaList[self.n - 1][0] * tmp > self.k):
                self.flow = self.flow + (self.k - self.cost)/self.spfaList[self.n - 1][0]
                return
            else:
                self.flow = self.flow + tmp
                self.cost = self.cost + self.spfaList[self.n - 1][0] * tmp


            x = self.spfaList[self.n - 1][2]
            while(x > -1):
                self.flowEdges[x][2] = self.flowEdges[x][3] + tmp
                self.flowEdges[x][3] = self.flowEdges[x][3] - tmp
                self.flowEdges[x^1][3] = self.flowEdges[x^1][3] + tmp
                x = self.spfaList[self.flowEdges[x^1][1]][2]
                # print("theMin2: ", tmp)
                # print("edge: {} ".format(self.flowEdges[x]))
            # print("second while finished")


    def PirntOriginGraph(self):
        for line in self.originGraph:
            print(line)

       
# 5 7
# 0 1 0 2 0
# 0 0 4 10 0
# 0 0 0 0 5
# 0 0 0 0 10
# 0 0 0 0 0
# here n=5, k=7
def GetInput():
    s = sys.stdin.readline()
    [num_n, num_k] = list(map(int, s.split()))

    inputGraph = []
    for i in range(num_n):
        line = sys.stdin.readline()
        line = list(map(int, line.split()))
        inputGraph.append(line)
    return [inputGraph, num_n, num_k]

    

if __name__ == '__main__':
    # read input
    [graph, n, k] = GetInput()
    pipes = Pipes(graph, n, k)
    # pipes.PirntOriginGraph()
    pipes.BuildFlowGraph()
    # print(pipes.flowGraph)
    # [0from, 1to ,2capacity, 3flow, 4cost]
    # for fr, t, c, f, cos in pipes.flowEdges:
    #     print("ei_from {} ei_to {} flow {} cost {}".format(fr, t, f, cos))
    pipes.Piper()
    print(int(pipes.flow))
