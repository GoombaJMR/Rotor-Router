//-----------------------------------------------//
//  RotorRouterMechanism Final Version A --------//
//  Vertex.h    ---------------------------------//
//  Created by Julian M. Rice | August 2018 -----//
//-----------------------------------------------//

#ifndef VERTEX_H
#define VERTEX_H

#include <stdio.h>
#include <string>
#include "Edge.h"

using namespace std;

class Edge;

class Vertex {
public:
    Vertex(string name, int index, int visitedCount, int edgeCount);
    void addEdge(Edge* newEdge);    //Add an edge to the vertex (degree increased)
    void setIndex(int edgeCount);   //Set the starting next exit value (random)
    void setVisitToZero()   { m_visitedCount = 0; } //Reset visit count to 0
    void incrementVisited() { m_visitedCount++; }   //Increase visit count by 1
    void changeIndex()  //Change vertex index to next in fixed cyclic order
        { m_index = (m_index + 1) % m_edgeCount; }
    void resetAllEdgeVisits();      //Reset visit count for all connected edges to 0
    void printStatus();             //Print visit count
    void printEdges();              //Print vertices this vertex is connected to
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

#endif
