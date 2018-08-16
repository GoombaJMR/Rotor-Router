//-----------------------------------------------//
//  RotorRouterMechanism v3
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
    Edge(Vertex* start, Vertex* destination, int id, string name);
    void incrementVisitCount()          { visitCount++; }
    void resetVisitCountEdge()          { visitCount = 0; }
    void changeStartVertex(Vertex* s)   { m_start = s; }
    void changeEndVertex(Vertex* e)     { m_destination = e; }
    int getVisitCount()         { return visitCount; }
    int getID()                 { return m_id; }
    string getName()            { return m_name; }
    Vertex* getStartVertex()    { return m_start; }
    Vertex* getEndVertex()      { return m_destination; }
private:
    int visitCount;
    int m_id;
    string m_name;
    Vertex* m_start;
    Vertex* m_destination;
};

Edge::Edge(Vertex* start, Vertex* destination, int id, string name) {
    m_start = start;
    m_destination = destination;
    m_id = id;
    m_name = name;
    visitCount = 0;
}
//--------------------------------------------
class Vertex {
public:
    Vertex(string name, int index, int visitedCount, int edgeCount);
    void addEdge(Edge* newEdge);
    void setIndex(int edgeCount);
    void setVisitToZero()   { m_visitedCount = 0; }
    void incrementVisited() { m_visitedCount++; }
    void changeIndex()      { m_index = (m_index + 1) % m_edgeCount; } //Core component of the RR Mechanism
    void resetAllEdgeVisits();
    void printStatus();
    void printEdges();
    int getIndex()          { return m_index; }
    int getVisited()        { return m_visitedCount; }
    int getEdgeCount()      { return m_edgeCount; }
    string getName()        { return m_name; }
    Edge* returnEdge(int num)   { return edges[num]; }
    Edge* edgeToCross(Vertex* vertex, int index)    { return vertex->edges[index]; }
private:
    int m_index;
    int m_visitedCount;
    int m_edgeCount;
    string m_name;
    vector<Edge*> edges;
};

Vertex::Vertex(string name, int index, int visitedCount, int edgeCount) {
    m_name = name;
    m_index = index;
    m_visitedCount = visitedCount;
    m_edgeCount = edgeCount;
}

void Vertex::addEdge(Edge* newEdge) {
    edges.push_back(newEdge);
    m_edgeCount++;
}

void Vertex::resetAllEdgeVisits() {
    for (int i = 0; i < m_edgeCount; i++) {
        edges[i]->resetVisitCountEdge();
    }
}

void Vertex::setIndex(int edgeCount) {
    m_index = randomInteger(0, edgeCount-1);
}

void Vertex::printStatus() {
    string pointingTo = edges[m_index]->getEndVertex()->getName();
    cout << "----------------------------" << endl;
    cout << "-- VERTEX " << m_name << endl;
    cout << "-- Degree: " << m_edgeCount << endl;
    cout << "-- Times Visited: " << m_visitedCount << endl;
    cout << "-- Pointing to: " << m_index << " (VERTEX " << pointingTo << ")" << endl;
}

void Vertex::printEdges() {
    //cout << "----------------------------" << endl;
    cout << "   | Edges of VERTEX " << m_name << " |" << endl;
    for (int i = 0; i < edges.size(); i++) {
        Edge* e = edges[i];
        cout << "-- Edge " << i+1 << ": ";
        cout << e->getEndVertex()->getName() << endl;
    }
    cout << endl;
}

//--------------------------------------------
class Graph {
public:
    Graph(int edgeCount) { m_edgeCount = edgeCount; }
    void insertVertex(Vertex* vertex);
    void insertEdge(Edge* edge);
    Vertex* returnVertex(int index) {  return vertices[index]; }
    Vertex* randomVertex();
    int getVertexCount() { return vertices.size(); }
    int getEdgeCount()   { return m_edgeCount; }
    void printGraph();
private:
    int m_edgeCount;
    vector<Vertex*> vertices;
    vector<Edge*> edges;
    vector<Edge*> eulerCycle; //New Data Structure
};

