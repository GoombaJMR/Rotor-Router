//-----------------------------------------------//
//  RotorRouterMechanism Final Version A --------//
//  Edge.cpp    ---------------------------------//
//  Created by Julian M. Rice | August 2018 -----//
//-----------------------------------------------//

#include "Edge.h"
#include "Vertex.h"
#include <string>
#include <vector>

using namespace std;

Edge::Edge(Vertex* start, Vertex* destination, int id, string name) {
    m_start = start;
    m_destination = destination;
    m_id = id;
    m_name = name;
    m_checkForCycle = 0;
    m_visitCount = 0;
}
