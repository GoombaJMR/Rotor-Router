//-----------------------------------------------//
//  RotorRouterMechanism v2
//  Created by Julian M. Rice | July 2018
//-----------------------------------------------//

// LIBRARIES & NAMESPACE ------------------------//
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;
int randomInteger(int min, int max);

// CLASSES --------------------------------------//
class Vertex;

class Edge {
public:
    Edge(Vertex* start, Vertex* destination);
    void incrementVisitCount()          { visitCount++; }
    void changeStartVertex(Vertex* s)   { m_start = s; }
    void changeEndVertex(Vertex* e)     { m_destination = e; }
    int getVisitCount()         { return visitCount; }
    Vertex* getStartVertex()    { return m_start; }
    Vertex* getEndVertex()      { return m_destination; }
private:
    int visitCount;
    Vertex* m_start;
    Vertex* m_destination;
};

Edge::Edge(Vertex* start, Vertex* destination) {
    m_start = start;
    m_destination = destination;
    visitCount = 0;
}
//--------------------------------------------
class Vertex {
public:
    Vertex(string name, int index, int visitedCount, int edgeCount);
    void addEdge(Vertex* dest);
    void setIndex(int edgeCount);
    void incrementVisited() { m_visitedCount++; }
    void changeIndex()      { m_index = (m_index + 1) % m_edgeCount; } //Core component of the RR Mechanism
    void printStatus();
    void printEdges();
    
    //Accessor Member Functions
    int getIndex()          { return m_index; }
    int getVisited()        { return m_visitedCount; }
    int getEdgeCount()      { return m_edgeCount; }
    string getName()        { return m_name; }
    Edge edgeToCross(Vertex* vertex, int index)    { return vertex->edges[index]; }
private:
    int m_index;
    int m_visitedCount;
    int m_edgeCount;
    string m_name;
    vector<Edge> edges;
};

Vertex::Vertex(string name, int index, int visitedCount, int edgeCount) {
    m_name = name;
    m_index = index;
    m_visitedCount = visitedCount;
    m_edgeCount = edgeCount;
}

void Vertex::addEdge(Vertex* dest) {
    Edge newEdge(this, dest);
    edges.push_back(newEdge);
    m_edgeCount++;
}

void Vertex::setIndex(int edgeCount) {
    m_index = randomInteger(0, edgeCount-1);
}

void Vertex::printStatus() {
    string pointingTo = edges[m_index].getEndVertex()->getName();
    cout << "----------------------------" << endl;
    cout << "-- VERTEX " << m_name << endl;
    cout << "-- Degree: " << m_edgeCount << endl;
    cout << "-- Times Visited: " << m_visitedCount << endl;
    cout << "-- Pointing to: " << m_index << " (VERTEX " << pointingTo << ")" << endl;
    //cout << "----------------------------" << endl;
}

void Vertex::printEdges() {
    //cout << "----------------------------" << endl;
    cout << "   | Edges of VERTEX " << m_name << " |" << endl;
    for (int i = 0; i < edges.size(); i++) {
        Edge e = edges[i];
        cout << "-- Edge " << i+1 << ": ";
        cout << e.getEndVertex()->getName() << " | VISITS: " << e.getVisitCount() << endl;
    }
    cout << endl;
}

//--------------------------------------------
class Graph {
public:
    Graph() {}
    void insertVertex(Vertex* vertex);
    Vertex* returnVertex(int index) {  return vertices[index]; }
    Vertex* randomVertex();
    int getVertexCount() { return vertices.size(); }
    void printGraph();
private:
    vector<Vertex*> vertices;
};

void Graph::insertVertex(Vertex* vertex) {
    vertices.push_back(vertex);
}

Vertex* Graph::randomVertex() {
    unsigned long numOfVertices = vertices.size();
    int randomId = randomInteger(0, numOfVertices-1);
    return vertices[randomId];
}

void Graph::printGraph() {
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i]->printStatus();
        vertices[i]->printEdges();
    }
}

// FUNCTION PROTOTYPES ------------------------//
int instructions();
int testInstructions();
void quasiWalk(int steps, Graph g, Vertex* s, double results[]);
Vertex* mobileAgent(Graph graph, Vertex* start, int iterations);
void testGraph1(Graph& g);
void testGraph2(Graph& g);

//
int main(int argc, const char * argv[]) {
    Graph g;
    //testGraph2(test);
    Vertex A = Vertex("A", 0, 0, 0); Vertex B = Vertex("B", 0, 0, 0);
    Vertex C = Vertex("C", 0, 0, 0); Vertex D = Vertex("D", 0, 0, 0);
    Vertex E = Vertex("E", 0, 0, 0); Vertex F = Vertex("F", 0, 0, 0);
    Vertex *Ap = &A; Vertex *Bp = &B; Vertex *Cp = &C;
    Vertex *Dp = &D; Vertex *Ep = &E; Vertex *Fp = &F;
    A.addEdge(Bp);  A.addEdge(Cp);  A.addEdge(Dp);  A.addEdge(Ep);
    B.addEdge(Ap);  B.addEdge(Cp);  B.addEdge(Dp);
    C.addEdge(Ap);  C.addEdge(Bp);  C.addEdge(Dp);  C.addEdge(Fp);
    D.addEdge(Ap);  D.addEdge(Bp);  D.addEdge(Ep);  D.addEdge(Fp);
    E.addEdge(Ap);  E.addEdge(Cp);  E.addEdge(Dp);  E.addEdge(Fp);
    F.addEdge(Cp);  F.addEdge(Dp);  F.addEdge(Ep);
    A.setIndex(A.getEdgeCount()); B.setIndex(B.getEdgeCount());
    C.setIndex(C.getEdgeCount()); D.setIndex(D.getEdgeCount());
    E.setIndex(E.getEdgeCount()); F.setIndex(F.getEdgeCount());
    g.insertVertex(Ap); g.insertVertex(Bp); g.insertVertex(Cp);
    g.insertVertex(Dp); g.insertVertex(Ep); g.insertVertex(Fp);
    
    
    double arrayOfResults[10] = { 0,0,0,0,0,0,0,0,0,0 };
    int graphSize = g.getVertexCount();
    int input = instructions();
    int tests = testInstructions();
    
    for (int i = 0; i < tests; i++) {
        Vertex* randomStart = g.randomVertex();
        quasiWalk(input, g, randomStart, arrayOfResults);
    }
    
    cout << "-RESULTS--------------------------" << endl;
    cout << "-Number of STEPS per TEST: " << input << endl;
    cout << "-Number of TESTS: " << tests << endl;
    
    for (int i = 0; i < graphSize; i++) {
        arrayOfResults[i] /= tests;
        cout << "  Average Visited Count for Vertex " << g.returnVertex(i)->getName() << ": " << arrayOfResults[i] << endl;
    }
    
    cout << "-END------------------------------" << endl << endl;
    
    return 0;
}