void Graph::insertVertex(Vertex* vertex) {
    vertices.push_back(vertex);
}

void Graph::insertEdge(Edge* edge) {
    edges.push_back(edge);
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
void quasiWalk(int steps, Graph g, Vertex* s, double resultsV[], double resultsE[]);
Vertex* mobileAgent(Graph graph, Vertex* start, int iterations);
void testGraph1(Graph& g);
void testGraph2(Graph& g);

int main(int argc, const char * argv[]) {
    Graph g(11);
    //testGraph2(test);
    Vertex A = Vertex("A", 0, 0, 0); Vertex B = Vertex("B", 0, 0, 0);
    Vertex C = Vertex("C", 0, 0, 0); Vertex D = Vertex("D", 0, 0, 0);
    Vertex E = Vertex("E", 0, 0, 0); Vertex F = Vertex("F", 0, 0, 0);
    Vertex *Ap = &A; Vertex *Bp = &B; Vertex *Cp = &C;
    Vertex *Dp = &D; Vertex *Ep = &E; Vertex *Fp = &F;
    
    Edge e1a(Ap, Bp, 0, "AB"); Edge e2a(Ap, Cp, 1, "AC"); Edge e3a(Ap, Dp, 2, "AD"); Edge e4a(Ap, Ep, 3, "AE");
    Edge e1b(Bp, Ap, 0, "AB"); Edge e5a(Bp, Cp, 4, "BC"); Edge e6a(Bp, Dp, 5, "BD");
    Edge e2b(Cp, Ap, 1, "AC"); Edge e5b(Cp, Bp, 4, "BC"); Edge e7a(Cp, Ep, 6, "CE"); Edge e8a(Cp, Fp, 7, "CF");
    Edge e3b(Dp, Ap, 2, "AD"); Edge e6b(Dp, Bp, 5, "BD"); Edge e9a(Dp, Ep, 8, "DE"); Edge e10a(Dp, Fp, 9, "DF");
    Edge e4b(Ep, Ap, 3, "AE"); Edge e7b(Ep, Cp, 6, "CE"); Edge e9b(Ep, Dp, 8, "DE"); Edge e11a(Ep, Fp, 10, "EF");
    Edge e8b(Fp, Cp, 7, "CF"); Edge e10b(Fp, Dp, 9, "DF"); Edge e11b(Fp, Ep, 10, "EF");
    
    Edge* e1aP = &e1a;  Edge* e1bP = &e1b;   Edge* e2aP = &e2a; Edge* e2bP = &e2b;
    Edge* e3aP = &e3a;  Edge* e3bP = &e3b;   Edge* e4aP = &e4a; Edge* e4bP = &e4b;
    Edge* e5aP = &e5a;  Edge* e5bP = &e5b;   Edge* e6aP = &e6a; Edge* e6bP = &e6b;
    Edge* e7aP = &e7a;  Edge* e7bP = &e7b;   Edge* e8aP = &e8a; Edge* e8bP = &e8b;
    Edge* e9aP = &e9a;  Edge* e9bP = &e9b;   Edge* e10aP = &e10a; Edge* e10bP = &e10b;
    Edge* e11aP = &e11a; Edge* e11bP = &e11b;
    Edge* edgeList[11] = { e1aP, e2aP, e3aP, e4aP, e5aP, e6aP, e7aP, e8aP, e9aP, e10aP, e11aP };
    
    A.addEdge(e1aP);  A.addEdge(e2aP);  A.addEdge(e3aP);  A.addEdge(e4aP);
    B.addEdge(e1bP);  B.addEdge(e5aP);  B.addEdge(e6aP);
    C.addEdge(e2bP);  C.addEdge(e5bP);  C.addEdge(e7aP);  C.addEdge(e8aP);
    D.addEdge(e3bP);  D.addEdge(e6bP);  D.addEdge(e9aP);  D.addEdge(e10aP);
    E.addEdge(e4bP);  E.addEdge(e7bP);  E.addEdge(e9bP);  E.addEdge(e11aP);
    F.addEdge(e8bP);  F.addEdge(e10bP);  F.addEdge(e11bP);
    
    A.setIndex(A.getEdgeCount()); B.setIndex(B.getEdgeCount());
    C.setIndex(C.getEdgeCount()); D.setIndex(D.getEdgeCount());
    E.setIndex(E.getEdgeCount()); F.setIndex(F.getEdgeCount());
    
    g.insertVertex(Ap); g.insertVertex(Bp); g.insertVertex(Cp);
    g.insertVertex(Dp); g.insertVertex(Ep); g.insertVertex(Fp);
    g.insertEdge(e1aP); g.insertEdge(e1bP);
    g.insertEdge(e2aP); g.insertEdge(e2bP);
    g.insertEdge(e3aP); g.insertEdge(e3bP);
    g.insertEdge(e4aP); g.insertEdge(e4bP);
    g.insertEdge(e5aP); g.insertEdge(e5bP);
    g.insertEdge(e6aP); g.insertEdge(e6bP);
    g.insertEdge(e7aP); g.insertEdge(e7bP);
    g.insertEdge(e8aP); g.insertEdge(e8bP);
    g.insertEdge(e9aP); g.insertEdge(e9bP);
    g.insertEdge(e10aP); g.insertEdge(e10bP);
    g.insertEdge(e11aP); g.insertEdge(e11bP);
    
    double arrayOfResults[10] = { 0,0,0,0,0,0,0,0,0,0 };
    double arrayOfEdgeResults[11] = { 0,0,0,0,0,0,0,0,0,0,0 };
    int graphSize = g.getVertexCount();
    int input = instructions();
    int tests = testInstructions();
    
    for (int i = 0; i < tests; i++) {
        Vertex* randomStart = g.randomVertex();
        quasiWalk(input, g, randomStart, arrayOfResults, arrayOfEdgeResults);
    }
    
    cout << "-RESULTS--------------------------" << endl;
    cout << "-Number of STEPS per TEST: " << input << endl;
    cout << "-Number of TESTS: " << tests << endl;
    cout << "  Average Visited Count for Vertices" << endl;
    for (int i = 0; i < graphSize; i++) {
        arrayOfResults[i] /= tests;
        cout << "    " << g.returnVertex(i)->getName() << ": " << arrayOfResults[i] << endl;
    }
    cout << "  Average Visited Count for Edges" << endl;
    for (int i = 0; i < g.getEdgeCount(); i++) {
        arrayOfEdgeResults[i] /= tests;
        cout << "    " << edgeList[i]->getName() << ": " << arrayOfEdgeResults[i] << endl;
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
        start->edgeToCross(start, currentIndex)->incrementVisitCount();
        Edge* cross = start->edgeToCross(start, currentIndex);
        destination = cross->getEndVertex();
    
        cout << "[Step " << i+1 << "] Agent crosses the EDGE (between) "
             << cross->getStartVertex()->getName() << " and " << cross->getEndVertex()->getName()
             << " and is now at VERTEX " << cross->getEndVertex()->getName() << endl;
        
        destination->incrementVisited();
        start->changeIndex();
        start = destination;
    }
    return destination;
}

void quasiWalk(int steps, Graph g, Vertex* s, double resultsV[], double resultsE[]) {
    int graphVertexCount = g.getVertexCount();
    int currentEdgeID = 0;
    Edge* currentEdge = NULL;
    mobileAgent(g, s, steps);
    for (int i = 0; i < graphVertexCount; i++) {
        resultsV[i] += g.returnVertex(i)->getVisited();
        for (int j = 0; j < g.returnVertex(i)->getEdgeCount(); j++) {
            currentEdge = g.returnVertex(i)->returnEdge(j);
            currentEdgeID = currentEdge->getID();
            resultsE[currentEdgeID] += currentEdge->getVisitCount();
            currentEdge->resetVisitCountEdge();
        }
        g.returnVertex(i)->setVisitToZero();
        g.returnVertex(i)->resetAllEdgeVisits();
    }
    //g.printGraph();
}

//--------------------------------------------