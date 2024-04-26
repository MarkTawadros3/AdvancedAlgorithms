#include <iostream>
#include <list>

using namespace std;

class Graph {
    int numVertices;
    list<int>* adjLists;
    bool* visited;
    list<int> finished;

    public:

        Graph(int sizeOfGraph) {
            numVertices = sizeOfGraph;
            adjLists = new list<int>[sizeOfGraph];
            visited = new bool[sizeOfGraph];
        }

        void addEdge(int vertex1, int vertex2) {
            adjLists[vertex1].push_back(vertex2);
        }

        void executeDFS() {
            for (int i = 0; i < numVertices; i++) {
                if (!visited[i]) {
                    depthFirstSearch(i);
                }
            }
            transposeGraph();
            for (int x = 0; x < numVertices; x++) {
                visited[x] = false;
            }
            int c = 1;
            list<int>::reverse_iterator y;
            for (y = finished.rbegin(); y != finished.rend(); y++) {
                if (!visited[*y]) {
                    cout << "Group #" << c << ": {";
                    transposeDFS(*y);
                    cout << "}\n";
                    c++;
                }
            }
        }

        void depthFirstSearch(int vertex) {
            visited[vertex] = true;
            list<int> adjList = adjLists[vertex];
            list<int>::iterator adjvert;
            for (adjvert = adjList.begin(); adjvert != adjList.end(); ++adjvert) {
                if (!visited[*adjvert]) {
                    depthFirstSearch(*adjvert);
                }
            }
            finished.push_back(vertex);
        }

        void transposeGraph() {
            list<int>* newAdjLists = new list<int>[numVertices];
            for (int i = 0; i < numVertices; i++) {
                list<int>::iterator j;
                for (j = adjLists[i].begin(); j != adjLists[i].end(); ++j) {
                    newAdjLists[*j].push_front(i);
                }
            }
            for (int i = 0; i < numVertices; i++) {
                adjLists[i].clear();
                list<int>::iterator j;
                for (j = newAdjLists[i].begin(); j != newAdjLists[i].end(); ++j) {
                    adjLists[i].push_front(*j);
                }
            }
            delete[] newAdjLists;
        }

        void transposeDFS(int v) {
            visited[v] = true;
            list<int> adjList = adjLists[v];
            cout << v << " ";
            list<int>::iterator a;
            for (a = adjList.begin(); a != adjList.end(); ++a) {
                if (!visited[*a]) {
                    transposeDFS(*a);
                }
            }
        }
};

int main() {
    Graph g(11);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 0);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 3);
    g.addEdge(6, 5);
    g.addEdge(6, 7);
    g.addEdge(7, 8);
    g.addEdge(8, 9);
    g.addEdge(9, 6);
    g.addEdge(9, 10);
    g.executeDFS();
    return 0;
}