// FUNCTIONS ------------------------//
int randomInteger(int min, int max) {
    if (max < min)
        swap(max, min);
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

int instructions() {
    int trips;
    cout << "[Console] Please input the number of times the mobile agent moves: ";
    cin >> trips;
    return trips;
}

int testInstructions() {
    int testCount;
    cout << "[Console] Please input the number of times the test will be run: ";
    cin >> testCount;
    return testCount;
}

Vertex* mobileAgent(Graph graph, Vertex* start, int iterations) {
    Vertex* destination = NULL;
    for (int i = 0; i < iterations; i++) {
        int currentIndex = start->getIndex();
        start->edgeToCross(start, currentIndex).incrementVisitCount();
        //cout << start->edgeToCross(start, currentIndex).getVisitCount() << endl;
        Edge cross = start->edgeToCross(start, currentIndex);
        destination = cross.getEndVertex();
    
        cout << "[Step " << i+1 << "] Agent crosses the EDGE (between) "
             << cross.getStartVertex()->getName() << " and " << cross.getEndVertex()->getName()
             << " and is now at VERTEX " << cross.getEndVertex()->getName() << endl;
        
        destination->incrementVisited();
        start->changeIndex();
        start = destination;
    }
    return destination;
}

void quasiWalk(int steps, Graph g, Vertex* s, double results[]) {
    int graphVertexCount = g.getVertexCount();
    mobileAgent(g, s, steps);
    for (int i = 0; i < graphVertexCount; i++) {
        results[i] += g.returnVertex(i)->getVisited();
    }
    g.printGraph();
}

//--------------------------------------------
void testGraph1(Graph& g) {
    Vertex A = Vertex("A", 0, 0, 0);
    Vertex B = Vertex("B", 0, 0, 0);
    Vertex C = Vertex("C", 0, 0, 0);
    Vertex D = Vertex("D", 0, 0, 0);
    Vertex *Ap = &A;
    Vertex *Bp = &B;
    Vertex *Cp = &C;
    Vertex *Dp = &D;
    A.addEdge(Bp);
    A.addEdge(Cp);
    A.addEdge(Dp);
    B.addEdge(Ap);
    B.addEdge(Cp);
    B.addEdge(Dp);
    C.addEdge(Ap);
    C.addEdge(Bp);
    D.addEdge(Ap);
    D.addEdge(Bp);
    A.setIndex(A.getEdgeCount());
    B.setIndex(B.getEdgeCount());
    C.setIndex(C.getEdgeCount());
    D.setIndex(D.getEdgeCount());
    g.insertVertex(Ap);
    g.insertVertex(Bp);
    g.insertVertex(Cp);
    g.insertVertex(Dp);
}

void testGraph2(Graph& g) {
    Vertex A = Vertex("A", 0, 0, 0);
    Vertex B = Vertex("B", 0, 0, 0);
    Vertex C = Vertex("C", 0, 0, 0);
    Vertex D = Vertex("D", 0, 0, 0);
    Vertex E = Vertex("E", 0, 0, 0);
    Vertex F = Vertex("F", 0, 0, 0);
    Vertex *Ap = &A;
    Vertex *Bp = &B;
    Vertex *Cp = &C;
    Vertex *Dp = &D;
    Vertex *Ep = &E;
    Vertex *Fp = &F;
    A.addEdge(Bp);
    A.addEdge(Cp);
    A.addEdge(Dp);
    A.addEdge(Ep);
    B.addEdge(Ap);
    B.addEdge(Cp);
    B.addEdge(Dp);
    C.addEdge(Ap);
    C.addEdge(Bp);
    C.addEdge(Dp);
    C.addEdge(Fp);
    D.addEdge(Ap);
    D.addEdge(Bp);
    D.addEdge(Ep);
    D.addEdge(Fp);
    E.addEdge(Ap);
    E.addEdge(Cp);
    E.addEdge(Dp);
    E.addEdge(Fp);
    F.addEdge(Cp);
    F.addEdge(Dp);
    F.addEdge(Ep);
    A.setIndex(A.getEdgeCount());
    B.setIndex(B.getEdgeCount());
    C.setIndex(C.getEdgeCount());
    D.setIndex(D.getEdgeCount());
    E.setIndex(E.getEdgeCount());
    F.setIndex(F.getEdgeCount());
    g.insertVertex(Ap);
    g.insertVertex(Bp);
    g.insertVertex(Cp);
    g.insertVertex(Dp);
    g.insertVertex(Ep);
    g.insertVertex(Fp);
}