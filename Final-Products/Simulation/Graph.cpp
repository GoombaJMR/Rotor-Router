//-----------------------------------------------//
//  RotorRouterMechanism Final Version A --------//
//  Graph.cpp    --------------------------------//
//  Created by Julian M. Rice | August 2018 -----//
//-----------------------------------------------//

#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include "Functions.h"

void Graph::insertVertex(Vertex* vertex) {
    vertices.push_back(vertex);
}

void Graph::insertEdge(Edge* edge) {
    edges.push_back(edge);
}

void Graph::insertEdgeToOverall(Edge* edge) {
    overallCycle.push_back(edge);
}

void Graph::insertEdgeToCycle(Edge* edge) {
    eulerCycle.push_back(edge);
}

Vertex* Graph::randomVertex() {
    int numOfVertices = vertices.size();
    int randomId = randomInteger(0, numOfVertices-1);
    return vertices[randomId];
}

void Graph::printGraph() {
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i]->printStatus();
        vertices[i]->printEdges();
    }
}

void Graph::resetOverallCycle() {
    for (int i = 0; i < overallCycle.size(); i++) {
        overallCycle.pop_back();
    }
}

void Graph::resetEulerCycle() {
    for (int i = 0; i < eulerCycle.size(); i++) {
        eulerCycle.pop_back();
    }
}
