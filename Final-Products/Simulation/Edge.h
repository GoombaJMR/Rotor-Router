//-----------------------------------------------//
//  RotorRouterMechanism Final Version A --------//
//  Edge.h    -----------------------------------//
//  Created by Julian M. Rice | August 2018 -----//
//-----------------------------------------------//

#ifndef EDGE_H
#define EDGE_H

#include <stdio.h>
#include <vector>
#include "Vertex.h"

using namespace std;
class Vertex;

class Edge {
public:
    Edge(Vertex* start, Vertex* destination, int id, string name);
    void incrementVisitCount()          { m_visitCount++; }
    void incrementCheck()               { m_checkForCycle++; }
    void resetVisitCountEdge()          { m_visitCount = 0; }
    void resetCycleCountCheck()         { m_checkForCycle = 0; }
    void changeStartVertex(Vertex* s)   { m_start = s; }
    void changeEndVertex(Vertex* e)     { m_destination = e; }
    int getVisitCount()                 { return m_visitCount; }
    int getID()                         { return m_id; }
    int getCheck()                      { return m_checkForCycle; }
    string getName()                    { return m_name; }
    Vertex* getStartVertex()            { return m_start; }
    Vertex* getEndVertex()              { return m_destination; }
private:
    int m_visitCount;
    int m_id;
    int m_checkForCycle;
    string m_name;
    Vertex* m_start;
    Vertex* m_destination;
};

#endif
