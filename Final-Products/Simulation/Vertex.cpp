//-----------------------------------------------//
//  RotorRouterMechanism Final Version A --------//
//  Vertex.cpp    -------------------------------//
//  Created by Julian M. Rice | August 2018 -----//
//-----------------------------------------------//

#include "Edge.h"
#include "Vertex.h"
#include "Functions.h"
#include <iostream>

using namespace std;

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
    cout << "   | Edges of VERTEX " << m_name << " |" << endl;
    for (int i = 0; i < edges.size(); i++) {
        Edge* e = edges[i];
        cout << "-- Edge " << i+1 << ": ";
        cout << e->getEndVertex()->getName() << endl;
    }
    cout << endl;
}
