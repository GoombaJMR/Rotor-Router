//-----------------------------------------------//
//  RotorRouterMechanism Final Version A --------//
//  Graph.h    ----------------------------------//
//  Created by Julian M. Rice | August 2018 -----//
//-----------------------------------------------//

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

class Graph {
public:
    Graph() { };
    void insertVertex(Vertex* vertex);      //Add a vertex to the graph
    void insertEdge(Edge* edge);            //Add an edge to the graph
    void insertEdgeToOverall(Edge* edge);   //Add an edge to the traversal history vector
    void insertEdgeToCycle(Edge* edge);     //Add an edge to the euler cycle vector
    Vertex* randomVertex();                 //Return a random vertex (agent starting vertex)
    Vertex* returnVertex(int index)         //Return a vertex given an index (0 to V-1)
    {  return vertices[index]; }
    Edge* returnEdge(int index)             //Return an edge given an index (0 to E-1)
    { return edges[index]; }
    Edge* returnEdgeFromOverall(int index)  //Return an edge from the traversal history vector
    { return overallCycle[index]; }
    Edge* returnEdgeFromCycle(int index)    //Return an edge from the lock in euler cycle
    { return eulerCycle[index]; }
    int getVertexCount()                    //Return the number of vertices in the graph
    { return vertices.size(); }
    int getEdgeCount()                      //Return the number of edges in the graph
    { return edges.size(); }
    int getOverallCount()                   //Return the length of the traversal (# of steps)
    { return overallCycle.size(); }
    void printGraph();                      //Print the status for each vertex, edge
    void resetOverallCycle();               //Pop all values in the traversal history vector
    void resetEulerCycle();                 //Pop all values in the euler cycle vector
private:
    vector<Vertex*> vertices;   //Holds all vertex pointers in the graph
    vector<Edge*> edges;        //Holds all edge pointers in the graph
    vector<Edge*> overallCycle; //Holds the traversal history for an agent (S steps)
    vector<Edge*> eulerCycle;   //Holds the euler cycle that the agent locks-in
};

#endif
